/*
 * GPUPartialWaveLookupTable.cpp
 *
 *  Created on: May 9, 2011
 *      Author: nberger
 */

#include "GPUPartialWaveLookupTable.h"
#include "GPUPartialWaveAnalysis.h"


#ifdef USECPU
#include "Analysis_cpu.h"
using namespace Analysis_CPU;
#else
#include "Analysis.h"
using namespace Analysis_GPU;
#endif
using std::cout;
using std::endl;

GPUPartialWaveLookupTable::GPUPartialWaveLookupTable(GPUSetOfPartialWaves * _waveset, unsigned int index):
GPULookupTable(_waveset->GetAnalysis()->GetDeviceInterface(),
			  _waveset->GetAnalysis()->GetNevents(index),
			  _waveset->GetNActiveWaves(),
			  _waveset->GetAnalysis()->Blocksize),

GPUParameterDependentObject(_waveset->GetAnalysis()->GetParameters(),
							_waveset->GetActiveDynamicParameters(),
							_waveset->GetActiveDynamicParameterNames(),
							_waveset->GetAnalysis()->GetNSets()),
mwaveset(_waveset),
mindex(index)
{
	mfilled = new unsigned int[mdim];
	for(unsigned int i=0; i < mdim; i++)
		mfilled[i] = 0;
}

GPUPartialWaveLookupTable::~GPUPartialWaveLookupTable() {

	delete[] mfilled;
}


void GPUPartialWaveLookupTable::FillTable(){

	if(!mcoefficientsx[0])
		AllocateMemory();

	vector<GPUPartialWave *> waves =  mwaveset->GetActiveWaves();
	mwaveset->SetUsecount(mindex);
	for (int b = 0; b < mwaveset->GetAnalysis()->GetNBlocks(mindex); b++) {
		unsigned int size = mwaveset->GetAnalysis()->Blocksize;
		//cout << "Block : " << b << endl;
		//PrintStreamMemoryUse();
	/*	cout << "MBS: " << mblocksize << endl;
		cout << "size: " << size << endl;
		cout << "mblocks " << mnblocks << endl;
		cout << "b " << b << endl;
		cout << "nadd " << mnadditionalevents << endl;
		cout << "naddsize " << mnadditionalsize << endl;*/
		if(b == mwaveset->GetAnalysis()->GetNBlocks(mindex)-1 && mwaveset->GetAnalysis()->GetNevents(mindex)%mwaveset->GetAnalysis()->Blocksize)
			size = mwaveset->GetAnalysis()->GetNevents(mindex)%mwaveset->GetAnalysis()->Blocksize;
		//cout << "size: " << size << endl;
		int n = 0;
		vector<GPUPartialWave *>::iterator it_i;
		vector<GPUPartialWave *>::iterator it_j;
		for (it_i = waves.begin(); it_i < waves.end(); ++it_i) {
			for (it_j = it_i; it_j < waves.end(); ++it_j) {
				//cout << "n " << n << " filled "<< mfilled[n] <<" i " << (*it_i)->DynamicCacheValid(mindex) << " " << (*it_j)->DynamicCacheValid(mindex) << endl;
				if(!(mfilled[n] && (*it_i)->DynamicCacheValid(mindex) && (*it_j)->DynamicCacheValid(mindex))){
					//cout << "filling " << endl;
					mfilled[n] = false;
					GPUDataStream<float2> * aiaj = (*it_i)->Contract((*it_j), mindex, b);
					//aiaj->print();
					//cout << "Offset : " << (b%4)*mblocksize*mdim/4 << endl;
					kernelfilllookup(cl::NDRange(size/4),
									mwaveset->GetDeviceInterface(),
									aiaj,
									(b%4)*mblocksize*mdim/4,
									n,
									mdim,
									mcoefficientsx[b/4],
									mcoefficientsy[b/4]);


					//mcoefficientsy[b/4]->Wait();
					delete aiaj;
					if(b == mwaveset->GetAnalysis()->GetNBlocks(mindex)-1){
						//cout << "Filled at " << n << endl;
						mfilled[n] = true;
					}
				}
				n++;

			}
		}

		mwaveset->GetAnalysis()->Reset(mindex,b);
		mwaveset->GetAnalysis()->GetDeviceInterface()->GetQueue()->finish();

		//mcoefficientsx[b/4]->printAt(2048*mdim,100);
		if(b%4==3 || b==mwaveset->GetAnalysis()->GetNBlocks(mindex)-1)
			mcachevalid[b/4]=true;
		/*if(b%4==3){
			mcoefficientsx[b/4]->printAt(0,mblocksize*mdim);
			mcoefficientsy[b/4]->printAt(0,mblocksize*mdim);
			assert(0);
		}*/
		/*if(b==mwaveset->GetAnalysis()->GetNBlocks(mindex)-1){
			//mcoefficientsx[b/4]->printAt(1000,100);
			mcoefficientsy[b/4]->printAt(1000,100);
			cout << "Index " << b/4 << endl;
		}*/
	}
	ValidateCache(mindex);
}
