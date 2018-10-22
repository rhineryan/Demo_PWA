/*
 * GPUComputedPropagator.cpp
 *
 *  Created on: Jul 13, 2009
 *      Author: nberger
 */

#include "GPUComputedPropagator.h"
#include "GPUDataDependentObject.h"

#ifdef USECPU
#include "Complex_cpu.h"
#include "Tensors_cpu.h"
#else
#include "Complex.h"
#include "Tensors.h"
#endif

#ifdef USECPU
using namespace Complex_CPU;
using namespace Tensors_CPU;
#else
using namespace Complex_GPU;
using namespace Tensors_GPU;
#endif

template <typename T, typename L, typename R, char op>
GPUComputedPropagator<T, L, R, op>::GPUComputedPropagator(GPUPartialWaveAnalysis * ana, L & _lhs, R & _rhs):
	GPUPropagatorType<T>(ana,"",std::vector<char**>(),0),lhs(_lhs), rhs(_rhs)
	{
		this->mName.clear();
		this->mparindices.clear();
		this->mparnames.clear();
		mnlhs =0;
		mnrhs = 0;
		GPUPropagator * prop1 = dynamic_cast<GPUPropagator *>(&lhs);
		if(prop1){
			mnlhs = prop1->GetNPars();
			this->mName.insert(this->mName.end(), prop1->GetNames().begin(), prop1->GetNames().end());
			this->mparindices.insert(this->mparindices.end(), prop1->GetParameters().begin(), prop1->GetParameters().end());
			this->mparnames.insert(this->mparnames.end(), prop1->GetParameterNames().begin(), prop1->GetParameterNames().end());
			for(int s=0; s < this->GetNSets(); s++){
				this->mlastvalues[s].clear();
				this->mlastvalues[s].insert(this->mlastvalues[s].end(), prop1->GetLastValues(s).begin(), prop1->GetLastValues(s).end());
			}
		}
		GPUPropagator * prop2 = dynamic_cast<GPUPropagator *>(&rhs);
		if(prop2){
			mnrhs = prop2->GetNPars();
			this->mName.insert(this->mName.end(), prop2->GetNames().begin(), prop2->GetNames().end());
			this->mparindices.insert(this->mparindices.end(), prop2->GetParameters().begin(), prop2->GetParameters().end());
			this->mparnames.insert(this->mparnames.end(), prop2->GetParameterNames().begin(), prop2->GetParameterNames().end());
			for(int s=0; s < this->GetNSets(); s++){
				if(!prop1)
					this->mlastvalues[s].clear();
				this->mlastvalues[s].insert(this->mlastvalues[s].end(), prop2->GetLastValues(s).begin(), prop2->GetLastValues(s).end());
			}

		}
		assert(mnrhs+mnlhs);
}

