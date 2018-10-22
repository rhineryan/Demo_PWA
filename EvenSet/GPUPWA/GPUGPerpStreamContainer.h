/// \file GPUGPerpStreamContainer.h


/*
 * GPUGPerpStreamContainer.h
 *
 *  Created on: May 9, 2011
 *      Author: nberger
 */

#ifndef GPUGPERPSTREAMCONTAINER_H_
#define GPUGPERPSTREAMCONTAINER_H_

class GPUStreamTensor2;

/// Class needed for partial waves that need a GPerp tensor in contractions
/***
 * Sole purpose is the storage of the GPerp tensor
 */

class GPUGPerpStreamContainer {
public:
	/// Constructor
	GPUGPerpStreamContainer();

	/// Destructor
	virtual ~GPUGPerpStreamContainer();

	/// Get g_mu_nu^(perp perp) used in the contraction for radiative decays to mesons
	GPUStreamTensor2 * GetGPerpStream(){return mg_perp_stream;};
	/// Set g_mu_nu^(perp perp) used in the contraction for radiative decays to mesons
	void SetGPerpStream(GPUStreamTensor2 * _gperp){mg_perp_stream = _gperp;};


protected:
	///  \f$g_{\perp\perp}\f$ used in the contraction for radiative decays to mesons
	static GPUStreamTensor2 * mg_perp_stream;
};

#endif /* GPUGPERPSTREAMCONTAINER_H_ */
