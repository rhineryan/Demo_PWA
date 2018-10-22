/* Summing_cpu.h  -- source for interface functions to the kernels
 defined in Summing.cl, the corresponding binaries are in binfiles/Summing_cpu.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#include"Summing_cpu.h"
#include"KernelFile.h"
#include<vector>
#include<iostream>
#include<cassert>


namespace Summing_CPU{

	 cl::Kernel * k_int_sum_16 = 0;
	 cl::Kernel * k_int_sum_N = 0;
	 cl::Kernel * k_int_sum2d_16 = 0;
	 cl::Kernel * k_int_sum2d_N = 0;
	 cl::Kernel * k_int_sum2d_16_weighted = 0;
	 cl::Kernel * k_int_sum2d_N_weighted = 0;
	 cl::Kernel * k_float_sum_16 = 0;
	 cl::Kernel * k_float_sum_N = 0;
	 cl::Kernel * k_float_sum2d_16 = 0;
	 cl::Kernel * k_float_sum2d_N = 0;
	 cl::Kernel * k_float_sum2d_16_weighted = 0;
	 cl::Kernel * k_float_sum2d_N_weighted = 0;
	 cl::Kernel * k_double_sum_16 = 0;
	 cl::Kernel * k_double_sum_N = 0;
	 cl::Kernel * k_double_sum2d_16 = 0;
	 cl::Kernel * k_double_sum2d_N = 0;
	 cl::Kernel * k_double_sum2d_16_weighted = 0;
	 cl::Kernel * k_double_sum2d_N_weighted = 0;
	 cl::Kernel * k_double2_sum_16 = 0;
	 cl::Kernel * k_double2_sum_N = 0;
	 cl::Kernel * k_double2_sumcomponents_16 = 0;
	 cl::Kernel * k_double2_sumcomponents_N = 0;
	 cl::Kernel * k_double2_sumcomponents_weighted_16 = 0;
	 cl::Kernel * k_double2_sumcomponents_weighted_N = 0;
	 cl::Kernel * k_double2_sum2d_16 = 0;
	 cl::Kernel * k_double2_sum2d_N = 0;
	 cl::Kernel * k_double2_sum2d_16_weighted = 0;
	 cl::Kernel * k_double2_sum2d_N_weighted = 0;
	 cl::Kernel * k_float2_sum_16 = 0;
	 cl::Kernel * k_float2_sum_N = 0;
	 cl::Kernel * k_float2_sumcomponents_16 = 0;
	 cl::Kernel * k_float2_sumcomponents_N = 0;
	 cl::Kernel * k_float2_sumcomponents_weighted_16 = 0;
	 cl::Kernel * k_float2_sumcomponents_weighted_N = 0;
	 cl::Kernel * k_float2_sum2d_16 = 0;
	 cl::Kernel * k_float2_sum2d_N = 0;
	 cl::Kernel * k_float2_sum2d_16_weighted = 0;
	 cl::Kernel * k_float2_sum2d_N_weighted = 0;
	 cl::Kernel * k_float4_sum_16 = 0;
	 cl::Kernel * k_float4_sum_N = 0;
	 cl::Kernel * k_float4_sumcomponents_16 = 0;
	 cl::Kernel * k_float4_sumcomponents_N = 0;
	 cl::Kernel * k_float4_sumcomponents_weighted_16 = 0;
	 cl::Kernel * k_float4_sumcomponents_weighted_N = 0;
	 cl::Kernel * k_float4_sum2d_16 = 0;
	 cl::Kernel * k_float4_sum2d_N = 0;
	 cl::Kernel * k_float4_sum2d_16_weighted = 0;
	 cl::Kernel * k_float4_sum2d_N_weighted = 0;
	 cl::Kernel * k_float44_sum_16 = 0;
	 cl::Kernel * k_float44_sum_N = 0;
	 cl::Kernel * k_float44_sum2d_16 = 0;
	 cl::Kernel * k_float44_sum2d_N = 0;
	 cl::Kernel * k_float44_sum2d_16_weighted = 0;
	 cl::Kernel * k_float44_sum2d_N_weighted = 0;
	 cl::Kernel * k_float444_sum_16 = 0;
	 cl::Kernel * k_float444_sum_N = 0;
	 cl::Kernel * k_float444_sum2d_16 = 0;
	 cl::Kernel * k_float444_sum2d_N = 0;
	 cl::Kernel * k_float444_sum2d_16_weighted = 0;
	 cl::Kernel * k_float444_sum2d_N_weighted = 0;
	 int prepare_kernels(const DeviceInterface * dev){
		 FILE * input = fopen("binfiles/Summing_cpu.bin","rb");
		 if(!input){
			 	std::cerr << "Loading binary file binfiles/Summing_cpu.bin failed \n";
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

		 k_int_sum_16 = new cl::Kernel(*bProgram, "int_sum_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel int_sum_16\n";
			 return FAILURE;
		 }

		 k_int_sum_N = new cl::Kernel(*bProgram, "int_sum_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel int_sum_N\n";
			 return FAILURE;
		 }

		 k_int_sum2d_16 = new cl::Kernel(*bProgram, "int_sum2d_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel int_sum2d_16\n";
			 return FAILURE;
		 }

		 k_int_sum2d_N = new cl::Kernel(*bProgram, "int_sum2d_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel int_sum2d_N\n";
			 return FAILURE;
		 }

		 k_int_sum2d_16_weighted = new cl::Kernel(*bProgram, "int_sum2d_16_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel int_sum2d_16_weighted\n";
			 return FAILURE;
		 }

		 k_int_sum2d_N_weighted = new cl::Kernel(*bProgram, "int_sum2d_N_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel int_sum2d_N_weighted\n";
			 return FAILURE;
		 }

		 k_float_sum_16 = new cl::Kernel(*bProgram, "float_sum_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float_sum_16\n";
			 return FAILURE;
		 }

		 k_float_sum_N = new cl::Kernel(*bProgram, "float_sum_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float_sum_N\n";
			 return FAILURE;
		 }

		 k_float_sum2d_16 = new cl::Kernel(*bProgram, "float_sum2d_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float_sum2d_16\n";
			 return FAILURE;
		 }

		 k_float_sum2d_N = new cl::Kernel(*bProgram, "float_sum2d_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float_sum2d_N\n";
			 return FAILURE;
		 }

		 k_float_sum2d_16_weighted = new cl::Kernel(*bProgram, "float_sum2d_16_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float_sum2d_16_weighted\n";
			 return FAILURE;
		 }

		 k_float_sum2d_N_weighted = new cl::Kernel(*bProgram, "float_sum2d_N_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float_sum2d_N_weighted\n";
			 return FAILURE;
		 }

		 k_double_sum_16 = new cl::Kernel(*bProgram, "double_sum_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double_sum_16\n";
			 return FAILURE;
		 }

		 k_double_sum_N = new cl::Kernel(*bProgram, "double_sum_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double_sum_N\n";
			 return FAILURE;
		 }

		 k_double_sum2d_16 = new cl::Kernel(*bProgram, "double_sum2d_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double_sum2d_16\n";
			 return FAILURE;
		 }

		 k_double_sum2d_N = new cl::Kernel(*bProgram, "double_sum2d_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double_sum2d_N\n";
			 return FAILURE;
		 }

		 k_double_sum2d_16_weighted = new cl::Kernel(*bProgram, "double_sum2d_16_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double_sum2d_16_weighted\n";
			 return FAILURE;
		 }

		 k_double_sum2d_N_weighted = new cl::Kernel(*bProgram, "double_sum2d_N_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double_sum2d_N_weighted\n";
			 return FAILURE;
		 }

		 k_double2_sum_16 = new cl::Kernel(*bProgram, "double2_sum_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double2_sum_16\n";
			 return FAILURE;
		 }

		 k_double2_sum_N = new cl::Kernel(*bProgram, "double2_sum_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double2_sum_N\n";
			 return FAILURE;
		 }

		 k_double2_sumcomponents_16 = new cl::Kernel(*bProgram, "double2_sumcomponents_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double2_sumcomponents_16\n";
			 return FAILURE;
		 }

		 k_double2_sumcomponents_N = new cl::Kernel(*bProgram, "double2_sumcomponents_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double2_sumcomponents_N\n";
			 return FAILURE;
		 }

		 k_double2_sumcomponents_weighted_16 = new cl::Kernel(*bProgram, "double2_sumcomponents_weighted_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double2_sumcomponents_weighted_16\n";
			 return FAILURE;
		 }

		 k_double2_sumcomponents_weighted_N = new cl::Kernel(*bProgram, "double2_sumcomponents_weighted_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double2_sumcomponents_weighted_N\n";
			 return FAILURE;
		 }

		 k_double2_sum2d_16 = new cl::Kernel(*bProgram, "double2_sum2d_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double2_sum2d_16\n";
			 return FAILURE;
		 }

		 k_double2_sum2d_N = new cl::Kernel(*bProgram, "double2_sum2d_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double2_sum2d_N\n";
			 return FAILURE;
		 }

		 k_double2_sum2d_16_weighted = new cl::Kernel(*bProgram, "double2_sum2d_16_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double2_sum2d_16_weighted\n";
			 return FAILURE;
		 }

		 k_double2_sum2d_N_weighted = new cl::Kernel(*bProgram, "double2_sum2d_N_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel double2_sum2d_N_weighted\n";
			 return FAILURE;
		 }

		 k_float2_sum_16 = new cl::Kernel(*bProgram, "float2_sum_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float2_sum_16\n";
			 return FAILURE;
		 }

		 k_float2_sum_N = new cl::Kernel(*bProgram, "float2_sum_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float2_sum_N\n";
			 return FAILURE;
		 }

		 k_float2_sumcomponents_16 = new cl::Kernel(*bProgram, "float2_sumcomponents_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float2_sumcomponents_16\n";
			 return FAILURE;
		 }

		 k_float2_sumcomponents_N = new cl::Kernel(*bProgram, "float2_sumcomponents_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float2_sumcomponents_N\n";
			 return FAILURE;
		 }

		 k_float2_sumcomponents_weighted_16 = new cl::Kernel(*bProgram, "float2_sumcomponents_weighted_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float2_sumcomponents_weighted_16\n";
			 return FAILURE;
		 }

		 k_float2_sumcomponents_weighted_N = new cl::Kernel(*bProgram, "float2_sumcomponents_weighted_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float2_sumcomponents_weighted_N\n";
			 return FAILURE;
		 }

		 k_float2_sum2d_16 = new cl::Kernel(*bProgram, "float2_sum2d_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float2_sum2d_16\n";
			 return FAILURE;
		 }

		 k_float2_sum2d_N = new cl::Kernel(*bProgram, "float2_sum2d_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float2_sum2d_N\n";
			 return FAILURE;
		 }

		 k_float2_sum2d_16_weighted = new cl::Kernel(*bProgram, "float2_sum2d_16_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float2_sum2d_16_weighted\n";
			 return FAILURE;
		 }

		 k_float2_sum2d_N_weighted = new cl::Kernel(*bProgram, "float2_sum2d_N_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float2_sum2d_N_weighted\n";
			 return FAILURE;
		 }

		 k_float4_sum_16 = new cl::Kernel(*bProgram, "float4_sum_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float4_sum_16\n";
			 return FAILURE;
		 }

		 k_float4_sum_N = new cl::Kernel(*bProgram, "float4_sum_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float4_sum_N\n";
			 return FAILURE;
		 }

		 k_float4_sumcomponents_16 = new cl::Kernel(*bProgram, "float4_sumcomponents_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float4_sumcomponents_16\n";
			 return FAILURE;
		 }

		 k_float4_sumcomponents_N = new cl::Kernel(*bProgram, "float4_sumcomponents_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float4_sumcomponents_N\n";
			 return FAILURE;
		 }

		 k_float4_sumcomponents_weighted_16 = new cl::Kernel(*bProgram, "float4_sumcomponents_weighted_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float4_sumcomponents_weighted_16\n";
			 return FAILURE;
		 }

		 k_float4_sumcomponents_weighted_N = new cl::Kernel(*bProgram, "float4_sumcomponents_weighted_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float4_sumcomponents_weighted_N\n";
			 return FAILURE;
		 }

		 k_float4_sum2d_16 = new cl::Kernel(*bProgram, "float4_sum2d_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float4_sum2d_16\n";
			 return FAILURE;
		 }

		 k_float4_sum2d_N = new cl::Kernel(*bProgram, "float4_sum2d_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float4_sum2d_N\n";
			 return FAILURE;
		 }

		 k_float4_sum2d_16_weighted = new cl::Kernel(*bProgram, "float4_sum2d_16_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float4_sum2d_16_weighted\n";
			 return FAILURE;
		 }

		 k_float4_sum2d_N_weighted = new cl::Kernel(*bProgram, "float4_sum2d_N_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float4_sum2d_N_weighted\n";
			 return FAILURE;
		 }

		 k_float44_sum_16 = new cl::Kernel(*bProgram, "float44_sum_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float44_sum_16\n";
			 return FAILURE;
		 }

		 k_float44_sum_N = new cl::Kernel(*bProgram, "float44_sum_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float44_sum_N\n";
			 return FAILURE;
		 }

		 k_float44_sum2d_16 = new cl::Kernel(*bProgram, "float44_sum2d_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float44_sum2d_16\n";
			 return FAILURE;
		 }

		 k_float44_sum2d_N = new cl::Kernel(*bProgram, "float44_sum2d_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float44_sum2d_N\n";
			 return FAILURE;
		 }

		 k_float44_sum2d_16_weighted = new cl::Kernel(*bProgram, "float44_sum2d_16_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float44_sum2d_16_weighted\n";
			 return FAILURE;
		 }

		 k_float44_sum2d_N_weighted = new cl::Kernel(*bProgram, "float44_sum2d_N_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float44_sum2d_N_weighted\n";
			 return FAILURE;
		 }

		 k_float444_sum_16 = new cl::Kernel(*bProgram, "float444_sum_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float444_sum_16\n";
			 return FAILURE;
		 }

		 k_float444_sum_N = new cl::Kernel(*bProgram, "float444_sum_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float444_sum_N\n";
			 return FAILURE;
		 }

		 k_float444_sum2d_16 = new cl::Kernel(*bProgram, "float444_sum2d_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float444_sum2d_16\n";
			 return FAILURE;
		 }

		 k_float444_sum2d_N = new cl::Kernel(*bProgram, "float444_sum2d_N", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float444_sum2d_N\n";
			 return FAILURE;
		 }

		 k_float444_sum2d_16_weighted = new cl::Kernel(*bProgram, "float444_sum2d_16_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float444_sum2d_16_weighted\n";
			 return FAILURE;
		 }

		 k_float444_sum2d_N_weighted = new cl::Kernel(*bProgram, "float444_sum2d_N_weighted", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel float444_sum2d_N_weighted\n";
			 return FAILURE;
		 }

	 return 0;
	 }



	 int int_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<int> * in, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_int_sum_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum_16->setArg(1, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_int_sum_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int int_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<int> * in, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_int_sum_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum_N->setArg(1, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum_N->setArg(2, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum_N->setArg(3, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum_N->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_int_sum_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int int_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<int> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_int_sum2d_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum2d_16->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum2d_16->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_int_sum2d_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int int_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<int> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_int_sum2d_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum2d_N->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum2d_N->setArg(2, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum2d_N->setArg(3, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum2d_N->setArg(4, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum2d_N->setArg(5, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_int_sum2d_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int int_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<int> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_int_sum2d_16_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((in->GetEvent()));
		 err = k_int_sum2d_16_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum2d_16_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum2d_16_weighted->setArg(3, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_int_sum2d_16_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int int_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<int> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_int_sum2d_N_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((in->GetEvent()));
		 err = k_int_sum2d_N_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum2d_N_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum2d_N_weighted->setArg(3, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum2d_N_weighted->setArg(4, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum2d_N_weighted->setArg(5, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_int_sum2d_N_weighted->setArg(6, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_int_sum2d_N_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * in, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float_sum_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum_16->setArg(1, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float_sum_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * in, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float_sum_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum_N->setArg(1, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum_N->setArg(2, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum_N->setArg(3, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum_N->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float_sum_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float_sum2d_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum2d_16->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum2d_16->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float_sum2d_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float_sum2d_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum2d_N->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum2d_N->setArg(2, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum2d_N->setArg(3, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum2d_N->setArg(4, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum2d_N->setArg(5, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float_sum2d_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_float_sum2d_16_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((in->GetEvent()));
		 err = k_float_sum2d_16_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum2d_16_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum2d_16_weighted->setArg(3, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float_sum2d_16_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_float_sum2d_N_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((in->GetEvent()));
		 err = k_float_sum2d_N_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum2d_N_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum2d_N_weighted->setArg(3, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum2d_N_weighted->setArg(4, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum2d_N_weighted->setArg(5, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float_sum2d_N_weighted->setArg(6, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float_sum2d_N_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<double> * in, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_double_sum_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum_16->setArg(1, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double_sum_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<double> * in, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_double_sum_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum_N->setArg(1, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum_N->setArg(2, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum_N->setArg(3, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum_N->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double_sum_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<double> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_double_sum2d_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum2d_16->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum2d_16->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double_sum2d_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<double> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_double_sum2d_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum2d_N->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum2d_N->setArg(2, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum2d_N->setArg(3, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum2d_N->setArg(4, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum2d_N->setArg(5, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double_sum2d_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<double> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_double_sum2d_16_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((in->GetEvent()));
		 err = k_double_sum2d_16_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum2d_16_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum2d_16_weighted->setArg(3, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double_sum2d_16_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<double> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_double_sum2d_N_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((in->GetEvent()));
		 err = k_double_sum2d_N_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum2d_N_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum2d_N_weighted->setArg(3, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum2d_N_weighted->setArg(4, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum2d_N_weighted->setArg(5, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double_sum2d_N_weighted->setArg(6, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double_sum2d_N_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double2_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_double2_sum_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum_16->setArg(1, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double2_sum_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double2_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_double2_sum_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum_N->setArg(1, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum_N->setArg(2, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum_N->setArg(3, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum_N->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double2_sum_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double2_sumcomponents_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, Stream<double> * result_0, Stream<double> * result_1){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_double2_sumcomponents_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sumcomponents_16->setArg(1, *(*result_0)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sumcomponents_16->setArg(2, *(*result_1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double2_sumcomponents_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result_0->SetEvent(event);

		 result_1->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double2_sumcomponents_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, uint offset, uint resultoffset, uint n, Stream<double> * result_0, Stream<double> * result_1){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_double2_sumcomponents_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sumcomponents_N->setArg(1, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sumcomponents_N->setArg(2, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sumcomponents_N->setArg(3, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sumcomponents_N->setArg(4, *(*result_0)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sumcomponents_N->setArg(5, *(*result_1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double2_sumcomponents_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result_0->SetEvent(event);

		 result_1->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double2_sumcomponents_weighted_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, Stream<float> * weights, Stream<double> * result_0, Stream<double> * result_1){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_double2_sumcomponents_weighted_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((weights->GetEvent()));
		 err = k_double2_sumcomponents_weighted_16->setArg(1, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sumcomponents_weighted_16->setArg(2, *(*result_0)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sumcomponents_weighted_16->setArg(3, *(*result_1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double2_sumcomponents_weighted_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result_0->SetEvent(event);

		 result_1->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double2_sumcomponents_weighted_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, Stream<float> * weights, uint offset, uint resultoffset, uint n, Stream<double> * result_0, Stream<double> * result_1){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_double2_sumcomponents_weighted_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((weights->GetEvent()));
		 err = k_double2_sumcomponents_weighted_N->setArg(1, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sumcomponents_weighted_N->setArg(2, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sumcomponents_weighted_N->setArg(3, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sumcomponents_weighted_N->setArg(4, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sumcomponents_weighted_N->setArg(5, *(*result_0)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sumcomponents_weighted_N->setArg(6, *(*result_1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double2_sumcomponents_weighted_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result_0->SetEvent(event);

		 result_1->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double2_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_double2_sum2d_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum2d_16->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum2d_16->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double2_sum2d_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double2_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_double2_sum2d_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum2d_N->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum2d_N->setArg(2, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum2d_N->setArg(3, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum2d_N->setArg(4, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum2d_N->setArg(5, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double2_sum2d_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double2_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<double2> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_double2_sum2d_16_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((in->GetEvent()));
		 err = k_double2_sum2d_16_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum2d_16_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum2d_16_weighted->setArg(3, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double2_sum2d_16_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int double2_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<double2> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_double2_sum2d_N_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((in->GetEvent()));
		 err = k_double2_sum2d_N_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum2d_N_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum2d_N_weighted->setArg(3, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum2d_N_weighted->setArg(4, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum2d_N_weighted->setArg(5, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_double2_sum2d_N_weighted->setArg(6, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_double2_sum2d_N_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float2_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float2_sum_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum_16->setArg(1, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float2_sum_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float2_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float2_sum_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum_N->setArg(1, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum_N->setArg(2, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum_N->setArg(3, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum_N->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float2_sum_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float2_sumcomponents_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, Stream<double> * result_0, Stream<double> * result_1){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float2_sumcomponents_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sumcomponents_16->setArg(1, *(*result_0)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sumcomponents_16->setArg(2, *(*result_1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float2_sumcomponents_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result_0->SetEvent(event);

		 result_1->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float2_sumcomponents_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, uint offset, uint resultoffset, uint n, Stream<double> * result_0, Stream<double> * result_1){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float2_sumcomponents_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sumcomponents_N->setArg(1, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sumcomponents_N->setArg(2, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sumcomponents_N->setArg(3, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sumcomponents_N->setArg(4, *(*result_0)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sumcomponents_N->setArg(5, *(*result_1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float2_sumcomponents_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result_0->SetEvent(event);

		 result_1->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float2_sumcomponents_weighted_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, Stream<float> * weights, Stream<double> * result_0, Stream<double> * result_1){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float2_sumcomponents_weighted_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((weights->GetEvent()));
		 err = k_float2_sumcomponents_weighted_16->setArg(1, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sumcomponents_weighted_16->setArg(2, *(*result_0)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sumcomponents_weighted_16->setArg(3, *(*result_1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float2_sumcomponents_weighted_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result_0->SetEvent(event);

		 result_1->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float2_sumcomponents_weighted_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, Stream<float> * weights, uint offset, uint resultoffset, uint n, Stream<double> * result_0, Stream<double> * result_1){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float2_sumcomponents_weighted_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((weights->GetEvent()));
		 err = k_float2_sumcomponents_weighted_N->setArg(1, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sumcomponents_weighted_N->setArg(2, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sumcomponents_weighted_N->setArg(3, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sumcomponents_weighted_N->setArg(4, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sumcomponents_weighted_N->setArg(5, *(*result_0)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sumcomponents_weighted_N->setArg(6, *(*result_1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float2_sumcomponents_weighted_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result_0->SetEvent(event);

		 result_1->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float2_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float2_sum2d_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum2d_16->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum2d_16->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float2_sum2d_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float2_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float2_sum2d_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum2d_N->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum2d_N->setArg(2, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum2d_N->setArg(3, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum2d_N->setArg(4, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum2d_N->setArg(5, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float2_sum2d_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float2_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float2> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_float2_sum2d_16_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((in->GetEvent()));
		 err = k_float2_sum2d_16_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum2d_16_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum2d_16_weighted->setArg(3, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float2_sum2d_16_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float2_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float2> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_float2_sum2d_N_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((in->GetEvent()));
		 err = k_float2_sum2d_N_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum2d_N_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum2d_N_weighted->setArg(3, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum2d_N_weighted->setArg(4, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum2d_N_weighted->setArg(5, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float2_sum2d_N_weighted->setArg(6, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float2_sum2d_N_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float4_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float4_sum_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum_16->setArg(1, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float4_sum_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float4_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float4_sum_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum_N->setArg(1, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum_N->setArg(2, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum_N->setArg(3, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum_N->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float4_sum_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float4_sumcomponents_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, Stream<double> * result_0, Stream<double> * result_1, Stream<double> * result_2, Stream<double> * result_3){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float4_sumcomponents_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_16->setArg(1, *(*result_0)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_16->setArg(2, *(*result_1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_16->setArg(3, *(*result_2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_16->setArg(4, *(*result_3)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float4_sumcomponents_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result_0->SetEvent(event);

		 result_1->SetEvent(event);

		 result_2->SetEvent(event);

		 result_3->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float4_sumcomponents_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, uint offset, uint resultoffset, uint n, Stream<double> * result_0, Stream<double> * result_1, Stream<double> * result_2, Stream<double> * result_3){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float4_sumcomponents_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_N->setArg(1, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_N->setArg(2, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_N->setArg(3, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_N->setArg(4, *(*result_0)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_N->setArg(5, *(*result_1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_N->setArg(6, *(*result_2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_N->setArg(7, *(*result_3)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float4_sumcomponents_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result_0->SetEvent(event);

		 result_1->SetEvent(event);

		 result_2->SetEvent(event);

		 result_3->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float4_sumcomponents_weighted_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, Stream<float> * weights, Stream<double> * result_0, Stream<double> * result_1, Stream<double> * result_2, Stream<double> * result_3){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float4_sumcomponents_weighted_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((weights->GetEvent()));
		 err = k_float4_sumcomponents_weighted_16->setArg(1, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_weighted_16->setArg(2, *(*result_0)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_weighted_16->setArg(3, *(*result_1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_weighted_16->setArg(4, *(*result_2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_weighted_16->setArg(5, *(*result_3)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float4_sumcomponents_weighted_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result_0->SetEvent(event);

		 result_1->SetEvent(event);

		 result_2->SetEvent(event);

		 result_3->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float4_sumcomponents_weighted_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, Stream<float> * weights, uint offset, uint resultoffset, uint n, Stream<double> * result_0, Stream<double> * result_1, Stream<double> * result_2, Stream<double> * result_3){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float4_sumcomponents_weighted_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((weights->GetEvent()));
		 err = k_float4_sumcomponents_weighted_N->setArg(1, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_weighted_N->setArg(2, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_weighted_N->setArg(3, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_weighted_N->setArg(4, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_weighted_N->setArg(5, *(*result_0)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_weighted_N->setArg(6, *(*result_1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_weighted_N->setArg(7, *(*result_2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sumcomponents_weighted_N->setArg(8, *(*result_3)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float4_sumcomponents_weighted_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result_0->SetEvent(event);

		 result_1->SetEvent(event);

		 result_2->SetEvent(event);

		 result_3->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float4_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float4_sum2d_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum2d_16->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum2d_16->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float4_sum2d_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float4_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float4_sum2d_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum2d_N->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum2d_N->setArg(2, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum2d_N->setArg(3, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum2d_N->setArg(4, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum2d_N->setArg(5, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float4_sum2d_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float4_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float4> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_float4_sum2d_16_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in != weights)
			 evvec->push_back((in->GetEvent()));
		 err = k_float4_sum2d_16_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum2d_16_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum2d_16_weighted->setArg(3, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float4_sum2d_16_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float4_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float4> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_float4_sum2d_N_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in != weights)
			 evvec->push_back((in->GetEvent()));
		 err = k_float4_sum2d_N_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum2d_N_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum2d_N_weighted->setArg(3, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum2d_N_weighted->setArg(4, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum2d_N_weighted->setArg(5, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float4_sum2d_N_weighted->setArg(6, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float4_sum2d_N_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float44_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float44> * in, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float44_sum_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum_16->setArg(1, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float44_sum_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float44_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float44> * in, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float44_sum_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum_N->setArg(1, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum_N->setArg(2, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum_N->setArg(3, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum_N->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float44_sum_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float44_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float44> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float44_sum2d_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum2d_16->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum2d_16->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float44_sum2d_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float44_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float44> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float44_sum2d_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum2d_N->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum2d_N->setArg(2, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum2d_N->setArg(3, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum2d_N->setArg(4, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum2d_N->setArg(5, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float44_sum2d_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float44_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float44> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_float44_sum2d_16_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((in->GetEvent()));
		 err = k_float44_sum2d_16_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum2d_16_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum2d_16_weighted->setArg(3, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float44_sum2d_16_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float44_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float44> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_float44_sum2d_N_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((in->GetEvent()));
		 err = k_float44_sum2d_N_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum2d_N_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum2d_N_weighted->setArg(3, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum2d_N_weighted->setArg(4, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum2d_N_weighted->setArg(5, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float44_sum2d_N_weighted->setArg(6, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float44_sum2d_N_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float444_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float444> * in, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float444_sum_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum_16->setArg(1, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float444_sum_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float444_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float444> * in, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float444_sum_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum_N->setArg(1, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum_N->setArg(2, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum_N->setArg(3, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum_N->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float444_sum_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float444_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float444> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float444_sum2d_16->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum2d_16->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum2d_16->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float444_sum2d_16, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float444_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float444> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in->GetEvent()));
		 err = k_float444_sum2d_N->setArg(0, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum2d_N->setArg(1, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum2d_N->setArg(2, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum2d_N->setArg(3, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum2d_N->setArg(4, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum2d_N->setArg(5, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float444_sum2d_N, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float444_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float444> * in, uint d1, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_float444_sum2d_16_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((in->GetEvent()));
		 err = k_float444_sum2d_16_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum2d_16_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum2d_16_weighted->setArg(3, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float444_sum2d_16_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int float444_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float444> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((weights->GetEvent()));
		 err = k_float444_sum2d_N_weighted->setArg(0, *(*weights)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((in->GetEvent()));
		 err = k_float444_sum2d_N_weighted->setArg(1, *(*in)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum2d_N_weighted->setArg(2, d1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum2d_N_weighted->setArg(3, offset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum2d_N_weighted->setArg(4, resultoffset);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum2d_N_weighted->setArg(5, n);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_float444_sum2d_N_weighted->setArg(6, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_float444_sum2d_N_weighted, cl::NullRange, range, cl::NullRange, evvec, &event );
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