template <typename L, typename R, char op>
GPUComputedPropagator<float, L, R, op>::GPUComputedPropagator(GPUPartialWaveAnalysis * ana, L & _lhs, R & _rhs):
	GPUPropagatorType<float>(ana,"",std::vector<char**>(),0),lhs(_lhs), rhs(_rhs)
	{
	this->mName.clear();
		this->mparindices.clear();
		this->mparnames.clear();
		mnlhs =0;
		mnrhs = 0;
		GPUPropagator * prop1 = dynamic_cast<GPUPropagator *>(&lhs);
		if(prop1){
			/*cout << "LSIZE: " << prop1->GetParameterNames().size() << endl;
			for(unsigned int i=0; i < prop1->GetParameterNames().size(); i++){
				cout << *(prop1->GetParameterNames()[i]) << endl;
			}*/
			mnlhs = prop1->GetNPars();
			this->mName.insert(this->mName.end(), prop1->GetNames().begin(), prop1->GetNames().end());
			this->mparindices.insert(this->mparindices.end(), prop1->GetParameters().begin(), prop1->GetParameters().end());
			for(int s=0; s < this->GetNSets(); s++){
				this->mlastvalues[s].clear();
				this->mlastvalues[s].insert(this->mlastvalues[s].end(), prop1->GetLastValues(s).begin(), prop1->GetLastValues(s).end());
			}
			this->mparnames.insert(this->mparnames.end(), prop1->GetParameterNames().begin(), prop1->GetParameterNames().end());
		}
		GPUPropagator * prop2 = dynamic_cast<GPUPropagator *>(&rhs);
		if(prop2){
			/*cout << "RSIZE: " << prop2->GetParameterNames().size() << endl;
			for(unsigned int i=0; i < prop2->GetParameterNames().size(); i++){
				cout << &(prop2->GetParameterNames()[i]) << endl;
			}*/
			mnrhs = prop2->GetNPars();
			this->mName.insert(this->mName.end(), prop2->GetNames().begin(), prop2->GetNames().end());
			this->mparindices.insert(this->mparindices.end(), prop2->GetParameters().begin(), prop2->GetParameters().end());
			for(int s=0; s < this->GetNSets(); s++){
				if(!prop1)
					this->mlastvalues[s].clear();
				this->mlastvalues[s].insert(this->mlastvalues[s].end(), prop2->GetLastValues(s).begin(), prop2->GetLastValues(s).end());
			}
			this->mparnames.insert(this->mparnames.end(), prop2->GetParameterNames().begin(), prop2->GetParameterNames().end());
		}
		assert(mnrhs+mnlhs);
		/*cout << "SIZE: " << mparnames.size() << endl;
		for(unsigned int i=0; i < this->mparnames.size(); i++){
			cout << *(mparnames[i]) << endl;
		}*/
}



template <typename T, typename L, typename R, char op>
GPUComputedPropagator<T, L, R, op>::~GPUComputedPropagator() {
}

template < typename L, typename R, char op>
GPUComputedPropagator<float, L, R, op>::~GPUComputedPropagator() {
}


template <typename T,typename L, typename R, char op>
void GPUComputedPropagator<T, L, R, op>::calculate(int index, int block){
	assert(0);
	return;
}

template<typename T, typename L, typename R, char op>
void GPUComputedPropagator<T, L, R, op>::IncreaseUsecount(int index, int block) {
	assert(block < (int)this->musecount[index].size());
	if(this->musecount[index][block]  < 1){
		GPUDataDependentObject * prop1 = dynamic_cast<GPUDataDependentObject *> (&lhs);
		if(prop1)
			prop1->IncreaseUsecount(index, block);
		GPUDataDependentObject * prop2 = dynamic_cast<GPUDataDependentObject *> (&rhs);
		if(prop2)
			prop2->IncreaseUsecount(index, block);
	}
	this->musecount[index][block]++;
}


template<typename L, typename R, char op>
void GPUComputedPropagator<float, L, R, op>::IncreaseUsecount(int index, int block) {
	assert(block < (int)this->musecount[index].size());
	if(this->musecount[index][block]  < 1){
		GPUDataDependentObject * prop1 = dynamic_cast<GPUDataDependentObject *> (&lhs);
		if(prop1)
			prop1->IncreaseUsecount(index, block);
		GPUDataDependentObject * prop2 = dynamic_cast<GPUDataDependentObject *> (&rhs);
		if(prop2)
			prop2->IncreaseUsecount(index, block);
	}
	this->musecount[index][block]++;
}


template <typename T,typename L, typename R, char op>
void GPUComputedPropagator<T, L, R, op>::IncreaseUsecount(int index){
	if(this->musecount[index][0]  < 1){
		GPUDataDependentObject * prop1 = dynamic_cast<GPUDataDependentObject *> (&lhs);
		if(prop1)
			prop1->IncreaseUsecount(index);
		GPUDataDependentObject * prop2 = dynamic_cast<GPUDataDependentObject *> (&rhs);
		if(prop2)
			prop2->IncreaseUsecount(index);
	}
	for(unsigned int i =0; i < this->musecount[index].size(); i++){
		this->musecount[index][i]++;
	}
}

