/// \file GPUComputedTensor.h

#ifndef GPU_Computed_Tensor_H
#define GPU_Computed_Tensor_H
#include "GPUStreamTensor.h"
#include "GPUConstTensor.h"
#include "GPUTensor.h"
#include "GPUDataDependentObjectType.h"

#ifdef USECPU
#include "Tensors_cpu.h"
using namespace Tensors_CPU;
#else
#include "Tensors.h"
using namespace Tensors_GPU;
#endif

class DeviceInterface;

/// Template class implementing an operation involving two GPUTensors
/** Through template specialization, GPUPWA implements all the tensor
 *  operations involving streams on the GPU.
 *
 *  The class also implements the Tensor caching mechanism: A call to
 *  IncreaseUsecount() will increase the usecount of the instance by one.
 *  If the usecount was zero before, the IncreaseUsecount() methods of
 *  the arguments will also be called. On the first call of operator(index, block),
 *  GPUTwoStreamOpBase will perform the calculation required, usually calling the
 *  operator() methods of the arguments. The result is cached. Every time operator()
 *  is called, the usecount is decreased by one. If the usecount reaches 0, the cached
 *  stream is deleted. Separate usecounts are kept for each index and block.
 *
 */
template<typename tt, ///< Base type of the result (float, float44, float444, float4444)
		 typename T,  ///< Stream type of the result (GPUDataStream<tt>), present for historical reasons
		 typename L,  ///< Stream type (if stream) or base type (if const) of the left hand argument
		 typename R,  ///< Stream type (if stream) or base type (if const) of the right hand argument
		 int oper, 	  ///< Integer denoting the operation to be performed, if possible we use the ASCII code of the corresponding char (+,-,* etc.)
		 bool regL=false, ///< Boolean denoting whether the left hand argument is a GPUDataDependentObject
		 bool regR=false ///< Boolean denoting whether the left hand argument is a GPUDataDependentObject
		 >
class GPUTwoStreamOpBase: public T
{
public:
	/// Constructor
	GPUTwoStreamOpBase(L _lhs, R _rhs);
	/// Destructor
	virtual ~GPUTwoStreamOpBase(void){};
	/// Do the calculation!
	virtual GPUDataStream<tt> * operator()(int index =0, int block =0);
	/// Increase the usecount at an index (caching mechanism)
	virtual void IncreaseUsecount(int index);
	/// Increase the usecount at a block and index (caching mechanism)
	virtual void IncreaseUsecount(int index, int block);
protected:
	/// Check the range of the index
	virtual void assertindex(int index);
	/// Left hand operand
	L lhs;
	/// Right hand operand
	R rhs;
	/// Integer designating the operation
	const int op;
};




template<typename tt, typename T, typename L, typename R, int oper, bool regL=false, bool regR=false>
class GPUTwoStreamOp: public GPUTwoStreamOpBase<tt,T,L,R,oper,regL,regR>
{
public:
	/// Constructors
	GPUTwoStreamOp(L  _lhs, R  _rhs):GPUTwoStreamOpBase<tt,T,L,R,oper,regL,regR>(_lhs,_rhs){};
	/// Destructor
	virtual ~GPUTwoStreamOp(void){};
		/// Do the calculation!
	virtual GPUDataStream<tt> * operator()(int index =0, int block=0);
};

template<typename tt, typename T, typename L, typename R, int oper>
class GPUTwoStreamOpBase<tt, T, L, R, oper, true, false>: public T
{
public:
	/// Constructors
	GPUTwoStreamOpBase(L  _lhs, R  _rhs);
	/// Destructor
	virtual ~GPUTwoStreamOpBase(void){};
	/// Do the calculation!
	virtual GPUDataStream<tt> * operator()(int index =0, int block=0)=0;
	/// Increase the usecount
	virtual void IncreaseUsecount(int index);
	/// Increase the usecount
	virtual void IncreaseUsecount(int index, int block);
protected:
	/// Ensure index is within range
	virtual void assertindex(int index);
	/// Left hand operand
	L lhs;
	/// Right hand operand
	R rhs;
	/// Integer designating the operation
	const int op;

};

template<typename tt, typename T, typename L, typename R, int oper>
class GPUTwoStreamOpBase<tt, T, L, R, oper, false, true>: public T
{
public:
	/// Constructors
	GPUTwoStreamOpBase(L  _lhs, R  _rhs);
	/// Destructor
	virtual ~GPUTwoStreamOpBase(void){};
	/// Do the calculation!
	virtual GPUDataStream<tt> * operator()(int index =0, int block =0)=0;
	/// Increase the usecount
	virtual void IncreaseUsecount(int index);
	/// Increase the usecount
	virtual void IncreaseUsecount(int index, int block);
protected:
	/// Ensure index is within range
	virtual void assertindex(int index);
	/// Left hand operand
	L lhs;
	/// Right hand operand
	R rhs;
	/// Integer designating the operation
	const int op;

};


template<typename tt, typename T, typename L, typename R, int oper>
class GPUTwoStreamOpBase<tt, T, L, R, oper, true, true>: public T
{
public:
	/// Constructors
	GPUTwoStreamOpBase(L  _lhs, R  _rhs);
	/// Destructor
	virtual ~GPUTwoStreamOpBase(void){};
	/// Do the calculation!
	virtual GPUDataStream<tt> * operator()(int index =0, int block=0) =0;
	/// Increase the usecount
	virtual void IncreaseUsecount(int index);
	/// Increase the usecount
	virtual void IncreaseUsecount(int index, int block);
protected:
	/// Ensure index is within range
	virtual void assertindex(int index);
	/// Left hand operand
	L lhs;
	/// Right hand operand
	R rhs;
	/// Integer designating the operation
	const int op;

};


//------------Lorentz transformation----------------------------------//
/// Lorentz boost.
/** Boost _lhs into the rest system of _rhs**/
GPUStreamVector & lorentzboost  (GPUStreamVector & _lhs, GPUStreamVector & _rhs);
/// Lorentz rotation
GPUStreamVector & lorentzrotation  (GPUStreamVector & _lhs, GPUStreamVector & _rhs);
/// Angle of the transverse (xy) part of the vector with the x axis
GPUStreamScalar & phi  (GPUStreamVector & _lhs);
/// Angle of the vector with the z axis
GPUStreamScalar & costheta  (GPUStreamVector & _lhs);
//---------------------------Addition-------------------------------//

/// Add two scalars
GPUStreamScalar & operator+  (GPUStreamScalar & _lhs, GPUStreamScalar & _rhs);

/// Add a scalar and a float
GPUStreamScalar & operator+  (GPUStreamScalar & _lhs,  float _rhs);
/// Add a scalar and a float
GPUStreamScalar & operator+  ( float _lhs, GPUStreamScalar & _rhs);
/// Add a scalar and a float
GPUStreamScalar & operator+  (GPUStreamScalar & _lhs, GPUConstScalar & _rhs);
/// Add a scalar and a float
GPUStreamScalar & operator+  (GPUConstScalar & _lhs, GPUStreamScalar & _rhs);

