#include "GPUComputedTensor.h"
#include <iostream>
#include "GPUDataStream.h"
#ifdef USECPU
#include "Orbitals_cpu.h"
#include "Tensors_cpu.h"
#else
#include "Orbitals.h"
#include "Tensors.h"
#endif

#ifdef USECPU
using namespace Orbitals_CPU;
using namespace Tensors_CPU;
#else
using namespace Orbitals_GPU;
using namespace Tensors_GPU;
#endif

template<typename tt, typename T, typename L, typename R, int oper, bool regL, bool regR>
void GPUTwoStreamOpBase<tt,T,L,R,oper, regL, regR>::assertindex(int index){
	// Two const objects, there should be no index dependence
	//assert(1);
}

template<typename tt, typename T, typename L, typename R, int oper>
void GPUTwoStreamOpBase<tt, T,L,R,oper, true, true>::assertindex(int index){
	assert(index < this->GetNSets());
}

template<typename tt, typename T, typename L, typename R, int oper>
void GPUTwoStreamOpBase<tt,T,L,R,oper, true, false>::assertindex(int index){
	assert(index < this->GetNSets());
	}

template<typename tt, typename T, typename L, typename R, int oper>
void GPUTwoStreamOpBase<tt, T,L,R,oper, false, true>::assertindex(int index){
	assert(index < this->GetNSets());
	}

template<typename tt, typename T, typename L, typename R, int oper, bool regL, bool regR>
void GPUTwoStreamOpBase<tt,T,L,R,oper, regL, regR>::IncreaseUsecount(int index){
	cout << "Hmm?" << endl;
}

template<typename tt, typename T, typename L, typename R, int oper>
void GPUTwoStreamOpBase<tt, T,L,R,oper, true, true>::IncreaseUsecount(int index){
	if(this->musecount[index][0]  < 1){
		this->lhs.IncreaseUsecount(index);
		this->rhs.IncreaseUsecount(index);
	}
	for(unsigned int i =0; i < this->musecount[index].size(); i++){
		this->musecount[index][i]++;
	}
	//cout << this << " TwoOpLRIncreasing usecount[" << index << "] "<< this->musecount[index][0] << endl;
}

template<typename tt, typename T, typename L, typename R, int oper>
void GPUTwoStreamOpBase<tt,T,L,R,oper, true, false>::IncreaseUsecount(int index){
	if(this->musecount[index][0]  < 1){
		this->lhs.IncreaseUsecount(index);
	}
	for(unsigned int i =0; i < this->musecount[index].size(); i++){
		this->musecount[index][i]++;
	}
	//cout << this << " TwoOpLIncreasing usecount[" << index << "] "<< this->musecount[index][0] << endl;
}

template<typename tt, typename T, typename L, typename R, int oper>
void GPUTwoStreamOpBase<tt, T,L,R,oper, false, true>::IncreaseUsecount(int index){
	if(this->musecount[index][0]  < 1){
		this->rhs.IncreaseUsecount(index);
	}
	for(unsigned int i =0; i < this->musecount[index].size(); i++){
		this->musecount[index][i]++;
	}
	//cout << this << " TwoOpRIncreasing usecount[" << index << "] "<< this->musecount[index][0] << endl;
}





template<typename tt, typename T, typename L, typename R, int oper, bool regL, bool regR>
void GPUTwoStreamOpBase<tt,T,L,R,oper, regL, regR>::IncreaseUsecount(int index, int block){
	cout << "Hmm?" << endl;
}

template<typename tt, typename T, typename L, typename R, int oper>
void GPUTwoStreamOpBase<tt, T,L,R,oper, true, true>::IncreaseUsecount(int index, int block){
	assert(block < (int)this->musecount[index].size());
	if(this->musecount[index][block]  < 1){
		this->lhs.IncreaseUsecount(index, block);
		this->rhs.IncreaseUsecount(index, block);
	}
	this->musecount[index][block]++;
	//cout << this << " TwoOpLRIncreasing usecount[" << index << "] "<< this->musecount[index][0] << endl;
}

template<typename tt, typename T, typename L, typename R, int oper>
void GPUTwoStreamOpBase<tt,T,L,R,oper, true, false>::IncreaseUsecount(int index, int block){
	assert(block < (int)this->musecount[index].size());
	if(this->musecount[index][block]  < 1){
		this->lhs.IncreaseUsecount(index,block);
	}
	this->musecount[index][block]++;
	//cout << this << " TwoOpLIncreasing usecount[" << index << "] "<< this->musecount[index][0] << endl;
}

template<typename tt, typename T, typename L, typename R, int oper>
void GPUTwoStreamOpBase<tt, T,L,R,oper, false, true>::IncreaseUsecount(int index, int block){
	assert(block < (int)this->musecount[index].size());
	if(this->musecount[index][block]  < 1){
		this->rhs.IncreaseUsecount(index,block);
	}
		this->musecount[index][block]++;
	//cout << this << " TwoOpRIncreasing usecount[" << index << "] "<< this->musecount[index][0] << endl;
}


template<typename tt, typename T, typename L, typename R, int oper>
GPUTwoStreamOpBase<tt, T, L, R, oper, true, false>::GPUTwoStreamOpBase(L  _lhs, R  _rhs):T(_lhs.GetList()),lhs(_lhs),rhs(_rhs),op(oper){
	assert(! this->mstream[0][0]);
	}


template<typename tt, typename T, typename L, typename R, int oper>
GPUTwoStreamOpBase<tt, T, L, R, oper, false, true>::GPUTwoStreamOpBase(L  _lhs, R  _rhs):T(_rhs.GetList()),lhs(_lhs),rhs(_rhs),op(oper){
	assert(! this->mstream[0][0]);
	}

template<typename tt, typename T, typename L, typename R, int oper>
GPUTwoStreamOpBase<tt,T, L, R, oper, true, true>::GPUTwoStreamOpBase(L  _lhs, R  _rhs):T(_lhs.GetList()),lhs(_lhs),rhs(_rhs),op(oper){
		if(this->lhs.GetList() != this->rhs.GetList()){
			// Two lists, register to both
			this->rhs.GetList()->Register(this);
		}
		assert(! this->mstream[0][0]);
	}


/// Add two scalars
GPUStreamScalar & operator+  (GPUStreamScalar & _lhs, GPUStreamScalar & _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,GPUStreamScalar &,'+',true,true>(_lhs,_rhs);
}
/// Add a scalar and a float
GPUStreamScalar & operator+  (GPUStreamScalar & _lhs, float _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'+',true,false>(_lhs,_rhs);
}
GPUStreamScalar & operator+  (float _lhs, GPUStreamScalar&  _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'+',true,false>(_rhs,_lhs);
}
GPUStreamScalar & operator+  (GPUStreamScalar & _lhs, GPUConstScalar & _rhs){
	float temp = _rhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'+',true,false>(_lhs,temp);
}
GPUStreamScalar & operator+  (GPUConstScalar & _lhs, GPUStreamScalar & _rhs){
	float temp  = _lhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'+',true,false>(_rhs,temp);
}


