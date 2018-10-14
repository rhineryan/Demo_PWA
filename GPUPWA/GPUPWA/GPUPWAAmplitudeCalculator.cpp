#include "GPUPWAAmplitudeCalculator.h"

#include "GPUPartialWaveAnalysis.h"
#include "GPUDataStream.h"
#include "GPUIndexStream.h"
#include "GPULookupTable.h"
#include "GPUStreamTensor.h"
#include "float44.h"
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
#include "Analysis_cpu.h"
using namespace Analysis_CPU;
#else
#include "Analysis.h"
using namespace Analysis_GPU;
#endif




GPUPWAAmplitudeCalculator::GPUPWAAmplitudeCalculator(GPUPartialWaveAnalysis * _ana, GPULookupTable * const _table,GPULookupTable * const _mctable, std::vector<GPUDataStream<float4> **> _Weights, char * _mcintegralfilename):
	GPUPWACalculator(_ana, _Weights), mAna(_ana),
	mLookupTable(_table),mMCLookupTable(_mctable),
	mNCoefficientBlocks(_table->GetNBlocks()),mNAdditionalEvents(_table->GetNAdditional()),
	mNMCCoefficientBlocks(_mctable->GetNBlocks()),mNMCAdditionalEvents(_mctable->GetNAdditional()),
	mMCIntegralCoefficients(0)
{
	mParmatrix = mAna->parmatrix();
	if(_mcintegralfilename)
		ReadMCIntegralFile( _mcintegralfilename);

	mFitinit = false;

	minnergradients = 0;
	mgradients = 0;
	mshortgradients =0;

	mhessian =0;
	mshorthessian =0;

	mmask =0;
}

GPUPWAAmplitudeCalculator::~GPUPWAAmplitudeCalculator(void)
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


void GPUPWAAmplitudeCalculator::cleanupFit(){
  // clean up resources allocated for the fit
  if(mFitinit){
    for(int i=0; i < mNCoefficientBlocks; i++){
      delete mdcs[i];
    }
    delete [] mdcs;
    delete mlogdcs;
    delete mshortlogdcs;


    delete mgradindex;

    delete mdtcs;

    if(minnergradients){
    	for(int i=0; i < mNCoefficientBlocks; i++){
    		if(minnergradients[i])
    			delete minnergradients[i];
    	}
    	delete [] minnergradients;
    }

    if(mgradients)
    	delete mgradients;
    if(mshortgradients)
    	delete mshortgradients;

    if(mhessian)
    	delete mhessian;
    if(mshorthessian)
    	delete mshorthessian;

    if(mmask)
    	delete mmask;
  }
}


double GPUPWAAmplitudeCalculator::Likelihood(const vector<double> & pars){
	vector<double> dummy;
	return LikelihoodGradientHessianCalc(pars, dummy, dummy, false, false);
}


double GPUPWAAmplitudeCalculator::LikelihoodGradient(const vector<double> & pars, vector<double> & grad){
	vector<double> dummy;
	return LikelihoodGradientHessianCalc(pars, grad, dummy, true, false);
}


double GPUPWAAmplitudeCalculator::LikelihoodGradientHessian(const vector<double> & pars, vector<double> & grad, vector<double> & hessian){
	return LikelihoodGradientHessianCalc(pars, grad, hessian, true, true);
}

