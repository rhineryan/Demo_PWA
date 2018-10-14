#include "GPUPartialWaveAnalysis.h"
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "Status.h"


#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <Minuit2/MnMigrad.h>
#include <Minuit2/MnHesse.h>
#include <Minuit2/MnFumiliMinimize.h>
#include <Minuit2/FunctionMinimum.h>
#include <Minuit2/MnMinos.h>
#include <Minuit2/MnPrint.h>
#include "MnFunctionCross2.h"
#include <Minuit2/MnCross.h>
#include <TFumili.h>
#include "GPUFumiliMinimize.h"
#include "GPUMinuitFCN.h"
#include "GPUFumiliFCN.h"
#include "GPUPWAAmplitudeCalculator.h"
#include "GPUPWAFreeCalculator.h"
#include "GPUPartialWaveLookupTable.h"
#include <TGraph.h>

#include "GPUMinimizationHistory.h"
#include "GPUMinosMinimizationHistory.h"
#include "GPUFitConstraintList.h"


#include "PrepareKernels.h"
#include "FileCfg.h"

using std::ofstream;
using std::ifstream;
using std::ios;
using std::setprecision;
using std::setw;

GPUPartialWaveAnalysis::GPUPartialWaveAnalysis(char * _name, char * _filename, int _ndatasets):
#ifdef USECPU
	GPUDataDependentObjectList(new DeviceInterface(CL_DEVICE_TYPE_CPU), _ndatasets),
#else
	GPUDataDependentObjectList(new DeviceInterface(CL_DEVICE_TYPE_GPU), _ndatasets),
#endif
	mFilename(_filename),
	mWeights(_ndatasets,(GPUDataStream<float4> **)(0)),mWeightsSingle(_ndatasets,(GPUDataStream<float> **)(0)),
	mCPUWeights(_ndatasets,(float*)(0)), msumofweights(_ndatasets,0.0),mparscartesian(0), mparspolar(0),
	mLastFitHistory(0), mBestFitHistory(0),mWaves(new GPUSetOfPartialWaves(this)),mLookupData(0),mLookupMC(0)
{
	cout << "Initializing Kernels" << endl;
	// Initialize the Kernels for the GPU here
#ifdef USECPU
	cout<< "cpu"<<endl;
	PrepareKernels_CPU(mdeviceinterface);
#else
	PrepareKernels_GPU(mdeviceinterface);
#endif
	//cout << "Reading env vars..." << endl;
	char * devnr = getenv("GPUPWA_GPU_NR");
	//cout << "Device number " << devnr << "xxx" <<endl;
	if(devnr){
		int nr = atoi(devnr);
		cout << "Device number " << nr << " of " <<mdeviceinterface->GetNDevices() << endl;
		if ((unsigned int)nr < mdeviceinterface->GetNDevices()){
			mdeviceinterface->SetStandardDevice(nr);
		} else {
			cout << "Invalid device number specified (" << nr <<") with "
				<< mdeviceinterface->GetNDevices() << " available - aborting" << endl;
			exit(-1);
		}

	}

	// Initialize Root here
	gSystem->Load("libTree");
	gSystem->Load("libMinuit2");
	gROOT->SetBatch();

#include "Style.h"
	// Copy name
	mName = new char[strlen(_name)+1];
	strcpy(mName, _name);

	// Strip name of spaces (for filenames etc).
	mNoSpaceName = new char[strlen(_name)+1];
	//strcpy(mNoSpaceName, _name);
	//char * space;
	//while((space = strchr(mNoSpaceName,' '))){
	//	strcpy(space, space+1);
	//}
	int pos = 0;
	for (int i = 0; i < strlen(_name); ++i) {
		if (_name[i] != ' ')
			mNoSpaceName[pos++] = _name[i];
	}
	mNoSpaceName[pos] = '\0';


	// Get hold of all the necessary files...
	ConfigFile f(mFilename);
	FileCfg pfile;
	if(f.readInto(pfile, "ParameterFile")){
		cout << "Reading parameters from " << pfile.path << endl;
		mParaFile = new ConfigFile(pfile.path);
	} else {
		cout << "ParameterFile entry in " << mFilename << " not found, aborting" << endl;
		exit(-1);
	}

	FileCfg rfile;
	if(f.readInto(rfile, "ResonanceFile")){
		cout << "Reading resonance parameters from " << rfile.path << endl;
		mResFile  = new ConfigFile(rfile.path);
	} else {
		cout << "ResonanceFile entry in " << mFilename << " not found, aborting" << endl;
		exit(-1);
	}

	FileCfg dfile;
	if(f.readInto(dfile, "DataFile")){
		cout << "Using data in " << dfile.path << endl;
		mInputFiles.push_back(dfile.path);
	} else {
		cout << "DataFile entry in " << mFilename << " not found, aborting" << endl;
		exit(-1);
	}
	//FileCfg sfile;
	//if(f.readInto(sfile, "SteeringFile")){
	//        cout << "Steering from " << sfile.path << endl;
	//        mSteeringFile = new ConfigFile(sfile.path);
	//} else {
	//       cout << "Steering entry in " << mFilename << " not found, aborting" << endl;
	//        exit(-1);
	//}

	for(int i = 1; i < _ndatasets; i++){
		FileCfg mfile;
		char name[32];
		sprintf(name, "MCFile%i",i);
		if(f.readInto(mfile, name)){
			cout << "Using MC in " << mfile.path << endl;
			mInputFiles.push_back(mfile.path);
		} else {
			cout << name <<" entry in " << mFilename << " not found, aborting" << endl;
			exit(-1);
		}
	}

	// Create Parameter collection
	mParameters = new ROOT::Minuit2::MnUserParameters();

	// Create phase space parameter - always at index 0!
	char name[20];
	sprintf(name,"phasespace");
	char fname[64];
	sprintf(fname,"bg_mag");
	ParaCfg pcf;
	mParaFile->readInto(pcf, fname);
	int index = AddParameter(name, pcf.v, pcf.e);
	if(pcf.e < 0)
		FixParameter(index);
	else {
		if(pcf.l != 999)
			LimitParameterLow(index, pcf.l);
		if(pcf.u != 999)
			LimitParameterHigh(index, pcf.u);
	}


	// Create phase space parameter - always at index 0!
	//mParameters->Add("phasespace", 0.0,0.0);
	//mParameters->Fix((unsigned int)0);

	// Set default values for indices
	mDataIndex =0;
	mMCIndex =1;

	mLikelihood = 0.0;

	mRuncounter = GPURuncounter::GetInstance(mNoSpaceName);

	mConstraintList = new GPUFitConstraintList();

	//cout << mLookupData << " /// " << mLookupMC << endl;
}

GPUPartialWaveAnalysis::~GPUPartialWaveAnalysis(void)
{
	delete[] mName;
	delete[] mNoSpaceName;
	delete mConstraintList;
	delete mWaves;
}




// Handling Fit Parameters
void GPUPartialWaveAnalysis::SetParameterVector(vector<double> _vec) const{
	for(unsigned int i =0; i < _vec.size(); i++){
		mParameters->SetValue(i,_vec[i]);
	}

}


void GPUPartialWaveAnalysis::PrintParameters() const{
	vector<double> parvec = mParameters->Params();
	for(int i=0; i < (int)parvec.size(); i++){
		cout << i << ":   " << mParameters->Name(i) << ": " << parvec[i] << " +- " << mParameters->Error(i) << endl;
	}
}


