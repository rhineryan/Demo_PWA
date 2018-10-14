///  \file  GPUPropagatorMassDependentBreitWigner.h
/*
 *
 *
 *
 *
 *
 *  Created on: Feb 16, 2009
 *      Author: nberger
 */




#ifndef GPUPROPAGATORMASSDEPENDENTBREITWIGNER_H_
#define GPUPROPAGATORMASSDEPENDENTBREITWIGNER_H_

#include "GPUBasicPropagator.h"
#include "GPUPropagatorDerivative.h"
#include "ResCfg.h"

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

class GPUPropagatorMassDependentBreitWigner: public GPUBasicPropagator, public GPUPropagatorDerivative {
public:
	/// Constructor taking mass and width
	GPUPropagatorMassDependentBreitWigner(char * name,
										  GPUStreamScalar & _mx2, /// <! Stream with center of mass energy squared
										  int _l,                  /// <! angular momentum l
										  float _decay_m1, 		/// <! mass of the first decay particle
										  float _decay_m2);     /// <! mass of the second decay particle
	/// Destructor
	virtual ~GPUPropagatorMassDependentBreitWigner();
	/// virtual () operator; performs the actual stream calculation
	virtual GPUDataStream<float2> * operator()(int index =0, int block=0);
	/// Get a stream of the derivative of the propagator with regards to the mass
	virtual GPUDataStream<float2> * GetMassDerivative(int index, int block);
	/// Get a stream of the derivative of the propagator with regards to the width
	virtual GPUDataStream<float2> * GetWidthDerivative(int index, int block);
	/// Get a stream of the derivative of the |propagator|^2 with regards to the mass
	virtual GPUDataStream<float> * GetAbsMassDerivative(int index, int block);
	/// Get a stream of the derivative of the |propagator|^2 with regards to the width
	virtual GPUDataStream<float> * GetAbsWidthDerivative(int index, int block);

private:
	/// Decay momentum as a function of resonance mass
	float p_mr(float mr);
	/// Derivative of decay momentum as a function of resonance mass
	float dp_mr(float mr);
	/// Angular momentum
	const int m_l;
	/// Mass of first decay particle
	const float m1_2;
	/// Mass of second decay particle
	const float m2_2;
};

#endif /* GPUPROPAGATORMASSDEPENDENTBREITWIGNER_H_ */