double GPUPWAAmplitudeCalculator::LikelihoodGradientHessianCalc(const vector<double> & pars, vector<double> & gradient, vector<double> & hessian, bool dogradient, bool dohessian){
  /* This is the real meat: where all the actual calculations happen and all the time is spent.
     I will thus comment in some detail on what is going on... */
	//cout << "In calc!" << endl;
  // We do of course quite a bit of timing stuff, so we know where we spend time
  clock_t beforeall = clock();
  // Make sure we have got the event weights set (a few other things should probably
  // be checked as well) -> TODO!
  assert(mWeights[mAna->GetDataIndex()]);
  // Write the parameters we have received (from the fitter) to the analysis
  mAna->SetParameterVector(pars);

  // Check wheter we have already calculated the coefficients for the fit
  if(!mLookupTable->CacheValid()){
	 // cout << "Cache not valid" << endl;
    clock_t before = clock();
    // if not, prepare the lookup table
    mLookupTable->FillTable();
    clock_t after = clock();
    // note that this timing is not reliable, as the transfer of the tables to the GPU happens asynchronously
    cout << "Lookup Table creation :" << (after-before) << " ticks = " <<  (float)(after-before)/(float)CLOCKS_PER_SEC << " s" << endl;
  }
  //cout << "LUT ok!" << endl;
  // Check wheter the MC integral coefficients are ready
  if(!mMCIntegralCoefficients){
    clock_t before = clock();
    // If not, read the corresponding file
    ReadMCIntegralFile();
    clock_t after = clock();
    cout << "Reading MC Integral File :" << (after-before) << " ticks = " <<  (float)(after-before)/(float)CLOCKS_PER_SEC << " s" << endl;
  }
  // Empty the gradient vector
  gradient.clear();

  // Calculate TCS  (could we do that somehere where it is more parallel to the GPU? ->TODO
  double tcs = TotalXSection();

  int nwaves = mLookupTable->GetNWaves();

  // Get parameter streams
  GPUDataStream<float2> * mypars = mAna->pars2streamCartesian();
  GPUDataStream<float2> * myparsPolar = mAna->pars2streamPolar();

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

  mngrad = pnums.size();
  unsigned int nhessian = mngrad*(mngrad+1)/2;
  //If all the parameters are fixed, make sure we do not crash the program.
  // Also no gradients/hessian are required.
  if(nactive==0){
	  nactive = 1;
	  pnums.push_back(-1);
	  dogradient = false;
	  dohessian = false;
  }
  // Size of the hessian matrix (uper right+diagonal)
  int parmatsize = nactive*(nactive+1)/2;

  // Number of results from GPU summing
  //int sumblocks = mNCoefficientBlocks*2;
  //if(mNAdditionalEvents != 0)
  //  sumblocks = (mNCoefficientBlocks-1)*2;



  // Create all the storage on CPU and GPU needed for the fit in the first iteration
  if(!mFitinit){
    counter =0;
    clock_t before = clock();

    mdcs = new GPUDataStream<float4>*[mNCoefficientBlocks];

    unsigned int maxblocksize = mAna->Blocksize;
    if(mNCoefficientBlocks == 1 && mNAdditionalEvents != 0){
    	maxblocksize = mNAdditionalEvents;
    }

    mgradindex = new GPUGradientIndexStream(mdev, pnums);

    mlogdcs = new GPUDataStream<float4>(mdev, maxblocksize);
    unsigned int dims7[] = {maxblocksize, nhessian};
    mhessian = new GPUDataStream<float4>(mdev,dims7);


    // The last block of events usually contains less than 8192*4 events and is treated separately
    if(mNAdditionalEvents != 0){
      mshortlogdcs = new GPUDataStream<float4>(mdev, mNAdditionalEvents);
      unsigned int dims8[] = {mNAdditionalEvents,nhessian};
      mshorthessian =  new GPUDataStream<float4>(mdev, dims8);
    } else {
      mshortlogdcs = new GPUDataStream<float4>(mdev, mAna->Blocksize);
      unsigned int dims8[] = {mAna->Blocksize,nhessian};
      mshorthessian =  new GPUDataStream<float4>(mdev, dims8);
    }

    for(int i=0; i < mNCoefficientBlocks; i++){
      int size = maxblocksize;
      if( i == mNCoefficientBlocks-1 && mNAdditionalEvents != 0)
    	  size = mNAdditionalEvents;
      mdcs[i] = new GPUDataStream<float4>(mdev, size);
    }
    mdtcs = new GPUDataStream<float>(mdev, mpsize);


    minnergradients = new GPUDataStream<float4> *[mNCoefficientBlocks];

    for(int j=0; j < mNCoefficientBlocks; j++){
    	unsigned int size = maxblocksize;
    	if( j == mNCoefficientBlocks-1 && mNAdditionalEvents != 0)
     	  size = mNAdditionalEvents;
       unsigned int dims9[] = {size,mngrad};
       minnergradients[j] = new GPUDataStream<float4>(mdev, dims9);
     }

    unsigned int dims8[] = {maxblocksize,mngrad};
    mgradients = new GPUDataStream<float4>(mdev,dims8);

    if(mNAdditionalEvents != 0){
    	unsigned int dims9[] = {mNAdditionalEvents,mngrad};
    	mshortgradients = new GPUDataStream<float4>(mdev, dims9);
    }

    // Mask of parameter-gradient relations
    unsigned int dims10[] = {2*nwaves, mpsize};
    mmask = new GPUDataStream<float>(mdev, dims10);
    (mmask)->Write(&(mParmatrix[0][0]));
    //cout << "waiting for mask" << endl;
    //mmask->GetEvent().wait();
    // Fit initi is done, takes some time (again not reliable due to async transfers)
    mFitinit = true;
    clock_t after = clock();
    cout << "Memory Allocation :" << (after-before) << " ticks = " <<  (float)(after-before)/(float)CLOCKS_PER_SEC << " s" << endl;
  }

  // Pointers for switching between long and short versions
  GPUDataStream<float4> * logdcs =0;

 // clock_t before = clock();
  double sum = 0.0;
  unsigned int num;
  for(int b=0; b < mNCoefficientBlocks; b++){
    // Select long or short version
    if( b == mNCoefficientBlocks-1 && mNAdditionalEvents != 0){
      logdcs = mshortlogdcs;
      num = mNAdditionalEvents;
    } else {
      logdcs = mlogdcs;
      num = mAna->Blocksize;
    }
    //cout << "Nadd " << mNAdditionalEvents << endl;
  //  cout << num << endl;
  //  cout << "Weights: " <<(mWeights[mAna->GetDataIndex()][b])->GetD1() << endl;
  //  cout << "Coeffx : " << (mCoefficientsx[b])->GetD1() << ", " << (mCoefficientsx[b])->GetD2() <<endl;
    // Main kernel call, calculates log likelihood and dcs
    //mCoefficientsy[b]->printAt(0,num*10);
 //   mypars->printAt(0,4);
  //  cout << "tcs " << tcs << endl;
   // cout << "Bgpar "<< mAna->GetParameters()->Value((unsigned int)0) << endl;
  //  assert(0);

    pwamult4(cl::NDRange(num),
    		mdev,
    		(mWeights[mAna->GetDataIndex()][b]),
    		mLookupTable->GetCoefficientsX(b),
    		mLookupTable->GetCoefficientsY(b),
    		mypars,
    		nwaves,
    		(float)mAna->GetParameters()->Value((unsigned int)0),
        	(float)tcs,
        	(mdcs[b]),
        	logdcs);
    //if(b==1){
    	//(mWeights[mAna->GetDataIndex()][b])->printAt(0,num);
    	//(mWeights[mAna->GetDataIndex()][b])->printAt(0,num);
    	//mLookupTable->GetCoefficientsX(b)->printAt(0,num);
    	//mLookupTable->GetCoefficientsY(b)->printAt(1000,100);
    	// logdcs->printAt(0,num);
    	//assert(0);
    //}
   //   cout << "Running pwamult..." << endl;
    //  logdcs->GetEvent().wait();
    //  cout << "dcs" <<endl;
    //  mdcs[b]->print();
    //  cout << "log"<< endl;
 //   cout << "Logdcs for block " << b << endl;
    //logdcs->print();
   //   cout << "C sum is " << sum << endl;
      double partsum = logdcs->sum(true);
      //cout << "Partsum: " << partsum << " per ev: " << partsum/num <<  endl;
      sum += partsum;
  //    cout << "sum is " << sum << endl;
   //   if(!(sum < 1e9))

  }

  // Add contribution from constraints
  sum += mAna->GetConstraintLHContribution();

  //cout << "Sum is " << sum << endl;
  //assert(0);

  /*	for(int i =0; i < mpsize; i++)
    if(!(mAna->GetParameters()->Parameter(i).IsFixed()))
    cout << "Par " << i << ": " << pars[i] <<  endl; */
//  clock_t after = clock();
 // cout << "Likelihood :" << (after-before) << " ticks = " <<  (float)(after-before)/(float)CLOCKS_PER_SEC << " s" << endl;
 // before = clock();

  // Calculate gradient
  if(dogradient || dohessian){
	  GPUDataStream<float4> * gradients = 0;
	  float dtcstemp[mpsize];
	  // Get DCS derivatives
	  for(int i =0; i < mpsize; i++){
		  if(!(mAna->GetParameters()->Parameter(i).IsFixed())){
			  dtcstemp[i]  = (float)TotalXSectionDerivative(i);
		  } else {
			  dtcstemp[i]  = 0.0f;
		  }
	  }
	  // Write dcs derivatives to GPU
	  mdtcs->Write(dtcstemp);
//	  cout << "dTCS" << endl;
//	  mdtcs->print();

	  // Zero the gradient vector
	  for(int i =0; i < mpsize; i++){
		  gradient.push_back(0);
	  }
	  for(int b=0; b < mNCoefficientBlocks; b++){
		  int length;
		  // Switch between short and long blocks
		  if( b == mNCoefficientBlocks-1 && mNAdditionalEvents != 0){
			  gradients = mshortgradients;
			  length = mNAdditionalEvents;

		  } else {
			  gradients = mgradients;
			  length = mAna->Blocksize;
		  }


		  //gradients = mgradients;
		  //cout << "Gradindex" << endl;
		  //mgradindex->printAt(0,pnums.size());
		  //cout << "Mask" << endl;
		  //mmask->printAt(0,2*nwaves*mpsize);
		  // Main kernel call, calculates likelihood gradients and inner gradients for use in the hessian
		  pwagradmult4all(cl::NDRange(length*mngrad), mdev,
				  mgradindex, mWeights[mAna->GetDataIndex()][b],
				  mdcs[b],
				  mLookupTable->GetCoefficientsX(b),
				  mLookupTable->GetCoefficientsY(b),
				  myparsPolar,
				  nwaves, mngrad, (mmask),
				  (float)mAna->GetParameters()->Value((unsigned int)0),
				  (float)tcs, mdtcs, gradients,
				  (minnergradients[b]));

//	cout << "TCS: " << tcs << endl;

	//  gradients->print();
	//  cout << "inner: " << b << endl;
	 // minnergradients[b]->print();
	//	  assert(0);

		  int activeindex =0;
		  double * gtemp = gradients->sum2d(mngrad);

	//	  cout << "inner after sum: " << b << endl;
	//			  minnergradients[b]->print();

		  for(int i =0; i < mpsize; i++){
			  if(!(mAna->GetParameters()->Parameter(i).IsFixed())){
				  assert(activeindex < mngrad);
			//	  cout << "Gradient " << i <<": " <<gtemp[activeindex] << endl;
				  gradient[i] += gtemp[activeindex];
				  activeindex++;
			  }
		  }


	  }

	  // Add contribution from constraints
	  for(unsigned int i =0; i < (unsigned int)mpsize; i++){
		  if(!(mAna->GetParameters()->Parameter(i).IsFixed()))
			  gradient[i] += mAna->GetConstraintGradientContribution(i);
	  }

	/*  for(int i =0; i < mpsize; i++){
		  if(!(mAna->GetParameters()->Parameter(i).IsFixed()))
			  cout << "Gradient " << i << ": " << gradient[i] << endl;
      }*/

  }


 // after = clock();
 // cout << "Gradient :" << (after-before) << " ticks = " <<  (float)(after-before)/(float)CLOCKS_PER_SEC << " s" << endl;
//  before = clock();



  if(dohessian){
	  // Hessian
	  //zero the output vector
	  // clock_t before = clock();
	  for(int i =0; i < mpsize; i++){
		  for(int j =i; j < mpsize; j++){
			  hessian[i+j*(j+1)/2] = 0;
		  }
	  }
	  // clock_t after = clock();
	  // cout << "Zero vector :" << (after-before) << " ticks = " <<  (float)(after-before)/(float)CLOCKS_PER_SEC << " s" << endl;
	  // before = clock();

	  GPUDataStream<float4> * hessianstream;
	  int length =0;
	  //for(int k=0; k < mNCoefficientBlocks; k++){
	  for(int k= mNCoefficientBlocks-1; k >=0; k--){
		  // Switch between short and long blocks
		  if( k ==mNCoefficientBlocks-1 && mNAdditionalEvents != 0){
			  hessianstream = mshorthessian;
			  length = mNAdditionalEvents;
		  } else {
			  hessianstream = mhessian;
			  length =mAna->Blocksize;
		  }
		  //unsigned int nhessian = mngrad*(mngrad+1)/2;
		  // Main kernel call, calculates hessian from inner gradients
	//	  cout << length << endl;
	//	  minnergradients[k]->print();
		  kernelhessian4all(cl::NDRange(length*nhessian),
				  	  	  	mdev,
				  	  	  	(minnergradients[k]),
				  	  	  	mdcs[k],
				  	  	  	mWeights[mAna->GetDataIndex()][k],
				  	  	  	mngrad,
				  	  	  	(float)mAna->GetParameters()->Value((unsigned int)0),
				  	  	  	(float)tcs,
				  	  	  	hessianstream);
	//	  hessianstream->GetEvent().wait();
	//	  cout << "Hessian" << endl;
	//	  hessianstream->print();


    	  double * htemp = hessianstream->sum2d(parmatsize,true);
    	  int cindex =0;
    	  for(int i =0; i < mpsize; i++){
    		  for(int j =i; j < mpsize; j++){
    			  if(!(mAna->GetParameters()->Parameter(i).IsFixed() || mAna->GetParameters()->Parameter(j).IsFixed())){
    				  hessian[i+j*(j+1)/2] += htemp[cindex];
    			//	  if(!(htemp[cindex] < 1e11))
    			//		  cout << htemp[cindex] << " at block " << k << ", i: " << i <<  ", j: " << j <<endl;
    				  cindex++;
    			  }
    		  }
    	  }

	  }

 //   after = clock();
//    cout << "Calculate :" << (after-before) << " ticks = " <<  (float)(after-before)/(float)CLOCKS_PER_SEC << " s" << endl;
  //  before = clock();


 //   after = clock();
 //      cout << "Sum rest :" << (after-before) << " ticks = " <<  (float)(after-before)/(float)CLOCKS_PER_SEC << " s" << endl;


 /*  for(int i =0; i < mpsize; i++){
	   if(!(mAna->GetParameters()->Parameter(i).IsFixed()))
		   for(int j =i; j < mpsize; j++){
			   if(!(mAna->GetParameters()->Parameter(j).IsFixed()))
				   cout << "Hessian: " << i <<", " << j << ": " << hessian[i+j*(j+1)/2] << endl;

    		}
   }*/

	// For the moment, we ignore off-diagonal contributions from the Hessian from constraints
   for(int i =0; i < mpsize; i++){
	   if(!(mAna->GetParameters()->Parameter(i).IsFixed())){
		   if(mAna->GetConstraintGradientContribution(i) != 0.0){
			   hessian[i+i*(i+1)/2] += mAna->GetConstraintHessianContribution(i,i);
		   }
	   }
   }
 }
//  after = clock();
//  cout << "Hessian :" << (after-before) << " ticks = " <<  (float)(after-before)/(float)CLOCKS_PER_SEC << " s" << endl;







//	cout << "Total X-Section " << tcs << " ";
//	cout << "Likelihood " << sum << endl;
 // counter++;
 // cout << counter << endl;
  clock_t afterall = clock();
//  cout << "Fit time :" << (afterall-beforeall) << " ticks = " <<  (float)(afterall-beforeall)/(float)CLOCKS_PER_SEC << " s" << endl;
  mfittimes.push_back((float)(afterall-beforeall)/(float)CLOCKS_PER_SEC);
  return sum;
}