void GPUPartialWaveAnalysis::SetEventWeights(float * weights, unsigned int index){
	int nevents = GetNevents(index);
	//cout << "Setting weights for " << nevents << " events" << endl;
	mCPUWeights[index] = weights;
	double wsum =0.0;
	for(int i=0; i < nevents;i++)
		wsum += weights[i];
	msumofweights[index] = wsum;

	//if(index==GetDataIndex()){
	//  if(nevents%4)
	//    cout << "WARNING: Event number for weights not divisible by 4!" << endl;

	//cout << "Dimsize is " << Blocksize << endl;

	int blocks = nevents/(Blocksize*4);
	int restb   = nevents%(Blocksize*4);
	int rest =0;
	if(restb)
		rest = (restb+3)/4;

	if(rest)  {    blocks++;}

	//cout << "Blocks " << blocks << " rest " << rest << endl;

	mWeights[index] = new GPUDataStream<float4>*[blocks];
	for(int i =0; i < blocks-1; i++){
		mWeights[index][i] = new GPUDataStream<float4>(mdeviceinterface, Blocksize);
		mWeights[index][i]->Write((float4 *)(&weights[i*Blocksize*4]));
	}
	if(rest==0)
		rest = GPUDataStream<float4>::DIMSIZE;
	mWeights[index][blocks -1] = new GPUDataStream<float4>(mdeviceinterface, rest);
	float * restweights = new float[rest*4];
	for(int i=0; i < restb; i++)
		restweights[i] = weights[(blocks-1)*Blocksize*4 +i];
	for(int i=restb; i < rest*4; i++)
		restweights[i] = 0.0f;

	mWeights[index][blocks-1]->Write((float4 *)(restweights));
	//}

	if(index!=GetDataIndex()){
		int blocks = nevents/(GPUDataDependentObject::Blocksize);
		int restb   = nevents%(GPUDataDependentObject::Blocksize);
		int rest =0;
		if(restb)
			rest = (restb+3)/4;
		if(rest)  {    blocks++;}
		mWeightsSingle[index] = new GPUDataStream<float>*[blocks];
		for(int i =0; i < blocks-1; i++){
			mWeightsSingle[index][i] = new GPUDataStream<float>(mdeviceinterface, GPUDataDependentObject::Blocksize);
			mWeightsSingle[index][i]->Write(&weights[i*GPUDataDependentObject::Blocksize]);
		}
		if(rest==0)
			rest = GPUDataDependentObject::Blocksize;
		mWeightsSingle[index][blocks -1] = new GPUDataStream<float>(mdeviceinterface, rest);
		float * restweights = new float[rest*4];
		for(int i=0; i < restb; i++)
			restweights[i] = weights[(blocks-1)*Blocksize*4 +i];
		for(int i=restb; i < rest*4; i++)
			restweights[i] = 0.0f;
		mWeightsSingle[index][blocks-1]->Write((restweights) );
	}


}


// Set event weights to a constant

void GPUPartialWaveAnalysis::SetEventWeights(float weight, unsigned int index){
	int nevents = GetNevents(index);
	//cout << "Weights at index " << index << ": " << weight << endl;
	int origevents = nevents;
	while(nevents%4)
		nevents++;
	float * weights = new float[nevents];
	for(int i =0; i < nevents; i++){
		weights[i] = weight;
		if (i >= origevents){
			weights[i] = 0.0f;
		}
		//cout <<"origevents="<<origevents << " i="<<i <<" weights[i]="<<weights[i]<<endl;
	}
	SetEventWeights(weights, index);
	// delete [] weights;
}
// Set event weights from a vector of event numbers and a vector of weights

void GPUPartialWaveAnalysis::SetEventWeights(vector<int> nums, vector<float> weights, unsigned int _index){
	assert(nums.size() <= weights.size());
	int nevents =0;
	for(vector<int>::iterator it = nums.begin(); it < nums.end(); ++it)
		nevents += (*it);
	int origevents = nevents;
	//cout << "origevents="<<origevents<<" GetNumberData="<<GetNumberData()<<endl;
	assert(nevents = GetNevents(_index));
	while(nevents%4)
		nevents++;
	float * fweights = new float[nevents];
	int index =0;
	int evs = 0;
	for(vector<int>::iterator it = nums.begin(); it < nums.end(); ++it){
		int up = (*it)+evs;
		//cout <<"evs="<<evs <<" up="<<up<<endl;
		for(int i = evs; i < up; i++){
			fweights[i] = weights[index];
			evs++;
		}
		//cout<< "fweights[up-1]="<<fweights[up-1]<<endl;
		index++;
	}
	for(int i = origevents; i <  nevents; i++){
		fweights[i] = 0.0f;
	}
	SetEventWeights(fweights,_index);
	//	delete [] fweights;

}

// Add a constraint to this partial wave analysis
void GPUPartialWaveAnalysis::AddConstraint(GPUFitConstraint * constraint){
	mConstraintList->AddConstraint(constraint);
}

// Remove a constraint from this partial wave analysis
void GPUPartialWaveAnalysis::RemoveConstraint(unsigned int index){
	mConstraintList->RemoveConstraint(index);
}

// Get a pointer to a constraint
GPUFitConstraint * GPUPartialWaveAnalysis::GetConstraint(unsigned int index) const {
	return mConstraintList->GetConstraint(index);
}

// Get the log likelihood contribution of the constraints
double GPUPartialWaveAnalysis::GetConstraintLHContribution() const{
	return (*mConstraintList)();
}

// Get the log likelihood gradient contribution of the constraints with regard to the parameter at index
double GPUPartialWaveAnalysis::GetConstraintGradientContribution(unsigned int index) const{
	return mConstraintList->gradient(index);
}

// Get the log likelihood gradient contribution of the constraints with regard to the parameter at index
double GPUPartialWaveAnalysis::GetConstraintHessianContribution(unsigned int i, unsigned int j) const{
	return mConstraintList->hessian(i,j);
}

// Describe constraints
void GPUPartialWaveAnalysis::DescribeConstraints(std::ostream & outstream) const{
	mConstraintList->describe(outstream);
}

// Report constraints contribution to likelihood
void GPUPartialWaveAnalysis::ReportConstraints(std::ostream & outstream) const {
	mConstraintList->report(outstream);
}




