/// \file GPUDataDependentObjectList.h
#pragma once
#include "GPUDataDependentObject.h"
#include "DeviceInterface.h"
#include <vector>

using std::vector;

/// A vector of DataDependentObject
typedef vector<GPUDataDependentObject *> objectvector_t;
/// An iterator over a vector of DataDependentObject
typedef vector<GPUDataDependentObject *>::iterator objectiterator_t;

/// Base class for all classes holding objects with a cache mechanism
/** Note thet the GPUDataDependentObjectList is a GPUDataDependentObject itself,
so lists can be nested and the caching mechanism should still work.

**/
class GPUDataDependentObjectList :
	public GPUDataDependentObject
{
public:
  /// Constructor for a top level list
  GPUDataDependentObjectList(const DeviceInterface * dev, int nSets = 2);
  ///<  The number of data sets in the list, i.e. the range of the index. Usually this number is two, for data and MC
  /// Constructor for a list registered at a higher level list
  GPUDataDependentObjectList(GPUDataDependentObjectList * _list, ///< Higher level list
			     int nsets = 2);///<  The number of data sets in the list, i.e. the range of the index. Usually this number is two, for data and MC

  /// Destructor
  virtual ~GPUDataDependentObjectList(void);
  /// Clear all cached values at index
  virtual void Reset(int index=0);
  /// Clear all cached values at index/block.
  virtual void Reset(int index, int block);
  /// Clear all cached values, including those read from a file
  virtual void ResetInputs();
  /// Clear all cached values, including those read from a file at an index
  virtual void ResetInput(int index =0);
  /// Add an object to the list
  virtual void Register(GPUDataDependentObject * object);
  /// Get the number of sets
  virtual int GetNSets() const{return mNumberOfSets;};
  /// Get the number of blocks at an index
  virtual int GetNBlocks(int index){
	  assert(index < (int)mnblocks.size());
	     if(!eventsok)
	     	initEvents(index);
	     return mnblocks[index];
  }
  /// Get the number of events at an index
  virtual int GetNevents(int index=0){
    assert(index < (int)mnevents.size());
    if(!eventsok)
    	initEvents(index);
    return mnevents[index];
  };

  virtual int GetLength(int index, int block){
      assert(index < (int)mnevents.size());
      if(!eventsok)
      	initEvents(index);
      return mlength[index][block];
    };
  /// Get a vector of event numbers for the different indices
  virtual std::vector<int> GetNeventsList() {
	  if(!eventsok){
		  for(int i=0; i < GetNSets(); i++)
			  initEvents(i);
	  }
	  return mnevents;
  };
  /// Set the number of events at a particular index and performs consistency checks
  virtual void SetNevents(int index, int n);
  
  /// Get a pointer to the interface to the device where this list lives
  virtual const DeviceInterface * GetDeviceInterface() const {return mdeviceinterface;};


 protected:
  /// Initialise the event numbers (by searching input file objects)
  void initEvents(int index);
  /// Pointer to the interface of the Device where the data for this object live
  const DeviceInterface * mdeviceinterface;
  /// Parent list, NULL if this is the top level list
  objectvector_t mObjList;
  /// Number of data sets used by the objects in this list
  const int mNumberOfSets;
  /// Vector of lengths (event numbers) at indices
  std::vector<int> mnevents;
  /// Vector of lengths (event numbers) at blocks
   std::vector<std::vector<int> > mlength;
  /// Vector of the number of blocks
  std::vector<int> mnblocks;
  /// mnevents and mnblocks are initialised or not
  bool eventsok;
};
