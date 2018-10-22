/*
 * opencltest.cpp
 *
 *  Created on: Mar 2, 2010
 *      Author: nberger
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <cassert>

#include <CL/cl.hpp>

#include "KernelFile.h"
#include "DeviceInterface.h"
#include "Stream.h"

#include "testkernels.h"

#define FAILURE -1
#define SUCCESS 0

#define mysize 20

int main(){
	cl_int err;

	// Platform info
/*.	std::vector<cl::Platform> platforms;
	std::cout<<"Getting Platform Information\n";
	err = cl::Platform::get(&platforms);
	if(err != CL_SUCCESS){
		std::cerr << "Platform::get() failed (" << err << ")" << std::endl;
		return FAILURE;
	}

	std::vector<cl::Platform>::iterator i;

	if(platforms.size() > 0) {
		for(i = platforms.begin(); i != platforms.end(); ++i){
			//std::cout << (*i).getInfo<CL_PLATFORM_VENDOR>(&err).c_str() << std::endl;
			if(!strcmp((*i).getInfo<CL_PLATFORM_VENDOR>(&err).c_str(), "Advanced Micro Devices, Inc.")){
				break;
			}
		}
	}
	if(err != CL_SUCCESS){
		std::cerr << "Platform::getInfo() failed (" << err << ")" << std::endl;
		return FAILURE;
	}*/

	/*
	 * If we could find our platform, use it. Otherwise pass a NULL and get whatever the
	 * implementation thinks we should be using.
	 */

	/*cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM, (cl_context_properties)(*i)(), 0 };

	std::cout<<"Creating a context AMD platform\n";
	cl::Context context(CL_DEVICE_TYPE_GPU, cps, NULL, NULL, &err);
	if (err != CL_SUCCESS) {
		std::cerr << "Context::Context() failed (" << err << ")\n";
		return FAILURE;
	}

	std::cout<<"Getting device info\n";
	std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
	if (err != CL_SUCCESS) {
		std::cerr << "Context::getInfo() failed (" << err << ")\n";
		return FAILURE;
	}

	if (devices.size() == 0) {
		std::cerr << "No device available\n";
		return FAILURE;
	}

	std::cout<<"Loading and compiling CL source\n";
	KernelFile file;
	if (!file.open("HelloCL_Kernels.cl")) {
		std::cerr << "We couldn't load CL source code\n";
		return FAILURE;
	}
	cl::Program::Sources sources(1, std::make_pair(file.source().data(), file.source().size()));
	cl::Program*    pProgram;
	pProgram = new cl::Program(context, sources);
	if (err != CL_SUCCESS) {
		std::cerr << "Program::Program() failed (" << err << ")\n";
		return FAILURE;
   }
	cl::Program&    program = *pProgram;
	err = program.build(devices);
	if (err != CL_SUCCESS) {
		std::cerr << "Program::build() failed (" << err << ")\n";
		return FAILURE;
	}

	std::vector<size_t> svec = program.getInfo<CL_PROGRAM_BINARY_SIZES>();
	std::cout << "NSizes: " << svec.size() << std::endl;
	std::cout << "Size(0): " << svec[0] << std::endl;

	std::vector<char *> bvec = program.getInfo<CL_PROGRAM_BINARIES>();
	std::cout << bvec.size() << std::endl;

	cl::Kernel kernel(program, "hello", &err);
	if (err != CL_SUCCESS) {
		std::cerr << "Kernel::Kernel() failed (" << err << ")\n";
		return FAILURE;
	}
	if (err != CL_SUCCESS) {
		std::cerr << "Kernel::setArg() failed (" << err << ")\n";
		return FAILURE;
	}

	cl::CommandQueue queue(context, devices[0], 0, &err);
	if (err != CL_SUCCESS) {
		std::cerr << "CommandQueue::CommandQueue() failed (" << err << ")\n";
	}

	std::cout<<"Running CL program\n";
	err = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(4, 4), cl::NDRange(2, 2));

	if (err != CL_SUCCESS) {
		std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
		return FAILURE;
	}

	err = queue.finish();
	if (err != CL_SUCCESS) {
		std::cerr << "Event::wait() failed (" << err << ")\n";
	}

	delete pProgram;*/


	DeviceInterface * devGPU = new DeviceInterface(CL_DEVICE_TYPE_GPU);
	if(devGPU->initialized() != OK)
		return FAILURE;
	DeviceInterface * devCPU = new DeviceInterface(CL_DEVICE_TYPE_CPU);
	if(devCPU->initialized() != OK)
		return FAILURE;
	std::cout << "Number of GPU queues: " << devGPU->GetNQueues() << std::endl;
	std::cout << "GPU block size: " << devGPU->GetBlockSize()/(1024*1024) <<"M" << std::endl;
	std::cout << "Number of CPU queues: " << devCPU->GetNQueues() << std::endl;
	std::cout << "CPU block size: " << devCPU->GetBlockSize()/(1024*1024) <<"M"  << std::endl;



	FloatStream * fstream = new FloatStream(devGPU, mysize, FloatStream::READWRITE);
	FloatStream * f4stream = new FloatStream(devGPU, mysize, FloatStream::READWRITE);
	FloatStream * outstream = new FloatStream(devGPU, mysize, FloatStream::WRITEONLY);

	float data[mysize];
	float data4[mysize];

	for(int i=0; i < mysize; i++){
		data[i] = i;
		data4[i] = 3*i;

	}

	clock_t start = clock();
	//for(int i =0; i < 100000; i++){
	fstream->Write(data);
	//std::cout << "Written" << std::endl;
	f4stream->Write(data4);
	//std::cout << "Written 4" << std::endl;

	for(int i=0; i < mysize; i++){
			data[i] = 777;
			data4[i] = 3*777;

	}

	testkernels_GPU::prepare_kernels(devGPU);

	testkernels_GPU::testmul(devGPU, outstream);