//---lorentz boost and rotation
GPUStreamVector & lorentzboost  (GPUStreamVector & _lhs, GPUStreamVector & _rhs){

	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,GPUStreamVector &,'B',true,true>(_lhs,_rhs);
}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,GPUStreamVector &,'B',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	assert(this->lhs.Rank() == this->rhs.Rank());
	Stream<float4> * lstream = this->lhs(index,block);
	Stream<float4> * rstream = this->rhs(index,block);

	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// boost
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(),this->lhs.GetLength(index,block));
	kernellorentzboost(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

GPUStreamVector & lorentzrotation  (GPUStreamVector & _lhs, GPUStreamVector & _rhs){

	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,GPUStreamVector &,'R',true,true>(_lhs,_rhs);
}



template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,GPUStreamVector &,'R',true,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];

	assert(this->lhs.Rank() == this->rhs.Rank());
	Stream<float4> * lstream = this->lhs(index,block);
	Stream<float4> * rstream = this->rhs(index,block);

	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// rotation
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kernellorentzrotation(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

/// Cosine of a vector
GPUStreamScalar & costheta(GPUStreamVector & _lhs){
	return * new GPUOneStreamOp<float, GPUStreamScalar,'h',GPUStreamVector ,true>(_lhs);
}
template<> GPUDataStream<float> * GPUOneStreamOp<float, GPUStreamScalar,'h',GPUStreamVector, true >::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	// Cosine of a stream of floats
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcostheta_1(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}
/// phi of a vector
GPUStreamScalar & phi(GPUStreamVector & _lhs){
	return * new GPUOneStreamOp<float, GPUStreamScalar,'p',GPUStreamVector ,true>(_lhs);
}
template<> GPUDataStream<float> * GPUOneStreamOp<float, GPUStreamScalar,'p',GPUStreamVector,true >::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	// Cosine of a stream of floats
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorphi_1(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


/// Add two vectors
GPUStreamVector & operator+  (GPUStreamVector & _lhs, GPUStreamVector & _rhs){

	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,GPUStreamVector &,'+',true,true>(_lhs,_rhs);
}
/// Add a vector and a float4
GPUStreamVector & operator+  (GPUStreamVector & _lhs, float4 _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,float4,'+',true,false>(_lhs,_rhs);
}
GPUStreamVector & operator+  (float4 _lhs, GPUStreamVector & _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,float4,'+',true,false>(_rhs,_lhs);
}
GPUStreamVector & operator+  (GPUStreamVector & _lhs, GPUConstVector & _rhs){
	float4 temp  = _rhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,float4,'+',true,false>(_lhs,temp);
}
GPUStreamVector & operator+  (GPUConstVector & _lhs, GPUStreamVector & _rhs){
	float4 temp  = _lhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,float4,'+',true,false>(_rhs,temp);
}

/// Add two second rank tensors
GPUStreamTensor2 & operator+  (GPUStreamTensor2 & _lhs, GPUStreamTensor2 & _rhs){

	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,GPUStreamTensor2 &,'+',true,true>(_lhs,_rhs );
}

/// Add a tensor 2 and a float44
GPUStreamTensor2 & operator+  (GPUStreamTensor2 & _lhs, float44 _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,float44,'+',true,false>(_lhs,_rhs);
}
GPUStreamTensor2 & operator+  (float44 _lhs, GPUStreamTensor2 & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,float44,'+',true,false>(_rhs,_lhs);
}
GPUStreamTensor2 & operator+  (GPUStreamTensor2 & _lhs, GPUConstTensor2 & _rhs){
	float44 temp  = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,float44,'+',true,false>(_lhs,temp);
}
GPUStreamTensor2 & operator+  (GPUConstTensor2 & _lhs, GPUStreamTensor2 & _rhs){
	float44 temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,float44,'+',true,false>(_rhs,temp);
}

/// Add two third rank tensors
GPUStreamTensor3 & operator+  (GPUStreamTensor3 & _lhs, GPUStreamTensor3 & _rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,GPUStreamTensor3 &,'+',true,true>(_lhs,_rhs );
}

/// Add a tensor 3 and a float444
GPUStreamTensor3 & operator+  (GPUStreamTensor3 & _lhs, float444 _rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,float444,'+',true,false>(_lhs,_rhs);
}
GPUStreamTensor3 & operator+  (float444 _lhs, GPUStreamTensor3 & _rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,float444,'+',true,false>(_rhs,_lhs);
}
GPUStreamTensor3 & operator+  (GPUStreamTensor3 & _lhs, GPUConstTensor3 & _rhs){
	float444 temp  = _rhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,float444,'+',true,false>(_lhs,temp);
}
GPUStreamTensor3 & operator+  (GPUConstTensor3 & _lhs, GPUStreamTensor3 & _rhs){
	float444 temp  = _lhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,float444,'+',true,false>(_rhs,temp);
}


/// Add a tensor 4 and a float4444
GPUStreamTensor4 & operator+  (GPUStreamTensor4 & _lhs, float4444 _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,float4444,'+',true,false>(_lhs,_rhs);
}
GPUStreamTensor4 & operator+  (float4444 _lhs, GPUStreamTensor4 & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,float4444,'+',true,false>(_rhs,_lhs);
}
GPUStreamTensor4 & operator+  (GPUStreamTensor4 & _lhs, GPUConstTensor4 & _rhs){
	float4444 temp  = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,float4444,'+',true,false>(_lhs,temp);
}
GPUStreamTensor4 & operator+  (GPUConstTensor4 & _lhs, GPUStreamTensor4 & _rhs){
	float4444 temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,float4444,'+',true,false>(_rhs,temp);
}

GPUStreamTensor4 & operator+  (GPUStreamTensor4 & _lhs, GPUStreamTensor4 & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,GPUStreamTensor4 &,'+',true,true>(_lhs,_rhs);
}



/// Subtract two scalars
GPUStreamScalar & operator-  (GPUStreamScalar & _lhs, GPUStreamScalar & _rhs){

	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,GPUStreamScalar &,'-',true,true>(_lhs,_rhs);
}
/// Subtract a scalar and a float
GPUStreamScalar & operator-  (GPUStreamScalar & _lhs, float _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'-',true,false>(_lhs,_rhs);
}
GPUStreamScalar & operator-  (float _lhs, GPUStreamScalar & _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,float,GPUStreamScalar &,'-',false,true>(_lhs,_rhs);
}
GPUStreamScalar & operator-  (GPUStreamScalar & _lhs, GPUConstScalar & _rhs){
	float temp  = _rhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'-',true,false>(_lhs,temp);
}
GPUStreamScalar & operator-  (GPUConstScalar & _lhs, GPUStreamScalar & _rhs){
	float temp  = _lhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,float,GPUStreamScalar &,'-',false,true>(temp,_rhs);
}


/// Subtract two vectors
GPUStreamVector & operator-  (GPUStreamVector & _lhs, GPUStreamVector & _rhs){

	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,GPUStreamVector &,'-',true,true>(_lhs,_rhs);
}
/// Subtract a vector and a float4
GPUStreamVector & operator-  (GPUStreamVector & _lhs, float4 _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,float4,'-',true,false>(_lhs,_rhs);
}
GPUStreamVector & operator-  (float4 _lhs, GPUStreamVector & _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,float4,GPUStreamVector &,'-',false,true>(_lhs,_rhs);
}
GPUStreamVector & operator-  (GPUStreamVector & _lhs, GPUConstVector & _rhs){
	float4 temp  = _rhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,float4,'-',true,false>(_lhs,temp);
}
 GPUStreamVector & operator-  (GPUConstVector & _lhs, GPUStreamVector & _rhs){
	// std::cout<<" in GPUStreamVector & operator-  (GPUConstVector & _lhs, GPUStreamVector & _rhs) : "<<std::endl;
	float4 temp  =  _lhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,float4,GPUStreamVector &,'-',false,true>(temp,_rhs);
}




/// Subtract two second rank tensors
GPUStreamTensor2 & operator-  (GPUStreamTensor2 & _lhs, GPUStreamTensor2 & _rhs){

	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,GPUStreamTensor2 &,'-',true,true>(_lhs,_rhs);
}
/// Subtract a second rank tensor and a float44
GPUStreamTensor2 & operator-  (GPUStreamTensor2 & _lhs, float44 _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,float44,'-',true,false>(_lhs,_rhs);
}
GPUStreamTensor2 & operator-  (float44 _lhs, GPUStreamTensor2 & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,float44,GPUStreamTensor2 &,'-',false,true>(_lhs,_rhs);
}
GPUStreamTensor2 & operator-  (GPUStreamTensor2 & _lhs, GPUConstTensor2 & _rhs){
	float44 temp  = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,float44,'-',true,false>(_lhs,temp);
}
GPUStreamTensor2 & operator-  (GPUConstTensor2 & _lhs, GPUStreamTensor2 & _rhs){
	float44 temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,float44,GPUStreamTensor2 &,'-',false,true>(temp,_rhs);
}


/// Subtract two third rank tensors
GPUStreamTensor3 & operator-  (GPUStreamTensor3 & _lhs, GPUStreamTensor3 & _rhs){

	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,GPUStreamTensor3 &,'-',true,true>(_lhs,_rhs);
}
/// Subtract a thiord rank tensor and a float444
GPUStreamTensor3 & operator-  (GPUStreamTensor3 & _lhs, float444 _rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,float444,'-',true,false>(_lhs,_rhs);
}
GPUStreamTensor3 & operator-  (float444 _lhs, GPUStreamTensor3 & _rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,float444,GPUStreamTensor3 &,'-',false,true>(_lhs,_rhs);
}
GPUStreamTensor3 & operator-  (GPUStreamTensor3 & _lhs, GPUConstTensor3 & _rhs){
	float444 temp  = _rhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,float444,'-',true,false>(_lhs,temp);
}
GPUStreamTensor3 & operator-  (GPUConstTensor3 & _lhs, GPUStreamTensor3 & _rhs){
	float444 temp  = _lhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,float444,GPUStreamTensor3 &,'-',false,true>(temp,_rhs);
}



/// Subtract two rank 4 tensors
GPUStreamTensor4 & operator-  (GPUStreamTensor4 & _lhs, GPUStreamTensor4 & _rhs){

	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,GPUStreamTensor4 &,'-',true,true>(_lhs,_rhs);
}
/// Subtract a rank 4 tensor and a float4444
GPUStreamTensor4 & operator-  (GPUStreamTensor4 & _lhs, float4444 _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,float4444,'-',true,false>(_lhs,_rhs);
}
GPUStreamTensor4 & operator-  (float4444 _lhs, GPUStreamTensor4 & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,float4444,GPUStreamTensor4 &,'-',false,true>(_lhs,_rhs);
}
GPUStreamTensor4 & operator-  (GPUStreamTensor4 & _lhs, GPUConstTensor4 & _rhs){
	float4444 temp  = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,float4444,'-',true,false>(_lhs,temp);
}
GPUStreamTensor4 & operator-  (GPUConstTensor4 & _lhs, GPUStreamTensor4 & _rhs){
	float4444 temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,float4444,GPUStreamTensor4 &,'-',false,true>(temp,_rhs);
}




/// Multiply two scalars
GPUStreamScalar & operator*  (GPUStreamScalar & _lhs, GPUStreamScalar & _rhs){

	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,GPUStreamScalar &,'*',true,true>(_lhs,_rhs);
}
/// Multiply a scalar and a float
GPUStreamScalar & operator*  (GPUStreamScalar & _lhs, float _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'*',true,false>(_lhs,_rhs);
}
GPUStreamScalar & operator*  (float _lhs, GPUStreamScalar & _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'*',true,false>(_rhs,_lhs);
}
GPUStreamScalar & operator*  (GPUStreamScalar & _lhs, GPUConstScalar & _rhs){
	float temp  = _rhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'*',true,false>(_lhs,temp);
}
GPUStreamScalar & operator*  (GPUConstScalar & _lhs, GPUStreamScalar & _rhs){
	float temp  = _lhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'*',true,false>(_rhs,temp);
}

/// Multiply a scalar and a vector
GPUStreamVector & operator*  (GPUStreamScalar & _lhs, GPUStreamVector & _rhs){

	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,GPUStreamScalar &,'*',true,true>(_rhs,_lhs);
}
GPUStreamVector & operator*  (GPUStreamVector & _lhs, GPUStreamScalar & _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,GPUStreamScalar &,'*',true,true>(_lhs,_rhs);
}
/// Multiply a const scalar and a vector
GPUStreamVector & operator*  (GPUStreamVector & _lhs, float _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,float,'*',true,false>(_lhs,_rhs);
}
GPUStreamVector & operator*  (float _lhs, GPUStreamVector & _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,float,'*',true,false>(_rhs,_lhs);
}
GPUStreamVector & operator*  (GPUStreamVector & _lhs, GPUConstScalar & _rhs){
	float temp  = _rhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,float,'*',true,false>(_lhs,temp);
}

GPUStreamVector & operator*  (GPUConstScalar & _lhs, GPUStreamVector & _rhs){
	float temp  = _lhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,float,'*',true,false>(_rhs,temp);
}


/// Multiply a scalar and a const vector
GPUStreamVector & operator*  (GPUStreamScalar & _lhs,  float4 _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamScalar &,float4,'*',true,false>(_lhs,_rhs);
}
GPUStreamVector & operator*  ( float4 _lhs, GPUStreamScalar & _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamScalar &,float4,'*',true,false>(_rhs,_lhs);
}
GPUStreamVector & operator*  (GPUStreamScalar & _lhs, GPUConstVector & _rhs){
	float4 temp  = _rhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamScalar &,float4,'*',true,false>(_lhs,temp);
}
GPUStreamVector & operator*  (GPUConstVector & _lhs, GPUStreamScalar & _rhs){
	float4 temp  = _lhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamScalar &,float4,'*',true,false>(_rhs,temp);
}

/// Multiply a scalar and a Tensor2
GPUStreamTensor2 & operator*  (GPUStreamScalar & _lhs, GPUStreamTensor2 & _rhs){

	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,GPUStreamScalar &,'*',true,true>(_rhs,_lhs);
}
GPUStreamTensor2 & operator*  (GPUStreamTensor2 & _lhs, GPUStreamScalar & _rhs){

	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,GPUStreamScalar &,'*',true,true>(_lhs,_rhs);
}
/// Multiply a const scalar and a Tensor2
GPUStreamTensor2 & operator*  (GPUStreamTensor2 & _lhs, float _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,float,'*',true,false>(_lhs,_rhs);
}
GPUStreamTensor2 & operator*  (float _lhs, GPUStreamTensor2 & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,float,'*',true,false>(_rhs,_lhs);
}
GPUStreamTensor2 & operator*  (GPUStreamTensor2 & _lhs, GPUConstScalar & _rhs){
	float temp  = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,float,'*',true,false>(_lhs,temp);
}

GPUStreamTensor2 & operator*  (GPUConstScalar & _lhs, GPUStreamTensor2 & _rhs){
	float temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,float,'*',true,false>(_rhs,temp);
}


/// Multiply a scalar and a const Tensor2
GPUStreamTensor2 & operator*  (GPUStreamScalar & _lhs,  float44 _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamScalar &,float44,'*',true,false>(_lhs,_rhs);
}
GPUStreamTensor2 & operator*  ( float44 _lhs, GPUStreamScalar & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamScalar &,float44,'*',true,false>(_rhs,_lhs);
}
GPUStreamTensor2 & operator*  (GPUStreamScalar & _lhs, GPUConstTensor2 & _rhs){
	float44 temp  = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamScalar &,float44,'*',true,false>(_lhs,temp);
}
GPUStreamTensor2 & operator*  (GPUConstTensor2 & _lhs, GPUStreamScalar & _rhs){
	float44 temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamScalar &,float44,'*',true,false>(_rhs,temp);
}


/// Multiply a scalar and a Tensor3
GPUStreamTensor3 & operator*  (GPUStreamScalar & _lhs, GPUStreamTensor3 & _rhs){

	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,GPUStreamScalar &,'*',true,true>(_rhs,_lhs);
}
GPUStreamTensor3 & operator*  (GPUStreamTensor3 & _lhs, GPUStreamScalar & _rhs){

	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,GPUStreamScalar &,'*',true,true>(_lhs,_rhs);
}
/// Multiply a const scalar and a Tensor3
GPUStreamTensor3 & operator*  (GPUStreamTensor3 & _lhs, float _rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,float,'*',true,false>(_lhs,_rhs);
}
GPUStreamTensor3 & operator*  (float _lhs, GPUStreamTensor3 & _rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,float,'*',true,false>(_rhs,_lhs);
}
GPUStreamTensor3 & operator*  (GPUStreamTensor3 & _lhs, GPUConstScalar & _rhs){
	float temp  = _rhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,float,'*',true,false>(_lhs,temp);
}

GPUStreamTensor3 & operator*  (GPUConstScalar & _lhs, GPUStreamTensor3 & _rhs){
	float temp  = _lhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,float,'*',true,false>(_rhs,temp);
}


/// Multiply a scalar and a const Tensor3
GPUStreamTensor3 & operator*  (GPUStreamScalar & _lhs,  float444 _rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamScalar &,float444,'*',true,false>(_lhs,_rhs);
}
GPUStreamTensor3 & operator*  ( float444 _lhs, GPUStreamScalar & _rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamScalar &,float444,'*',true,false>(_rhs,_lhs);
}
GPUStreamTensor3 & operator*  (GPUStreamScalar & _lhs, GPUConstTensor3 & _rhs){
	float444 temp  = _rhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamScalar &,float444,'*',true,false>(_lhs,temp);
}
GPUStreamTensor3 & operator*  (GPUConstTensor3 & _lhs, GPUStreamScalar & _rhs){
	float444 temp  = _lhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamScalar &,float444,'*',true,false>(_rhs,temp);
}


/// Multiply a scalar and a Tensor4
GPUStreamTensor4 & operator*  (GPUStreamScalar & _lhs, GPUStreamTensor4 & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,GPUStreamScalar &,'*',true,true>(_rhs,_lhs);
}
GPUStreamTensor4 & operator*  (GPUStreamTensor4 & _lhs, GPUStreamScalar & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,GPUStreamScalar &,'*',true,true>(_lhs,_rhs);
}
/// Multiply a const scalar and a Tensor4
GPUStreamTensor4 & operator*  (GPUStreamTensor4 & _lhs, float _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,float,'*',true,false>(_lhs,_rhs);
}
GPUStreamTensor4 & operator*  (float _lhs, GPUStreamTensor4 & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,float,'*',true,false>(_rhs,_lhs);
}
GPUStreamTensor4 & operator*  (GPUStreamTensor4 & _lhs, GPUConstScalar & _rhs){
	float temp  = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,float,'*',true,false>(_lhs,temp);
}

GPUStreamTensor4 & operator*  (GPUConstScalar & _lhs, GPUStreamTensor4 & _rhs){
	float temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,float,'*',true,false>(_rhs,temp);
}


/// Multiply a scalar and a const Tensor4
GPUStreamTensor4 & operator*  (GPUStreamScalar & _lhs,  float4444 _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamScalar &,float4444,'*',true,false>(_lhs,_rhs);
}
GPUStreamTensor4 & operator*  ( float4444 _lhs, GPUStreamScalar & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamScalar &,float4444,'*',true,false>(_rhs,_lhs);
}
GPUStreamTensor4 & operator*  (GPUStreamScalar & _lhs, GPUConstTensor4 & _rhs){
	float4444 temp  = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamScalar &,float4444,'*',true,false>(_lhs,temp);
}
GPUStreamTensor4 & operator*  (GPUConstTensor4 & _lhs, GPUStreamScalar & _rhs){
	float4444 temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamScalar &,float4444,'*',true,false>(_rhs,temp);
}




/// Multiply consts - not templated because of ambiguities
GPUConstScalar & operator*  ( GPUConstScalar & _lhs, GPUConstScalar & _rhs){
	return * new GPUConstScalar(_lhs()*_rhs());
}
GPUConstVector & operator*  ( GPUConstScalar & _lhs, GPUConstVector & _rhs){
	return * new GPUConstVector(_lhs()*_rhs());
}
GPUConstTensor2 & operator*  ( GPUConstScalar & _lhs, GPUConstTensor2 & _rhs){
	return * new GPUConstTensor2(_lhs()*_rhs());
}

GPUConstTensor3 & operator*  ( GPUConstScalar & _lhs, GPUConstTensor3 & _rhs){
	return * new GPUConstTensor3(_lhs()*_rhs());
}

GPUConstTensor4 & operator*  ( GPUConstScalar & _lhs, GPUConstTensor4 & _rhs){
	return * new GPUConstTensor4(_lhs()*_rhs());
}

/// Divide two scalars
GPUStreamScalar & operator/  (GPUStreamScalar & _lhs, GPUStreamScalar & _rhs){

	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,GPUStreamScalar &,'/',true,true>(_lhs,_rhs);
}
/// Divide a scalar and a float
GPUStreamScalar & operator/  (GPUStreamScalar & _lhs, float _rhs){
	float temp  = 1.0f/_rhs;
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'*',true,false>(_lhs,temp);
}
GPUStreamScalar & operator/  (float _lhs, GPUStreamScalar & _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,float,GPUStreamScalar &,'/',false,true>(_lhs,_rhs);
}
GPUStreamScalar & operator/  (GPUStreamScalar & _lhs, GPUConstScalar & _rhs){
	float temp  = 1.0f/_rhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'*',true,false>(_lhs,temp);
}
GPUStreamScalar & operator/  (GPUConstScalar & _lhs, GPUStreamScalar & _rhs){
	float temp  = _lhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,float,GPUStreamScalar &,'/',false,true>(temp,_rhs);
}

/// Divide a scalar and a vector
GPUStreamVector & operator/  (GPUStreamVector & _lhs, GPUStreamScalar & _rhs){

	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,GPUStreamScalar &,'/',true,true>(_lhs,_rhs);
}
/// Divide a const scalar and a vector
GPUStreamVector & operator/  (GPUStreamVector & _lhs, float _rhs){
	float temp  = 1.0f/_rhs;
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,float,'*',true,false>(_lhs,temp);
}
GPUStreamVector & operator/  (GPUStreamVector & _lhs, GPUConstScalar & _rhs){
	float temp  = 1.0f/_rhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,float,'*',true,false>(_lhs,temp);
}


/// Divide a scalar and a const vector
GPUStreamVector & operator/  ( float4 _lhs, GPUStreamScalar & _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,float4,GPUStreamScalar &,'/',false,true>(_lhs,_rhs);
}
GPUStreamVector & operator/  (GPUConstVector & _lhs, GPUStreamScalar & _rhs){
	float4 temp  = _lhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,float4,GPUStreamScalar &,'/',false,true>(temp,_rhs);
}

/// Divide a scalar and a Tensor2
GPUStreamTensor2 & operator/  (GPUStreamTensor2 & _lhs, GPUStreamScalar & _rhs){

	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,GPUStreamScalar &,'/',true,true>(_lhs,_rhs);
}
/// Divide a const scalar and a Tensor2
GPUStreamTensor2 & operator/  (GPUStreamTensor2 & _lhs, float _rhs){
	float temp  = 1.0f/_rhs;
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,float,'*',true,false>(_lhs,temp);
}
GPUStreamTensor2 & operator/  (GPUStreamTensor2 & _lhs, GPUConstScalar & _rhs){
	float temp  = 1.0f/_rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,float,'*',true,false>(_lhs,temp);
}


/// Divide a scalar and a const Tensor2
GPUStreamTensor2 & operator/  ( float44 _lhs, GPUStreamScalar & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,float44,GPUStreamScalar &,'/',false,true>(_lhs,_rhs);
}
GPUStreamTensor2 & operator/  (GPUConstTensor2 & _lhs, GPUStreamScalar & _rhs){
	float44 temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,float44,GPUStreamScalar &,'/',false,true>(temp,_rhs);
}
GPUConstScalar & operator/ (float _lhs, GPUConstScalar & _rhs){
	return * new GPUConstScalar(_lhs/_rhs());
}
GPUConstVector & operator/ (float4 _lhs, GPUConstScalar & _rhs){
	return * new GPUConstVector(_lhs/_rhs());
}
GPUConstTensor2 & operator/ (float44 _lhs, GPUConstScalar & _rhs){
	return * new GPUConstTensor2(_lhs/_rhs());
}



/// Divide a scalar and a Tensor3
GPUStreamTensor3 & operator/  (GPUStreamTensor3 & _lhs, GPUStreamScalar & _rhs){

	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,GPUStreamScalar &,'/',true,true>(_lhs,_rhs);
}
/// Divide a const scalar and a Tensor3
GPUStreamTensor3 & operator/  (GPUStreamTensor3 & _lhs, float _rhs){
	float temp  = 1.0f/_rhs;
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,float,'*',true,false>(_lhs,temp);
}
GPUStreamTensor3 & operator/  (GPUStreamTensor3 & _lhs, GPUConstScalar & _rhs){
	float temp  = 1.0f/_rhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,float,'*',true,false>(_lhs,temp);
}


/// Divide a scalar and a const Tensor3
GPUStreamTensor3 & operator/  ( float444 _lhs, GPUStreamScalar & _rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,float444,GPUStreamScalar &,'/',false,true>(_lhs,_rhs);
}
GPUStreamTensor3 & operator/  (GPUConstTensor3 & _lhs, GPUStreamScalar & _rhs){
	float444 temp  = _lhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,float444,GPUStreamScalar &,'/',false,true>(temp,_rhs);
}

GPUConstTensor3 & operator/ (float444 _lhs, GPUConstScalar & _rhs){
	return * new GPUConstTensor3(_lhs/_rhs());
}



/// Divide a scalar and a Tensor4
GPUStreamTensor4 & operator/  (GPUStreamTensor4 & _lhs, GPUStreamScalar & _rhs){

	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,GPUStreamScalar &,'/',true,true>(_lhs,_rhs);
}
/// Divide a const scalar and a Tensor4
GPUStreamTensor4 & operator/  (GPUStreamTensor4 & _lhs, float _rhs){
	float temp  = 1.0f/_rhs;
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,float,'*',true,false>(_lhs,temp);
}
GPUStreamTensor4 & operator/  (GPUStreamTensor4 & _lhs, GPUConstScalar & _rhs){
	float temp  = 1.0f/_rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,float,'*',true,false>(_lhs,temp);
}


/// Divide a scalar and a const Tensor4
GPUStreamTensor4 & operator/  ( float4444 _lhs, GPUStreamScalar & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,float4444,GPUStreamScalar &,'/',false,true>(_lhs,_rhs);
}
GPUStreamTensor4 & operator/  (GPUConstTensor4 & _lhs, GPUStreamScalar & _rhs){
	float4444 temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,float4444,GPUStreamScalar &,'/',false,true>(temp,_rhs);
}

GPUConstTensor4 & operator/ (float4444 _lhs, GPUConstScalar & _rhs){
	return * new GPUConstTensor4(_lhs/_rhs());
}



// Repeat as contraction for consisten interface
/// Multiply two scalars
GPUStreamScalar & operator|  (GPUStreamScalar & _lhs, GPUStreamScalar & _rhs){

	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,GPUStreamScalar &,'*',true,true>(_lhs,_rhs);
}
/// Multiply a scalar and a float
GPUStreamScalar & operator|  (GPUStreamScalar & _lhs, float _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'*',true,false>(_lhs,_rhs);
}
GPUStreamScalar & operator|  (float _lhs, GPUStreamScalar & _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'*',true,false>(_rhs,_lhs);
}
GPUStreamScalar & operator|  (GPUStreamScalar & _lhs, GPUConstScalar & _rhs){
	float temp  = _rhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'*',true,false>(_lhs,temp);
}
GPUStreamScalar & operator|  (GPUConstScalar & _lhs, GPUStreamScalar & _rhs){
	float temp  = _lhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'*',true,false>(_rhs,temp);
}




/// Contract two vectors
GPUStreamScalar & operator|  (GPUStreamVector & _lhs, GPUStreamVector & _rhs){

	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamVector &,GPUStreamVector &,'|',true,true>(_lhs,_rhs);
}

/// Contract a vector and a float4
GPUStreamScalar & operator|  (GPUStreamVector & _lhs,  float4 _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamVector &,float4,'|',true,false>(_lhs,_rhs);
}

GPUStreamScalar & operator|  ( float4 _lhs, GPUStreamVector & _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamVector &,float4,'|',true,false>(_rhs,_lhs);
}
GPUStreamScalar & operator|  (GPUStreamVector & _lhs, GPUConstVector & _rhs){
	float4 temp  = _rhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamVector &,float4,'|',true,false>(_lhs,temp);
}
GPUStreamScalar & operator|  (GPUConstVector & _lhs, GPUStreamVector & _rhs){
	float4 temp  = _lhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamVector &,float4,'|',true,false>(_rhs,temp);
}

/// Contract a vector and second Rank tensor
GPUStreamVector & operator|  (GPUStreamVector & _lhs, GPUStreamTensor2 & _rhs){

	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor2 &,GPUStreamVector &,'|',true,true>(_rhs,_lhs);
}

GPUStreamVector & operator|  (GPUStreamTensor2 & _lhs, GPUStreamVector & _rhs){

	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor2 &,GPUStreamVector &,'|',true,true>(_lhs,_rhs);
}
/// Contract a vector and a float44
GPUStreamVector & operator|  (GPUStreamVector & _lhs,  float44 _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,float44,GPUStreamVector &,'|',false,true>(_rhs,_lhs);
}
GPUStreamVector & operator|  ( float44 _lhs, GPUStreamVector & _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,float44,GPUStreamVector &,'|',false,true>(_lhs,_rhs);
}
GPUStreamVector & operator|  (GPUStreamVector & _lhs, GPUConstTensor2 & _rhs){
	float44 temp  = _rhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,float44,GPUStreamVector &,'|',false,true>(temp,_lhs);
}

GPUStreamVector & operator|  (GPUConstTensor2 & _lhs, GPUStreamVector & _rhs){
	float44 temp  = _lhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,float44,GPUStreamVector &,'|',false,true>(temp,_rhs);
}
/// Contract a second rank tensor and a float4
GPUStreamVector & operator|  (GPUStreamTensor2 & _lhs,  float4 _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor2 &,float4,'|',true,false>(_lhs,_rhs);
}
GPUStreamVector & operator|  ( float4 _lhs, GPUStreamTensor2 & _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor2 &,float4,'|',true,false>(_rhs,_lhs);
}
GPUStreamVector & operator|  (GPUStreamTensor2 & _lhs, GPUConstVector & _rhs){
	float4 temp  = _rhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor2 &,float4,'|',true,false>(_lhs,temp);
}
GPUStreamVector & operator|  (GPUConstVector & _lhs, GPUStreamTensor2 & _rhs){
	float4 temp  = _lhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor2 &,float4,'|',true,false>(_rhs,temp);
}

/// Contract two second rank tensors
GPUStreamScalar & operator|  (GPUStreamTensor2 & _lhs, GPUStreamTensor2 & _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor2 &,GPUStreamTensor2 &,'|',true,true>(_lhs,_rhs);
}

GPUStreamTensor2 & operator ||  (GPUStreamTensor2 & _lhs, GPUStreamTensor2 & _rhs){
          return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,GPUStreamTensor2 &,222,true,true>(_lhs,_rhs);
}

/// Contract a second rank tensor and a float44
GPUStreamScalar & operator|  (GPUStreamTensor2 & _lhs,  float44 _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor2 &,float44,'|',true,false>(_lhs,_rhs);
}
GPUStreamScalar & operator|  ( float44 _lhs, GPUStreamTensor2 & _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor2 &,float44,'|',true,false>(_rhs,_lhs);
}
GPUStreamScalar & operator|  (GPUStreamTensor2 & _lhs, GPUConstTensor2 & _rhs){
	float44 temp  = _rhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor2 &,float44,'|',true,false>(_lhs,temp);
}
GPUStreamScalar & operator|  (GPUConstTensor2 & _lhs, GPUStreamTensor2 & _rhs){
	float44 temp  = _lhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor2 &,float44,'|',true,false>(_rhs,temp);
}



/// Contract two third rank tensors
GPUStreamScalar & operator|  (GPUStreamTensor3 & _lhs, GPUStreamTensor3 & _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor3 &,GPUStreamTensor3 &,'|',true,true>(_lhs,_rhs);
}

GPUStreamTensor2 & operator ||  (GPUStreamTensor3 & _lhs, GPUStreamTensor3 & _rhs){
  return * new GPUTwoStreamOp<float44, GPUStreamTensor2, GPUStreamTensor3 &,GPUStreamTensor3 &,233,true,true>(_lhs,_rhs);
}

/// Contract a third rank tensor and a float444
GPUStreamScalar & operator|  (GPUStreamTensor3 & _lhs,  float444 _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor3 &,float444,'|',true,false>(_lhs,_rhs);
}
GPUStreamScalar & operator|  ( float444 _lhs, GPUStreamTensor3 & _rhs){
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor3 &,float444,'|',true,false>(_rhs,_lhs);
}
GPUStreamScalar & operator|  (GPUStreamTensor3 & _lhs, GPUConstTensor3 & _rhs){
	float444 temp  = _rhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor3 &,float444,'|',true,false>(_lhs,temp);
}
GPUStreamScalar & operator|  (GPUConstTensor3 & _lhs, GPUStreamTensor3 & _rhs){
	float444 temp  = _lhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor3 &,float444,'|',true,false>(_rhs,temp);
}


/// Contract a third rank and a second rank tensor
GPUStreamVector & operator|  (GPUStreamTensor3 & _lhs, GPUStreamTensor2 & _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor3 &,GPUStreamTensor2 &,'|',true,true>(_lhs,_rhs);
}
GPUStreamVector & operator|  (GPUStreamTensor2 & _lhs, GPUStreamTensor3 & _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor3 &,GPUStreamTensor2 &,'|',true,true>(_rhs,_lhs);
}
/// Contract a third rank tensor and a float44
GPUStreamVector & operator|  (GPUStreamTensor3 & _lhs,  float44 _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor3 &,float44,'|',true,false>(_lhs,_rhs);
}
GPUStreamVector & operator|  ( float44 _lhs, GPUStreamTensor3 & _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor3 &,float44,'|',true,false>(_rhs,_lhs);
}
GPUStreamVector & operator|  (GPUStreamTensor3 & _lhs, GPUConstTensor2 & _rhs){
	float44 temp  = _rhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor3 &,float44,'|',true,false>(_lhs,temp);
}
GPUStreamVector & operator|  (GPUConstTensor2 & _lhs, GPUStreamTensor3 & _rhs){
	float44 temp  = _lhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor3 &,float44,'|',true,false>(_rhs,temp);
}
/// Contract a second rank tensor and a float444
GPUStreamVector & operator|  (GPUStreamTensor2 & _lhs,  float444 _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor2 &,float444,'|',true,false>(_lhs,_rhs);
}
GPUStreamVector & operator|  ( float444 _lhs, GPUStreamTensor2 & _rhs){
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor2 &,float444,'|',true,false>(_rhs,_lhs);
}
GPUStreamVector & operator|  (GPUStreamTensor2 & _lhs, GPUConstTensor3 & _rhs){
	float444 temp  = _rhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor2 &,float444,'|',true,false>(_lhs,temp);
}
GPUStreamVector & operator|  (GPUConstTensor3 & _lhs, GPUStreamTensor2 & _rhs){
	float444 temp  = _lhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor2 &,float444,'|',true,false>(_rhs,temp);
}



/// Contract a third rank tensor and a vector
GPUStreamTensor2 & operator|  (GPUStreamTensor3 & _lhs, GPUStreamVector & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor3 &,GPUStreamVector &,'|',true,true>(_lhs,_rhs);
}
GPUStreamTensor2 & operator|  (GPUStreamVector & _lhs, GPUStreamTensor3 & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor3 &,GPUStreamVector &,'|',true,true>(_rhs,_lhs);
}
/// Contract a third rank tensor and a float4
GPUStreamTensor2 & operator|  (GPUStreamTensor3 & _lhs,  float4 _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor3 &,float4,'|',true,false>(_lhs,_rhs);
}
GPUStreamTensor2 & operator|  ( float4 _lhs, GPUStreamTensor3 & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor3 &,float4,'|',true,false>(_rhs,_lhs);
}
GPUStreamTensor2 & operator|  (GPUStreamTensor3 & _lhs, GPUConstVector & _rhs){
	float4 temp  = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor3 &,float4,'|',true,false>(_lhs,temp);
}
GPUStreamTensor2 & operator|  (GPUConstVector & _lhs, GPUStreamTensor3 & _rhs){
	float4 temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor3 &,float4,'|',true,false>(_rhs,temp);
}
/// Contract a vector and a float444
GPUStreamTensor2 & operator|  (GPUStreamVector & _lhs,  float444 _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamVector &,float444,'|',true,false>(_lhs,_rhs);
}
GPUStreamTensor2 & operator|  ( float444 _lhs, GPUStreamVector & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamVector &,float444,'|',true,false>(_rhs,_lhs);
}
GPUStreamTensor2 & operator|  (GPUStreamVector & _lhs, GPUConstTensor3 & _rhs){
	float444 temp  = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamVector &,float444,'|',true,false>(_lhs,temp);
}
GPUStreamTensor2 & operator|  (GPUConstTensor3 & _lhs, GPUStreamVector & _rhs){
	float444 temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamVector &,float444,'|',true,false>(_rhs,temp);
}

///
GPUStreamTensor2 & operator|  (GPUStreamTensor4 & _lhs, GPUConstTensor2 & _rhs){
	float44 temp = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor4 &,float44,'|',true,false>(_lhs,temp);
}

GPUStreamTensor2 & operator|  (GPUStreamTensor4 & _lhs, GPUStreamTensor2 & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor4 &, GPUStreamTensor2 &,'|',true, true>(_lhs,_rhs);
}

GPUStreamScalar & operator|  (GPUStreamTensor4 & _lhs, GPUConstTensor4 & _rhs){
	float4444 temp = _rhs();
	return * new GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor4 &,float4444,'|',true,false>(_lhs,temp);
}

GPUStreamVector & operator|  (GPUStreamTensor4 & _lhs, GPUConstTensor3 & _rhs){
	float444 temp = _rhs();
	return * new GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor4 &,float444,'|',true,false>(_lhs,temp);
}


GPUStreamVector  & operator|  (GPUConstTensor4 & _lhs, GPUStreamTensor3 & _rhs){
        float4444 temp = _lhs();
        return * new GPUTwoStreamOp<float4, GPUStreamVector,float4444, GPUStreamTensor3 &,'|',false, true>(temp, _rhs); }

// 20160301-mintj
GPUStreamVector  & operator|  (GPUStreamTensor4 & _lhs, GPUStreamTensor3 & _rhs){
        return * new GPUTwoStreamOp<float4, GPUStreamVector, GPUStreamTensor4 &, GPUStreamTensor3 &,'|',true, true>(_lhs, _rhs);
}

GPUConstTensor3 & operator|  (GPUConstTensor4 & _lhs, GPUConstVector & _rhs){
        return *new GPUConstTensor3(_lhs()|_rhs());
}



/// Contract const objects not templated because of ambiguities
GPUConstVector & operator|  (GPUConstTensor2 & _lhs, GPUConstVector & _rhs){
	return * new GPUConstVector(_lhs()|_rhs());
}
GPUConstVector & operator|  (GPUConstVector & _lhs, GPUConstTensor2 & _rhs){
	return * new GPUConstVector(_lhs()|_rhs());
}


// Contract a fourth rank tensor and a const vector
GPUStreamTensor3 &  operator|  (GPUStreamTensor4 & _lhs, GPUConstVector & _rhs){
	float4 temp = _rhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3, float4, GPUStreamTensor4 &,  '|',false, true>(temp, _lhs);
}
// Contract a vector and a rank 4 const Tensor
GPUStreamTensor3 & operator |  (GPUStreamVector & _lhs, GPUConstTensor4 & _rhs){
	float4444 temp = _rhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3, GPUStreamVector &, float4444,'|',true, false>(_lhs, temp);
}

// Contract a fourth rank const tensor and a vector
GPUStreamTensor3 &  operator|  (GPUConstTensor4 & _lhs, GPUStreamVector & _rhs){
	float4444 temp = _lhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,  GPUStreamVector &, float4444, '|',true, false>(_rhs, temp);
}
// Contract a const vector and a rank 4 Tensor
GPUStreamTensor3 & operator |  (GPUConstVector & _lhs, GPUStreamTensor4 & _rhs){
	float4 temp = _lhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3, float4, GPUStreamTensor4 &,  '|', false, true>(temp, _rhs);
}

// Contract a fourth rank tensor and a vector
GPUStreamTensor3 &  operator|  (GPUStreamTensor4 & _lhs, GPUStreamVector & _rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3,  GPUStreamVector &, GPUStreamTensor4 &,'|',true, true>(_rhs,_lhs);
}
// Contract a const vector and a rank 4 const Tensor
GPUStreamTensor3 & operator |  (GPUStreamVector & _lhs, GPUStreamTensor4 & _rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3, GPUStreamVector &,  GPUStreamTensor4 &,'|',true, true>(_lhs,_rhs);
}

// Contract one index of a fourth rank tensor and a second rank tensor
GPUStreamTensor4 & operator|| (GPUStreamTensor4 & _lhs, GPUStreamTensor2 & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,  GPUStreamTensor4 &, GPUStreamTensor2 &,'@',true, true>(_lhs,_rhs);
}
// Contract one index of a second rank tensor and a fourth rank tensor
GPUStreamTensor4 & operator|| (GPUStreamTensor2 & _lhs, GPUStreamTensor4 & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,  GPUStreamTensor2 &, GPUStreamTensor4 &,'@',true, true>(_lhs,_rhs);
}

// Contract one index of a const fourth rank tensor and a second rank tensor
GPUStreamTensor4 & operator|| (GPUConstTensor4 & _lhs, GPUStreamTensor2 & _rhs){
	float4444 temp = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,  float4444, GPUStreamTensor2 &,'@',false, true>(temp,_rhs);
}
// Contract one index of a const second rank tensor and a fourth rank tensor
GPUStreamTensor4 & operator|| (GPUConstTensor2 & _lhs, GPUStreamTensor4 & _rhs){
	float44 temp = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,  float44, GPUStreamTensor4 &,'@',false, true>(temp,_rhs);
}

// Contract one index of a fourth rank tensor and a const second rank tensor
GPUStreamTensor4 & operator|| (GPUStreamTensor4 & _lhs, GPUConstTensor2 & _rhs){
	float44 temp = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,  GPUStreamTensor4 &, float44,'@',true, false>(_lhs,temp);
}
// Contract one index of a second rank tensor and a const fourth rank tensor
GPUStreamTensor4 & operator|| (GPUStreamTensor2 & _lhs, GPUConstTensor4 & _rhs){
	float4444 temp = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4,  GPUStreamTensor2 &, float4444,'@',true, false>(_lhs,temp);
}

// Contract one index of a const second rank tensor and a const fourth rank tensor
GPUConstTensor4 & operator|| (GPUConstTensor2 & _lhs, GPUConstTensor4 & _rhs){
	return *new GPUConstTensor4(_lhs()||_rhs());
}
// Contract one index of a const fourth rank tensor and a const second rank tensor
GPUConstTensor4 & operator|| (GPUConstTensor4 & _lhs, GPUConstTensor2 & _rhs){
	return *new GPUConstTensor4(_lhs()||_rhs());
}




/// Outer product of two vectors
GPUStreamTensor2 & operator% (GPUStreamVector & _lhs, GPUStreamVector & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamVector &,GPUStreamVector &,'%',true,true>(_lhs,_rhs);
}
/// Outer product of a vector and a float4
GPUStreamTensor2 & operator%  (GPUStreamVector & _lhs,  float4 _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamVector &,float4,'%',true,false>(_lhs,_rhs);
}

GPUStreamTensor2 & operator%  ( float4 _lhs, GPUStreamVector & _rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,float4,GPUStreamVector &,'%',false,true>(_lhs,_rhs);
}
GPUStreamTensor2 & operator%  (GPUStreamVector & _lhs, GPUConstVector & _rhs){
	float4 temp  = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamVector &,float4,'%',true,false>(_lhs,temp);
}
GPUStreamTensor2 & operator%  (GPUConstVector & _lhs, GPUStreamVector & _rhs){
	float4 temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor2,float4,GPUStreamVector &,'%',false,true>(temp,_rhs);
}

GPUConstTensor2 & operator%  (GPUConstVector & _lhs, GPUConstVector & _rhs){
	return * new GPUConstTensor2(_lhs()%_rhs());
}

GPUStreamTensor3 & operator% (GPUStreamTensor2 &_lhs, GPUStreamVector &_rhs){
//	std::cout<<" in GPUStreamTensor3 & operator% (GPUStreamTensor2 &_lhs, GPUStreamVector &_rhs): "<<std::endl;
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3, GPUStreamTensor2 &, GPUStreamVector &,'%',true,true>(_lhs,_rhs);
}

GPUStreamTensor3 & operator% (GPUStreamTensor2 &_lhs, GPUConstVector &_rhs){
	float4 temp  = _rhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3, GPUStreamTensor2 &, float4,'%',true,false>(_lhs,temp);
}

GPUStreamTensor3 & operator% (GPUStreamTensor2 &_lhs, float4 &_rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3, GPUStreamTensor2 &, float4,'%',true,false>(_lhs,_rhs);
}


GPUStreamTensor3 & operator% (GPUConstTensor2 &_lhs, GPUStreamVector &_rhs){
	float44 temp  = _lhs();
//	std::cout<<" c.x: "<<temp.c.x<<" c.y:"<<temp.c.y<<" c.z: "<<temp.c.z<<" c.w: "<<temp.c.w<<std::endl;
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3, float44, GPUStreamVector &,'%',false,true>(temp,_rhs);
}

GPUStreamTensor3 & operator% (float44 &_lhs, GPUStreamVector &_rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3, float44, GPUStreamVector &,'%',false,true>(_lhs,_rhs);
}


/// rank2 const and vector const
GPUConstTensor3 & operator%  (GPUConstTensor2 & _lhs, GPUConstVector & _rhs){
	return * new GPUConstTensor3(_lhs()%_rhs());
}



GPUStreamTensor3 & operator% (GPUStreamVector &_lhs, GPUStreamTensor2 &_rhs){
//	std::cout<<" in GPUStreamTensor3 & operator% (GPUStreamTensor2 &_lhs, GPUStreamVector &_rhs): "<<std::endl;
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3, GPUStreamVector &, GPUStreamTensor2 &,'%',true,true>(_lhs,_rhs);
}

GPUStreamTensor3 & operator% (GPUStreamVector &_lhs, GPUConstTensor2 &_rhs){
	float44 temp  = _rhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3, GPUStreamVector &, float44,'%',true,false>(_lhs,temp);
}

GPUStreamTensor3 & operator% (GPUStreamVector &_lhs, float44 &_rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3, GPUStreamVector &, float44,'%',true,false>(_lhs,_rhs);
}


GPUStreamTensor3 & operator% (GPUConstVector &_lhs, GPUStreamTensor2 &_rhs){
	float4 temp  = _lhs();
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3, float4, GPUStreamTensor2 &,'%',false,true>(temp,_rhs);
}

GPUStreamTensor3 & operator% (float4 &_lhs, GPUStreamTensor2 &_rhs){
	return * new GPUTwoStreamOp<float444, GPUStreamTensor3, float4, GPUStreamTensor2 &,'%',false,true>(_lhs,_rhs);
}


/// rank2 const and vector const
GPUConstTensor3 & operator%  (GPUConstVector & _lhs, GPUConstTensor2 & _rhs){
	return * new GPUConstTensor3(_lhs()%_rhs());
}




/// rank2 stream and rank2 stream
GPUStreamTensor4 & operator% (GPUStreamTensor2 &_lhs, GPUStreamTensor2 &_rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4, GPUStreamTensor2 &, GPUStreamTensor2 &,'%',true,true>(_lhs,_rhs);
}

/// rank2 stream and rank2 const
GPUStreamTensor4 & operator% (GPUStreamTensor2 &_lhs, GPUConstTensor2 &_rhs){
    float44 temp  = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4, GPUStreamTensor2 &, float44,'%',true,false>(_lhs,temp);
}

/// rank2 const and rank2 stream
GPUStreamTensor4 & operator% (GPUConstTensor2 &_lhs, GPUStreamTensor2 &_rhs){
    float44 temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4, float44, GPUStreamTensor2 &,'%',false,true>(temp,_rhs);
}

/// rank2 const and rank2 const
GPUConstTensor4 & operator%  (GPUConstTensor2 & _lhs, GPUConstTensor2 & _rhs){
	return * new GPUConstTensor4(_lhs()%_rhs());
}

/// Outer product of a third rank Tensor and a Vector
GPUStreamTensor4 & operator% (GPUStreamTensor3 &_lhs, GPUStreamVector &_rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4, GPUStreamTensor3 &, GPUStreamVector &,'%',true,true>(_lhs,_rhs);
}
/// Outer product of a third rank tensor and a const vector
GPUStreamTensor4 & operator% (GPUStreamTensor3 &_lhs, GPUConstVector &_rhs){
    float4 temp  = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4, GPUStreamTensor3 &, float4,'%',true,false>(_lhs,temp);
}
/// Outer product of a const third rank tensor and a vector
GPUStreamTensor4 & operator% (GPUConstTensor3 &_lhs, GPUStreamVector &_rhs){
    float444 temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4, float444, GPUStreamVector &,'%',false,true>(temp,_rhs);
}
/// Outer product of a const third rank Tensor and a const Vector
GPUConstTensor4 & operator%  (GPUConstTensor3 & _lhs, GPUConstVector & _rhs){
	return * new GPUConstTensor4(_lhs()%_rhs());
}

/// Outer product of a third rank Tensor and a Vector
GPUStreamTensor4 & operator% (GPUStreamVector &_lhs, GPUStreamTensor3 &_rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4, GPUStreamVector &, GPUStreamTensor3 &,'%',true,true>(_lhs,_rhs);
}
/// Outer product of a third rank tensor and a const vector
GPUStreamTensor4 & operator% (GPUStreamVector &_lhs, GPUConstTensor3 &_rhs){
    float444 temp  = _rhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4, GPUStreamVector &, float444,'%',true,false>(_lhs,temp);
}
/// Outer product of a const third rank tensor and a vector
GPUStreamTensor4 & operator% (GPUConstVector &_lhs, GPUStreamTensor3 &_rhs){
    float4 temp  = _lhs();
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4, float4, GPUStreamTensor3 &,'%',false,true>(temp,_rhs);
}

/// Outer product of a const third rank Tensor and a const Vector
GPUConstTensor4 & operator%  (GPUConstVector & _lhs, GPUConstTensor3 & _rhs){
	return * new GPUConstTensor4(_lhs()%_rhs());
}

/// Special function for orbitals
GPUStreamTensor4 & spin3projecttensor2(GPUStreamTensor2 &_lhs, GPUStreamTensor2 &_rhs){
	return * new GPUTwoStreamOp<float44, GPUStreamTensor4, GPUStreamTensor2 &, GPUStreamTensor2 &,'#',true,true>(_lhs,_rhs);
}


template<> GPUDataStream<float> * GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,GPUStreamScalar &,'+',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	assert(this->lhs.Rank() == this->rhs.Rank());
	Stream<float> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Adding two streams of floats
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensoradd_0_0(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float> * GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'+',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * lstream = this->lhs(index,block);
	// Adding a stream of floats and a float
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensoradd_0_f(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,GPUStreamVector &,'+',true,true>::operator()(int index, int block){
//	cout << "Adding two vectors for index " << index << " block " << block << endl;
//	cout << mList << endl;
//	cout << mList->GetNSets() << endl;
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	assert(this->lhs.Rank() == this->rhs.Rank());
	Stream<float4> * lstream = this->lhs(index,block);
	Stream<float4> * rstream = this->rhs(index,block);
//	cout << "Lpointer " << lstream << endl;
//	cout << "Rpointer " << rstream << endl;
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Adding two streams of four-vectors
//	cout << mList << endl;
//	cout << mList->GetNSets() << endl;
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
//	float4 * ld;
//	ld = lstream->AllocateRead();
//	cout << ld[0].x << endl;
//	float4 * rd;
//	rd = rstream->AllocateRead();
//	cout << rd[0].x << endl;
//	cout << mList << endl;
//	cout << mList->GetNSets() << endl;
	kerneltensoradd_1_1(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
//	float4 * res = this->mstream[index][block]->AllocateRead();
//	cout << res[0].x << endl;
//	cout << mList << endl;
//	cout << mList->GetNSets() << endl;
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,float4,'+',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	// Adding a stream of vectors and a float4
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensoradd_1_f(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,GPUStreamTensor2 &,'+',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	assert(this->lhs.Rank() == this->rhs.Rank());
	Stream<float44> * lstream = this->lhs(index,block);
	Stream<float44> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Adding two streams of second rank tensors
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensoradd_2_2(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,float44,'+',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	// Adding a stream of vectors and a float4
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensoradd_2_f44(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,GPUStreamTensor3 &,'+',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	assert(this->lhs.Rank() == this->rhs.Rank());
	Stream<float444> * lstream = this->lhs(index,block);
	Stream<float444> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Adding two streams of second rank tensors
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensoradd_3_3(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,float444,'+',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	// Adding a stream of vectors and a float4
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensoradd_3_f(mList->GetDeviceInterface(), lstream, this->rhs,this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}




template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,GPUStreamTensor4 &,'+',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	assert(this->lhs.Rank() == this->rhs.Rank());
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	GPUDataStream<float44> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Adding two streams of rank 4
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,this->lhs.GetLength(index,block));
	for(int i = 0; i < 16; i++){
		// Here we crash... why??
		(*lstream)(i);
		(*rstream)(i);
		(*this->mstream[index][block])(i);
		kerneltensoradd_2_2(mList->GetDeviceInterface(), (*lstream)(i), (*rstream)(i), (*this->mstream[index][block])(i));
	}
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,float4444,'+',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	// Adding rank 4 stream and a float4444
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(),0, 16,this->lhs.GetLength(index,block));
	for(int i = 0; i < 16; i++){
	  kerneltensoradd_2_f44(mList->GetDeviceInterface(),(*lstream)(i), rhs(i), (*this->mstream[index][block])(i));
	}
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}




template<> GPUDataStream<float> * GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,GPUStreamScalar &,'-',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	assert(this->lhs.Rank() == this->rhs.Rank());
	Stream<float> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Subtracting two streams of floats
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorsub_0_0(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float> * GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'-',true, false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * lstream = this->lhs(index,block);
	// Adding a stream of floats and a float
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorsub_0_f(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float> * GPUTwoStreamOp<float, GPUStreamScalar,float,GPUStreamScalar &,'-', false, true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * rstream = this->rhs(index,block);
	// Subtracting a stream of floats and a float
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
	kerneltensorsub_f_0(mList->GetDeviceInterface(), this->lhs, rstream, this->mstream[index][block]);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,GPUStreamVector &,'-',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	assert(this->lhs.Rank() == this->rhs.Rank());
	Stream<float4> * lstream = this->lhs(index,block);
	Stream<float4> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Subtracting two streams of four-vectors
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorsub_1_1(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,float4,'-',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	// Subtracting a stream of floats and a float
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorsub_1_f(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,float4,GPUStreamVector &,'-',false,true>::operator()(int index, int block){
//	std::cout<<" in template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,float4,GPUStreamVector &,'-'>::operator()(int index, int block): "<<std::endl;
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * rstream = this->rhs(index,block);
	// Subtracting a stream of floats and a float
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
	kerneltensorsub_f_1(mList->GetDeviceInterface(), this->lhs, rstream, this->mstream[index][block]);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,GPUStreamTensor2 &,'-',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	assert(this->lhs.Rank() == this->rhs.Rank());
	Stream<float44> * lstream = this->lhs(index,block);
	Stream<float44> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Subtracting two streams of second rank tensors
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorsub_2_2(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,float44,'-',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	// Subtracting a stream of vectors and a float4
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorsub_2_f(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,float44,GPUStreamTensor2 &,'-',false,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * rstream = this->rhs(index,block);
	// Subtracting a stream of vectors and a float4
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
	kerneltensorsub_f_2(mList->GetDeviceInterface(), this->lhs, rstream, this->mstream[index][block]);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,GPUStreamTensor3 &,'-',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	assert(this->lhs.Rank() == this->rhs.Rank());
	Stream<float444> * lstream = this->lhs(index,block);
	Stream<float444> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Subtracting two streams of second rank tensors
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorsub_3_3(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,float444,'-',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	// Subtracting a stream of vectors and a float4
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorsub_3_f(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3,float444,GPUStreamTensor3 &,'-',false,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * rstream = this->rhs(index,block);
	// Subtracting a stream of rank3and a float444
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
	kerneltensorsub_f_3(mList->GetDeviceInterface(), this->lhs, rstream, this->mstream[index][block]);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}




template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,GPUStreamTensor4 &,'-',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	assert(this->lhs.Rank() == this->rhs.Rank());
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	GPUDataStream<float44> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Subtracting two streams of rank 4
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	for(int i = 0; i < 16; i++){
		kerneltensorsub_2_2(mList->GetDeviceInterface(), (*lstream)(i), (*rstream)(i), (*this->mstream[index][block])(i));
	}
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,float4444,'-',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	// Subtracting a stream of rank4 and a float4444
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	for(int i = 0; i < 16; i++){
		kerneltensorsub_2_f(mList->GetDeviceInterface(), (*lstream)(i),rhs(i), (*this->mstream[index][block])(i));
	}
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4,float4444,GPUStreamTensor4 &,'-',false,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * rstream = this->rhs(index,block);
	// Subtracting a stream of float4444 and rank4
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->rhs.GetLength(index,block));
	for(int i = 0; i < 16; i++){
		kerneltensorsub_f_2(mList->GetDeviceInterface(), lhs(i), (*rstream)(i), (*this->mstream[index][block])(i));
	}
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}



template<> GPUDataStream<float> * GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,GPUStreamScalar &,'*',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Multiplying two streams of floats
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_0_0(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float> * GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,float,'*',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_0_f(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,GPUStreamScalar &,'*',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_0_1(mList->GetDeviceInterface(), rstream, lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,float,'*',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_f_1(mList->GetDeviceInterface(), this->rhs, lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamScalar &,float4,'*',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_0_f4(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,GPUStreamScalar &,'*',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_0_2(mList->GetDeviceInterface(), rstream, lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,float,'*',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_f_2(mList->GetDeviceInterface(), this->rhs, lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamScalar &,float44,'*',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_0_f44(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,GPUStreamScalar &,'*',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_0_3(mList->GetDeviceInterface(), rstream, lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,float,'*',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_f_3(mList->GetDeviceInterface(), this->rhs, lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamScalar &,float444,'*',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_0_f444(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,GPUStreamScalar &,'*',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	GPUDataStream<float> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	for(int i=0; i < 16; i++){
	  kerneltensormult_0_2(mList->GetDeviceInterface(), rstream, (*lstream)(i), (*this->mstream[index][block])(i));
	}
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,float,'*',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	for(int i=0; i < 16; i++){
		kerneltensormult_f_2(mList->GetDeviceInterface(), this->rhs, (*lstream)(i), (*this->mstream[index][block])(i));
	}
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamScalar &,float4444,'*',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	for(int i = 0; i < 16; i++){
		kerneltensormult_0_f44(mList->GetDeviceInterface(), lstream,rhs(i), (*this->mstream[index][block])(i));
	}
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}



template<> GPUDataStream<float> * GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamScalar &,GPUStreamScalar &,'/',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Dividing two streams of floats
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensordiv_0_0(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float> * GPUTwoStreamOp<float, GPUStreamScalar,float,GPUStreamScalar &,'/',false,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * rstream = this->rhs(index,block);
	// Dividing two streams of floats
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
	kerneltensordiv_f_0(mList->GetDeviceInterface(), this->lhs, rstream, this->mstream[index][block]);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,GPUStreamScalar &,'/',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Dividing vector stream by scalar stream
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensordiv_1_0(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,float4,GPUStreamScalar &,'/',false,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * rstream = this->rhs(index,block);
	// Dividing const vector by scalar stream
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
	kerneltensordiv_f4_0(mList->GetDeviceInterface(), this->lhs, rstream, this->mstream[index][block]);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor2 &,GPUStreamScalar &,'/',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Dividing tensor stream by scalar stream
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensordiv_2_0(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamVector &,GPUStreamScalar &,'*'>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)== this->rhs.GetLength(index,block));
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_0_1(mList->GetDeviceInterface(), rstream, lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,float44,GPUStreamScalar &,'/',false,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * rstream = this->rhs(index,block);
	// Dividing const tensor by scalar stream
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
	kerneltensordiv_f44_0(mList->GetDeviceInterface(), this->lhs, rstream, this->mstream[index][block]);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,GPUStreamScalar &,'/',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Dividing tensor stream by scalar stream
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensordiv_3_0(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3,float444,GPUStreamScalar &,'/',false,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * rstream = this->rhs(index,block);
	// Dividing const tensor by scalar stream
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
	kerneltensordiv_f444_0(mList->GetDeviceInterface(), this->lhs, rstream, this->mstream[index][block]);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,GPUStreamScalar &,'/',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Dividing tensor stream by scalar stream
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	for(int i=0; i < 16; i++){
			kerneltensordiv_2_0(mList->GetDeviceInterface(), (*lstream)(i), rstream, (*this->mstream[index][block])(i));
	}
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4,float4444,GPUStreamScalar &,'/',false,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float> * rstream = this->rhs(index,block);
	// Dividing const tensor by scalar stream
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->rhs.GetLength(index,block));
	for(int i = 0; i < 16; i++){
			kerneltensordiv_f44_0(mList->GetDeviceInterface(), lhs(i), rstream, (*this->mstream[index][block])(i));
	}
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float> * GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamVector &,GPUStreamVector &,'|',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	Stream<float4> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Contracting vector streams
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_1_1(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}



template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamTensor3 &,GPUStreamScalar &,'*'>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensormult_0_3(mList->GetDeviceInterface(), rstream, lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float> * GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamVector &,float4,'|',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	// Contracting vector stream with const vector
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_1_f(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor2 &,GPUStreamVector &,'|',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	Stream<float4> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Contracting second rank stream with vector stream
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_2_1(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor2 &,float4,'|',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	// Contracting second rank Tensor stream with const vector
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_2_f4(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &,GPUStreamScalar &,'*'>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	Stream<float> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)== this->rhs.GetLength(index,block));
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	for(int i =0; i < 16; i++){
		kerneltensormult_0_2(mList->GetDeviceInterface(), rstream, (*lstream)(i), (*this->mstream[index][block])(i));
	}
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];

}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,float44,GPUStreamVector &,'|',false,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * rstream = this->rhs(index,block);
	// Contracting const second rank Tensor with vector stream
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
	kerneltensorcontract_f44_1(mList->GetDeviceInterface(), this->lhs, rstream, this->mstream[index][block]);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float> * GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor2 &,GPUStreamTensor2 &,'|',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	Stream<float44> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Contracting Tensor2 streams
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_2_2(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2, GPUStreamTensor2 &,GPUStreamTensor2 &, 222,true,true>::operator()(int index, int block){

         this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];

	  Stream<float44> * lstream = this->lhs(index,block);
	  Stream<float44> * rstream = this->rhs(index,block);
	  assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));

	  // Contracting Tensor2 streams
	  this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	  kerneltensorcontract2_2_2(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	  this->lhs.DecreaseUsecount(index,block);
	  this->rhs.DecreaseUsecount(index,block);
	  return this->mstream[index][block];
}




template<> GPUDataStream<float> * GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor2 &,float44,'|',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	// Contracting Tensor2 stream with const Tensor2
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_2_f44(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float> * GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor3 &,GPUStreamTensor3 &,'|',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	Stream<float444> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Contracting Tensor3 streams
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_3_3(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}



template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor3 &,GPUStreamTensor3 &,233,true,true>::operator()(int index, int block){

  this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
  Stream<float444> * lstream = this->lhs(index,block);
  Stream<float444> * rstream = this->rhs(index,block);
  assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
  // Contracting Tensor3 streams
  this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));

  kerneltensorcontract2_3_3(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
  this->lhs.DecreaseUsecount(index,block);
  this->rhs.DecreaseUsecount(index,block);
  return this->mstream[index][block];
}


template<> GPUDataStream<float> * GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor3 &,float444,'|',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	// Contracting Tensor3 stream with const Tensor3
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_3_f444(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor3 &,GPUStreamTensor2 &,'|',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	Stream<float44> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Contracting Tensor2 and Tensor3 streams
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_3_2(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor2 &,float444,'|',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	// Contracting Tensor2 stream with const Tensor3
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_2_f444(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4> * GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor3 &,float44,'|',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	// Contracting Tensor3 stream with const Tensor2
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_3_f44(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor3 &,GPUStreamVector &,'|',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	Stream<float4> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Contracting Tensor2 and Tensor3 streams
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_3_1(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamVector &,float444,'|',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	// Contracting Vector stream with const Tensor3
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_f444_1(mList->GetDeviceInterface(), this->rhs, lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor3 &,float4,'|',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	// Contracting Tensor3 stream with const Vector
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcontract_3_f4(mList->GetDeviceInterface(), lstream, this->rhs,  this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float44>* GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor4 &,float44,'|',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	// Contracting Tensor4 stream with const Tensor2
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	GPUDataStream<float> * temp[16];
	for(int i=0; i<16; i++){
	  temp[i] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	  kerneltensorcontract_2_f44(mList->GetDeviceInterface(), (*lstream)(i), this->rhs, (temp[i]));
	}
	kerneltensormake_2(mList->GetDeviceInterface(), (temp[0]), (temp[1]), (temp[2]), (temp[3]),
			   (temp[4]), (temp[5]), (temp[6]), (temp[7]),
			   (temp[8]), (temp[9]), (temp[10]), (temp[11]),
			   (temp[12]), (temp[13]), (temp[14]), (temp[15]), this->mstream[index][block]);
	for(int i=0; i<16; i++){
	  delete temp[i];
	}
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44>* GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamTensor4 &, GPUStreamTensor2 &,'|',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	GPUDataStream<float44> * rstream = this->rhs(index,block);
	// Contracting Tensor4 stream with const Tensor2
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	GPUDataStream<float> * temp[16];
	for(int i=0; i<16; i++){
	  temp[i] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	  kerneltensorcontract_2_2(mList->GetDeviceInterface(),(*lstream)(i), (rstream), (temp[i]));
	}
	kerneltensormake_2(mList->GetDeviceInterface(),(temp[0]), (temp[1]), (temp[2]), (temp[3]),
			   (temp[4]), (temp[5]), (temp[6]), (temp[7]),
			   (temp[8]), (temp[9]), (temp[10]), (temp[11]),
			   (temp[12]), (temp[13]), (temp[14]), (temp[15]), this->mstream[index][block]);
	for(int i=0; i<16; i++){
	  delete temp[i];
	}
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

/********* One index contractions **********/

template<> GPUDataStream<float44>* GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &, GPUStreamTensor2 &,'@',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	GPUDataStream<float44> * rstream = this->rhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	for(int i=0; i<16; i++){
	  kerneltensorcontract2_2_2(mList->GetDeviceInterface(),(*lstream)(i), (rstream), (*(this->mstream[index][block]))(i));
	}
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44>* GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor2 &, GPUStreamTensor4 &,'@',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	GPUDataStream<float44> * rstream = this->rhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	GPUDataStream<float4> * temp = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	GPUDataStream<float4> * temparr[4];
	for(int i=0; i<4; i++){
		temparr[i] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	}
	for(int i=0; i<4; i++){
		kernelgetvector_2(mList->GetDeviceInterface(), lstream,i,temp);
		for(int j=0; j<4; j++){
			for(int k=0; k<4; k++){
				kerneltensorcontract_2_1(mList->GetDeviceInterface(), (*rstream)(j,k),temp, temparr[k]);
			}
			kerneltensormake_2_1(mList->GetDeviceInterface(), temparr[0], temparr[1], temparr[2], temparr[3], (*(this->mstream[index][block]))(i,j));
		}
	}
	delete temp;
	for(int i=0; i<4; i++){
		delete temparr[i];
	}
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float44>* GPUTwoStreamOp<float44, GPUStreamTensor4, float4444, GPUStreamTensor2 &,'@',false,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * rstream = this->rhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->rhs.GetLength(index,block));
	for(int i=0; i<16; i++){
	  kerneltensorcontract2_f44_2(mList->GetDeviceInterface(),lhs(i), (rstream), (*(this->mstream[index][block]))(i));
	}
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44>* GPUTwoStreamOp<float44, GPUStreamTensor4,float44, GPUStreamTensor4 &,'@',false,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * rstream = this->rhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->rhs.GetLength(index,block));
	GPUDataStream<float4> * temparr[4];
	for(int i=0; i<4; i++){
		temparr[i] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
	}
	for(int i=0; i<4; i++){
		float4 v;
		if(i==0)
			v = lhs.c;
		if(i==1)
			v = lhs.d;
		if(i==2)
			v = lhs.e;
		if(i==3)
			v = lhs.f;
		for(int j=0; j<4; j++){
			for(int k=0; k<4; k++){
				kerneltensorcontract_2_f4(mList->GetDeviceInterface(), (*rstream)(j,k), v, temparr[k]);
			}
			kerneltensormake_2_1(mList->GetDeviceInterface(), temparr[0], temparr[1], temparr[2], temparr[3], (*(this->mstream[index][block]))(i,j));
		}
	}
	for(int i=0; i<4; i++){
		delete temparr[i];
	}
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44>* GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor4 &, float44,'@',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	for(int i=0; i<16; i++){
	  kerneltensorcontract2_2_f44(mList->GetDeviceInterface(),(*lstream)(i), rhs, (*(this->mstream[index][block]))(i));
	}
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44>* GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamTensor2 &, float4444,'@',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	GPUDataStream<float4> * temp = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	GPUDataStream<float4> * temparr[4];
	for(int i=0; i<4; i++){
		temparr[i] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	}
	for(int i=0; i<4; i++){
		kernelgetvector_2(mList->GetDeviceInterface(), lstream,i,temp);
		for(int j=0; j<4; j++){
			for(int k=0; k<4; k++){
				kerneltensorcontract_f44_1(mList->GetDeviceInterface(), rhs(j,k),temp, temparr[k]);
			}
			kerneltensormake_2_1(mList->GetDeviceInterface(), temparr[0], temparr[1], temparr[2], temparr[3], (*(this->mstream[index][block]))(i,j));
		}
	}
	delete temp;
	for(int i=0; i<4; i++){
		delete temparr[i];
	}
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


/********* END One index contractions **********/




















template<> GPUDataStream<float>* GPUTwoStreamOp<float, GPUStreamScalar,GPUStreamTensor4 &,float4444,'|',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	// Contracting Tensor4 stream with const Tensor4
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	std::vector<GPUDataStream<float> * > streams;
	for(int m=0;m<16;m++){
		streams.push_back(new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block)));
	}
	int k=0;
	for(int i=0; i < 4; i++){
	  for(int j=0; j < 4; j++){
	    int sign = 1;
	    if(3==i)
	      sign = -sign;
	    if(3==j)
	      sign = -sign;
	    kerneltensorcontract_2_f44(mList->GetDeviceInterface(), (*lstream)(i,j), sign*rhs(i,j), streams[k]);
	    k++;
	  }
	}
	kerneltensoradd_0_16(mList->GetDeviceInterface(), streams[0], streams[1], streams[2], streams[3], streams[4], streams[5], streams[6], streams[7],
	                     streams[8], streams[9], streams[10], streams[11], streams[12], streams[13], streams[14], streams[15],
			     this->mstream[index][block]);
	for(int n=0;n<16;n++){
	  delete streams[n];
	}
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

//20160301-mintj
template<> GPUDataStream<float4>* GPUTwoStreamOp<float4, GPUStreamVector, GPUStreamTensor4 &, GPUStreamTensor3 &,'|',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	GPUDataStream<float444> * rstream = this->rhs(index,block);
	// Contracting Tensor4 stream with Tensor3
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));

	GPUDataStream<float4> * temp[4][4];
	for(int i=0; i<4; i++){
	  for(int j=0; j<4; j++){
	     temp[i][j] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	     int sign = 1;
	     if(i==3)
	       sign = -sign;
	     if(j==3)
	       sign = -sign;
	     kerneltensorcontract_2_3_sign(mList->GetDeviceInterface(), (*lstream)(i,j), rstream, sign, (temp[i][j]));
	  }
	}

	  kerneltensoradd_4_16(mList->GetDeviceInterface(), (temp[0][0]), (temp[0][1]),(temp[0][2]),(temp[0][3]),
			       (temp[1][0]), (temp[1][1]),(temp[1][2]),(temp[1][3]),
			       (temp[2][0]), (temp[2][1]),(temp[2][2]),(temp[2][3]),
			       (temp[3][0]), (temp[3][1]),(temp[3][2]),(temp[3][3]),
			       this->mstream[index][block]);

	for(int ii=0; ii<4; ii++){
	  for(int jj=0; jj<4; jj++){
	    delete temp[ii][jj];
	  }
	}
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4>* GPUTwoStreamOp<float4, GPUStreamVector,GPUStreamTensor4 &,float444,'|',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	// Contracting Tensor4 stream with const Tensor3
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));

	GPUDataStream<float4> * temp[4][4];
	for(int i=0; i<4; i++){
	  for(int j=0; j<4; j++){
	     temp[i][j] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	     int sign = 1;
	     if(i==3)
	       sign = -sign;
	     if(j==3)
	       sign = -sign;
	     kerneltensorcontract_2_f444(mList->GetDeviceInterface(), (*lstream)(i,j), sign*rhs, (temp[i][j]));
	  }
	}

	  kerneltensoradd_4_16(mList->GetDeviceInterface(), (temp[0][0]), (temp[0][1]),(temp[0][2]),(temp[0][3]),
			       (temp[1][0]), (temp[1][1]),(temp[1][2]),(temp[1][3]),
			       (temp[2][0]), (temp[2][1]),(temp[2][2]),(temp[2][3]),
			       (temp[3][0]), (temp[3][1]),(temp[3][2]),(temp[3][3]),
			       this->mstream[index][block]);

	for(int ii=0; ii<4; ii++){
	  for(int jj=0; jj<4; jj++){
	    delete temp[ii][jj];
	  }
	}
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}



template<> GPUDataStream<float4>* GPUTwoStreamOp<float4, GPUStreamVector,float4444, GPUStreamTensor3 &,'|',false, true>::operator()(int index, int block){

  this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
  GPUDataStream<float444> * rstream = this->rhs(index,block);

  // Contracting Tensor4 stream with const Tensor3
  this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));

  GPUDataStream<float4> * temp[4][4];
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      temp[i][j] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
      int sign = 1;
      if(i==3)
	sign = -sign;
      if(j==3)
	sign = -sign;


      kerneltensorcontract_f44_3(mList->GetDeviceInterface(), sign*lhs(i,j), rstream, (temp[i][j]));

    }
  }

  for(int n=0; n<4; n++){

    kerneltensoradd_4_16(mList->GetDeviceInterface(),(temp[0][0]), (temp[0][1]),(temp[0][2]),(temp[0][3]),
                         (temp[1][0]), (temp[1][1]),(temp[1][2]),(temp[1][3]),
                         (temp[2][0]), (temp[2][1]),(temp[2][2]),(temp[2][3]),
                         (temp[3][0]), (temp[3][1]),(temp[3][2]),(temp[3][3]),
                         this->mstream[index][block]);

}

for(int ii=0; ii<4; ii++){
  for(int jj=0; jj<4; jj++){
    delete temp[ii][jj];
  }
}
return this->mstream[index][block];
}



template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamVector &,GPUStreamVector &,'%',true,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	Stream<float4> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Outer product of vector streams
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorouter_1_1(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,GPUStreamVector &,float4,'%',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	// Outer product of vector stream and const vector
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorouter_1_f4(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor2,float4,GPUStreamVector &,'%',false,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * rstream = this->rhs(index,block);
	// Outer product of vector streams
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
	kerneltensorouter_f4_1(mList->GetDeviceInterface(), this->lhs, rstream, this->mstream[index][block]);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3, GPUStreamTensor2 &, GPUStreamVector &,'%',true,true>::operator()(int index, int block){
    this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	Stream<float4> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Outer product of rank2 stream and vector streams
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorouter_2_1(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3, GPUStreamVector &, GPUStreamTensor2 &,'%',true,true>::operator()(int index, int block){
    this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	Stream<float44> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Outer product of rank2 stream and vector streams
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorouter_1_2(mList->GetDeviceInterface(), lstream, rstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3, GPUStreamTensor2 &, float4,'%',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	// Outer product of rank2 stream and vector const
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorouter_2_f4(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3, GPUStreamVector &, float44,'%',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	// Outer product of rank2 stream and vector const
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorouter_1_f44(mList->GetDeviceInterface(), lstream, this->rhs, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3, float44, GPUStreamVector &,'%',false,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * rstream = this->rhs(index,block);
	// Outer product of rank2 const and stream vector
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
	kerneltensorouter_f44_1(mList->GetDeviceInterface(), this->lhs, rstream, this->mstream[index][block]);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUTwoStreamOp<float444, GPUStreamTensor3, float4, GPUStreamTensor2 &,'%',false,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * rstream = this->rhs(index,block);
	// Outer product of rank2 const and stream vector
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
	kerneltensorouter_f4_2(mList->GetDeviceInterface(), this->lhs, rstream, this->mstream[index][block]);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4, GPUStreamTensor2 &, GPUStreamTensor2 &,'%',true,true>::operator()(int index, int block){

	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	GPUDataStream<float44> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Outer product of rank2 stream and rank2 streams
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
        /// can the same memory temp be used again and again???
	GPUDataStream<float> * temp = new GPUDataStream<float>(mList->GetDeviceInterface(),  this->lhs.GetLength(index,block));

	for(int i=0; i<4; i++){
		for(int j=0;j<4; j++){

		  kernelgetfloat_2(mList->GetDeviceInterface(), lstream, i, j, temp);

		  kerneltensormult_0_2(mList->GetDeviceInterface(), temp, rstream, (*this->mstream[index][block])(i,j));

		}
	}
	delete temp;
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float44>* GPUTwoStreamOp<float44, GPUStreamTensor4, GPUStreamTensor2 &, float44,'%',true,false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	// Outer product of rank2 stream and float44
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			kerneltensormult_0i_f44(mList->GetDeviceInterface(), lstream,i,j, this->rhs, (*this->mstream[index][block])(i,j));

		}
	}
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float44>* GPUTwoStreamOp<float44, GPUStreamTensor4, float44, GPUStreamTensor2 &,'%',false,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * rstream = this->rhs(index,block);
	// Outer product of rank2 const and rank2 stream
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->rhs.GetLength(index,block));

	for(int i=0; i<4; i++){
	  for(int j=0; j<4; j++){
	    kerneltensormult_0i_f44(mList->GetDeviceInterface(), rstream,i,j, this->lhs, (*this->mstream[index][block])(i,j));
	  }
	}
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4, GPUStreamTensor3 &, GPUStreamVector &,'%',true,true>::operator()(int index, int block){

	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float444> * lstream = this->lhs(index,block);
	GPUDataStream<float4> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Outer product of rank2 stream and rank2 streams
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
        /// can the same memory temp be used again and again???
	GPUDataStream<float4> * temp = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));

	for(int i=0; i<4; i++){
		for(int j=0;j<4; j++){
		  kernelgetvector_3(mList->GetDeviceInterface(),lstream, i, j, temp);
		  kerneltensorouter_1_1(mList->GetDeviceInterface(),temp, rstream, (*this->mstream[index][block])(i,j));
		}
	}
	delete temp;
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4, GPUStreamTensor3 &, float4,'%',true,false>::operator()(int index, int block){

	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float444> * lstream = this->lhs(index,block);
	// Outer product of rank2 stream and rank2 streams
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
        /// can the same memory temp be used again and again???
	GPUDataStream<float4> * temp = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));

	for(int i=0; i<4; i++){
		for(int j=0;j<4; j++){
		  kernelgetvector_3(mList->GetDeviceInterface(), lstream, i, j, temp);
		  kerneltensorouter_1_f4(mList->GetDeviceInterface(), temp, rhs, (*this->mstream[index][block])(i,j));
		}
	}
	delete temp;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4, float444, GPUStreamVector &,'%',false,true>::operator()(int index, int block){

	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float4> * rstream = this->rhs(index,block);
	// Outer product of rank2 stream and rank2 streams
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->rhs.GetLength(index,block));

	for(int i=0; i<4; i++){
		for(int j=0;j<4; j++){
			float4 v;
			if(i==0 && j==0) v = lhs.cc;
			if(i==0 && j==1) v = lhs.cd;
			if(i==0 && j==2) v = lhs.ce;
			if(i==0 && j==3) v = lhs.cf;

			if(i==1 && j==0) v = lhs.dc;
			if(i==1 && j==1) v = lhs.dd;
			if(i==1 && j==2) v = lhs.de;
			if(i==1 && j==3) v = lhs.df;

			if(i==2 && j==0) v = lhs.ec;
			if(i==2 && j==1) v = lhs.ed;
			if(i==2 && j==2) v = lhs.ee;
			if(i==2 && j==3) v = lhs.ef;

			if(i==3 && j==0) v = lhs.fc;
			if(i==3 && j==1) v = lhs.fd;
			if(i==3 && j==2) v = lhs.fe;
			if(i==3 && j==3) v = lhs.ff;

			kerneltensorouter_f4_1(mList->GetDeviceInterface(), v, rstream, (*this->mstream[index][block])(i,j));
		}
	}
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}




template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4, GPUStreamVector &, GPUStreamTensor3 &,'%',true,true>::operator()(int index, int block){

	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float4> * lstream = this->lhs(index,block);
	GPUDataStream<float444> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	// Outer product of rank2 stream and rank2 streams
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
        /// can the same memory temp be used again and again???
	GPUDataStream<float> * temp1 = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	GPUDataStream<float444> * temp2 = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));

	for(int i=0; i<4; i++){
		kernelgetfloat_1(mList->GetDeviceInterface(),lstream, i, temp1);
		kerneltensormult_0_3(mList->GetDeviceInterface(),temp1, rstream, temp2);
		for(int j=0;j<4; j++){
		  kernelgetfloat44_3(mList->GetDeviceInterface(),temp2, j, (*this->mstream[index][block])(i,j));
		}
	}
	delete temp1;
	delete temp2;
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4, float4, GPUStreamTensor3 &,'%',false,true>::operator()(int index, int block){

	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float444> * rstream = this->rhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->rhs.GetLength(index,block));
        /// can the same memory temp be used again and again???
	GPUDataStream<float444> * temp2 = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));

	for(int i=0; i<4; i++){
		float f=0.0f;
		if(i==0) f = lhs.x;
		if(i==1) f = lhs.y;
		if(i==2) f = lhs.z;
		if(i==3) f = lhs.w;
		kerneltensormult_f_3(mList->GetDeviceInterface(),f, rstream, temp2);
		for(int j=0;j<4; j++){
		  kernelgetfloat44_3(mList->GetDeviceInterface(), temp2, j, (*this->mstream[index][block])(i,j));
		}
	}
	delete temp2;
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4, GPUStreamVector &, float444,'%',true,false>::operator()(int index, int block){

	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float4> * lstream = this->lhs(index,block);


	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));

	GPUDataStream<float> * temp1 = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	GPUDataStream<float444> * temp2 = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));

	for(int i=0; i<4; i++){
		kernelgetfloat_1(mList->GetDeviceInterface(),lstream, i, temp1);
		kerneltensormult_0_f444(mList->GetDeviceInterface(), temp1, rhs, temp2);
		for(int j=0;j<4; j++){
		  kernelgetfloat44_3(mList->GetDeviceInterface(), temp2, j, (*this->mstream[index][block])(i,j));
		}
	}
	delete temp1;
	delete temp2;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float44> * GPUTwoStreamOp<float44, GPUStreamTensor4, GPUStreamTensor2 &, GPUStreamTensor2 &,'#',true,true>::operator()(int index, int block){

	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	GPUDataStream<float44> * rstream = this->rhs(index,block);
	assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
  	for(int i=0; i<4; i++){
		for(int j=0;j<4; j++){
		  kernelspinproject3_2_2(mList->GetDeviceInterface(),lstream, rstream, i,j, (*this->mstream[index][block])(i,j));
		}
	}
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}




 template <typename tt, typename T, int oper, typename A, bool reg> void GPUOneStream<tt, T, oper, A, reg>::assertindex(int index){
		assert(index < (int)this->mlength.size());
	}

 template <typename tt, typename T, int oper, typename A> void GPUOneStream<tt, T, oper, A, true>::assertindex(int index){
		assert(index < this->GetNSets());
	}

 template <typename tt, typename T, int oper, typename A, bool reg> void GPUOneStream<tt, T, oper, A, reg>::IncreaseUsecount(int index){
	 for(unsigned int i =0; i < this->musecount[index].size(); i++){
		this->musecount[index][i]++;
	 	}
 	}

  template <typename tt, typename T, int oper, typename A> void GPUOneStream<tt, T, oper, A, true>::IncreaseUsecount(int index){
	  if(this->musecount[index][0]  < 1){
		  this->lhs.IncreaseUsecount(index);
	  }
	  for(unsigned int i =0; i < this->musecount[index].size(); i++){
		  this->musecount[index][i]++;
	  }
  }


  template <typename tt, typename T, int oper, typename A, bool reg> void GPUOneStream<tt, T, oper, A, reg>::IncreaseUsecount(int index, int block){
	  assert(block < this->musecount[index].size());
	  this->musecount[index][block]++;
  }

    template <typename tt, typename T, int oper, typename A> void GPUOneStream<tt, T, oper, A, true>::IncreaseUsecount(int index, int block){
    	assert(block < (int)this->musecount[index].size());
    	if(this->musecount[index][block]  < 1){
  		  this->lhs.IncreaseUsecount(index,block);
    	}

    	this->musecount[index][block]++;
    }



template<typename tt, typename T, int oper, typename A>
	GPUOneStream<tt, T, oper, A, true>::GPUOneStream(A & _lhs):T(_lhs.GetList()),lhs(_lhs),op(oper){
	}


// Negation
/// Negate a scalar
GPUStreamScalar & operator - (GPUStreamScalar & _lhs){
	return * new GPUOneStreamOp<float, GPUStreamScalar,'-',GPUStreamScalar,true>(_lhs);
}
/// Negate a vector
GPUStreamVector & operator - (GPUStreamVector & _lhs){
	return * new GPUOneStreamOp<float4, GPUStreamVector,'-',GPUStreamVector,true>(_lhs);
}
/// Negate a second rank tensor
GPUStreamTensor2 & operator - (GPUStreamTensor2 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor2,'-',GPUStreamTensor2,true>(_lhs);
}

/// Negate a third rank tensor
GPUStreamTensor3 & operator - (GPUStreamTensor3 & _lhs){
	return * new GPUOneStreamOp<float444, GPUStreamTensor3,'-',GPUStreamTensor3,true>(_lhs);
}

/// Negate a four rank tensor
GPUStreamTensor4 & operator - (GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,'-',GPUStreamTensor4,true>(_lhs);
}



template<> GPUDataStream<float> * GPUOneStreamOp<float, GPUStreamScalar,'-',GPUStreamScalar,true>::operator()(int index, int block){
	assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * lstream = this->lhs(index,block);
	// Negating a stream of floats
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorneg_0(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float4> * GPUOneStreamOp<float4, GPUStreamVector,'-',GPUStreamVector,true>::operator()(int index, int block){
	assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	// Negating a stream of float4s
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorneg_1(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor2,'-',GPUStreamTensor2,true>::operator()(int index, int block){
	assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = lhs(index,block);
	// Negating a stream of float44s
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), lhs.GetLength(index,block));
	kerneltensorneg_2(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float444> * GPUOneStreamOp<float444, GPUStreamTensor3,'-',GPUStreamTensor3,true>::operator()(int index, int block){
	assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = lhs(index,block);
	// Negating a stream of float444s
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), lhs.GetLength(index,block));
	kerneltensorneg_3(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,'-',GPUStreamTensor4,true>::operator()(int index, int block){
	assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = lhs(index,block);
	// Negating a stream of float4444s
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  lhs.GetLength(index,block));
	for(int i = 0; i < 16; i++){
	   kerneltensorneg_2(mList->GetDeviceInterface(), (*lstream)(i), (*this->mstream[index][block])(i));
	}
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}



// Functions of scalars
/// Square root of a scalar
GPUStreamScalar & sqrt(GPUStreamScalar & _lhs){
	return * new GPUOneStreamOp<float, GPUStreamScalar,'r',GPUStreamScalar,true>(_lhs);
}

/// Sine of a scalar
GPUStreamScalar & sin(GPUStreamScalar & _lhs){
	return * new GPUOneStreamOp<float, GPUStreamScalar,'s',GPUStreamScalar,true>(_lhs);
}

/// Cosine of a scalar
GPUStreamScalar & cos(GPUStreamScalar & _lhs){
	return * new GPUOneStreamOp<float, GPUStreamScalar,'c',GPUStreamScalar,true>(_lhs);
}

/// Tangent of a scalar
GPUStreamScalar & tan(GPUStreamScalar & _lhs){
	return * new GPUOneStreamOp<float, GPUStreamScalar,'t',GPUStreamScalar,true>(_lhs);
}

/// Exponentiation of a scalar
GPUStreamScalar & exp(GPUStreamScalar & _lhs){
	return * new GPUOneStreamOp<float, GPUStreamScalar,'e',GPUStreamScalar,true>(_lhs);
}

/// transpose of a float44
GPUStreamTensor2 & trans(GPUStreamTensor2 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor2,'T',GPUStreamTensor2,true>(_lhs);
}


/// five transpose of rank3 tensor
GPUStreamTensor3 & trans_213(GPUStreamTensor3 & _lhs){
	return * new GPUOneStreamOp<float444, GPUStreamTensor3,213,GPUStreamTensor3,true>(_lhs);
}

GPUStreamTensor3 & trans_132(GPUStreamTensor3 & _lhs){
	return * new GPUOneStreamOp<float444, GPUStreamTensor3,132,GPUStreamTensor3,true>(_lhs);
}

GPUStreamTensor3 & trans_231(GPUStreamTensor3 & _lhs){
	return * new GPUOneStreamOp<float444, GPUStreamTensor3,231,GPUStreamTensor3,true>(_lhs);
}

GPUStreamTensor3 & trans_312(GPUStreamTensor3 & _lhs){
	return * new GPUOneStreamOp<float444, GPUStreamTensor3,312,GPUStreamTensor3,true>(_lhs);
}

GPUStreamTensor3 & trans_321(GPUStreamTensor3 & _lhs){
	return * new GPUOneStreamOp<float444, GPUStreamTensor3,321,GPUStreamTensor3,true>(_lhs);
}



// transpose rank4 stream, result is 4123
GPUStreamTensor4 & trans_4123(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,4123,GPUStreamTensor4,true>(_lhs);
}


// transpose rank4 stream, result sequence is 1423
GPUStreamTensor4 & trans_1423(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,1423,GPUStreamTensor4,true>(_lhs);
}


// transpose rank4 stream, result sequence is 1243
GPUStreamTensor4 & trans_1243(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,1243,GPUStreamTensor4,true>(_lhs);
}

// transpose rank4 stream, result sequence is 4213
GPUStreamTensor4 & trans_4213(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,4213,GPUStreamTensor4,true>(_lhs);
}

// transpose rank4 stream, result sequence is 2413
GPUStreamTensor4 & trans_2413(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,2413,GPUStreamTensor4,true>(_lhs);
}


// transpose rank4 stream, result sequence is 2143
GPUStreamTensor4 & trans_2143(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,2143,GPUStreamTensor4,true>(_lhs);
}


// transpose rank4 stream, result sequence is 2134
GPUStreamTensor4 & trans_2134(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,2134,GPUStreamTensor4,true>(_lhs);
}


// transpose rank4 stream, result sequence is 4132
GPUStreamTensor4 & trans_4132(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,4132,GPUStreamTensor4,true>(_lhs);
}


// transpose rank4 stream, result sequence is 1432
GPUStreamTensor4 & trans_1432(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,1432,GPUStreamTensor4,true>(_lhs);
}


// transpose rank4 stream, result sequence is 1342
GPUStreamTensor4 & trans_1342(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,1342,GPUStreamTensor4,true>(_lhs);
}


// transpose rank4 stream, result sequence is 1324
GPUStreamTensor4 & trans_1324(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,1324,GPUStreamTensor4,true>(_lhs);
}

// transpose rank4 stream, result sequence is 4231
GPUStreamTensor4 & trans_4231(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,4231,GPUStreamTensor4,true>(_lhs);
}

// transpose rank4 stream, result sequence is 2431
GPUStreamTensor4 & trans_2431(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,2431,GPUStreamTensor4,true>(_lhs);
}


// transpose rank4 stream, result sequence is 2341
GPUStreamTensor4 & trans_2341(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,2341,GPUStreamTensor4,true>(_lhs);
}


// transpose rank4 stream, result sequence is 2314
GPUStreamTensor4 & trans_2314(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,2314,GPUStreamTensor4,true>(_lhs);
}

// transpose rank4 stream, result sequence is 4312
GPUStreamTensor4 & trans_4312(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,4312,GPUStreamTensor4,true>(_lhs);
}

// transpose rank4 stream, result sequence is 3412
GPUStreamTensor4 & trans_3412(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,3412,GPUStreamTensor4,true>(_lhs);
}

// transpose rank4 stream, result sequence is 3142
GPUStreamTensor4 & trans_3142(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,3142,GPUStreamTensor4,true>(_lhs);
}

// transpose rank4 stream, result sequence is 3124
GPUStreamTensor4 & trans_3124(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,3124,GPUStreamTensor4,true>(_lhs);
}

// transpose rank4 stream, result sequence is 4321
GPUStreamTensor4 & trans_4321(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,4321,GPUStreamTensor4,true>(_lhs);
}

// transpose rank4 stream, result sequence is 3421
GPUStreamTensor4 & trans_3421(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,3421,GPUStreamTensor4,true>(_lhs);
}

 //transpose rank4 stream, result sequence is 3241
GPUStreamTensor4 & trans_3241(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,3241,GPUStreamTensor4,true>(_lhs);
}

// transpose rank4 stream, result sequence is 3214
GPUStreamTensor4 & trans_3214(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,3214,GPUStreamTensor4,true>(_lhs);
}



GPUConstTensor4 & trans_4123(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_4123(_lhs()));
}

GPUConstTensor4 & trans_1423(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_1423(_lhs()));
}

GPUConstTensor4 & trans_1243(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_1243(_lhs()));
}
//GPUConstTensor4 & trans_1234(GPUConstTensor4 & _lhs);

GPUConstTensor4 & trans_4213(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_4213(_lhs()));
}

GPUConstTensor4 & trans_2413(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_2413(_lhs()));
}

GPUConstTensor4 & trans_2143(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_2143(_lhs()));
}

GPUConstTensor4 & trans_2134(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_2134(_lhs()));
}

GPUConstTensor4 & trans_4132(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_4132(_lhs()));
}

GPUConstTensor4 & trans_1432(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_1432(_lhs()));
}

GPUConstTensor4 & trans_1342(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_1342(_lhs()));
}

GPUConstTensor4 & trans_1324(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_1324(_lhs()));
}

GPUConstTensor4 & trans_4231(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_4231(_lhs()));
}

GPUConstTensor4 & trans_2431(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_2431(_lhs()));
}

GPUConstTensor4 & trans_2341(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_2341(_lhs()));
}

GPUConstTensor4 & trans_2314(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_2314(_lhs()));
}

GPUConstTensor4 & trans_4312(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_4312(_lhs()));
}

GPUConstTensor4 & trans_3412(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_3412(_lhs()));
}

GPUConstTensor4 & trans_3142(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_3142(_lhs()));
}

