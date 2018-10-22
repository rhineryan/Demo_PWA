#include "GPUDataStream.h"
#include <cassert>
#include <cmath>

//#include "GPUPartialWaveAnalysis.h"
#include "GPUDataDependentObject.h"
#ifdef USECPU
#include "Summing_cpu.h"
#else
#include "Summing.h"
#endif
#include "DeviceInterface.h"
#include "vector_operators.h"

#define PRINTNUM 10
#define PRINTSTART 0

#ifdef USECPU
using namespace Summing_CPU;
#else
using namespace Summing_GPU;
#endif

template <typename T>
GPUDataStream<T>::GPUDataStream(const DeviceInterface * dev, unsigned int size):Stream<T>(dev, size),mnstreams(0),mysize(size)
{
}

template <typename T>
GPUDataStream<T>::GPUDataStream(const DeviceInterface * dev, unsigned int * sizes):Stream<T>(dev, sizes[0], sizes[1]),mnstreams(0),mysize(sizes[0]*sizes[1])
{
}



template <typename T>
GPUDataStream<T>::GPUDataStream(const DeviceInterface * dev, unsigned int m, unsigned int n):Stream<T>(dev, m, n),mnstreams(0),mysize(m*n)
{
}

template <typename T>
GPUDataStream<T>::GPUDataStream(const DeviceInterface * dev, unsigned int flag, unsigned int nstreams, unsigned int size):
  Stream<T>(dev,0), mnstreams(nstreams), mysize(size){
	assert(mnstreams > 0);
	for(unsigned int i = 0; i < nstreams; i++){
		//cout << i << endl;
		mstreams.push_back(new GPUDataStream<T>(dev, size));
	}
	assert(mstreams.size()==nstreams);
}

template <typename T>
GPUDataStream<T>::~GPUDataStream(void)
{
	for(int i = 0; i < (int)mstreams.size(); i++){
		delete mstreams[i];
	}
	for(int i = 0; i < (int)msumstreams.size(); i++){
		if(msumstreams[i])
			delete msumstreams[i];
	}
	for(int i = 1; i < (int)mcompsumstreams.size(); i++){
		if(mcompsumstreams[i])
			delete mcompsumstreams[i];
	}
	for(int i = 0; i < (int)m2dsumstreams.size(); i++){
			if(m2dsumstreams[i])
				delete m2dsumstreams[i];
		}
}


template <typename T>
void GPUDataStream<T>::print(){
		cout << "*********************************" << endl;
		unsigned int m = Stream<T>::memsize();
		T * data = new T[m/sizeof(T)];
		this->Read(data);
		for(int i =PRINTSTART; i < PRINTSTART+PRINTNUM; i++){
			cout << i << ": " << data[i] << endl;
		}
		cout << "*********************************" << endl;
		delete [] data;
	}

template <typename T>
void GPUDataStream<T>::printAt(int index, int n){
		cout << "*********************************" << endl;
		unsigned int m = Stream<T>::memsize();
		T * data = new T[m/sizeof(T)];
		this->Read(data);
		for(int i=index; i < index+n; i++){
			cout << i << ": " << data[i] << endl;
		}
		cout << "*********************************" << endl;
		delete [] data;
	}

template <typename T>
double GPUDataStream<T>::sumCPU(){
	unsigned int m = Stream<T>::memsize();
	T * data = new T[m];
	this->Read(data);
	double x = 0.0;
	for(unsigned int i =1; i < m; i++){
		x = x + addcomponents(data[i]);
	}
	delete [] data;
	return x;
}

template <typename T>
	double * GPUDataStream<T>::sumcomponentsCPU(){
	cout << "Warning! Summing for this type not implemented" << endl;
	return 0;
}

template <>
	double * GPUDataStream<float>::sumcomponentsCPU(){
	double * out = new double[1];
	out[0] = sumCPU();
	return out;
}

template <>
	double * GPUDataStream<double>::sumcomponentsCPU(){
	double * out = new double[1];
	out[0] = sumCPU();
	return out;
}

template <>
	double * GPUDataStream<double2>::sumcomponentsCPU(){
	unsigned int m = Stream<double2>::memsize()/sizeof(double2);
	double2 * data = new double2[m];
	this->Read(data);
	double * x = new double[2];
	x[0] = 0.0;
	x[1] = 0.0;
	for(unsigned int i =1; i < m; i++){
		x[0] += data[i].x;
		x[1] += data[i].y;
	}
	delete [] data;
	return x;
}

