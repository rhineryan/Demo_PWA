/// \file GPUConstTensor.h

#pragma once
#include "GPUTensor.h"
#include "float44.h"
#include "float444.h"
#include "float4444.h"
#include <vector>

/// Template class for constant tensors
/** In the GPUPWA framework, constant tensors are objects, whose
    value does not depend on the event under study, e.g. the metric
    tensor or the four vector of a particle in its rest system.
    Note that the default constructor is protected, so only derived
    objects can create unitialised GPUConstTensors.

    With the indexing mechanism, GPUConstTensors can take different
    values for different data sets, e.g. data and MC.
**/
template <typename T>
class GPUConstTensor :
	public GPUTensor
{
public:
  /// Constructor initialising the tensor with T
  GPUConstTensor(const T _t);
  /// Destructor
  virtual ~GPUConstTensor(void){};
  /// Bracket operator, returning the value of the tensor
  T operator()(int index =0){return mdata[0];};
  /// Get a pointer to the first element of the Tensor
  float * Read(int index=0){return (float*)(&mdata[index]);};
  /// Print the contents of the Tensor to cout
  void Print();
protected:
  /// Protected default constructor
  GPUConstTensor(void);
  /// The value of the tensor
  std::vector<T> mdata;
};

/// GPUConstTensor representing a scalar
typedef GPUConstTensor<float> GPUConstScalar;
/// GPUConstTensor representing a vector
typedef GPUConstTensor<float4> GPUConstVector;
/// GPUConstTensor representing a second rank tensor
typedef GPUConstTensor<float44> GPUConstTensor2;
/// GPUConstTensor representing a third rank tensor
typedef GPUConstTensor<float444> GPUConstTensor3;
/// GPUConstTensor representing a fourth rank tensor
typedef GPUConstTensor<float4444> GPUConstTensor4;
