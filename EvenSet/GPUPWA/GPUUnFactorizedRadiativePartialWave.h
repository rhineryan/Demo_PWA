/// \file GPUUnFactorizedRadiativePartialWave.h

/*
 * GPUUnFactorizedRadiativePartialWave.h
 *
 *  Created on: May 9, 2011
 *      Author: nberger
 */

#ifndef GPUUNFACTORIZEDRADIATIVEPARTIALWAVE_H_
#define GPUUNFACTORIZEDRADIATIVEPARTIALWAVE_H_

#include "GPUUnFactorizedPartialWave.h"
#include "GPUGPerpStreamContainer.h"

/// Class representing a partial wave that does not factorize into a scalar complex part and a real rank two tensor and is thus represented by a rank2 complex tensor and is contracted using a GPerp tensor
class GPUUnFactorizedRadiativePartialWave: public GPUUnFactorizedPartialWave<float44>,
		public GPUGPerpStreamContainer {
public:
	/// Constructor
	GPUUnFactorizedRadiativePartialWave(GPUPropagatorType<float44> & _propagator,      ///< Complex propagator
			 	 	 	 	 	 	 	 	   char * _name);                    ///< Name for the wave
	/// Destructor
	virtual ~GPUUnFactorizedRadiativePartialWave();

	/// Contract this wave with another one
	virtual GPUDataStream<float2> * Contract(GPUPartialWave * wave, unsigned int index, unsigned int block);

	/// Core functionality: Contract parameter independent parts with another wave to a scalar number stream
	/** Will return 0, as there is no parameter-independent part, has to be checked by the calling function
	 */
	virtual GPUDataStream<float> * ContractOrbital(GPUPartialWave * wave, unsigned int index, unsigned int block){return 0;};

	/// Check whether a wave combination has a parameter independent part
	virtual bool HasContractOrbital(GPUPartialWave * wave){return false;};

	/// Increase the Usecount for the caching mechanism
	virtual void IncreaseUsecount(unsigned int index){
		mPropagator.IncreaseUsecount(index);
		mg_perp_stream->IncreaseUsecount(index);
	};

};

#endif /* GPUUNFACTORIZEDRADIATIVEPARTIALWAVE_H_ */