template <>
	double * GPUDataStream<float2>::sumcomponentsCPU(){
	unsigned int m = Stream<float2>::memsize()/sizeof(float2);
	float2 * data = new float2[m];
	this->Read(data);
	double * x = new double[2];
	x[0] = 0.0;
	x[1] = 0.0;
	for(unsigned int i =1; i < m; i++){
		x[0] += (double)data[i].x;
		x[1] += (double)data[i].y;
	}
	delete [] data;
	return x;
}

template <>
	double * GPUDataStream<float4>::sumcomponentsCPU(){
	unsigned int m = Stream<float4>::memsize()/sizeof(float4);
	float4 * data = new float4[m];
	this->Read(data);
	double * x = new double[4];
	x[0] = 0.0;
	x[1] = 0.0;
	x[2] = 0.0;
	x[3] = 0.0;
	for(unsigned int i =1; i < m; i++){
		x[0] += (double)data[i].x;
		x[1] += (double)data[i].y;
		x[2] += (double)data[i].z;
		x[3] += (double)data[i].w;
	}
	delete [] data;
	return x;
}


//////////////////////////////////


template <typename T>
	double * GPUDataStream<T>::sumcomponentsweightedCPU(GPUDataStream<float> * weights){
	cout << "Warning! Weighted summing for this type not implemented" << endl;
	return 0;
}

template <>
	double * GPUDataStream<float>::sumcomponentsweightedCPU(GPUDataStream<float> * weights){
	unsigned int m = Stream<float>::memsize()/sizeof(float);
	float * data = new float[m];
	this->Read(data);

	float * wbuffer = new float[m];
	weights->Read(wbuffer);

	double * x = new double[1];
	x[0] = 0.0;
	for(unsigned int i =1; i < m; i++){
		x[0] += (double)(data[i] * wbuffer[i]);
	}
	delete [] data;
	delete [] wbuffer;
	return x;
}

template <>
	double * GPUDataStream<double>::sumcomponentsweightedCPU(GPUDataStream<float> * weights){
	unsigned int m = Stream<double>::memsize()/sizeof(double);
	double * data = new double[m];
	this->Read(data);

	float * wbuffer = new float[m];
	weights->Read(wbuffer);

	double * x = new double[1];
	x[0] = 0.0;
	for(unsigned int i =1; i < m; i++){
		x[0] += data[i] * wbuffer[i];
	}
	delete [] data;
	delete [] wbuffer;
	return x;
}

template <>
	double * GPUDataStream<double2>::sumcomponentsweightedCPU(GPUDataStream<float> * weights){
	unsigned int m = Stream<double2>::memsize()/sizeof(double2);
	double2 * data = new double2[m];
	this->Read(data);

	float * wbuffer = new float[m];
	weights->Read(wbuffer);

	double * x = new double[2];
	x[0] = 0.0;
	x[1] = 0.0;
	for(unsigned int i =1; i < m; i++){
		x[0] += data[i].x * wbuffer[i];
		x[1] += data[i].y * wbuffer[i];
	}
	delete [] data;
	delete [] wbuffer;
	return x;
}

template <>
	double * GPUDataStream<float2>::sumcomponentsweightedCPU(GPUDataStream<float> * weights){
	unsigned int m = Stream<float2>::memsize()/sizeof(float2);
	float2 * data = new float2[m];
	this->Read(data);

	float * wbuffer = new float[m];
	weights->Read(wbuffer);

	double * x = new double[2];
	x[0] = 0.0;
	x[1] = 0.0;
	for(unsigned int i =1; i < m; i++){
		x[0] += (double)data[i].x * wbuffer[i];
		x[1] += (double)data[i].y * wbuffer[i];
	}
	delete [] data;
	delete [] wbuffer;
	return x;
}