template <typename L, typename R, char op>
void GPUComputedPropagator<float, L, R, op>::IncreaseUsecount(int index){
	if(this->musecount[index][0]  < 1){
		GPUDataDependentObject * prop1 = dynamic_cast<GPUDataDependentObject *> (&lhs);
		if(prop1)
			prop1->IncreaseUsecount(index);
		GPUDataDependentObject * prop2 = dynamic_cast<GPUDataDependentObject *> (&rhs);
		if(prop2)
			prop2->IncreaseUsecount(index);
	}
	for(unsigned int i =0; i < this->musecount[index].size(); i++){
		this->musecount[index][i]++;
	}

}


// multiply two complex values
template <>
GPUDataStream<float2> * GPUComputedPropagator<float, GPUScalarPropagator, GPUScalarPropagator,'*'>::operator()(int index, int block){
	if(this->CacheValid(index))
		if(this->mstream[index][block])
			return this->mstream[index][block];

	//if(this->mstream[index][block])
	//	delete this->mstream[index][block];
	InvalidateCache(index);
	Stream<float2> * lstream = this->lhs(index,block);
	Stream<float2> * rstream = this->rhs(index,block);

	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));

	this->mstream[index][block] = new GPUDataStream<float2>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kernelmultiplycomplex(mList->GetDeviceInterface(),lstream, rstream, this->mstream[index][block]);

	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);

	this->ValidateCache(index);
	return this->mstream[index][block];

}



// Add two complex values
template <>
GPUDataStream<float2> * GPUComputedPropagator<float, GPUScalarPropagator, GPUScalarPropagator,'+'>::operator()(int index, int block){

	if(this->CacheValid(index))
		if(this->mstream[index][block])
			return this->mstream[index][block];

	InvalidateCache(index);

	Stream<float2> * lstream = this->lhs(index,block);
	Stream<float2> * rstream = this->rhs(index,block);

	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));

	this->mstream[index][block] = new GPUDataStream<float2>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneladdcomplex(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);

	//this->mlength[index][block] = this->lhs.GetLength(index,block);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);

	this->ValidateCache(index);
	return this->mstream[index][block];

}


// Multiply a complex and a scalar stream
template <>
GPUDataStream<float2> * GPUComputedPropagator<float, GPUScalarPropagator, GPUStreamScalar,'*'>::operator()(int index, int block){
	if(this->CacheValid(index))
		if(this->mstream[index][block])
			return this->mstream[index][block];

	//if(this->mstream[index][block])
	//	delete this->mstream[index][block];
	InvalidateCache(index);

	Stream<float2> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs(index,block);

	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));

	this->mstream[index][block] = new GPUDataStream<float2>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kernelmultiplycomplexf(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);

	//this->mlength[index][block] = this->lhs.GetLength(index,block);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);

	this->ValidateCache(index);
	return this->mstream[index][block];

}

// Add two complex tensor2s
template <>
void GPUComputedPropagator<float44, GPUTensor2Propagator, GPUTensor2Propagator,'+'>::calculate(int index, int block){
	//cout << "Calculating sum " << endl;

	Stream<float44> * lstream = this->lhs.realpart(index,block);
	Stream<float44> * rstream = this->rhs.realpart(index,block);

	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));

	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensoradd_2_2(mList->GetDeviceInterface(),lstream, rstream, this->mstream[index][block]);

	Stream<float44> * listream = this->lhs.imagpart(index,block);
	Stream<float44> * ristream = this->rhs.imagpart(index,block);
	this->mImagstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensoradd_2_2(mList->GetDeviceInterface(),listream, ristream, this->mImagstream[index][block]);

	//this->mlength[index][block] = this->lhs.GetLength(index,block);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);

	this->ValidateCache(index);
}

