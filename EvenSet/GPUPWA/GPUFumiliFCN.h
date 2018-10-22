/// \file GPUFumiliFCN.h
#pragma once

#include "Minuit2/FumiliFCNBase.h"
#include "GPUPWACalculator.h"

///Function to be minimized by FUMILI
/** Derived from the corresponding class in ROOT::Minuit2, this function implements the appropriate
 * callbacks to a GPUPWACalculator providing Likelihoods, Gradients and Fumili Hessians.
 *
 */

class GPUFumiliFCN :
	public ROOT::Minuit2::FumiliFCNBase
{
public:
	/// Constructor taking apointer to a GPUPWACalculator doing the actual work
	GPUFumiliFCN(GPUPWACalculator * _calc);
	/// Destructor
	virtual ~GPUFumiliFCN(void);
	/// Call the GPUPWACalculator::GradientLikelihoodHessian() method and cache results
	virtual void EvaluateConst(const std::vector<double> & par) const;
	/// Call Evaluate const
	virtual void EvaluateAll(const std::vector<double> & par);
	/// Call evaluate const, return Likelihood
	virtual double operator() (const std::vector<double> & par)const;
	/// "One sigma", 0.5 for Log Likelihood
	virtual double Up() const {return 0.5;}; // Log Likelihood!
protected:
	/// Pointer to the calculator class
	mutable GPUPWACalculator * mCalc;
};



