/// \file GPUPartialWaveLookupTable.h

/*
 * GPUPartialWaveLookupTable.h
 *
 *  Created on: May 9, 2011
 *      Author: nberger
 */

#ifndef GPUPARTIALWAVELOOKUPTABLE_H_
#define GPUPARTIALWAVELOOKUPTABLE_H_

#include "GPULookupTable.h"
#include "GPUParameterDependentObject.h"
#include "GPUSetOfPartialWaves.h"

/// Class representing a lookup table filled from GPUPartialWave objects
class GPUPartialWaveLookupTable: public GPULookupTable,
		public GPUParameterDependentObject {
public:
	/// Constructor
	GPUPartialWaveLookupTable(GPUSetOfPartialWaves * _waveset, ///< Set of partial waves
							unsigned int index=0); ///< Index, specifying the data set (data/MC)
	/// Destructor
	virtual ~GPUPartialWaveLookupTable();

	/// Fill the table from the partial waves
	virtual void FillTable();

	/// Check whether the cache is valid
	virtual bool CacheValid(){
		return GPULookupTable::CacheValid() && GPUParameterDependentObject::CacheValid(mindex);
	}
protected:
	/// The set of partial waves to be used
	GPUSetOfPartialWaves * const mwaveset;
	/// The index of the data set (data/MC) to be used
	const unsigned int mindex;
	/// Indicator of already filled slots in table
	unsigned int * mfilled;
};

#endif /* GPUPARTIALWAVELOOKUPTABLE_H_ */
