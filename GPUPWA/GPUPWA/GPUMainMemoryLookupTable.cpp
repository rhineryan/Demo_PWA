/*
 * GPUMainMemoryLookupTable.cpp
 *
 *  Created on: Apr 27, 2011
 *      Author: nberger
 */

#include "GPUMainMemoryLookupTable.h"
#include <cassert>

GPUMainMemoryLookupTable::GPUMainMemoryLookupTable(float ** coefficientsx,
												   float ** coefficientsy,
												   const DeviceInterface * dev,
												   unsigned int nevents,
												   unsigned int nwaves,
												   unsigned int blocksize)
: GPULookupTable(dev, nevents, nwaves, blocksize)
{
	mincoefficientsx = coefficientsx;
	mincoefficientsy = coefficientsy;

	mcpucoefficientsx = new float4 * [mnblocks];
	mcpucoefficientsy = new float4 * [mnblocks];

	for(unsigned int i=0; i < mnblocks; i++){
		unsigned int size = blocksize;
		if(i == mnblocks -1 && mnadditionalevents)
			size = mnadditionalsize;
		mcpucoefficientsx[i] = new float4[size];
		mcpucoefficientsy[i] = new float4[size];
	}
	mallocated = true;
	mcpucoefficients =0;

}

GPUMainMemoryLookupTable::GPUMainMemoryLookupTable(float4 ** coefficientsx,
												   float4 ** coefficientsy,
												   const DeviceInterface * dev,
												   unsigned int nevents,
												   unsigned int nwaves,
												   unsigned int blocksize)
: GPULookupTable(dev, nevents, nwaves, blocksize)
{
	mincoefficientsx = 0;
	mincoefficientsy = 0;

	mcpucoefficientsx = coefficientsx;
	mcpucoefficientsy = coefficientsy;
	mcpucoefficients =0;
	mallocated = false;
}

GPUMainMemoryLookupTable::GPUMainMemoryLookupTable(float2 ** coefficients,
												   const DeviceInterface * dev,
												   unsigned int nevents,
												   unsigned int nwaves,
												   unsigned int blocksize)
: GPULookupTable(dev, nevents, nwaves, blocksize)
{
	mincoefficientsx = 0;
	mincoefficientsy = 0;
	mcpucoefficients = coefficients;
	mcpucoefficientsx = new float4 * [mnblocks];
	mcpucoefficientsy = new float4 * [mnblocks];

	for(unsigned int i=0; i < mnblocks; i++){
		unsigned int size = blocksize;
		if(i == mnblocks -1 && mnadditionalevents)
			size = mnadditionalsize;
		mcpucoefficientsx[i] = new float4[size];
		mcpucoefficientsy[i] = new float4[size];
	}
	mallocated = true;
}


GPUMainMemoryLookupTable::~GPUMainMemoryLookupTable() {
	if(mallocated){
		for(unsigned int i=0; i < mnblocks; i++){
			delete[] mcpucoefficientsx[i];
			delete[] mcoefficientsy[i];
		}
		delete[] mcpucoefficientsx;
		delete[] mcpucoefficientsy;
	}
}

void GPUMainMemoryLookupTable::FillTable(){
	if(mallocated)
		ReformatTable();
	if(mcoefficientsx[0] ==0)
		AllocateMemory();

	for(unsigned int i=0; i < mnblocks; i++){
		mcoefficientsx[i]->Write(mcpucoefficientsx[i]);
		mcoefficientsy[i]->Write(mcpucoefficientsy[i]);
	}
	mcoefficientsx[mnblocks-1]->GetEvent().wait();
	mcoefficientsy[mnblocks-1]->GetEvent().wait();
}

void GPUMainMemoryLookupTable::FillTable(unsigned int block){
	assert(block < mnblocks);
	if(mallocated)
		ReformatTable(block);
	if(mcoefficientsx[block] ==0)
		AllocateMemory();

	mcoefficientsx[block]->Write(mcpucoefficientsx[block]);
	mcoefficientsy[block]->Write(mcpucoefficientsy[block]);

	mcoefficientsx[block]->GetEvent().wait();
	mcoefficientsy[block]->GetEvent().wait();
}