/// Add const objects of the same type
template <typename T>
GPUConstTensor<T> & operator+  (GPUConstTensor<T> & _lhs, GPUConstTensor<T> & _rhs){
	return * new GPUConstTensor<T>(_lhs()+_rhs());
}
/// Add const objects of the same type
template <typename T>
GPUConstTensor<T> & operator+  (GPUConstTensor<T> & _lhs,  T _rhs){
	return * new GPUConstTensor<T>(_lhs()+_rhs);
}
/// Add const objects of the same type
template <typename T>
GPUConstTensor<T> & operator+  ( T _lhs, GPUConstTensor<T> & _rhs){
	return * new GPUConstTensor<T>(_lhs+_rhs());
}

/// Add two vectors
GPUStreamVector & operator+  (GPUStreamVector & _lhs, GPUStreamVector & _rhs);
/// Add a vector and a float4
GPUStreamVector & operator+  (GPUStreamVector & _lhs,  float4 _rhs);
/// Add a vector and a float4
GPUStreamVector & operator+  ( float4 _lhs, GPUStreamVector & _rhs);
/// Add a vector and a float4
GPUStreamVector & operator+  (GPUStreamVector & _lhs, GPUConstVector & _rhs);
/// Add a vector and a float4
GPUStreamVector & operator+  (GPUConstVector & _lhs, GPUStreamVector & _rhs);

/// Add two second rank tensors
GPUStreamTensor2 & operator+  (GPUStreamTensor2 & _lhs, GPUStreamTensor2 & _rhs);
/// Add a second rank tensor and a float44
GPUStreamTensor2 & operator+  (GPUStreamTensor2 & _lhs,  float44  _rhs);
/// Add a second rank tensor and a float44
GPUStreamTensor2 & operator+  ( float44  _lhs, GPUStreamTensor2 & _rhs);
/// Add a second rank tensor and a float44
GPUStreamTensor2 & operator+  (GPUStreamTensor2 & _lhs, GPUConstTensor2 & _rhs);
/// Add a second rank tensor and a float44
GPUStreamTensor2 & operator+  (GPUConstTensor2 & _lhs, GPUStreamTensor2 & _rhs);

/// Add two third rank tensors
GPUStreamTensor3 & operator+  (GPUStreamTensor3 & _lhs, GPUStreamTensor3 & _rhs);
/// Add a third rank tensor and a float444
GPUStreamTensor3 & operator+  (GPUStreamTensor3 & _lhs,  float444  _rhs);
/// Add a third rank tensor and a float444
GPUStreamTensor3 & operator+  ( float444  _lhs, GPUStreamTensor3 & _rhs);
/// Add a third rank tensor and a float444
GPUStreamTensor3 & operator+  (GPUStreamTensor3 & _lhs, GPUConstTensor3 & _rhs);
/// Add a third rank tensor and a float444
GPUStreamTensor3 & operator+  (GPUConstTensor3 & _lhs, GPUStreamTensor3 & _rhs);

/// Add two rank 4 tensors
GPUStreamTensor4 & operator+  (GPUStreamTensor4 & _lhs, GPUStreamTensor4 & _rhs);
/// Add a rank 4 tensor and a float4444
GPUStreamTensor4 & operator+  (GPUStreamTensor4 & _lhs,  float4444  _rhs);
/// Add a rank 4 tensor and a float4444
GPUStreamTensor4 & operator+  ( float4444  _lhs, GPUStreamTensor4 & _rhs);
/// Add a rank 4 tensor and a float4444
GPUStreamTensor4 & operator+  (GPUStreamTensor4 & _lhs, GPUConstTensor4 & _rhs);
/// Add a rank 4 tensor and a float4444
GPUStreamTensor4 & operator+  (GPUConstTensor4 & _lhs, GPUStreamTensor4 & _rhs);


//---------------------------Subtraction-------------------------------//

/// Subtract two scalars
GPUStreamScalar & operator-  (GPUStreamScalar & _lhs, GPUStreamScalar & _rhs);

/// Subtract a scalar and a float
GPUStreamScalar & operator-  (GPUStreamScalar & _lhs,  float _rhs);
/// Subtract a scalar and a float
GPUStreamScalar & operator-  ( float _lhs, GPUStreamScalar & _rhs);
/// Subtract a scalar and a float
GPUStreamScalar & operator-  (GPUStreamScalar & _lhs, GPUConstScalar & _rhs);
/// Subtract a scalar and a float
GPUStreamScalar & operator-  (GPUConstScalar & _lhs, GPUStreamScalar & _rhs);

/// Subtract const objects of the same type
template <typename T>
GPUConstTensor<T> & operator-  (GPUConstTensor<T> & _lhs, GPUConstTensor<T> & _rhs){
	return * new GPUConstTensor<T>(_lhs()-_rhs());
}
/// Subtract const objects of the same type
template <typename T>
GPUConstTensor<T> & operator-  (GPUConstTensor<T> & _lhs,  T _rhs){
	return * new GPUConstTensor<T>(_lhs()-_rhs);
}
/// Subtract const objects of the same type
template <typename T>
GPUConstTensor<T> & operator-  ( T _lhs, GPUConstTensor<T> & _rhs){
	return * new GPUConstTensor<T>(_lhs-_rhs());
}

/// Subtract two vectors
GPUStreamVector & operator-  (GPUStreamVector & _lhs, GPUStreamVector & _rhs);
/// Subtract a vector and a float4
GPUStreamVector & operator-  (GPUStreamVector & _lhs,  float4 _rhs);
/// Subtract a vector and a float4
GPUStreamVector & operator-  ( float4  _lhs, GPUStreamVector & _rhs);
/// Subtract a vector and a float4
GPUStreamVector & operator-  (GPUStreamVector & _lhs, GPUConstVector & _rhs);
/// Subtract a vector and a float4
GPUStreamVector & operator-  (GPUConstVector & _lhs, GPUStreamVector & _rhs);

/// Subtract two second rank tensors
GPUStreamTensor2 & operator-  (GPUStreamTensor2 & _lhs, GPUStreamTensor2 & _rhs);
/// Subtract a second rank tensor and a float44
GPUStreamTensor2 & operator-  (GPUStreamTensor2 & _lhs,  float44  _rhs);
/// Subtract a second rank tensor and a float44
GPUStreamTensor2 & operator-  ( float44  _lhs, GPUStreamTensor2 & _rhs);
/// Subtract a second rank tensor and a float44
GPUStreamTensor2 & operator-  (GPUStreamTensor2 & _lhs, GPUConstTensor2 & _rhs);
/// Subtract a second rank tensor and a float44
GPUStreamTensor2 & operator-  (GPUConstTensor2 & _lhs, GPUStreamTensor2 & _rhs);

/// Subtract two third rank tensors
GPUStreamTensor3 & operator-  (GPUStreamTensor3 & _lhs, GPUStreamTensor3 & _rhs);
/// Subtract a third rank tensor and a float444
GPUStreamTensor3 & operator-  (GPUStreamTensor3 & _lhs,  float444  _rhs);
/// Subtract a third rank tensor and a float444
GPUStreamTensor3 & operator-  ( float444  _lhs, GPUStreamTensor3 & _rhs);
/// Subtract a third rank tensor and a float444
GPUStreamTensor3 & operator-  (GPUStreamTensor3 & _lhs, GPUConstTensor3 & _rhs);
/// Subtract a third rank tensor and a float444
GPUStreamTensor3 & operator-  (GPUConstTensor3 & _lhs, GPUStreamTensor3 & _rhs);

