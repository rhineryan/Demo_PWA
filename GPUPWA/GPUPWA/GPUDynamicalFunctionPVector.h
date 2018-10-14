///  \file  GPUDynamicalFunctionPVector.h
/*
 *
 *
 *
 *
 *
 *  Created on: April 8, 2011
 *      Author: liubj
 */




#ifndef GPUDYNAMICALFUNCTIONPVECTOR_H_
#define GPUDYNAMICALFUNCTIONPVECTOR_H_

#include "GPUBasicPropagator.h"
#include "ResCfg.h"
#include "ParaCfg.h"
#include <vector>
/// Propagator class implementing a mass dependent Breit-Wigner
/**
 *   The Breit-Wigner form used here is
 *	 \f$ BW(m_{x}^{2}) = \frac{1}{m_{x}^{2} -m_{r}^{2} + i m_{x} \Gamma_{m_{x}}} \f$
 *	 with
 *	 \f$ \Gamma_{m_{x}} = \Gamma(m_{r}^{2}) \frac{ m_{r}^{2}}{ m_{x}^{2}}\left(\frac{p(m_{x}^{2})}{p(m_{r}^{2})}  \right)^{2\ell+1} \f$
 *	 and \f$ p(s) \f$ the momentum of the decay particles in the mother rest frame.
 *	 The derivatives of this function with regard to the resonance mass is a bit ugly and has been evaluated in MAPLE.
 *
 */

class GPUDynamicalFunctionPVector: public GPUBasicPropagator{
public:
	/// Constructor taking mass and width
  GPUDynamicalFunctionPVector(char * name,
			      GPUStreamScalar & _mx2, /// <! Stream with center of mass energy squared
			      std::vector<char **> _parnames,// parameter names; each resonance have (m,w), (gx,gy); and there are 4 poly.terms (6 paramaters) in the P-vector c, cs, (dx,dy), (dsx, dsy);
			      unsigned int _nresnonaces, // number of resonances in the K-matrix
			      float _decay_m1,
			      float _decay_m2);     /// <! mass of the second decay particle
	/// Destructor
	virtual ~GPUDynamicalFunctionPVector();
	/// virtual () operator; performs the actual stream calculation
	virtual GPUDataStream<float2> * operator()(int index =0, int block=0);


private:

	/// Mass of first decay particle
	const float m1_2;
	/// Mass of second decay particle
	const float m2_2;
	mutable GPUDataStream<float4>* mpars;
	unsigned int m_nresonances;
};

#endif /* GPUPROPAGATORMASSDEPENDENTBREITWIGNER_H_ */