// Subtract two complex tensor2s
template <>
void GPUComputedPropagator<float44, GPUTensor2Propagator, GPUTensor2Propagator,'-'>::calculate(int index, int block){

	Stream<float44> * lstream = this->lhs.realpart(index,block);
	Stream<float44> * rstream = this->rhs.realpart(index,block);

	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));

	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorsub_2_2(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);

	Stream<float44> * listream = this->lhs.imagpart(index,block);
	Stream<float44> * ristream = this->rhs.imagpart(index,block);
	this->mImagstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorsub_2_2(mList->GetDeviceInterface(), listream, ristream, this->mImagstream[index][block]);

	//this->mlength[index][block] = this->lhs.GetLength(index,block);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);

	this->ValidateCache(index);


}

// Multiply a tensor2 and a scalar propagator
template <>
void GPUComputedPropagator<float44, GPUScalarPropagator, GPUStreamTensor2,'*'>::calculate(int index, int block){
	//cout <<"Multiplying Tensor2 and Propagator" << endl;

	Stream<float> * lrealstream = this->lhs.realpart(index,block);
	Stream<float> * limagstream = this->lhs.imagpart(index,block);
/*	cout << "LHS real" << endl;
	printStream(lrealstream, this->lhs.GetLength(index,block));
	cout << "LHS imag" << endl;
	printStream(limagstream, this->rhs.GetLength(index,block));*/
	Stream<float44> * rstream = this->rhs(index,block);
/*	cout << "RHS" << endl;
	print44Stream(rstream, this->rhs.GetLength(index,block));*/

	//assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));

	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_0_2(mList->GetDeviceInterface(), lrealstream, rstream, this->mstream[index][block]);

	this->mImagstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_0_2(mList->GetDeviceInterface(),limagstream, rstream, this->mImagstream[index][block]);

	//this->mlength[index][block] = this->lhs.GetLength(index,block);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);

	this->ValidateCache(index);

}

// Multiply a tensor2 propagator and a scalar propagator
template <>
void GPUComputedPropagator<float44, GPUScalarPropagator, GPUTensor2Propagator,'*'>::calculate(int index, int block){

	Stream<float> * lrealstream = this->lhs.realpart(index,block);
	Stream<float> * limagstream = this->lhs.imagpart(index,block);

	Stream<float44> * rrealstream = this->rhs.realpart(index,block);
	Stream<float44> * rimagstream = this->rhs.imagpart(index,block);


	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	this->mImagstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_c_c44(mList->GetDeviceInterface(), lrealstream, limagstream, rrealstream, rimagstream, this->mstream[index][block], this->mImagstream[index][block]);

	//this->mlength[index][block] = this->lhs.GetLength(index,block);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);

	this->ValidateCache(index);

}

// Contract a tensor3 and a tensor 2 propagator
template <>
void GPUComputedPropagator<float4, GPUTensor2Propagator,GPUStreamTensor3,'|'>::calculate(int index, int block){

	Stream<float44> * lrealstream = this->lhs.realpart(index,block);
	Stream<float44> * limagstream = this->lhs.imagpart(index,block);
	Stream<float444> * rstream = this->rhs(index,block);

	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));

	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_3_2(mList->GetDeviceInterface(), rstream, lrealstream, this->mstream[index][block]);

	this->mImagstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_3_2(mList->GetDeviceInterface(), rstream, limagstream, this->mImagstream[index][block]);

	//this->mlength[index][block] = this->lhs.GetLength(index,block);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);

	this->ValidateCache(index);
}

// Contract a tensor3 and a tensor 2 propagator
template <>
void GPUComputedPropagator<float44, GPUVectorPropagator,GPUStreamTensor3,'|'>::calculate(int index, int block){

	Stream<float4> * lrealstream = this->lhs.realpart(index,block);
	Stream<float4> * limagstream = this->lhs.imagpart(index,block);
	Stream<float444> * rstream = this->rhs(index,block);

	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));

	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_3_1(mList->GetDeviceInterface(), rstream, lrealstream, this->mstream[index][block]);

	this->mImagstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_3_1(mList->GetDeviceInterface(), rstream, limagstream, this->mImagstream[index][block]);

	//this->mlength[index][block] = this->lhs.GetLength(index,block);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);

	this->ValidateCache(index);

}