/// Subtract two rank4 tensors
GPUStreamTensor4 & operator-  (GPUStreamTensor4 & _lhs, GPUStreamTensor4 & _rhs);
/// Subtract a rank4 tensor and a float4444
GPUStreamTensor4 & operator-  (GPUStreamTensor4 & _lhs,  float4444  _rhs);
/// Subtract a rank4 tensor and a float4444
GPUStreamTensor4 & operator-  ( float4444  _lhs, GPUStreamTensor4 & _rhs);
/// Subtract a rank4 tensor and a float4444
GPUStreamTensor4 & operator-  (GPUStreamTensor4 & _lhs, GPUConstTensor4 & _rhs);
/// Subtract a rank4 tensor and a float4444
GPUStreamTensor4 & operator-  (GPUConstTensor4 & _lhs, GPUStreamTensor4 & _rhs);



//---------------------------Multiplication with a scalar-------------------------------//

/// Multiply two scalars
GPUStreamScalar & operator*  (GPUStreamScalar & _lhs, GPUStreamScalar & _rhs);

/// Multiply a scalar and a float
GPUStreamScalar & operator*  (GPUStreamScalar & _lhs,  float _rhs);
/// Multiply a scalar and a float
GPUStreamScalar & operator*  ( float _lhs, GPUStreamScalar & _rhs);
/// Multiply a scalar and a float
GPUStreamScalar & operator*  (GPUStreamScalar & _lhs, GPUConstScalar & _rhs);
/// Multiply a scalar and a float
GPUStreamScalar & operator*  (GPUConstScalar & _lhs, GPUStreamScalar & _rhs);

/// Multiply a scalar and a vector
GPUStreamVector & operator*  (GPUStreamScalar & _lhs, GPUStreamVector & _rhs);
/// Multiply a scalar and a vector
GPUStreamVector & operator*  (GPUStreamVector & _lhs, GPUStreamScalar & _rhs);

/// Multiply a const scalar and a vector
GPUStreamVector & operator*  (GPUStreamVector & _lhs,  float _rhs);
/// Multiply a const scalar and a vector
GPUStreamVector & operator*  ( float _lhs, GPUStreamVector & _rhs);
/// Multiply a const scalar and a vector
GPUStreamVector & operator*  (GPUStreamVector & _lhs, GPUConstScalar & _rhs);
/// Multiply a const scalar and a vector
GPUStreamVector & operator*  (GPUConstScalar & _lhs, GPUStreamVector & _rhs);

/// Multiply a scalar and a const vector
GPUStreamVector & operator*  (GPUStreamScalar & _lhs,  float4 _rhs);
/// Multiply a scalar and a const vector
GPUStreamVector & operator*  ( float4 _lhs, GPUStreamScalar & _rhs);
/// Multiply a scalar and a const vector
GPUStreamVector & operator*  (GPUStreamScalar & _lhs, GPUConstVector & _rhs);
/// Multiply a scalar and a const vector
GPUStreamVector & operator*  (GPUConstVector & _lhs, GPUStreamScalar & _rhs);

/// Multiply const objects with scalars
template <typename T>
GPUConstTensor<T> & operator*  (GPUConstTensor<T> & _lhs, float _rhs){
	return * new GPUConstTensor<T>(_lhs()*_rhs);
}
/// Multiply const objects with scalars
template <typename T>
GPUConstTensor<T> & operator*  (float _rhs,GPUConstTensor<T> & _lhs){
	return * new GPUConstTensor<T>(_lhs()*_rhs);
}
/// Multiply const objects with scalars
template <typename T>
GPUConstTensor<T> & operator*  (GPUConstTensor<T> & _lhs,  GPUConstScalar & _rhs){
	return * new GPUConstTensor<T>(_lhs()*_rhs());
}
// have to specify one side because of ambiguities in template resolution...
/// Multiply a const scalar with a const scalar
GPUConstScalar & operator*  ( GPUConstScalar & _lhs, GPUConstScalar & _rhs);
/// Multiply a const scalar with a const vector
GPUConstVector & operator*  ( GPUConstScalar & _lhs, GPUConstVector & _rhs);
/// Multiply a const scalar with a const tensor2
GPUConstTensor2 & operator*  ( GPUConstScalar & _lhs, GPUConstTensor2 & _rhs);

/// Multiply a scalar and a Tensor2
GPUStreamTensor2 & operator*  (GPUStreamScalar & _lhs, GPUStreamTensor2 & _rhs);
/// Multiply a scalar and a Tensor2
GPUStreamTensor2 & operator*  (GPUStreamTensor2 & _lhs, GPUStreamScalar & _rhs);

/// Multiply a const scalar and a Tensor2
GPUStreamTensor2 & operator*  (GPUStreamTensor2 & _lhs,  float _rhs);
/// Multiply a const scalar and a Tensor2
GPUStreamTensor2 & operator*  ( float _lhs, GPUStreamTensor2 & _rhs);
/// Multiply a const scalar and a Tensor2
GPUStreamTensor2 & operator*  (GPUStreamTensor2 & _lhs, GPUConstScalar & _rhs);
/// Multiply a const scalar and a Tensor2
GPUStreamTensor2 & operator*  (GPUConstScalar & _lhs, GPUStreamTensor2 & _rhs);

/// Multiply a scalar and a const Tensor2
GPUStreamTensor2 & operator*  (GPUStreamScalar & _lhs,  float44  _rhs);
/// Multiply a scalar and a const Tensor2
GPUStreamTensor2 & operator*  ( float44  _lhs, GPUStreamScalar & _rhs);
/// Multiply a scalar and a const Tensor2
GPUStreamTensor2 & operator*  (GPUStreamScalar & _lhs, GPUConstTensor2 & _rhs);
/// Multiply a scalar and a const Tensor2
GPUStreamTensor2 & operator*  (GPUConstTensor2 & _lhs, GPUStreamScalar & _rhs);


/// Multiply a scalar and a Tensor3
GPUStreamTensor3 & operator*  (GPUStreamScalar & _lhs, GPUStreamTensor3 & _rhs);
/// Multiply a scalar and a Tensor3
GPUStreamTensor3 & operator*  (GPUStreamTensor3 & _lhs, GPUStreamScalar & _rhs);

/// Multiply a const scalar and a Tensor3
GPUStreamTensor3 & operator*  (GPUStreamTensor3 & _lhs,  float _rhs);
/// Multiply a const scalar and a Tensor3
GPUStreamTensor3 & operator*  ( float _lhs, GPUStreamTensor3 & _rhs);
/// Multiply a const scalar and a Tensor3
GPUStreamTensor3 & operator*  (GPUStreamTensor3 & _lhs, GPUConstScalar & _rhs);
/// Multiply a const scalar and a Tensor3
GPUStreamTensor3 & operator*  (GPUConstScalar & _lhs, GPUStreamTensor3 & _rhs);

/// Multiply a scalar and a const Tensor3
GPUStreamTensor3 & operator*  (GPUStreamScalar & _lhs,  float444  _rhs);
/// Multiply a scalar and a const Tensor3
GPUStreamTensor3 & operator*  ( float444  _lhs, GPUStreamScalar & _rhs);
/// Multiply a scalar and a const Tensor3
GPUStreamTensor3 & operator*  (GPUStreamScalar & _lhs, GPUConstTensor3 & _rhs);
/// Multiply a scalar and a const Tensor3
GPUStreamTensor3 & operator*  (GPUConstTensor3 & _lhs, GPUStreamScalar & _rhs);

