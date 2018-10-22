/// \file GPUPropagatorFlatte3.h
#ifndef GPUPROPAGATORFLATTE3_H_
#define GPUPROPAGATORFLATTE3_H_

#include "GPUBasicPropagator.h"
#include "GPUPropagatorDerivative.h"
#include "ResCfg.h"

/// Implementation of a Flatte3 Propagator

class GPUPropagatorFlatte3 :
	public GPUBasicPropagator, public GPUPropagatorDerivative
{
public:
	/// Constructor
	GPUPropagatorFlatte3(char * name,  ///< name of the propagator
							GPUStreamScalar & _mx2,
              float _m1a,
              float _m1b,
              float _m2a,
              float _m2b,
              float _m3a,
              float _m3b);///< data stream with the squared invariant mass of the daughters
	/// Destructor
	virtual ~GPUPropagatorFlatte3(void);
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
	const float m1a;
	const float m1b;
	const float m2a;
	const float m2b;
	const float m3a;
	const float m3b;

};

#endif /* GPUPROPAGATORFLATTE3_H_ */
