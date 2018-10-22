///\file GPUDataDependentObject.h
#pragma once

#include <vector>
#include <cassert>
#include <iostream>
#include <stdlib.h>

using std::cout;
using std::endl;

class GPUDataDependentObjectList;

/// Class for cache management for Objects dependent on input data
	/** All objects calculated from input four-vector files should inherit from this class,
		ensuring that they are properly registered, so that cached streams can be reset when
		input data change */
class GPUDataDependentObject
{

public:
	/// Constructor, taking a pointer to a list of such objects
	/** If list is zero, the Object is not registered (not recommended), this feature is used for
	some derived classes which implement their own registration mechanism */
	GPUDataDependentObject(GPUDataDependentObjectList * _list);
	/// Destructor
	virtual ~GPUDataDependentObject(void);
	/// Reset the cached values
	/** Derived objects should invalidate their cached Streams and other calculated values at
	this call */
	virtual void Reset(int index =0)=0;
	/// Reset one block of cached values
	virtual void Reset(int index, int block)=0;
	/// Reset inputs from files
	/** Derived Objects which read their contents from a file, should invalidate these contents
	and reread the file if necessay */
	virtual void ResetInputs(){Reset();};
	/// Reset file inputs for a particular source stream
	virtual void ResetInput(int index =0){Reset(index);};
	/// Return the list where this Object is registered
	virtual GPUDataDependentObjectList * GetList(){return mList;};
	/// Set (and checkfor consistency!) event number at a particular index
	virtual void SetNevents(int index, int n);
	/// Get event number at a particular index - only works if object is registered!
	virtual int GetNevents(int index);
	/// Get the length of the stream, to be implemented by derived classes
	virtual int GetLength(int index=0, int block =0);
	/// Get the current number of streams
	virtual int GetNStreams();
	/// Get the current number of blocks at index
	virtual int GetNBlocks(int index);
	/// Get the number of data sets contained
	virtual int GetNSets();
	/// Get the number of events read from a file, to be implemented differently in file based derived classes
	virtual int GetReadEvents(int index){return 0;};


	/// Set the usecount to 0
	virtual void ResetUsecount();
	/// Set the usecount to 0 at index;
	virtual void ResetUsecount(int index);
	/// Set the usecount  at index;
	virtual void SetUsecount(int index, int num);
	/// Set the usecount to 0 at index and block;
	virtual void ResetUsecount(int index, int block){musecount[index][block] = 0;};
	/// Increase the usecount at a particular index
	/** Derived classes with dependencies on other Tensors (e.g. GPUComputedTensor)
	 *  should provide an implementation propagating the increase to the tensors
	 *  needed in the input
	 */
	virtual void IncreaseUsecount(int index);
	/// Increase the usecount at a particular index and block
	/** Derived classes with dependencies on other Tensors (e.g. GPUComputedTensor)
	 *  should provide an implementation propagating the increase to the tensors
	 *  needed in the input
	 */
	virtual void IncreaseUsecount(int index, int block);
	/// Decrease usecount, return result, if reaches zero, reset.
	virtual int DecreaseUsecount(int index, int block);
	/// Return usecount
	virtual int GetUsecount(int index, int block){return musecount[index][block];};

	/// Size of a Block
	/** Almost all calculations involving tensors in GPUPWA are performed blockwise, i.e. the
	    final result is calculated for one block, then the cache is cleared and the next block
	    is calculated. This allows even very large calculations to store all intermediate values
	    in GPU memory, thus removing the necessity for swaps. In general, the smaller the block
	    size, the less memory is consumed, but calculations also become slower.
	 */
	 const static int Blocksize;



protected:
	/// Constructor without arguments
	/** The Object is not registered upon creation, this feature is used for
	some derived classes which implement their own registration mechanism */
	GPUDataDependentObject(){mList = 0;};
	/// The list where this object is registered
	GPUDataDependentObjectList * mList;
	/// Init the usecount
	virtual void InitUsecount(int index, int nevents);
	// Vector of stream lengths
	//std::vector<std::vector<int> > mlength;
	/// Vector of use counts used for cache management
	std::vector<std::vector<int> > musecount;

};