template <>
	double * GPUDataStream<float4>::sumcomponentsweightedCPU(GPUDataStream<float> * weights){
	unsigned int m = Stream<float4>::memsize()/sizeof(float4);
	float4 * data = new float4[m];
	this->Read(data);

	float * wbuffer = new float[m];
	weights->Read(wbuffer);

	double * x = new double[4];
	x[0] = 0.0;
	x[1] = 0.0;
	x[2] = 0.0;
	x[3] = 0.0;
	for(unsigned int i =1; i < m; i++){
		x[0] += (double)data[i].x * wbuffer[i];
		x[1] += (double)data[i].y * wbuffer[i];
		x[2] += (double)data[i].z * wbuffer[i];
		x[3] += (double)data[i].w * wbuffer[i];
	}
	delete [] data;
	return x;
}
template <typename T>
void GPUDataStream<T>::initsumnumbers(){
	unsigned int m = Stream<T>::memsize()/sizeof(T);
	unsigned int n = m;
	unsigned int nextsize;
	unsigned int reminder;
	if(n <= 16){
		mnsum.push_back(0);
		mreminders.push_back(n);
		msizes.push_back(1);
	} else {
		while(n > 16){
			nextsize = n/16;
			reminder = n%16;
			mnsum.push_back(nextsize);
			mreminders.push_back(reminder);
			if(reminder)
				n = nextsize + 1;
			else
				n = nextsize;
			msizes.push_back(n);
		}
		if(n > 1){
			mnsum.push_back(0);
			mreminders.push_back(n);
			msizes.push_back(1);
		}
	}
}

template <typename T>
void GPUDataStream<T>::init2dsumnumbers(unsigned int d1){
	unsigned int m = Stream<T>::memsize()/sizeof(T);
	unsigned int nev = m/d1;
	unsigned int n = nev;
	unsigned int nextsize;
	unsigned int reminder;
	if(n <= 16){
		mnsum2d.push_back(0);
		mreminders2d.push_back(n);
		msizes2d.push_back(1);
	} else {
		while(n > 16){
			nextsize = n/16;
			reminder = n%16;
			mnsum2d.push_back(nextsize);
			mreminders2d.push_back(reminder);
			if(reminder)
				n = nextsize + 1;
			else
				n = nextsize;
			msizes2d.push_back(n);
		}
		if(n > 1){
			mnsum2d.push_back(0);
			mreminders2d.push_back(n);
			msizes2d.push_back(1);
		}
	}
}


template <typename T>
double GPUDataStream<T>::sum(bool keepmemory){

	if(!msizes.size()){ // the first time we do a sum, we have to calculate a few numbers...
		initsumnumbers();
	}


	// some diagnostic output
/*	for(unsigned int i = 0; i < msizes.size(); i++){
		cout << "Step " << i << " size " << msizes[i] << " msums " << mnsum[i] << " remainder " << mreminders[i] << endl;
	}*/

	// If this has not been done yet, initialize the sum streams
	if(!msumstreams.size()){
		for(unsigned int i = 0; i < msizes.size(); i++){
	//		cout << "initializing stream of size " << msizes[i] << endl;
			msumstreams.push_back(new GPUDataStream<double>(this->mdev, msizes[i]));
		}
	}
	if(mnsum[0]){
		callsumkernel(mnsum[0]);
	}
	if(mreminders[0]){
//		this->printAt(mnsum[0]*16,mreminders[0]);
		callremindersumkernel(mreminders[0],mnsum[0]*16, mnsum[0]);
	}
//	msumstreams[0]->printAt(0,msizes[0]);
//	cout << "Before first wait" << endl;
//	cout << msumstreams[0]->GetEvent().getInfo<CL_EVENT_COMMAND_EXECUTION_STATUS>() << endl;
//	msumstreams[0]->GetEvent().wait();
//	msumstreams[0]->printAt(0,msizes[0]);
	for(unsigned int i = 1; i < msizes.size(); i++){
		if(mnsum[i])
			double_sum_16(cl::NDRange(mnsum[i]), this->mdev, msumstreams[i-1],msumstreams[i]);
		if(mreminders[i])
			double_sum_N(cl::NDRange(1), this->mdev, msumstreams[i-1], mnsum[i]*16, mnsum[i], mreminders[i],msumstreams[i]);
//		cout << "Before wait" << endl;
//		cout << msumstreams[i]->GetEvent().getInfo<CL_EVENT_COMMAND_EXECUTION_STATUS>() << endl;
//		msumstreams[i]->GetEvent().wait();
//		cout << "After wait" << endl;
//		msumstreams[i]->printAt(0,msizes[i]);
	}
//	cout << "Before read" << endl;
	double sum[1];
//	cout << msumstreams[msizes.size()-1]->GetD1() << endl;
	//msumstreams[msizes.size()-1]->GetEvent().getInfo<CL_EVENT_COMMAND_EXECUTION_STATUS>();

	msumstreams[msizes.size()-1]->Read(sum);
//	cout << "Read!" << endl;
	if(!keepmemory){ // clear up...
		//for(unsigned int i = 1; i < msumstreams.size(); i++){
		// modified by fucd
		for(unsigned int i = 0; i < msumstreams.size(); i++){
			delete msumstreams[i];
		}
		msumstreams.clear();
	}
//	cout << "Cleaned up!" << endl;
	return sum[0];
}