STATUS GPUPWAAmplitudeCalculator::GetAmplitudes(const vector<double> & pars, char * filename){
	 /* This is the real meat: where all the actual calculations happen and all the time is spent.
	     I will thus comment in some detail on what is going on... */

	  // We do of course quite a bit of timing stuff, so we know where we spend time
	  clock_t beforeall = clock();
	  // Make sure we have got the event weights set (a few other things should probably
	  // be checked as well) -> TODO!
	  assert(mWeights[mAna->GetDataIndex()]);
	  // Write the parameters we have received (from the fitter) to the analysis
	  mAna->SetParameterVector(pars);

	  // Check wheter we have already calculated the coefficients for the fit
	  // Check wheter we have already calculated the coefficients for the fit
	  if(!mLookupTable->CacheValid()){
		  clock_t before = clock();
	      // if not, prepare the lookup table
	      mLookupTable->FillTable();
	      clock_t after = clock();
	      // note that this timing is not reliable, as the transfer of the tables to the GPU happens asynchronously
	      cout << "Lookup Table creation :" << (after-before) << " ticks = " <<  (float)(after-before)/(float)CLOCKS_PER_SEC << " s" << endl;
	  }
  // Check wheter the MC integral coefficients are ready
	/*  if(!mMCIntegralCoefficients){
	    clock_t before = clock();
	    // If not, read the corresponding file
	    ReadMCIntegralFile();
	    clock_t after = clock();
	    cout << "Reading MC Integral File :" << (after-before) << " ticks = " <<  (float)(after-before)/(float)CLOCKS_PER_SEC << " s" << endl;
	  }*/
	  // Calculate TCS  (could we do that somehere where it is more parallel to the GPU? ->TODO
	  double tcs = 1.0;//TotalXSection();

	  int nwaves = mLookupTable->GetNWaves();

	  // Get parameter streams
	  GPUDataStream<float2> * mypars = mAna->pars2streamCartesian();

	  // The following stuff is repeated in every iteration, should we make member variables?
	  mpsize = (int)mAna->GetParameters()->Params().size();




	  // Create all the storage on CPU and GPU needed for the fit in the first iteration
	  if(!mFitinit){
	    counter =0;
	    clock_t before = clock();

	    mdcs = new GPUDataStream<float4>*[mNCoefficientBlocks];

	    mlogdcs = new GPUDataStream<float4>(mdev, mAna->Blocksize);


	    // The last block of events usually contains less than 8192*4 events and is treated separately
	    if(mNAdditionalEvents != 0){
	      mshortlogdcs = new GPUDataStream<float4>(mdev, mNAdditionalEvents);
	    } else {
	      mshortlogdcs = new GPUDataStream<float4>(mdev, mAna->Blocksize);
	    }

	    for(int i=0; i < mNCoefficientBlocks; i++){
	      int size = mAna->Blocksize;
	      if( i == mNCoefficientBlocks-1 && mNAdditionalEvents != 0)
	    	  size = mNAdditionalEvents;
	      mdcs[i] = new GPUDataStream<float4>(mdev, size);
	    }

	    mFitinit = true;
	    clock_t after = clock();
	    cout << "Memory Allocation :" << (after-before) << " ticks = " <<  (float)(after-before)/(float)CLOCKS_PER_SEC << " s" << endl;
	  }

	  // Pointers for switching between long and short versions
	  GPUDataStream<float4> * logdcs =0;

	  FILE * f = fopen(filename, "w");



	  //float4 outbuffer[mAna->Blocksize];
float4 * outbuffer = new float4[mAna->Blocksize];


	 // clock_t before = clock();
	  unsigned int num;
	  for(int b=0; b < mNCoefficientBlocks; b++){
	    // Select long or short version
	    if( b == mNCoefficientBlocks-1 && mNAdditionalEvents != 0){
	      logdcs = mshortlogdcs;
	      num = mNAdditionalEvents;
	    } else {
	      logdcs = mlogdcs;
	      num = mAna->Blocksize;
	    }

	    pwamult4(cl::NDRange(num), mdev, (mWeights[mAna->GetDataIndex()][b]),
				  mLookupTable->GetCoefficientsX(b),
				  mLookupTable->GetCoefficientsY(b),
				  mypars,
				  nwaves, (float)mAna->GetParameters()->Value((unsigned int)0),
				  (float)tcs, (mdcs[b]),logdcs);

	    mdcs[b]->Read(outbuffer);

	    int nev = mAna->Blocksize;
	    if(b == mNCoefficientBlocks-1 && mNAdditionalEvents != 0)
	    	nev = mNAdditionalEvents;

	    for(int i =0; i < nev; i++){
	    	fprintf(f, "%e\n", outbuffer[i].x);
	    	fprintf(f, "%e\n", outbuffer[i].y);
	    	fprintf(f, "%e\n", outbuffer[i].z);
	    	fprintf(f, "%e\n", outbuffer[i].w);
	    }


	  }
	  fclose(f);

delete [] outbuffer;
	  clock_t afterall = clock();
//  cout << "Fit time :" << (afterall-beforeall) << " ticks = " <<  (float)(afterall-beforeall)/(float)CLOCKS_PER_SEC << " s" << endl;
  mfittimes.push_back((float)(afterall-beforeall)/(float)CLOCKS_PER_SEC);
  return OK;
}


