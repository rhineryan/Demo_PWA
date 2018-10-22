/// \file GPUMainMemoryLookupTable.h

/*
 * GPUMainMemoryLookupTable.h
 *
 *  Created on: Apr 27, 2011
 *      Author: nberger
 */

#ifndef GPUMAINMEMORYLOOKUPTABLE_H_
#define GPUMAINMEMORYLOOKUPTABLE_H_

#include "GPULookupTable.h"

/// Lookup table using contracted amplitudes stored in main memory obtained from outside GPUPWA
/*** If there is a source of contracted amplitudes (\f$A_iA_j\f$s) outside of the GPUPWA framework
 * (e.g. FDC),  they should be fed into the framework through this interface. This lookup table can
 * then replace partial waves if it is set as the data source of a GPUPartialWaveAnalysis via the
 * GPUPartialWaveAnalysis::SetLookupTable() method.
 *
 * The coefficients come as 2D arrays, with the indices as follows array[event][wavecombination]
 * where event is the event index and wavecombination counts through the upper right part of the
 * \f$A_iA_j\f$ matrix, e.g. for three waves there should be \f$A_0A_0\f$, \f$A_0A_1\f$, \f$A_0A_2\f$,
 * \f$A_1A_1\f$, \f$A_1A_2\f$ and \f$A_2A_2\f$. The size of the array should thus be nevents in the
 * first dimension and nwaves*(nwaves+1)/2 in the second dimension
 *
 */

class GPUMainMemoryLookupTable: public GPULookupTable {
public:
	/// Constructor taking real and imaginary parts
	GPUMainMemoryLookupTable(float ** coefficientsx, ///< Real part of the coefficients
							 float ** coefficientsy, ///< Imaginary part of the coefficients
							 const DeviceInterface * dev, ///< Device interface for LUT storage
			   	   	   	   	 unsigned int nevents, ///< Number of events
			   	   	   	   	 unsigned int nwaves,  ///< Number of waves
			   	   	   	   	 unsigned int blocksize=GPUDataStream<float4>::DIMSIZE); ///< Size of one block
	GPUMainMemoryLookupTable(float2 ** coefficients, ///< Coefficients as complex numbers
							 const DeviceInterface * dev,///< Device interface for LUT storage
			   	   	   	   	 unsigned int nevents, ///< Number of events
			   	   	   	   	 unsigned int nwaves, ///< Number of waves
			   	   	   	   	 unsigned int blocksize=GPUDataStream<float4>::DIMSIZE);///< Size of one block
	GPUMainMemoryLookupTable(float4 ** coefficientsx, ///< Real part of the coefficients, 4 events in one float4
							 float4 ** coefficientsy, ///< Imaginary part of the coefficients, 4 events in one float4
							 const DeviceInterface * dev,///< Device interface for LUT storage
			   	   	   	   	 unsigned int nevents, ///< Number of events
			   	   	   	   	 unsigned int nwaves, ///< Number of waves
			   	   	   	   	 unsigned int blocksize=GPUDataStream<float4>::DIMSIZE); ///< Size of one block
	/// Destructor
	virtual ~GPUMainMemoryLookupTable();

	/// Copy main memory to GPU
	virtual void FillTable();
	/// Copy one block from main memory to GPU
	virtual void FillTable(unsigned int block);

protected:
	/// Bring main memory data into a format where they can be written to GPU
	virtual void ReformatTable();
	/// Bring main memory data into a format where they can be written to GPU for one block
	virtual void ReformatTable(unsigned int block);

	/// Formatted data in main memory, real part
	float4 ** mcpucoefficientsx;
	/// Formatted data in main memory, imaginary part
	float4 ** mcpucoefficientsy;
	/// Unformatted data in main memory, complex numbers
	float2 ** mcpucoefficients;

	/// Pointer to input data, real part
	float ** mincoefficientsx;
	/// Pointer to input data, imaginary part
	float ** mincoefficientsy;

	/// Remeber whether cleanup of is needed
	bool mallocated;
};

#endif /* GPUMAINMEMORYLOOKUPTABLE_H_ */
