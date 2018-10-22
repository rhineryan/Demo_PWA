/// \file GPUPropagatorSigma.h
#ifndef GPUPROPAGATORSIGMA_H_
#define GPUPROPAGATORSIGMA_H_

#include "GPUBasicPropagator.h"
#include "GPUPropagatorDerivative.h"
#include "ResCfg.h"

/// Implementation of a Sigma Propagator

class GPUPropagatorSigma :
	public GPUBasicPropagator, public GPUPropagatorDerivative
{
public:
	/// Constructor
	GPUPropagatorSigma(char * name,  ///< name of the propagator
							GPUStreamScalar & _mx2);///< data stream with the squared invariant mass of the daughters
	/// Destructor
	virtual ~GPUPropagatorSigma(void);
	/// Bracket operator performs the calculation or returns a cached value
	virtual GPUDataStream<float2> * operator()(int index =0, int block=0);
	/// Dummy method for interface consistency; call will stop the program
	virtual GPUDataStream<float2> * GetMassDerivative(int index, int block){assert(0); return 0;};
	/// Dummy method for interface consistency; call will stop the program
	virtual GPUDataStream<float2> * GetWidthDerivative(int index, int block){assert(0); return 0;};
	/// Dummy method for interface consistency; call will stop the program
	virtual GPUDataStream<float> * GetAbsMassDerivative(int index, int block){assert(0); return 0;};
	/// Dummy method for interface consistency; call will stop the program
	virtual GPUDataStream<float> * GetAbsWidthDerivative(int index, int block){assert(0); return 0;};

private:

};

#endif /* GPUPROPAGATORSIGMA_H_ */