double GPUPWAAmplitudeCalculator::TotalXSection(){
	double sum =0.0;

	vector<GPUPartialWave *> waves;
	waves = mAna->GetWaves()->GetWaves();
	int	nwaves = mAna->GetWaves()->GetNWaves();


	ROOT::Minuit2::MnUserParameters * Parameters = mAna->GetParameters();

	for(int i = 0; i < nwaves; i++){
		if(mAna->GetWaves()->Active(i)){
			double2 par_i = mdouble2(Parameters->Value(waves[i]->GetMagnitudeParameter()) * cos(Parameters->Value(waves[i]->GetPhaseParameter())),
					Parameters->Value(waves[i]->GetMagnitudeParameter()) * sin(Parameters->Value(waves[i]->GetPhaseParameter())));
			sum += mMCIntegralCoefficients[i][i].x*(par_i.x*par_i.x+par_i.y*par_i.y);
			for(int j = i+1; j < nwaves; j++){
				if(mAna->GetWaves()->Active(j)){
					double2 par_j = mdouble2(Parameters->Value(waves[j]->GetMagnitudeParameter()) * cos(Parameters->Value(waves[j]->GetPhaseParameter())),
							Parameters->Value(waves[j]->GetMagnitudeParameter()) * sin(Parameters->Value(waves[j]->GetPhaseParameter())));
					double2 pprod = par_i*par_j;
					sum += 2.0*( pprod.x*mMCIntegralCoefficients[i][j].x + pprod.y*mMCIntegralCoefficients[i][j].x
							+ par_i.x*par_j.y*mMCIntegralCoefficients[i][j].y - par_i.y*par_j.x*mMCIntegralCoefficients[i][j].y);
				}
			}
		}
	}
	//	cout << "Sum " << sum << endl;
	sum = sum/mAna->GetNumberMCGen();
		//cout << "TCS " << sum << endl;
	//	cout << "Par0 " << (float)mAna->GetParameters()->Value((unsigned int)0) << endl;;
	double accfrac = (double)mAna->GetSumOfWeights(mAna->GetMCIndex())/(double)mAna->GetNumberMCGen();
	return (sum + (float)mAna->GetParameters()->Value((unsigned int)0)*accfrac);
}