STATUS GPUPartialWaveAnalysis::MinuitMinimize(GPUPWACalculator * mycalc,
		GPUMinimizationHistory *& minhist){
	// Copy initial parameters
	ROOT::Minuit2::MnUserParameters initialpars(*mParameters);
	// Create objects for the Fit
  //ROOT::Minuit2::MnStrategy strat(1); // add by xiongxa (zhangjq) defualt by miniut
  ROOT::Minuit2::MnStrategy strat(0); // add by xiongxa (zhangjq) allowed when the error is not so precise
	ROOT::Minuit2::FCNBase * fcn = new GPUMinuitFCN(mycalc);
	//ROOT::Minuit2::MnMigrad * migrad = new ROOT::Minuit2::MnMigrad(*fcn, *mParameters);
  ROOT::Minuit2::MnMigrad * migrad = new ROOT::Minuit2::MnMigrad(*fcn, *mParameters, strat); // add by xiongxa (zhangjq)
	ROOT::Minuit2::VariableMetricMinimizer minimizer;

	//ROOT::Minuit2::MnMachinePrecision prec;
	//cout << "Accuray : " << prec.Eps() << endl;
	migrad->SetPrecision(1e-11);

	// Do Fit
	//ROOT::Minuit2::FunctionMinimum minimum = minimizer.Minimize(*fcn,migrad->State(),migrad->Strategy(),2000,20);
	ROOT::Minuit2::FunctionMinimum minimum = minimizer.Minimize(*fcn,migrad->State(),migrad->Strategy(),100000,200); //add by xiongxa
  //ROOT::Minuit2::FunctionMinimum minimum = minimizer.Minimize(*fcn,migrad->State(),migrad->Strategy(),5000,5); // add by xiongxa (zhangjq)
  //ROOT::Minuit2::MnHesse hesse(migrad->Strategy() ); //add by xiongxa
  //hesse(*fcn, minimum, 0); //add by xiongxa

  cout<<__LINE__<<" I am in;"<<endl;
  cout<<"IsValid ="<<minimum.IsValid()<<endl;
  cout<<"likelihood ="<<minimum.Fval()<<endl;
	if(!minimum.IsValid()){
		cout << "Fit failed!" << endl;
#ifdef WINDOWS
		if(_isnan(minimum.Fval()))
			cout << "Likelihood NaN!" << endl;
#endif
#ifndef WINDOWS
		if(isnan(minimum.Fval()))
			cout << "Likelihood NaN!" << endl;
#endif
		delete fcn;
		delete migrad;
		return FAILURE;
	}

//***************************output the Error matrix**********************************

        int covq=0;
        char minbasic[100];
        char mincov[100];
        char minglocc[100];
        sprintf(minbasic,"./minimum_basic.txt");
        sprintf(mincov,"./minimum_covariance.txt");
        sprintf(minglocc,"./minimum_globalcc.txt");
        ofstream fminbasic(minbasic);
        ofstream fmincov(mincov);
        ofstream fminglocc(minglocc);
        
        fminbasic<<minimum<<endl;
        fmincov<< minimum.UserCovariance() << std::endl;
        fminglocc<< minimum.UserState().GlobalCC() << std::endl;
        ROOT::Minuit2::MinimumError minerror = minimum.Error();
        if(minerror.IsValid()) cout<<"has valid covariance"<<endl;
        if(minerror.IsAccurate()&&minerror.IsPosDef())
         {
           covq =3;
           cout<<"covquality =3 full accurate covariance matrix"<<endl;
         }
        if(minerror.IsPosDef()&&(!minerror.IsAccurate()))
         {
           covq =1;
           cout<<"covquality =1 approximation only, not accurate"<<endl;
         }
        if(minerror.IsMadePosDef())
         {
           covq=2;
           cout<<"2= full matrix, but forced positive-definite"<<endl;
         }

	ROOT::Minuit2::MnUserParameters  resultpars = minimum.UserParameters();
	if(minhist)
		delete minhist;
	minhist = new GPUMinimizationHistory(this,
			initialpars, resultpars,
			minimum.Fval(), minimum.Edm(),
			minimum.IsValid(), minimum.NFcn());
	delete fcn;
	delete migrad;
	return OK;
}


STATUS GPUPartialWaveAnalysis::FumiliMinimize(GPUPWACalculator * mycalc,
		GPUMinimizationHistory *& minhist){
	// Copy initial parameters
	ROOT::Minuit2::MnUserParameters initialpars(*mParameters);
	// Create objects for the Fit
	GPUFumiliFCN * fcn = new GPUFumiliFCN(mycalc);
	ROOT::Minuit2::MnFumiliMinimize * fumili = new ROOT::Minuit2::MnFumiliMinimize(*fcn, *mParameters);

	// Fix parameters etc.
	fumili->SetPrecision(1e-11);

	// Do Fit
	ROOT::Minuit2::FunctionMinimum minimum = ((*fumili)(2000,200.0));

	if(!minimum.IsValid()){
		cout << "Fit failed!" << endl;
#ifdef WINDOWS
		if(_isnan(minimum.Fval()))
			cout << "Likelihood NaN!" << endl;
#endif
#ifndef WINDOWS
		if(isnan(minimum.Fval()))
			cout << "Likelihood NaN!" << endl;
#endif
		delete fcn;
		delete fumili;
		return FAILURE;
	}

	ROOT::Minuit2::MnUserParameters  resultpars = minimum.UserParameters();
	if(minhist)
		delete minhist;
	minhist = new GPUMinimizationHistory(
			this,
			initialpars, resultpars,
			minimum.Fval(), minimum.Edm(),
			minimum.IsValid(), minimum.NFcn());

	delete fcn;
	delete fumili;
	return OK;
}


STATUS GPUPartialWaveAnalysis::OldfumiliMinimize(GPUPWACalculator * mycalc,
		GPUMinimizationHistory *& minhist){
	// Copy initial parameters
	ROOT::Minuit2::MnUserParameters initialpars(*mParameters);
	GPUFumiliMinimize* myoldfumili = new GPUFumiliMinimize(mycalc);
	double arg[10];
	arg[0]=1500;
	//arg[1]=0.001;
	arg[1]=0.1;
	myoldfumili->ExecuteCommand("FUM",arg,2);
	arg[0]=1e-14;
	myoldfumili->ExecuteCommand("SET EPS",arg,1);
	myoldfumili->SetParameters();
	myoldfumili->SetFitMethod();
	int fstat=myoldfumili->Minimize();

	//	if (fstat!=0){
	//		cout<< "Fit failed!" << endl;
	//	   if (fstat==-2) cout<<"function is not decreasing (or bad derivatives)"<<endl;
	//	   if (fstat==-3) cout<<"error estimations are infinite"<<endl;
	//	   if (fstat==-4) cout<<"maximum number of iterations is exceeded"<<endl;
	//	   return FAILURE;
	//	}

	if (fstat==-2) cout<<"function is not decreasing (or bad derivatives)"<<endl;
	if (fstat==-3) cout<<"error estimations are infinite"<<endl;
	if (fstat!=0 && fstat!=-2&& fstat!=-3){
		cout<< "Fit failed!" << endl;
		// if (fstat==-2) cout<<"function is not decreasing (or bad derivatives)"<<endl;
		// if (fstat==-3) cout<<"error estimations are infinite"<<endl;
		if (fstat==-4) cout<<"maximum number of iterations is exceeded"<<endl;
		return FAILURE;
	}


	//cout << "---- FIT RESULTS ----" << endl;
	double amin; double edm; double errdef; int nvpar; int nparx;
	myoldfumili->GetStats(amin, edm, errdef, nvpar, nparx);
	mLikelihood = amin/2.0;

	ROOT::Minuit2::MnUserParameters  resultpars = myoldfumili->GetParameters();

	if(minhist)
		delete minhist;
	minhist = new GPUMinimizationHistory(
			this,
			initialpars, resultpars,
			mLikelihood, edm, !((bool)fstat));
	delete myoldfumili;
	return OK;
}


STATUS GPUPartialWaveAnalysis::MinuitGradMinimize(GPUPWACalculator * mycalc,
		GPUMinimizationHistory *& minhist){
	// Copy initial parameters
	ROOT::Minuit2::MnUserParameters initialpars(*mParameters);
	// Create objects for the Fit
	ROOT::Minuit2::FCNGradientBase * fcn = new GPUMinuitFCN(mycalc);
	ROOT::Minuit2::MnMigrad * migrad = new ROOT::Minuit2::MnMigrad(*fcn, *mParameters);
	ROOT::Minuit2::VariableMetricMinimizer minimizer;

	//ROOT::Minuit2::MnMachinePrecision prec;
	//cout << "Accuray : " << prec.Eps() << endl;
	// Fix parameters etc.
	migrad->SetPrecision(1e-11);

	// Do Fit
	ROOT::Minuit2::FunctionMinimum minimum = minimizer.Minimize(*fcn,migrad->State(),migrad->Strategy(),2000,20);

	if(!minimum.IsValid()){
		cout << "Fit failed!" << endl;
#ifdef WINDOWS
		if(_isnan(minimum.Fval()))
			cout << "Likelihood NaN!" << endl;
#endif
#ifndef WINDOWS
		if(isnan(minimum.Fval()))
			cout << "Likelihood NaN!" << endl;
#endif
		delete fcn;
		delete migrad;
		return FAILURE;
	}

	ROOT::Minuit2::MnUserParameters  resultpars = minimum.UserParameters();
	if(minhist)
		delete minhist;
	minhist = new GPUMinimizationHistory(
			this,
			initialpars, resultpars,
			minimum.Fval(), minimum.Edm(),
			minimum.IsValid(), minimum.NFcn());
	delete fcn;
	delete migrad;
	return OK;
}