/// Multiply a scalar and a Tensor4
GPUStreamTensor4 & operator*  (GPUStreamScalar & _lhs, GPUStreamTensor4 & _rhs);
/// Multiply a scalar and a Tensor4
GPUStreamTensor4 & operator*  (GPUStreamTensor4 & _lhs, GPUStreamScalar & _rhs);

/// Multiply a const scalar and a Tensor4
GPUStreamTensor4 & operator*  (GPUStreamTensor4 & _lhs,  float _rhs);
/// Multiply a const scalar and a Tensor4
GPUStreamTensor4 & operator*  ( float _lhs, GPUStreamTensor4 & _rhs);
/// Multiply a const scalar and a Tensor4
GPUStreamTensor4 & operator*  (GPUStreamTensor4 & _lhs, GPUConstScalar & _rhs);
/// Multiply a const scalar and a Tensor4
GPUStreamTensor4 & operator*  (GPUConstScalar & _lhs, GPUStreamTensor4 & _rhs);

/// Multiply a scalar and a const Tensor4
GPUStreamTensor4 & operator*  (GPUStreamScalar & _lhs,  float4444  _rhs);
/// Multiply a scalar and a const Tensor4
GPUStreamTensor4 & operator*  ( float4444  _lhs, GPUStreamScalar & _rhs);
/// Multiply a scalar and a const Tensor4
GPUStreamTensor4 & operator*  (GPUStreamScalar & _lhs, GPUConstTensor4 & _rhs);
/// Multiply a scalar and a const Tensor4
GPUStreamTensor4 & operator*  (GPUConstTensor4 & _lhs, GPUStreamScalar & _rhs);




//---------------------------Division by a scalar-------------------------------//

/// Divide two scalars
GPUStreamScalar & operator/  (GPUStreamScalar & _lhs, GPUStreamScalar & _rhs);

/// Divide a scalar and a float
GPUStreamScalar & operator/  (GPUStreamScalar & _lhs,  float  _rhs);
/// Divide a scalar and a float
GPUStreamScalar & operator/  ( float  _lhs, GPUStreamScalar & _rhs);
/// Divide a scalar and a float
GPUStreamScalar & operator/  (GPUStreamScalar & _lhs, GPUConstScalar & _rhs);
/// Divide a scalar and a float
GPUStreamScalar & operator/  (GPUConstScalar & _lhs, GPUStreamScalar & _rhs);

/// Divide a scalar and a vector
GPUStreamVector & operator/  (GPUStreamVector & _lhs, GPUStreamScalar & _rhs);

/// Divide a const scalar and a vector
GPUStreamVector & operator/  (GPUStreamVector & _lhs,  float _rhs);
/// Divide a const scalar and a vector
GPUStreamVector & operator/  (GPUStreamVector & _lhs, GPUConstScalar & _rhs);

/// Divide a scalar and a const vector
GPUStreamVector & operator/  ( float4 _lhs, GPUStreamScalar & _rhs);
/// Divide a scalar and a const vector
GPUStreamVector & operator/  (GPUConstVector & _lhs, GPUStreamScalar & _rhs);

/// Divide const objects with scalars
template <typename T>
GPUConstTensor<T> & operator/  (GPUConstTensor<T> & _lhs, float _rhs){
	return * new GPUConstTensor<T>(_lhs()/_rhs);
}
/// Divide const objects with scalars
template <typename T>
GPUConstTensor<T> & operator/  (GPUConstTensor<T> & _lhs,  GPUConstScalar & _rhs){
	return * new GPUConstTensor<T>(_lhs()/_rhs());
}
/// Divide const scalar with const scalar
GPUConstScalar & operator/ (float  _lhs, GPUConstScalar & _rhs);
/// Divide const vector with const scalar
GPUConstVector & operator/ (float4  _lhs, GPUConstScalar & _rhs);
/// Divide const second rank tensor with scalar
GPUConstTensor2 & operator/ (float44   _lhs, GPUConstScalar & _rhs);


/// Divide a scalar and a Tensor2
GPUStreamTensor2 & operator/  (GPUStreamTensor2 & _lhs, GPUStreamScalar & _rhs);
/// Divide a const scalar and a Tensor2
GPUStreamTensor2 & operator/  (GPUStreamTensor2 & _lhs,  float _rhs);
/// Divide a const scalar and a Tensor2
GPUStreamTensor2 & operator/  (GPUStreamTensor2 & _lhs, GPUConstScalar & _rhs);

/// Divide a scalar and a const Tensor2
GPUStreamTensor2 & operator/  ( float44  _lhs, GPUStreamScalar & _rhs);
/// Divide a scalar and a const Tensor2
GPUStreamTensor2 & operator/  (GPUConstTensor2 & _lhs, GPUStreamScalar & _rhs);

/// Divide a scalar and a Tensor3
GPUStreamTensor3 & operator/  (GPUStreamTensor3 & _lhs, GPUStreamScalar & _rhs);

/// Divide a const scalar and a Tensor3
GPUStreamTensor3 & operator/  (GPUStreamTensor3 & _lhs,  float _rhs);
/// Divide a const scalar and a Tensor3
GPUStreamTensor3 & operator/  (GPUStreamTensor3 & _lhs, GPUConstScalar & _rhs);

/// Divide a scalar and a const Tensor3
GPUStreamTensor3 & operator/  ( float444  _lhs, GPUStreamScalar & _rhs);
/// Divide a scalar and a const Tensor3
GPUStreamTensor3 & operator/  (GPUConstTensor3 & _lhs, GPUStreamScalar & _rhs);


/// Divide a scalar and a Tensor4

GPUStreamTensor4 & operator/  (GPUStreamTensor4 & _lhs, GPUStreamScalar & _rhs);
/// Divide a const scalar and a Tensor4
GPUStreamTensor4 & operator/  (GPUStreamTensor4 & _lhs,  float _rhs);
/// Divide a const scalar and a Tensor4
GPUStreamTensor4 & operator/  (GPUStreamTensor4 & _lhs, GPUConstScalar & _rhs);

/// Divide a scalar and a const Tensor4
GPUStreamTensor4 & operator/  ( float4444  _lhs, GPUStreamScalar & _rhs);
/// Divide a scalar and a const Tensor4
GPUStreamTensor4 & operator/  (GPUConstTensor4 & _lhs, GPUStreamScalar & _rhs);


//---------------------------Tensor contraction-------------------------------//

// include scalars here for easier interfacing
/// Multiply two scalars
GPUStreamScalar & operator|  (GPUStreamScalar & _lhs, GPUStreamScalar & _rhs);

/// Multiply a scalar and a float
GPUStreamScalar & operator|  (GPUStreamScalar & _lhs,  float _rhs);
/// Multiply a scalar and a float
GPUStreamScalar & operator|  ( float _lhs, GPUStreamScalar & _rhs);
/// Multiply a scalar and a float
GPUStreamScalar & operator|  (GPUStreamScalar & _lhs, GPUConstScalar & _rhs);
/// Multiply a scalar and a float
GPUStreamScalar & operator|  (GPUConstScalar & _lhs, GPUStreamScalar & _rhs);

