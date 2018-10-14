/// \file GPUPropagatorDerivative.h
/*
 * GPUPropagatorDerivative.h
 *
 *  Created on: Aug 27, 2009
 *      Author: nberger
 */

#ifndef GPUPROPAGATORDERIVATIVE_H_
#define GPUPROPAGATORDERIVATIVE_H_

#include <vector>
#include "GPUDataStream.h"

/// Base class for propagators with derivatives
class GPUPropagatorDerivative {
public:
	/// Constructor - not that the member stream vectors have to be initialized by the derived classes
	GPUPropagatorDerivative();
	/// Destructor
	virtual ~GPUPropagatorDerivative();
	/// Get a stream of the derivative of the propagator with regards to the mass
	virtual GPUDataStream<float2> * GetMassDerivative(int index, int block) =0;
	/// Get a stream of the derivative of the propagator with regards to the width
	virtual GPUDataStream<float2> * GetWidthDerivative(int index, int block) =0;
	// Get a stream of the derivative of the |propagator|^2 with regards to the mass
	virtual GPUDataStream<float> * GetAbsMassDerivative(int index, int block) =0;
	/// Get a stream of the derivative of the |propagator|^2 with regards to the width
	virtual GPUDataStream<float> * GetAbsWidthDerivative(int index, int block) =0;
	/// Reset the derivatives at an index
	virtual void ResetDerivatives(int index);
	/// Reset the derivatives at an index and block
	virtual void ResetDerivatives(int index, int block);

protected:
	/// The cached calculated stream for mass derivative
	std::vector<std::vector<GPUDataStream<float2> *> > mDmass;
	/// The cached calculated stream for width derivative
	std::vector<std::vector<GPUDataStream<float2> *> > mDwidth;
	/// The cached calculated stream for mass derivative of |propagator|^2
	std::vector<std::vector<GPUDataStream<float> *> > mAbsDmass;
	/// The cached calculated stream for width derivative of |propagator|^2
	std::vector<std::vector<GPUDataStream<float> *> > mAbsDwidth;
};

#endif /* GPUPROPAGATORDERIVATIVE_H_ */