//Contract a rank 4 tensor and a complex rank 2 tensor
template <>
void GPUComputedPropagator<float44,  GPUTensor2Propagator, GPUStreamTensor4,'|'>::calculate(int index, int block){

	Stream<float44> * lrealstream = this->lhs.realpart(index,block);
	Stream<float44> * limagstream = this->lhs.imagpart(index,block);
	GPUDataStream<float44> * rstream = this->rhs(index,block);

	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));


	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	this->mImagstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	GPUDataStream<float> * temp[16];
	for(int i=0; i<16; i++){
		temp[i] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
		kerneltensorcontract_2_2(mList->GetDeviceInterface(), (*rstream)(i), lrealstream, (temp[i]));
	}
	kerneltensormake_2(mList->GetDeviceInterface(), (temp[0]), (temp[1]), (temp[2]), (temp[3]),
				   (temp[4]), (temp[5]), (temp[6]), (temp[7]),
				   (temp[8]), (temp[9]), (temp[10]), (temp[11]),
				   (temp[12]), (temp[13]), (temp[14]), (temp[15]), this->mstream[index][block]);

	for(int i=0; i<16; i++){
		temp[i] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
		kerneltensorcontract_2_2(mList->GetDeviceInterface(), (*rstream)(i), limagstream, (temp[i]));
	}
	kerneltensormake_2(mList->GetDeviceInterface(), (temp[0]), (temp[1]), (temp[2]), (temp[3]),
					   (temp[4]), (temp[5]), (temp[6]), (temp[7]),
					   (temp[8]), (temp[9]), (temp[10]), (temp[11]),
					   (temp[12]), (temp[13]), (temp[14]), (temp[15]), this->mImagstream[index][block]);


	for(int i=0; i<16; i++){
		delete temp[i];
	}

	//this->mlength[index][block] = this->lhs.GetLength(index,block);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);

	this->ValidateCache(index);

}


// Multiply a complex vector and a complex scalar
template <>
void GPUComputedPropagator<float4, GPUVectorPropagator, GPUScalarPropagator,'*'>::calculate(int index, int block){

	Stream<float4> * lstream = this->lhs.realpart(index,block);
	Stream<float> * rstream = this->rhs.realpart(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));

	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));

	Stream<float4> * listream = this->lhs.imagpart(index,block);
	Stream<float> * ristream = this->rhs.imagpart(index,block);
	this->mImagstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_c4_c(mList->GetDeviceInterface(), lstream, listream, rstream, ristream, this->mstream[index][block], this->mImagstream[index][block]);

	//this->mlength[index][block] = this->lhs.GetLength(index,block);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);

	this->ValidateCache(index);
}

// Multiply a stream vector and a complex scalar
template <>
void GPUComputedPropagator<float4, GPUStreamVector, GPUScalarPropagator,'*'>::calculate(int index, int block){


	Stream<float4> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs.realpart(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));

	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));

	Stream<float> * ristream = this->rhs.imagpart(index,block);
	this->mImagstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_4_c(mList->GetDeviceInterface(), lstream, rstream, ristream, this->mstream[index][block], this->mImagstream[index][block]);

	//this->mlength[index][block] = this->lhs.GetLength(index,block);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);

	this->ValidateCache(index);
}

// Add two complex vectors
template <>
void GPUComputedPropagator<float4, GPUVectorPropagator, GPUVectorPropagator,'+'>::calculate(int index, int block){

	Stream<float4> * lstream = this->lhs.realpart(index,block);
	Stream<float4> * rstream = this->rhs.realpart(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensoradd_1_1(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block] );


	Stream<float4> * listream = this->lhs.imagpart(index,block);
	Stream<float4> * ristream = this->rhs.imagpart(index,block);
	this->mImagstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensoradd_1_1(mList->GetDeviceInterface(),listream, ristream, this->mImagstream[index][block]);

	//this->mlength[index][block] = this->lhs.GetLength(index,block);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);

	this->ValidateCache(index);

}

