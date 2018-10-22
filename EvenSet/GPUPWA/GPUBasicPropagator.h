/// \file GPUBasicPropagator.h
/*
 * GPUBasicPropagator.h
 *
 *  Created on: Aug 26, 2009
 *      Author: nberger
 */

#ifndef GPUBASICPROPAGATOR_H_
#define GPUBASICPROPAGATOR_H_

#include "GPUPropagatorType.h"
#include "GPUStreamTensor.h"

class GPUPartialWaveAnalysis;

/// A basic propagator (abstract base class), taking the invariant mass squared of the daughters and returning a complex value
class GPUBasicPropagator: public GPUScalarPropagator{
public:
	/// Constructor, taking a scalar stream, representing the invariant mass
	GPUBasicPropagator(char * name, GPUStreamScalar & _mx2, std::vector<char **> parnames, unsigned int npar = 2);
	/// Destructor
	virtual ~GPUBasicPropagator();
	/// Return the invariannt masss input stream
	virtual GPUStreamScalar & GetMx2(){return mx2;};

protected:
	/// A scalar stream representing the invariant mass
	GPUStreamScalar & mx2;
};

#endif /* GPUBASICPROPAGATOR_H_ */