/// Contract two vectors
GPUStreamScalar & operator|  (GPUStreamVector & _lhs, GPUStreamVector & _rhs);
/// Contract a vector and a float4
GPUStreamScalar & operator|  (GPUStreamVector & _lhs,  float4 _rhs);
/// Contract a vector and a float4
GPUStreamScalar & operator|  ( float4 _lhs, GPUStreamVector & _rhs);
/// Contract a vector and a float4
GPUStreamScalar & operator|  (GPUStreamVector & _lhs, GPUConstVector & _rhs);
/// Contract a vector and a float4
GPUStreamScalar & operator|  (GPUConstVector & _lhs, GPUStreamVector & _rhs);

/// Contract a vector and second Rank tensor
GPUStreamVector & operator|  (GPUStreamVector & _lhs, GPUStreamTensor2 & _rhs);
/// Contract a vector and second Rank tensor
GPUStreamVector & operator |  (GPUStreamTensor2 & _lhs, GPUStreamVector & _rhs);

/// Contract a vector and a float44
GPUStreamVector & operator |  (GPUStreamVector & _lhs,  float44  _rhs);
/// Contract a vector and a float44
GPUStreamVector & operator |  ( float44  _lhs, GPUStreamVector & _rhs);
/// Contract a vector and a float44
GPUStreamVector & operator |  (GPUStreamVector & _lhs, GPUConstTensor2 & _rhs);
/// Contract a vector and a float44
GPUStreamVector & operator |  (GPUConstTensor2 & _lhs, GPUStreamVector & _rhs);

/// Contract a second rank tensor and a float4
GPUStreamVector & operator |  (GPUStreamTensor2 & _lhs,  float4 _rhs);
/// Contract a second rank tensor and a float4
GPUStreamVector & operator |  ( float4 _lhs, GPUStreamTensor2 & _rhs);
/// Contract a second rank tensor and a float4
GPUStreamVector & operator |  (GPUStreamTensor2 & _lhs, GPUConstVector & _rhs);
/// Contract a second rank tensor and a float4
GPUStreamVector & operator |  (GPUConstVector & _lhs, GPUStreamTensor2 & _rhs);

/// Contract two second rank tensors
GPUStreamScalar & operator |  (GPUStreamTensor2 & _lhs, GPUStreamTensor2 & _rhs);

/// Contract two second rank tensors
GPUStreamTensor2 & operator ||  (GPUStreamTensor2 & _lhs, GPUStreamTensor2 & _rhs);


/// Contract a second rank tensor and a float44
GPUStreamScalar & operator |  (GPUStreamTensor2 & _lhs,  float44  _rhs);
/// Contract a second rank tensor and a float44
GPUStreamScalar & operator |  ( float44  _lhs, GPUStreamTensor2 & _rhs);
/// Contract a second rank tensor and a float44
GPUStreamScalar & operator |  (GPUStreamTensor2 & _lhs, GPUConstTensor2 & _rhs);
/// Contract a second rank tensor and a float44
GPUStreamScalar & operator |  (GPUConstTensor2 & _lhs, GPUStreamTensor2 & _rhs);

/// Contract two third rank tensors
GPUStreamScalar & operator|  (GPUStreamTensor3 & _lhs, GPUStreamTensor3 & _rhs);
/// Contract a third rank tensor and a float444
GPUStreamScalar & operator |  (GPUStreamTensor3 & _lhs,  float444  _rhs);
/// Contract a third rank tensor and a float444
GPUStreamScalar & operator |  ( float444  _lhs, GPUStreamTensor3 & _rhs);
/// Contract a third rank tensor and a float444
GPUStreamScalar & operator |  (GPUStreamTensor3 & _lhs, GPUConstTensor3 & _rhs);
/// Contract a third rank tensor and a float444
GPUStreamScalar & operator |  (GPUConstTensor3 & _lhs, GPUStreamTensor3 & _rhs);


/// Contract a third rank and a second rank tensor
GPUStreamVector & operator |  (GPUStreamTensor3 & _lhs, GPUStreamTensor2 & _rhs);
/// Contract a third rank and a second rank tensor
GPUStreamVector & operator |  (GPUStreamTensor2 & _lhs, GPUStreamTensor3 & _rhs);

/// Contract a third rank tensor and a float44
GPUStreamVector & operator|  (GPUStreamTensor3 & _lhs,  float44  _rhs);
/// Contract a third rank tensor and a float44
GPUStreamVector & operator|  ( float44  _lhs, GPUStreamTensor3 & _rhs);
/// Contract a third rank tensor and a float44
GPUStreamVector & operator|  (GPUStreamTensor3 & _lhs, GPUConstTensor2 & _rhs);
/// Contract a third rank tensor and a float44
GPUStreamVector & operator|  (GPUConstTensor2 & _lhs, GPUStreamTensor3 & _rhs);

/// Contract a second rank tensor and a float444
GPUStreamVector & operator|  (GPUStreamTensor2 & _lhs,  float444  _rhs);
/// Contract a second rank tensor and a float444
GPUStreamVector & operator|  ( float444  _lhs, GPUStreamTensor2 & _rhs);
/// Contract a second rank tensor and a float444
GPUStreamVector & operator|  (GPUStreamTensor2 & _lhs, GPUConstTensor3 & _rhs);
/// Contract a second rank tensor and a float444
GPUStreamVector & operator|  (GPUConstTensor3 & _lhs, GPUStreamTensor2 & _rhs);

/// Contract a third rank tensor and a vector
GPUStreamTensor2 & operator|  (GPUStreamTensor3 & _lhs, GPUStreamVector & _rhs);
/// Contract a third rank tensor and a vector
GPUStreamTensor2 & operator|  (GPUStreamVector & _lhs, GPUStreamTensor3 & _rhs);

/// Contract a third rank tensor and a third tensor
GPUStreamTensor2 & operator||  (GPUStreamTensor3 & _lhs, GPUStreamTensor3 & _rhs);

/// Contract a third rank tensor and a float4
GPUStreamTensor2 & operator|  (GPUStreamTensor3 & _lhs,  float4 _rhs);
/// Contract a third rank tensor and a float4
GPUStreamTensor2 & operator|  ( float4 _lhs, GPUStreamTensor3 & _rhs);
/// Contract a third rank tensor and a float4
GPUStreamTensor2 & operator|  (GPUStreamTensor3 & _lhs, GPUConstVector & _rhs);
/// Contract a third rank tensor and a float4
GPUStreamTensor2 & operator|  (GPUConstVector & _lhs, GPUStreamTensor3 & _rhs);

/// Contract a vector and a float444
GPUStreamTensor2 & operator|  (GPUStreamVector & _lhs,  float444  _rhs);
/// Contract a vector and a float444
GPUStreamTensor2 & operator|  ( float444  _lhs, GPUStreamVector & _rhs);
/// Contract a vector and a float444
GPUStreamTensor2 & operator|  (GPUStreamVector & _lhs, GPUConstTensor3 & _rhs);
/// Contract a vector and a float444
GPUStreamTensor2 & operator|  (GPUConstTensor3 & _lhs, GPUStreamVector & _rhs);

/// Contract a fourth rank tensor and a second rank tensor
GPUStreamTensor2 & operator | (GPUStreamTensor4 & _lhs, GPUConstTensor2 & _rhs);
/// Contract a fourth rank tensor and a second rank tensor
GPUStreamTensor2 & operator | (GPUStreamTensor4 & _lhs, GPUStreamTensor2 & _rhs);
/// Contract two fourth rank tensors
GPUStreamScalar  & operator |  (GPUStreamTensor4 & _lhs, GPUConstTensor4 & _rhs);
/// Contract a fourth rank tensor and a third rank tensor
GPUStreamVector  & operator |  (GPUStreamTensor4 & _lhs, GPUConstTensor3 & _rhs);
/// Contract a fourth rank tensor and a third rank tensor
GPUStreamVector & operator | (GPUStreamTensor4 & _lhs, GPUStreamTensor3 & _rhs); /// mintj

