/// \file GPUFumiliMinimize.h
#pragma once

#include "TFumili.h"
#include "GPUPWACalculator.h"
#include "Minuit2/MnUserParameters.h"

/// GPUPWA implementation of FUMILI, similar to BES II version
class GPUFumiliMinimize :
	public TFumili
{
public:
	/// Constructor, taking a GPUPWACalculator that does the work
	GPUFumiliMinimize(GPUPWACalculator * _calc);
	/// Destructor
	virtual ~GPUFumiliMinimize(void);
	/// Do alikelihhod fit
	virtual void FitLikelihood(Int_t &npar, Double_t *gin, Double_t &f, Double_t *u, Int_t flag);
	/// Set the Parameters
	virtual void SetParameters();
	/// Set the fit method
	virtual void SetFitMethod();
	/// Evaluate the target function
	double         EvalTFN(double *,double*);
	/// Get the currently used set of parameters
	const ROOT::Minuit2::MnUserParameters GetParameters() const;

protected:
	/// Initialize and reset
   virtual void InitAndReset(unsigned int npar) {
	   SetParNumber((int)npar);
      mNpar = npar;
      mPara = std::vector<double>(npar);
      mGrad = std::vector<double>(npar);
      mHess = std::vector<double>(static_cast<int>( 0.5*npar*(npar+1) ));
   }

   /// Associated calculator
   mutable GPUPWACalculator * mCalc;
   /// Number of parameters
   unsigned int mNpar;
   /// Vector of parameter values
   std::vector<double> mPara;
   /// Vector of gradients with respect to parameters
   std::vector<double> mGrad;
   /// Vector containing the upper right part of the Hessian matrix in the Fumili approximation
   std::vector<double> mHess;

};