GPUConstTensor4 & trans_3124(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_3124(_lhs()));
}

GPUConstTensor4 & trans_4321(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_4321(_lhs()));
}

GPUConstTensor4 & trans_3421(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_3421(_lhs()));
}

GPUConstTensor4 & trans_3241(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_3241(_lhs()));
}

GPUConstTensor4 & trans_3214(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(transpose_3214(_lhs()));
}



///
GPUStreamVector & moveindex(GPUStreamVector & _lhs){
	return * new GPUOneStreamOp<float4, GPUStreamVector,'0',GPUStreamVector,true>(_lhs);
}

GPUStreamTensor2 & movefirstindex(GPUStreamTensor2 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor2,'0',GPUStreamTensor2,true>(_lhs);
}

GPUStreamTensor2 & movelastindex(GPUStreamTensor2 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor2,'1',GPUStreamTensor2,true>(_lhs);
}

GPUStreamTensor2 & moveindices(GPUStreamTensor2 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor2,'_',GPUStreamTensor2,true>(_lhs);
}

GPUStreamTensor3 & moveindices(GPUStreamTensor3 & _lhs){
	return * new GPUOneStreamOp<float444, GPUStreamTensor3,'_',GPUStreamTensor3,true>(_lhs);
}

GPUStreamTensor3 & movefirstindex(GPUStreamTensor3 & _lhs){
	return * new GPUOneStreamOp<float444, GPUStreamTensor3,'0',GPUStreamTensor3,true>(_lhs);
}

