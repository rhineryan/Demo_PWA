/// \file GPUStreamInputVector.h
#pragma once
#include "GPUStreamTensor.h"
#include "Status.h"
#include "GPUDataStream.h"

/// Base class for streams that contain data that is read from a file
/* As the input to PWAs is always 4-vectors, this class is derived of
 GPUStreamVector and not the more general GPUStreamTensor. Usually,
 GPUStreamTensor objects contain intermediate results of calculations
 and thus cached values have to be invalidated, when parameters change.
 Here, the values are read from a file, so the cache only has to be
 invalidated either to free memory or if the input file changes.
 */
class GPUStreamInputVector: public GPUStreamVector {
public:
	///Constructor taking a GPUDataDependentObjectList
	/** Note that the filename will have to be set before reading a file **/
	GPUStreamInputVector(GPUDataDependentObjectList *_list///< GPUDataDependentObjectList where this StreamVector is to be registerd for cache handling
			);
	///Constructor taking a GPUDataDependentObjectList and a filename
	GPUStreamInputVector(GPUDataDependentObjectList *_list, ///< GPUDataDependentObjectList where this StreamVector is to be registerd for cache handling
			const char * _filename ///< Name of the file for the stream at index 0. Filenames for higher indices have to be set separately
			);
	///Destructor
	virtual ~GPUStreamInputVector(void) {
	}
	;
	///Get the Filename at an index
	virtual const char * GetFilename(int index = 0) {
		if (index >= (int) mFilename.size())
			return 0;
		return mFilename[index];
	}
	;
	/// Change the input file
	/** This will necessarily invalidate the cache */
	virtual void SetFilename(const char * _filename, int index = 0) {
		assert(index < (int)mFilename.size());
		assert(index < (int)mstream.size());
		assert(index < (int)mlength.size());
		mFilename[index] = _filename;
		mList->Reset(index);
		ResetInput(index);
		int nevents;
		if (TestFile(index, nevents))
			exit(102);
		SetNevents(index, nevents);
		InitUsecount(index, nevents);
	}
	;
	/// Test whether the file exists and write its length to length - has to be implemented by derived classes
	virtual STATUS TestFile(int index, int & length) =0;
	///Read the file for a specific index. Has to be implemeted by derived classes depending on file type
	virtual STATUS ReadFile(int index = 0) = 0;
	/// Bracket operator: read file if necessary, return stream
	virtual GPUDataStream<float4> * operator()(int index = 0, int block = 0) {
		assert(index < (int)mstream.size());
		if(!mfileread[index])
			ReadFile(index);
		if ((int) mstream[index].size() <= block || !mstream[index][block]) {
			CopyBuffer(index, block);
		}
		return mstream[index][block];
	}
	;
	/// Copy the buffer for a particular index and block to a stream on the GPU
	virtual void CopyBuffer(int index, int block);
	/// Reset of inputs, invalidate any preexisting streams if necessary
	virtual void ResetInputs() {
		for (int i = 0; i < (int) mstream.size(); i++) {
			if (mBuffer[i]) {
				delete[] mBuffer[i];
				mBuffer[i] = 0;
			}
			for (int j = 0; j < (int) mstream[i].size(); j++) {
				if (mstream[i][j]) {
					delete mstream[i][j];
					mstream[i][j] = 0;
				}
				mlength[i][j] = 0;
				musecount[i][j] = 0;
			}
		}
	}
	;
	/// Reset of input, invalidate any preexisting stream if necessary
	virtual void ResetInput(int index) {
		if (mBuffer[index]) {
			delete[] mBuffer[index];
			mBuffer[index] = 0;
		}
		if (index < (int) mlength.size()) {
			for (int j = 0; j < (int) mstream[index].size(); j++) {
				if (mstream[index][j]) {
					delete mstream[index][j];
					mstream[index][j] = 0;
				}
				mlength[index][j] = 0;
				musecount[index][j] = 0;
			}
		}
	}
	;
	// Do the usual stuff at a reset, but do not reset lengths...
	virtual void Reset(int index, int block) {
		if (block == -1) {
			if ((int) mlength.size() > index) {
				for (int j = 0; j < (int) mlength[index].size(); j++) {
					if (mstream[index][j])
						delete mstream[index][j];
					mstream[index][j] = 0;
					musecount[index][j] = 0;
				}
			}
		} else {
			if ((int) mlength.size() > index) {
				if ((int) mlength[index].size() > block) {
					if (mstream[index][block])
						delete mstream[index][block];
					mstream[index][block] = 0;
					musecount[index][block] = 0;
				}
			}
		}
	}
	;

	/// Get Length of the stream
	virtual int GetLength(int index = 0, int block = 0) {
		assert(index < (int)mlength.size());
		if (!mlength[index].size())
			ReadFile(index);
		//cout << "Length : " << mlength[index][block] << " at " << index << " : " << block << endl;
		return mlength[index][block];
	}
	;

	/// Get the number of events read from a file
	virtual int GetReadEvents(int index) {
		assert(index < (int)mlength.size());
		if (!mlength[index].size())
			ReadFile(index);
		int sum = 0;
		for (unsigned int i = 0; i < mlength[index].size(); i++)
			sum += mlength[index][i];
		return sum;

	}
	;

	/// Get the number of Blocks in a stream
	virtual int GetNBlocks(int index) {
		assert(index < (int)mlength.size());
		if (!mlength[index].size())
			ReadFile(index);
		return mlength[index].size();
	}
	;

protected:
	/// Vector with the filenames
	std::vector<const char *> mFilename;
	/// Buffer for the file content in main memory - copied to CPU when needed
	std::vector<float4 *> mBuffer;
	/// Lengths of the streams
	std::vector<std::vector<int> > mlength;
	/// already read the file at an index
	std::vector<bool> mfileread;
};
