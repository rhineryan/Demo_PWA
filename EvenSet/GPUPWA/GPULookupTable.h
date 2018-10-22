/// \file GPULookupTable.h

/*
 * GPULookupTable.h
 *
 *  Created on: Apr 27, 2011
 *      Author: nberger
 */

#ifndef GPULOOKUPTABLE_H_
#define GPULOOKUPTABLE_H_

#include"GPUDataStream.h"

class DeviceInterface;

/// Abstract base class for lookup tables, holding the AiAj values
/** GPU storage needed by a lookup table is nevents * nwaves * (nwaves+1) floats
 *
 */
class GPULookupTable {
public:
	/// Constructor
	GPULookupTable(const DeviceInterface * dev, /// < Device on which this lookup table is stored
				   unsigned int nevents,        ///< Number of events
				   unsigned int nwaves,         ///< Number of partial waves
				   unsigned int blocksize=GPUDataStream<float4>::DIMSIZE); ///< Size of one block
	/// Destructor
	virtual ~GPULookupTable();

	/// Get the real part of the coefficients
	virtual GPUDataStream<float4> * GetCoefficientsX(unsigned int block);
	/// Get the imaginary part of the coefficients
	virtual GPUDataStream<float4> * GetCoefficientsY(unsigned int block);

	/// Make sure the lookup table is recalculated before next use
	virtual void invalidateCache();
	/// Make sure that block of the lookup table is recalculated before next use
	virtual void invalidateCache(unsigned int block);


	/// Get the number of waves in this table
	virtual const unsigned int GetNWaves() const{return mnwaves;};
	/// Get the number of blocks in this table
	virtual const unsigned int GetNBlocks() const{return mnblocks;};
	/// Get the size of the last block
	virtual const unsigned int GetNAdditional() const{return mnadditionalsize;};


	/// Fill the table - needs to be implemented by derived classes
	virtual void FillTable() = 0;

	/// Check whether the cached values are still ok with the current parameters
	virtual bool CacheValid(){
		bool val = true;
		for(unsigned int i=0; i < mnblocks; i++)
			val = val && mcachevalid[i];
			return val;
	};

protected:


	/// Allocate the GPU memory for this lookup table
	virtual void AllocateMemory();

	/// Device interface on which the table resides
	const DeviceInterface * mdev;
	/// Number of blocks
	const unsigned int mnblocks;
	/// Number of events
	const unsigned int mnevents;
	/// Size of one block
	const unsigned int mblocksize;
	/// Number of events in last block
	const unsigned int mnadditionalevents;
	/// Size of last block
	const unsigned int mnadditionalsize;
	/// 2nd dimension size of table
	const unsigned int mdim;
	/// Number of waves
	const unsigned int mnwaves;
	/// Booleans registering whether cached values are still ok
	bool * mcachevalid;

	/// The actual lookup table, real part
	GPUDataStream<float4> ** mcoefficientsx;
	/// The actual lookup table, imaginary part
	GPUDataStream<float4> ** mcoefficientsy;
};

#endif /* GPULOOKUPTABLE_H_ */
