/// \file GPUStreamInputRootFileVector.h
#pragma once

#include "Status.h"



#include "GPUStreamInputVector.h"
/// Class for streams that contain data that is read from a root file
/** As the input to PWAs is always 4-vectors, this class is derived of
   GPUStreamVector and not the more general GPUStreamTensor. Usually,
   GPUStreamTensor objects contain intermediate results of calculations
   and thus cached values have to be invalidated, when parameters change.
   Here, the values are read from a file, so the cache only has to be
   invalidated either to free memory or if the input file changes. The
   root file is expected to contain a tree named treenam with the 4- vector
   components in branches px, py, pz and E. Note that different indices
   both have their own file- and treenames, so it is possible to store data
   and MC in the same file using different trenames or in different files
   using the same (or diffrent) tree names.
*/
class GPUStreamInputRootFileVector :
	public GPUStreamInputVector
{
public:
	/// Create a Stream Vector to be fed from a root file
	/** \param _list Object where to register this vector (usually the Partial Wave Analysis Object)
	 **/
	GPUStreamInputRootFileVector(GPUDataDependentObjectList *_list);
	/// Create a Stream Vector to be fed from a root file
	/** \param _list Object where to register this vector (usually the Partial Wave Analysis Object)
	    \param _filename: Name of the root file
	    \param _treename: Name of the root tree holding the variables
	    \param _px: name of branch holding px
	    \param _py: name of branch holding py
	    \param _pz: name of branch holding pz
	    \param _E: name of branch holding E
	**/
	GPUStreamInputRootFileVector(GPUDataDependentObjectList *_list,const char * _filename, const char * _treename, const char * _px, const char * _py, const char * _pz, const char * _E);
	/// Destructor
	virtual ~GPUStreamInputRootFileVector();
	/// Test whether the file exists and write its length to length
	virtual STATUS TestFile(int index, int & length);
	/// Read the file and write its contents to a GPU Stream
	virtual STATUS ReadFile(int index = 0);
	// Reset of cached values; do nothing, as nothing is calculated here
	//virtual void Reset(int index =0){};
	/// Get the name of the tree for an index
	virtual const char * GetTreename(int index = 0){return mTreename[index];};
	/// Change the input tree name
	/** This will necessarily invalidate the cache */
	virtual void SetTreename(char * _treename, int index =0){
		assert((int)mTreename.size() > index);
		mTreename[index] = _treename; mList->Reset(index);ResetInput(index);
	};

	/// Set the names of the branches holding the 4-vector
	virtual void SetBranchNames(const char * _px, const char * _py, const char * _pz, const char * _E){
		mpx = _px; mpy = _py; mpz = _pz; mE = _E;
	};
	/// Set the name of the branch holding px
	virtual void SetPxBranchName(const char *_p){
		mpx = _p;
	};
	/// Set the name of the branch holding py
	virtual void SetPyBranchName(const char *_p){
		mpy = _p;
	};
	/// Set the name of the branch holding pz
	virtual void SetPzBranchName(const char *_p){
		mpz = _p;
	};
	/// Set the name of the branch holding E
	virtual void SetEBranchName(const char *_p){
		mE = _p;
	};

	/// Get the name of the branch holding px
	virtual const char * GetPxBranchName(){ return mpx;};
	/// Get the name of the branch holding px
	virtual const char * GetPyBranchName(){ return mpy;};
	/// Get the name of the branch holding px
	virtual const char * GetPzBranchName(){ return mpz;};
	/// Get the name of the branch holding px
	virtual const char * GetEBranchName(){ return mE;};

private:
	std::vector<const char *> mTreename; /// Name of the root tree holding the four-vector data
	const char * mpx; /// Name of the branch holding px
	const char * mpy; /// Name of the branch holding py
	const char * mpz; /// Name of the branch holding pz
	const char * mE;  /// Name of the branch holding E

};