// Subtract two complex vectors
template <>
void GPUComputedPropagator<float4, GPUVectorPropagator, GPUVectorPropagator,'-'>::calculate(int index, int block){

	Stream<float4> * lstream = this->lhs.realpart(index,block);
	Stream<float4> * rstream = this->rhs.realpart(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorsub_1_1(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block] );


	Stream<float4> * listream = this->lhs.imagpart(index,block);
	Stream<float4> * ristream = this->rhs.imagpart(index,block);
	this->mImagstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorsub_1_1(mList->GetDeviceInterface(), listream, ristream, this->mImagstream[index][block]);

	//this->mlength[index][block] = this->lhs.GetLength(index,block);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);

	this->ValidateCache(index);
}



GPUScalarPropagator & operator+  (GPUScalarPropagator & _lhs, GPUScalarPropagator & _rhs){
	return * new GPUComputedPropagator<float, GPUScalarPropagator, GPUScalarPropagator,'+'>(_lhs.GetAnalysis(), _lhs, _rhs);
}
GPUScalarPropagator & operator*  (GPUScalarPropagator & _lhs, GPUScalarPropagator & _rhs){
	return * new GPUComputedPropagator<float, GPUScalarPropagator, GPUScalarPropagator,'*'>(_lhs.GetAnalysis(), _lhs, _rhs);
}
GPUScalarPropagator & operator*  (GPUStreamScalar & _lhs, GPUScalarPropagator & _rhs){
	return * new GPUComputedPropagator<float, GPUScalarPropagator, GPUStreamScalar,'*'>(_rhs.GetAnalysis(), _rhs, _lhs);
}
GPUScalarPropagator & operator*  (GPUScalarPropagator & _lhs, GPUStreamScalar & _rhs){
	return * new GPUComputedPropagator<float, GPUScalarPropagator, GPUStreamScalar,'*'>(_lhs.GetAnalysis(), _lhs, _rhs);
}

GPUTensor2Propagator & operator* (GPUScalarPropagator & _lhs, GPUStreamTensor2 & _rhs){
	return * new GPUComputedPropagator<float44, GPUScalarPropagator, GPUStreamTensor2,'*'>(_lhs.GetAnalysis(), _lhs, _rhs);
}

GPUTensor2Propagator & operator* (GPUStreamTensor2 & _lhs, GPUScalarPropagator & _rhs){
	return * new GPUComputedPropagator<float44, GPUScalarPropagator, GPUStreamTensor2,'*'>(_rhs.GetAnalysis(), _rhs, _lhs);
}

GPUTensor2Propagator & operator* (GPUScalarPropagator & _lhs, GPUTensor2Propagator & _rhs){
	return * new GPUComputedPropagator<float44, GPUScalarPropagator, GPUTensor2Propagator,'*'>(_lhs.GetAnalysis(), _lhs, _rhs);
}

GPUTensor2Propagator & operator* (GPUTensor2Propagator & _lhs, GPUScalarPropagator & _rhs){
	return * new GPUComputedPropagator<float44, GPUScalarPropagator, GPUTensor2Propagator,'*'>(_lhs.GetAnalysis(), _rhs, _lhs);
}

GPUTensor2Propagator & operator+ (GPUTensor2Propagator & _lhs, GPUTensor2Propagator & _rhs){
	return * new GPUComputedPropagator<float44, GPUTensor2Propagator, GPUTensor2Propagator,'+'>(_lhs.GetAnalysis(), _lhs, _rhs);
}