template <typename T>
double * GPUDataStream<T>::sumcomponents(bool keepmemory){
	return sumcomponentsweighted(0, keepmemory);
}




template <typename T>
double * GPUDataStream<T>::sum2d(unsigned int d1, bool keepmemory){
	cout << "2D summing not implemented for this data type, aborting" << endl;
	assert(0);
	return 0;
}


template <typename T>
void GPUDataStream<T>::allocatesum2dspace(unsigned int d1){
	if(!msizes2d.size()){ // the first time we do a 2d sum, we have to calculate a few numbers...
		init2dsumnumbers(d1);
	}
	// If this has not been done yet, initialize the sum streams
	if(!m2dsumstreams.size()){
		for(unsigned int i = 0; i < msizes2d.size(); i++){
	//		cout << "initializing stream of size " << msizes2d[i]*d1 << " mnsum 2d : " << mnsum2d[i]*d1 << endl;
			m2dsumstreams.push_back(new GPUDataStream<double>(this->mdev, msizes2d[i]*d1));
		}
	}
}

template <>
double * GPUDataStream<float4>::sum2d(unsigned int d1, bool keepmemory){
	if(!msizes2d.size()){ // the first time we do a 2d sum, we have to calculate a few numbers...
		init2dsumnumbers(d1);
	}
	// If this has not been done yet, initialize the sum streams
	if(!m2dsumstreams.size()){
		for(unsigned int i = 0; i < msizes2d.size(); i++){
		//	cout << "initializing stream of size " << msizes2d[i]*d1 << " mnsum 2d : " << mnsum2d[i]*d1 << endl;
			m2dsumstreams.push_back(new GPUDataStream<double>(this->mdev, msizes2d[i]*d1));
		}
	}
	// some diagnostic output
//	for(unsigned int i = 0; i < msizes2d.size(); i++){
//		cout << "Step " << i << " size " << msizes2d[i] << " msums " << mnsum2d[i] << " remainder " << mreminders2d[i] << endl;
//	}
//	cout << "First step" << endl;
//	this->printAt(0,32);
	if(mnsum2d[0]){
		float4_sum2d_16(cl::NDRange(mnsum2d[0]), this->mdev, this, d1, m2dsumstreams[0]);
	}
	if(mreminders2d[0]){
		float4_sum2d_N(cl::NDRange(1), this->mdev, this, d1,  mnsum2d[0]*16*d1, mnsum2d[0]*d1, mreminders2d[0], m2dsumstreams[0]);
	}
//	cout << "Second step" << endl;
//	m2dsumstreams[0]->print();
	double * sum = new double[d1];

	for(unsigned int i = 1; i < msizes2d.size(); i++){
		if(mnsum2d[i])
			double_sum2d_16(cl::NDRange(mnsum2d[i]), this->mdev, m2dsumstreams[i-1],d1,m2dsumstreams[i]);
		if(mreminders2d[i])
			double_sum2d_N(cl::NDRange(1), this->mdev, m2dsumstreams[i-1],  d1, mnsum2d[i]*16*d1, mnsum2d[i]*d1, mreminders2d[i], m2dsumstreams[i]);
//		m2dsumstreams[i]->print();
	}

	m2dsumstreams[msizes2d.size()-1]->Read(sum);

	if(!keepmemory){ // clear up...
		for(unsigned int i = 0; i < m2dsumstreams.size(); i++){
			delete m2dsumstreams[i];
		}
		m2dsumstreams.clear();
	}
	return sum;

}

