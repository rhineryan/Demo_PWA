/// \file GPUFactorizedRadiativePartialWave.h
/*
 * GPUFactorizedRadiativePartialWave.h
 *
 *  Created on: May 9, 2011
 *      Author: nberger
 */

#ifndef GPUFACTORIZEDRADIATIVEPARTIALWAVE_H_
#define GPUFACTORIZEDRADIATIVEPARTIALWAVE_H_

#include "GPUFactorizedPartialWave.h"
#include "GPUGPerpStreamContainer.h"

/// Class representing a partial wave that factorizes into a scalar complex part and a real rank two tensor and is contracted using a GPerp tensor

class GPUFactorizedRadiativePartialWave: public GPUFactorizedPartialWave<float44>, public GPUGPerpStreamContainer {
public:
	/// Constructor
	GPUFactorizedRadiativePartialWave(GPUStreamTensor<float44> & _orbitalTensor, ///< (Real) orbital tensor, has to have the correct rank for the analysis
			 	 	 	 	 	 	  GPUScalarPropagator & _propagator,      ///< Complex propagator
			 	 	 	 	 	 	  char * _name);
	/// Destructor
	virtual ~GPUFactorizedRadiativePartialWave();

	/// Contract this wave with another one
	virtual GPUDataStream<float2> * Contract(GPUPartialWave * wave, unsigned int index, unsigned int block);

	/// Contract the parameter independent part of this wave with another one
	virtual GPUDataStream<float> * ContractOrbital(GPUPartialWave * wave, unsigned int index, unsigned int block);

	/// Check whether a wave combination has a parameter independent part
	virtual bool HasContractOrbital(GPUPartialWave * wave);

	 /// Increase the Usecount for the caching mechanism
	virtual void IncreaseUsecount(unsigned int index){
		mOrbitalTensor.IncreaseUsecount(index);
		mPropagator.IncreaseUsecount(index);
		mg_perp_stream->IncreaseUsecount(index);
	 };

};

#endif /* GPUFACTORIZEDRADIATIVEPARTIALWAVE_H_ */
