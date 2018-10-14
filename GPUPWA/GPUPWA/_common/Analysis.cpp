/* Analysis.h  -- source for interface functions to the kernels
 defined in /scratchfs/bes/xiongxa/Demo_PWA_GPUPWA/GPUPWA/GPUPWA/Analysis.cl, the corresponding binaries are in binfiles/Analysis.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#include"Analysis.h"
#include"KernelFile.h"
#include<vector>
#include<iostream>
#include<cassert>


namespace Analysis_GPU{

	 cl::Kernel * k_pwamult4 = 0;
	 cl::Kernel * k_collectpropagators4 = 0;
	 cl::Kernel * k_freepwamult4 = 0;
	 cl::Kernel * k_freepwamult4tcs = 0;
	 cl::Kernel * k_freepwamult4tcsweighted = 0;
	 cl::Kernel * k_pwagradmult4all = 0;
	 cl::Kernel * k_kernelhessian = 0;
	 cl::Kernel * k_kernelhessian4all = 0;
	 cl::Kernel * k_pwamultdcsonly4 = 0;
	 cl::Kernel * k_pwamultdcsonly4weighted = 0;
	 cl::Kernel * k_pwamultdcsonlyonewave4 = 0;
	 cl::Kernel * k_pwamultdcsonlytwowaves4 = 0;
	 cl::Kernel * k_kernelmult_c_c_f = 0;
	 cl::Kernel * k_kernelmult_c_cbar_f = 0;
	 cl::Kernel * k_kernelmult_2c_cbar_f = 0;
	 cl::Kernel * k_kernelmult_c2_f = 0;
	 cl::Kernel * k_kernelsum16float2double = 0;
	 cl::Kernel * k_kernelsum16float2double2d = 0;
	 cl::Kernel * k_kernelweightedsumfloat2double = 0;
	 cl::Kernel * k_kernelsumfloat2double = 0;
	 cl::Kernel * k_kernelsumdouble2double = 0;
	 cl::Kernel * k_kernel4orbitaltensor = 0;
	 cl::Kernel * k_kernel4orbitaltensorconst = 0;
	 cl::Kernel * k_kernel3orbitaltensor = 0;
	 cl::Kernel * k_kernel3orbitaltensorconst = 0;
	 cl::Kernel * k_kernelfilllookup = 0;
	 int prepare_kernels(const DeviceInterface * dev){
		 FILE * input = fopen("binfiles/Analysis.bin","rb");
		 if(!input){
			 	std::cerr << "Loading binary file binfiles/Analysis.bin failed \n";
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

		 k_pwamult4 = new cl::Kernel(*bProgram, "pwamult4", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel pwamult4\n";
			 return FAILURE;
		 }

		 k_collectpropagators4 = new cl::Kernel(*bProgram, "collectpropagators4", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel collectpropagators4\n";
			 return FAILURE;
		 }

		 k_freepwamult4 = new cl::Kernel(*bProgram, "freepwamult4", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel freepwamult4\n";
			 return FAILURE;
		 }

		 k_freepwamult4tcs = new cl::Kernel(*bProgram, "freepwamult4tcs", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel freepwamult4tcs\n";
			 return FAILURE;
		 }

		 k_freepwamult4tcsweighted = new cl::Kernel(*bProgram, "freepwamult4tcsweighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel freepwamult4tcsweighted\n";
			 return FAILURE;
		 }

		 k_pwagradmult4all = new cl::Kernel(*bProgram, "pwagradmult4all", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel pwagradmult4all\n";
			 return FAILURE;
		 }

		 k_kernelhessian = new cl::Kernel(*bProgram, "kernelhessian", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelhessian\n";
			 return FAILURE;
		 }

		 k_kernelhessian4all = new cl::Kernel(*bProgram, "kernelhessian4all", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelhessian4all\n";
			 return FAILURE;
		 }

		 k_pwamultdcsonly4 = new cl::Kernel(*bProgram, "pwamultdcsonly4", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel pwamultdcsonly4\n";
			 return FAILURE;
		 }

		 k_pwamultdcsonly4weighted = new cl::Kernel(*bProgram, "pwamultdcsonly4weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel pwamultdcsonly4weighted\n";
			 return FAILURE;
		 }

		 k_pwamultdcsonlyonewave4 = new cl::Kernel(*bProgram, "pwamultdcsonlyonewave4", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel pwamultdcsonlyonewave4\n";
			 return FAILURE;
		 }

		 k_pwamultdcsonlytwowaves4 = new cl::Kernel(*bProgram, "pwamultdcsonlytwowaves4", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel pwamultdcsonlytwowaves4\n";
			 return FAILURE;
		 }

		 k_kernelmult_c_c_f = new cl::Kernel(*bProgram, "kernelmult_c_c_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmult_c_c_f\n";
			 return FAILURE;
		 }

		 k_kernelmult_c_cbar_f = new cl::Kernel(*bProgram, "kernelmult_c_cbar_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmult_c_cbar_f\n";
			 return FAILURE;
		 }

		 k_kernelmult_2c_cbar_f = new cl::Kernel(*bProgram, "kernelmult_2c_cbar_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmult_2c_cbar_f\n";
			 return FAILURE;
		 }

		 k_kernelmult_c2_f = new cl::Kernel(*bProgram, "kernelmult_c2_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmult_c2_f\n";
			 return FAILURE;
		 }

		 k_kernelsum16float2double = new cl::Kernel(*bProgram, "kernelsum16float2double", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelsum16float2double\n";
			 return FAILURE;
		 }

		 k_kernelsum16float2double2d = new cl::Kernel(*bProgram, "kernelsum16float2double2d", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelsum16float2double2d\n";
			 return FAILURE;
		 }

		 k_kernelweightedsumfloat2double = new cl::Kernel(*bProgram, "kernelweightedsumfloat2double", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelweightedsumfloat2double\n";
			 return FAILURE;
		 }

		 k_kernelsumfloat2double = new cl::Kernel(*bProgram, "kernelsumfloat2double", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelsumfloat2double\n";
			 return FAILURE;
		 }

		 k_kernelsumdouble2double = new cl::Kernel(*bProgram, "kernelsumdouble2double", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelsumdouble2double\n";
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

		 k_kernelfilllookup = new cl::Kernel(*bProgram, "kernelfilllookup", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelfilllookup\n";
			 return FAILURE;
		 }

	 return 0;
	 }



	 int pwamult4(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weight, Stream<float4> * lookupx, Stream<float4> * lookupy, Stream<float2> * parameters, uint n, float bgpar, float tcs, Stream<float4> * dcs, Stream<float4> * logdcs){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weight->GetEvent()));
		 err = k_pwamult4->setArg(0, *(*weight)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(lookupx != weight)
			 evvec->push_back((lookupx->GetEvent()));
		 err = k_pwamult4->setArg(1, *(*lookupx)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(lookupy != weight)
			if(lookupy != lookupx)
				 evvec->push_back((lookupy->GetEvent()));
		 err = k_pwamult4->setArg(2, *(*lookupy)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((parameters->GetEvent()));
		 err = k_pwamult4->setArg(3, *(*parameters)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamult4->setArg(4, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamult4->setArg(5, bgpar);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamult4->setArg(6, tcs);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamult4->setArg(7, *(*dcs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamult4->setArg(8, *(*logdcs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_pwamult4, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 dcs->SetEvent(event);

		 logdcs->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int collectpropagators4(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * propagator, uint nwave, uint waveindex, Stream<float4> * prop){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((propagator->GetEvent()));
		 err = k_collectpropagators4->setArg(0, *(*propagator)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_collectpropagators4->setArg(1, nwave);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_collectpropagators4->setArg(2, waveindex);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_collectpropagators4->setArg(3, *(*prop)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_collectpropagators4, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 prop->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int freepwamult4(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weight, Stream<float4> * lookup, Stream<float4> * propagator, Stream<float2> * parameters, uint n, float bgpar, float tcs, Stream<float4> * dcs, Stream<float4> * logdcs){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weight->GetEvent()));
		 err = k_freepwamult4->setArg(0, *(*weight)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(lookup != weight)
			 evvec->push_back((lookup->GetEvent()));
		 err = k_freepwamult4->setArg(1, *(*lookup)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator != weight)
			if(propagator != lookup)
				 evvec->push_back((propagator->GetEvent()));
		 err = k_freepwamult4->setArg(2, *(*propagator)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((parameters->GetEvent()));
		 err = k_freepwamult4->setArg(3, *(*parameters)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_freepwamult4->setArg(4, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_freepwamult4->setArg(5, bgpar);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_freepwamult4->setArg(6, tcs);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_freepwamult4->setArg(7, *(*dcs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_freepwamult4->setArg(8, *(*logdcs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_freepwamult4, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 dcs->SetEvent(event);

		 logdcs->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int freepwamult4tcs(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * lookup, Stream<float4> * propagator, Stream<float2> * parameters, uint n, Stream<float4> * dcs){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((lookup->GetEvent()));
		 err = k_freepwamult4tcs->setArg(0, *(*lookup)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator != lookup)
			 evvec->push_back((propagator->GetEvent()));
		 err = k_freepwamult4tcs->setArg(1, *(*propagator)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((parameters->GetEvent()));
		 err = k_freepwamult4tcs->setArg(2, *(*parameters)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_freepwamult4tcs->setArg(3, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_freepwamult4tcs->setArg(4, *(*dcs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_freepwamult4tcs, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 dcs->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int freepwamult4tcsweighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float4> * lookup, Stream<float4> * propagator, Stream<float2> * parameters, uint n, Stream<float4> * dcs){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_freepwamult4tcsweighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(lookup != weights)
			 evvec->push_back((lookup->GetEvent()));
		 err = k_freepwamult4tcsweighted->setArg(1, *(*lookup)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator != weights)
			if(propagator != lookup)
				 evvec->push_back((propagator->GetEvent()));
		 err = k_freepwamult4tcsweighted->setArg(2, *(*propagator)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((parameters->GetEvent()));
		 err = k_freepwamult4tcsweighted->setArg(3, *(*parameters)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_freepwamult4tcsweighted->setArg(4, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_freepwamult4tcsweighted->setArg(5, *(*dcs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_freepwamult4tcsweighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 dcs->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int pwagradmult4all(const cl::NDRange & range, const DeviceInterface * dev, Stream<int> * input, Stream<float4> * weightin, Stream<float4> * dcsin, Stream<float4> * lookupx, Stream<float4> * lookupy, Stream<float2> * parameters, uint nwaves, uint ngrads, Stream<float> * gradpar, float bgpar, float tcs, Stream<float> * dtcsin, Stream<float4> * grad, Stream<float4> * innergrad){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_pwagradmult4all->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((weightin->GetEvent()));
		 err = k_pwagradmult4all->setArg(1, *(*weightin)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(dcsin != weightin)
			 evvec->push_back((dcsin->GetEvent()));
		 err = k_pwagradmult4all->setArg(2, *(*dcsin)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(lookupx != weightin)
			if(lookupx != dcsin)
				 evvec->push_back((lookupx->GetEvent()));
		 err = k_pwagradmult4all->setArg(3, *(*lookupx)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(lookupy != weightin)
			if(lookupy != dcsin)
				if(lookupy != lookupx)
					 evvec->push_back((lookupy->GetEvent()));
		 err = k_pwagradmult4all->setArg(4, *(*lookupy)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((parameters->GetEvent()));
		 err = k_pwagradmult4all->setArg(5, *(*parameters)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwagradmult4all->setArg(6, nwaves);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwagradmult4all->setArg(7, ngrads);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((gradpar->GetEvent()));
		 err = k_pwagradmult4all->setArg(8, *(*gradpar)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwagradmult4all->setArg(9, bgpar);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwagradmult4all->setArg(10, tcs);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(dtcsin != gradpar)
			 evvec->push_back((dtcsin->GetEvent()));
		 err = k_pwagradmult4all->setArg(11, *(*dtcsin)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwagradmult4all->setArg(12, *(*grad)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwagradmult4all->setArg(13, *(*innergrad)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_pwagradmult4all, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 grad->SetEvent(event);

		 innergrad->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelhessian(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * gradient1, Stream<float> * gradient2, Stream<float> * dcs, Stream<float> * weight, float bgpar, float tcs, Stream<float> * hessian){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((gradient1->GetEvent()));
		 err = k_kernelhessian->setArg(0, *(*gradient1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(gradient2 != gradient1)
			 evvec->push_back((gradient2->GetEvent()));
		 err = k_kernelhessian->setArg(1, *(*gradient2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(dcs != gradient1)
			if(dcs != gradient2)
				 evvec->push_back((dcs->GetEvent()));
		 err = k_kernelhessian->setArg(2, *(*dcs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(weight != gradient1)
			if(weight != gradient2)
				if(weight != dcs)
					 evvec->push_back((weight->GetEvent()));
		 err = k_kernelhessian->setArg(3, *(*weight)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelhessian->setArg(4, bgpar);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelhessian->setArg(5, tcs);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelhessian->setArg(6, *(*hessian)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelhessian, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 hessian->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelhessian4all(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * gradients, Stream<float4> * dcs, Stream<float4> * weight, uint ngrad, float bgpar, float tcs, Stream<float4> * hessian){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((gradients->GetEvent()));
		 err = k_kernelhessian4all->setArg(0, *(*gradients)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(dcs != gradients)
			 evvec->push_back((dcs->GetEvent()));
		 err = k_kernelhessian4all->setArg(1, *(*dcs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(weight != gradients)
			if(weight != dcs)
				 evvec->push_back((weight->GetEvent()));
		 err = k_kernelhessian4all->setArg(2, *(*weight)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelhessian4all->setArg(3, ngrad);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelhessian4all->setArg(4, bgpar);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelhessian4all->setArg(5, tcs);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelhessian4all->setArg(6, *(*hessian)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelhessian4all, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 hessian->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int pwamultdcsonly4(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * lookupx, Stream<float4> * lookupy, Stream<float2> * parameters, uint n, float bgpar, Stream<float4> * dcs){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((lookupx->GetEvent()));
		 err = k_pwamultdcsonly4->setArg(0, *(*lookupx)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(lookupy != lookupx)
			 evvec->push_back((lookupy->GetEvent()));
		 err = k_pwamultdcsonly4->setArg(1, *(*lookupy)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((parameters->GetEvent()));
		 err = k_pwamultdcsonly4->setArg(2, *(*parameters)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamultdcsonly4->setArg(3, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamultdcsonly4->setArg(4, bgpar);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamultdcsonly4->setArg(5, *(*dcs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_pwamultdcsonly4, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 dcs->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int pwamultdcsonly4weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * lookupx, Stream<float4> * lookupy, Stream<float4> * weights, Stream<float2> * parameters, uint n, float bgpar, Stream<float4> * dcs){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((lookupx->GetEvent()));
		 err = k_pwamultdcsonly4weighted->setArg(0, *(*lookupx)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(lookupy != lookupx)
			 evvec->push_back((lookupy->GetEvent()));
		 err = k_pwamultdcsonly4weighted->setArg(1, *(*lookupy)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(weights != lookupx)
			if(weights != lookupy)
				 evvec->push_back((weights->GetEvent()));
		 err = k_pwamultdcsonly4weighted->setArg(2, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((parameters->GetEvent()));
		 err = k_pwamultdcsonly4weighted->setArg(3, *(*parameters)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamultdcsonly4weighted->setArg(4, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamultdcsonly4weighted->setArg(5, bgpar);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamultdcsonly4weighted->setArg(6, *(*dcs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_pwamultdcsonly4weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 dcs->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int pwamultdcsonlyonewave4(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * lookupx, Stream<float2> * parameters, uint n, uint wavenumber, Stream<float4> * dcs){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((lookupx->GetEvent()));
		 err = k_pwamultdcsonlyonewave4->setArg(0, *(*lookupx)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((parameters->GetEvent()));
		 err = k_pwamultdcsonlyonewave4->setArg(1, *(*parameters)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamultdcsonlyonewave4->setArg(2, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamultdcsonlyonewave4->setArg(3, wavenumber);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamultdcsonlyonewave4->setArg(4, *(*dcs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_pwamultdcsonlyonewave4, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 dcs->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int pwamultdcsonlytwowaves4(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * lookupx, Stream<float4> * lookupy, Stream<float2> * parameters, uint n, uint wave1, uint wave2, Stream<float4> * dcs){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((lookupx->GetEvent()));
		 err = k_pwamultdcsonlytwowaves4->setArg(0, *(*lookupx)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(lookupy != lookupx)
			 evvec->push_back((lookupy->GetEvent()));
		 err = k_pwamultdcsonlytwowaves4->setArg(1, *(*lookupy)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((parameters->GetEvent()));
		 err = k_pwamultdcsonlytwowaves4->setArg(2, *(*parameters)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamultdcsonlytwowaves4->setArg(3, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamultdcsonlytwowaves4->setArg(4, wave1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamultdcsonlytwowaves4->setArg(5, wave2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_pwamultdcsonlytwowaves4->setArg(6, *(*dcs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_pwamultdcsonlytwowaves4, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 dcs->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmult_c_c_f(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * c1, Stream<float2> * c2, Stream<float> * f, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((c1->GetEvent()));
		 err = k_kernelmult_c_c_f->setArg(0, *(*c1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(c2 != c1)
			 evvec->push_back((c2->GetEvent()));
		 err = k_kernelmult_c_c_f->setArg(1, *(*c2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((f->GetEvent()));
		 err = k_kernelmult_c_c_f->setArg(2, *(*f)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmult_c_c_f->setArg(3, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmult_c_c_f, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmult_c_cbar_f(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * c1, Stream<float2> * c2, Stream<float> * f, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((c1->GetEvent()));
		 err = k_kernelmult_c_cbar_f->setArg(0, *(*c1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(c2 != c1)
			 evvec->push_back((c2->GetEvent()));
		 err = k_kernelmult_c_cbar_f->setArg(1, *(*c2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((f->GetEvent()));
		 err = k_kernelmult_c_cbar_f->setArg(2, *(*f)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmult_c_cbar_f->setArg(3, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmult_c_cbar_f, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmult_2c_cbar_f(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * c1, Stream<float2> * c2, Stream<float> * f, double2 pprodd, Stream<float> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((c1->GetEvent()));
		 err = k_kernelmult_2c_cbar_f->setArg(0, *(*c1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(c2 != c1)
			 evvec->push_back((c2->GetEvent()));
		 err = k_kernelmult_2c_cbar_f->setArg(1, *(*c2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((f->GetEvent()));
		 err = k_kernelmult_2c_cbar_f->setArg(2, *(*f)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmult_2c_cbar_f->setArg(3, pprodd);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmult_2c_cbar_f->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmult_2c_cbar_f, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmult_c2_f(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * c1, Stream<float> * f, Stream<float> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((c1->GetEvent()));
		 err = k_kernelmult_c2_f->setArg(0, *(*c1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((f->GetEvent()));
		 err = k_kernelmult_c2_f->setArg(1, *(*f)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmult_c2_f->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmult_c2_f, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelsum16float2double(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * input, Stream<double2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelsum16float2double->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelsum16float2double->setArg(1, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelsum16float2double, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelsum16float2double2d(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * input, uint n, Stream<double2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelsum16float2double2d->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelsum16float2double2d->setArg(1, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelsum16float2double2d->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelsum16float2double2d, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelweightedsumfloat2double(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * nin, Stream<float> * weights, Stream<float2> * input, Stream<double2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((nin->GetEvent()));
		 err = k_kernelweightedsumfloat2double->setArg(0, *(*nin)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(weights != nin)
			 evvec->push_back((weights->GetEvent()));
		 err = k_kernelweightedsumfloat2double->setArg(1, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelweightedsumfloat2double->setArg(2, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelweightedsumfloat2double->setArg(3, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelweightedsumfloat2double, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelsumfloat2double(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * nin, Stream<float2> * input, Stream<double2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((nin->GetEvent()));
		 err = k_kernelsumfloat2double->setArg(0, *(*nin)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelsumfloat2double->setArg(1, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelsumfloat2double->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelsumfloat2double, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelsumdouble2double(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * nin, Stream<double2> * input, Stream<double2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((nin->GetEvent()));
		 err = k_kernelsumdouble2double->setArg(0, *(*nin)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelsumdouble2double->setArg(1, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelsumdouble2double->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelsumdouble2double, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernel4orbitaltensor(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * rtin, uint i, uint j, Stream<float44> * delpin, Stream<float44> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((rtin->GetEvent()));
		 err = k_kernel4orbitaltensor->setArg(0, *(*rtin)());
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

		 evvec->push_back((delpin->GetEvent()));
		 err = k_kernel4orbitaltensor->setArg(3, *(*delpin)());
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

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernel4orbitaltensor, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernel4orbitaltensorconst(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * rtin, uint i, uint j, float44 delp, Stream<float44> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((rtin->GetEvent()));
		 err = k_kernel4orbitaltensorconst->setArg(0, *(*rtin)());
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

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernel4orbitaltensorconst, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernel3orbitaltensor(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * rtin, Stream<float4> * pain, Stream<float444> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((rtin->GetEvent()));
		 err = k_kernel3orbitaltensor->setArg(0, *(*rtin)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(pain != rtin)
			 evvec->push_back((pain->GetEvent()));
		 err = k_kernel3orbitaltensor->setArg(1, *(*pain)());
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

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernel3orbitaltensor, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernel3orbitaltensorconst(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * rtin, float4 pa, Stream<float444> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((rtin->GetEvent()));
		 err = k_kernel3orbitaltensorconst->setArg(0, *(*rtin)());
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

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernel3orbitaltensorconst, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelfilllookup(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * input, uint offset, uint ijindex, uint lookupsize, Stream<float4> * cx, Stream<float4> * cy){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelfilllookup->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfilllookup->setArg(1, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfilllookup->setArg(2, ijindex);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfilllookup->setArg(3, lookupsize);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfilllookup->setArg(4, *(*cx)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelfilllookup->setArg(5, *(*cy)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelfilllookup, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 cx->SetEvent(event);

		 cy->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

}
