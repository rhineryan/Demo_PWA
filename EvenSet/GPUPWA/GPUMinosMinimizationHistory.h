///\file GPUMinosMinimizationHistory.h
/*
 * GPUMinosMinimizationHistory.h
 *
 *  Created on: Dec 4, 2008
 *      Author: nberger
 */

#ifndef GPUMINOSMINIMIZATIONHISTORY_H_
#define GPUMINOSMINIMIZATIONHISTORY_H_

#include "GPUMinimizationHistory.h"
#include <vector>

/// Class storing the results of a MINOS run
class GPUMinosMinimizationHistory: public GPUMinimizationHistory {
public:
	/// Constructor
	GPUMinosMinimizationHistory(GPUPartialWaveAnalysis* ana,
			   const ROOT::Minuit2::MnUserParameters _InputParameters,
			   const ROOT::Minuit2::MnUserParameters _ResultParameters,
			   const double minimumLikelihood,
			   const double EDM, const bool OK,
			   std::vector<double> downerr, std::vector<double> uperr);
	/// Destructor
	virtual ~GPUMinosMinimizationHistory();

	/// Print a set of parameters
	virtual void PrintParameters(ROOT::Minuit2::MnUserParameters  pars, ostream & out = cout) const;

protected:
	/// Storage for lower side errors
	std::vector<double> mdownerr;
	/// Storage for upper side errors
	std::vector<double> muperr;
};

#endif /* GPUMINOSMINIMIZATIONHISTORY_H_ */
