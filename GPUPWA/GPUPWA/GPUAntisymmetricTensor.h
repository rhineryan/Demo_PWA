/// \file GPUAntisymmetricTensor.h

#pragma once
#include "GPUConstTensor.h"


/// The Totally antisymmetric Levi Civitta Tensor \f$ \epsilon_{ijkl} \f$
/** \f$ \epsilon_{ijkl} \f$ is 1 for \f$ ijkl\f$ an even permutation of
 *  1234, -1 for odd permutations and 0 otherwise
 */
class GPUAntisymmetricTensor:
	public GPUConstTensor4
{
public:
  ///Constructor, setting up the metric tensor
  GPUAntisymmetricTensor();
  /// Destructor
  virtual ~GPUAntisymmetricTensor();
};


/// The 0 component of the the totally antisymmetric Levi Civitta Tensor \f$ \epsilon_{ijk0} \f$
/** \f$ \epsilon_{ijk0} \f$ is 1 for \f$ ijk0\f$ an even permutation of
 *  0123, -1 for odd permutations and 0 otherwise
 */
class GPUAntisymmetricTensorZeroComponent:
	public GPUConstTensor3
{
public:
	///Constructor, setting up the tensor
	 GPUAntisymmetricTensorZeroComponent();
	 /// Destructor
	 virtual ~GPUAntisymmetricTensorZeroComponent();
};