GPUStreamTensor3 & movemiddleindex(GPUStreamTensor3 & _lhs){
	return * new GPUOneStreamOp<float444, GPUStreamTensor3,'1',GPUStreamTensor3,true>(_lhs);
}

GPUStreamTensor3 & movelastindex(GPUStreamTensor3 & _lhs){
	return * new GPUOneStreamOp<float444, GPUStreamTensor3,'2',GPUStreamTensor3,true>(_lhs);
}


GPUStreamTensor4 & movelastindex(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,'3',GPUStreamTensor4,true>(_lhs);
}

GPUStreamTensor4 & moveindices(GPUStreamTensor4 & _lhs){
	return * new GPUOneStreamOp<float44, GPUStreamTensor4,')',GPUStreamTensor4,true>(_lhs);
}



GPUConstVector & moveindex(GPUConstVector & _lhs){
	return * new GPUConstVector(moveindex(_lhs()));
}

GPUConstTensor2 & movefirstindex(GPUConstTensor2 & _lhs){
	return * new GPUConstTensor2(movefirstindex(_lhs()));
}

GPUConstTensor2 & movelastindex(GPUConstTensor2 & _lhs){
	return * new GPUConstTensor2(movelastindex(_lhs()));
}

GPUConstTensor2 & moveindices(GPUConstTensor2 & _lhs){
	return * new GPUConstTensor2(moveindices(_lhs()));
}

