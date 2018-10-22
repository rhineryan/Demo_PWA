/// \file GPUPWAFreeCalculator.h
#pragma once
#include "GPUPWACalculator.h"
#include "Status.h"
#include "GPUPartialWaveAnalysis.h"

///Class performing likelihood, gradient and Hessian calculations on the GPU for fits with both production amplitudes and resonance parameters free
/** Note that this class contain the core algorithms of GPUPWA. It has been programmed with speed rather than
 *  easy reading in mind. The tensors and propagators are read in blocks of size GPUStreamTensor::Blocksize events
 *  and then packed into lookup tables of four-event vectors and GPUDataStream::Dimsize rows.The events in the last
 *  block (which is usually shorter than GPUDataStream::Dimsize) are often treated separately, hence the "short"
 *  version of the temporary streams
 *
 * The MC integration is repeated for every iteration in this class
 *
 * The current implementation does not support gradients and hessians, these features are foreseen for a future version
 */

class GPUPWAFreeCalculator :
	public GPUPWACalculator
{
public:
	/// Constructor
	GPUPWAFreeCalculator(GPUPartialWaveAnalysis  * _ana, ///< Mother analysis
			GPULookupTable * _datatable, ///< Lookup table to be used (data)
			GPULookupTable * _mctable, ///< Lookup table to be used (mc)
			std::vector<GPUDataStream<float4> **> _Weights ///< Event weights
			);
	/// Destructor, deleting all the temporary resources on the GPU
	virtual ~GPUPWAFreeCalculator(void);
	/// Calculate the negative log likelihood for a model with the given parameters
	virtual double Likelihood(const vector<double> & pars);
	/// Calculate the negative log likelihood and its gradient vector for a model with the given parameters (not yet supported)
	virtual double LikelihoodGradient(const vector<double> & pars, vector<double> & grad);
	/// Calculate the negative log likelihood, its gradient vector and the upper right half of the hessian matrix in the fumili approximation for a model with the given parameters (not yet supported)
	virtual double LikelihoodGradientHessian(const vector<double> & pars, vector<double> & grad, vector<double> & hessian);

	/// Write a file of MC integral coefficients
	/** For the case of free resonance parameters, the overhead for this is too big and we create the coefficients on the fly.
	 *  The function remains for compatibility reasons, but does nothing.
	**/
	virtual STATUS WriteMCIntegralFile(bool all = true, char * filename =0){return OK;};

	/// Read a file of MC integral coefficients
	/** For the case of free resonance parameters, the overhead for this is too big and we create the coefficients on the fly.
	 *  The function remains for compatibility reasons, but does nothing.
	**/
	virtual STATUS ReadMCIntegralFile(char * filename = 0){return OK;};

//	virtual float ** GetDcs(int index =0, bool dooffdiagonal = false, int nblocks = -1);

	/// Prepare lookup table for the fit
	void PrepareLookup4(int index);

 	/// get the total cross sctions of each partial wave
  virtual double** PartialTotalXSection(){return 0;};//dummy
  /// get the derivation of the total cross sctions of each partial wave
  virtual double** PartialTotalXSectionDerivative(int parnum){return 0;};//dummy

protected:
	/// Main work function performing the required calculations
	virtual double LikelihoodGradientHessianCalc(const vector<double> & pars, vector<double> & grad, vector<double> & hessian, bool dogradient = true, bool dohessian = true);
	// The serious stuff
	/// Calculate the MC integral coefficients for this partial wave analysis - dummy, as this is done per iteration
	virtual void MCIntegral(bool all = true){};

	/// Delete MC integral coefficients calaulated earlier
	void clearMCIntegralCoefficients(){};
	/// Reserve memory for MC integral coefficients from nwaves
	void initMCIntegralCoefficients(int nwaves){};

	/// Clean up all the intermediate and temporary streams used in the fit
	void cleanupFit();

	/// matrix of parameter-wave relations used for gradients;
	float ** mParmatrix;


	/// Mother analysis
	/** Here we now the type of analysis (rank of the partial waves),
	 * so we deliberately hide the mAna member of the base class
	 */
	GPUPartialWaveAnalysis * mAna;

	/// Data Lookup table
	GPULookupTable * mLookupData;
	/// MC lookup table
	GPULookupTable * mLookupMC;

	/// Number of coefficient 2D arrays
	int mNCoefficientBlocksData;
	/// Number of events in last block
	int mNAdditionalEventsData;

	/// Number of coefficient 2D arrays
	int mNCoefficientBlocksMC;
	/// Number of events in last block
	int mNAdditionalEventsMC;


	/// Resources on the GPU used for the fit are initialised
	bool mFitinit;

	/// Stream storing the dcs values (from LH calculation to gradient calculation)
	GPUDataStream<float4> ** mdcs;
	/// Stream storing the eventwise log likelihoods
	GPUDataStream<float4> * mlogdcs;

	/// Stream storing the eventwise log likelihoods (short version)
	GPUDataStream<float4> * mshortlogdcs;

	/// Stream storing the eventwise dcs (MC)
	GPUDataStream<float4> * mdcsmc;
	/// Stream storing the eventwise dcs (short version, MC)
	GPUDataStream<float4> * mshortdcsmc;



	/// Size of the parameter vector
	int mpsize;


	/// Count number of fit iterations
	int counter;
	/// Vector of iteration times
	std::vector<double> mfittimes;

};
