/*
 * GPULookupTable.cpp
 *
 *  Created on: Apr 27, 2011
 *      Author: nberger
 */

#include "GPULookupTable.h"

#include "Opencl_interface/DeviceInterface.h"
#include <cassert>

GPULookupTable::GPULookupTable(const DeviceInterface * dev, unsigned int nevents, unsigned int nwaves, unsigned int blocksize):
	mdev(dev),
	mnblocks(nevents/(blocksize*4) + ((nevents%(blocksize*4))?1:0)),
	mnevents(nevents),
	mblocksize(blocksize),
	mnadditionalevents(nevents%(blocksize*4)),
	mnadditionalsize(mnadditionalevents/4 + ((mnadditionalevents%4)?1:0)),
	mdim(nwaves*(nwaves+1)/2),
	mnwaves(nwaves),
	mcachevalid(new bool[mnblocks]),
	mcoefficientsx(new GPUDataStream<float4> * [mnblocks]),
	mcoefficientsy(new GPUDataStream<float4> * [mnblocks])
{
	for(unsigned int i = 0; i < mnblocks; i++){
		mcachevalid[i] = false;
		mcoefficientsx[i]  = 0;
		mcoefficientsy[i]  = 0;
	}
}

GPULookupTable::~GPULookupTable() {
	delete[] mcachevalid;
	for(unsigned int i = 0; i < mnblocks; i++){
		if(mcoefficientsx[i])
			delete mcoefficientsx[i];
		if(mcoefficientsy[i])
			delete mcoefficientsy[i];
	}
	delete[]  mcoefficientsx;
	delete[]  mcoefficientsy;
}

GPUDataStream<float4> * GPULookupTable::GetCoefficientsX(unsigned int block){
	assert(block <= mnblocks);
	if(!(mcachevalid[block] && mcoefficientsx[block])){
		//cout << "refilling... " << endl;
		FillTable();
	}
	return mcoefficientsx[block];
}

GPUDataStream<float4> * GPULookupTable::GetCoefficientsY(unsigned int block){
	assert(block <= mnblocks);
	if(!(mcachevalid[block] && mcoefficientsy[block])){
		//cout << "refilling... " << endl;
		FillTable();
	}
	return mcoefficientsy[block];
}

void GPULookupTable::invalidateCache(){
	for(unsigned int i = 0; i < mnblocks; i++){
		mcachevalid[i] = false;
	}
}

void GPULookupTable::invalidateCache(unsigned int block){
	assert(block <= mnblocks);
	mcachevalid[block] = false;
}

void GPULookupTable::AllocateMemory(){
	for(unsigned int i = 0; i < mnblocks; i++){
		unsigned int dims[] = {mnadditionalsize, mdim};
		if(i < mnblocks -1 || mnadditionalevents == 0){
		    dims[0] = mblocksize;
		}
		//cout << "BS " << mblocksize << " AS: " << mnadditionalsize << endl;
		mcoefficientsx[i] = new GPUDataStream<float4>(mdev, dims);
		mcoefficientsy[i] = new GPUDataStream<float4>(mdev, dims);
	}
}