GPUConstTensor3 & moveindices(GPUConstTensor3 & _lhs){
	return * new GPUConstTensor3(moveindices(_lhs()));
}


GPUConstTensor3 & movefirstindex(GPUConstTensor3 & _lhs){
	return * new GPUConstTensor3(movefirstindex(_lhs()));
}

GPUConstTensor3 & movemiddleindex(GPUConstTensor3 & _lhs){
	return * new GPUConstTensor3(movemiddleindex(_lhs()));
}

GPUConstTensor3 & movemlastindex(GPUConstTensor3 & _lhs){
	return * new GPUConstTensor3(movelastindex(_lhs()));
}


GPUConstTensor4 & movelastindex(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(movelastindex(_lhs()));
}

GPUConstTensor4 & moveindices(GPUConstTensor4 & _lhs){
	return * new GPUConstTensor4(moveindices(_lhs()));
}


template<> GPUDataStream<float> * GPUOneStreamOp<float, GPUStreamScalar,'r',GPUStreamScalar,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * lstream = this->lhs(index,block);
	// Square root of a stream of floats
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorsqrt_0(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float> * GPUOneStreamOp<float, GPUStreamScalar,'s',GPUStreamScalar,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * lstream = this->lhs(index,block);
	// Sine of a stream of floats
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorsin_0(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float> * GPUOneStreamOp<float, GPUStreamScalar,'c',GPUStreamScalar,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * lstream = this->lhs(index,block);
	// Cosine of a stream of floats
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorcos_0(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float> * GPUOneStreamOp<float, GPUStreamScalar,'t',GPUStreamScalar,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * lstream = this->lhs(index,block);
	// Tangent of a stream of floats
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensortan_0(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float> * GPUOneStreamOp<float, GPUStreamScalar,'e',GPUStreamScalar,true>::operator()(int index, int block){

//	std::cout<<" hi, in GPUOneStreamOp<float, GPUStreamScalar,'e'>::operator()(int index, int block):  "<<std::endl;
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float> * lstream = this->lhs(index,block);
	// Exponentiation of a stream of floats
	this->mstream[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensorexp_0(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor2,'T',GPUStreamTensor2,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	//
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensortrans_2(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}



/// transpose rank3 stream, result sequence is 213
template<> GPUDataStream<float444> * GPUOneStreamOp<float444, GPUStreamTensor3,213,GPUStreamTensor3,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensortrans_3_213(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


/// transpose rank3 stream, result sequence is 132
template<> GPUDataStream<float444> * GPUOneStreamOp<float444, GPUStreamTensor3,132,GPUStreamTensor3,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kerneltensortrans_3_132(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


/// transpose rank3 stream, result sequence is 231
template<> GPUDataStream<float444> * GPUOneStreamOp<float444, GPUStreamTensor3,231,GPUStreamTensor3,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	GPUDataStream<float444>* temp = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));

	kerneltensortrans_3_213(mList->GetDeviceInterface(), lstream, temp);

	kerneltensortrans_3_132(mList->GetDeviceInterface(), temp, this->mstream[index][block]);

	delete temp;
    this->lhs.DecreaseUsecount(index,block);
    return this->mstream[index][block];
}


/// transpose rank3 stream, result sequence is 312
template<> GPUDataStream<float444> * GPUOneStreamOp<float444, GPUStreamTensor3,312,GPUStreamTensor3,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	GPUDataStream<float444>* temp = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));

	kerneltensortrans_3_132(mList->GetDeviceInterface(), lstream, temp);
	kerneltensortrans_3_213(mList->GetDeviceInterface(), temp, this->mstream[index][block]);

	delete temp;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


/// transpose rank3 stream, result sequence is 321
template<> GPUDataStream<float444> * GPUOneStreamOp<float444, GPUStreamTensor3,321,GPUStreamTensor3,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	GPUDataStream<float444>* temp1 = new GPUDataStream<float444>(mList->GetDeviceInterface(),  this->lhs.GetLength(index,block));

	kerneltensortrans_3_132(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);

	kerneltensortrans_3_213(mList->GetDeviceInterface(), this->mstream[index][block], temp1);

	kerneltensortrans_3_132(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	this->lhs.DecreaseUsecount(index,block);
	delete temp1;
	//delete temp2;

	return this->mstream[index][block];
}



// transpose rank4 stream, result sequence is 4123
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,4123,GPUStreamTensor4,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));

	transpose_1243(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	transpose_1324(mList->GetDeviceInterface(), this->mstream[index][block], temp1);
	transpose_2134(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);
	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}



// transpose rank4 stream, result sequence is 1423
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,1423,GPUStreamTensor4,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(),  0, 16, this->lhs.GetLength(index,block));
	transpose_1243(mList->GetDeviceInterface(), lstream, temp1);
	transpose_1324(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


// transpose rank4 stream, result sequence is 1243
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,1243,GPUStreamTensor4,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	transpose_1243(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


// transpose rank4 stream, result sequence is 4213
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,4213,GPUStreamTensor4,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));

	transpose_1243(mList->GetDeviceInterface(), lstream, temp1);
	transpose_2134(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);
	transpose_1324(mList->GetDeviceInterface(), this->mstream[index][block], temp1);
	transpose_2134(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);
	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}



