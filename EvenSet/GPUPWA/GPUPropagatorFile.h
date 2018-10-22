/// \file GPUPropagatorFile.h

/*
 * GPUPropagatorFile.h
 *
 *  Created on: Apr 28, 2009
 *      Author: nberger
 */

#ifndef GPUPROPAGATORFILE_H_
#define GPUPROPAGATORFILE_H_

#include "GPUPropagatorType.h"
#include "GPUFileTable.h"
#include "GPUDataStream.h"
#include "GPUStreamTensor.h"
#include <cassert>
#include <vector>

class GPUPartialWaveAnalysis;


/// Class representing a propagator (complex number) taken from a file (through a GPUFileTable)
/** Note that this kind of propagator does not allow for varying resonance parameters;
 * calling any member function dependent on varying parameters will stop your program
 *
 */

class GPUPropagatorFile: public GPUPropagatorType<float> {
public:
	/// Constructor
	GPUPropagatorFile(GPUPartialWaveAnalysis * _ana, ///<GPUPartialWaveAnalysis where the scalar is registered for cache handling
			  char * name,
			  std::vector<GPUFileTable<float2> *> _tables,    ///< Vector of GPUFileTable objects holding the information represented by this Propagator, usually with two elements, one for data, one for MC
			  std::vector<unsigned int> _columns         ///< Vector of columns in the GPUFileTable to take the data from
			  );
	/// Destructor
	virtual ~GPUPropagatorFile();

	/// () operator; return the value read from the GPUFileTable
	virtual GPUDataStream<float2> * operator()(int index =0, int block=0);
	/// Dummy method for interface consistency; call will stop the program
	virtual GPUDataStream<float2> * operator()(int index, int block, float mass, float width){assert(0); return 0;};
	/// Dummy method for interface consistency; call will stop the program
	virtual GPUDataStream<float2> * GetMassDerivative(int index, int block, float mass, float width){assert(0); return 0;};
	/// Dummy method for interface consistency; call will stop the program
	virtual GPUDataStream<float2> * GetWidthDerivative(int index, int block, float mass, float width){assert(0); return 0;};
	/// Dummy method for interface consistency; call will stop the program
	virtual GPUDataStream<float> * GetAbsMassDerivative(int index, int block, float mass, float width){assert(0); return 0;};
	/// Dummy method for interface consistency; call will stop the program
	virtual GPUDataStream<float> * GetAbsWidthDerivative(int index, int block, float mass, float width){assert(0); return 0;};
protected:
	/// Copy data from the GPUFileTable to the GPU
	virtual void CopyBuffer(int index, int block);
	 /// Pointers to GPUFileTables for objects taking their data from a file
	  std::vector<GPUFileTable<float2> *> mtables;
	  /// Columns in the file tables object
	  std::vector<unsigned int> mcolumns;
};

#endif /* GPUPROPAGATORFILE_H_ */