double GPUPWAAmplitudeCalculator::TotalXSectionDerivative(int parnum){
  if(parnum == 0)
    return 1.0;

  double sum =0.0;

  vector<GPUPartialWave *> waves;
  waves = mAna->GetWaves()->GetWaves();
  int	nwaves = mAna->GetWaves()->GetNWaves();

  ROOT::Minuit2::MnUserParameters * Parameters = mAna->GetParameters();

  int activeindex = 0;
  for(int i = 0; i < nwaves; i++){
    if( mAna->GetWaves()->Active(i)){
      if(mParmatrix[parnum][2*activeindex]){

	sum += 2.0f*mMCIntegralCoefficients[i][i].x*Parameters->Value(waves[i]->GetMagnitudeParameter());
      }
      int activeindex2 = activeindex+1;
      for(int j = i+1; j < nwaves; j++){
	if( mAna->GetWaves()->Active(j)){
	  float dphase = Parameters->Value(waves[i]->GetPhaseParameter()) - Parameters->Value(waves[j]->GetPhaseParameter());
	  //			cout << "dphase " << dphase << endl;
	  if(mParmatrix[parnum][2*activeindex]){
	    //				cout << waves[j]->GetMagnitudeParameter() << " " << mMCIntegralCoefficients[i][j].x << endl;
	    sum += 2.0f * Parameters->Value(waves[j]->GetMagnitudeParameter())* (cos(dphase)*mMCIntegralCoefficients[i][j].x - sin(dphase)* mMCIntegralCoefficients[i][j].y);
	  }
	  if(mParmatrix[parnum][2*activeindex2]){
	    sum += 2.0f* Parameters->Value(waves[i]->GetMagnitudeParameter()) * (cos(dphase)*mMCIntegralCoefficients[i][j].x - sin(dphase)* mMCIntegralCoefficients[i][j].y);
	  }
	  if(mParmatrix[parnum][2*activeindex+1]){
	    sum += 2.0f * Parameters->Value(waves[i]->GetMagnitudeParameter())*Parameters->Value(waves[j]->GetMagnitudeParameter())*
	      (-mMCIntegralCoefficients[i][j].x*sin(dphase) - mMCIntegralCoefficients[i][j].y*cos(dphase));
	  }
	  if(mParmatrix[parnum][2*activeindex2+1]){
	    sum -= 2.0f * Parameters->Value(waves[i]->GetMagnitudeParameter())*Parameters->Value(waves[j]->GetMagnitudeParameter())*
	      (-mMCIntegralCoefficients[i][j].x*sin(dphase) - mMCIntegralCoefficients[i][j].y*cos(dphase));
	  }

	  activeindex2++;
	}
      }
      activeindex++;
    }
  }
  sum = sum/mAna->GetNumberMCGen();

// cout << "dTCS " << parnum << ": "<< sum << endl;

  return sum;
}



void GPUPWAAmplitudeCalculator::clearMCIntegralCoefficients(){
  if(mMCIntegralCoefficients)
    for(int i =0; i < mNMCIntegralCoefficients; i++)
      delete [] mMCIntegralCoefficients[i];
  delete [] mMCIntegralCoefficients;
  mMCIntegralCoefficients = 0;
  mNMCIntegralCoefficients = 0;
}


void GPUPWAAmplitudeCalculator::initMCIntegralCoefficients(unsigned int nwaves){
  if(mMCIntegralCoefficients)
    clearMCIntegralCoefficients();
  mMCIntegralCoefficients = new double2*[nwaves];
  for(unsigned int i =0; i < nwaves; i++){
    mMCIntegralCoefficients[i] = new double2[nwaves];
  }
  mNMCIntegralCoefficients = nwaves;
}


void GPUPWAAmplitudeCalculator::MCIntegral(bool all){

  initMCIntegralCoefficients(mMCLookupTable->GetNWaves());

  unsigned int blocks = mMCLookupTable->GetNBlocks();

  unsigned int waves = mMCLookupTable->GetNWaves();

  unsigned int dim = waves*(waves+1)/2;

  GPUDataStream<float4> ** weights = mAna->GetWeights(mAna->GetMCIndex());

  for(unsigned int i =0; i < waves; i++){
    for(unsigned int j =0; j < waves; j++){
      mMCIntegralCoefficients[i][j].x = 0;
      mMCIntegralCoefficients[i][j].y = 0;
    }
  }

  for(unsigned int b=0; b < blocks; b++){
	  GPUDataStream<float4> * cx = mMCLookupTable->GetCoefficientsX(b);
	  GPUDataStream<float4> * cy = mMCLookupTable->GetCoefficientsY(b);
	  double * mysumx;
	  double * mysumy;
	  if(weights){
		  mysumx = cx->sum2dweighted(weights[b],dim);
		  mysumy = cy->sum2dweighted(weights[b],dim);
	  } else {
		  mysumx = cx->sum2d(dim);
		  mysumy = cy->sum2d(dim);
	  }
	  unsigned int index =0;
	  for(unsigned int i =0; i < waves; i++){
	     for(unsigned int j =i; j < waves; j++){
	        mMCIntegralCoefficients[i][j].x += mysumx[index];
	        mMCIntegralCoefficients[i][j].y += mysumy[index];
	        index++;
		  }
	  }

  }
//  assert(0);
}



