/*
 * Stream.h
 *
 *  Created on: Apr 8, 2010
 *      Author: nberger
 */

#ifndef STREAM_H_
#define STREAM_H_


#include <tr1/memory> // used for the shared_ptr
#include <CL/cl.hpp>
#include "../float44.h"
#include "../float444.h"

class DeviceInterface;
class cl::Buffer;

/// Class interfacing to OpenCL buffers (memory objects)
template <typename T>
class Stream {
public:
	/// Fix the type of the stream
	enum Streamtype{READONLY, WRITEONLY, READWRITE};
	/// Constructor for a 1D stream
	Stream(const DeviceInterface * dev, unsigned int size, Streamtype type = READWRITE);
	/// Constructor for a 2D stream
	Stream(const DeviceInterface * dev, unsigned int d1, unsigned int d2, Streamtype type = READWRITE);
	/// Constructor for a 3D stream
	Stream(const DeviceInterface * dev, unsigned int d1, unsigned int d2, unsigned int d3, Streamtype type = READWRITE);
	/// Destructor
	virtual ~Stream();
	/// Bracket operator returns the buffer
	cl::Buffer * operator()(){return  &mbuffer;};

	/// Write the stream contents into the device
	void Write(T * data);
	/// Read the Stream contents from device to memory
	void Read(T * data, std::vector<cl::Event> *evvec =0);
	/// Allocate memory and then read the stream contents into it
	T * AllocateRead(std::vector<cl::Event> *evvec =0);

	/// Wait for event
	void Wait(){ mevent.wait();};

	/// Get the event
	cl::Event GetEvent()
		{return mevent;};
	/// Set the event
	void SetEvent(cl::Event ev){
		mevent = ev;};


	/// Get the size in the first dimension
	unsigned int GetD1(){return md1;};
	/// Get the size in the second dimension
	unsigned int GetD2(){return md2;};
	/// Get the size in the third dimension
	unsigned int GetD3(){return md3;};

	/// get size in memory (static version for memory allocation
	static unsigned int memsize(int size){return size*sizeof(T);};
	/// get size in memory (dynamic version)
	unsigned int memsize(){return mmemsize;};

	/// Get the total memory used by streams of this type
	static unsigned int GetMemoryUse(){return mmemoryuse;};


	/// Get the device where this stream exists
	const DeviceInterface * GetDeviceInterface() const {return mdev;};

protected:
	/// Convert a Streamtype to a OpenCL memory type flag
	cl_mem_flags toclmemflag(Streamtype t);

	/// the actual OpenCL buffer holding the stream data
	cl::Buffer  mbuffer;
	/// Device, on which the buffer resides
	const DeviceInterface * mdev;
	/// Size of the buffer in memory
	const unsigned int mmemsize;
	/// Dimensionality of the buffer
	const unsigned int mdim;
	/// Size of the buffer in first dimension
	const unsigned int md1;
	/// Size of the buffer in second dimension
	const unsigned int md2;
	/// Size of the buffer in third dimension
	const unsigned int md3;
	/// Event associated with the buffer - contents will be valid after Event.Wait() returns
	cl::Event mevent;
	/// Total memory used by this type of buffer
	static unsigned int mmemoryuse;
};

/// Stream of floats
typedef Stream<cl_float> FloatStream;
/// Stream of float2s
typedef Stream<float2> Float2Stream;
/// Stream of float3s
//typedef Stream<float3> Float3Stream;
/// Stream of float4s
typedef Stream<float4> Float4Stream;
/// Stream of float16s
typedef Stream<float16> Float16Stream;
/// Stream of float44s
typedef Stream<float44> Float44Stream;
/// Stream of float444s
typedef Stream<float444> Float444Stream;
/// Stream of doubles
typedef Stream<cl_double> DoubleStream;
/// Stream of float2s
typedef Stream<double2> Double2Stream;

/// Global function returning the total memory used by streams on the GPU
unsigned int GetStreamMemoryUse();
/// Global function printing the memory used by each type of stream on the GPU
unsigned int PrintStreamMemoryUse();

#endif /* STREAM_H_ */