STATUS GPUPartialWaveAnalysis::MinuitMinosMinimize(GPUPWACalculator * mycalc,
		GPUMinimizationHistory *& minhist){
	// Copy initial parameters
	ROOT::Minuit2::MnUserParameters initialpars(*mParameters);

	// Create objects for the Fit
	ROOT::Minuit2::FCNBase * fcn = new GPUMinuitFCN(mycalc);
	ROOT::Minuit2::MnMigrad * migrad = new ROOT::Minuit2::MnMigrad(*fcn, *mParameters);
	ROOT::Minuit2::VariableMetricMinimizer minimizer;

	//ROOT::Minuit2::MnMachinePrecision prec;
	//cout << "Accuray : " << prec.Eps() << endl;
	// Fix parameters etc.
	migrad->SetPrecision(1e-11);

	// Do Fit
	ROOT::Minuit2::FunctionMinimum minimum = minimizer.Minimize(*fcn,migrad->State(),migrad->Strategy(),2000,20);

	if(!minimum.IsValid()){
		cout << "Fit failed!" << endl;
#ifdef WINDOWS
		if(_isnan(minimum.Fval()))
			cout << "Likelihood NaN!" << endl;
#endif
#ifndef WINDOWS
		if(isnan(minimum.Fval()))
			cout << "Likelihood NaN!" << endl;
#endif
		delete fcn;
		delete migrad;
		return FAILURE;
	}

	ROOT::Minuit2::MnMinos * minos = new ROOT::Minuit2::MnMinos(*fcn, minimum,0);

	ROOT::Minuit2::MnUserParameters  resultpars = minimum.UserParameters();
	ROOT::Minuit2::MnUserParameterState upar = minimum.UserState();
	ROOT::Minuit2::MnStrategy strat(1);
	vector<double> pvec = resultpars.Params();
	vector<double> uperrs(pvec.size(),0);
	vector<double> downerrs(pvec.size(),0);
	for(unsigned int i=0; i < (unsigned int)pvec.size(); i++){
		if(!(mParameters->Parameter(i).IsFixed())){
			std::vector<unsigned int> para(1, i);
			double err = upar.Error(i);
			double val = upar.Value(i) - err;
			std::vector<double> xmid(1, val);
			std::vector<double> xdir(1, -err);
			double toler = 1.0;
			int maxcalls = 100;
			ROOT::Minuit2::MnFunctionCross2 cross(*fcn, upar, minimum.Fval(), strat);
			ROOT::Minuit2::MnCross aopt = cross(para, xmid, xdir, toler, maxcalls);
			if(aopt.AtLimit())
				cout << "MnMinos Parameter is at Lower limit." << i << endl;
			if(aopt.AtMaxFcn())
				cout << "MnMinos maximum number of function calls exceeded for Parameter " << i << endl;
			if(aopt.NewMinimum())
				cout << "MnMinos new Minimum found while looking for Parameter " << i << endl;
			if(!aopt.IsValid())
				cout << "MnMinos could not find Lower Value for Parameter " << i << endl;
			err = minimum.UserState().Error(i);
			double lower = aopt.IsValid() ? -1.*err*(1.+ aopt.Value()) : (aopt.AtLimit() ? upar.Parameter(i).LowerLimit() : upar.Value(i));

			val = upar.Value(i) + err;
			xmid[0] = val;
			xdir[0] = err;
			ROOT::Minuit2::MnFunctionCross2 cross2(*fcn, upar, minimum.Fval(), strat);
			ROOT::Minuit2::MnCross aopt2 = cross2(para, xmid, xdir, toler, maxcalls);
			if(aopt2.AtLimit())
				cout << "MnMinos Parameter is at Upper limit." << i << endl;
			if(aopt2.AtMaxFcn())
				cout << "MnMinos maximum number of function calls exceeded for Parameter " << i << endl;
			if(aopt2.NewMinimum())
				cout << "MnMinos new Minimum found while looking for Parameter " << i << endl;
			if(!aopt2.IsValid())
				cout << "MnMinos could not find Upper Value for Parameter " << i << endl;

			double upper = aopt2.IsValid() ? err*(1.+ aopt2.Value()) : (aopt2.AtLimit() ? upar.Parameter(i).UpperLimit() : upar.Value(i));

			uperrs[i] = upper;
			downerrs[i] = lower;

		}

	}

	if(minhist)
		delete minhist;
	minhist = new GPUMinosMinimizationHistory(this,
			initialpars, resultpars,
			minimum.Fval(), minimum.Edm(),
			minimum.IsValid(),
			uperrs, downerrs);


	delete fcn;
	delete migrad;
	delete minos;

	return OK;
}




STATUS GPUPartialWaveAnalysis::DoDynamicFit(FITTER fitter, double deltas, int ngood, double spread, int nfit, bool stopatconvergence){
	std::vector<std::vector<double> > configs;

	for(int i=0; i < nfit; i++){
		std::vector<double> config(GetParameterVector());
		if(i > 0){ // Fit the original configuration first
			for(int j=0; j < (int)config.size(); j++){
				if(!mParameters->Parameter(j).IsFixed()){
					double err = mParameters->Error(j);
					double var;
					if(!mParameters->Parameter(j).HasLimits()){
						// Parameter does not have limits, we are free to move it
						// around in the given range
						double random  = 2.0*(float)rand()/(float)RAND_MAX - 1.0;
						var = spread*err*random;
					} else { // there are limits -> lots of cases...
						if(mParameters->Parameter(j).HasLowerLimit() &&
								mParameters->Parameter(j).HasUpperLimit()){
							// limited on both sides - see wheter limit range or
							// the given range are larger.
							double up = config[j] + spread*err;
							double down = config[j] - spread*err;
							if(up > mParameters->Parameter(j).UpperLimit())
								up = mParameters->Parameter(j).UpperLimit();
							if(down < mParameters->Parameter(j).LowerLimit())
								down = mParameters->Parameter(j).LowerLimit();

							double random = (double)rand()/(double)RAND_MAX;
							var = random*(up-down)+down;
						} else if(mParameters->Parameter(j).HasLowerLimit()){
							// lower limit only
							double up = config[j] + spread*err;
							double down = config[j] - spread*err;
							if(down < mParameters->Parameter(j).LowerLimit())
								down = mParameters->Parameter(j).LowerLimit();
							double random = (double)rand()/(double)RAND_MAX;
							var = random*(up-down)+down;
						} else {
							// upper limit only
							double up = config[j] + spread*err;
							double down = config[j] - spread*err;
							if(up > mParameters->Parameter(j).UpperLimit())
								up = mParameters->Parameter(j).UpperLimit();
							double random = (double)rand()/(double)RAND_MAX;
							var = random*(up-down)+down;
						}
					}
					config[j] = config[j]+var;
				}
			}
		}
		configs.push_back(config);
	}
	return DoDynamicFit(fitter, deltas, ngood, configs, stopatconvergence);
}


