#include "GPUDataDependentObjectList.h"
#include <cassert>


GPUDataDependentObjectList::GPUDataDependentObjectList(const DeviceInterface * dev, int nsets):
	GPUDataDependentObject(),mdeviceinterface(dev), mNumberOfSets(nsets),mnevents(nsets,-1),mlength(nsets,std::vector<int>()),mnblocks(nsets,-1),eventsok(0)
{
	assert(nsets > 0);
	assert(mdeviceinterface);
}

GPUDataDependentObjectList::GPUDataDependentObjectList(GPUDataDependentObjectList * _list, int nsets):
	GPUDataDependentObject(_list),mdeviceinterface(_list->GetDeviceInterface()),mNumberOfSets(nsets),mnevents(nsets,-1),mlength(nsets,std::vector<int>()),mnblocks(nsets,-1),eventsok(0)
{
	assert(nsets > 0);
	assert(mdeviceinterface);
}


GPUDataDependentObjectList::~GPUDataDependentObjectList(void)
{
}

void GPUDataDependentObjectList::Reset(int index){
	for(objectiterator_t it = mObjList.begin(); it < mObjList.end(); ++it)
		(*it)->Reset(index);
}

void GPUDataDependentObjectList::Reset(int index, int block){
	for(objectiterator_t it = mObjList.begin(); it < mObjList.end(); ++it)
		(*it)->Reset(index,block);
}

void GPUDataDependentObjectList::ResetInputs(){
  for(objectiterator_t it = mObjList.begin(); it < mObjList.end(); ++it)
    (*it)->ResetInputs();
  for(unsigned int i=0; i < mnevents.size(); i++)
    mnevents[i] = -1;
}

void GPUDataDependentObjectList::ResetInput(int index){
  for(objectiterator_t it = mObjList.begin(); it < mObjList.end(); ++it)
    (*it)->ResetInput(index);
  mnevents[index] = -1;
}

void GPUDataDependentObjectList::Register(GPUDataDependentObject * object){
	mObjList.push_back(object);
}

// Set the number of events at a particular index and performs consistency checks
void GPUDataDependentObjectList::SetNevents(int index, int n){
  assert((int)mnevents.size() > index);
  //cout << "New event number " << n << " stored event number " << mnevents[index] << endl;
  if(mnevents[index] != -1){
    if(mnevents[index] != n){
      cout << "ERROR: Event numbers not matching for index "<< index << endl;
      // This might be a bit harsh, but here we actually bail out!
      assert(0);
    } else {
      // All fine here, do nothing
    }
  } else {
    // Value was not set, so we set it now
    mnevents[index] = n;
    mnblocks[index] = n/GPUDataDependentObject::Blocksize;
    if(n%GPUDataDependentObject::Blocksize)
    	mnblocks[index]++;

    mlength[index].clear();
    for(int i =0; i < mnblocks[index]; i++){
  	  mlength[index].push_back(GPUDataDependentObject::Blocksize);
    }
    if(n%GPUDataDependentObject::Blocksize)
  	  mlength[index][mnblocks[index]-1] = n%GPUDataDependentObject::Blocksize;
  }

}


void GPUDataDependentObjectList::initEvents(int index){
	int n =0;
	for(objectiterator_t it = mObjList.begin(); it < mObjList.end(); ++it){
	   n =  (*it)->GetReadEvents(index);
	   if(n){
		   SetNevents(index, n);
		   break;
	   }
	}
	if(!n){
		cout << "Specify an input file dependent object first to fix event numbers!" << endl;
		assert(0);
	}
	eventsok = true;
}
