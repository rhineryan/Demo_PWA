/* Complex_cpu.h  -- source for interface functions to the kernels
 defined in /scratchfs/bes/xiongxa/Demo_PWA_GPUPWA/GPUPWA/GPUPWA/Complex.cl, the corresponding binaries are in binfiles/Complex_cpu.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#include"Complex_cpu.h"
#include"KernelFile.h"
#include<vector>
#include<iostream>
#include<cassert>


namespace Complex_CPU{

	 cl::Kernel * k_kernelmultiplycomplex = 0;
	 cl::Kernel * k_kerneladdcomplex = 0;
	 cl::Kernel * k_kernelmultiplycomplexf = 0;
	 cl::Kernel * k_kernelcomplexsplit = 0;
	 cl::Kernel * k_kerneltensormult_c4_c = 0;
	 cl::Kernel * k_kerneltensormult_4_c = 0;
	 cl::Kernel * k_kerneltensormult_c_c44 = 0;
	 int prepare_kernels(const DeviceInterface * dev){
		 FILE * input = fopen("binfiles/Complex_cpu.bin","rb");
		 if(!input){
			 	std::cerr << "Loading binary file binfiles/Complex_cpu.bin failed \n";
			 	return FAILURE;
		 }
		 fseek(input, 0L, SEEK_END);
		 size_t size = ftell(input);
		 rewind(input);
		 cl_int err;
		 char * binary = new char[size];
		 fread(binary, sizeof(char), size, input);
		 fclose(input);
		 cl::Program::Binaries binaries;
		 std::vector<int> binstatus;
		 for(unsigned int d=0; d < (*(dev->GetDevices())).size(); d++){
			 binstatus.push_back(0);
			 binaries.push_back(std::make_pair(binary, size));
		 }
		 cl::Program * bProgram = new cl::Program(*(dev->GetContext()),
		 						   *(dev->GetDevices()),
		 						   binaries,
		 						   &binstatus,
		 						   &err);
		 if (err != CL_SUCCESS) {
			 	std::cerr << "Loading binaries failed (" << err << ")\n";
			 	return FAILURE;
		 }
		 err = bProgram->build(*(dev->GetDevices()));
		 if (err != CL_SUCCESS) {
		 	std::cerr << "Program::build() failed (" << err << ")\n";
		 	return FAILURE;
		 }

		 k_kernelmultiplycomplex = new cl::Kernel(*bProgram, "kernelmultiplycomplex", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmultiplycomplex\n";
			 return FAILURE;
		 }

		 k_kerneladdcomplex = new cl::Kernel(*bProgram, "kerneladdcomplex", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneladdcomplex\n";
			 return FAILURE;
		 }

		 k_kernelmultiplycomplexf = new cl::Kernel(*bProgram, "kernelmultiplycomplexf", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmultiplycomplexf\n";
			 return FAILURE;
		 }

		 k_kernelcomplexsplit = new cl::Kernel(*bProgram, "kernelcomplexsplit", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcomplexsplit\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_c4_c = new cl::Kernel(*bProgram, "kerneltensormult_c4_c", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_c4_c\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_4_c = new cl::Kernel(*bProgram, "kerneltensormult_4_c", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_4_c\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_c_c44 = new cl::Kernel(*bProgram, "kerneltensormult_c_c44", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_c_c44\n";
			 return FAILURE;
		 }

	 return 0;
	 }



	 int kernelmultiplycomplex(const DeviceInterface * dev, Stream<float2> * in1, Stream<float2> * in2, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in1->GetEvent()));
		 err = k_kernelmultiplycomplex->setArg(0, *(*in1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in2 != in1)
			 evvec->push_back((in2->GetEvent()));
		 err = k_kernelmultiplycomplex->setArg(1, *(*in2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmultiplycomplex->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmultiplycomplex, cl::NullRange, cl::NDRange(in1->GetD1(),in1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneladdcomplex(const DeviceInterface * dev, Stream<float2> * in1, Stream<float2> * in2, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in1->GetEvent()));
		 err = k_kerneladdcomplex->setArg(0, *(*in1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in2 != in1)
			 evvec->push_back((in2->GetEvent()));
		 err = k_kerneladdcomplex->setArg(1, *(*in2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneladdcomplex->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneladdcomplex, cl::NullRange, cl::NDRange(in1->GetD1(),in1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmultiplycomplexf(const DeviceInterface * dev, Stream<float2> * in1, Stream<float> * in2, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in1->GetEvent()));
		 err = k_kernelmultiplycomplexf->setArg(0, *(*in1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((in2->GetEvent()));
		 err = k_kernelmultiplycomplexf->setArg(1, *(*in2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmultiplycomplexf->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmultiplycomplexf, cl::NullRange, cl::NDRange(in1->GetD1(),in1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelcomplexsplit(const DeviceInterface * dev, Stream<float2> * myin, Stream<float> * real, Stream<float> * imag){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((myin->GetEvent()));
		 err = k_kernelcomplexsplit->setArg(0, *(*myin)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcomplexsplit->setArg(1, *(*real)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcomplexsplit->setArg(2, *(*imag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcomplexsplit, cl::NullRange, cl::NDRange(myin->GetD1(),myin->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 real->SetEvent(event);

		 imag->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_c4_c(const DeviceInterface * dev, Stream<float4> * lreal, Stream<float4> * limag, Stream<float> * rreal, Stream<float> * rimag, Stream<float4> * resultreal, Stream<float4> * resultimag){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((lreal->GetEvent()));
		 err = k_kerneltensormult_c4_c->setArg(0, *(*lreal)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(limag != lreal)
			 evvec->push_back((limag->GetEvent()));
		 err = k_kerneltensormult_c4_c->setArg(1, *(*limag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((rreal->GetEvent()));
		 err = k_kerneltensormult_c4_c->setArg(2, *(*rreal)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(rimag != rreal)
			 evvec->push_back((rimag->GetEvent()));
		 err = k_kerneltensormult_c4_c->setArg(3, *(*rimag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_c4_c->setArg(4, *(*resultreal)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_c4_c->setArg(5, *(*resultimag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_c4_c, cl::NullRange, cl::NDRange(lreal->GetD1(),lreal->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 resultreal->SetEvent(event);

		 resultimag->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_4_c(const DeviceInterface * dev, Stream<float4> * lreal, Stream<float> * rreal, Stream<float> * rimag, Stream<float4> * resultreal, Stream<float4> * resultimag){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((lreal->GetEvent()));
		 err = k_kerneltensormult_4_c->setArg(0, *(*lreal)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((rreal->GetEvent()));
		 err = k_kerneltensormult_4_c->setArg(1, *(*rreal)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(rimag != rreal)
			 evvec->push_back((rimag->GetEvent()));
		 err = k_kerneltensormult_4_c->setArg(2, *(*rimag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_4_c->setArg(3, *(*resultreal)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_4_c->setArg(4, *(*resultimag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_4_c, cl::NullRange, cl::NDRange(lreal->GetD1(),lreal->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 resultreal->SetEvent(event);

		 resultimag->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_c_c44(const DeviceInterface * dev, Stream<float> * lreal, Stream<float> * limag, Stream<float44> * rreal, Stream<float44> * rimag, Stream<float44> * resultreal, Stream<float44> * resultimag){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((lreal->GetEvent()));
		 err = k_kerneltensormult_c_c44->setArg(0, *(*lreal)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(limag != lreal)
			 evvec->push_back((limag->GetEvent()));
		 err = k_kerneltensormult_c_c44->setArg(1, *(*limag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((rreal->GetEvent()));
		 err = k_kerneltensormult_c_c44->setArg(2, *(*rreal)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(rimag != rreal)
			 evvec->push_back((rimag->GetEvent()));
		 err = k_kerneltensormult_c_c44->setArg(3, *(*rimag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_c_c44->setArg(4, *(*resultreal)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_c_c44->setArg(5, *(*resultimag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_c_c44, cl::NullRange, cl::NDRange(lreal->GetD1(),lreal->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 resultreal->SetEvent(event);

		 resultimag->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

}