STATUS GPUPartialWaveAnalysis::DoMultiFit(FITTER fitter, double spread, int nfit, bool stopatconvergence){
	std::vector<std::vector<double> > configs;

	for(int i=0; i < nfit; i++){
		std::vector<double> config(GetParameterVector());
		if(i > 0){ // Fit the original configuration first
			for(int j=0; j < (int)config.size(); j++){
				if(!mParameters->Parameter(j).IsFixed()){
					double err = mParameters->Error(j);
					//std::cout << i <<", VALUE = " << config[j] << ", ERROR = " << err << std::endl;
					//double err = fabs(config[j]) * 0.1;
					double var;
					if(!mParameters->Parameter(j).HasLimits()){
						// Parameter does not have limits, we are free to move it
						// around in the given range
						double random  = 2.0*(float)rand()/(float)RAND_MAX - 1.0;
						var = spread*err*random;
						//std::cout << "NO LIMITS : " << config[j] << " " << var << config[j]+var << std::endl;
						config[j] = config[j]+var;
					} else { // there are limits -> lots of cases...
						if(mParameters->Parameter(j).HasLowerLimit() &&
								mParameters->Parameter(j).HasUpperLimit()){
							// limited on both sides - see wheter limit range or
							// the given range are larger.
							double up = config[j] + spread*err;
							double down = config[j] - spread*err;
							if(up > mParameters->Parameter(j).UpperLimit())
								up = mParameters->Parameter(j).UpperLimit();
							if(down < mParameters->Parameter(j).LowerLimit())
								down = mParameters->Parameter(j).LowerLimit();

							double random = (double)rand()/(double)RAND_MAX;
							var = random*(up-down)+down;
							//std::cout << "HAS LIMITS : " << config[j] << " " << random << " " << var << std::endl;
						} else if(mParameters->Parameter(j).HasLowerLimit()){
							// lower limit only
							double up = config[j] + spread*err;
							double down = config[j] - spread*err;
							if(down < mParameters->Parameter(j).LowerLimit())
								down = mParameters->Parameter(j).LowerLimit();
							double random = (double)rand()/(double)RAND_MAX;
							var = random*(up-down)+down;
						} else {
							// upper limit only
							double up = config[j] + spread*err;
							double down = config[j] - spread*err;
							if(up > mParameters->Parameter(j).UpperLimit())
								up = mParameters->Parameter(j).UpperLimit();
							double random = (double)rand()/(double)RAND_MAX;
							var = random*(up-down)+down;
						}
						config[j] = var;
						//std::cout << "HAS LIMITS : " << config[j] << std::endl;
					}
					//config[j] = config[j]+var;
				}
			}
		}
		configs.push_back(config);
	}
	return DoMultiFit(fitter, configs, stopatconvergence);
}



TGraph * GPUPartialWaveAnalysis::ScanParameter(FITTER fitter,
		int parameterindex,
		double min,
		double max,
		int steps){

	double * xvalues = new double[steps];
	double * plotxvalues = new double[steps];
	double * yvalues = new double[steps];

	//std::vector<double> originalpars = mParameters->Params();
	//std::vector<double> originalerrs = mParameters->Errors();

	ROOT::Minuit2::MnUserParameters * parcopy = GetParameterCopy();

	for(int i=0; i < steps; i++){
		xvalues[i] = min+i*(max-min)/(steps-1.0);
	}
	int index =0;

	double lastlikelihood;
	double lh = 777777;

	for(int i=0; i < steps; i++){
		//	SetParameterVector(originalpars);
		//	SetParameterErrorVector(originalerrs);
		//	ReleaseParameter(parameterindex);
		SetParameters(new ROOT::Minuit2::MnUserParameters(*parcopy));
		FixParameter(parameterindex, xvalues[i]);
		MCIntegral();
		Reset(1);
		if(!DoFit(fitter)){
			lh = mLastFitHistory->GetMinimumLikelihood();
			//plotxvalues[index] = xvalues[i];
			//	index++;
		} else {
			//SetParameterVector(originalpars);
			//SetParameterErrorVector(originalerrs);
			if(mBestFitHistory){
				delete mBestFitHistory;
				mBestFitHistory = 0;
			}
			SetParameters(new ROOT::Minuit2::MnUserParameters(*parcopy));
			FixParameter(parameterindex, xvalues[i]);
			DoMultiFit(fitter,5,100,true);
			if(mBestFitHistory){
				lh = mBestFitHistory->GetMinimumLikelihood();
				//plotxvalues[index] = xvalues[i];
				//	index++;
			} else {
				lh = 777777;
			}
		}
		if(lh != 777777 && (i == 0 || lh - lastlikelihood < 100.0)){
			yvalues[index] = lh;
			plotxvalues[index] = xvalues[i];
			index++;
			lastlikelihood = lh;
		}
		Reset(0);
	}

	TGraph * graph = new TGraph(index, plotxvalues, yvalues);
	return graph;
}

bool GPUPartialWaveAnalysis::HasFreeResonanceParameters() const{
	ROOT::Minuit2::MnUserParameters * pars = GetParameters();
	bool free = false;
	vector<GPUPartialWave *>::iterator it_i;
	vector<GPUPartialWave *> waves;
	waves =  GetWaves()->GetActiveWaves();
	for(it_i = waves.begin(); it_i < waves.end(); ++it_i){
		vector<unsigned int *> mp = (*it_i)->GetDynamicParameters();
		//cout << "Size: " << mp.size() << endl;
		for(unsigned int j =0; j < mp.size(); j++){
			//cout << "Par: " << *(mp[j]) << endl;
			if(!pars->Parameter(*(mp[j])).IsFixed()){
				free = true;
			}
		}
	}
	return free;
}

GPULookupTable * GPUPartialWaveAnalysis::GetLookupTable(unsigned int index){
	if(index == GetDataIndex()){
		if(mLookupData){
			return mLookupData;
		} else {
			return new GPUPartialWaveLookupTable(GetWaves(),index);
		}
	} else if(index == GetMCIndex()){
		if(mLookupMC)
			return mLookupMC;
		else
			return new GPUPartialWaveLookupTable(GetWaves(),index);
	}
	cout << "Invalid index for lookup table" << endl;
	assert(0);
}

void GPUPartialWaveAnalysis::MCIntegral(bool all){
	GPULookupTable * lut = GetLookupTable(GetDataIndex());
	GPUPWAAmplitudeCalculator * mycalc = new GPUPWAAmplitudeCalculator(this, lut, GetLookupTable(GetMCIndex()), mWeights);
	mycalc->WriteMCIntegralFile(all);
	delete mycalc;
	delete lut;
}