void GPUMainMemoryLookupTable::ReformatTable(){
	for(unsigned int b=0; b < mnblocks; b++){
		ReformatTable(b);
	}
}
void GPUMainMemoryLookupTable::ReformatTable(unsigned int block){
	assert(mallocated);

	unsigned int size = mblocksize;
	if(block == mnblocks -1 && mnadditionalevents)
		size = mnadditionalsize-1;
	if(mcpucoefficients ==0){
		for(unsigned int ev =0; ev < size; ev++){
			for(unsigned int index =0; index < mdim; index++){
				mcpucoefficientsx[block][ev*mdim + index].x = mincoefficientsx[index][ev*4];
				mcpucoefficientsx[block][ev*mdim + index].y = mincoefficientsx[index][ev*4+1];
				mcpucoefficientsx[block][ev*mdim + index].z = mincoefficientsx[index][ev*4+2];
				mcpucoefficientsx[block][ev*mdim + index].w = mincoefficientsx[index][ev*4+3];

				mcpucoefficientsy[block][ev*mdim + index].x = mincoefficientsy[index][ev*4];
				mcpucoefficientsy[block][ev*mdim + index].y = mincoefficientsy[index][ev*4+1];
				mcpucoefficientsy[block][ev*mdim + index].z = mincoefficientsy[index][ev*4+2];
				mcpucoefficientsy[block][ev*mdim + index].w = mincoefficientsy[index][ev*4+3];
			}
		}
		if(block == mnblocks -1 && mnadditionalevents){
			unsigned int ev = mnadditionalsize-1;
			for(unsigned int index =0; index < mdim; index++){
				switch(mnadditionalevents%4){
				case 0:
					mcpucoefficientsx[block][ev*mdim + index].x = mincoefficientsx[index][ev*4];
					mcpucoefficientsx[block][ev*mdim + index].y = mincoefficientsx[index][ev*4+1];
					mcpucoefficientsx[block][ev*mdim + index].z = mincoefficientsx[index][ev*4+2];
					mcpucoefficientsx[block][ev*mdim + index].w = mincoefficientsx[index][ev*4+3];

					mcpucoefficientsy[block][ev*mdim + index].x = mincoefficientsy[index][ev*4];
					mcpucoefficientsy[block][ev*mdim + index].y = mincoefficientsy[index][ev*4+1];
					mcpucoefficientsy[block][ev*mdim + index].z = mincoefficientsy[index][ev*4+2];
					mcpucoefficientsy[block][ev*mdim + index].w = mincoefficientsy[index][ev*4+3];
					break;
				case 1:
					mcpucoefficientsx[block][ev*mdim + index].x = mincoefficientsx[index][ev*4];
					mcpucoefficientsx[block][ev*mdim + index].y = 0;
					mcpucoefficientsx[block][ev*mdim + index].z = 0;
					mcpucoefficientsx[block][ev*mdim + index].w = 0;

					mcpucoefficientsy[block][ev*mdim + index].x = mincoefficientsy[index][ev*4];
					mcpucoefficientsy[block][ev*mdim + index].y = 0;
					mcpucoefficientsy[block][ev*mdim + index].z = 0;
					mcpucoefficientsy[block][ev*mdim + index].w = 0;
					break;
				case 2:
					mcpucoefficientsx[block][ev*mdim + index].x = mincoefficientsx[index][ev*4];
					mcpucoefficientsx[block][ev*mdim + index].y = mincoefficientsx[index][ev*4+1];
					mcpucoefficientsx[block][ev*mdim + index].z = 0;
					mcpucoefficientsx[block][ev*mdim + index].w = 0;

					mcpucoefficientsy[block][ev*mdim + index].x = mincoefficientsy[index][ev*4];
					mcpucoefficientsy[block][ev*mdim + index].y = mincoefficientsy[index][ev*4+1];
					mcpucoefficientsy[block][ev*mdim + index].z = 0;
					mcpucoefficientsy[block][ev*mdim + index].w = 0;
					break;
				case 3:
					mcpucoefficientsx[block][ev*mdim + index].x = mincoefficientsx[index][ev*4];
					mcpucoefficientsx[block][ev*mdim + index].y = mincoefficientsx[index][ev*4+1];
					mcpucoefficientsx[block][ev*mdim + index].z = mincoefficientsx[index][ev*4+2];
					mcpucoefficientsx[block][ev*mdim + index].w = 0;

					mcpucoefficientsy[block][ev*mdim + index].x = mincoefficientsy[index][ev*4];
					mcpucoefficientsy[block][ev*mdim + index].y = mincoefficientsy[index][ev*4+1];
					mcpucoefficientsy[block][ev*mdim + index].z = mincoefficientsy[index][ev*4+2];
					mcpucoefficientsy[block][ev*mdim + index].w = 0;
					break;
				default:
					assert(0);
				}
			}
		}
	} else {
		for(unsigned int ev =0; ev < size; ev++){
			for(unsigned int index =0; index < mdim; index++){
				mcpucoefficientsx[block][ev*mdim + index].x = mcpucoefficients[index][ev*4].x;
				mcpucoefficientsx[block][ev*mdim + index].y = mcpucoefficients[index][ev*4+1].x;
				mcpucoefficientsx[block][ev*mdim + index].z = mcpucoefficients[index][ev*4+2].x;
				mcpucoefficientsx[block][ev*mdim + index].w = mcpucoefficients[index][ev*4+3].x;

				mcpucoefficientsy[block][ev*mdim + index].x = mcpucoefficients[index][ev*4].y;
				mcpucoefficientsy[block][ev*mdim + index].y = mcpucoefficients[index][ev*4+1].y;
				mcpucoefficientsy[block][ev*mdim + index].z = mcpucoefficients[index][ev*4+2].y;
				mcpucoefficientsy[block][ev*mdim + index].w = mcpucoefficients[index][ev*4+3].y;
			}
		}
		if(block == mnblocks -1 && mnadditionalevents){
			unsigned int ev = mnadditionalsize-1;
			for(unsigned int index =0; index < mdim; index++){
				switch(mnadditionalevents%4){
				case 0:
					mcpucoefficientsx[block][ev*mdim + index].x = mcpucoefficients[index][ev*4].x;
					mcpucoefficientsx[block][ev*mdim + index].y = mcpucoefficients[index][ev*4+1].x;
					mcpucoefficientsx[block][ev*mdim + index].z = mcpucoefficients[index][ev*4+2].x;
					mcpucoefficientsx[block][ev*mdim + index].w = mcpucoefficients[index][ev*4+3].x;

					mcpucoefficientsy[block][ev*mdim + index].x = mcpucoefficients[index][ev*4].y;
					mcpucoefficientsy[block][ev*mdim + index].y = mcpucoefficients[index][ev*4+1].y;
					mcpucoefficientsy[block][ev*mdim + index].z = mcpucoefficients[index][ev*4+2].y;
					mcpucoefficientsy[block][ev*mdim + index].w = mcpucoefficients[index][ev*4+3].y;
					break;
				case 1:
					mcpucoefficientsx[block][ev*mdim + index].x = mcpucoefficients[index][ev*4].x;
					mcpucoefficientsx[block][ev*mdim + index].y = 0;
					mcpucoefficientsx[block][ev*mdim + index].z = 0;
					mcpucoefficientsx[block][ev*mdim + index].w = 0;

					mcpucoefficientsy[block][ev*mdim + index].x = mcpucoefficients[index][ev*4].y;
					mcpucoefficientsy[block][ev*mdim + index].y = 0;
					mcpucoefficientsy[block][ev*mdim + index].z = 0;
					mcpucoefficientsy[block][ev*mdim + index].w = 0;
					break;
				case 2:
					mcpucoefficientsx[block][ev*mdim + index].x = mcpucoefficients[index][ev*4].x;
					mcpucoefficientsx[block][ev*mdim + index].y = mcpucoefficients[index][ev*4+1].x;
					mcpucoefficientsx[block][ev*mdim + index].z = 0;
					mcpucoefficientsx[block][ev*mdim + index].w = 0;

					mcpucoefficientsy[block][ev*mdim + index].x = mcpucoefficients[index][ev*4].y;
					mcpucoefficientsy[block][ev*mdim + index].y = mcpucoefficients[index][ev*4+1].y;
					mcpucoefficientsy[block][ev*mdim + index].z = 0;
					mcpucoefficientsy[block][ev*mdim + index].w = 0;
					break;
				case 3:
					mcpucoefficientsx[block][ev*mdim + index].x = mcpucoefficients[index][ev*4].x;
					mcpucoefficientsx[block][ev*mdim + index].y = mcpucoefficients[index][ev*4+1].x;
					mcpucoefficientsx[block][ev*mdim + index].z = mcpucoefficients[index][ev*4+2].x;
					mcpucoefficientsx[block][ev*mdim + index].w = 0;

					mcpucoefficientsy[block][ev*mdim + index].x = mcpucoefficients[index][ev*4].y;
					mcpucoefficientsy[block][ev*mdim + index].y = mcpucoefficients[index][ev*4+1].y;
					mcpucoefficientsy[block][ev*mdim + index].z = mcpucoefficients[index][ev*4+2].y;
					mcpucoefficientsy[block][ev*mdim + index].w = 0;
					break;
				default:
					assert(0);
				}
			}
		}
	}


}
