/* Propagators_cpu.h  -- source for interface functions to the kernels
 defined in /scratchfs/bes/xiongxa/Demo_PWA_GPUPWA/GPUPWA/GPUPWA/Propagators.cl, the corresponding binaries are in binfiles/Propagators_cpu.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#include"Propagators_cpu.h"
#include"KernelFile.h"
#include<vector>
#include<iostream>
#include<cassert>


namespace Propagators_CPU{

	 cl::Kernel * k_kernelbreitwigner = 0;
	 cl::Kernel * k_kernelgaussian = 0;
	 cl::Kernel * k_kerneldbreitwignerdmass = 0;
	 cl::Kernel * k_kerneldbreitwignerdwidth = 0;
	 cl::Kernel * k_kerneldbw2dmass = 0;
	 cl::Kernel * k_kerneldbw2dwidth = 0;
	 cl::Kernel * k_kernelmassdependentbreitwigner0 = 0;
	 cl::Kernel * k_kernelmassdependentbreitwigner1 = 0;
	 cl::Kernel * k_kernelmassdependentbreitwigner2 = 0;
	 cl::Kernel * k_kernelmassdependentbreitwigner3 = 0;
	 cl::Kernel * k_kernelmassdependentbreitwigner4 = 0;
	 cl::Kernel * k_kernelmassdependentbreitwigner0dwidth = 0;
	 cl::Kernel * k_kernelmassdependentbreitwigner1dwidth = 0;
	 cl::Kernel * k_kernelmassdependentbreitwigner2dwidth = 0;
	 cl::Kernel * k_kernelmassdependentbreitwigner3dwidth = 0;
	 cl::Kernel * k_kernelmassdependentbreitwigner4dwidth = 0;
	 cl::Kernel * k_kernelmassdependentbreitwigner0dmass = 0;
	 cl::Kernel * k_kernelmassdependentbreitwigner1dmass = 0;
	 cl::Kernel * k_kernelmassdependentbreitwigner2dmass = 0;
	 cl::Kernel * k_kernelmassdependentbreitwigner3dmass = 0;
	 cl::Kernel * k_kernelmassdependentbreitwigner4dmass = 0;
	 cl::Kernel * k_kerneldmassdependentbreitwigner20dwidth = 0;
	 cl::Kernel * k_kerneldmassdependentbreitwigner21dwidth = 0;
	 cl::Kernel * k_kerneldmassdependentbreitwigner22dwidth = 0;
	 cl::Kernel * k_kerneldmassdependentbreitwigner23dwidth = 0;
	 cl::Kernel * k_kerneldmassdependentbreitwigner24dwidth = 0;
	 cl::Kernel * k_kernelflatte2 = 0;
	 cl::Kernel * k_kernelflatte3 = 0;
	 cl::Kernel * k_kernelflatte4 = 0;
	 cl::Kernel * k_kernelsigma = 0;
	 cl::Kernel * k_kernelfnscalarzou = 0;
	 cl::Kernel * k_kernelfnscalarcm2 = 0;
	 cl::Kernel * k_kernelfnscalarcm = 0;
	 cl::Kernel * k_kernelfnscalarchung = 0;
	 cl::Kernel * k_kernel_a0980 = 0;
	 cl::Kernel * k_kernelsumBW = 0;
	 cl::Kernel * k_kernelComBW = 0;
	 int prepare_kernels(const DeviceInterface * dev){
		 FILE * input = fopen("binfiles/Propagators_cpu.bin","rb");
		 if(!input){
			 	std::cerr << "Loading binary file binfiles/Propagators_cpu.bin failed \n";
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

		 k_kernelbreitwigner = new cl::Kernel(*bProgram, "kernelbreitwigner", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelbreitwigner\n";
			 return FAILURE;
		 }

		 k_kernelgaussian = new cl::Kernel(*bProgram, "kernelgaussian", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelgaussian\n";
			 return FAILURE;
		 }

		 k_kerneldbreitwignerdmass = new cl::Kernel(*bProgram, "kerneldbreitwignerdmass", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneldbreitwignerdmass\n";
			 return FAILURE;
		 }

		 k_kerneldbreitwignerdwidth = new cl::Kernel(*bProgram, "kerneldbreitwignerdwidth", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneldbreitwignerdwidth\n";
			 return FAILURE;
		 }

		 k_kerneldbw2dmass = new cl::Kernel(*bProgram, "kerneldbw2dmass", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneldbw2dmass\n";
			 return FAILURE;
		 }

		 k_kerneldbw2dwidth = new cl::Kernel(*bProgram, "kerneldbw2dwidth", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneldbw2dwidth\n";
			 return FAILURE;
		 }

		 k_kernelmassdependentbreitwigner0 = new cl::Kernel(*bProgram, "kernelmassdependentbreitwigner0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmassdependentbreitwigner0\n";
			 return FAILURE;
		 }

		 k_kernelmassdependentbreitwigner1 = new cl::Kernel(*bProgram, "kernelmassdependentbreitwigner1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmassdependentbreitwigner1\n";
			 return FAILURE;
		 }

		 k_kernelmassdependentbreitwigner2 = new cl::Kernel(*bProgram, "kernelmassdependentbreitwigner2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmassdependentbreitwigner2\n";
			 return FAILURE;
		 }

		 k_kernelmassdependentbreitwigner3 = new cl::Kernel(*bProgram, "kernelmassdependentbreitwigner3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmassdependentbreitwigner3\n";
			 return FAILURE;
		 }

		 k_kernelmassdependentbreitwigner4 = new cl::Kernel(*bProgram, "kernelmassdependentbreitwigner4", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmassdependentbreitwigner4\n";
			 return FAILURE;
		 }

		 k_kernelmassdependentbreitwigner0dwidth = new cl::Kernel(*bProgram, "kernelmassdependentbreitwigner0dwidth", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmassdependentbreitwigner0dwidth\n";
			 return FAILURE;
		 }

		 k_kernelmassdependentbreitwigner1dwidth = new cl::Kernel(*bProgram, "kernelmassdependentbreitwigner1dwidth", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmassdependentbreitwigner1dwidth\n";
			 return FAILURE;
		 }

		 k_kernelmassdependentbreitwigner2dwidth = new cl::Kernel(*bProgram, "kernelmassdependentbreitwigner2dwidth", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmassdependentbreitwigner2dwidth\n";
			 return FAILURE;
		 }

		 k_kernelmassdependentbreitwigner3dwidth = new cl::Kernel(*bProgram, "kernelmassdependentbreitwigner3dwidth", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmassdependentbreitwigner3dwidth\n";
			 return FAILURE;
		 }

		 k_kernelmassdependentbreitwigner4dwidth = new cl::Kernel(*bProgram, "kernelmassdependentbreitwigner4dwidth", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmassdependentbreitwigner4dwidth\n";
			 return FAILURE;
		 }

		 k_kernelmassdependentbreitwigner0dmass = new cl::Kernel(*bProgram, "kernelmassdependentbreitwigner0dmass", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmassdependentbreitwigner0dmass\n";
			 return FAILURE;
		 }

		 k_kernelmassdependentbreitwigner1dmass = new cl::Kernel(*bProgram, "kernelmassdependentbreitwigner1dmass", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmassdependentbreitwigner1dmass\n";
			 return FAILURE;
		 }

		 k_kernelmassdependentbreitwigner2dmass = new cl::Kernel(*bProgram, "kernelmassdependentbreitwigner2dmass", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmassdependentbreitwigner2dmass\n";
			 return FAILURE;
		 }

		 k_kernelmassdependentbreitwigner3dmass = new cl::Kernel(*bProgram, "kernelmassdependentbreitwigner3dmass", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmassdependentbreitwigner3dmass\n";
			 return FAILURE;
		 }

		 k_kernelmassdependentbreitwigner4dmass = new cl::Kernel(*bProgram, "kernelmassdependentbreitwigner4dmass", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmassdependentbreitwigner4dmass\n";
			 return FAILURE;
		 }

		 k_kerneldmassdependentbreitwigner20dwidth = new cl::Kernel(*bProgram, "kerneldmassdependentbreitwigner20dwidth", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneldmassdependentbreitwigner20dwidth\n";
			 return FAILURE;
		 }

		 k_kerneldmassdependentbreitwigner21dwidth = new cl::Kernel(*bProgram, "kerneldmassdependentbreitwigner21dwidth", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneldmassdependentbreitwigner21dwidth\n";
			 return FAILURE;
		 }

		 k_kerneldmassdependentbreitwigner22dwidth = new cl::Kernel(*bProgram, "kerneldmassdependentbreitwigner22dwidth", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneldmassdependentbreitwigner22dwidth\n";
			 return FAILURE;
		 }

		 k_kerneldmassdependentbreitwigner23dwidth = new cl::Kernel(*bProgram, "kerneldmassdependentbreitwigner23dwidth", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneldmassdependentbreitwigner23dwidth\n";
			 return FAILURE;
		 }

		 k_kerneldmassdependentbreitwigner24dwidth = new cl::Kernel(*bProgram, "kerneldmassdependentbreitwigner24dwidth", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneldmassdependentbreitwigner24dwidth\n";
			 return FAILURE;
		 }

		 k_kernelflatte2 = new cl::Kernel(*bProgram, "kernelflatte2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelflatte2\n";
			 return FAILURE;
		 }

		 k_kernelflatte3 = new cl::Kernel(*bProgram, "kernelflatte3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelflatte3\n";
			 return FAILURE;
		 }

		 k_kernelflatte4 = new cl::Kernel(*bProgram, "kernelflatte4", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelflatte4\n";
			 return FAILURE;
		 }

		 k_kernelsigma = new cl::Kernel(*bProgram, "kernelsigma", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelsigma\n";
			 return FAILURE;
		 }

		 k_kernelfnscalarzou = new cl::Kernel(*bProgram, "kernelfnscalarzou", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelfnscalarzou\n";
			 return FAILURE;
		 }

		 k_kernelfnscalarcm2 = new cl::Kernel(*bProgram, "kernelfnscalarcm2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelfnscalarcm2\n";
			 return FAILURE;
		 }

		 k_kernelfnscalarcm = new cl::Kernel(*bProgram, "kernelfnscalarcm", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelfnscalarcm\n";
			 return FAILURE;
		 }

		 k_kernelfnscalarchung = new cl::Kernel(*bProgram, "kernelfnscalarchung", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelfnscalarchung\n";
			 return FAILURE;
		 }

		 k_kernel_a0980 = new cl::Kernel(*bProgram, "kernel_a0980", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernel_a0980\n";
			 return FAILURE;
		 }

		 k_kernelsumBW = new cl::Kernel(*bProgram, "kernelsumBW", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelsumBW\n";
			 return FAILURE;
		 }

		 k_kernelComBW = new cl::Kernel(*bProgram, "kernelComBW", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelComBW\n";
			 return FAILURE;
		 }

	 return 0;
	 }



	 int kernelbreitwigner(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelbreitwigner->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelbreitwigner->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelbreitwigner->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelbreitwigner->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelbreitwigner->setArg(4, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelbreitwigner, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelgaussian(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelgaussian->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgaussian->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgaussian->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgaussian->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgaussian->setArg(4, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelgaussian, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneldbreitwignerdmass(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kerneldbreitwignerdmass->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbreitwignerdmass->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbreitwignerdmass->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbreitwignerdmass->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbreitwignerdmass->setArg(4, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneldbreitwignerdmass, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneldbreitwignerdwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kerneldbreitwignerdwidth->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbreitwignerdwidth->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbreitwignerdwidth->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbreitwignerdwidth->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbreitwignerdwidth->setArg(4, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneldbreitwignerdwidth, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneldbw2dmass(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kerneldbw2dmass->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbw2dmass->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbw2dmass->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbw2dmass->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbw2dmass->setArg(4, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneldbw2dmass, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneldbw2dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kerneldbw2dwidth->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbw2dwidth->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbw2dwidth->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbw2dwidth->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldbw2dwidth->setArg(4, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneldbw2dwidth, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmassdependentbreitwigner0(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelmassdependentbreitwigner0->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmassdependentbreitwigner0, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmassdependentbreitwigner1(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelmassdependentbreitwigner1->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmassdependentbreitwigner1, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmassdependentbreitwigner2(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelmassdependentbreitwigner2->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmassdependentbreitwigner2, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmassdependentbreitwigner3(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelmassdependentbreitwigner3->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmassdependentbreitwigner3, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmassdependentbreitwigner4(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelmassdependentbreitwigner4->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmassdependentbreitwigner4, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmassdependentbreitwigner0dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelmassdependentbreitwigner0dwidth->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0dwidth->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0dwidth->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0dwidth->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0dwidth->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0dwidth->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0dwidth->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0dwidth->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmassdependentbreitwigner0dwidth, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmassdependentbreitwigner1dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelmassdependentbreitwigner1dwidth->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1dwidth->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1dwidth->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1dwidth->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1dwidth->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1dwidth->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1dwidth->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1dwidth->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmassdependentbreitwigner1dwidth, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmassdependentbreitwigner2dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelmassdependentbreitwigner2dwidth->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2dwidth->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2dwidth->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2dwidth->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2dwidth->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2dwidth->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2dwidth->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2dwidth->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmassdependentbreitwigner2dwidth, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmassdependentbreitwigner3dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelmassdependentbreitwigner3dwidth->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3dwidth->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3dwidth->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3dwidth->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3dwidth->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3dwidth->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3dwidth->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3dwidth->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmassdependentbreitwigner3dwidth, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmassdependentbreitwigner4dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelmassdependentbreitwigner4dwidth->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4dwidth->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4dwidth->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4dwidth->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4dwidth->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4dwidth->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4dwidth->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4dwidth->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmassdependentbreitwigner4dwidth, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmassdependentbreitwigner0dmass(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelmassdependentbreitwigner0dmass->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0dmass->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0dmass->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0dmass->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0dmass->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0dmass->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0dmass->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner0dmass->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmassdependentbreitwigner0dmass, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmassdependentbreitwigner1dmass(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelmassdependentbreitwigner1dmass->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1dmass->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1dmass->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1dmass->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1dmass->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1dmass->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1dmass->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner1dmass->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmassdependentbreitwigner1dmass, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmassdependentbreitwigner2dmass(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelmassdependentbreitwigner2dmass->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2dmass->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2dmass->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2dmass->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2dmass->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2dmass->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2dmass->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner2dmass->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmassdependentbreitwigner2dmass, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmassdependentbreitwigner3dmass(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelmassdependentbreitwigner3dmass->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3dmass->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3dmass->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3dmass->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3dmass->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3dmass->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3dmass->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner3dmass->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmassdependentbreitwigner3dmass, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmassdependentbreitwigner4dmass(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelmassdependentbreitwigner4dmass->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4dmass->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4dmass->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4dmass->setArg(3, wr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4dmass->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4dmass->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4dmass->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmassdependentbreitwigner4dmass->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmassdependentbreitwigner4dmass, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneldmassdependentbreitwigner20dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g, float pmr, float m1_2, float m2_2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kerneldmassdependentbreitwigner20dwidth->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner20dwidth->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner20dwidth->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner20dwidth->setArg(3, g);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner20dwidth->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner20dwidth->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner20dwidth->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner20dwidth->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneldmassdependentbreitwigner20dwidth, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneldmassdependentbreitwigner21dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g, float pmr, float m1_2, float m2_2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kerneldmassdependentbreitwigner21dwidth->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner21dwidth->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner21dwidth->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner21dwidth->setArg(3, g);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner21dwidth->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner21dwidth->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner21dwidth->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner21dwidth->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneldmassdependentbreitwigner21dwidth, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneldmassdependentbreitwigner22dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g, float pmr, float m1_2, float m2_2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kerneldmassdependentbreitwigner22dwidth->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner22dwidth->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner22dwidth->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner22dwidth->setArg(3, g);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner22dwidth->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner22dwidth->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner22dwidth->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner22dwidth->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneldmassdependentbreitwigner22dwidth, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneldmassdependentbreitwigner23dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g, float pmr, float m1_2, float m2_2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kerneldmassdependentbreitwigner23dwidth->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner23dwidth->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner23dwidth->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner23dwidth->setArg(3, g);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner23dwidth->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner23dwidth->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner23dwidth->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner23dwidth->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneldmassdependentbreitwigner23dwidth, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneldmassdependentbreitwigner24dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g, float pmr, float m1_2, float m2_2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kerneldmassdependentbreitwigner24dwidth->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner24dwidth->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner24dwidth->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner24dwidth->setArg(3, g);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner24dwidth->setArg(4, pmr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner24dwidth->setArg(5, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner24dwidth->setArg(6, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneldmassdependentbreitwigner24dwidth->setArg(7, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneldmassdependentbreitwigner24dwidth, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelflatte2(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g1, float m1a, float m1b, float g2, float m2a, float m2b, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelflatte2->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte2->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte2->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte2->setArg(3, g1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte2->setArg(4, m1a);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte2->setArg(5, m1b);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte2->setArg(6, g2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte2->setArg(7, m2a);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte2->setArg(8, m2b);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte2->setArg(9, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelflatte2, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelflatte3(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g1, float m1a, float m1b, float g2, float m2a, float m2b, float g3, float m3a, float m3b, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelflatte3->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte3->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte3->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte3->setArg(3, g1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte3->setArg(4, m1a);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte3->setArg(5, m1b);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte3->setArg(6, g2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte3->setArg(7, m2a);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte3->setArg(8, m2b);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte3->setArg(9, g3);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte3->setArg(10, m3a);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte3->setArg(11, m3b);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte3->setArg(12, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelflatte3, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelflatte4(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g1, float m1a, float m1b, float g2, float m2a, float m2b, float g3, float m3a, float m3b, float g4, float m4a, float m4b, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelflatte4->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte4->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte4->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte4->setArg(3, g1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte4->setArg(4, m1a);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte4->setArg(5, m1b);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte4->setArg(6, g2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte4->setArg(7, m2a);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte4->setArg(8, m2b);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte4->setArg(9, g3);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte4->setArg(10, m3a);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte4->setArg(11, m3b);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte4->setArg(12, g4);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte4->setArg(13, m4a);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte4->setArg(14, m4b);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelflatte4->setArg(15, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelflatte4, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelsigma(const DeviceInterface * dev, Stream<float> * mx2in, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelsigma->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelsigma->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelsigma, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelfnscalarzou(const DeviceInterface * dev, Stream<float> * mx2in, uint n, Stream<float4> * par, float c, float cs, float2 d, float2 ds, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelfnscalarzou->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarzou->setArg(1, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((par->GetEvent()));
		 err = k_kernelfnscalarzou->setArg(2, *(*par)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarzou->setArg(3, c);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarzou->setArg(4, cs);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarzou->setArg(5, d);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarzou->setArg(6, ds);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarzou->setArg(7, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarzou->setArg(8, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarzou->setArg(9, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelfnscalarzou, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelfnscalarcm2(const DeviceInterface * dev, Stream<float> * mx2in, uint n, Stream<float4> * par, float c, float cs, float2 d, float2 ds, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelfnscalarcm2->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm2->setArg(1, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((par->GetEvent()));
		 err = k_kernelfnscalarcm2->setArg(2, *(*par)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm2->setArg(3, c);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm2->setArg(4, cs);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm2->setArg(5, d);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm2->setArg(6, ds);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm2->setArg(7, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm2->setArg(8, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm2->setArg(9, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelfnscalarcm2, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelfnscalarcm(const DeviceInterface * dev, Stream<float> * mx2in, uint n, Stream<float4> * par, float c, float cs, float2 d, float2 ds, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelfnscalarcm->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm->setArg(1, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((par->GetEvent()));
		 err = k_kernelfnscalarcm->setArg(2, *(*par)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm->setArg(3, c);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm->setArg(4, cs);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm->setArg(5, d);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm->setArg(6, ds);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm->setArg(7, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm->setArg(8, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarcm->setArg(9, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelfnscalarcm, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelfnscalarchung(const DeviceInterface * dev, Stream<float> * mx2in, uint n, Stream<float4> * par, float c, float cs, float2 d, float2 ds, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelfnscalarchung->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarchung->setArg(1, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((par->GetEvent()));
		 err = k_kernelfnscalarchung->setArg(2, *(*par)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarchung->setArg(3, c);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarchung->setArg(4, cs);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarchung->setArg(5, d);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarchung->setArg(6, ds);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarchung->setArg(7, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarchung->setArg(8, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfnscalarchung->setArg(9, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelfnscalarchung, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernel_a0980(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g1, float m1a, float m1b, float g2, float m2a, float m2b, float g3, float m3a, float m3b, float g4, float m4a, float m4b, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernel_a0980->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel_a0980->setArg(1, mr);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel_a0980->setArg(2, mr2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel_a0980->setArg(3, g1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel_a0980->setArg(4, m1a);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel_a0980->setArg(5, m1b);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel_a0980->setArg(6, g2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel_a0980->setArg(7, m2a);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel_a0980->setArg(8, m2b);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel_a0980->setArg(9, g3);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel_a0980->setArg(10, m3a);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel_a0980->setArg(11, m3b);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel_a0980->setArg(12, g4);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel_a0980->setArg(13, m4a);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel_a0980->setArg(14, m4b);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernel_a0980->setArg(15, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernel_a0980, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelsumBW(const DeviceInterface * dev, Stream<float> * mx123in, Stream<float> * mx2in, uint n, Stream<float4> * par, float m1_2, float m2_2, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx123in->GetEvent()));
		 err = k_kernelsumBW->setArg(0, *(*mx123in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(mx2in != mx123in)
			 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelsumBW->setArg(1, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelsumBW->setArg(2, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((par->GetEvent()));
		 err = k_kernelsumBW->setArg(3, *(*par)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelsumBW->setArg(4, m1_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelsumBW->setArg(5, m2_2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelsumBW->setArg(6, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelsumBW, cl::NullRange, cl::NDRange(mx123in->GetD1(),mx123in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelComBW(const DeviceInterface * dev, Stream<float> * mx2in, Stream<float4> * par, Stream<float2> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((mx2in->GetEvent()));
		 err = k_kernelComBW->setArg(0, *(*mx2in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((par->GetEvent()));
		 err = k_kernelComBW->setArg(1, *(*par)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelComBW->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelComBW, cl::NullRange, cl::NDRange(mx2in->GetD1(),mx2in->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

}