GPUTensor2Propagator & operator- (GPUTensor2Propagator & _lhs, GPUTensor2Propagator & _rhs){
	return * new GPUComputedPropagator<float44, GPUTensor2Propagator, GPUTensor2Propagator,'-'>(_lhs.GetAnalysis(), _lhs, _rhs);
}

GPUVectorPropagator & operator+ (GPUVectorPropagator & _lhs, GPUVectorPropagator & _rhs){
	return * new GPUComputedPropagator<float4, GPUVectorPropagator, GPUVectorPropagator,'+'>(_lhs.GetAnalysis(), _lhs, _rhs);
}

GPUVectorPropagator & operator- (GPUVectorPropagator & _lhs, GPUVectorPropagator & _rhs){
	return * new GPUComputedPropagator<float4, GPUVectorPropagator, GPUVectorPropagator,'-'>(_lhs.GetAnalysis(), _lhs, _rhs);
}

GPUVectorPropagator & operator| (GPUStreamTensor3 & _lhs, GPUTensor2Propagator & _rhs){
	return * new GPUComputedPropagator<float4, GPUTensor2Propagator, GPUStreamTensor3, '|'>(_rhs.GetAnalysis(), _rhs, _lhs);
}

GPUVectorPropagator & operator| (GPUTensor2Propagator & _lhs, GPUStreamTensor3 & _rhs){
	return * new GPUComputedPropagator<float4, GPUTensor2Propagator, GPUStreamTensor3, '|'>(_lhs.GetAnalysis(), _lhs, _rhs);
}

GPUTensor2Propagator & operator| (GPUStreamTensor3 & _lhs, GPUVectorPropagator & _rhs){
	return * new GPUComputedPropagator<float44, GPUVectorPropagator, GPUStreamTensor3, '|'>(_rhs.GetAnalysis(), _rhs, _lhs);
}

GPUTensor2Propagator & operator| (GPUVectorPropagator & _lhs, GPUStreamTensor3 & _rhs){
	return * new GPUComputedPropagator<float44, GPUVectorPropagator, GPUStreamTensor3, '|'>(_lhs.GetAnalysis(), _lhs, _rhs);
}

GPUTensor2Propagator & operator| (GPUStreamTensor4 & _lhs, GPUTensor2Propagator & _rhs){
	return * new GPUComputedPropagator<float44, GPUTensor2Propagator, GPUStreamTensor4, '|'>(_rhs.GetAnalysis(), _rhs, _lhs);
}

GPUTensor2Propagator & operator| (GPUTensor2Propagator & _lhs, GPUStreamTensor4 & _rhs){
	return * new GPUComputedPropagator<float44, GPUTensor2Propagator,  GPUStreamTensor4,'|'>(_lhs.GetAnalysis(), _lhs, _rhs);
}

GPUVectorPropagator & operator* (GPUVectorPropagator & _lhs, GPUScalarPropagator & _rhs){
	return * new GPUComputedPropagator<float4, GPUVectorPropagator, GPUScalarPropagator, '*'>(_lhs.GetAnalysis(), _lhs, _rhs);
}

GPUVectorPropagator & operator* (GPUScalarPropagator & _lhs, GPUVectorPropagator & _rhs){
	return * new GPUComputedPropagator<float4, GPUVectorPropagator, GPUScalarPropagator, '*'>(_lhs.GetAnalysis(), _rhs, _lhs);
}

GPUVectorPropagator & operator* (GPUStreamVector & _lhs, GPUScalarPropagator & _rhs){
	return * new GPUComputedPropagator<float4, GPUStreamVector, GPUScalarPropagator, '*'>(_rhs.GetAnalysis(), _lhs, _rhs);
}

GPUVectorPropagator & operator* (GPUScalarPropagator & _lhs, GPUStreamVector & _rhs){
	return * new GPUComputedPropagator<float4, GPUStreamVector, GPUScalarPropagator, '*'>(_lhs.GetAnalysis(), _rhs, _lhs);
}

template class GPUComputedPropagator<float, GPUScalarPropagator, GPUStreamScalar, '*'>;