///////////////////////////////

template <>
double * GPUDataStream<float4>::sum2dweighted(GPUDataStream<float4> * weights, unsigned int d1, bool keepmemory){
	if(!msizes2d.size()){ // the first time we do a 2d sum, we have to calculate a few numbers...
		init2dsumnumbers(d1);
	}
	// If this has not been done yet, initialize the sum streams
	if(!m2dsumstreams.size()){
		for(unsigned int i = 0; i < msizes2d.size(); i++){
		//	cout << "initializing stream of size " << msizes2d[i]*d1 << " mnsum 2d : " << mnsum2d[i]*d1 << endl;
			m2dsumstreams.push_back(new GPUDataStream<double>(this->mdev, msizes2d[i]*d1));
		}
	}
	// some diagnostic output
//	for(unsigned int i = 0; i < msizes2d.size(); i++){
//		cout << "Step " << i << " size " << msizes2d[i] << " msums " << mnsum2d[i] << " remainder " << mreminders2d[i] << endl;
//	}
//	cout << "First step" << endl;
//	this->printAt(0,32);
	if(mnsum2d[0]){
		float4_sum2d_16_weighted(cl::NDRange(mnsum2d[0]), this->mdev, weights, this, d1, m2dsumstreams[0]);
	}
	if(mreminders2d[0]){
		float4_sum2d_N_weighted(cl::NDRange(1), this->mdev, weights, this, d1,  mnsum2d[0]*16*d1, mnsum2d[0]*d1, mreminders2d[0], m2dsumstreams[0]);
	}
//	cout << "Second step" << endl;
//	m2dsumstreams[0]->print();
	double * sum = new double[d1];

	for(unsigned int i = 1; i < msizes2d.size(); i++){
		if(mnsum2d[i])
			double_sum2d_16(cl::NDRange(mnsum2d[i]), this->mdev, m2dsumstreams[i-1],d1,m2dsumstreams[i]);
		if(mreminders2d[i])
			double_sum2d_N(cl::NDRange(1), this->mdev, m2dsumstreams[i-1],  d1, mnsum2d[i]*16*d1, mnsum2d[i]*d1, mreminders2d[i], m2dsumstreams[i]);
//		m2dsumstreams[i]->print();
	}

	m2dsumstreams[msizes2d.size()-1]->Read(sum);

	if(!keepmemory){ // clear up...
		for(unsigned int i = 0; i < m2dsumstreams.size(); i++){
			delete m2dsumstreams[i];
		}
		m2dsumstreams.clear();
	}
	return sum;

}


///////////////////////////////

template <typename T>
double * GPUDataStream<T>::sumcomponentsweighted(GPUDataStream<float> * weights, bool keepmemory){
	cout << "Error: Component wise summing for this type not implemented!" << endl;
	assert(0);
	return 0;
}


