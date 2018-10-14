/// \file GPUComputedPropagator.h
/*
 * GPUComputedPropagator.h
 *
 *  Created on: Jul 13, 2009
 *      Author: nberger
 */

#ifndef GPUCOMPUTEDPROPAGATOR_H_
#define GPUCOMPUTEDPROPAGATOR_H_

#include "GPUPropagatorType.h"
#include "GPUStreamTensor.h"
#include <vector>
#include <cassert>

using std::vector;

class GPUPartialWaveAnalysis;


/// Template class for propagators (objects contaiining complex numbers) constructed from Tensors and Propagators
/** Please note that there is a separate implementation for scalar propagators
 *
 *
 */

template<typename T, ///< rank of the propagator (float, float4, float444...)
		 typename L, ///< type of the first argument
		 typename R, ///< type of the second argument
		 char op>    ///< operation to be performed

class GPUComputedPropagator: public GPUPropagatorType<T> {
public:
	/// Constructor
	GPUComputedPropagator(GPUPartialWaveAnalysis * ana, L & lhs, R & rhs);
	/// Destructor
	virtual ~GPUComputedPropagator();
	/// Set the usecount for the caching mechanism
	virtual void IncreaseUsecount(int index);
	/// Set the usecount for the caching mechanism
	virtual void IncreaseUsecount(int index, int block);

protected:
	/// perform the actual calculation
	virtual void calculate(int index, int block);
	/// Left hand argument
	L & lhs;
	/// Right hand argument
	R & rhs;
	/// number of dynamic parameters in lhs
	unsigned int mnlhs;
	/// umber of dynamic parameters in rhs
	unsigned int mnrhs;
};


/// Template class for scalar propagators (objects contaiining complex numbers) constructed from Tensors and Propagators
template<typename L, ///< type of the first argument
		 typename R, ///< type of the second argument
		 char op>    ///< operation to be performed
class GPUComputedPropagator<float, L, R, op>: public GPUPropagatorType<float> {
public:
	/// Constructor
	GPUComputedPropagator(GPUPartialWaveAnalysis * ana, L & lhs, R & rhs);
	/// Destructor
	virtual ~GPUComputedPropagator();
	/// For the scalar case: return a float2 stream
	virtual GPUDataStream<float2> * operator()(int index, int block);
	/// Set the usecount for the caching mechanism
	virtual void IncreaseUsecount(int index);
	/// Set the usecount for the caching mechanism
	virtual void IncreaseUsecount(int index, int block);

protected:
	/// Left hand argument
	L & lhs;
	/// Right hand argument
	R & rhs;
	/// number of masses/widths in lhs
	unsigned int mnlhs;
	/// umber of masses/widths in rhs
	unsigned int mnrhs;
};



/// Add scalar propagators
GPUScalarPropagator & operator+  (GPUScalarPropagator & _lhs, GPUScalarPropagator & _rhs);
/// Multiply scalar propagators
GPUScalarPropagator & operator*  (GPUScalarPropagator & _lhs, GPUScalarPropagator & _rhs);
/// Multiply a scalar propagator with a scalar
GPUScalarPropagator & operator*  (GPUStreamScalar & _lhs, GPUScalarPropagator & _rhs);
/// Multiply a scalar propagator with a scalar
GPUScalarPropagator & operator*  (GPUScalarPropagator & _lhs, GPUStreamScalar & _rhs);

/// Multiply a scalar propagator with a second rank tensor
GPUTensor2Propagator & operator* (GPUScalarPropagator & _lhs, GPUStreamTensor2 & _rhs);
/// Multiply a scalar propagator with a second rank tensor
GPUTensor2Propagator & operator* (GPUStreamTensor2 & _lhs, GPUScalarPropagator & _rhs);

/// Multiply a scalar propagator with a second rank propagator
GPUTensor2Propagator & operator* (GPUScalarPropagator & _lhs, GPUTensor2Propagator & _rhs);
/// Multiply a second rank propagator with a scalar propagator
GPUTensor2Propagator & operator* (GPUTensor2Propagator & _lhs, GPUScalarPropagator & _rhs);

/// Add two second rank propagators
GPUTensor2Propagator & operator+ (GPUTensor2Propagator & _lhs, GPUTensor2Propagator & _rhs);
/// Subtract second rank propagators
GPUTensor2Propagator & operator- (GPUTensor2Propagator & _lhs, GPUTensor2Propagator & _rhs);

/// Add vector propagators
GPUVectorPropagator & operator+ (GPUVectorPropagator & _lhs, GPUVectorPropagator & _rhs);
/// Subtract vector propagators
GPUVectorPropagator & operator- (GPUVectorPropagator & _lhs, GPUVectorPropagator & _rhs);

/// Contract a rank 3 tensor and a second rank propagator
GPUVectorPropagator & operator| (GPUStreamTensor3 & _lhs, GPUTensor2Propagator & _rhs);
/// Contract a second rank propagator and a rank three tensor
GPUVectorPropagator & operator| (GPUTensor2Propagator & _rhs, GPUStreamTensor3 & _lhs);

/// Contract a rank 3 tensor with a vector propagator
GPUTensor2Propagator & operator| (GPUStreamTensor3 & _lhs, GPUVectorPropagator & _rhs);
/// Contract a vector propagator with a rank three tensor
GPUTensor2Propagator & operator| (GPUVectorPropagator & _rhs, GPUStreamTensor3 & _lhs);

/// Contract a rank 4 tensor with a rank 2 propagator
GPUTensor2Propagator & operator| (GPUStreamTensor4 & _lhs, GPUTensor2Propagator & _rhs);
/// Contract a rank 2 propagator with a rank 4 tensor
GPUTensor2Propagator & operator| (GPUTensor2Propagator & _rhs, GPUStreamTensor4 & _lhs);

/// Multiply a vector propagator with a scalar propagator
GPUVectorPropagator & operator* (GPUVectorPropagator & _lhs, GPUScalarPropagator & _rhs);
/// Multiply a vector propagator with a scalar propagator
GPUVectorPropagator & operator* (GPUScalarPropagator & _rhs, GPUVectorPropagator & _lhs);

/// Multiply a vector with a scalar propagator
GPUVectorPropagator & operator* (GPUStreamVector & _lhs, GPUScalarPropagator & _rhs);
/// Multiply a scalar propagator with a vector
GPUVectorPropagator & operator* (GPUScalarPropagator & _rhs, GPUStreamVector & _lhs);

/// Propagator as a sum of two scalar propagators
typedef GPUComputedPropagator<float, GPUScalarPropagator, GPUScalarPropagator, '+'> GPUScalarSumPropagator;

#endif /* GPUCOMPUTEDPROPAGATOR_H_ */
