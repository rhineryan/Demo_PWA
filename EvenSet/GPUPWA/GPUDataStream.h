/// \file GPUDataStream.h
#ifndef _GPU_DATA_STREAM_H
#define _GPU_DATA_STREAM_H

#include "Stream.h"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

class DeviceInterface;

/// Base class for all stream data on the GPU
/** This class implements 1D and 2D streams by acting as a wrapper to Stream<T>, which in turn
 * implements the interface to OpenCL buffers and also
 *  handles collections of four or sixteen GPUDataStreams for implementation of rank3 and 4 tensors.
 *  This is only semi-elegant, but has worked for a long time.
 *
 */

template <typename T>
class GPUDataStream :
	public Stream<T>
{
public:
	/// Constructor
	GPUDataStream(const DeviceInterface * dev, unsigned int size);
	/// Constructor for 2D stream
	GPUDataStream(const DeviceInterface * dev, unsigned int * sizes);
	/// Constructor for 2D stream
	GPUDataStream(const DeviceInterface * dev, unsigned int n, unsigned int m);
	/// Constructor for multi stream
	/** Flag is currently not needed, however we do somehow require a difference to
	 *  2d streams
	 */
	GPUDataStream(const DeviceInterface * dev, unsigned int flag, unsigned int nstream, unsigned int size);
	/// Destructor
	virtual ~GPUDataStream(void);
	/// Size of one dimension in the stream, 8192 on current hardware
	static const int DIMSIZE;
	/// Print a stream (used for debugging)
	void print();
	/// Print stream elements (used for debugging)
	void printAt(int index, int n =1);

	/// Sum a stream on the CPU
	double sumCPU();

	/// Sum a stream componentwise on the CPU in double precision
	double * sumcomponentsCPU();

	/// Sum a two stream componentwise on the CPU in double precision
	double * sumcomponentsweightedCPU(GPUDataStream<float> * weights);

	/// Sum a stream componentwise on the GPU in double precision
	double * sumcomponents(bool keepmemory = false);

	/// Sum a stream to a double
	double sum(bool keepmemory = false);

	/// Sum a two stream componentwise on the CPU in double precision
	double * sumcomponentsweighted(GPUDataStream<float> * weights,bool keepmemory = false);

	/// Sum a 2D stream to an array of doubles
	double * sum2d(unsigned int d1, bool keepmemory = false);

	/// Sum a 2D stream to an array of doubles, using weights
	double * sum2dweighted(GPUDataStream<float4> * weights, unsigned int d1, bool keepmemory = false);

	/// Sum a 2D stream to an array of doubles
	void  allocatesum2dspace(unsigned int d1);

	/// Minimum of two doubles
	double min(double a, double b){
		if(a > b)
			return b;
		return a;
	}

	/// Access to a substream in a multistream
	virtual GPUDataStream<T> *& operator() (int index){
		assert(index < mnstreams);
		return mstreams[index];
	};

	/// Access to a substream in a multistream
	virtual GPUDataStream<T> *& operator() (int index1, int index2){
		assert(index2 + 4*index1 < mnstreams);
			return mstreams[index1*4+index2];
	};

	/// Access to the first substream in a 4-stream multistream
	virtual GPUDataStream<T> *& x() {
		assert(mnstreams == 4);
		return mstreams[0];
	}

	/// Access to the second substream in a 4-stream multistream
	virtual GPUDataStream<T> *& y() {
		assert(mnstreams == 4);
		return mstreams[1];
	}

	/// Access to the third substream in a 4-stream multistream
	virtual GPUDataStream<T> *& z() {
		assert(mnstreams == 4);
		return mstreams[2];
	}

	/// Access to the fourth substream in a 4-stream multistream
	virtual GPUDataStream<T> *& w() {
		assert(mnstreams == 4);
		return mstreams[3];
	}

	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& xx() {
		assert(mnstreams == 16);
		return mstreams[0];
	}

	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& xy() {
		assert(mnstreams == 16);
		return mstreams[1];
	}

	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& xz() {
		assert(mnstreams == 16);
		return mstreams[2];
	}

	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& xw() {
		assert(mnstreams == 16);
		return mstreams[3];
	}

	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& yx() {
		assert(mnstreams == 16);
		return mstreams[4];
	}
	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& yy() {
		assert(mnstreams == 16);
		return mstreams[5];
	}
	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& yz() {
		assert(mnstreams == 16);
		return mstreams[6];
	}
	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& yw() {
		assert(mnstreams == 16);
		return mstreams[7];
	}
	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& zx() {
		assert(mnstreams == 16);
		return mstreams[8];
	}
	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& zy() {
		assert(mnstreams == 16);
		return mstreams[9];
	}
	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& zz() {
		assert(mnstreams == 16);
		return mstreams[10];
	}
	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& zw() {
		assert(mnstreams == 16);
		return mstreams[11];
	}
	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& wx() {
		assert(mnstreams == 16);
		return mstreams[12];
	}
	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& wy() {
		assert(mnstreams == 16);
		return mstreams[13];
	}
	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& wz() {
		assert(mnstreams == 16);
		return mstreams[14];
	}
	/// Access a substream in a 16-stream multistream
	virtual GPUDataStream<T> *& ww() {
		assert(mnstreams == 16);
		return mstreams[15];
	}




protected:

	//double * m_sum;

	/// Vector of substreams in a multistream
	std::vector<GPUDataStream<T> *> mstreams;
	/// Number of substreams in a multistream
	const int mnstreams;
	/// Total number of elements in the stream(s)
	const int mysize;
	/// Vector of streams used for summing
	std::vector<GPUDataStream<double> *> msumstreams;
	/// Vector of streams used for summing componentwise
	std::vector<GPUDataStream<double> *> mcompsumstreams;
	/// Vector of streams used for summing
	std::vector<GPUDataStream<double> *> m2dsumstreams;
	/// Number of events to sum 16 fold in each step
	std::vector<unsigned int> mnsum;
	/// Size of the sum streams
	std::vector<unsigned int> msizes;
	/// Number of events not fitting in the 16 folding
	std::vector<unsigned int> mreminders;

	/// Number of events to sum 16 fold in each step
	std::vector<unsigned int> mnsum2d;
	/// Size of the sum streams
	std::vector<unsigned int> msizes2d;
	/// Number of events not fitting in the 16 folding
	std::vector<unsigned int> mreminders2d;

	/// call a kernel to sum 16*n elements to n doubles
	void callsumkernel(unsigned int n);
	/// call a kernel to sum n elements to 1 double with an offset
	void callremindersumkernel(unsigned int n, unsigned int offset, unsigned int resultoffset);
	/// calculate the number of events in the steps of the sum
	void initsumnumbers();
	/// calculate the number of events in the steps of the sum
	void init2dsumnumbers(unsigned int d1);

};



///GPUDataStream of float elements
typedef GPUDataStream<float> GPUScalarDataStream;
///GPUDataStream of float2 elements
typedef GPUDataStream<float2> GPUFloat2DataStream;
///GPUDataStream of float4 elements
typedef GPUDataStream<float4> GPUVectorDataStream;
///GPUDataStream of float44 elements
typedef GPUDataStream<float16> GPUTensorDataStream;

#endif
