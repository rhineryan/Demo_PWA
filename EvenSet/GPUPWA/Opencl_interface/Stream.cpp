/*
 * Stream.cpp
 *
 *  Created on: Apr 8, 2010
 *      Author: nberger
 */

#include "Stream.h"
#include <cassert>
#include "DeviceInterface.h"
#include "vector_operators.h"

template <typename T>
Stream<T>::Stream(const DeviceInterface * dev, unsigned int size, Streamtype type)
	:mdev(dev),mmemsize(size*sizeof(T)),mdim(1),md1(size),md2(1),md3(1) {
	cl_int err = CL_SUCCESS;
	//mevent = new cl::Event();
	if(mmemsize){
		mbuffer =  cl::Buffer(*(dev->GetContext()),
							toclmemflag(type),
							mmemsize,
							NULL,
							&err);
		if(err != CL_SUCCESS){
			std::cout << "Stream error: Failed to allcoate memory on device "
					<< dev->GetDeviceType() << " aborting now!" << std::endl;
			assert(0);
		}
	}

	mmemoryuse += mmemsize;
}

template <typename T>
Stream<T>::Stream(const DeviceInterface * dev, unsigned int _d1, unsigned int _d2, Streamtype type)
	:mdev(dev),mmemsize(_d1*_d2*sizeof(T)),mdim(2),md1(_d1),md2(_d2),md3(1) {
	cl_int err = CL_SUCCESS;
	//mevent = new cl::Event();
	if(mmemsize){
		mbuffer =  cl::Buffer(*(dev->GetContext()),
				toclmemflag(type),
				mmemsize,
				0,
				&err);
		if(err != CL_SUCCESS){
			std::cout << "Stream error: Failed to allcoate memory on device "
				<< dev->GetDeviceType() << " aborting now!" << std::endl;
			assert(0);
		}
	}

	mmemoryuse += mmemsize;
}

template <typename T>
Stream<T>::Stream(const DeviceInterface * dev, unsigned int _d1, unsigned int _d2, unsigned int _d3, Streamtype type)
:mdev(dev),mmemsize(_d1*_d2*_d3*sizeof(T)),mdim(3),md1(_d1),md2(_d2),md3(_d3) {
	cl_int err = CL_SUCCESS;
	//mevent = new cl::Event();

	if(mmemsize){
		mbuffer =  cl::Buffer(*(dev->GetContext()),
				toclmemflag(type),
				mmemsize,
				0,
				&err);
		if(err != CL_SUCCESS){
			std::cout << "Stream error: Failed to allcoate memory on device "
					<< dev->GetDeviceType() << " aborting now!" << std::endl;
				assert(0);
		}
	}
	mmemoryuse += mmemsize;
}


template <typename T>
Stream<T>::~Stream() {
	//delete mbuffer;
	mmemoryuse -= mmemsize;
	//mbuffer.release();
	//cl::detail::ReferenceHandler<cl_mem>::release(&mbuffer);

// Are we creating a memory leak here by not deleting mevent?
// With the delete, the whole thing crashes...
//	if(mevent)
//		delete mevent;
//	cout << GetStreamMemoryUse() << endl;
}


template <typename T>
void Stream<T>::Write(T * data) {
	mevent.wait();

	mdev->GetQueue()->enqueueWriteBuffer(mbuffer,
			false,
			0,
			mmemsize,
			data,0,&mevent);
}

template <typename T>
void Stream<T>::Read(T * data, std::vector<cl::Event> *evvec) {
	bool delflag = false;
	if(mevent.getInfo<CL_EVENT_COMMAND_EXECUTION_STATUS>() != CL_COMPLETE){
		if(!evvec){
			evvec = new std::vector<cl::Event>;
			delflag = true;
		}
		evvec->push_back(mevent);
	}
	//std::cout << "Before read (memsize = " <<mmemsize << ")"<< endl;
	//cl::Event w;
	//mevent = w;
	//cout << mbuffer << endl;
	mdev->GetQueue()->enqueueReadBuffer(mbuffer,
			false,
			0,
			mmemsize,
			data,evvec,&mevent);
//	std::cout << "After read" << endl;
//	cout << data << endl;
//	for(int i =0; i < 10000; i++)
//	cout << *data << endl;
	mevent.wait();
//	std::cout << "After wait" << endl;
	if(delflag)
		delete evvec;
}


template <typename T>
T * Stream<T>::AllocateRead(std::vector<cl::Event> *evvec) {
	T * data = new T[mmemsize/sizeof(T)];
	//cout << mmemsize/sizeof(T) << endl;
	Read(data, evvec);
	return data;
}


template <typename T>
cl_mem_flags Stream<T>::toclmemflag(Streamtype t){
	switch(t){
	case READONLY:
		return CL_MEM_READ_ONLY;
	case WRITEONLY:
		return CL_MEM_WRITE_ONLY;
	case READWRITE:
		return CL_MEM_READ_WRITE;
	default:
		std::cout << "Stream warning: Unknown memory access type, using R/W" << std::endl;
		return CL_MEM_READ_WRITE;
	}
}

template <typename T>
unsigned int Stream<T>::mmemoryuse = 0;

template class Stream<cl_int>;
template class Stream<cl_float>;
template class Stream<float2>;
//template class Stream<float3>;
template class Stream<float4>;
template class Stream<float16>;
template class Stream<float44>;
template class Stream<float444>;
template class Stream<cl_double>;
template class Stream<double2>;

unsigned int GetStreamMemoryUse(){
	unsigned int sum = 0;
	sum += Stream<float>::GetMemoryUse();
	sum += Stream<float2>::GetMemoryUse();
	//sum += Stream<float3>::GetMemoryUse();
	sum += Stream<float4>::GetMemoryUse();
	sum += Stream<float16>::GetMemoryUse();
	sum += Stream<float44>::GetMemoryUse();
	sum += Stream<float444>::GetMemoryUse();
	sum += Stream<double>::GetMemoryUse();
	sum += Stream<double2>::GetMemoryUse();
	return sum;
}

unsigned int PrintStreamMemoryUse(){
	cout << "Memory use :" << endl;
	cout << "Float:    " << Stream<float>::GetMemoryUse() << endl;
	cout << "Float2:   " << Stream<float2>::GetMemoryUse() << endl;
	cout << "Float4:   " << Stream<float4>::GetMemoryUse() << endl;
	cout << "Float44:  " << Stream<float44>::GetMemoryUse() << endl;
	cout << "Float444: " << Stream<float444>::GetMemoryUse() << endl;
	cout << "Double:   " << Stream<double>::GetMemoryUse() << endl;
	cout << "Double2:  " << Stream<double2>::GetMemoryUse() << endl;
	cout << "______________________________________________" << endl;
	unsigned int sum = 0;
	sum += Stream<float>::GetMemoryUse();
	sum += Stream<float2>::GetMemoryUse();
	//sum += Stream<float3>::GetMemoryUse();
	sum += Stream<float4>::GetMemoryUse();
	sum += Stream<float16>::GetMemoryUse();
	sum += Stream<float44>::GetMemoryUse();
	sum += Stream<float444>::GetMemoryUse();
	sum += Stream<double>::GetMemoryUse();
	sum += Stream<double2>::GetMemoryUse();
	return sum;
}