// transpose rank4 stream, result sequence is 2413
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,2413,GPUStreamTensor4,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp2 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	transpose_2134(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	transpose_1243(mList->GetDeviceInterface(), this->mstream[index][block], temp2);
	transpose_1324(mList->GetDeviceInterface(), temp2, this->mstream[index][block]);

	delete temp2;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


// transpose rank4 stream, result sequence is 2143
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,2143,GPUStreamTensor4,true>::operator()(int index, int block){

	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	transpose_1243(mList->GetDeviceInterface(), lstream, temp1);
	transpose_2134(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

// transpose rank4 stream, result sequence is 2134
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,2134,GPUStreamTensor4,true>::operator()(int index, int block){
this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));

	transpose_2134(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);

	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


// transpose rank4 stream, result sequence is 4132
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,4132,GPUStreamTensor4,true>::operator()(int index, int block){

	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	transpose_1324(mList->GetDeviceInterface(), lstream, temp1);

	transpose_1243(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	transpose_1324(mList->GetDeviceInterface(), this->mstream[index][block], temp1);

	transpose_2134(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

// transpose rank4 stream, result sequence is 1432
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,1432,GPUStreamTensor4,true>::operator()(int index, int block){

	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	transpose_1243(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);

	transpose_1324(mList->GetDeviceInterface(), this->mstream[index][block], temp1);

	transpose_1243(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


// transpose rank4 stream, result sequence is 1342
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,1342,GPUStreamTensor4,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	transpose_1324(mList->GetDeviceInterface(), lstream, temp1);

	transpose_1243(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);
	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


void transpose_1324(const DeviceInterface * dev, GPUDataStream<float44>* lstream, GPUDataStream<float44>* rstream){
  for(int i=0; i<4; i++){
    kerneltensorassign_c(dev, (*lstream)(i,0), (*lstream)(i,1), (*lstream)(i,2), (*lstream)(i,3), (*rstream)(i,0));
    kerneltensorassign_d(dev, (*lstream)(i,0), (*lstream)(i,1), (*lstream)(i,2), (*lstream)(i,3), (*rstream)(i,1));
    kerneltensorassign_e(dev, (*lstream)(i,0), (*lstream)(i,1), (*lstream)(i,2), (*lstream)(i,3), (*rstream)(i,2));
    kerneltensorassign_f(dev, (*lstream)(i,0), (*lstream)(i,1), (*lstream)(i,2), (*lstream)(i,3), (*rstream)(i,3));

  }
}


void transpose_1243(const DeviceInterface * dev, GPUDataStream<float44>* lstream, GPUDataStream<float44>* rstream){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			kerneltensortrans_2(dev, (*lstream)(i,j), (*rstream)(i,j));
		}
	}
}



void transpose_2134(const DeviceInterface * dev, GPUDataStream<float44>* lstream, GPUDataStream<float44>* rstream){
  for(int i=0; i < 4; i++){
    for(int j=0; j < 4; j++){
      kerneltensorcopy_2(dev, (*lstream)(i,j), (*rstream)(j,i));
    }
  }
}


// transpose rank4 stream, result sequence is 1324
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,1324,GPUStreamTensor4,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);

	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	transpose_1324(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


// transpose rank4 stream, result sequence is 4231
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,4231,GPUStreamTensor4,true>::operator()(int index, int block){
			this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));

	transpose_2134(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	transpose_1324(mList->GetDeviceInterface(), this->mstream[index][block], temp1);
	transpose_1243(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);
	transpose_1324(mList->GetDeviceInterface(), this->mstream[index][block], temp1);
	transpose_2134(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


// transpose rank4 stream, result sequence is 2431
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,2431,GPUStreamTensor4,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));

	transpose_2134(mList->GetDeviceInterface(), lstream, temp1);
	transpose_1324(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);
	transpose_1243(mList->GetDeviceInterface(), this->mstream[index][block], temp1);
	transpose_1324(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


// transpose rank4 stream, result sequence is 2341
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,2341,GPUStreamTensor4,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	transpose_2134(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	transpose_1324(mList->GetDeviceInterface(), this->mstream[index][block], temp1);
	transpose_1243(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);
	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


// transpose rank4 stream, result sequence is 2314
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,2314,GPUStreamTensor4,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	transpose_2134(mList->GetDeviceInterface(), lstream, temp1);
	transpose_1324(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);
	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


// transpose rank4 stream, result sequence is 4312
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,4312,GPUStreamTensor4,true>::operator()(int index, int block){

	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));

	transpose_1243(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	transpose_1324(mList->GetDeviceInterface(), this->mstream[index][block], temp1);
	transpose_2134(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);
	transpose_1243(mList->GetDeviceInterface(), this->mstream[index][block], temp1);
	transpose_1324(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);
	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

// transpose rank4 stream, result sequence is 3412

template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,3412,GPUStreamTensor4,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));

	transpose_1324(mList->GetDeviceInterface(), lstream, temp1);

	transpose_2134(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	transpose_1243(mList->GetDeviceInterface(), this->mstream[index][block], temp1);

	transpose_1324(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	delete temp1;

	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


// transpose rank4 stream, result sequence is 3142
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,3142,GPUStreamTensor4,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));

	transpose_1324(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);

	transpose_2134(mList->GetDeviceInterface(), this->mstream[index][block], temp1);

	transpose_1243(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}



// transpose rank4 stream, result sequence is 3124
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,3124,GPUStreamTensor4,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,this->lhs.GetLength(index,block));
	transpose_1324(mList->GetDeviceInterface(), lstream, temp1);

	transpose_2134(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


// transpose rank4 stream, result sequence is 4321
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,4321,GPUStreamTensor4,true>::operator()(int index, int block){

	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));

	transpose_1243(mList->GetDeviceInterface(), lstream, temp1);

	transpose_1324(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	transpose_2134(mList->GetDeviceInterface(), this->mstream[index][block], temp1);

	transpose_1243(mList->GetDeviceInterface(), temp1,  this->mstream[index][block]);

	transpose_1324(mList->GetDeviceInterface(),  this->mstream[index][block], temp1);

	transpose_1243(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);


	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


// transpose rank4 stream, result sequence is 3421
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,3421,GPUStreamTensor4,true>::operator()(int index, int block){
	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));

	transpose_1324(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	transpose_2134(mList->GetDeviceInterface(), this->mstream[index][block], temp1);
	transpose_1243(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);
	transpose_1324(mList->GetDeviceInterface(), this->mstream[index][block], temp1);
	transpose_1243(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

 //transpose rank4 stream, result sequence is 3241
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,3241,GPUStreamTensor4,true>::operator()(int index, int block){

	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));

	transpose_2134(mList->GetDeviceInterface(), lstream, temp1);

	transpose_1324(mList->GetDeviceInterface(), temp1,  this->mstream[index][block]);

	transpose_1243(mList->GetDeviceInterface(), this->mstream[index][block], temp1);

	transpose_2134(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


// transpose rank4 stream, result sequence is 3214
template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,3214,GPUStreamTensor4,true>::operator()(int index, int block){

	this->assertindex(index);
	if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	GPUDataStream<float44>* temp1 = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	transpose_1324(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);

	transpose_2134(mList->GetDeviceInterface(), this->mstream[index][block], temp1);

	transpose_1324(mList->GetDeviceInterface(), temp1, this->mstream[index][block]);

	delete temp1;
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}



template<> GPUDataStream<float4> * GPUOneStreamOp<float4, GPUStreamVector,'0',GPUStreamVector,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float4> * lstream = this->lhs(index,block);
	// Square root of a stream of floats
	this->mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kernelmoveindex_1(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);
	//this->mstream[index][block]->error();
	//this->mlength[index][block] = this->lhs.GetLength(index,block);
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor2,'0',GPUStreamTensor2,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	// Square root of a stream of floats
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kernelmovefirstindex_2(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);

	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor2,'1',GPUStreamTensor2,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	// Square root of a stream of floats
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kernelmovelastindex_2(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);

	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor2,'_',GPUStreamTensor2,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float44> * lstream = this->lhs(index,block);
	// Square root of a stream of floats
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kernelmoveindices_2(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);

	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUOneStreamOp<float444, GPUStreamTensor3,'_',GPUStreamTensor3,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);

	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kernelmoveindices_3(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);

	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUOneStreamOp<float444, GPUStreamTensor3,'0',GPUStreamTensor3,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	// Square root of a stream of floats
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kernelmovefirstindex_3(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);

	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUOneStreamOp<float444, GPUStreamTensor3,'1',GPUStreamTensor3,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	// Square root of a stream of floats
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kernelmovemiddleindex_3(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);

	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

template<> GPUDataStream<float444> * GPUOneStreamOp<float444, GPUStreamTensor3,'2',GPUStreamTensor3,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	Stream<float444> * lstream = this->lhs(index,block);
	// Square root of a stream of floats
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	kernelmovelastindex_3(mList->GetDeviceInterface(), lstream, this->mstream[index][block]);

	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float44> * GPUOneStreamOp<float44, GPUStreamTensor4,'3',GPUStreamTensor4,true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	for(int i=0; i<4; i++){
	  for(int j=0; j<4; j++){
	    kernelmovelastindex_2(mList->GetDeviceInterface(), (*lstream)(i,j), (*this->mstream[index][block])(i,j));
	  }
	}
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float44>* GPUOneStreamOp<float44, GPUStreamTensor4,')',GPUStreamTensor4, true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	GPUDataStream<float44> * lstream = this->lhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16,  this->lhs.GetLength(index,block));
	for(int i=0; i<4; i++){
	  for(int j=0; j<4; j++){
	    kernelmoveindices_2(mList->GetDeviceInterface(), (*lstream)(i,j), (*this->mstream[index][block])(i,j));
	  }
	}
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


GPUStreamTensor4 & spin4orbitaltensor(GPUStreamVector & rtilde, GPUStreamTensor2 & delp){
  return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamVector&,GPUStreamTensor2&,4444,true,true>(rtilde,delp);
}

GPUStreamTensor4 & spin4orbitaltensor(GPUStreamVector & rtilde, GPUConstTensor2 & delp){
  float44 temp = delp();
  return * new GPUTwoStreamOp<float44, GPUStreamTensor4,GPUStreamVector&,float44,4444,true,false>(rtilde,temp);
}

template<> GPUDataStream<float44>*  GPUTwoStreamOp<float44,GPUStreamTensor4,GPUStreamVector&,GPUStreamTensor2&,4444,true,true>::operator()(int index, int block){

  this->assertindex(index);
  if(this->mstream[index][block]) return this->mstream[index][block];

  GPUDataStream<float4> *    rtstream = this->lhs(index,block);
  GPUDataStream<float44> * delpstream = this->rhs(index,block);

  assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
  this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));

  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      kernel4orbitaltensor(mList->GetDeviceInterface(), rtstream, i, j, delpstream, (*this->mstream[index][block])(i,j));
    }
  }
  this->lhs.DecreaseUsecount(index,block);
  this->rhs.DecreaseUsecount(index,block);
  return this->mstream[index][block];
}



