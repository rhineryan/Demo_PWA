/// \file GPUPropagatorType.h
/*
 * GPUPropagatorType.h
 *
 *  Created on: Aug 25, 2009
 *      Author: nberger
 */

#ifndef GPUPROPAGATORTYPE_H_
#define GPUPROPAGATORTYPE_H_

#include "GPUPropagator.h"
#include "GPUDataDependentObjectType.h"
#include <vector>

class GPUDataDependentObjectList;

/// Template class for complex objects of arbitrary rank
/** Note that there is a specialised template for the (usual) complex number case;
 *  in the general case, two separate stream exist for the real and imaginary parts,
 *  (the real part being stored in the GPUDataDependentObjectType<T> mstream variable)
 *  whereas in the complex case, mstream is a float2 holding both the real and complex
 *  part.
 */
template <typename T>
class GPUPropagatorType: public GPUPropagator, public GPUDataDependentObjectType<T> {
public:
	/// Constructor
	GPUPropagatorType(GPUPartialWaveAnalysis * ana, char * name, std::vector<char **> parnames, unsigned int npar);
	/// Constructor taking mass and with vectors
	GPUPropagatorType(GPUPartialWaveAnalysis * ana,
					std::vector<char *> names,
					std::vector<unsigned int *> _Parameters,
					std::vector<char **> parnames);
	/// Destructor
	virtual ~GPUPropagatorType();

	/// Get the real part
	virtual GPUDataStream<T> * realpart(int index,
										int block);
	/// Get the imaginary part
	virtual GPUDataStream<T> * imagpart(int index,
										int block);
	/// Read the stream to memory
	virtual T* Read(int index=0);

	/// Read a block of the stream to memory
	virtual T* ReadBlock(int index=0, int block = 0);
	/// Reset cached information at index
	virtual void Reset(int index=0);
	/// Reset the cached streams at index and block
	virtual void Reset(int index, int block);

	// Read the stream to memory and print contents
	/* Print nelements, for nelements < 1, all elemnts are printed, in the second argument,
	a different output stream can be specified, default is cout */
	//virtual void Print(int nelemnets = 0, std::ostream & output = std::cout, int index=0, int block =0);

	virtual bool isScalar(){return false;};;
	virtual bool isVector();
	virtual bool isTensor2();
	virtual bool isTensor3();
	virtual bool isTensor4();


protected:
	// Protected constructor w/o arguments for derived objects implementing their own registration mechanism
	//GPUPropagatorType();
	/// perform the actual calculation
	virtual void calculate(int index, int block) = 0;
	/// Invalidate all cached streams (e.g. in case the mass/width changes)
	virtual void InvalidateCache(unsigned int index);

	/// Data Stream for the imaginary part
	std::vector< std::vector<GPUDataStream<T>*> > mImagstream;
};



template <>
class GPUPropagatorType<float>: public GPUPropagator, public GPUDataDependentObjectType<float2> {
public:
	/// Constructor
	GPUPropagatorType(GPUPartialWaveAnalysis * ana, char * name, std::vector<char **> parnames, unsigned int npar);
	/// Constructor taking mass and with vectors
	GPUPropagatorType(GPUPartialWaveAnalysis * ana,
						std::vector<char *> names,
						std::vector<unsigned int *> _Parameters,
						std::vector<char **> parnames);
	/// Destructor
	virtual ~GPUPropagatorType();

	// () operator; performs the actual stream calculation in derived classes
	virtual GPUDataStream<float2> * operator()(int index =0, int block=0) =0;

	/// Get the real part
	virtual GPUDataStream<float> * realpart(int index,
										int block);

	/// Get the imaginary part
	virtual GPUDataStream<float> * imagpart(int index,
										int block);

	/// Read the stream to memory
	virtual float2 * Read(int index=0);

	/// Read a block of the stream to memory
	virtual float2 * ReadBlock(int index=0, int block = 0);
	/// Reset cached information at index
	virtual void Reset(int index=0);
	/// Reset the cached streams at index and block
	virtual void Reset(int index, int block);
	/// Read the stream to memory and print contents
	/** Print nelements, for nelements < 1, all elemnts are printed, in the second argument,
	a different output stream can be specified, default is cout */
	virtual void Print(int nelemnets = 0, std::ostream & output = std::cout, int index=0, int block =0);


	virtual bool isScalar(){return true;};
	virtual bool isVector(){return false;};
	virtual bool isTensor2(){return false;};
	virtual bool isTensor3(){return false;};
	virtual bool isTensor4(){return false;};


protected:
	// Protected constructor w/o arguments for derived objects implementing their own registration mechanism
	//GPUPropagatorType();
	/// perform the calculation of real and imaginary part
	virtual void calculate(int index, int block);
	/// Invalidate all cached streams (e.g. in case the mass/width changes)
	virtual void InvalidateCache(unsigned int index);
	/// The cached calculated real stream
	std::vector<std::vector<GPUDataStream<float> *> > mrealstream;
	/// The cached calculated imaginary stream
	std::vector<std::vector<GPUDataStream<float> *> > mimagstream;
};

/// A scalar propagator (a complex number)
typedef GPUPropagatorType<float> GPUScalarPropagator;
/// A vector propagator (a four-vector of complex numbers)
typedef GPUPropagatorType<float4> GPUVectorPropagator;
/// A rank 2 propagator (a 4x4 matrix of complex numbers)
typedef GPUPropagatorType<float44> GPUTensor2Propagator;
/// A rank 3 propagator (a 4x4x4 matrix of complex numbers)
typedef GPUPropagatorType<float444> GPUTensor3Propagator;


#endif /* GPUPROPAGATORTYPE_H_ */
