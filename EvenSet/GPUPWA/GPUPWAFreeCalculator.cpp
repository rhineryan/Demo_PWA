#include "GPUPWAFreeCalculator.h"

#include "GPUPartialWaveAnalysis.h"
#include "GPUDataStream.h"
#include "GPUIndexStream.h"
#include "GPUPropagatorType.h"
#include "GPULookupTable.h"
#include "GPUStreamTensor.h"
#ifdef USECPU
#include "Analysis_cpu.h"
#else
#include "Analysis.h"
#endif
#include <Minuit2/MnMigrad.h>
#include <Minuit2/MnFumiliMinimize.h>
#include <Minuit2/FunctionMinimum.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <vector>

using std::ofstream;
using std::ifstream;
using std::ios;
using std::setprecision;
using std::cout;
using std::endl;
using std::vector;
using std::iterator;

#ifdef USECPU
using namespace Analysis_CPU;
#else
using namespace Analysis_GPU;
#endif

GPUPWAFreeCalculator::GPUPWAFreeCalculator(GPUPartialWaveAnalysis * _ana,
		GPULookupTable * _datalookup,
		GPULookupTable * _mclookup,
		std::vector<GPUDataStream<float4> **> _Weights):
	GPUPWACalculator(_ana, _Weights),
	mAna(_ana),
	mLookupData(_datalookup), mLookupMC(_mclookup),
	mNCoefficientBlocksData(_datalookup->GetNBlocks()), mNAdditionalEventsData(_datalookup->GetNAdditional()),
	mNCoefficientBlocksMC(_mclookup->GetNBlocks()), mNAdditionalEventsMC(_mclookup->GetNAdditional())
{
	mParmatrix = mAna->parmatrix();
	mFitinit = false;
}


GPUPWAFreeCalculator::~GPUPWAFreeCalculator(void)
{
	clearMCIntegralCoefficients();
	delete [] mParmatrix;

	cleanupFit();

	double sum =0;
	for(unsigned int i =1; i < mfittimes.size(); i++){
		sum+= mfittimes[i];
	}
	if(sum >0)
		std::cout << "Average Fit time: " << sum/(mfittimes.size()-1) << "s (" << mfittimes.size() << " iterations, of which " << mfittimes.size()-1 << " considered)."<< std::endl;
}


void GPUPWAFreeCalculator::cleanupFit(){
  // clean up resources allocated for the fit
  if(mFitinit){
    for(int i=0; i < mNCoefficientBlocksData; i++){
      delete mdcs[i];
    }
    delete [] mdcs;
    delete mlogdcs;
    delete mshortlogdcs;

  }
}


double GPUPWAFreeCalculator::Likelihood(const vector<double> & pars){
	vector<double> dummy;
	return LikelihoodGradientHessianCalc(pars, dummy, dummy, false, false);
}


double GPUPWAFreeCalculator::LikelihoodGradient(const vector<double> & pars, vector<double> & grad){
	vector<double> dummy;
	cout << "ERROR: Gradient and Hessians with free parameters not yet supported!" << endl;
	assert(0);
	return LikelihoodGradientHessianCalc(pars, grad, dummy, true, false);
}


double GPUPWAFreeCalculator::LikelihoodGradientHessian(const vector<double> & pars, vector<double> & grad, vector<double> & hessian){
	cout << "ERROR: Gradient and Hessians with free parameters not yet supported!" << endl;
	assert(0);
	return LikelihoodGradientHessianCalc(pars, grad, hessian, true, true);
}


