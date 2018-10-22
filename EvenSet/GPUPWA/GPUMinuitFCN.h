/// \file GPUMinuitFCN.h

#pragma once

#include "Minuit2/FCNGradientBase.h"
#include "GPUPWACalculator.h"
#include "float44.h"

/// Implementation of the ROOT::Minuit2::FCNGradientBase interface implementing the callbacks to a GPUPWACalculator
class GPUMinuitFCN :
	public ROOT::Minuit2::FCNGradientBase
{
public:
	/// Constructor taking a pointer to a GPUPWACalculator doing the actual work
	GPUMinuitFCN(GPUPWACalculator * _calc);
	/// Destructor
	virtual ~GPUMinuitFCN(void);
	/// Check analytical gradients with numerical ones; not implemented
	virtual bool CheckGradient() const {return false;};
	/// Change of FCN for 1 sigma - 0.5 for log Likelihood
	virtual double Up() const {return 0.5;}; // Log Likelihood!
	/// Get the gradient vector
	virtual vector<double> Gradient(const vector<double> & x) const;
	/// Get the likelihood value
	virtual double operator() (const vector<double> & x) const;


protected:
	/// Pointer to the GPUPWACalculator doing all the work
	GPUPWACalculator * mCalc;
};