STATUS GPUPartialWaveAnalysis::DoFit(FITTER fitter){
	assert(mWeights[GetDataIndex()]);

	GPUPWACalculator * mycalc;

	if(HasFreeResonanceParameters()){
		if(fitter == MINUIT || fitter == MINUITMINOS){
			cout << "Free resonance paramaters in the Fit - expect minimization to be slower" << endl;
			mycalc = new GPUPWAFreeCalculator(this, GetLookupTable(GetDataIndex()), GetLookupTable(GetMCIndex()),mWeights);
		} else {
			cout << "ERROR: Free resonance parameters currently only supported with the MINUIT and MINUITMINOS fitters" << endl;
			assert(0);
		}
	} else {
		mycalc = new GPUPWAAmplitudeCalculator(this, GetLookupTable(GetDataIndex()), GetLookupTable(GetMCIndex()), mWeights);
	}
	GPUMinimizationHistory * minhist = 0;
	STATUS mystatus;

	// Copy initial parameters
	ROOT::Minuit2::MnUserParameters initialpars(*mParameters);

	//mycalc->ReadMCIntegralFile();
	switch(fitter){
		case MINUIT:
			mystatus = MinuitMinimize(mycalc, minhist);
			break;
		case FUMILI:
			mystatus = FumiliMinimize(mycalc, minhist);
			break;
		case MINUITGRAD:
			mystatus = MinuitGradMinimize(mycalc, minhist);
			break;
		case MINUITMINOS:
			mystatus = MinuitMinosMinimize(mycalc, minhist);
			break;
		case OLDFUMILI:
			mystatus = OldfumiliMinimize(mycalc, minhist);
			break;

		case INITONLY:
			mcalc = mycalc;
			return OK;
			break;
		default:
			cout << "Unkown fitter, aborting!" << endl;
			return FAILURE;
	}


	int fitcount = mRuncounter->IncrementFitCounter();
	cout << endl << endl;
	if(!mystatus){
		minhist->Print();
		ReportConstraints(cout);
    //comment by xiongxa
/*
		char paraoutputfilename[255];
		sprintf(paraoutputfilename,"para_output_%s_%04i.txt", GetNoSpaceName(), fitcount);
		ofstream paraoutputfile(paraoutputfilename);
		minhist->PrintResult(paraoutputfile);

		char parainputfilename[255];
		sprintf(parainputfilename,"para_input_%s_%04i.txt", GetNoSpaceName(), fitcount);
		ofstream parainputfile(parainputfilename);
		minhist->PrintInput(parainputfile);

		char outfilename[255];
		sprintf(outfilename,"fitresult_%s_%04i.txt", GetNoSpaceName(), fitcount);
		ofstream resultfile(outfilename);
		if(!outfilename){
			cout << "ERROR: Cannot open file " << outfilename << " for writing!" << endl;
		} else {
			minhist->Print(resultfile);
			resultfile.close();
		}
*/

		if(mLastFitHistory)
			delete mLastFitHistory;
		mLastFitHistory = new GPUMinimizationHistory(*minhist);
		if(mBestFitHistory){
			if(mBestFitHistory->GetMinimumLikelihood() > minhist->GetMinimumLikelihood()){
				delete mBestFitHistory;
				mBestFitHistory = new GPUMinimizationHistory(*minhist);
			}
		} else {
			mBestFitHistory = new GPUMinimizationHistory(*minhist);
		}
	} else {
		//	cout << "Fit failed..." << endl;
	}
	delete minhist;
	delete mycalc;
	return mystatus;
}

STATUS GPUPartialWaveAnalysis::GetAmplitudes(char * filename){
	assert(mWeights[GetDataIndex()]);
	GPULookupTable * datatable = GetLookupTable(GetDataIndex());
	GPULookupTable * mctable = GetLookupTable(GetMCIndex());
	GPUPWAAmplitudeCalculator * mycalc = new GPUPWAAmplitudeCalculator(this, datatable, mctable, mWeights);

	mycalc->GetAmplitudes(mParameters->Params(), filename);

	delete mycalc;
	delete datatable;
	delete mctable;
	return OK;
}

STATUS GPUPartialWaveAnalysis::DoDynamicFit(FITTER fitter, double deltas, int ngood, std::vector<std::vector<double> > inputs, bool stopatconvergence){
	assert(mWeights[GetDataIndex()]);


	GPUPWACalculator * mycalc;

	GPULookupTable * datatable = GetLookupTable(GetDataIndex());
	GPULookupTable * mctable = GetLookupTable(GetMCIndex());

	if(HasFreeResonanceParameters()){
		if(fitter == MINUIT){
			cout << "Free resonance paramaters in the Fit - expect minimization to be slower" << endl;
			mycalc = new GPUPWAFreeCalculator(this, datatable, mctable, mWeights);
		} else {
			cout << "ERROR: Free resonance parameters currently only supported with the MINUIT fiter" << endl;
			assert(0);
		}
	} else {
		mycalc = new GPUPWAAmplitudeCalculator(this,  datatable, mctable, mWeights);
	}

	//GPUPWAAmplitudeCalculator<T> * mycalc = new GPUPWAAmplitudeCalculator<T>(this, mWaves, mWeights);

	GPUMinimizationHistory * minhist = 0;

	STATUS mystatus = FAILURE;

	std::vector<double> originalerrs = mParameters->Errors();

	double deltas_temp=1000;
	int igood = 0;
	int fitcount = mRuncounter->GetFitCounter();
	char outfilename[255];
	sprintf(outfilename,"multifitresults_%s_%i.txt", GetNoSpaceName(), fitcount);
	std::cout <<std::fixed<<endl;
	std::cout <<std::setprecision(4)<<endl;

	ofstream resultfile(outfilename);
	if(!outfilename){
		cout << "ERROR: Cannot open file " << outfilename << " for writing!" << endl;
		return FAILURE;
	}

	for(int i =0; i < (int)inputs.size(); i++){

		//	for(int j = 0; j < (int)inputs[i].size(); j++)
		//		cout << j << ":  " << inputs[i][j] << " +- " << originalerrs[j] << endl;


		SetParameterVector(inputs[i]);
		SetParameterErrorVector(originalerrs);

		// Copy initial parameters
		ROOT::Minuit2::MnUserParameters initialpars(*mParameters);

		//mycalc->ReadMCIntegralFile();
		switch(fitter){
			case MINUIT:
				mystatus = MinuitMinimize(mycalc, minhist);
				break;
			case FUMILI:
				mystatus = FumiliMinimize(mycalc, minhist);
				break;
			case MINUITGRAD:
				mystatus = MinuitGradMinimize(mycalc, minhist);
				break;
			case MINUITMINOS:
				mystatus = MinuitMinosMinimize(mycalc, minhist);
				break;
			case OLDFUMILI:
				mystatus = OldfumiliMinimize(mycalc, minhist);
				break;

			case INITONLY:
				mcalc = mycalc;
				return OK;
				break;
			default:
				cout << "Unkown fitter, aborting!" << endl;
				return FAILURE;
		}

		if(mystatus == OK){
			minhist->Print();
			int fitcount = mRuncounter->IncrementFitCounter();
			//resultfile <<  fixed <<endl;
			//resultfile <<  setprecision(4) <<endl;
			if(!mBestFitHistory){mBestFitHistory = new GPUMinimizationHistory(*minhist);}
			resultfile << "Fit " << setw(10) << fitcount <<  ": Minimum Likelihood : "
				<< std::fixed  << std::setprecision(4) << minhist->GetMinimumLikelihood()
				<< ":  iGood : "<< igood
				<< ":  mini for above : " << mBestFitHistory->GetMinimumLikelihood()<<endl;

			char paraoutputfilename[255];
			sprintf(paraoutputfilename,"para_output_%s_%04i.txt", GetNoSpaceName(), fitcount);
			ofstream paraoutputfile(paraoutputfilename);
			minhist->PrintOutputPara(paraoutputfile);

			if(mLastFitHistory) {
				delete mLastFitHistory;
			}
			mLastFitHistory = new GPUMinimizationHistory(*minhist);
			if(mBestFitHistory){
				//				if(mBestFitHistory->GetMinimumLikelihood() > minhist->GetMinimumLikelihood()){
				//					delete mBestFitHistory;
				//					mBestFitHistory = new GPUMinimizationHistory(*minhist);
				//				}

				deltas_temp = fabs(mBestFitHistory->GetMinimumLikelihood() - minhist->GetMinimumLikelihood());
				if (deltas_temp <= deltas) {
					igood = igood + 1 ;
				}else if(mBestFitHistory->GetMinimumLikelihood() > minhist->GetMinimumLikelihood()){
					igood = 0 ;
				}

				if(mBestFitHistory->GetMinimumLikelihood() > minhist->GetMinimumLikelihood()){
					delete mBestFitHistory;
					mBestFitHistory = new GPUMinimizationHistory(*minhist);
				}

			} else {
				mBestFitHistory = new GPUMinimizationHistory(*minhist);
			}
			if(igood>ngood) {
				break;
			}
			if(stopatconvergence) {
				break;
			}
		}
		//lixl             else {
		//lixl			int fitcount = mRuncounter->IncrementFitCounter();
		//lixl			resultfile << "Fit " << setw(8) << fitcount <<  ": Did not converge."  << endl;
		//lixl 		}
	}
	if(mBestFitHistory){
		resultfile << "Best Likelihood obtained was: "
			<< setw(12) << mBestFitHistory->GetMinimumLikelihood() << endl;

		SetParameters(new ROOT::Minuit2::MnUserParameters(mBestFitHistory->GetResultParameters()));
	}
	resultfile.close();


	delete minhist;
	delete mycalc;
	delete datatable;
	delete mctable;
	return mystatus;
}