template<> GPUDataStream<float44>*  GPUTwoStreamOp<float44,GPUStreamTensor4,GPUStreamVector&, float44,4444,true,false>::operator()(int index, int block){

  this->assertindex(index);
  if(this->mstream[index][block]) return this->mstream[index][block];

  GPUDataStream<float4> *    rtstream = this->lhs(index,block);


  this->mstream[index][block] = new GPUDataStream<float44>(mList->GetDeviceInterface(), 0, 16, this->lhs.GetLength(index,block));

  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      kernel4orbitaltensorconst(mList->GetDeviceInterface(), rtstream, i, j, this->rhs, (*this->mstream[index][block])(i,j));

    }
  }
  this->lhs.DecreaseUsecount(index,block);
  return this->mstream[index][block];
}




GPUStreamTensor3 & spin3orbitaltensor(GPUStreamVector & rtilde, GPUStreamVector & pa){
  return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamVector&,GPUStreamVector&, 3333,true,true>(rtilde,pa);
}

GPUStreamTensor3 & spin3orbitaltensor(GPUStreamVector & rtilde, GPUConstVector & pa){
  float4 temp = pa();
  return * new GPUTwoStreamOp<float444, GPUStreamTensor3,GPUStreamVector&,float4,3333,true,false>(rtilde,temp);
}