template <>
double * GPUDataStream<double2>::sumcomponentsweighted(GPUDataStream<float> * weights, bool keepmemory){
	if(!msizes.size()){ // the first time we do a sum, we have to calculate a few numbers...
			initsumnumbers();
		}

		// some diagnostic output
		//for(unsigned int i = 0; i < msizes.size(); i++){
		//	cout << "Step " << i << " size " << msizes[i] << " msums " << mnsum[i] << " remainder " << mreminders[i] << endl;
		//}


		// If this has not been done yet, initialize the sum streams
		if(!msumstreams.size()){
			for(unsigned int i = 0; i < msizes.size(); i++){
				msumstreams.push_back(new GPUDataStream<double>(this->mdev, msizes[i]));
			}
		}
		if(!mcompsumstreams.size()){
			mcompsumstreams.push_back(msumstreams[0]);
			mcompsumstreams.push_back(new GPUDataStream<double>(this->mdev, msizes[0]));
		}
		if(weights){
			if(mnsum[0]){
				double2_sumcomponents_weighted_16(cl::NDRange(mnsum[0]), this->mdev, this, weights, mcompsumstreams[0], mcompsumstreams[1]);
			}
			if(mreminders[0]){
				double2_sumcomponents_weighted_N(cl::NDRange(1), this->mdev, this, weights, mnsum[0]*16, mnsum[0], mreminders[0], mcompsumstreams[0], mcompsumstreams[1]);
			}
		} else {
			if(mnsum[0]){
				double2_sumcomponents_16(cl::NDRange(mnsum[0]), this->mdev, this, mcompsumstreams[0], mcompsumstreams[1]);
			}
			if(mreminders[0]){
				double2_sumcomponents_N(cl::NDRange(1), this->mdev, this, mnsum[0]*16, mnsum[0], mreminders[0], mcompsumstreams[0], mcompsumstreams[1]);
			}
		}



		double * sum = new double[2];
		GPUDataStream<double> * instream;
		for(unsigned int k =0; k < 2; k++){
			for(unsigned int i = 1; i < mreminders.size(); i++){
				if(i==1)
					instream = mcompsumstreams[k];
				else
					instream = msumstreams[i-1];
				if(mnsum[i]){
					double_sum_16(cl::NDRange(mnsum[i]), this->mdev, instream,msumstreams[i]);
				}
				if(mreminders[i]){
					double_sum_N(cl::NDRange(1), this->mdev, instream, mnsum[i]*16, mnsum[i], mreminders[i],msumstreams[i]);
				}
			}
			msumstreams[mreminders.size()-1]->Read(&(sum[k]));
		}
		if(!keepmemory){ // clear up...
			for(unsigned int i = 0; i < msumstreams.size(); i++){
				delete msumstreams[i];
			}
			msumstreams.clear();
			for(unsigned int i = 1; i < mcompsumstreams.size(); i++){
				delete mcompsumstreams[i];
			}
			mcompsumstreams.clear();
		}
		return sum;
}

template <>
double * GPUDataStream<float2>::sumcomponentsweighted(GPUDataStream<float> * weights, bool keepmemory){

	if(!msizes.size()){ // the first time we do a sum, we have to calculate a few numbers...
		initsumnumbers();
	}

	// some diagnostic output
/*	for(unsigned int i = 0; i < msizes.size(); i++){
		cout << "Step " << i << " size " << msizes[i] << " msums " << mnsum[i] << " remainder " << mreminders[i] << endl;
	}
	float2 * wurz = AllocateRead();
	for(unsigned int i=0; i < GetD1();i++)
		cout << i << ": "<< wurz[i].x <<", " << wurz[i].y << endl;
*/

	// If this has not been done yet, initialize the sum streams
	if(!msumstreams.size()){
		for(unsigned int i = 0; i < msizes.size(); i++){
			msumstreams.push_back(new GPUDataStream<double>(this->mdev, msizes[i]));
		}
	}
	if(!mcompsumstreams.size()){
		mcompsumstreams.push_back(msumstreams[0]);
		mcompsumstreams.push_back(new GPUDataStream<double>(this->mdev, msizes[0]));
	}
	//cout << "Weights " << weights << endl;
	if(weights){
		if(mnsum[0]){
			//cout << mnsum[0] << endl;
			float2_sumcomponents_weighted_16(cl::NDRange(mnsum[0]), this->mdev, this, weights, mcompsumstreams[0], mcompsumstreams[1]);
		}
		if(mreminders[0]){
			float2_sumcomponents_weighted_N(cl::NDRange(1), this->mdev, this, weights, mnsum[0]*16, mnsum[0], mreminders[0], mcompsumstreams[0], mcompsumstreams[1]);
		}
	} else {
		if(mnsum[0]){
			float2_sumcomponents_16(cl::NDRange(mnsum[0]), this->mdev, this, mcompsumstreams[0], mcompsumstreams[1]);
		}
		if(mreminders[0]){
			float2_sumcomponents_N(cl::NDRange(1), this->mdev, this, mnsum[0]*16, mnsum[0], mreminders[0], mcompsumstreams[0], mcompsumstreams[1]);
		}
	}

/*	double * x0 = new double[msizes[0]];
	double * x1 = new double[msizes[0]];

	for(unsigned int i=0; i < msizes[0];i++){
		x0[i] = -333;
		x1[i] = -555;
	}
	mcompsumstreams[0]->Read(x0);
	mcompsumstreams[1]->Read(x1);
	//double * x0 = mcompsumstreams[0]->AllocateRead();
	//double * x1 = mcompsumstreams[1]->AllocateRead();

	for(unsigned int i=0; i < msizes[0];i++)
		cout << i << ": "<< x0[i] <<", " << x1[i] << endl;
*/

	double * sum = new double[2];
	GPUDataStream<double> * instream;
	for(unsigned int k =0; k < 2; k++){
		for(unsigned int i = 1; i < mreminders.size(); i++){
			if(i==1)
				instream = mcompsumstreams[k];
			else
				instream = msumstreams[i-1];
			if(mnsum[i]){
				double_sum_16(cl::NDRange(mnsum[i]), this->mdev, instream,msumstreams[i]);
			}
			if(mreminders[i]){
				double_sum_N(cl::NDRange(1), this->mdev, instream, mnsum[i]*16, mnsum[i], mreminders[i],msumstreams[i]);
			}
		}
		msumstreams[mreminders.size()-1]->Read(&(sum[k]));
	}
	if(!keepmemory){ // clear up...
		for(unsigned int i = 0; i < msumstreams.size(); i++){
			delete msumstreams[i];
		}
		msumstreams.clear();
		for(unsigned int i = 1; i < mcompsumstreams.size(); i++){
			delete mcompsumstreams[i];
		}
		mcompsumstreams.clear();
	}
	return sum;
}