STATUS GPUPartialWaveAnalysis::DoMultiFit(FITTER fitter, std::vector<std::vector<double> > inputs, bool stopatconvergence){
	assert(mWeights[GetDataIndex()]);


	GPUPWACalculator * mycalc;
	GPULookupTable * datatable = GetLookupTable(GetDataIndex());
	GPULookupTable * mctable = GetLookupTable(GetMCIndex());
	if(HasFreeResonanceParameters()){
		if(fitter == MINUIT){
			cout << "Free resonance paramaters in the Fit - expect minimization to be slower" << endl;
			mycalc = new GPUPWAFreeCalculator(this, datatable, mctable, mWeights);
		} else {
			cout << "ERROR: Free resonance parameters currently only supported with the MINUIT fiter" << endl;
			assert(0);
		}
	} else {
		mycalc = new GPUPWAAmplitudeCalculator(this, datatable, mctable, mWeights);
	}

	//GPUPWAAmplitudeCalculator<T> * mycalc = new GPUPWAAmplitudeCalculator<T>(this, mWaves, mWeights);

	GPUMinimizationHistory * minhist = 0;

	STATUS mystatus = FAILURE;

	std::vector<double> originalerrs = mParameters->Errors();

	int fitcount = mRuncounter->GetFitCounter();
	char outfilename[255];

	sprintf(outfilename,"multifitresults_%s_%i.txt", GetNoSpaceName(), fitcount);


	ofstream resultfile(outfilename);
	if(!outfilename){
		cout << "ERROR: Cannot open file " << outfilename << " for writing!" << endl;
		return FAILURE;
	}

	for(int i =0; i < (int)inputs.size(); i++){

		//	for(int j = 0; j < (int)inputs[i].size(); j++)
		//		cout << j << ":  " << inputs[i][j] << " +- " << originalerrs[j] << endl;


		SetParameterVector(inputs[i]);
		SetParameterErrorVector(originalerrs);

		// Copy initial parameters
		ROOT::Minuit2::MnUserParameters initialpars(*mParameters);

		//mycalc->ReadMCIntegralFile();
		switch(fitter){
			case MINUIT:
				mystatus = MinuitMinimize(mycalc, minhist);
				break;
			case FUMILI:
				mystatus = FumiliMinimize(mycalc, minhist);
				break;
			case MINUITGRAD:
				mystatus = MinuitGradMinimize(mycalc, minhist);
				break;
			case MINUITMINOS:
				mystatus = MinuitMinosMinimize(mycalc, minhist);
				break;
			case OLDFUMILI:
				mystatus = OldfumiliMinimize(mycalc, minhist);
				break;

			case INITONLY:
				mcalc = mycalc;
				return OK;
				break;
			default:
				cout << "Unkown fitter, aborting!" << endl;
				return FAILURE;
		}

		if(mystatus == OK){
			minhist->Print();
			int fitcount = mRuncounter->IncrementFitCounter();

			resultfile << "Fit " << setw(20) << fitcount <<  ": Minimum Likelihood : "
				<< std::setprecision(20) << minhist->GetMinimumLikelihood() <<endl;
/*

			char paraoutputfilename[255];
			sprintf(paraoutputfilename,"para_output_%s_%04i.txt", GetNoSpaceName(), fitcount);
			ofstream paraoutputfile(paraoutputfilename);
			minhist->PrintOutputPara(paraoutputfile);

			char resoutputfilename[255];
			sprintf(resoutputfilename,"res_output_%s_%04i.txt", GetNoSpaceName(), fitcount);
			ofstream resoutputfile(resoutputfilename);
			minhist->PrintOutputPara(resoutputfile);

*/

			if(mLastFitHistory)

				delete mLastFitHistory;
			mLastFitHistory = new GPUMinimizationHistory(*minhist);
			if(mBestFitHistory){
				if(mBestFitHistory->GetMinimumLikelihood() > minhist->GetMinimumLikelihood()){
					delete mBestFitHistory;
					mBestFitHistory = new GPUMinimizationHistory(*minhist);
				}
			} else {
				mBestFitHistory = new GPUMinimizationHistory(*minhist);
			}
			if(stopatconvergence)
				break;
		} else {
			int fitcount = mRuncounter->IncrementFitCounter();
			resultfile << "Fit " << setw(8) << fitcount <<  ": Did not converge."  << endl;
		}
	}
	if(mBestFitHistory){
		resultfile << "Best Likelihood obtained was: "
			<< setw(12) << mBestFitHistory->GetMinimumLikelihood() << endl;

		SetParameters(new ROOT::Minuit2::MnUserParameters(mBestFitHistory->GetResultParameters()));
	}
	resultfile.close();


	delete minhist;
	delete mycalc;
	delete datatable;
	delete mctable;
	return mystatus;
}


GPUDataStream<float2> * GPUPartialWaveAnalysis::pars2streamCartesian() const{
	vector<GPUPartialWave *> waves;
	waves =  GetWaves()->GetActiveWaves();
	int npars =0;
	float2 * temp = new float2[waves.size()];
	vector<GPUPartialWave *>::iterator it_i;
	for(it_i = waves.begin(); it_i < waves.end(); ++it_i){
		float2 val = mfloat2(mParameters->Value((*it_i)->GetMagnitudeParameter())*cos(mParameters->Value((*it_i)->GetPhaseParameter())),
				mParameters->Value((*it_i)->GetMagnitudeParameter())*sin(mParameters->Value((*it_i)->GetPhaseParameter())));
		temp[npars] = val;
		/*	cout << "Wave " << npars << " Magnitude " << mParameters->Value((*it_i)->GetMagnitudeParameter()) << " Phase " << mParameters->Value((*it_i)->GetPhaseParameter()) << endl;
			cout << "Cartesian: " << val. x << "," << val.y << endl;*/
		npars++;
	}

	/*for(vector<GPUPartialWave *>::iterator it_i = waves.begin(); it_i < waves.end(); ++it_i){
	  float2 val(mParameters->Value((*it_i)->GetMassParameter()),
	  mParameters->Value((*it_i)->GetWidthParameter()));
	  temp[npars] = val;
	  npars++;
	  }
	  for(int i =0; i < nadd; i++){
	  float2 val(mParameters->Value((unsigned int)waves.size()*4+i),0);
	  temp[npars] = val;
	  npars++;
	  }*/
	if(mparscartesian)
		delete mparscartesian;
	mparscartesian = new GPUDataStream<float2>(mdeviceinterface, npars);
	mparscartesian->Write(temp);
	mparscartesian->GetEvent().wait();
	delete [] temp;
	return mparscartesian;
}


