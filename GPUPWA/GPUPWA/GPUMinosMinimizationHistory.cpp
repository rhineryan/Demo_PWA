/*
 * GPUMinosMinimizationHistory.cpp
 *
 *  Created on: Dec 4, 2008
 *      Author: nberger
 */

#include "GPUMinosMinimizationHistory.h"
#include <iomanip>

using std::setw;


GPUMinosMinimizationHistory::GPUMinosMinimizationHistory(GPUPartialWaveAnalysis* ana,
		   const ROOT::Minuit2::MnUserParameters _InputParameters,
		   const ROOT::Minuit2::MnUserParameters _ResultParameters,
		   const double minimumLikelihood,
		   const double EDM, const bool OK,
		   std::vector<double> downerr, std::vector<double> uperr) :
			   GPUMinimizationHistory(ana, _InputParameters, _ResultParameters,
					   minimumLikelihood, EDM, OK), mdownerr(downerr), muperr(uperr)
{}

GPUMinosMinimizationHistory::~GPUMinosMinimizationHistory() {
}

void GPUMinosMinimizationHistory::PrintParameters(ROOT::Minuit2::MnUserParameters  pars, ostream & out) const{
	std::vector<double> pvec = pars.Params();
	for(int i=0; i < (int)pvec.size(); i++){
		cout << setw(2) <<  i << ":   " << setw(15) << pars.Name(i) << ": " << setw(10) <<pvec[i] << " +- " << setw(10) << pars.Error(i) << endl;
		cout << setw(21) << "          Minos errors: " <<  "  + " << setw(10) << muperr[i] <<  "  - " << mdownerr[i] << endl;
	}
}
