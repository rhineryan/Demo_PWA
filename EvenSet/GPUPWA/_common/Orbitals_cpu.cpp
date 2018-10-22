/* Orbitals_cpu.h  -- source for interface functions to the kernels
 defined in /scratchfs/bes/xiongxa/Demo_PWA_GPUPWA/GPUPWA/GPUPWA/Orbitals.cl, the corresponding binaries are in binfiles/Orbitals_cpu.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#include"Orbitals_cpu.h"
#include"KernelFile.h"
#include<vector>
#include<iostream>
#include<cassert>


namespace Orbitals_CPU{

	 cl::Kernel * k_kernel4orbitaltensor = 0;
	 cl::Kernel * k_kernel4orbitaltensorconst = 0;
	 cl::Kernel * k_kernel3orbitaltensor = 0;
	 cl::Kernel * k_kernel3orbitaltensorconst = 0;
	 cl::Kernel * k_kernelspinproject3_2_2 = 0;
	 int prepare_kernels(const DeviceInterface * dev){
		 FILE * input = fopen("binfiles/Orbitals_cpu.bin","rb");
		 if(!input){
			 	std::cerr << "Loading binary file binfiles/Orbitals_cpu.bin failed \n";
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

		 k_kernel4orbitaltensor = new cl::Kernel(*bProgram, "kernel4orbitaltensor", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernel4orbitaltensor\n";
			 return FAILURE;
		 }

		 k_kernel4orbitaltensorconst = new cl::Kernel(*bProgram, "kernel4orbitaltensorconst", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernel4orbitaltensorconst\n";
			 return FAILURE;
		 }

		 k_kernel3orbitaltensor = new cl::Kernel(*bProgram, "kernel3orbitaltensor", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernel3orbitaltensor\n";
			 return FAILURE;
		 }

		 k_kernel3orbitaltensorconst = new cl::Kernel(*bProgram, "kernel3orbitaltensorconst", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernel3orbitaltensorconst\n";
			 return FAILURE;
		 }

		 k_kernelspinproject3_2_2 = new cl::Kernel(*bProgram, "kernelspinproject3_2_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelspinproject3_2_2\n";
			 return FAILURE;
		 }

	 return 0;
	 }



	 int kernel4orbitaltensor(const DeviceInterface * dev, Stream<float4> * rt, int i, int j, Stream<float44> * delp, Stream<float44> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((rt->GetEvent()));
		 err = k_kernel4orbitaltensor->setArg(0, *(*rt)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel4orbitaltensor->setArg(1, i);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel4orbitaltensor->setArg(2, j);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((delp->GetEvent()));
		 err = k_kernel4orbitaltensor->setArg(3, *(*delp)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel4orbitaltensor->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernel4orbitaltensor, cl::NullRange, cl::NDRange(rt->GetD1(),rt->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernel4orbitaltensorconst(const DeviceInterface * dev, Stream<float4> * rt, int i, int j, float44 delp, Stream<float44> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((rt->GetEvent()));
		 err = k_kernel4orbitaltensorconst->setArg(0, *(*rt)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel4orbitaltensorconst->setArg(1, i);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel4orbitaltensorconst->setArg(2, j);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel4orbitaltensorconst->setArg(3, delp);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel4orbitaltensorconst->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernel4orbitaltensorconst, cl::NullRange, cl::NDRange(rt->GetD1(),rt->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernel3orbitaltensor(const DeviceInterface * dev, Stream<float4> * rt, Stream<float4> * pa, Stream<float444> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((rt->GetEvent()));
		 err = k_kernel3orbitaltensor->setArg(0, *(*rt)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(pa != rt)
			 evvec->push_back((pa->GetEvent()));
		 err = k_kernel3orbitaltensor->setArg(1, *(*pa)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel3orbitaltensor->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernel3orbitaltensor, cl::NullRange, cl::NDRange(rt->GetD1(),rt->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernel3orbitaltensorconst(const DeviceInterface * dev, Stream<float4> * rt, float4 pa, Stream<float444> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((rt->GetEvent()));
		 err = k_kernel3orbitaltensorconst->setArg(0, *(*rt)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel3orbitaltensorconst->setArg(1, pa);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel3orbitaltensorconst->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernel3orbitaltensorconst, cl::NullRange, cl::NDRange(rt->GetD1(),rt->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelspinproject3_2_2(const DeviceInterface * dev, Stream<float44> * gtin, Stream<float44> * Tin, uint i, uint j, Stream<float44> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((gtin->GetEvent()));
		 err = k_kernelspinproject3_2_2->setArg(0, *(*gtin)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(Tin != gtin)
			 evvec->push_back((Tin->GetEvent()));
		 err = k_kernelspinproject3_2_2->setArg(1, *(*Tin)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelspinproject3_2_2->setArg(2, i);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelspinproject3_2_2->setArg(3, j);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelspinproject3_2_2->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelspinproject3_2_2, cl::NullRange, cl::NDRange(gtin->GetD1(),gtin->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

}
