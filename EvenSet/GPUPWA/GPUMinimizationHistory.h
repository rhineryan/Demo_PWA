/// /file GPUMinimizationHistory.h
/*
 * GPUMinimizationHistory.h
 *
 *  Created on: Dec 2, 2008
 *      Author: nberger
 */

#ifndef GPUMINIMIZATIONHISTORY_H_
#define GPUMINIMIZATIONHISTORY_H_

#include "Minuit2/MnUserParameters.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ofstream;
using std::ostream;

class GPUPartialWaveAnalysis;

/// Class for storing, printing and saving Inputs and Results of a minimization
/**
 *
 *
 */
class GPUMinimizationHistory {
public:
	/// Constructor
	GPUMinimizationHistory(GPUPartialWaveAnalysis* ana,
						   const ROOT::Minuit2::MnUserParameters _InputParameters,
						   const ROOT::Minuit2::MnUserParameters _ResultParameters,
						   const double minimumLikelihood,
						   const double EDM, const bool OK, const int Niterations =0);
	/// Destructor
	virtual ~GPUMinimizationHistory();
	/// Get the input parameter set used
	ROOT::Minuit2::MnUserParameters GetInputParameters() const {return m_InputParameters;};
	/// Get the result parameters
	ROOT::Minuit2::MnUserParameters GetResultParameters() const {return m_ResultParameters;};
	/// Get the minimum likelihood
	virtual double GetMinimumLikelihood() const {return m_minimumLikelihood;};
	/// Get the estimated distance to minimum (i.e. the estimated error on the minimum likelihood)
	virtual double GetEDM() const {return mEDM;};
	/// Check whether Fit Converged ok
	virtual bool Converged() const {return mOK;};
	/// Print the complete information
	virtual void Print(ostream & out = cout);
	/// Print Information on PWA Analysis
	virtual void PrintAnalysis(ostream & out = cout);
	/// Print Partial Wave information
	virtual void PrintWaves(ostream & out = cout) const;
	/// Print the Input Information
	virtual void PrintInput(ostream & out = cout) const;
	/// Print the output information
	virtual void PrintResult(ostream & out = cout) const;
	/// Print the fit information
	virtual void PrintFitInfo(ostream & out = cout) const;
	/// Print a set of parameters
	virtual void PrintParameters(ROOT::Minuit2::MnUserParameters  pars, ostream & out = cout) const;
//add by lixl 
        /// Print the Input Information of para.inp 
	virtual void PrintInputPara(ostream & out = cout) const;
	/// Print the output information of para.inp 
	virtual void PrintOutputPara(ostream & out = cout) const;
        /// Print the Input Information of res.inp 
	virtual void PrintInputRes(ostream & out = cout) const;
	/// Print the output information of res.inp 
	virtual void PrintOutputRes(ostream & out = cout) const;
	/// Print a set of resonance parameters
	virtual void PrintResParameters(ROOT::Minuit2::MnUserParameters  pars, ostream & out = cout) const;
	/// Print a set of magnitude/phase parameters
	virtual void PrintParaParameters(ROOT::Minuit2::MnUserParameters  pars, ostream & out = cout) const;
 
private:
	/// And the Analysis where we got all the information from
	GPUPartialWaveAnalysis * mana;
	/// Input Parameters to the Fit
	const ROOT::Minuit2::MnUserParameters m_InputParameters;
	/// Parameter Values at the End of the Fit
	const ROOT::Minuit2::MnUserParameters m_ResultParameters;
	/// Minimum Likelihood as determined by the Fit
	const double m_minimumLikelihood;
	/// Estimated Distance to Minimum from the Fit
	const double mEDM;
	/// Fit Converged?
	const bool mOK;
	/// Number of iterations used
	const int mNiterations;
	/// Names of the active partial waves
	std::vector<char *> mWaveNames;
	/// Magnitude parameters of the active partial waves
	std::vector<unsigned int> mMagnitudeParameters;
	/// Phase parameters of the active partial waves
	std::vector<unsigned int> mPhaseParameters;
	/// Dynamic parameters of the active partial waves
	std::vector<unsigned int *> mDynamicParameters;
	/// Number of dynamic parameters of the active partial waves
	std::vector<unsigned int> mNDynamicParameters;

};

#endif /* GPUMINIMIZATIONHISTORY_H_ */
