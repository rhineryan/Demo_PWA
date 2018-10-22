///  \file  GPUDynamicalSumBW.h
/*
 *
 *  Created on: july 9, 2017
 *      Author: xiongxa
 */




#ifndef GPUDYNAMICALSUMBW_H_
#define GPUDYNAMICALSUMBW_H_

#include "GPUBasicPropagator.h"
#include "ResCfg.h"
#include "ParaCfg.h"
#include <vector>
/// Propagator class implementing a mass dependent Breit-Wigner
/**
 *   The Breit-Wigner form used here is
 *
 */

class GPUDynamicalSumBW: public GPUBasicPropagator{
public:
	/// Constructor taking mass and width
  GPUDynamicalSumBW(char * name,
			      GPUStreamScalar & _mx2, /// <! Stream with center of mass energy squared
			      GPUStreamScalar & _mx123, /// <! Stream with center of mass energy squared
			      std::vector<char **> _parnames,// parameter names; each resonance have (m,w), (gx,gy); and there are 4 poly.terms (6 paramaters) in the P-vector c, cs, (dx,dy), (dsx, dsy);
			      unsigned int _nresnonaces, // number of resonances in the K-matrix
			      float _decay_m1,
			      float _decay_m2);     /// <! mass of the second decay particle
	/// Destructor
	virtual ~GPUDynamicalSumBW();
	/// virtual () operator; performs the actual stream calculation
	virtual GPUDataStream<float2> * operator()(int index =0, int block=0);


private:

	/// Mass of first decay particle
	const float m1_2;
	/// Mass of second decay particle
	const float m2_2;
	mutable GPUDataStream<float4>* mpars;
	unsigned int m_nresonances;
  GPUStreamScalar & mx123;
};

#endif /* GPUPROPAGATORMASSDEPENDENTBREITWIGNER_H_ */
