/// \file GPUPWAAmplitudeCalculator.h
#pragma once
#include "GPUPWACalculator.h"
#include "Status.h"

class GPULookupTable;

///Class performing likelihood, gradient and Hessian calculations on the GPU for fits with production amplitudes as the only free parameters
/** Note that this class contain the core algorithms of GPUPWA. It has been programmed with speed rather than
 *  easy reading in mind. The tensors and propagators are read in blocks of size GPUStreamTensor::Blocksize events
 *  and then packed into lookup tables of four-event vectors and GPUDataStream::Dimsize rows.The events in the last
 *  block (which is usually shorter than GPUDataStream::Dimsize) are often treated separately, hence the "short"
 *  version of the temporary streams
 *
 */
class GPUPWAAmplitudeCalculator :
	public GPUPWACalculator
{
public:
	/// Constructor
	GPUPWAAmplitudeCalculator(GPUPartialWaveAnalysis  * _ana, ///< Mother partial wave analysis
							 GPULookupTable * _datatable, ///< Lookup table for data
							 GPULookupTable * _mctable, ///< Lookup table for MC
							 std::vector<GPUDataStream<float4> **> _Weights, /// Event weights
							 char * _mcintegralfilename =0 /// Name of a file with a precalculated MC integral (optional)
							 );
	/// Destructor - will clean up all the streams on the GPU
	virtual ~GPUPWAAmplitudeCalculator(void);
	/// Calculate the negative log likelihood for a model with the given parameters
	virtual double Likelihood(const vector<double> & pars);
	/// Calculate the negative log likelihood and its gradient vector for a model with the given parameters
	virtual double LikelihoodGradient(const vector<double> & pars, vector<double> & grad);
	/// Calculate the negative log likelihood, its gradient vector and the upper right half of the hessian matrix in the fumili approximation for a model with the given parameters
	virtual double LikelihoodGradientHessian(const vector<double> & pars, vector<double> & grad, vector<double> & hessian);

	/// Write amplitudes for the current parameter set to a file
	virtual STATUS GetAmplitudes(const vector<double> & pars, char * filename);

	/// Write a file of MC integral coefficients
	/** This function will call MCIntegral() if necessary.
	The output is a textfile of number pairs (complex values), representing the values in and above the diagonal of the
	AiAj coefficient matrix -> the diagaonal values should all be real.
	**/
	virtual STATUS WriteMCIntegralFile(bool all = true, char * filename =0);

	/// Read a file of MC integral coefficients
	virtual STATUS ReadMCIntegralFile(char * filename = 0);

	/// Get the differential cross section values
	virtual float ** GetDcs(unsigned int index =0, ///< index (data or MC)
							bool dooffdiagonal = false, ///< calculate the interference terms
							int nblocks = -1 ///< if larger than 0, a subset of nblocks of the data will be used
							);


	/// get the total cross ssctions of each partial wave
	virtual double** PartialTotalXSection();
	/// get the derivation of the total cross ssctions of each partial wave
	virtual double** PartialTotalXSectionDerivative(int parnum);

protected:
	/// Main work function performing the required calculations
	virtual double LikelihoodGradientHessianCalc(const vector<double> & pars, vector<double> & grad, vector<double> & hessian, bool dogradient = true, bool dohessian = true);
	/// Calculate the MC integral of the total cross section
	double TotalXSection();
	/// Calculate the MC integral of the total cross derivative
	double TotalXSectionDerivative(int parnum);
		// The serious stuff
	/// Calculate the MC integral coefficients for this partial wave analysis
	/** /param all: Select wheter the parameters should be calculated for all (recommended) or only the active waves
		On calling this function, all input streams should be linked to the correct MC data files
		If it is needed in the contraction (radiative decay to mesons), g_mu_nu^(perp perp) has to be set
	**/
	virtual void MCIntegral(bool all = true);

	/// Delete MC integral coefficients calaulated earlier
	void clearMCIntegralCoefficients();
	/// Reserve memory for MC integral coefficients from nwaves
	void initMCIntegralCoefficients(unsigned int nwaves);

	/// Clean up all the intermediate and temporary streams used in the fit
	void cleanupFit();

	/// matrix of parameter-wave realtions used for gradients;
	float ** mParmatrix;


	/// Mother analysis
	/** Here we now the type of analysis (rank of the partial waves),
	 * so we deliberately hide the mAna member of the base class
	 */
	GPUPartialWaveAnalysis * mAna;

	/// Lookup table
	GPULookupTable *  mLookupTable;
	/// Lookup table
	GPULookupTable *  mMCLookupTable;

	/// Number of coefficient 2D arrays
	int mNCoefficientBlocks;
	/// Number of events in last block
	int mNAdditionalEvents;

	/// Number of coefficient 2D arrays
	int mNMCCoefficientBlocks;
	/// Number of events in last block
	int mNMCAdditionalEvents;

	/// Stored MC integral coefficients
	double2 ** mMCIntegralCoefficients;
	/// Number of MC integral coefficients (used for memory management)
	int mNMCIntegralCoefficients;

	/// Resources on the GPU used for the fit are initialised
	bool mFitinit;

	// GPU ressources for fit
	/// Stream storing the dcs values (from LH calculation to gradient calculation)
	GPUDataStream<float4> ** mdcs;
	/// Stream storing the eventwise log likelihoods
	GPUDataStream<float4> * mlogdcs;
	/// Stream storing the eventwise log likelihoods (short version)
	GPUDataStream<float4> * mshortlogdcs;

	/// Gradients of the total X-section
	GPUDataStream<float> * mdtcs;

	/// Gradient index
	GPUDataStream<int> * mgradindex;



	/// 2-D stream containing gradients
	GPUDataStream<float4> * mgradients;
	/// 2-D stream containing gradients (short version)
	GPUDataStream<float4> * mshortgradients;
	/// 2-D streams containing inner gradients for use in hessian calculation
	GPUDataStream<float4> ** minnergradients;


	/// Size of the parameter vector
	int mpsize;
	/// Number of gradients
	int mngrad;

	/// 2-D Stream holding elements of the hessian matrix
	GPUDataStream<float4> * mhessian;
	/// 2-D Stream holding elements of the hessian matrix (short version)
	GPUDataStream<float4> * mshorthessian;

	/// Mask of wave-parameter relations used in the gradient calculation
	GPUDataStream<float> * mmask;

	/// Count number of fit iterations
	int counter;

	/// Vector of iteration times
	std::vector<double> mfittimes;

};