STATUS GPUPWAAmplitudeCalculator::WriteMCIntegralFile(bool all, char * filename){
  if(mMCIntegralCoefficients == 0)
    MCIntegral(all);

  bool delfilename = false;
  if(filename == 0){
    filename = new char[256];
    delfilename = true;
    sprintf(filename,"%s_%s",mAna->GetNoSpaceName(),"Amplitude_MC_Integral");
  }

  ofstream f(filename,ios::out);
  if(f.bad()){
    cout << "Opening of file " << filename << " failed!" << endl;
    return FAILURE;
  }
  f << "MC Integral coefficients file generated for " << mAna->GetName() << " Analysis." << endl;
  f << "Line reserved for version checking." << endl;
  f << "Line reserved for parameter checking" << endl;

  f << setprecision(12);
  f << mNMCIntegralCoefficients << endl;
  int lines = 4;
  for(int i = 0; i < mNMCIntegralCoefficients; i++){
    for(int j = i; j < mNMCIntegralCoefficients; j++){
      f << mMCIntegralCoefficients[i][j].x << " " << mMCIntegralCoefficients[i][j].y << endl;
      lines++;
    }
  }
  f << "End of file, should contain " << endl << lines +2 << " lines, including this one." << endl;

  if(f.bad()){
    cout << "Writing to file " << filename << " went wrong!" << endl;
    f.close();
    return FAILURE;
  }
  f.close();
  if(delfilename)
    delete [] filename;
  return OK;
}


STATUS GPUPWAAmplitudeCalculator::ReadMCIntegralFile(char * filename){
  bool delfilename = false;
  if(filename == 0){
    filename = new char[256];
    delfilename = true;
    sprintf(filename,"%s_%s",mAna->GetNoSpaceName(),"Amplitude_MC_Integral");
  }
  ifstream f(filename,ios::in);
  if(f.bad()){
    cout << "Opening of file " << filename << " failed!" << endl;
    return FAILURE;
  }
  char line[512];
  // These lines could/should be parsed to see wether we read a correct file
  f.getline(line,512);
  f.getline(line,512);
  f.getline(line,512);
  if(f.bad()){
    cout << "Reading of file " << filename << " failed!" << endl;
    f.close();
    return FAILURE;
  }
  int wavenumber = -1;
  f >> wavenumber;
  cout << "Number of waves to be read from file : " << wavenumber << endl;
  if(f.bad() || wavenumber < 0){
    cout << "Reading of number of waves from file " << filename << " failed!" << endl;
    return FAILURE;
  }
  initMCIntegralCoefficients(wavenumber);
  int lines = 4;
  //cout << mNMCIntegralCoefficients << endl;
  for(int i = 0; i < mNMCIntegralCoefficients; i++){
    for(int j = i; j < mNMCIntegralCoefficients; j++){
      f >> mMCIntegralCoefficients[i][j].x >> mMCIntegralCoefficients[i][j].y;
      //lixl cout << "(" << mMCIntegralCoefficients[i][j].x << " : " << mMCIntegralCoefficients[i][j].y << ")" << endl;
      lines++;
    }
  }
  if(f.bad()){
    cout << "Reading coefficients from file " << filename << " failed!" << endl;
    f.close();
    return FAILURE;
  }
  // Needed in order to finish line above...
  f.getline(line,512);
  f.getline(line,512);
  int linefile = -1;
  f >> linefile;
  if(f.bad() || linefile != lines+2){
    cout << "Reading from file " << filename << " went wrong!" << endl;
    //cout << linefile << " != " << lines+2 << endl;
    f.close();
    return FAILURE;
  }
  f.close();
  if(delfilename)
    delete [] filename;
  return OK;
}