GPUDataStream<float2>* GPUPartialWaveAnalysis::pars2streamPolar() const{
	vector<GPUPartialWave *> waves;
	waves =  GetWaves()->GetActiveWaves();
	int npars =0;
	float2 * temp = new float2[waves.size()];
	vector<GPUPartialWave *>::iterator it_i;
	for(it_i = waves.begin(); it_i < waves.end(); ++it_i){
		float2 val = mfloat2(mParameters->Value((*it_i)->GetMagnitudeParameter()),
				mParameters->Value((*it_i)->GetPhaseParameter()));
		temp[npars] = val;
		npars++;
	}
	/*	for(vector<GPUPartialWave *>::iterator it_i = waves.begin(); it_i < waves.end(); ++it_i){
		float2 val(mParameters->Value((*it_i)->GetMassParameter()),
		mParameters->Value((*it_i)->GetWidthParameter()));
		temp[npars] = val;
		npars++;
		}
		for(int i =0; i < nadd; i++){
		float2 val(mParameters->Value((unsigned int)waves.size()*4+i),0);
		temp[npars] = val;
		npars++;
		}*/
	if(mparspolar)
		delete mparspolar;
	mparspolar = new GPUDataStream<float2>(mdeviceinterface, npars);
	mparspolar->Write(temp);
	mparspolar->GetEvent().wait();
	delete [] temp;
	return mparspolar;
}

GPUDataStream<float4>* GPUPartialWaveAnalysis::allpars2streamCartesian() const{
	vector<GPUPartialWave *> waves;
	waves =  GetWaves()->GetActiveWaves();
	int npars =0;
	float4 * temp = new float4[waves.size()];
	vector<GPUPartialWave *>::iterator it_i;
	for(it_i = waves.begin(); it_i < waves.end(); ++it_i){
		if((*it_i)->GetDynamicParameters().size() != 2)
			assert(0);
		float4 val = mfloat4(mParameters->Value((*it_i)->GetMagnitudeParameter())*cos(mParameters->Value((*it_i)->GetPhaseParameter())),
				mParameters->Value((*it_i)->GetMagnitudeParameter())*sin(mParameters->Value((*it_i)->GetPhaseParameter())),
				mParameters->Value((*it_i)->GetDynamicParameter(0)),
				mParameters->Value((*it_i)->GetDynamicParameter(1))
				);
		temp[npars] = val;
		npars++;
	}
	GPUDataStream<float4> * parstream = new GPUDataStream<float4>(mdeviceinterface, npars);
	parstream->Write(temp);
	delete [] temp;
	return parstream;
}

GPUDataStream<float4>* GPUPartialWaveAnalysis::allpars2streamPolar() const{
	vector<GPUPartialWave *> waves;
	waves =  GetWaves()->GetActiveWaves();
	int npars =0;
	float4 * temp = new float4[waves.size()];
	vector<GPUPartialWave *>::iterator it_i;
	for(it_i = waves.begin(); it_i < waves.end(); ++it_i){
		if((*it_i)->GetDynamicParameters().size() != 2)
			assert(0);
		float4 val = mfloat4(mParameters->Value((*it_i)->GetMagnitudeParameter()),
				mParameters->Value((*it_i)->GetPhaseParameter()),
				mParameters->Value((*it_i)->GetDynamicParameter(0)),
				mParameters->Value((*it_i)->GetDynamicParameter(1)));
		temp[npars] = val;
		npars++;
	}
	GPUDataStream<float4> * parstream = new GPUDataStream<float4>(mdeviceinterface, npars);
	parstream->Write(temp);
	delete [] temp;
	return parstream;
}

float** GPUPartialWaveAnalysis::parmatrix() const{
	vector<GPUPartialWave *> waves;
	waves =  GetWaves()->GetActiveWaves();
	//cout << "size: " <<  mParameters->Params().size() << endl;
	float ** matrix = new float*[mParameters->Params().size()];
	float * matrixstore = new float[(int)(mParameters->Params().size()*2*waves.size())];
	for(unsigned int i =0; i < mParameters->Params().size(); i++){
		matrix[i] = &matrixstore[2*i*waves.size()];
		for(unsigned int j =0; j < 2*waves.size(); j++){
			matrix[i][j] =0.0;
		}
	}
	for(unsigned int i =0; i < waves.size(); i++){
		//cout << "Mag " << waves[i]->GetMagnitudeParameter() << endl;
		matrix[waves[i]->GetMagnitudeParameter()][2*i] = 1;
		//cout << "Phase " << waves[i]->GetPhaseParameter() << endl;
		matrix[waves[i]->GetPhaseParameter()][2*i+1] = 1;
	}
	return matrix;
}

float** GPUPartialWaveAnalysis::allparmatrix() const{
	vector<GPUPartialWave *> waves;
	waves =  GetWaves()->GetActiveWaves();
	float ** matrix = new float*[mParameters->Params().size()];
	float * matrixstore = new float[(int)(mParameters->Params().size()*4*waves.size())];
	for(unsigned int i =0; i < mParameters->Params().size(); i++){
		matrix[i] = &matrixstore[4*i*waves.size()];
		for(unsigned int j =0; j < 4*waves.size(); j++){
			matrix[i][j] =0.0;
		}
	}
	for(unsigned int i =0; i < waves.size(); i++){
		if(waves[i]->GetDynamicParameters().size() != 2)
			assert(0);
		matrix[waves[i]->GetMagnitudeParameter()][4*i] = 1;
		matrix[waves[i]->GetPhaseParameter()][4*i+1] = 1;
		matrix[waves[i]->GetDynamicParameter(0)][4*i+2] = 1;
		matrix[waves[i]->GetDynamicParameter(1)][4*i+3] = 1;
	}
	return matrix;
}

float ** GPUPartialWaveAnalysis::GetMCDcs(bool dooffdiagonal, int nblocks){
	GPUPWAAmplitudeCalculator * mycalc = new GPUPWAAmplitudeCalculator(this, GetLookupTable(GetDataIndex()), GetLookupTable(GetMCIndex()),mWeights);
	float ** temp = mycalc->GetDcs(mMCIndex, dooffdiagonal, nblocks);
	delete mycalc;
	return temp;
}




void GPUPartialWaveAnalysis::InitCalculator() {
	GPUPWAAmplitudeCalculator * mycalc = new GPUPWAAmplitudeCalculator(this, GetLookupTable(GetDataIndex()), GetLookupTable(GetMCIndex()), mWeights);
	mcalc=mycalc;
}

double** GPUPartialWaveAnalysis::GetPartialTotalXSection() const{
	//GPUPWAAmplitudeCalculator<T> * mycalc = new GPUPWAAmplitudeCalculator<T>(this, mWaves, mWeights);
	// mcalc = mycalc;

	double** temp = mcalc->PartialTotalXSection();

	//delete mcalc;
	return temp;
}

double** GPUPartialWaveAnalysis::GetPartialTotalXSectionDerivative(int parnum) const{
	//GPUPWAAmplitudeCalculator<T> * mycalc = new GPUPWAAmplitudeCalculator<T>(this, mWaves, mWeights);
	double** temp = mcalc->PartialTotalXSectionDerivative(parnum);
	//delete mcalc;
	return temp;
}

