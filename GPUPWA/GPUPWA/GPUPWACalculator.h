/// \file GPUPWACalculator.h

#pragma once
#include <vector>
#include "GPUSetOfPartialWaves.h"
#include "GPUPartialWaveAnalysis.h"
#include "Status.h"

using std::vector;

///Abstract base class defining the interface for a calculation class
class GPUPWACalculator
{
public:
	/// Constructor
	GPUPWACalculator(GPUPartialWaveAnalysis * _ana, /// Mother analysis
					std::vector<GPUDataStream<float4> **> _Weights /// Event weights
					);
	/// Destructor
	virtual ~GPUPWACalculator(void);
	/// Get mother analysis
	virtual const GPUPartialWaveAnalysis * GetAnalysis() const {return mAna;};

	/// Calculate the negative log likelihood for a model with the given parameters
	virtual double Likelihood(const vector<double> & pars) = 0;
	/// Calculate the negative log likelihood and its gradient vector for a model with the given parameters
	virtual double LikelihoodGradient(const vector<double> & pars, vector<double> & grad) =0;
	/// Calculate the negative log likelihood, its gradient vector and the upper right half of the hessian matrix in the fumili approximation for a model with the given parameters
	virtual double LikelihoodGradientHessian(const vector<double> & pars, vector<double> & grad, vector<double> &hessian) =0;

	/// Write a file of MC integral coefficients
	/** This function will call MCIntegral() if necessary.
	The output is a textfile of number pairs (complex values), representing the values in and above the diagonal of the
	AiAj coefficient matrix -> the diagaonal values should all be real.
	**/
	virtual STATUS WriteMCIntegralFile(bool all = true, char * filename =0) =0;
	/// get the total cross sctions of each partial wave
	virtual double** PartialTotalXSection()=0;
	/// get the derivation of the total cross sctions of each partial wave
	virtual double** PartialTotalXSectionDerivative(int parnum)=0;

protected:


	/// "Mother" Partial wave analysis (needed for event numbers etc.)
	GPUPartialWaveAnalysis * mAna;
	/// Device interface, taken from mother analysis
	const DeviceInterface * mdev;
	/// Streams of event weights
	std::vector<GPUDataStream<float4> **> mWeights;

	// The serious stuff
	/// Calculate the MC integral coefficients for this partial wave analysis
	/** /param all: Select wheter the parameters should be calculated for all (recommended) or only the active waves
		On calling this function, all input streams should be linked to the correct MC data files
		If it is needed in the contraction (radiative decay to mesons), g_mu_nu^(perp perp) has to be set
	**/
	virtual void MCIntegral(bool all = true) = 0;

	/// Read a file of MC integral coefficients
	virtual STATUS ReadMCIntegralFile(char * filename = 0) =0;

};
