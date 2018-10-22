/*
 * GPUPropagatorFile.cpp
 *
 *  Created on: Apr 28, 2009
 *      Author: nberger
 */

#include "GPUPropagatorFile.h"
#include "GPUFileTable.h"
#include "GPUPartialWaveAnalysis.h"

GPUPropagatorFile::GPUPropagatorFile(GPUPartialWaveAnalysis * _ana,
									char * name,
									 std::vector<GPUFileTable<float2> *> _tables,
									 std::vector<unsigned int> _columns ):
									 GPUScalarPropagator(_ana, name, std::vector<char **>(), 0),
									 mtables(_tables),
									 mcolumns(_columns){

										 assert(_ana->GetNSets() == (int)_tables.size());
										 assert(_ana->GetNSets() == (int)_columns.size());
										 for(int index =0; index < _ana->GetNSets(); index++){
											 //mlength[index].clear();
											 int nentries = mtables[index]->nevents();
											 while(nentries > 0){
												 if(nentries > GPUDataDependentObject::Blocksize){
													 //mlength[index].push_back(GPUDataDependentObject::Blocksize);
													 mstream[index].push_back(0);
												 } else {
													 //mlength[index].push_back(nentries);
													 mstream[index].push_back(0);
												 }
												 nentries -= GPUDataDependentObject::Blocksize;
											 }
											 _ana->SetNevents(index, mtables[index]->nevents());
										 }


}

GPUPropagatorFile::~GPUPropagatorFile() {
}

GPUDataStream<float2> * GPUPropagatorFile::operator()(int index, int block)
{
	assert(index < (int)mstream.size());
	assert(block < (int)mstream[index].size());
	if(mstream[index][block]){
		return mstream[index][block];
	} else {
		CopyBuffer(index,block);
		return mstream[index][block];
	}

}

void GPUPropagatorFile::CopyBuffer(int index, int block){
	 assert(index < (int)mstream.size());
	 assert(block < (int)mstream[index].size());

	 mstream[index][block] = new GPUDataStream<float2>(mList->GetDeviceInterface(), GetLength(index,block));
	 mstream[index][block]->Write((*mtables[index])(mcolumns[index])+block*GPUStreamTensor<float2>::Blocksize);
}