/// Contract a fourth rank const tensor and a third rank stream tensor
GPUStreamVector  & operator |  (GPUConstTensor4 & _lhs, GPUStreamTensor3 & _rhs);


/// Contract a fourth rank const tensor and a const vector
GPUConstTensor3 &  operator|  (GPUConstTensor4 & _lhs, GPUConstVector & _rhs);

/// Contract a const vector and a rank 4 const Tensor
GPUConstTensor3 & operator |  (GPUConstVector & _lhs, GPUConstTensor4 & _rhs);

/// Contract const objects
template <typename T>
GPUConstTensor<float> & operator|  (GPUConstTensor<T> & _lhs, GPUConstTensor<T> & _rhs){
	return * new GPUConstTensor<float>(_lhs()|_rhs());
}

/// Contract a fourth rank tensor and a const vector
GPUStreamTensor3 &  operator|  (GPUStreamTensor4 & _lhs, GPUConstVector & _rhs);
/// Contract a vector and a rank 4 const Tensor
GPUStreamTensor3 & operator |  (GPUStreamVector & _lhs, GPUConstTensor4 & _rhs);

/// Contract a fourth rank const tensor and a vector
GPUStreamTensor3 &  operator|  (GPUConstTensor4 & _lhs, GPUStreamVector & _rhs);
/// Contract a const vector and a rank 4 Tensor
GPUStreamTensor3 & operator |  (GPUConstVector & _lhs, GPUStreamTensor4 & _rhs);

/// Contract a fourth rank tensor and a vector
GPUStreamTensor3 &  operator|  (GPUStreamTensor4 & _lhs, GPUStreamVector & _rhs);
/// Contract a const vector and a rank 4 const Tensor
GPUStreamTensor3 & operator |  (GPUStreamVector & _lhs, GPUStreamTensor4 & _rhs);

/// Contract a const Tensor 2 and a const vector
GPUConstVector & operator|  (GPUConstTensor2 & _lhs, GPUConstVector & _rhs);
/// Contract a const vector and a const Tensor 2
GPUConstVector & operator|  (GPUConstVector & _lhs, GPUConstTensor2 & _rhs);

/// Contract one index of a fourth rank tensor and a second rank tensor
GPUStreamTensor4 & operator|| (GPUStreamTensor4 & _lhs, GPUStreamTensor2 & _rhs);
/// Contract one index of a second rank tensor and a fourth rank tensor
GPUStreamTensor4 & operator|| (GPUStreamTensor2 & _lhs, GPUStreamTensor4 & _rhs);

/// Contract one index of a const fourth rank tensor and a second rank tensor
GPUStreamTensor4 & operator|| (GPUConstTensor4 & _lhs, GPUStreamTensor2 & _rhs);
/// Contract one index of a const second rank tensor and a fourth rank tensor
GPUStreamTensor4 & operator|| (GPUConstTensor2 & _lhs, GPUStreamTensor4 & _rhs);

/// Contract one index of a fourth rank tensor and a const second rank tensor
GPUStreamTensor4 & operator|| (GPUStreamTensor4 & _lhs, GPUConstTensor2 & _rhs);
/// Contract one index of a second rank tensor and a const fourth rank tensor
GPUStreamTensor4 & operator|| (GPUStreamTensor2 & _lhs, GPUConstTensor4 & _rhs);

/// Contract one index of a const second rank tensor and a const fourth rank tensor
GPUConstTensor4 & operator|| (GPUConstTensor2 & _lhs, GPUConstTensor4 & _rhs);
/// Contract one index of a const fourth rank tensor and a const second rank tensor
GPUConstTensor4 & operator|| (GPUConstTensor4 & _lhs, GPUConstTensor2 & _rhs);

//---------------------------Outer product-------------------------------//

/// Outer product of two vectors
GPUStreamTensor2 & operator% (GPUStreamVector & _lhs, GPUStreamVector & _rhs);
/// Outer product of a vector and a float4
GPUStreamTensor2 & operator%  (GPUStreamVector & _lhs,  float4 _rhs);
/// Outer product of a vector and a float4
GPUStreamTensor2 & operator%  ( float4 _lhs, GPUStreamVector & _rhs);
/// Outer product of a vector and a float4
GPUStreamTensor2 & operator%  (GPUStreamVector & _lhs, GPUConstVector & _rhs);
/// Outer product of a vector and a float4
GPUStreamTensor2 & operator%  (GPUConstVector & _lhs, GPUStreamVector & _rhs);

/// Outer product of two const vectors
GPUConstTensor2 & operator%  (GPUConstVector & _lhs, GPUConstVector & _rhs);

/// Outer product of a second rank tensor and a vector
GPUStreamTensor3 & operator% (GPUStreamTensor2 &_lhs, GPUStreamVector &_rhs);
/// Outer product of a second rank tensor and a const vector
GPUStreamTensor3 & operator% (GPUStreamTensor2 &_lhs, GPUConstVector &_rhs);
/// Outer product of a const second rank tensor and a vector
GPUStreamTensor3 & operator% (GPUConstTensor2 &_lhs, GPUStreamVector &_rhs);
/// Outer product of a const second rank tensor and a const vector
GPUConstTensor3 & operator%  (GPUConstTensor2 & _lhs, GPUConstVector & _rhs);

/// Outer product of a second rank tensor and a vector
GPUStreamTensor3 & operator% (GPUStreamVector &_lhs, GPUStreamTensor2 &_rhs);
/// Outer product of a second rank tensor and a const vector
GPUStreamTensor3 & operator% (GPUStreamVector &_lhs, GPUConstTensor2 &_rhs);
/// Outer product of a const second rank tensor and a vector
GPUStreamTensor3 & operator% (GPUConstVector &_lhs, GPUStreamTensor2 &_rhs);
/// Outer product of a const second rank tensor and a const vector
GPUConstTensor3 & operator%  (GPUConstVector & _lhs, GPUConstTensor2 & _rhs);

/// Outer product of two second rank tensors
GPUStreamTensor4 & operator% (GPUStreamTensor2 &_lhs, GPUStreamTensor2 &_rhs);
/// Outer product of a second rank tensor and a const second rank tensor
GPUStreamTensor4 & operator% (GPUStreamTensor2 &_lhs, GPUConstTensor2 &_rhs);
/// Outer product of a second rank tensor and a const second rank tensor
GPUStreamTensor4 & operator% (GPUConstTensor2 &_lhs, GPUStreamTensor2 &_rhs);
/// Outer product of two const second rank tensors
GPUConstTensor4 & operator%  (GPUConstTensor2 & _lhs, GPUConstTensor2 & _rhs);

/// Outer product of a third rank Tensor and a Vector
GPUStreamTensor4 & operator% (GPUStreamTensor3 &_lhs, GPUStreamVector &_rhs);
/// Outer product of a third rank tensor and a const vector
GPUStreamTensor4 & operator% (GPUStreamTensor3 &_lhs, GPUConstVector &_rhs);
/// Outer product of a const third rank tensor and a vector
GPUStreamTensor4 & operator% (GPUConstTensor3 &_lhs, GPUStreamVector &_rhs);
/// Outer product of a const third rank Tensor and a const Vector
GPUConstTensor4 & operator%  (GPUConstTensor3 & _lhs, GPUConstVector & _rhs);