template <>
double * GPUDataStream<float4>::sumcomponentsweighted(GPUDataStream<float> * weights, bool keepmemory){

	if(!msizes.size()){ // the first time we do a sum, we have to calculate a few numbers...
			initsumnumbers();
		}

		// some diagnostic output
		//for(unsigned int i = 0; i < msizes.size(); i++){
		//	cout << "Step " << i << " size " << msizes[i] << " msums " << mnsum[i] << " remainder " << mreminders[i] << endl;
		//}


		// If this has not been done yet, initialize the sum streams
		if(!msumstreams.size()){
			for(unsigned int i = 0; i < msizes.size(); i++){
				msumstreams.push_back(new GPUDataStream<double>(this->mdev, msizes[i]));
			}
		}
		if(!mcompsumstreams.size()){
			mcompsumstreams.push_back(msumstreams[0]);
			mcompsumstreams.push_back(new GPUDataStream<double>(this->mdev, msizes[0]));
			mcompsumstreams.push_back(new GPUDataStream<double>(this->mdev, msizes[0]));
			mcompsumstreams.push_back(new GPUDataStream<double>(this->mdev, msizes[0]));
		}
		if(weights){
			if(mnsum[0]){
				float4_sumcomponents_weighted_16(cl::NDRange(mnsum[0]), this->mdev, this, weights, mcompsumstreams[0], mcompsumstreams[1],mcompsumstreams[2], mcompsumstreams[3] );
			}
			if(mreminders[0]){
				float4_sumcomponents_weighted_N(cl::NDRange(1), this->mdev, this, weights, mnsum[0]*16, mnsum[0], mreminders[0], mcompsumstreams[0], mcompsumstreams[1], mcompsumstreams[2], mcompsumstreams[3]);
			}
		} else {
			if(mnsum[0]){
				float4_sumcomponents_16(cl::NDRange(mnsum[0]), this->mdev, this, mcompsumstreams[0], mcompsumstreams[1],mcompsumstreams[2], mcompsumstreams[3] );
			}
			if(mreminders[0]){
				float4_sumcomponents_N(cl::NDRange(1), this->mdev, this, mnsum[0]*16, mnsum[0], mreminders[0], mcompsumstreams[0], mcompsumstreams[1], mcompsumstreams[2], mcompsumstreams[3]);
			}
		}



		double * sum = new double[4];
		GPUDataStream<double> * instream;
		for(unsigned int k =0; k < 4; k++){
			for(unsigned int i = 1; i < mreminders.size(); i++){
				if(i==1)
					instream = mcompsumstreams[k];
				else
					instream = msumstreams[i-1];
				if(mnsum[i]){
					double_sum_16(cl::NDRange(mnsum[i]), this->mdev, instream,msumstreams[i]);
				}
				if(mreminders[i]){
					double_sum_N(cl::NDRange(1), this->mdev, instream, mnsum[i]*16, mnsum[i], mreminders[i],msumstreams[i]);
				}
			}
			msumstreams[mreminders.size()-1]->Read(&(sum[k]));
		}
		if(!keepmemory){ // clear up...
			for(unsigned int i = 0; i < msumstreams.size(); i++){
				delete msumstreams[i];
			}
			msumstreams.clear();
			for(unsigned int i = 1; i < mcompsumstreams.size(); i++){
				delete mcompsumstreams[i];
			}
			mcompsumstreams.clear();
		}
		return sum;
}