float ** GPUPWAAmplitudeCalculator::GetDcs(unsigned int index, bool dooffdiagonal, int nblocks){



	// Check wheter we have already calculated the coefficients for the fit
	if(index == mAna->GetDataIndex()){
		if(!mLookupTable->CacheValid())
			mLookupTable->FillTable();
	} else if(index == mAna->GetMCIndex()){
		if(!mMCLookupTable->CacheValid())
			mMCLookupTable->FillTable();
	} else {
		cout << "Invalid index " << index << endl;
		assert(0);
	}

  vector<GPUPartialWave *> waves;

  waves =  mAna->GetWaves()->GetActiveWaves();
  int nwaves = (int)waves.size();
  vector<GPUPartialWave *>::iterator it_i;
  it_i = waves.begin();

  int ncoeffblocks = (int)((double)(nblocks*GPUStreamTensor<float4>::Blocksize)/(mAna->Blocksize*4.0));
  if((nblocks*GPUStreamTensor<float4>::Blocksize)%(mAna->Blocksize*4))
	  ncoeffblocks++;

  int length = 0;
  if(index == mAna->GetDataIndex())
    length = mAna->GetNumberData();
  if(index == mAna->GetMCIndex())
    length = mAna->GetNumberMCAcc();
  if(nblocks > 0 && nblocks < mNCoefficientBlocks)
	  length = ncoeffblocks*mAna->Blocksize*4;
  assert(length);
  int nresult = nwaves+2;
  if(dooffdiagonal)
    nresult = nwaves+2 + nwaves*(nwaves-1)/2;
  float ** result = new float *[nresult];
  for(int i =0; i < nresult; i++)
    result[i] = (float*)(new float[length]);

  int NCoefficientBlocks;
  //assert(ncoeffblocks <=  mNCoefficientBlocks);
  if(nblocks ==-1 && index == mAna->GetDataIndex())
	  NCoefficientBlocks = mNCoefficientBlocks;
  else if (nblocks ==-1 && index == mAna->GetMCIndex())
	  NCoefficientBlocks = mNMCCoefficientBlocks;
  else
	  NCoefficientBlocks = ncoeffblocks;

  int NAdditionalEvents = mNAdditionalEvents;
  if(index == mAna->GetMCIndex())
	  NAdditionalEvents = mNMCAdditionalEvents;

  GPUDataStream<float2> * mypars = mAna->pars2streamCartesian();
  GPUDataStream<float2> * myparsPolar = mAna->pars2streamPolar();

  if(index == mAna->GetDataIndex()){
	  for(int i=0; i < NCoefficientBlocks; i++){
		  int size = mAna->Blocksize;
		  if( i == mNCoefficientBlocks-1 && NAdditionalEvents != 0)
			  size = NAdditionalEvents;
		  //sum += size*4;
	  //cout << "In Get DCS: " << i << " : " << size << " total: " << sum << endl;
	  	  GPUDataStream<float4> * dcs = new GPUDataStream<float4>(mdev, size);
	  //cout << (float)mAna->GetParameters()->Value((unsigned int)0) << endl;
	  	  pwamultdcsonly4(cl::NDRange(size), mdev,  mLookupTable->GetCoefficientsX(i),  mLookupTable->GetCoefficientsY(i), mypars, nwaves, (float)mAna->GetParameters()->Value((unsigned int)0), dcs);
	  	  dcs->Read((float4*)&result[0][i* mAna->Blocksize*4]);
	  	  delete dcs;



	  	  for(int j =0; j < nwaves; j++){
		  //for(int i=0; i < NCoefficientBlocks; i++){
	  		  int size = mAna->Blocksize;
	  		  if( i == mNCoefficientBlocks-1 && NAdditionalEvents != 0)
	  			  size = NAdditionalEvents;
	  		  GPUDataStream<float4> * dcs = new GPUDataStream<float4>(mdev, size);
	  		  pwamultdcsonlyonewave4(cl::NDRange(size), mdev, mLookupTable->GetCoefficientsX(i), mypars, nwaves, j, dcs);
	  		  dcs->Read((float4*)&result[j+2][i* mAna->Blocksize*4]);
	  		  delete dcs;

	  	  }

	  	  if(dooffdiagonal){
	  		  int ind = nwaves +2;
	  		  for(int j =0; j < nwaves; j++){
	  			  for(int k = j+1; k < nwaves; k++){

	  				  int size = mAna->Blocksize;
	  				  if( i == mNCoefficientBlocks-1 && NAdditionalEvents != 0)
	  					  size = NAdditionalEvents;
	  				  GPUDataStream<float4> * dcs = new GPUDataStream<float4>(mdev, size);
	  				  pwamultdcsonlytwowaves4(cl::NDRange(size), mdev, mLookupTable->GetCoefficientsX(i),  mLookupTable->GetCoefficientsY(i),  mypars, nwaves, j, k, dcs);
	  				  dcs->Read((float4*)&result[ind][i* mAna->Blocksize*4]);
	  				  delete dcs;

	  				  ind++;
	  			  }
	  		  }
	  	  }
	  }
  } else {
	  for(int i=0; i < NCoefficientBlocks; i++){
		  int size = mAna->Blocksize;
		  if( i == mNMCCoefficientBlocks-1 && NAdditionalEvents != 0)
			  size = NAdditionalEvents;
		  //sum += size*4;
	  //cout << "In Get DCS: " << i << " : " << size << " total: " << sum << endl;
	  	  GPUDataStream<float4> * dcs = new GPUDataStream<float4>(mdev, size);
	  //cout << (float)mAna->GetParameters()->Value((unsigned int)0) << endl;
	  	  pwamultdcsonly4(cl::NDRange(size), mdev,  mMCLookupTable->GetCoefficientsX(i),  mMCLookupTable->GetCoefficientsY(i), mypars, nwaves, (float)mAna->GetParameters()->Value((unsigned int)0), dcs);
	  	  dcs->Read((float4*)&result[0][i* mAna->Blocksize*4]);
	  	  delete dcs;

	  	  for(int j =0; j < nwaves; j++){
		  //for(int i=0; i < NCoefficientBlocks; i++){
	  		  int size = mAna->Blocksize;
	  		  if( i == mNMCCoefficientBlocks-1 && NAdditionalEvents != 0)
	  			  size = NAdditionalEvents;
	  		  GPUDataStream<float4> * dcs = new GPUDataStream<float4>(mdev, size);
	  		  pwamultdcsonlyonewave4(cl::NDRange(size), mdev, mMCLookupTable->GetCoefficientsX(i), mypars, nwaves, j, dcs);
	  		  dcs->Read((float4*)&result[j+2][i* mAna->Blocksize*4]);
	  		  delete dcs;
	  	  }

	  	  if(dooffdiagonal){
	  		  int ind = nwaves +2;
	  		  for(int j =0; j < nwaves; j++){
	  			  for(int k = j+1; k < nwaves; k++){

	  				  int size = mAna->Blocksize;
	  				  if( i == mNMCCoefficientBlocks-1 && NAdditionalEvents != 0)
	  					  size = NAdditionalEvents;
	  				  GPUDataStream<float4> * dcs = new GPUDataStream<float4>(mdev, size);
	  				  pwamultdcsonlytwowaves4(cl::NDRange(size), mdev, mMCLookupTable->GetCoefficientsX(i),  mMCLookupTable->GetCoefficientsY(i),  mypars, nwaves, j, k, dcs);
	  				  dcs->Read((float4*)&result[ind][i* mAna->Blocksize*4]);
	  				  delete dcs;

	  				  ind++;
	  			  }
	  		  }
	  	  }
	  }

  }


  for(int j =0; j < length; j++)
    result[1][j] = (float)mAna->GetParameters()->Value((unsigned int)0);

  delete mypars;
  delete myparsPolar;
  //DeleteLookup4();
  return result;
}



void Test(){

  int nwaves = 4;
  int mNCoefficientBlocks = 7;
  int mNAdditionalEvents = 848;
  //GPUDataStream<float2>** mCoefficients = new GPUDataStream<float2>*[mNCoefficientBlocks];
  float2 ** coefficients = new float2*[mNCoefficientBlocks];

  for(int i =0; i < mNCoefficientBlocks; i++){
    coefficients[i] = new float2[(nwaves*(nwaves+1))/2*GPUDataStream<float2>::DIMSIZE];
    for(int j =0; j < (nwaves*(nwaves+1))/2*GPUDataStream<float2>::DIMSIZE; j++){
      coefficients[i][j].x = i;
      coefficients[i][j].y = j;
    }
  }

  //cout << "Coefficient: " << coefficients[1][8192*9+4098].x << " " << coefficients[1][8192*9+4098].y << endl;

  for(int i = 0; i < mNCoefficientBlocks; i++){
    cout << "i: " << i << endl;
    if(i < mNCoefficientBlocks -1 || mNAdditionalEvents ==0){
  //    mCoefficients[i] = new GPUDataStream<float2>( (nwaves*(nwaves+1))/2, mAna->Blocksize);
    } else {
   //   mCoefficients[i] = new GPUDataStream<float2>( (nwaves*(nwaves+1))/2, mNAdditionalEvents);
    }
    cout << "Before read" << endl;
  //  streamRead(*mCoefficients[i], coefficients[i]);
    cout << "After read" << endl;
  }

}


