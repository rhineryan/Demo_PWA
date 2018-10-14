#include "GPUDataDependentObject.h"
#include "GPUDataDependentObjectList.h"

#include <cassert>


//const int GPUDataDependentObject::Blocksize = 8192*128;//maybe 128 is too large
//const int GPUDataDependentObject::Blocksize = 8192*4;
const int GPUDataDependentObject::Blocksize = 8192*1;


GPUDataDependentObject::GPUDataDependentObject(GPUDataDependentObjectList * _list):
	//mlength(_list->GetNSets(),std::vector<int>()),
	musecount(_list->GetNSets(),std::vector<int>())
{
	//cout <<"List: " <<  _list << endl;
	assert(_list);
	_list->Register(this);
	mList = _list;
}

GPUDataDependentObject::~GPUDataDependentObject(void)
{
}

void GPUDataDependentObject::SetNevents(int index, int n){
  if(mList)
    mList->SetNevents(index, n);
};

int GPUDataDependentObject::GetNevents(int index) {
  if(mList)
    return mList->GetNevents(index);
  return -1;
};

int GPUDataDependentObject::GetLength(int index, int block){
	assert(mList);
	if(mList){
		assert(mList->GetLength(index, block) <= Blocksize);
		return mList->GetLength(index, block);
	}
	 return -1;
}

int GPUDataDependentObject::GetNSets() {
  if(mList)
    return mList->GetNSets();
  return -1;
};

int GPUDataDependentObject::GetNStreams() {
	return GetNSets();
};


int GPUDataDependentObject::GetNBlocks(int index) {
  if(mList)
    return mList->GetNBlocks(index);
  return -1;
};

void GPUDataDependentObject::ResetUsecount(){
	for(unsigned int i=0; i < musecount.size(); i++)
		for(unsigned int j=0; j < musecount[i].size(); j++)
			musecount[i][j] = 0;
};

void GPUDataDependentObject::ResetUsecount(int index){
	for(unsigned int j=0; j < musecount[index].size(); j++)
		musecount[index][j] = 0;
};

void GPUDataDependentObject::SetUsecount(int index, int num){
	ResetUsecount(index);
	int i =0;
	while(i < num){
		IncreaseUsecount(index);
		i++;
	}

};

void GPUDataDependentObject::IncreaseUsecount(int index){
	for(unsigned int j=0; j < musecount[index].size(); j++){
		if(musecount[index][j] < 0)
			musecount[index][j] =0;
		musecount[index][j]++;
	}

}

void GPUDataDependentObject::IncreaseUsecount(int index, int block){
	assert(block <(int)musecount[index].size());
	if(musecount[index][block] < 0)
		musecount[index][block] =0;
		musecount[index][block]++;
}

int GPUDataDependentObject::DecreaseUsecount(int index, int block){
	musecount[index][block]--;
	if(musecount[index][block] < 1)
		Reset(index,block);
	return musecount[index][block];
}

void GPUDataDependentObject::InitUsecount(int index, int nevents){
	while((int)musecount.size() <= index)
		musecount.push_back(std::vector<int>());
	int nblocks = nevents/Blocksize;
	if(nevents%Blocksize)
		nblocks++;
	if((int)musecount[index].size() < nblocks){
		while((int)musecount[index].size() < nblocks)
			musecount[index].push_back(0);
	}
	for(int i=0; i < (int)musecount[index].size(); i++)
		musecount[index][i] = 0;
}