/// Outer product of a third rank Tensor and a Vector
GPUStreamTensor4 & operator% (GPUStreamVector &_lhs, GPUStreamTensor3 &_rhs);
/// Outer product of a third rank tensor and a const vector
GPUStreamTensor4 & operator% (GPUStreamVector &_lhs, GPUConstTensor3 &_rhs);
/// Outer product of a const third rank tensor and a vector
GPUStreamTensor4 & operator% (GPUConstVector &_lhs, GPUStreamTensor3 &_rhs);
/// Outer product of a const third rank Tensor and a const Vector
GPUConstTensor4 & operator%  (GPUConstVector & _lhs, GPUConstTensor3 & _rhs);

/// Special function for orbitals...
GPUStreamTensor4 & spin3projecttensor2(GPUStreamTensor2 & gmn, GPUStreamTensor2 & T);


/// Template class implementing an operation involving one GPUTensor as an argument
/** Through template specialization, GPUPWA implements all the tensor
 *  operations involving a stream on the GPU.
 *
 *  The class also implements the Tensor caching mechanism: A call to
 *  IncreaseUsecount() will increase the usecount of the instance by one.
 *  If the usecount was zero before, the IncreaseUsecount() methods of
 *  the argument will also be called. On the first call of operator(index, block),
 *  GPUOneStreamOpBase will perform the calculation required, usually calling the
 *  operator() method of the argument. The result is cached. Every time operator()
 *  is called, the usecount is decreased by one. If the usecount reaches 0, the cached
 *  stream is deleted. Separate usecounts are kept for each index and block.
 *
 */

template <typename tt,  ///< Base type of the result (float, float44, float444, float4444)
			typename T, ///< Stream type of the result (GPUDataStream<tt>), present for historical reasons
			int oper,  ///< Integer denoting the operation to be performed - we often use the ASCII character code of the corresponding operation (-)
			typename A = T, ///< Stream type (if stream) or base type (if const) of the argument
			bool reg = false ///< Boolean denoting whether the argument is a GPUDataDependentObject
			>
class GPUOneStream :
	public T
{
public:
	/// Constructor taking a Tensor as argument
	GPUOneStream(A & _lhs):lhs(_lhs),op(oper){};
	/// Destructor
	virtual ~GPUOneStream(void){};
	/// Do the calculation!
	virtual GPUDataStream<tt> * operator()(int index=0, int block=0)=0;
	// Get the stream length
	//virtual int GetLength(int index = 0, int block=0);
	/// Increase the usecount
	virtual void IncreaseUsecount(int index);
	/// Increase the usecount
	virtual void IncreaseUsecount(int index, int block);
protected:
	/// Assert the correct index size
	virtual void assertindex(int index);
	/// The argument
	A & lhs;
	/// Integer denoting the operation to be performed
	const int op;
};



template<typename tt, typename T, int oper, typename A, bool reg>
class GPUOneStreamOp: public GPUOneStream<tt, T,oper, A, reg>
{
public:
	/// Constructor
	GPUOneStreamOp(A & _lhs):GPUOneStream<tt, T, oper,A, reg>(_lhs){};
	/// Destructor
	virtual ~GPUOneStreamOp(void){};
	/// Do the calculation!
	virtual GPUDataStream<tt> * operator()(int index=0, int block=0);
};

template<typename tt,typename T, int oper, typename A >
class GPUOneStream<tt,T,oper,A,true>: public T
{
public:
	/// Constructor
	GPUOneStream(A & _lhs);
	/// Destructor
	virtual ~GPUOneStream(void){};
	/// Do the calculation!
	virtual GPUDataStream<tt> * operator()(int index=0, int block=0)=0;
	// Get the stream length
	//virtual int GetLength(int index = 0, int block=0);
	/// Increase the usecount
	virtual void IncreaseUsecount(int index);
	/// Increase the usecount
	virtual void IncreaseUsecount(int index, int block);
protected:
	/// Assert the correct index size
	virtual void assertindex(int index);
	/// The operand
	A & lhs;
	/// Integer encoding the operation to be performed;
	const int op;

};

//#include "GPUOnestreamClasses.h"



//---------------------------Negation-------------------------------//

/// Negate a scalar
GPUStreamScalar & operator-  (GPUStreamScalar & _lhs);
/// Negate a vector
GPUStreamVector & operator-  (GPUStreamVector & _lhs);
/// Negate a second rank tensor
GPUStreamTensor2 & operator-  (GPUStreamTensor2 & _lhs);
/// Negate a rank3 tensor
GPUStreamTensor3 & operator-  (GPUStreamTensor3 & _lhs);
/// Negate a rank4 tensor
GPUStreamTensor4 & operator-  (GPUStreamTensor4 & _lhs);



/// Negate const objects
template <typename T>
GPUConstTensor<T> & operator-  (GPUConstTensor<T> & _lhs){
	return * new GPUConstTensor<T>(-_lhs());
}

//--------------------------Functions of scalars ------------------------//
/// Square root
GPUStreamScalar & sqrt(GPUStreamScalar & _lhs);
/// Square root of a const object (not implemented for vector and higher tensors)
template <typename T>
GPUConstTensor<T> & sqrt(GPUConstTensor<T> & _lhs){
	return * new GPUConstTensor<T>(sqrt(_lhs()));
}
/// Sine
GPUStreamScalar & sin(GPUStreamScalar & _lhs);
/// Sine of a const object (not implemented for vector and higher tensors)
template <typename T>
GPUConstTensor<T> & sin(GPUConstTensor<T> & _lhs){
	return * new GPUConstTensor<T>(sin(_lhs()));
}
/// Cosine
GPUStreamScalar & cos(GPUStreamScalar & _lhs);
/// Cosine of a const object (not implemented for vector and higher tensors)
template <typename T>
GPUConstTensor<T> & cos(GPUConstTensor<T> & _lhs){
	return * new GPUConstTensor<T>(cos(_lhs()));
}
/// Tangent
GPUStreamScalar & tan(GPUStreamScalar & _lhs);
/// Sine of a const object (not implemented for vector and higher tensors)
template <typename T>
GPUConstTensor<T> & tan(GPUConstTensor<T> & _lhs){
	return * new GPUConstTensor<T>(tan(_lhs()));
}
/// exponentiation
GPUStreamScalar & exp(GPUStreamScalar & _lhs);
/// Exponentiation of a const object (not implemented for vector and higher tensors)
template <typename T>
GPUConstTensor<T> & exp(GPUConstTensor<T> & _lhs){
	return * new GPUConstTensor<T>(exp(_lhs()));
}

/// Transpose a rank 2 tensor
GPUStreamTensor2 & trans(GPUStreamTensor2 & _lhs);

/// transpose of rank3 tensor 123 -> 213
GPUStreamTensor3 & trans_213(GPUStreamTensor3 & _lhs);
/// transpose of rank3 tensor 123 -> 132
GPUStreamTensor3 & trans_132(GPUStreamTensor3 & _lhs);
/// transpose of rank3 tensor 123 -> 231
GPUStreamTensor3 & trans_231(GPUStreamTensor3 & _lhs);
/// transpose of rank3 tensor 123 -> 312
GPUStreamTensor3 & trans_312(GPUStreamTensor3 & _lhs);
/// transpose of rank3 tensor 123 -> 321
GPUStreamTensor3 & trans_321(GPUStreamTensor3 & _lhs);