template <>
void GPUDataStream<int>::callsumkernel(unsigned int n){
	int_sum_16(cl::NDRange(n), this->mdev, this, msumstreams[0]);
}

template <>
void GPUDataStream<float>::callsumkernel(unsigned int n){
	float_sum_16(cl::NDRange(n), this->mdev, this, msumstreams[0]);
}

template <>
void GPUDataStream<double>::callsumkernel(unsigned int n){
	double_sum_16(cl::NDRange(n), this->mdev, this, msumstreams[0]);
}

template <>
void GPUDataStream<float2>::callsumkernel(unsigned int n){
	float2_sum_16(cl::NDRange(n), this->mdev, this, msumstreams[0]);
}

template <>
void GPUDataStream<float4>::callsumkernel(unsigned int n){
	float4_sum_16(cl::NDRange(n), this->mdev, this, msumstreams[0]);
}

template <>
void GPUDataStream<double2>::callsumkernel(unsigned int n){
	double2_sum_16(cl::NDRange(n), this->mdev, this, msumstreams[0]);
}

template <>
void GPUDataStream<float44>::callsumkernel(unsigned int n){
	float44_sum_16(cl::NDRange(n), this->mdev, this, msumstreams[0]);
}

template <>
void GPUDataStream<float444>::callsumkernel(unsigned int n){
	float444_sum_16(cl::NDRange(n), this->mdev, this, msumstreams[0]);
}

/////////////////////////
template <>
void GPUDataStream<int>::callremindersumkernel(unsigned int n, unsigned int offset, unsigned int resultoffset){
	int_sum_N(cl::NDRange(1), this->mdev, this,  offset, resultoffset, n, msumstreams[0]);
}


template <>
void GPUDataStream<float>::callremindersumkernel(unsigned int n, unsigned int offset, unsigned int resultoffset){
	float_sum_N(cl::NDRange(1), this->mdev, this,  offset, resultoffset, n, msumstreams[0]);
}

template <>
void GPUDataStream<double>::callremindersumkernel(unsigned int n, unsigned int offset, unsigned int resultoffset){
	double_sum_N(cl::NDRange(1), this->mdev, this,  offset, resultoffset, n, msumstreams[0]);
}

template <>
void GPUDataStream<float2>::callremindersumkernel(unsigned int n, unsigned int offset, unsigned int resultoffset){
	float2_sum_N(cl::NDRange(1), this->mdev, this,  offset, resultoffset, n, msumstreams[0]);
}

template <>
void GPUDataStream<float4>::callremindersumkernel(unsigned int n, unsigned int offset, unsigned int resultoffset){
	float4_sum_N(cl::NDRange(1), this->mdev, this, offset, resultoffset, n, msumstreams[0]);
}

template <>
void GPUDataStream<double2>::callremindersumkernel(unsigned int n, unsigned int offset, unsigned int resultoffset){
	double2_sum_N(cl::NDRange(1), this->mdev, this, offset, resultoffset, n, msumstreams[0]);
}

template <>
void GPUDataStream<float44>::callremindersumkernel(unsigned int n, unsigned int offset, unsigned int resultoffset){
	float44_sum_N(cl::NDRange(1), this->mdev, this, offset, resultoffset, n, msumstreams[0]);
}

template <>
void GPUDataStream<float444>::callremindersumkernel(unsigned int n, unsigned int offset, unsigned int resultoffset){
	float444_sum_N(cl::NDRange(1), this->mdev, this, offset, resultoffset, n, msumstreams[0]);
}


template <typename T>
const int GPUDataStream<T>::DIMSIZE = GPUDataDependentObject::Blocksize/4;

template class GPUDataStream<int>;
template class GPUDataStream<float>;
template class GPUDataStream<float2>;
//template class GPUDataStream<float3>;
template class GPUDataStream<float4>;
//template class GPUDataStream<float16>;
template class GPUDataStream<float44>;
template class GPUDataStream<float444>;

template class GPUDataStream<double>;
template class GPUDataStream<double2>;
