/* Tensors.h  -- source for interface functions to the kernels
 defined in /scratchfs/bes/xiongxa/Demo_PWA_GPUPWA/GPUPWA/GPUPWA/Tensors.cl, the corresponding binaries are in binfiles/Tensors.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#include"Tensors.h"
#include"KernelFile.h"
#include<vector>
#include<iostream>
#include<cassert>


namespace Tensors_GPU{

	 cl::Kernel * k_kerneltensorcopy_2 = 0;
	 cl::Kernel * k_kerneltensorassign_c = 0;
	 cl::Kernel * k_kerneltensorassign_d = 0;
	 cl::Kernel * k_kerneltensorassign_e = 0;
	 cl::Kernel * k_kerneltensorassign_f = 0;
	 cl::Kernel * k_kerneltensorassign_0 = 0;
	 cl::Kernel * k_kerneltensorassign_1 = 0;
	 cl::Kernel * k_kerneltensorassign_2 = 0;
	 cl::Kernel * k_kerneltensorassign_3 = 0;
	 cl::Kernel * k_kernelgetfloat_1 = 0;
	 cl::Kernel * k_kernelgetfloat_2 = 0;
	 cl::Kernel * k_kerneltensormake_2 = 0;
	 cl::Kernel * k_kerneltensormake_2_1 = 0;
	 cl::Kernel * k_kerneltensormake_3 = 0;
	 cl::Kernel * k_kernelgetvector_2 = 0;
	 cl::Kernel * k_kernelgetvector_3 = 0;
	 cl::Kernel * k_kernelgetfloat44_3 = 0;
	 cl::Kernel * k_kerneltensoradd_0_0 = 0;
	 cl::Kernel * k_kerneltensoradd_0_16 = 0;
	 cl::Kernel * k_kerneltensoradd_4_16 = 0;
	 cl::Kernel * k_kerneltensoradd_0_4 = 0;
	 cl::Kernel * k_kerneltensoradd_0_f = 0;
	 cl::Kernel * k_kerneltensoradd_1_1 = 0;
	 cl::Kernel * k_kerneltensoradd_1_f = 0;
	 cl::Kernel * k_kerneltensoradd_2_2 = 0;
	 cl::Kernel * k_kerneltensoradd_2_f44 = 0;
	 cl::Kernel * k_kerneltensoradd_3_3 = 0;
	 cl::Kernel * k_kerneltensoradd_3_f = 0;
	 cl::Kernel * k_kerneltensorsub_0_0 = 0;
	 cl::Kernel * k_kerneltensorsub_0_f = 0;
	 cl::Kernel * k_kerneltensorsub_f_0 = 0;
	 cl::Kernel * k_kerneltensorsub_1_1 = 0;
	 cl::Kernel * k_kerneltensorsub_1_f = 0;
	 cl::Kernel * k_kerneltensorsub_f_1 = 0;
	 cl::Kernel * k_kerneltensorsub_2_2 = 0;
	 cl::Kernel * k_kerneltensorsub_2_f = 0;
	 cl::Kernel * k_kerneltensorsub_f_2 = 0;
	 cl::Kernel * k_kerneltensorsub_3_3 = 0;
	 cl::Kernel * k_kerneltensorsub_3_f = 0;
	 cl::Kernel * k_kerneltensorsub_f_3 = 0;
	 cl::Kernel * k_kerneltensormult_0_0 = 0;
	 cl::Kernel * k_kerneltensormult_0_f = 0;
	 cl::Kernel * k_kerneltensormult_0_1 = 0;
	 cl::Kernel * k_kerneltensormult_0_f4 = 0;
	 cl::Kernel * k_kerneltensormult_f_1 = 0;
	 cl::Kernel * k_kerneltensormult_0_2 = 0;
	 cl::Kernel * k_kerneltensormult_0_f44 = 0;
	 cl::Kernel * k_kerneltensormult_0i_2 = 0;
	 cl::Kernel * k_kerneltensormult_0i_f44 = 0;
	 cl::Kernel * k_kerneltensormult_f_2 = 0;
	 cl::Kernel * k_kerneltensormult_fi_2 = 0;
	 cl::Kernel * k_kerneltensormult_0_3 = 0;
	 cl::Kernel * k_kerneltensormult_f_3 = 0;
	 cl::Kernel * k_kerneltensormult_0_f444 = 0;
	 cl::Kernel * k_kerneltensordiv_0_0 = 0;
	 cl::Kernel * k_kerneltensordiv_f_0 = 0;
	 cl::Kernel * k_kerneltensordiv_1_0 = 0;
	 cl::Kernel * k_kerneltensordiv_f4_0 = 0;
	 cl::Kernel * k_kerneltensordiv_2_0 = 0;
	 cl::Kernel * k_kerneltensordiv_2_f = 0;
	 cl::Kernel * k_kerneltensordiv_f44_0 = 0;
	 cl::Kernel * k_kerneltensordiv_3_0 = 0;
	 cl::Kernel * k_kerneltensordiv_3_f = 0;
	 cl::Kernel * k_kerneltensordiv_f444_0 = 0;
	 cl::Kernel * k_kerneltensorouter_1_1 = 0;
	 cl::Kernel * k_kerneltensorouter_1_f4 = 0;
	 cl::Kernel * k_kerneltensorouter_f4_1 = 0;
	 cl::Kernel * k_kerneltensorouter_2_1 = 0;
	 cl::Kernel * k_kerneltensorouter_2_f4 = 0;
	 cl::Kernel * k_kerneltensorouter_f44_1 = 0;
	 cl::Kernel * k_kerneltensorouter_1_2 = 0;
	 cl::Kernel * k_kerneltensorouter_f4_2 = 0;
	 cl::Kernel * k_kerneltensorouter_1_f44 = 0;
	 cl::Kernel * k_kerneltensorneg_0 = 0;
	 cl::Kernel * k_kerneltensorneg_1 = 0;
	 cl::Kernel * k_kerneltensorneg_2 = 0;
	 cl::Kernel * k_kerneltensorneg_3 = 0;
	 cl::Kernel * k_kerneltensorsqrt_0 = 0;
	 cl::Kernel * k_kerneltensorsin_0 = 0;
	 cl::Kernel * k_kerneltensorcos_0 = 0;
	 cl::Kernel * k_kerneltensortan_0 = 0;
	 cl::Kernel * k_kerneltensorexp_0 = 0;
	 cl::Kernel * k_kerneltensortrans_2 = 0;
	 cl::Kernel * k_kerneltensortrans_3_213 = 0;
	 cl::Kernel * k_kerneltensortrans_3_132 = 0;
	 cl::Kernel * k_kernelmoveindex_1 = 0;
	 cl::Kernel * k_kernelmovelastindex_2 = 0;
	 cl::Kernel * k_kernelmovefirstindex_2 = 0;
	 cl::Kernel * k_kernelmoveindices_2 = 0;
	 cl::Kernel * k_kernelmoveindices_3 = 0;
	 cl::Kernel * k_kernelmovelastindex_3 = 0;
	 cl::Kernel * k_kernelmovemiddleindex_3 = 0;
	 cl::Kernel * k_kernelmovefirstindex_3 = 0;
	 cl::Kernel * k_kernellorentzboost = 0;
	 cl::Kernel * k_kernellorentzrotation = 0;
	 cl::Kernel * k_kerneltensorphi_1 = 0;
	 cl::Kernel * k_kerneltensorcostheta_1 = 0;
	 cl::Kernel * k_kerneltensorcontract_1_1 = 0;
	 cl::Kernel * k_kerneltensorcontract_1_f = 0;
	 cl::Kernel * k_kerneltensorcontract_2_1 = 0;
	 cl::Kernel * k_kerneltensorcontract_f44_1 = 0;
	 cl::Kernel * k_kerneltensorcontract_2_f4 = 0;
	 cl::Kernel * k_kerneltensorcontract_2_2 = 0;
	 cl::Kernel * k_kerneltensorcontract_2_f44 = 0;
	 cl::Kernel * k_kerneltensorcontract2_2_2 = 0;
	 cl::Kernel * k_kerneltensorcontract2_2_f44 = 0;
	 cl::Kernel * k_kerneltensorcontract2_f44_2 = 0;
	 cl::Kernel * k_kerneltensorcontract_3_3 = 0;
	 cl::Kernel * k_kerneltensorcontract_3_f444 = 0;
	 cl::Kernel * k_kerneltensorcontract_3_1 = 0;
	 cl::Kernel * k_kerneltensorcontract_f444_1 = 0;
	 cl::Kernel * k_kerneltensorcontract_3_f4 = 0;
	 cl::Kernel * k_kerneltensorcontract_3_2 = 0;
	 cl::Kernel * k_kerneltensorcontract_3_f44 = 0;
	 cl::Kernel * k_kerneltensorcontract_2_3_sign = 0;
	 cl::Kernel * k_kerneltensorcontract_2_3 = 0;
	 cl::Kernel * k_kerneltensorcontract_2_f444 = 0;
	 cl::Kernel * k_kerneltensorcontract_f44_3 = 0;
	 cl::Kernel * k_kerneltensorcontract_f444_2 = 0;
	 cl::Kernel * k_kerneltensorcontract2_3_3 = 0;
	 int prepare_kernels(const DeviceInterface * dev){
		 FILE * input = fopen("binfiles/Tensors.bin","rb");
		 if(!input){
			 	std::cerr << "Loading binary file binfiles/Tensors.bin failed \n";
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

		 k_kerneltensorcopy_2 = new cl::Kernel(*bProgram, "kerneltensorcopy_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcopy_2\n";
			 return FAILURE;
		 }

		 k_kerneltensorassign_c = new cl::Kernel(*bProgram, "kerneltensorassign_c", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorassign_c\n";
			 return FAILURE;
		 }

		 k_kerneltensorassign_d = new cl::Kernel(*bProgram, "kerneltensorassign_d", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorassign_d\n";
			 return FAILURE;
		 }

		 k_kerneltensorassign_e = new cl::Kernel(*bProgram, "kerneltensorassign_e", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorassign_e\n";
			 return FAILURE;
		 }

		 k_kerneltensorassign_f = new cl::Kernel(*bProgram, "kerneltensorassign_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorassign_f\n";
			 return FAILURE;
		 }

		 k_kerneltensorassign_0 = new cl::Kernel(*bProgram, "kerneltensorassign_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorassign_0\n";
			 return FAILURE;
		 }

		 k_kerneltensorassign_1 = new cl::Kernel(*bProgram, "kerneltensorassign_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorassign_1\n";
			 return FAILURE;
		 }

		 k_kerneltensorassign_2 = new cl::Kernel(*bProgram, "kerneltensorassign_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorassign_2\n";
			 return FAILURE;
		 }

		 k_kerneltensorassign_3 = new cl::Kernel(*bProgram, "kerneltensorassign_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorassign_3\n";
			 return FAILURE;
		 }

		 k_kernelgetfloat_1 = new cl::Kernel(*bProgram, "kernelgetfloat_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelgetfloat_1\n";
			 return FAILURE;
		 }

		 k_kernelgetfloat_2 = new cl::Kernel(*bProgram, "kernelgetfloat_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelgetfloat_2\n";
			 return FAILURE;
		 }

		 k_kerneltensormake_2 = new cl::Kernel(*bProgram, "kerneltensormake_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormake_2\n";
			 return FAILURE;
		 }

		 k_kerneltensormake_2_1 = new cl::Kernel(*bProgram, "kerneltensormake_2_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormake_2_1\n";
			 return FAILURE;
		 }

		 k_kerneltensormake_3 = new cl::Kernel(*bProgram, "kerneltensormake_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormake_3\n";
			 return FAILURE;
		 }

		 k_kernelgetvector_2 = new cl::Kernel(*bProgram, "kernelgetvector_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelgetvector_2\n";
			 return FAILURE;
		 }

		 k_kernelgetvector_3 = new cl::Kernel(*bProgram, "kernelgetvector_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelgetvector_3\n";
			 return FAILURE;
		 }

		 k_kernelgetfloat44_3 = new cl::Kernel(*bProgram, "kernelgetfloat44_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelgetfloat44_3\n";
			 return FAILURE;
		 }

		 k_kerneltensoradd_0_0 = new cl::Kernel(*bProgram, "kerneltensoradd_0_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensoradd_0_0\n";
			 return FAILURE;
		 }

		 k_kerneltensoradd_0_16 = new cl::Kernel(*bProgram, "kerneltensoradd_0_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensoradd_0_16\n";
			 return FAILURE;
		 }

		 k_kerneltensoradd_4_16 = new cl::Kernel(*bProgram, "kerneltensoradd_4_16", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensoradd_4_16\n";
			 return FAILURE;
		 }

		 k_kerneltensoradd_0_4 = new cl::Kernel(*bProgram, "kerneltensoradd_0_4", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensoradd_0_4\n";
			 return FAILURE;
		 }

		 k_kerneltensoradd_0_f = new cl::Kernel(*bProgram, "kerneltensoradd_0_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensoradd_0_f\n";
			 return FAILURE;
		 }

		 k_kerneltensoradd_1_1 = new cl::Kernel(*bProgram, "kerneltensoradd_1_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensoradd_1_1\n";
			 return FAILURE;
		 }

		 k_kerneltensoradd_1_f = new cl::Kernel(*bProgram, "kerneltensoradd_1_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensoradd_1_f\n";
			 return FAILURE;
		 }

		 k_kerneltensoradd_2_2 = new cl::Kernel(*bProgram, "kerneltensoradd_2_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensoradd_2_2\n";
			 return FAILURE;
		 }

		 k_kerneltensoradd_2_f44 = new cl::Kernel(*bProgram, "kerneltensoradd_2_f44", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensoradd_2_f44\n";
			 return FAILURE;
		 }

		 k_kerneltensoradd_3_3 = new cl::Kernel(*bProgram, "kerneltensoradd_3_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensoradd_3_3\n";
			 return FAILURE;
		 }

		 k_kerneltensoradd_3_f = new cl::Kernel(*bProgram, "kerneltensoradd_3_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensoradd_3_f\n";
			 return FAILURE;
		 }

		 k_kerneltensorsub_0_0 = new cl::Kernel(*bProgram, "kerneltensorsub_0_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorsub_0_0\n";
			 return FAILURE;
		 }

		 k_kerneltensorsub_0_f = new cl::Kernel(*bProgram, "kerneltensorsub_0_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorsub_0_f\n";
			 return FAILURE;
		 }

		 k_kerneltensorsub_f_0 = new cl::Kernel(*bProgram, "kerneltensorsub_f_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorsub_f_0\n";
			 return FAILURE;
		 }

		 k_kerneltensorsub_1_1 = new cl::Kernel(*bProgram, "kerneltensorsub_1_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorsub_1_1\n";
			 return FAILURE;
		 }

		 k_kerneltensorsub_1_f = new cl::Kernel(*bProgram, "kerneltensorsub_1_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorsub_1_f\n";
			 return FAILURE;
		 }

		 k_kerneltensorsub_f_1 = new cl::Kernel(*bProgram, "kerneltensorsub_f_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorsub_f_1\n";
			 return FAILURE;
		 }

		 k_kerneltensorsub_2_2 = new cl::Kernel(*bProgram, "kerneltensorsub_2_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorsub_2_2\n";
			 return FAILURE;
		 }

		 k_kerneltensorsub_2_f = new cl::Kernel(*bProgram, "kerneltensorsub_2_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorsub_2_f\n";
			 return FAILURE;
		 }

		 k_kerneltensorsub_f_2 = new cl::Kernel(*bProgram, "kerneltensorsub_f_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorsub_f_2\n";
			 return FAILURE;
		 }

		 k_kerneltensorsub_3_3 = new cl::Kernel(*bProgram, "kerneltensorsub_3_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorsub_3_3\n";
			 return FAILURE;
		 }

		 k_kerneltensorsub_3_f = new cl::Kernel(*bProgram, "kerneltensorsub_3_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorsub_3_f\n";
			 return FAILURE;
		 }

		 k_kerneltensorsub_f_3 = new cl::Kernel(*bProgram, "kerneltensorsub_f_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorsub_f_3\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_0_0 = new cl::Kernel(*bProgram, "kerneltensormult_0_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_0_0\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_0_f = new cl::Kernel(*bProgram, "kerneltensormult_0_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_0_f\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_0_1 = new cl::Kernel(*bProgram, "kerneltensormult_0_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_0_1\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_0_f4 = new cl::Kernel(*bProgram, "kerneltensormult_0_f4", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_0_f4\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_f_1 = new cl::Kernel(*bProgram, "kerneltensormult_f_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_f_1\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_0_2 = new cl::Kernel(*bProgram, "kerneltensormult_0_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_0_2\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_0_f44 = new cl::Kernel(*bProgram, "kerneltensormult_0_f44", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_0_f44\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_0i_2 = new cl::Kernel(*bProgram, "kerneltensormult_0i_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_0i_2\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_0i_f44 = new cl::Kernel(*bProgram, "kerneltensormult_0i_f44", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_0i_f44\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_f_2 = new cl::Kernel(*bProgram, "kerneltensormult_f_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_f_2\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_fi_2 = new cl::Kernel(*bProgram, "kerneltensormult_fi_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_fi_2\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_0_3 = new cl::Kernel(*bProgram, "kerneltensormult_0_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_0_3\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_f_3 = new cl::Kernel(*bProgram, "kerneltensormult_f_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_f_3\n";
			 return FAILURE;
		 }

		 k_kerneltensormult_0_f444 = new cl::Kernel(*bProgram, "kerneltensormult_0_f444", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensormult_0_f444\n";
			 return FAILURE;
		 }

		 k_kerneltensordiv_0_0 = new cl::Kernel(*bProgram, "kerneltensordiv_0_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensordiv_0_0\n";
			 return FAILURE;
		 }

		 k_kerneltensordiv_f_0 = new cl::Kernel(*bProgram, "kerneltensordiv_f_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensordiv_f_0\n";
			 return FAILURE;
		 }

		 k_kerneltensordiv_1_0 = new cl::Kernel(*bProgram, "kerneltensordiv_1_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensordiv_1_0\n";
			 return FAILURE;
		 }

		 k_kerneltensordiv_f4_0 = new cl::Kernel(*bProgram, "kerneltensordiv_f4_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensordiv_f4_0\n";
			 return FAILURE;
		 }

		 k_kerneltensordiv_2_0 = new cl::Kernel(*bProgram, "kerneltensordiv_2_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensordiv_2_0\n";
			 return FAILURE;
		 }

		 k_kerneltensordiv_2_f = new cl::Kernel(*bProgram, "kerneltensordiv_2_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensordiv_2_f\n";
			 return FAILURE;
		 }

		 k_kerneltensordiv_f44_0 = new cl::Kernel(*bProgram, "kerneltensordiv_f44_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensordiv_f44_0\n";
			 return FAILURE;
		 }

		 k_kerneltensordiv_3_0 = new cl::Kernel(*bProgram, "kerneltensordiv_3_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensordiv_3_0\n";
			 return FAILURE;
		 }

		 k_kerneltensordiv_3_f = new cl::Kernel(*bProgram, "kerneltensordiv_3_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensordiv_3_f\n";
			 return FAILURE;
		 }

		 k_kerneltensordiv_f444_0 = new cl::Kernel(*bProgram, "kerneltensordiv_f444_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensordiv_f444_0\n";
			 return FAILURE;
		 }

		 k_kerneltensorouter_1_1 = new cl::Kernel(*bProgram, "kerneltensorouter_1_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorouter_1_1\n";
			 return FAILURE;
		 }

		 k_kerneltensorouter_1_f4 = new cl::Kernel(*bProgram, "kerneltensorouter_1_f4", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorouter_1_f4\n";
			 return FAILURE;
		 }

		 k_kerneltensorouter_f4_1 = new cl::Kernel(*bProgram, "kerneltensorouter_f4_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorouter_f4_1\n";
			 return FAILURE;
		 }

		 k_kerneltensorouter_2_1 = new cl::Kernel(*bProgram, "kerneltensorouter_2_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorouter_2_1\n";
			 return FAILURE;
		 }

		 k_kerneltensorouter_2_f4 = new cl::Kernel(*bProgram, "kerneltensorouter_2_f4", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorouter_2_f4\n";
			 return FAILURE;
		 }

		 k_kerneltensorouter_f44_1 = new cl::Kernel(*bProgram, "kerneltensorouter_f44_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorouter_f44_1\n";
			 return FAILURE;
		 }

		 k_kerneltensorouter_1_2 = new cl::Kernel(*bProgram, "kerneltensorouter_1_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorouter_1_2\n";
			 return FAILURE;
		 }

		 k_kerneltensorouter_f4_2 = new cl::Kernel(*bProgram, "kerneltensorouter_f4_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorouter_f4_2\n";
			 return FAILURE;
		 }

		 k_kerneltensorouter_1_f44 = new cl::Kernel(*bProgram, "kerneltensorouter_1_f44", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorouter_1_f44\n";
			 return FAILURE;
		 }

		 k_kerneltensorneg_0 = new cl::Kernel(*bProgram, "kerneltensorneg_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorneg_0\n";
			 return FAILURE;
		 }

		 k_kerneltensorneg_1 = new cl::Kernel(*bProgram, "kerneltensorneg_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorneg_1\n";
			 return FAILURE;
		 }

		 k_kerneltensorneg_2 = new cl::Kernel(*bProgram, "kerneltensorneg_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorneg_2\n";
			 return FAILURE;
		 }

		 k_kerneltensorneg_3 = new cl::Kernel(*bProgram, "kerneltensorneg_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorneg_3\n";
			 return FAILURE;
		 }

		 k_kerneltensorsqrt_0 = new cl::Kernel(*bProgram, "kerneltensorsqrt_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorsqrt_0\n";
			 return FAILURE;
		 }

		 k_kerneltensorsin_0 = new cl::Kernel(*bProgram, "kerneltensorsin_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorsin_0\n";
			 return FAILURE;
		 }

		 k_kerneltensorcos_0 = new cl::Kernel(*bProgram, "kerneltensorcos_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcos_0\n";
			 return FAILURE;
		 }

		 k_kerneltensortan_0 = new cl::Kernel(*bProgram, "kerneltensortan_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensortan_0\n";
			 return FAILURE;
		 }

		 k_kerneltensorexp_0 = new cl::Kernel(*bProgram, "kerneltensorexp_0", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorexp_0\n";
			 return FAILURE;
		 }

		 k_kerneltensortrans_2 = new cl::Kernel(*bProgram, "kerneltensortrans_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensortrans_2\n";
			 return FAILURE;
		 }

		 k_kerneltensortrans_3_213 = new cl::Kernel(*bProgram, "kerneltensortrans_3_213", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensortrans_3_213\n";
			 return FAILURE;
		 }

		 k_kerneltensortrans_3_132 = new cl::Kernel(*bProgram, "kerneltensortrans_3_132", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensortrans_3_132\n";
			 return FAILURE;
		 }

		 k_kernelmoveindex_1 = new cl::Kernel(*bProgram, "kernelmoveindex_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmoveindex_1\n";
			 return FAILURE;
		 }

		 k_kernelmovelastindex_2 = new cl::Kernel(*bProgram, "kernelmovelastindex_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmovelastindex_2\n";
			 return FAILURE;
		 }

		 k_kernelmovefirstindex_2 = new cl::Kernel(*bProgram, "kernelmovefirstindex_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmovefirstindex_2\n";
			 return FAILURE;
		 }

		 k_kernelmoveindices_2 = new cl::Kernel(*bProgram, "kernelmoveindices_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmoveindices_2\n";
			 return FAILURE;
		 }

		 k_kernelmoveindices_3 = new cl::Kernel(*bProgram, "kernelmoveindices_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmoveindices_3\n";
			 return FAILURE;
		 }

		 k_kernelmovelastindex_3 = new cl::Kernel(*bProgram, "kernelmovelastindex_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmovelastindex_3\n";
			 return FAILURE;
		 }

		 k_kernelmovemiddleindex_3 = new cl::Kernel(*bProgram, "kernelmovemiddleindex_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmovemiddleindex_3\n";
			 return FAILURE;
		 }

		 k_kernelmovefirstindex_3 = new cl::Kernel(*bProgram, "kernelmovefirstindex_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelmovefirstindex_3\n";
			 return FAILURE;
		 }

		 k_kernellorentzboost = new cl::Kernel(*bProgram, "kernellorentzboost", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernellorentzboost\n";
			 return FAILURE;
		 }

		 k_kernellorentzrotation = new cl::Kernel(*bProgram, "kernellorentzrotation", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernellorentzrotation\n";
			 return FAILURE;
		 }

		 k_kerneltensorphi_1 = new cl::Kernel(*bProgram, "kerneltensorphi_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorphi_1\n";
			 return FAILURE;
		 }

		 k_kerneltensorcostheta_1 = new cl::Kernel(*bProgram, "kerneltensorcostheta_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcostheta_1\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_1_1 = new cl::Kernel(*bProgram, "kerneltensorcontract_1_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_1_1\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_1_f = new cl::Kernel(*bProgram, "kerneltensorcontract_1_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_1_f\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_2_1 = new cl::Kernel(*bProgram, "kerneltensorcontract_2_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_2_1\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_f44_1 = new cl::Kernel(*bProgram, "kerneltensorcontract_f44_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_f44_1\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_2_f4 = new cl::Kernel(*bProgram, "kerneltensorcontract_2_f4", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_2_f4\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_2_2 = new cl::Kernel(*bProgram, "kerneltensorcontract_2_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_2_2\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_2_f44 = new cl::Kernel(*bProgram, "kerneltensorcontract_2_f44", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_2_f44\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract2_2_2 = new cl::Kernel(*bProgram, "kerneltensorcontract2_2_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract2_2_2\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract2_2_f44 = new cl::Kernel(*bProgram, "kerneltensorcontract2_2_f44", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract2_2_f44\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract2_f44_2 = new cl::Kernel(*bProgram, "kerneltensorcontract2_f44_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract2_f44_2\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_3_3 = new cl::Kernel(*bProgram, "kerneltensorcontract_3_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_3_3\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_3_f444 = new cl::Kernel(*bProgram, "kerneltensorcontract_3_f444", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_3_f444\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_3_1 = new cl::Kernel(*bProgram, "kerneltensorcontract_3_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_3_1\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_f444_1 = new cl::Kernel(*bProgram, "kerneltensorcontract_f444_1", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_f444_1\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_3_f4 = new cl::Kernel(*bProgram, "kerneltensorcontract_3_f4", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_3_f4\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_3_2 = new cl::Kernel(*bProgram, "kerneltensorcontract_3_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_3_2\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_3_f44 = new cl::Kernel(*bProgram, "kerneltensorcontract_3_f44", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_3_f44\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_2_3_sign = new cl::Kernel(*bProgram, "kerneltensorcontract_2_3_sign", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_2_3_sign\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_2_3 = new cl::Kernel(*bProgram, "kerneltensorcontract_2_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_2_3\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_2_f444 = new cl::Kernel(*bProgram, "kerneltensorcontract_2_f444", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_2_f444\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_f44_3 = new cl::Kernel(*bProgram, "kerneltensorcontract_f44_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_f44_3\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract_f444_2 = new cl::Kernel(*bProgram, "kerneltensorcontract_f444_2", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract_f444_2\n";
			 return FAILURE;
		 }

		 k_kerneltensorcontract2_3_3 = new cl::Kernel(*bProgram, "kerneltensorcontract2_3_3", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kerneltensorcontract2_3_3\n";
			 return FAILURE;
		 }

	 return 0;
	 }



	 int kerneltensorcopy_2(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensorcopy_2->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcopy_2->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcopy_2, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorassign_c(const DeviceInterface * dev, Stream<float44> * p1, Stream<float44> * p2, Stream<float44> * p3, Stream<float44> * p4, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((p1->GetEvent()));
		 err = k_kerneltensorassign_c->setArg(0, *(*p1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p2 != p1)
			 evvec->push_back((p2->GetEvent()));
		 err = k_kerneltensorassign_c->setArg(1, *(*p2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p3 != p1)
			if(p3 != p2)
				 evvec->push_back((p3->GetEvent()));
		 err = k_kerneltensorassign_c->setArg(2, *(*p3)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p4 != p1)
			if(p4 != p2)
				if(p4 != p3)
					 evvec->push_back((p4->GetEvent()));
		 err = k_kerneltensorassign_c->setArg(3, *(*p4)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorassign_c->setArg(4, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorassign_c, cl::NullRange, cl::NDRange(p1->GetD1(),p1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorassign_d(const DeviceInterface * dev, Stream<float44> * p1, Stream<float44> * p2, Stream<float44> * p3, Stream<float44> * p4, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((p1->GetEvent()));
		 err = k_kerneltensorassign_d->setArg(0, *(*p1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p2 != p1)
			 evvec->push_back((p2->GetEvent()));
		 err = k_kerneltensorassign_d->setArg(1, *(*p2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p3 != p1)
			if(p3 != p2)
				 evvec->push_back((p3->GetEvent()));
		 err = k_kerneltensorassign_d->setArg(2, *(*p3)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p4 != p1)
			if(p4 != p2)
				if(p4 != p3)
					 evvec->push_back((p4->GetEvent()));
		 err = k_kerneltensorassign_d->setArg(3, *(*p4)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorassign_d->setArg(4, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorassign_d, cl::NullRange, cl::NDRange(p1->GetD1(),p1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorassign_e(const DeviceInterface * dev, Stream<float44> * p1, Stream<float44> * p2, Stream<float44> * p3, Stream<float44> * p4, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((p1->GetEvent()));
		 err = k_kerneltensorassign_e->setArg(0, *(*p1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p2 != p1)
			 evvec->push_back((p2->GetEvent()));
		 err = k_kerneltensorassign_e->setArg(1, *(*p2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p3 != p1)
			if(p3 != p2)
				 evvec->push_back((p3->GetEvent()));
		 err = k_kerneltensorassign_e->setArg(2, *(*p3)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p4 != p1)
			if(p4 != p2)
				if(p4 != p3)
					 evvec->push_back((p4->GetEvent()));
		 err = k_kerneltensorassign_e->setArg(3, *(*p4)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorassign_e->setArg(4, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorassign_e, cl::NullRange, cl::NDRange(p1->GetD1(),p1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorassign_f(const DeviceInterface * dev, Stream<float44> * p1, Stream<float44> * p2, Stream<float44> * p3, Stream<float44> * p4, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((p1->GetEvent()));
		 err = k_kerneltensorassign_f->setArg(0, *(*p1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p2 != p1)
			 evvec->push_back((p2->GetEvent()));
		 err = k_kerneltensorassign_f->setArg(1, *(*p2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p3 != p1)
			if(p3 != p2)
				 evvec->push_back((p3->GetEvent()));
		 err = k_kerneltensorassign_f->setArg(2, *(*p3)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p4 != p1)
			if(p4 != p2)
				if(p4 != p3)
					 evvec->push_back((p4->GetEvent()));
		 err = k_kerneltensorassign_f->setArg(3, *(*p4)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorassign_f->setArg(4, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorassign_f, cl::NullRange, cl::NDRange(p1->GetD1(),p1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorassign_0(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensorassign_0->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorassign_0->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorassign_0, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorassign_1(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensorassign_1->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorassign_1->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorassign_1, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorassign_2(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensorassign_2->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorassign_2->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorassign_2, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorassign_3(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensorassign_3->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorassign_3->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorassign_3, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelgetfloat_1(const DeviceInterface * dev, Stream<float4> * input, float i, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelgetfloat_1->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgetfloat_1->setArg(1, i);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgetfloat_1->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelgetfloat_1, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelgetfloat_2(const DeviceInterface * dev, Stream<float44> * input, uint i, uint j, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelgetfloat_2->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgetfloat_2->setArg(1, i);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgetfloat_2->setArg(2, j);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgetfloat_2->setArg(3, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelgetfloat_2, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormake_2(const DeviceInterface * dev, Stream<float> * in1, Stream<float> * in2, Stream<float> * in3, Stream<float> * in4, Stream<float> * in5, Stream<float> * in6, Stream<float> * in7, Stream<float> * in8, Stream<float> * in9, Stream<float> * in10, Stream<float> * in11, Stream<float> * in12, Stream<float> * in13, Stream<float> * in14, Stream<float> * in15, Stream<float> * in16, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in1->GetEvent()));
		 err = k_kerneltensormake_2->setArg(0, *(*in1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in2 != in1)
			 evvec->push_back((in2->GetEvent()));
		 err = k_kerneltensormake_2->setArg(1, *(*in2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in3 != in1)
			if(in3 != in2)
				 evvec->push_back((in3->GetEvent()));
		 err = k_kerneltensormake_2->setArg(2, *(*in3)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in4 != in1)
			if(in4 != in2)
				if(in4 != in3)
					 evvec->push_back((in4->GetEvent()));
		 err = k_kerneltensormake_2->setArg(3, *(*in4)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in5 != in1)
			if(in5 != in2)
				if(in5 != in3)
					if(in5 != in4)
						 evvec->push_back((in5->GetEvent()));
		 err = k_kerneltensormake_2->setArg(4, *(*in5)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in6 != in1)
			if(in6 != in2)
				if(in6 != in3)
					if(in6 != in4)
						if(in6 != in5)
							 evvec->push_back((in6->GetEvent()));
		 err = k_kerneltensormake_2->setArg(5, *(*in6)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in7 != in1)
			if(in7 != in2)
				if(in7 != in3)
					if(in7 != in4)
						if(in7 != in5)
							if(in7 != in6)
								 evvec->push_back((in7->GetEvent()));
		 err = k_kerneltensormake_2->setArg(6, *(*in7)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in8 != in1)
			if(in8 != in2)
				if(in8 != in3)
					if(in8 != in4)
						if(in8 != in5)
							if(in8 != in6)
								if(in8 != in7)
									 evvec->push_back((in8->GetEvent()));
		 err = k_kerneltensormake_2->setArg(7, *(*in8)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in9 != in1)
			if(in9 != in2)
				if(in9 != in3)
					if(in9 != in4)
						if(in9 != in5)
							if(in9 != in6)
								if(in9 != in7)
									if(in9 != in8)
										 evvec->push_back((in9->GetEvent()));
		 err = k_kerneltensormake_2->setArg(8, *(*in9)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in10 != in1)
			if(in10 != in2)
				if(in10 != in3)
					if(in10 != in4)
						if(in10 != in5)
							if(in10 != in6)
								if(in10 != in7)
									if(in10 != in8)
										if(in10 != in9)
											 evvec->push_back((in10->GetEvent()));
		 err = k_kerneltensormake_2->setArg(9, *(*in10)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in11 != in1)
			if(in11 != in2)
				if(in11 != in3)
					if(in11 != in4)
						if(in11 != in5)
							if(in11 != in6)
								if(in11 != in7)
									if(in11 != in8)
										if(in11 != in9)
											if(in11 != in10)
												 evvec->push_back((in11->GetEvent()));
		 err = k_kerneltensormake_2->setArg(10, *(*in11)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in12 != in1)
			if(in12 != in2)
				if(in12 != in3)
					if(in12 != in4)
						if(in12 != in5)
							if(in12 != in6)
								if(in12 != in7)
									if(in12 != in8)
										if(in12 != in9)
											if(in12 != in10)
												if(in12 != in11)
													 evvec->push_back((in12->GetEvent()));
		 err = k_kerneltensormake_2->setArg(11, *(*in12)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in13 != in1)
			if(in13 != in2)
				if(in13 != in3)
					if(in13 != in4)
						if(in13 != in5)
							if(in13 != in6)
								if(in13 != in7)
									if(in13 != in8)
										if(in13 != in9)
											if(in13 != in10)
												if(in13 != in11)
													if(in13 != in12)
														 evvec->push_back((in13->GetEvent()));
		 err = k_kerneltensormake_2->setArg(12, *(*in13)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in14 != in1)
			if(in14 != in2)
				if(in14 != in3)
					if(in14 != in4)
						if(in14 != in5)
							if(in14 != in6)
								if(in14 != in7)
									if(in14 != in8)
										if(in14 != in9)
											if(in14 != in10)
												if(in14 != in11)
													if(in14 != in12)
														if(in14 != in13)
															 evvec->push_back((in14->GetEvent()));
		 err = k_kerneltensormake_2->setArg(13, *(*in14)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in15 != in1)
			if(in15 != in2)
				if(in15 != in3)
					if(in15 != in4)
						if(in15 != in5)
							if(in15 != in6)
								if(in15 != in7)
									if(in15 != in8)
										if(in15 != in9)
											if(in15 != in10)
												if(in15 != in11)
													if(in15 != in12)
														if(in15 != in13)
															if(in15 != in14)
																 evvec->push_back((in15->GetEvent()));
		 err = k_kerneltensormake_2->setArg(14, *(*in15)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in16 != in1)
			if(in16 != in2)
				if(in16 != in3)
					if(in16 != in4)
						if(in16 != in5)
							if(in16 != in6)
								if(in16 != in7)
									if(in16 != in8)
										if(in16 != in9)
											if(in16 != in10)
												if(in16 != in11)
													if(in16 != in12)
														if(in16 != in13)
															if(in16 != in14)
																if(in16 != in15)
																	 evvec->push_back((in16->GetEvent()));
		 err = k_kerneltensormake_2->setArg(15, *(*in16)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormake_2->setArg(16, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormake_2, cl::NullRange, cl::NDRange(in1->GetD1(),in1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormake_2_1(const DeviceInterface * dev, Stream<float4> * in1, Stream<float4> * in2, Stream<float4> * in3, Stream<float4> * in4, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in1->GetEvent()));
		 err = k_kerneltensormake_2_1->setArg(0, *(*in1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in2 != in1)
			 evvec->push_back((in2->GetEvent()));
		 err = k_kerneltensormake_2_1->setArg(1, *(*in2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in3 != in1)
			if(in3 != in2)
				 evvec->push_back((in3->GetEvent()));
		 err = k_kerneltensormake_2_1->setArg(2, *(*in3)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in4 != in1)
			if(in4 != in2)
				if(in4 != in3)
					 evvec->push_back((in4->GetEvent()));
		 err = k_kerneltensormake_2_1->setArg(3, *(*in4)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormake_2_1->setArg(4, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormake_2_1, cl::NullRange, cl::NDRange(in1->GetD1(),in1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormake_3(const DeviceInterface * dev, Stream<float4> * in1, Stream<float4> * in2, Stream<float4> * in3, Stream<float4> * in4, Stream<float4> * in5, Stream<float4> * in6, Stream<float4> * in7, Stream<float4> * in8, Stream<float4> * in9, Stream<float4> * in10, Stream<float4> * in11, Stream<float4> * in12, Stream<float4> * in13, Stream<float4> * in14, Stream<float4> * in15, Stream<float4> * in16, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((in1->GetEvent()));
		 err = k_kerneltensormake_3->setArg(0, *(*in1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in2 != in1)
			 evvec->push_back((in2->GetEvent()));
		 err = k_kerneltensormake_3->setArg(1, *(*in2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in3 != in1)
			if(in3 != in2)
				 evvec->push_back((in3->GetEvent()));
		 err = k_kerneltensormake_3->setArg(2, *(*in3)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in4 != in1)
			if(in4 != in2)
				if(in4 != in3)
					 evvec->push_back((in4->GetEvent()));
		 err = k_kerneltensormake_3->setArg(3, *(*in4)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in5 != in1)
			if(in5 != in2)
				if(in5 != in3)
					if(in5 != in4)
						 evvec->push_back((in5->GetEvent()));
		 err = k_kerneltensormake_3->setArg(4, *(*in5)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in6 != in1)
			if(in6 != in2)
				if(in6 != in3)
					if(in6 != in4)
						if(in6 != in5)
							 evvec->push_back((in6->GetEvent()));
		 err = k_kerneltensormake_3->setArg(5, *(*in6)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in7 != in1)
			if(in7 != in2)
				if(in7 != in3)
					if(in7 != in4)
						if(in7 != in5)
							if(in7 != in6)
								 evvec->push_back((in7->GetEvent()));
		 err = k_kerneltensormake_3->setArg(6, *(*in7)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in8 != in1)
			if(in8 != in2)
				if(in8 != in3)
					if(in8 != in4)
						if(in8 != in5)
							if(in8 != in6)
								if(in8 != in7)
									 evvec->push_back((in8->GetEvent()));
		 err = k_kerneltensormake_3->setArg(7, *(*in8)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in9 != in1)
			if(in9 != in2)
				if(in9 != in3)
					if(in9 != in4)
						if(in9 != in5)
							if(in9 != in6)
								if(in9 != in7)
									if(in9 != in8)
										 evvec->push_back((in9->GetEvent()));
		 err = k_kerneltensormake_3->setArg(8, *(*in9)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in10 != in1)
			if(in10 != in2)
				if(in10 != in3)
					if(in10 != in4)
						if(in10 != in5)
							if(in10 != in6)
								if(in10 != in7)
									if(in10 != in8)
										if(in10 != in9)
											 evvec->push_back((in10->GetEvent()));
		 err = k_kerneltensormake_3->setArg(9, *(*in10)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in11 != in1)
			if(in11 != in2)
				if(in11 != in3)
					if(in11 != in4)
						if(in11 != in5)
							if(in11 != in6)
								if(in11 != in7)
									if(in11 != in8)
										if(in11 != in9)
											if(in11 != in10)
												 evvec->push_back((in11->GetEvent()));
		 err = k_kerneltensormake_3->setArg(10, *(*in11)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in12 != in1)
			if(in12 != in2)
				if(in12 != in3)
					if(in12 != in4)
						if(in12 != in5)
							if(in12 != in6)
								if(in12 != in7)
									if(in12 != in8)
										if(in12 != in9)
											if(in12 != in10)
												if(in12 != in11)
													 evvec->push_back((in12->GetEvent()));
		 err = k_kerneltensormake_3->setArg(11, *(*in12)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in13 != in1)
			if(in13 != in2)
				if(in13 != in3)
					if(in13 != in4)
						if(in13 != in5)
							if(in13 != in6)
								if(in13 != in7)
									if(in13 != in8)
										if(in13 != in9)
											if(in13 != in10)
												if(in13 != in11)
													if(in13 != in12)
														 evvec->push_back((in13->GetEvent()));
		 err = k_kerneltensormake_3->setArg(12, *(*in13)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in14 != in1)
			if(in14 != in2)
				if(in14 != in3)
					if(in14 != in4)
						if(in14 != in5)
							if(in14 != in6)
								if(in14 != in7)
									if(in14 != in8)
										if(in14 != in9)
											if(in14 != in10)
												if(in14 != in11)
													if(in14 != in12)
														if(in14 != in13)
															 evvec->push_back((in14->GetEvent()));
		 err = k_kerneltensormake_3->setArg(13, *(*in14)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in15 != in1)
			if(in15 != in2)
				if(in15 != in3)
					if(in15 != in4)
						if(in15 != in5)
							if(in15 != in6)
								if(in15 != in7)
									if(in15 != in8)
										if(in15 != in9)
											if(in15 != in10)
												if(in15 != in11)
													if(in15 != in12)
														if(in15 != in13)
															if(in15 != in14)
																 evvec->push_back((in15->GetEvent()));
		 err = k_kerneltensormake_3->setArg(14, *(*in15)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(in16 != in1)
			if(in16 != in2)
				if(in16 != in3)
					if(in16 != in4)
						if(in16 != in5)
							if(in16 != in6)
								if(in16 != in7)
									if(in16 != in8)
										if(in16 != in9)
											if(in16 != in10)
												if(in16 != in11)
													if(in16 != in12)
														if(in16 != in13)
															if(in16 != in14)
																if(in16 != in15)
																	 evvec->push_back((in16->GetEvent()));
		 err = k_kerneltensormake_3->setArg(15, *(*in16)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormake_3->setArg(16, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormake_3, cl::NullRange, cl::NDRange(in1->GetD1(),in1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelgetvector_2(const DeviceInterface * dev, Stream<float44> * input, uint i, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelgetvector_2->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgetvector_2->setArg(1, i);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgetvector_2->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelgetvector_2, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelgetvector_3(const DeviceInterface * dev, Stream<float444> * input, uint i, uint j, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelgetvector_3->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgetvector_3->setArg(1, i);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgetvector_3->setArg(2, j);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgetvector_3->setArg(3, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelgetvector_3, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelgetfloat44_3(const DeviceInterface * dev, Stream<float444> * input, uint i, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelgetfloat44_3->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgetfloat44_3->setArg(1, i);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelgetfloat44_3->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelgetfloat44_3, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensoradd_0_0(const DeviceInterface * dev, Stream<float> * input1, Stream<float> * input2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensoradd_0_0->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != input1)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensoradd_0_0->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensoradd_0_0->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensoradd_0_0, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensoradd_0_16(const DeviceInterface * dev, Stream<float> * p1, Stream<float> * p2, Stream<float> * p3, Stream<float> * p4, Stream<float> * p5, Stream<float> * p6, Stream<float> * p7, Stream<float> * p8, Stream<float> * p9, Stream<float> * p10, Stream<float> * p11, Stream<float> * p12, Stream<float> * p13, Stream<float> * p14, Stream<float> * p15, Stream<float> * p16, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((p1->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(0, *(*p1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p2 != p1)
			 evvec->push_back((p2->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(1, *(*p2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p3 != p1)
			if(p3 != p2)
				 evvec->push_back((p3->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(2, *(*p3)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p4 != p1)
			if(p4 != p2)
				if(p4 != p3)
					 evvec->push_back((p4->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(3, *(*p4)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p5 != p1)
			if(p5 != p2)
				if(p5 != p3)
					if(p5 != p4)
						 evvec->push_back((p5->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(4, *(*p5)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p6 != p1)
			if(p6 != p2)
				if(p6 != p3)
					if(p6 != p4)
						if(p6 != p5)
							 evvec->push_back((p6->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(5, *(*p6)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p7 != p1)
			if(p7 != p2)
				if(p7 != p3)
					if(p7 != p4)
						if(p7 != p5)
							if(p7 != p6)
								 evvec->push_back((p7->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(6, *(*p7)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p8 != p1)
			if(p8 != p2)
				if(p8 != p3)
					if(p8 != p4)
						if(p8 != p5)
							if(p8 != p6)
								if(p8 != p7)
									 evvec->push_back((p8->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(7, *(*p8)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p9 != p1)
			if(p9 != p2)
				if(p9 != p3)
					if(p9 != p4)
						if(p9 != p5)
							if(p9 != p6)
								if(p9 != p7)
									if(p9 != p8)
										 evvec->push_back((p9->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(8, *(*p9)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p10 != p1)
			if(p10 != p2)
				if(p10 != p3)
					if(p10 != p4)
						if(p10 != p5)
							if(p10 != p6)
								if(p10 != p7)
									if(p10 != p8)
										if(p10 != p9)
											 evvec->push_back((p10->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(9, *(*p10)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p11 != p1)
			if(p11 != p2)
				if(p11 != p3)
					if(p11 != p4)
						if(p11 != p5)
							if(p11 != p6)
								if(p11 != p7)
									if(p11 != p8)
										if(p11 != p9)
											if(p11 != p10)
												 evvec->push_back((p11->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(10, *(*p11)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p12 != p1)
			if(p12 != p2)
				if(p12 != p3)
					if(p12 != p4)
						if(p12 != p5)
							if(p12 != p6)
								if(p12 != p7)
									if(p12 != p8)
										if(p12 != p9)
											if(p12 != p10)
												if(p12 != p11)
													 evvec->push_back((p12->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(11, *(*p12)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p13 != p1)
			if(p13 != p2)
				if(p13 != p3)
					if(p13 != p4)
						if(p13 != p5)
							if(p13 != p6)
								if(p13 != p7)
									if(p13 != p8)
										if(p13 != p9)
											if(p13 != p10)
												if(p13 != p11)
													if(p13 != p12)
														 evvec->push_back((p13->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(12, *(*p13)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p14 != p1)
			if(p14 != p2)
				if(p14 != p3)
					if(p14 != p4)
						if(p14 != p5)
							if(p14 != p6)
								if(p14 != p7)
									if(p14 != p8)
										if(p14 != p9)
											if(p14 != p10)
												if(p14 != p11)
													if(p14 != p12)
														if(p14 != p13)
															 evvec->push_back((p14->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(13, *(*p14)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p15 != p1)
			if(p15 != p2)
				if(p15 != p3)
					if(p15 != p4)
						if(p15 != p5)
							if(p15 != p6)
								if(p15 != p7)
									if(p15 != p8)
										if(p15 != p9)
											if(p15 != p10)
												if(p15 != p11)
													if(p15 != p12)
														if(p15 != p13)
															if(p15 != p14)
																 evvec->push_back((p15->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(14, *(*p15)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p16 != p1)
			if(p16 != p2)
				if(p16 != p3)
					if(p16 != p4)
						if(p16 != p5)
							if(p16 != p6)
								if(p16 != p7)
									if(p16 != p8)
										if(p16 != p9)
											if(p16 != p10)
												if(p16 != p11)
													if(p16 != p12)
														if(p16 != p13)
															if(p16 != p14)
																if(p16 != p15)
																	 evvec->push_back((p16->GetEvent()));
		 err = k_kerneltensoradd_0_16->setArg(15, *(*p16)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensoradd_0_16->setArg(16, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensoradd_0_16, cl::NullRange, cl::NDRange(p1->GetD1(),p1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensoradd_4_16(const DeviceInterface * dev, Stream<float4> * p00, Stream<float4> * p01, Stream<float4> * p02, Stream<float4> * p03, Stream<float4> * p10, Stream<float4> * p11, Stream<float4> * p12, Stream<float4> * p13, Stream<float4> * p20, Stream<float4> * p21, Stream<float4> * p22, Stream<float4> * p23, Stream<float4> * p30, Stream<float4> * p31, Stream<float4> * p32, Stream<float4> * p33, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((p00->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(0, *(*p00)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p01 != p00)
			 evvec->push_back((p01->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(1, *(*p01)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p02 != p00)
			if(p02 != p01)
				 evvec->push_back((p02->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(2, *(*p02)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p03 != p00)
			if(p03 != p01)
				if(p03 != p02)
					 evvec->push_back((p03->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(3, *(*p03)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p10 != p00)
			if(p10 != p01)
				if(p10 != p02)
					if(p10 != p03)
						 evvec->push_back((p10->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(4, *(*p10)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p11 != p00)
			if(p11 != p01)
				if(p11 != p02)
					if(p11 != p03)
						if(p11 != p10)
							 evvec->push_back((p11->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(5, *(*p11)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p12 != p00)
			if(p12 != p01)
				if(p12 != p02)
					if(p12 != p03)
						if(p12 != p10)
							if(p12 != p11)
								 evvec->push_back((p12->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(6, *(*p12)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p13 != p00)
			if(p13 != p01)
				if(p13 != p02)
					if(p13 != p03)
						if(p13 != p10)
							if(p13 != p11)
								if(p13 != p12)
									 evvec->push_back((p13->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(7, *(*p13)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p20 != p00)
			if(p20 != p01)
				if(p20 != p02)
					if(p20 != p03)
						if(p20 != p10)
							if(p20 != p11)
								if(p20 != p12)
									if(p20 != p13)
										 evvec->push_back((p20->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(8, *(*p20)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p21 != p00)
			if(p21 != p01)
				if(p21 != p02)
					if(p21 != p03)
						if(p21 != p10)
							if(p21 != p11)
								if(p21 != p12)
									if(p21 != p13)
										if(p21 != p20)
											 evvec->push_back((p21->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(9, *(*p21)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p22 != p00)
			if(p22 != p01)
				if(p22 != p02)
					if(p22 != p03)
						if(p22 != p10)
							if(p22 != p11)
								if(p22 != p12)
									if(p22 != p13)
										if(p22 != p20)
											if(p22 != p21)
												 evvec->push_back((p22->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(10, *(*p22)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p23 != p00)
			if(p23 != p01)
				if(p23 != p02)
					if(p23 != p03)
						if(p23 != p10)
							if(p23 != p11)
								if(p23 != p12)
									if(p23 != p13)
										if(p23 != p20)
											if(p23 != p21)
												if(p23 != p22)
													 evvec->push_back((p23->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(11, *(*p23)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p30 != p00)
			if(p30 != p01)
				if(p30 != p02)
					if(p30 != p03)
						if(p30 != p10)
							if(p30 != p11)
								if(p30 != p12)
									if(p30 != p13)
										if(p30 != p20)
											if(p30 != p21)
												if(p30 != p22)
													if(p30 != p23)
														 evvec->push_back((p30->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(12, *(*p30)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p31 != p00)
			if(p31 != p01)
				if(p31 != p02)
					if(p31 != p03)
						if(p31 != p10)
							if(p31 != p11)
								if(p31 != p12)
									if(p31 != p13)
										if(p31 != p20)
											if(p31 != p21)
												if(p31 != p22)
													if(p31 != p23)
														if(p31 != p30)
															 evvec->push_back((p31->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(13, *(*p31)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p32 != p00)
			if(p32 != p01)
				if(p32 != p02)
					if(p32 != p03)
						if(p32 != p10)
							if(p32 != p11)
								if(p32 != p12)
									if(p32 != p13)
										if(p32 != p20)
											if(p32 != p21)
												if(p32 != p22)
													if(p32 != p23)
														if(p32 != p30)
															if(p32 != p31)
																 evvec->push_back((p32->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(14, *(*p32)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p33 != p00)
			if(p33 != p01)
				if(p33 != p02)
					if(p33 != p03)
						if(p33 != p10)
							if(p33 != p11)
								if(p33 != p12)
									if(p33 != p13)
										if(p33 != p20)
											if(p33 != p21)
												if(p33 != p22)
													if(p33 != p23)
														if(p33 != p30)
															if(p33 != p31)
																if(p33 != p32)
																	 evvec->push_back((p33->GetEvent()));
		 err = k_kerneltensoradd_4_16->setArg(15, *(*p33)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensoradd_4_16->setArg(16, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensoradd_4_16, cl::NullRange, cl::NDRange(p00->GetD1(),p00->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensoradd_0_4(const DeviceInterface * dev, Stream<float> * p1, Stream<float> * p2, Stream<float> * p3, Stream<float> * p4, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((p1->GetEvent()));
		 err = k_kerneltensoradd_0_4->setArg(0, *(*p1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p2 != p1)
			 evvec->push_back((p2->GetEvent()));
		 err = k_kerneltensoradd_0_4->setArg(1, *(*p2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p3 != p1)
			if(p3 != p2)
				 evvec->push_back((p3->GetEvent()));
		 err = k_kerneltensoradd_0_4->setArg(2, *(*p3)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p4 != p1)
			if(p4 != p2)
				if(p4 != p3)
					 evvec->push_back((p4->GetEvent()));
		 err = k_kerneltensoradd_0_4->setArg(3, *(*p4)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensoradd_0_4->setArg(4, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensoradd_0_4, cl::NullRange, cl::NDRange(p1->GetD1(),p1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensoradd_0_f(const DeviceInterface * dev, Stream<float> * input1, float input2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensoradd_0_f->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensoradd_0_f->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensoradd_0_f->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensoradd_0_f, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensoradd_1_1(const DeviceInterface * dev, Stream<float4> * input1, Stream<float4> * input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensoradd_1_1->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != input1)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensoradd_1_1->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensoradd_1_1->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensoradd_1_1, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensoradd_1_f(const DeviceInterface * dev, Stream<float4> * input1, float4 input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensoradd_1_f->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensoradd_1_f->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensoradd_1_f->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensoradd_1_f, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensoradd_2_2(const DeviceInterface * dev, Stream<float44> * input1, Stream<float44> * input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensoradd_2_2->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != input1)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensoradd_2_2->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensoradd_2_2->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensoradd_2_2, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensoradd_2_f44(const DeviceInterface * dev, Stream<float44> * input1, float44 input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensoradd_2_f44->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensoradd_2_f44->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensoradd_2_f44->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensoradd_2_f44, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensoradd_3_3(const DeviceInterface * dev, Stream<float444> * input1, Stream<float444> * input2, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensoradd_3_3->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != input1)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensoradd_3_3->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensoradd_3_3->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensoradd_3_3, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensoradd_3_f(const DeviceInterface * dev, Stream<float444> * input1, float444 input2, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensoradd_3_f->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensoradd_3_f->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensoradd_3_f->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensoradd_3_f, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorsub_0_0(const DeviceInterface * dev, Stream<float> * input1, Stream<float> * input2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorsub_0_0->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != input1)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorsub_0_0->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_0_0->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorsub_0_0, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorsub_0_f(const DeviceInterface * dev, Stream<float> * input1, float input2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorsub_0_f->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_0_f->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_0_f->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorsub_0_f, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorsub_f_0(const DeviceInterface * dev, float input1, Stream<float> * input2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensorsub_f_0->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorsub_f_0->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_f_0->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorsub_f_0, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorsub_1_1(const DeviceInterface * dev, Stream<float4> * input1, Stream<float4> * input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorsub_1_1->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != input1)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorsub_1_1->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_1_1->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorsub_1_1, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorsub_1_f(const DeviceInterface * dev, Stream<float4> * input1, float4 input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorsub_1_f->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_1_f->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_1_f->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorsub_1_f, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorsub_f_1(const DeviceInterface * dev, float4 input1, Stream<float4> * input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensorsub_f_1->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorsub_f_1->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_f_1->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorsub_f_1, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorsub_2_2(const DeviceInterface * dev, Stream<float44> * input1, Stream<float44> * input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorsub_2_2->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != input1)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorsub_2_2->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_2_2->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorsub_2_2, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorsub_2_f(const DeviceInterface * dev, Stream<float44> * input1, float44 input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorsub_2_f->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_2_f->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_2_f->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorsub_2_f, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorsub_f_2(const DeviceInterface * dev, float44 input1, Stream<float44> * input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensorsub_f_2->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorsub_f_2->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_f_2->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorsub_f_2, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorsub_3_3(const DeviceInterface * dev, Stream<float444> * input1, Stream<float444> * input2, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorsub_3_3->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != input1)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorsub_3_3->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_3_3->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorsub_3_3, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorsub_3_f(const DeviceInterface * dev, Stream<float444> * input1, float444 input2, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorsub_3_f->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_3_f->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_3_f->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorsub_3_f, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorsub_f_3(const DeviceInterface * dev, float444 input1, Stream<float444> * input2, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensorsub_f_3->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorsub_f_3->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsub_f_3->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorsub_f_3, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_0_0(const DeviceInterface * dev, Stream<float> * input1, Stream<float> * input2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensormult_0_0->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != input1)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensormult_0_0->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0_0->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_0_0, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_0_f(const DeviceInterface * dev, Stream<float> * input1, float input2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensormult_0_f->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0_f->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0_f->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_0_f, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_0_1(const DeviceInterface * dev, Stream<float> * input1, Stream<float4> * input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensormult_0_1->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensormult_0_1->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0_1->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_0_1, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_0_f4(const DeviceInterface * dev, Stream<float> * input1, float4 input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensormult_0_f4->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0_f4->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0_f4->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_0_f4, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_f_1(const DeviceInterface * dev, float input1, Stream<float4> * input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensormult_f_1->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensormult_f_1->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_f_1->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_f_1, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_0_2(const DeviceInterface * dev, Stream<float> * input1, Stream<float44> * input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensormult_0_2->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensormult_0_2->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0_2->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_0_2, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_0_f44(const DeviceInterface * dev, Stream<float> * input1, float44 input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensormult_0_f44->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0_f44->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0_f44->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_0_f44, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_0i_2(const DeviceInterface * dev, Stream<float44> * inx, int i, int j, Stream<float44> * input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((inx->GetEvent()));
		 err = k_kerneltensormult_0i_2->setArg(0, *(*inx)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0i_2->setArg(1, i);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0i_2->setArg(2, j);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != inx)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensormult_0i_2->setArg(3, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0i_2->setArg(4, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_0i_2, cl::NullRange, cl::NDRange(inx->GetD1(),inx->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_0i_f44(const DeviceInterface * dev, Stream<float44> * inx, int i, int j, float44 input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((inx->GetEvent()));
		 err = k_kerneltensormult_0i_f44->setArg(0, *(*inx)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0i_f44->setArg(1, i);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0i_f44->setArg(2, j);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0i_f44->setArg(3, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0i_f44->setArg(4, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_0i_f44, cl::NullRange, cl::NDRange(inx->GetD1(),inx->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_f_2(const DeviceInterface * dev, float input1, Stream<float44> * input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensormult_f_2->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensormult_f_2->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_f_2->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_f_2, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_fi_2(const DeviceInterface * dev, float44 inx, int i, int j, Stream<float44> * input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensormult_fi_2->setArg(0, inx);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_fi_2->setArg(1, i);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_fi_2->setArg(2, j);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensormult_fi_2->setArg(3, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_fi_2->setArg(4, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_fi_2, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_0_3(const DeviceInterface * dev, Stream<float> * input1, Stream<float444> * input2, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensormult_0_3->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensormult_0_3->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0_3->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_0_3, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_f_3(const DeviceInterface * dev, float input1, Stream<float444> * input2, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensormult_f_3->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensormult_f_3->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_f_3->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_f_3, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensormult_0_f444(const DeviceInterface * dev, Stream<float> * input1, float444 input2, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensormult_0_f444->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0_f444->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensormult_0_f444->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensormult_0_f444, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensordiv_0_0(const DeviceInterface * dev, Stream<float> * input1, Stream<float> * input2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensordiv_0_0->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != input1)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensordiv_0_0->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensordiv_0_0->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensordiv_0_0, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensordiv_f_0(const DeviceInterface * dev, float input1, Stream<float> * input2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensordiv_f_0->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensordiv_f_0->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensordiv_f_0->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensordiv_f_0, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensordiv_1_0(const DeviceInterface * dev, Stream<float4> * input1, Stream<float> * input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensordiv_1_0->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensordiv_1_0->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensordiv_1_0->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensordiv_1_0, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensordiv_f4_0(const DeviceInterface * dev, float4 input1, Stream<float> * input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensordiv_f4_0->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensordiv_f4_0->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensordiv_f4_0->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensordiv_f4_0, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensordiv_2_0(const DeviceInterface * dev, Stream<float44> * input1, Stream<float> * input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensordiv_2_0->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensordiv_2_0->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensordiv_2_0->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensordiv_2_0, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensordiv_2_f(const DeviceInterface * dev, Stream<float44> * input1, float input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensordiv_2_f->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensordiv_2_f->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensordiv_2_f->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensordiv_2_f, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensordiv_f44_0(const DeviceInterface * dev, float44 input1, Stream<float> * input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensordiv_f44_0->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensordiv_f44_0->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensordiv_f44_0->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensordiv_f44_0, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensordiv_3_0(const DeviceInterface * dev, Stream<float444> * input1, Stream<float> * input2, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensordiv_3_0->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensordiv_3_0->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensordiv_3_0->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensordiv_3_0, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensordiv_3_f(const DeviceInterface * dev, Stream<float444> * input1, float input2, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensordiv_3_f->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensordiv_3_f->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensordiv_3_f->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensordiv_3_f, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensordiv_f444_0(const DeviceInterface * dev, float444 input1, Stream<float> * input2, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensordiv_f444_0->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensordiv_f444_0->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensordiv_f444_0->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensordiv_f444_0, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorouter_1_1(const DeviceInterface * dev, Stream<float4> * input1, Stream<float4> * input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorouter_1_1->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != input1)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorouter_1_1->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorouter_1_1->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorouter_1_1, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorouter_1_f4(const DeviceInterface * dev, Stream<float4> * input1, float4 input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorouter_1_f4->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorouter_1_f4->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorouter_1_f4->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorouter_1_f4, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorouter_f4_1(const DeviceInterface * dev, float4 input1, Stream<float4> * input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensorouter_f4_1->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorouter_f4_1->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorouter_f4_1->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorouter_f4_1, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorouter_2_1(const DeviceInterface * dev, Stream<float44> * input1, Stream<float4> * input2, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorouter_2_1->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorouter_2_1->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorouter_2_1->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorouter_2_1, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorouter_2_f4(const DeviceInterface * dev, Stream<float44> * input1, float4 input2, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorouter_2_f4->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorouter_2_f4->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorouter_2_f4->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorouter_2_f4, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorouter_f44_1(const DeviceInterface * dev, float44 input1, Stream<float4> * input2, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensorouter_f44_1->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorouter_f44_1->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorouter_f44_1->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorouter_f44_1, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorouter_1_2(const DeviceInterface * dev, Stream<float4> * lhs, Stream<float44> * rhs, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((lhs->GetEvent()));
		 err = k_kerneltensorouter_1_2->setArg(0, *(*lhs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((rhs->GetEvent()));
		 err = k_kerneltensorouter_1_2->setArg(1, *(*rhs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorouter_1_2->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorouter_1_2, cl::NullRange, cl::NDRange(lhs->GetD1(),lhs->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorouter_f4_2(const DeviceInterface * dev, float4 lhs, Stream<float44> * rhs, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensorouter_f4_2->setArg(0, lhs);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((rhs->GetEvent()));
		 err = k_kerneltensorouter_f4_2->setArg(1, *(*rhs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorouter_f4_2->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorouter_f4_2, cl::NullRange, cl::NDRange(rhs->GetD1(),rhs->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorouter_1_f44(const DeviceInterface * dev, Stream<float4> * lhs, float44 rhs, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((lhs->GetEvent()));
		 err = k_kerneltensorouter_1_f44->setArg(0, *(*lhs)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorouter_1_f44->setArg(1, rhs);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorouter_1_f44->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorouter_1_f44, cl::NullRange, cl::NDRange(lhs->GetD1(),lhs->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorneg_0(const DeviceInterface * dev, Stream<float> * input, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensorneg_0->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorneg_0->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorneg_0, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorneg_1(const DeviceInterface * dev, Stream<float4> * input, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensorneg_1->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorneg_1->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorneg_1, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorneg_2(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensorneg_2->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorneg_2->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorneg_2, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorneg_3(const DeviceInterface * dev, Stream<float444> * input, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensorneg_3->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorneg_3->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorneg_3, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorsqrt_0(const DeviceInterface * dev, Stream<float> * input, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensorsqrt_0->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsqrt_0->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorsqrt_0, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorsin_0(const DeviceInterface * dev, Stream<float> * input, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensorsin_0->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorsin_0->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorsin_0, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcos_0(const DeviceInterface * dev, Stream<float> * input, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensorcos_0->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcos_0->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcos_0, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensortan_0(const DeviceInterface * dev, Stream<float> * input, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensortan_0->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensortan_0->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensortan_0, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorexp_0(const DeviceInterface * dev, Stream<float> * input, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensorexp_0->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorexp_0->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorexp_0, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensortrans_2(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensortrans_2->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensortrans_2->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensortrans_2, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensortrans_3_213(const DeviceInterface * dev, Stream<float444> * input, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensortrans_3_213->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensortrans_3_213->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensortrans_3_213, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensortrans_3_132(const DeviceInterface * dev, Stream<float444> * input, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensortrans_3_132->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensortrans_3_132->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensortrans_3_132, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmoveindex_1(const DeviceInterface * dev, Stream<float4> * input, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelmoveindex_1->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmoveindex_1->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmoveindex_1, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmovelastindex_2(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelmovelastindex_2->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmovelastindex_2->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmovelastindex_2, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmovefirstindex_2(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelmovefirstindex_2->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmovefirstindex_2->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmovefirstindex_2, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmoveindices_2(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelmoveindices_2->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmoveindices_2->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmoveindices_2, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmoveindices_3(const DeviceInterface * dev, Stream<float444> * input, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelmoveindices_3->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmoveindices_3->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmoveindices_3, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmovelastindex_3(const DeviceInterface * dev, Stream<float444> * input, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelmovelastindex_3->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmovelastindex_3->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmovelastindex_3, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmovemiddleindex_3(const DeviceInterface * dev, Stream<float444> * input, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelmovemiddleindex_3->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmovemiddleindex_3->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmovemiddleindex_3, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelmovefirstindex_3(const DeviceInterface * dev, Stream<float444> * input, Stream<float444> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kernelmovefirstindex_3->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelmovefirstindex_3->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelmovefirstindex_3, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernellorentzboost(const DeviceInterface * dev, Stream<float4> * vector1, Stream<float4> * vector2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((vector1->GetEvent()));
		 err = k_kernellorentzboost->setArg(0, *(*vector1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(vector2 != vector1)
			 evvec->push_back((vector2->GetEvent()));
		 err = k_kernellorentzboost->setArg(1, *(*vector2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernellorentzboost->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernellorentzboost, cl::NullRange, cl::NDRange(vector1->GetD1(),vector1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernellorentzrotation(const DeviceInterface * dev, Stream<float4> * vector1, Stream<float4> * vector2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((vector1->GetEvent()));
		 err = k_kernellorentzrotation->setArg(0, *(*vector1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(vector2 != vector1)
			 evvec->push_back((vector2->GetEvent()));
		 err = k_kernellorentzrotation->setArg(1, *(*vector2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernellorentzrotation->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernellorentzrotation, cl::NullRange, cl::NDRange(vector1->GetD1(),vector1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorphi_1(const DeviceInterface * dev, Stream<float4> * input, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensorphi_1->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorphi_1->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorphi_1, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcostheta_1(const DeviceInterface * dev, Stream<float4> * input, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input->GetEvent()));
		 err = k_kerneltensorcostheta_1->setArg(0, *(*input)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcostheta_1->setArg(1, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcostheta_1, cl::NullRange, cl::NDRange(input->GetD1(),input->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_1_1(const DeviceInterface * dev, Stream<float4> * input1, Stream<float4> * input2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract_1_1->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != input1)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorcontract_1_1->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_1_1->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_1_1, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_1_f(const DeviceInterface * dev, Stream<float4> * input1, float4 input2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract_1_f->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_1_f->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_1_f->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_1_f, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_2_1(const DeviceInterface * dev, Stream<float44> * input1, Stream<float4> * input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract_2_1->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorcontract_2_1->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_2_1->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_2_1, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_f44_1(const DeviceInterface * dev, float44 input1, Stream<float4> * input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensorcontract_f44_1->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorcontract_f44_1->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_f44_1->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_f44_1, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_2_f4(const DeviceInterface * dev, Stream<float44> * input1, float4 input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract_2_f4->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_2_f4->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_2_f4->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_2_f4, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_2_2(const DeviceInterface * dev, Stream<float44> * input1, Stream<float44> * input2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract_2_2->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != input1)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorcontract_2_2->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_2_2->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_2_2, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_2_f44(const DeviceInterface * dev, Stream<float44> * input1, float44 input2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract_2_f44->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_2_f44->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_2_f44->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_2_f44, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract2_2_2(const DeviceInterface * dev, Stream<float44> * p1, Stream<float44> * p2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((p1->GetEvent()));
		 err = k_kerneltensorcontract2_2_2->setArg(0, *(*p1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p2 != p1)
			 evvec->push_back((p2->GetEvent()));
		 err = k_kerneltensorcontract2_2_2->setArg(1, *(*p2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract2_2_2->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract2_2_2, cl::NullRange, cl::NDRange(p1->GetD1(),p1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract2_2_f44(const DeviceInterface * dev, Stream<float44> * p1, float44 p2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((p1->GetEvent()));
		 err = k_kerneltensorcontract2_2_f44->setArg(0, *(*p1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract2_2_f44->setArg(1, p2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract2_2_f44->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract2_2_f44, cl::NullRange, cl::NDRange(p1->GetD1(),p1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract2_f44_2(const DeviceInterface * dev, float44 p1, Stream<float44> * p2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensorcontract2_f44_2->setArg(0, p1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((p2->GetEvent()));
		 err = k_kerneltensorcontract2_f44_2->setArg(1, *(*p2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract2_f44_2->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract2_f44_2, cl::NullRange, cl::NDRange(p2->GetD1(),p2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_3_3(const DeviceInterface * dev, Stream<float444> * input1, Stream<float444> * input2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract_3_3->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != input1)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorcontract_3_3->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_3_3->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_3_3, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_3_f444(const DeviceInterface * dev, Stream<float444> * input1, float444 input2, Stream<float> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract_3_f444->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_3_f444->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_3_f444->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_3_f444, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_3_1(const DeviceInterface * dev, Stream<float444> * input1, Stream<float4> * input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract_3_1->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorcontract_3_1->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_3_1->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_3_1, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_f444_1(const DeviceInterface * dev, float444 input1, Stream<float4> * input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensorcontract_f444_1->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorcontract_f444_1->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_f444_1->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_f444_1, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_3_f4(const DeviceInterface * dev, Stream<float444> * input1, float4 input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract_3_f4->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_3_f4->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_3_f4->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_3_f4, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_3_2(const DeviceInterface * dev, Stream<float444> * input1, Stream<float44> * input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract_3_2->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorcontract_3_2->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_3_2->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_3_2, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_3_f44(const DeviceInterface * dev, Stream<float444> * input1, float44 input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract_3_f44->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_3_f44->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_3_f44->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_3_f44, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_2_3_sign(const DeviceInterface * dev, Stream<float44> * input1, Stream<float444> * input2, int sign, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract_2_3_sign->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorcontract_2_3_sign->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_2_3_sign->setArg(2, sign);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_2_3_sign->setArg(3, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_2_3_sign, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_2_3(const DeviceInterface * dev, Stream<float44> * input1, Stream<float444> * input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract_2_3->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorcontract_2_3->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_2_3->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_2_3, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_2_f444(const DeviceInterface * dev, Stream<float44> * input1, float444 input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract_2_f444->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_2_f444->setArg(1, input2);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_2_f444->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_2_f444, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_f44_3(const DeviceInterface * dev, float44 input1, Stream<float444> * input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensorcontract_f44_3->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorcontract_f44_3->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_f44_3->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_f44_3, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract_f444_2(const DeviceInterface * dev, float444 input1, Stream<float44> * input2, Stream<float4> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kerneltensorcontract_f444_2->setArg(0, input1);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorcontract_f444_2->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract_f444_2->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract_f444_2, cl::NullRange, cl::NDRange(input2->GetD1(),input2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 output->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kerneltensorcontract2_3_3(const DeviceInterface * dev, Stream<float444> * input1, Stream<float444> * input2, Stream<float44> * output){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((input1->GetEvent()));
		 err = k_kerneltensorcontract2_3_3->setArg(0, *(*input1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(input2 != input1)
			 evvec->push_back((input2->GetEvent()));
		 err = k_kerneltensorcontract2_3_3->setArg(1, *(*input2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kerneltensorcontract2_3_3->setArg(2, *(*output)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kerneltensorcontract2_3_3, cl::NullRange, cl::NDRange(input1->GetD1(),input1->GetD2()), cl::NullRange, evvec, &event );
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