template<> GPUDataStream<float444>*  GPUTwoStreamOp<float444,GPUStreamTensor3,GPUStreamVector&,GPUStreamVector&,3333,true,true>::operator()(int index, int block){

  this->assertindex(index);
  if(this->mstream[index][block]) return this->mstream[index][block];

  GPUDataStream<float4> *    rtstream = this->lhs(index,block);
  GPUDataStream<float4> * 	 pastream = this->rhs(index,block);

  assert(this->lhs.GetLength(index,block)==this->rhs.GetLength(index,block));
  this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(),this->lhs.GetLength(index,block));

  kernel3orbitaltensor(mList->GetDeviceInterface(), rtstream, pastream, (this->mstream[index][block]));

  this->lhs.DecreaseUsecount(index,block);
  this->rhs.DecreaseUsecount(index,block);
  return this->mstream[index][block];
}



template<> GPUDataStream<float444>*  GPUTwoStreamOp<float444,GPUStreamTensor3,GPUStreamVector&, float4,3333,true,false>::operator()(int index, int block){

  this->assertindex(index);
  if(this->mstream[index][block]) return this->mstream[index][block];

  GPUDataStream<float4> *    rtstream = this->lhs(index,block);

  this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));

   kernel3orbitaltensorconst(mList->GetDeviceInterface(), rtstream, this->rhs, (this->mstream[index][block]));

  this->lhs.DecreaseUsecount(index,block);
  //this->mlength[index][block] = this->lhs.GetLength(index,block);
  return this->mstream[index][block];
}


template<> GPUDataStream<float444>*  GPUTwoStreamOp<float444, GPUStreamTensor3, float4, GPUStreamTensor4 &,'|',false, true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	// Contracting Tensor4 stream with const Tensor3
	GPUDataStream<float44> * rstream = this->rhs(index,block);
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
	GPUDataStream<float4> * temp[16];
	for(int i=0; i<16; i++){
	  temp[i] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->rhs.GetLength(index,block));
	  kerneltensorcontract_2_f4(mList->GetDeviceInterface(), (*rstream)(i), this->lhs, (temp[i]));
	}
	kerneltensormake_3(mList->GetDeviceInterface(), (temp[0]), (temp[1]), (temp[2]), (temp[3]),
			   (temp[4]), (temp[5]), (temp[6]), (temp[7]),
			   (temp[8]), (temp[9]), (temp[10]), (temp[11]),
			   (temp[12]), (temp[13]), (temp[14]), (temp[15]), this->mstream[index][block]);
	for(int i=0; i<16; i++){
	  delete temp[i];
	}

	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float444>*  GPUTwoStreamOp<float444, GPUStreamTensor3, GPUStreamVector &, GPUStreamTensor4 &,'|',true, true>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	GPUDataStream<float4> * lstream = this->lhs(index,block);
	GPUDataStream<float44> * rstream = this->rhs(index,block);
	GPUDataStream<float4> * temp[16];
	for(int i=0; i<16; i++){
	  temp[i] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	  kerneltensorcontract_2_1(mList->GetDeviceInterface(), (*rstream)(i), lstream, (temp[i]));
	}
	kerneltensormake_3(mList->GetDeviceInterface(),(temp[0]), (temp[1]), (temp[2]), (temp[3]),
			   (temp[4]), (temp[5]), (temp[6]), (temp[7]),
			   (temp[8]), (temp[9]), (temp[10]), (temp[11]),
			   (temp[12]), (temp[13]), (temp[14]), (temp[15]), this->mstream[index][block]);
	for(int i=0; i<16; i++){
	  delete temp[i];
	}
	this->lhs.DecreaseUsecount(index,block);
	this->rhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}


template<> GPUDataStream<float444>*  GPUTwoStreamOp<float444, GPUStreamTensor3, GPUStreamVector &,  float4444,'|',true, false>::operator()(int index, int block){
	this->assertindex(index); if(this->mstream[index][block]) return this->mstream[index][block];
	this->mstream[index][block] = new GPUDataStream<float444>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	GPUDataStream<float4> * lstream = this->lhs(index,block);
	GPUDataStream<float4> * temp[16];
	for(int i=0; i<16; i++){
	  temp[i] = new GPUDataStream<float4>(mList->GetDeviceInterface(), this->lhs.GetLength(index,block));
	  kerneltensorcontract_f44_1(mList->GetDeviceInterface(), rhs(i), lstream, (temp[i]));
	}
	kerneltensormake_3(mList->GetDeviceInterface(), (temp[0]), (temp[1]), (temp[2]), (temp[3]),
			   (temp[4]), (temp[5]), (temp[6]), (temp[7]),
			   (temp[8]), (temp[9]), (temp[10]), (temp[11]),
			   (temp[12]), (temp[13]), (temp[14]), (temp[15]), this->mstream[index][block]);
	for(int i=0; i<16; i++){
	  delete temp[i];
	}
	this->lhs.DecreaseUsecount(index,block);
	return this->mstream[index][block];
}