/*	err = devGPU->GetQueue()->finish();
	if (err != CL_SUCCESS) {
		std::cerr << "Event::wait() failed (" << err << ")\n";
	}*/

	//f4stream->Read(data4);

/*	err = devGPU->GetQueue()->finish();
	if (err != CL_SUCCESS) {
		std::cerr << "Event::wait() failed (" << err << ")\n";
	}*/

	//for(int i=0; i <20; i++)
	//	std::cout << data4[i] << std::endl;


/*	KernelFile file;
	if (!file.open("testkernels.cl")) {
		std::cerr << "We couldn't load CL source code\n";
		return FAILURE;
	}


	cl::Program::Sources sources(1, std::make_pair(file.source().data(), file.source().size()));
	cl::Program*    pProgram;
	pProgram = new cl::Program(*(devGPU->GetContext()), sources, &err);
	if (err != CL_SUCCESS) {
		std::cerr << "Program::Program() failed (" << err << ")\n";
		return FAILURE;
	}
	cl::Program&    program = *pProgram;
	err = program.build(*(devGPU->GetDevices()));
	if (err != CL_SUCCESS) {
		std::cerr << "Program::build() failed (" << err << ")\n";
		return FAILURE;
	}

	std::vector<size_t> svec;
	svec = program.getInfo<CL_PROGRAM_BINARY_SIZES>();
	//err = program.getInfo<std::vector<size_t> >(CL_PROGRAM_BINARY_SIZES, svec);
	//if (err != CL_SUCCESS) {
	//	std::cerr << "Program::getInfo failed (" << err << ")\n";
	//	return FAILURE;
	//}

	//std::vector<char *> bvec;
	for(unsigned int i=0; i < svec.size(); i++){
			std::cout << svec[i] << std::endl;
			//bvec.push_back(new char[svec[i]]);
	}

	//err = program.getInfo<std::vector<char *> >(CL_PROGRAM_BINARIES, bvec);
	size_t size = svec[0];
	//err = clGetProgramInfo(program(), CL_PROGRAM_BINARY_SIZES, sizeof(size), &size, NULL);
	//std::cout << size << std::endl;
	char * binary = new char[size];
	char * buffers[1];
	buffers[0] = binary;

	err = clGetProgramInfo(program(), CL_PROGRAM_BINARIES, sizeof(buffers), &buffers, NULL);

	FILE * output = fopen("kernel.bin", "wb");
	fwrite(binary, sizeof(char),size,output);
	fclose(output);
	delete binary;
	std::cout << "Wrote kernel.bin" << std::endl;


	FILE * input = fopen("kernel.bin","rb");
	fseek(input, 0L, SEEK_END);
	size = ftell(input);
	std::cout << size << std::endl;
	rewind(input);
	binary = new char[size];
	fread(binary, sizeof(char), size, input);
	fclose(input);

	//buffers[0] = binary;
	cl::Program::Binaries binaries(1, std::make_pair(binary, size));


	std::vector<int> binstatus;
	binstatus.push_back(0);
	cl::Program * bProgram = new cl::Program(*(devGPU->GetContext()),
							   *(devGPU->GetDevices()),
							   binaries,
							   &binstatus,
							   &err);
	if (err != CL_SUCCESS) {
		std::cerr << "Loading binaries failed (" << err << ")\n";
		return FAILURE;
	}

	std::cout << binstatus[0] << std::endl;

	err = bProgram->build(*(devGPU->GetDevices()));
	if (err != CL_SUCCESS) {
		std::cerr << "Program::build() failed (" << err << ")\n";
		return FAILURE;
	}


	cl::Kernel kernel(*bProgram, "testmul", &err);
	if (err != CL_SUCCESS) {
		std::cerr << "Kernel::Kernel() failed (" << err << ")\n";
		return FAILURE;
	}*/