/// Basic tranposition of a rank 4 tensor, used by the trans functions
void transpose_1324(const DeviceInterface * dev, GPUDataStream<float44>* lstream, GPUDataStream<float44>* rstream);
/// Basic tranposition of a rank 4 tensor, used by the trans functions
void transpose_1243(const DeviceInterface * dev, GPUDataStream<float44>* lstream, GPUDataStream<float44>* rstream);
/// Basic tranposition of a rank 4 tensor, used by the trans functions
void transpose_2134(const DeviceInterface * dev, GPUDataStream<float44>* lstream, GPUDataStream<float44>* rstream);

// 23 transposed of rank4 tensor

/// Transpose a fourth rank tensor 1234 -> 4123
GPUStreamTensor4 & trans_4123(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 1423
GPUStreamTensor4 & trans_1423(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 1243
GPUStreamTensor4 & trans_1243(GPUStreamTensor4 & _lhs);
//GPUStreamTensor4 & trans_1234(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 4213
GPUStreamTensor4 & trans_4213(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 2413
GPUStreamTensor4 & trans_2413(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 2143
GPUStreamTensor4 & trans_2143(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 2134
GPUStreamTensor4 & trans_2134(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 4132
GPUStreamTensor4 & trans_4132(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 1432
GPUStreamTensor4 & trans_1432(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 1342
GPUStreamTensor4 & trans_1342(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 1324
GPUStreamTensor4 & trans_1324(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 4231
GPUStreamTensor4 & trans_4231(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 2431
GPUStreamTensor4 & trans_2431(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 2341
GPUStreamTensor4 & trans_2341(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 2314
GPUStreamTensor4 & trans_2314(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 4312
GPUStreamTensor4 & trans_4312(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 3412
GPUStreamTensor4 & trans_3412(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 3142
GPUStreamTensor4 & trans_3142(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 3124
GPUStreamTensor4 & trans_3124(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 4321
GPUStreamTensor4 & trans_4321(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 3421
GPUStreamTensor4 & trans_3421(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 3241
GPUStreamTensor4 & trans_3241(GPUStreamTensor4 & _lhs);
/// Transpose a fourth rank tensor 1234 -> 3214
GPUStreamTensor4 & trans_3214(GPUStreamTensor4 & _lhs);


/// Transpose a const fourth rank tensor 1234 -> 4123
GPUConstTensor4 & trans_4123(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 1423
GPUConstTensor4 & trans_1423(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 1243
GPUConstTensor4 & trans_1243(GPUConstTensor4 & _lhs);
//GPUConstTensor4 & trans_1234(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 4213
GPUConstTensor4 & trans_4213(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 2413
GPUConstTensor4 & trans_2413(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 2143
GPUConstTensor4 & trans_2143(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 2134
GPUConstTensor4 & trans_2134(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 4132
GPUConstTensor4 & trans_4132(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 1432
GPUConstTensor4 & trans_1432(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 1342
GPUConstTensor4 & trans_1342(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 1324
GPUConstTensor4 & trans_1324(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 4231
GPUConstTensor4 & trans_4231(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 2431
GPUConstTensor4 & trans_2431(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 2341
GPUConstTensor4 & trans_2341(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 2314
GPUConstTensor4 & trans_2314(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 4312
GPUConstTensor4 & trans_4312(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 3412
GPUConstTensor4 & trans_3412(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 3142
GPUConstTensor4 & trans_3142(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 3124
GPUConstTensor4 & trans_3124(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 4321
GPUConstTensor4 & trans_4321(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 3421
GPUConstTensor4 & trans_3421(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 3241
GPUConstTensor4 & trans_3241(GPUConstTensor4 & _lhs);
/// Transpose a const fourth rank tensor 1234 -> 3214
GPUConstTensor4 & trans_3214(GPUConstTensor4 & _lhs);



/// raise/lower index of a vector
GPUStreamVector & moveindex(GPUStreamVector & _lhs);
/// raise/lower index of a const vector
GPUConstVector & moveindex(GPUConstVector & _lhs);
/// raise/lower index of a rank 2 tensor
GPUStreamTensor2 & movefirstindex(GPUStreamTensor2 & _lhs);
/// raise/lower index of a rank 2 tensor
GPUConstTensor2 & movefirstindex(GPUConstTensor2 & _lhs);

/// raise/lower index of a rank 2 tensor
GPUStreamTensor2 & movelastindex(GPUStreamTensor2 & _lhs);
/// raise/lower index of a rank 2 tensor
GPUConstTensor2 & movelastindex(GPUConstTensor2 & _lhs);

/// raise/lower indices of a rank 2 tensor
GPUStreamTensor2 & moveindices(GPUStreamTensor2 & _lhs);
/// raise/lower indices of a rank 2 tensor
GPUConstTensor2 & moveindices(GPUConstTensor2 & _lhs);

/// raise/lower indices of a rank 3 tensor
GPUStreamTensor3 & moveindices(GPUStreamTensor3 & _lhs);
/// raise/lower indices of a rank 2 tensor
GPUConstTensor3 & moveindices(GPUConstTensor3 & _lhs);


/// raise/lower index of a rank 3 tensor
GPUStreamTensor3 & movefirstindex(GPUStreamTensor3 & _lhs);
/// raise/lower index of a rank 3 tensor
GPUConstTensor3 & movefirstindex(GPUConstTensor3 & _lhs);

/// raise/lower index of a rank 3 tensor
GPUStreamTensor3 & movemiddleindex(GPUStreamTensor3 & _lhs);
/// raise/lower index of a rank 3 tensor
GPUConstTensor3 & movemiddleindex(GPUConstTensor3 & _lhs);

/// raise/lower index of a rank 3 tensor
GPUStreamTensor3 & movelastindex(GPUStreamTensor3 & _lhs);
/// raise/lower index of a rank 3 tensor
GPUConstTensor3 & movemlastindex(GPUConstTensor3 & _lhs);

/// raise/lower index of a rank 4 tensor
GPUStreamTensor4 & movelastindex(GPUStreamTensor4 & _lhs);
/// raise/lower index of a rank 4 tensor
GPUConstTensor4 & movemlastindex(GPUConstTensor4 & _lhs);

/// raise/lower indices of a rank 4 tensor
GPUStreamTensor4 & moveindices(GPUStreamTensor4 & _lhs);
/// raise/lower indices of a rank 4 tensor
GPUConstTensor4 & moveindices(GPUConstTensor4 & _lhs);

/// Get the spin3 Orbital Tensor
GPUStreamTensor3& spin3orbitaltensor(GPUStreamVector & rtilde, GPUStreamVector & pa);
/// Get the spin3 Orbital Tensor
GPUStreamTensor3& spin3orbitaltensor(GPUStreamVector & rtilde, GPUConstVector & pa);

/// Get the spin4 Orbital Tensor
GPUStreamTensor4& spin4orbitaltensor(GPUStreamVector & rtilde, GPUStreamTensor2 & delp);
/// Get the spin4 Orbital Tensor
GPUStreamTensor4& spin4orbitaltensor(GPUStreamVector & rtilde, GPUConstTensor2 & delp);


#endif

