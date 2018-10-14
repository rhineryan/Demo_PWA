///  \file  GPUPropagatorComBW.h
/*
 *
 *  Created on: july 9, 2017
 *      Author: xiongxa
 */


#ifndef GPUPROPAGATORCOMBW_H_
#define GPUPROPAGATORCOMBW_H_

#include "GPUBasicPropagator.h"
#include "ResCfg.h"
#include "ParaCfg.h"
#include <vector>
/// Propagator class implementing a mass dependent Breit-Wigner
/**
 *   The Breit-Wigner form used here is
 *
 */

class GPUPropagatorComBW: public GPUBasicPropagator{
public:
	/// Constructor taking mass and width
  GPUPropagatorComBW(char * name,
			      GPUStreamScalar & _mx2, /// <! Stream with center of mass energy squared
			      std::vector<char **> _parnames// parameter names; each resonance have (m,w), (gx,gy); and there are 4 poly.terms (6 paramaters) in the P-vector c, cs, (dx,dy), (dsx, dsy);
			      );     /// <! mass of the second decay particle
	/// Destructor
	virtual ~GPUPropagatorComBW();
	/// virtual () operator; performs the actual stream calculation
	virtual GPUDataStream<float2> * operator()(int index =0, int block=0);


private:

	mutable GPUDataStream<float4>* mpars;
};

#endif /* GPUPROPAGATORMASSDEPENDENTBREITWIGNER_H_ */