/*	err = kernel.setArg(0, f4stream);
	if (err != CL_SUCCESS) {
		std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
		return FAILURE;
	}

	err = kernel.setArg(1, fstream);
	if (err != CL_SUCCESS) {
		std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
		return FAILURE;
	}
*/

/*	if (err != CL_SUCCESS) {
		std::cerr << "Creating output buffer failed (" << err << ")\n";
		return FAILURE;
	}

	err = kernel.setArg(0, *(*outstream)());
	if (err != CL_SUCCESS) {
		std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
		return FAILURE;
	}
	//cl::Event * ev = new cl::Event();
	//std::vector<cl::Event> evvec;
	err = devGPU->GetQueue()->enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(mysize,1), cl::NDRange(mysize,1), 0, 0 );
	if (err != CL_SUCCESS) {
		std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
		return FAILURE;
	}
	std:: cout << "kernel enqued ok!" << std::endl;

*/

	//err = devGPU->GetQueue()->enqueueBarrier();
	//std:: cout << "enqued barrier!" << std::endl;
	//evvec.push_back(*ev);
	//ev->wait();
	/*err = devGPU->GetQueue()->finish();
	if (err != CL_SUCCESS) {
		std::cerr << "Event::wait() failed (" << err << ")\n";
	}
	std:: cout << "finished...!" << std::endl;*/
	//err = devGPU->GetQueue()->finish();
	//cl::Event * ev2 = new cl::Event();
	//std:: cout << "trying to read!" << std::endl;
	//outstream->Read(data4, &evvec, ev2);
//	outstream->Read(data4);
	//std:: cout << "read!" << std::endl;
/*	err = devGPU->GetQueue()->finish();
	if (err != CL_SUCCESS) {
		std::cerr << "Event::wait() failed (" << err << ")\n";
	}
	std:: cout << "finished...!" << std::endl;

	//ev2->wait();

	for(int i=0; i <20; i++)
		std::cout << data4[i] << std::endl;


	clock_t end = clock();
	std::cout << end-start << " ticks = " <<(float)(end-start)/(float)CLOCKS_PER_SEC << " s" << std::endl;
*/
	std::cout<<"Done\nPassed!\n";
	return OK;

}