double GPUPWAFreeCalculator::LikelihoodGradientHessianCalc(const vector<double> & pars, vector<double> & gradient, vector<double> & hessian, bool dogradient, bool dohessian){
	/* This is the real meat: where all the actual calculations happen and all the time is spent.
     I will thus comment in some detail on what is going on... */

	// We do of course quite a bit of timing stuff, so we know where we spend time
	clock_t beforeall = clock();
	// Make sure we have got the event weights set (a few other things should probably
	// be checked as well) -> TODO!
	assert(mWeights[mAna->GetDataIndex()]);
	// Write the parameters we have received (from the fitter) to the analysis
	mAna->SetParameterVector(pars);

	// Check whether we have already calculated the coefficients for the fit (Data)
	if(!mLookupData->CacheValid()){
//		clock_t before = clock();
		// if not, prepare the lookup table
		mLookupData->FillTable();
//		clock_t after = clock();
		// note that this timing is not reliable, as the transfer of the tables to the GPU happens asynchronously
//		cout << "Lookup Table creation (Data):" << (after-before) << " ticks = " <<  (float)(after-before)/(float)CLOCKS_PER_SEC << " s" << endl;
	}

	// Check whether we have already calculated the coefficients for the fit (MC)
	if(!mLookupMC->CacheValid()){
	//	clock_t before = clock();
		// if not, prepare the lookup table
		mLookupMC->FillTable();
//		clock_t after = clock();
		// note that this timing is not reliable, as the transfer of the tables to the GPU happens asynchronously
//		cout << "Lookup Table creation (MC):" << (after-before) << " ticks = " <<  (float)(after-before)/(float)CLOCKS_PER_SEC << " s" << endl;
	}

	// Empty the gradient vector
	gradient.clear();

	int nwaves = mLookupData->GetNWaves();

	// Get parameter streams
	GPUDataStream<float2> * mypars = mAna->pars2streamCartesian();
	//  Stream<float2> * myparsPolar = mAna->pars2streamPolar();

	// The following stuff is repeated in every iteration, should we make member variables? -> TODO
	mpsize = (int)mAna->GetParameters()->Params().size();

	// Create vector pnums with indices of the active parameters and count them
	std::vector<int> pnums;
	int nactive =0;
	for(int i =0; i < mpsize; i++){
		if(!(mAna->GetParameters()->Parameter(i).IsFixed())){
			nactive++;
			pnums.push_back(i);
		}
	}

	//cout << "going to create storage" << endl;
	// Create all the storage on CPU and GPU needed for the fit in the first iteration
	if(!mFitinit){
		counter =0;
		clock_t before = clock();

		unsigned int maxblocksizedata = mAna->Blocksize;
		if(mNCoefficientBlocksData == 1 && mNAdditionalEventsData != 0){
			maxblocksizedata = mNAdditionalEventsData;
		}

		unsigned int maxblocksizemc = mAna->Blocksize;
		if(mNCoefficientBlocksMC == 1 && mNAdditionalEventsMC != 0){
			maxblocksizemc = mNAdditionalEventsMC;
		}

		mdcs = new GPUDataStream<float4>*[mNCoefficientBlocksData];

		mlogdcs = new GPUDataStream<float4>(mdev, maxblocksizedata);

		mdcsmc = new GPUDataStream<float4>(mdev, maxblocksizemc);

		// The last block of events usually contains less than 8192*4 events and is treated separately
		if(mNAdditionalEventsData != 0){
			mshortlogdcs = new GPUDataStream<float4>(mdev, mNAdditionalEventsData);
		} else {
			mshortlogdcs = new GPUDataStream<float4>(mdev, maxblocksizedata);
		}

		// The last block of events usually contains less than 8192*4 events and is treated separately
		if(mNAdditionalEventsMC != 0){
			mshortdcsmc = new GPUDataStream<float4>(mdev, mNAdditionalEventsMC);
		} else {
			mshortdcsmc = new GPUDataStream<float4>(mdev, maxblocksizemc);
		}


		for(int i=0; i < mNCoefficientBlocksData; i++){
			int size = maxblocksizedata;
			if( i == mNCoefficientBlocksData-1 && mNAdditionalEventsData != 0)
				size = mNAdditionalEventsData;
			mdcs[i] = new GPUDataStream<float4>(mdev, size);
		}

		// Fit init is done, takes some time (again not reliable due to async transfers)
		mFitinit = true;
		clock_t after = clock();
		cout << "Memory Allocation :" << (after-before) << " ticks = " <<  (float)(after-before)/(float)CLOCKS_PER_SEC << " s" << endl;
	}


	// Pointers for switching between long and short versions
	GPUDataStream<float4> * logdcs =0;
	GPUDataStream<float4> * mcdcs =0;

	GPUDataStream<float4> ** mcweights = mAna->GetWeights(mAna->GetMCIndex());
	// Calculate the total X-section
	double tcs = 0.0;
	unsigned int num;
	for(int b=0; b < mNCoefficientBlocksMC; b++){
		if( b == mNCoefficientBlocksMC-1 && mNAdditionalEventsMC != 0){
			mcdcs = mshortdcsmc;
			num = mNAdditionalEventsMC;
		} else {
			mcdcs = mdcsmc;
			num = mAna->Blocksize;
		}


		if(mcweights){
			pwamultdcsonly4weighted(cl::NDRange(num),
							mdev,
							mLookupMC->GetCoefficientsX(b),
							mLookupMC->GetCoefficientsY(b),
							mcweights[b],
							mypars, nwaves, (float)0.0,
							mcdcs);
		} else {
			pwamultdcsonly4(cl::NDRange(num),
							mdev,
							mLookupMC->GetCoefficientsX(b),
							mLookupMC->GetCoefficientsY(b),
							mypars, nwaves, (float)0.0,
							mcdcs);
		}
		tcs += mcdcs->sum();

	}

	double accfrac = (double)mAna->GetSumOfWeights(mAna->GetMCIndex())/(double)mAna->GetNumberMCGen();
	tcs = tcs/mAna->GetNumberMCGen() + mAna->GetParameters()->Value((unsigned int)0)*accfrac;

	//cout << "TCS: " << tcs << endl;

	// clock_t before = clock();
	double sum = 0.0;
	for(int b=0; b < mNCoefficientBlocksData; b++){
		// Select long or short version
		if( b == mNCoefficientBlocksData-1 && mNAdditionalEventsData != 0){
			logdcs = mshortlogdcs;
			num = mNAdditionalEventsData;
		} else {
			logdcs = mlogdcs;
			num = mAna->Blocksize;
		}

	    pwamult4(cl::NDRange(num),
	    		mdev,
	    		(mWeights[mAna->GetDataIndex()][b]),
	    		mLookupData->GetCoefficientsX(b),
	    		mLookupData->GetCoefficientsY(b),
	    		mypars,
	    		nwaves,
	    		(float)mAna->GetParameters()->Value((unsigned int)0),
	        	(float)tcs,
	        	(mdcs[b]),
	        	logdcs);

	    //mLookupData->GetCoefficientsX(b)->printAt(0,num*10);
	    //mLookupData->GetCoefficientsY(b)->printAt(0,num*10);

	    double partsum = logdcs->sum();
	    //cout << "b : " << b << " partsum: "<< partsum << endl;
		sum += partsum;

	}
	//assert(0);
	sum += mAna->GetConstraintLHContribution();
	//cout << "sum: " << sum << endl;

	clock_t afterall = clock();
	//  cout << "Fit time :" << (afterall-beforeall) << " ticks = " <<  (float)(afterall-beforeall)/(float)CLOCKS_PER_SEC << " s" << endl;
	mfittimes.push_back((float)(afterall-beforeall)/(float)CLOCKS_PER_SEC);
	cout << ".";
	cout.flush();
	return sum;
}


