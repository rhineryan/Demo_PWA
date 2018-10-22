/// \file GPUFileTable.h

/*
 * GPUFileTable.h
 *
 *  Created on: Apr 24, 2009
 *      Author: nberger
 */

#ifndef GPUFILETABLE_H_
#define GPUFILETABLE_H_

#ifdef USECPU
#include "Tensors_cpu.h"
using namespace Tensors_CPU;
#else
#include "Tensors.h"
using namespace Tensors_GPU;
#endif

#include "float4444.h"
#include <cassert>


/// Class reading a tabular text file, creating objects and providing them to other objects
/** The goal of this class is to provide easy access to amplitudes etc. generated outside
 *  GPUPWA.
 */
template <typename T>
class GPUFileTable {
public:
	/// Constructor, specifying the file and the number of elements per line
	GPUFileTable(const char * filename, int nelements);
	/// Destructor
	virtual ~GPUFileTable();
	/// Number of elements in T
	static unsigned int datasize();
	/// access a column of the table
	virtual T * operator() (unsigned int index) {
		assert(index < mnelements);
		return mdata[index];};
	/// access an sub-column of the table (only for float4444s, which we organise in 16 float4s)
	virtual T * operator() (unsigned int index1, unsigned int index2){
		assert(0);
		return 0;};
	/// number of rows (events) in the table
	virtual unsigned int nevents() {return mnevents;};
	/// number of columns in the table
	virtual unsigned int nelements() {return mnelements;};
	/// check whether file was read ok
	virtual bool ok() {return mok;};

protected:
	/// number of elements per event
	const unsigned int mnelements;
	/// status of reading the file
	bool mok;
	/// the data table
	T ** mdata;
	/// number of events in the table
	unsigned int mnevents;
};

template <>
class GPUFileTable<float4444> {
public:
	/// Constructor, specifying the file and the number of elements per line
	GPUFileTable(const char * filename, int nelements);
	/// Destructor
	virtual ~GPUFileTable();
	/// Number of elements in T
	static unsigned int datasize();
	/// access a column of the table
	virtual float4444 * operator() (unsigned int index) {
		assert(0); return 0;};
	/// access an sub-column of the table (only for float4444s, which we organise in 16 float4s)
	virtual float44 * operator() (unsigned int index1, unsigned int index2){
		assert(datasize() == 256);
		assert(index1 < mnelements);
		assert(index2 < mnevents);
		return mdata[index1*16+index2];};
	/// number of rows (events) in the table
	virtual unsigned int nevents() {return mnevents;};
	/// number of columns in the table
	virtual unsigned int nelements() {return mnelements;};
	/// check whether file was read ok
	virtual bool ok() {return mok;};

protected:
	/// number of elements per event
	const unsigned int mnelements;
	/// status of reading the file
	bool mok;
	/// the data table
	float44 ** mdata;
	/// number of events in the table
	unsigned int mnevents;
};



/// File table containing scalars
typedef GPUFileTable<float> GPUScalarFileTable;
/// File table containing complex numbers
typedef GPUFileTable<float2> GPUComplexFileTable;
/// File table containing vectors
typedef GPUFileTable<float4> GPUVectorFileTable;
/// File table containing rank 2 tensors
typedef GPUFileTable<float44> GPUTensor2FileTable;
/// File table containing rank 3 tensors
typedef GPUFileTable<float444> GPUTensor3FileTable;


#endif /* GPUFILETABLE_H_ */