double** GPUPWAAmplitudeCalculator::PartialTotalXSection(){


  double sum =0.0;
  double tmp =0.0;
  double ngen=(double)mAna->GetNumberMCGen();
  int	nactivewaves = mAna->GetWaves()->GetNActiveWaves();
  double ** ptx = new double*[nactivewaves];
  double * matrixstore = new double[(int)(nactivewaves*(nactivewaves+1))];
  for(int i =0; i < nactivewaves; i++){
    ptx[i] = &matrixstore[(nactivewaves+1)*i];
    for(int j =0; j < nactivewaves+1; j++){
      ptx[i][j] =0.0;
    }
  }

  vector<GPUPartialWave *> waves;
  waves = mAna->GetWaves()->GetWaves();
  int	nwaves = mAna->GetWaves()->GetNWaves();

  ROOT::Minuit2::MnUserParameters * Parameters = mAna->GetParameters();
  if(!mMCIntegralCoefficients){
     // If not, read the corresponding file
    ReadMCIntegralFile();
  }
  
  int activeindex = 0;
  int activeindex2 = 0; 
  for(int i = 0; i < nwaves; i++){
    if(mAna->GetWaves()->Active(i)){
      double2 par_i=mdouble2(Parameters->Value(waves[i]->GetMagnitudeParameter()) * cos(Parameters->Value(waves[i]->GetPhaseParameter())),
		    Parameters->Value(waves[i]->GetMagnitudeParameter()) * sin(Parameters->Value(waves[i]->GetPhaseParameter())));
      tmp= mMCIntegralCoefficients[i][i].x*(par_i.x*par_i.x+par_i.y*par_i.y)/ngen;
      sum+=tmp;
      activeindex2 = activeindex;
      ptx[activeindex][activeindex2]=tmp;
      
      
      activeindex2 ++;
      for(int j = i+1; j < nwaves; j++){
	if(mAna->GetWaves()->Active(j)){
	  double2 par_j=mdouble2(Parameters->Value(waves[j]->GetMagnitudeParameter()) * cos(Parameters->Value(waves[j]->GetPhaseParameter())),
			Parameters->Value(waves[j]->GetMagnitudeParameter()) * sin(Parameters->Value(waves[j]->GetPhaseParameter())));
	  double2 pprod = par_i*par_j;
	  tmp = 2.0*( pprod.x*mMCIntegralCoefficients[i][j].x + pprod.y*mMCIntegralCoefficients[i][j].x
	  	       + par_i.x*par_j.y*mMCIntegralCoefficients[i][j].y - par_i.y*par_j.x*mMCIntegralCoefficients[i][j].y)/ngen;
	  sum += tmp;
	  ptx[activeindex][activeindex2]=tmp;
    activeindex2++;
	}
      }
     activeindex++;
    }
  }
  ptx[0][nactivewaves]=sum;
  
  double accfrac = (double)mAna->GetSumOfWeights(mAna->GetMCIndex())/(double)mAna->GetNumberMCGen();
  double total= sum + (float)mAna->GetParameters()->Value((unsigned int)0)*accfrac;
  ptx[1][nactivewaves]=total;
  return ptx;
}

double** GPUPWAAmplitudeCalculator::PartialTotalXSectionDerivative(int parnum){



  double sum =0.0;
  double tmp =0.0;
  double ngen=(double)mAna->GetNumberMCGen();

  vector<GPUPartialWave *> waves;
  waves = mAna->GetWaves()->GetWaves();
  int	nwaves = mAna->GetWaves()->GetNWaves();
  int	nactivewaves = mAna->GetWaves()->GetNActiveWaves();

  double ** ptxd = new double*[nactivewaves];
  double * matrixstore = new double[(int)(nactivewaves*(nactivewaves+1))];
  for(int i =0; i < nactivewaves; i++){
    ptxd[i] = &matrixstore[(nactivewaves+1)*i];
    for(int j =0; j < nactivewaves+1; j++){
      ptxd[i][j] =0.0;
    }
  }





  if(parnum == 0){

    ptxd[0][nactivewaves]=1.0;
                   return ptxd;
  }
  ROOT::Minuit2::MnUserParameters * Parameters = mAna->GetParameters();
  if(!mMCIntegralCoefficients){
     //If not, read the corresponding file
    ReadMCIntegralFile();
  }
 
  int activeindex = 0;
  int activeindex2 = 0;
  for(int i = 0; i < nwaves; i++){
    if( mAna->GetWaves()->Active(i)){
      activeindex2 = activeindex;
      if(mParmatrix[parnum][2*activeindex]){
         tmp=2.0f*mMCIntegralCoefficients[i][i].x*Parameters->Value(waves[i]->GetMagnitudeParameter())/ngen;
	       sum +=tmp;
	       
	       ptxd[activeindex][activeindex2]=tmp;
               
      }
      activeindex2 ++;
      
      for(int j = i+1; j < nwaves; j++){
	if( mAna->GetWaves()->Active(j)){
	
	  float dphase = Parameters->Value(waves[i]->GetPhaseParameter()) - Parameters->Value(waves[j]->GetPhaseParameter());
	  
	  if(mParmatrix[parnum][2*activeindex]){
	  
	    tmp = 2.0f * Parameters->Value(waves[j]->GetMagnitudeParameter())* (cos(dphase)*mMCIntegralCoefficients[i][j].x - sin(dphase)* mMCIntegralCoefficients[i][j].y)/ngen;
	    sum +=tmp;
	  
	       ptxd[activeindex][activeindex2]=tmp;
	  }
	  if(mParmatrix[parnum][2*activeindex2]){
	    tmp = 2.0f* Parameters->Value(waves[i]->GetMagnitudeParameter()) * (cos(dphase)*mMCIntegralCoefficients[i][j].x - sin(dphase)* mMCIntegralCoefficients[i][j].y)/ngen;
	    sum +=tmp;
	  
	       ptxd[activeindex][activeindex2]=tmp;
	  }
	  if(mParmatrix[parnum][2*activeindex+1]){
	    tmp= 2.0f * Parameters->Value(waves[i]->GetMagnitudeParameter())*Parameters->Value(waves[j]->GetMagnitudeParameter())*
	      (-mMCIntegralCoefficients[i][j].x*sin(dphase) - mMCIntegralCoefficients[i][j].y*cos(dphase))/ngen;
	    sum +=tmp;
	  
	       ptxd[activeindex][activeindex2]=tmp;
	  }
	  if(mParmatrix[parnum][2*activeindex2+1]){
	    tmp = - 2.0f * Parameters->Value(waves[i]->GetMagnitudeParameter())*Parameters->Value(waves[j]->GetMagnitudeParameter())*
	      (-mMCIntegralCoefficients[i][j].x*sin(dphase) - mMCIntegralCoefficients[i][j].y*cos(dphase))/ngen;
	    sum +=tmp;
	  
	       ptxd[activeindex][activeindex2]=tmp;
	  }
	  
	  activeindex2++;
	  
	}
      }
      activeindex++;
    }
  }
    ptxd[0][nactivewaves]=sum;
  return ptxd;
}

