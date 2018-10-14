/* Contractions.h  -- source for interface functions to the kernels
 defined in /scratchfs/bes/xiongxa/GamEtapKsKs/GPUPWA/gpupwa2.1_jpc2370check/GPUPWA/Contractions.cl, the corresponding binaries are in binfiles/Contractions.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#include"Contractions.h"
#include"KernelFile.h"
#include<vector>
#include<iostream>
#include<cassert>


namespace Contractions_GPU{

	 cl::Kernel * k_kernelone = 0;
	 cl::Kernel * k_kernelone_c = 0;
	 cl::Kernel * k_kernelcontractscalar = 0;
	 cl::Kernel * k_kernelcontractscalar_f_u = 0;
	 cl::Kernel * k_kernelcontractscalar_u_f = 0;
	 cl::Kernel * k_kernelcontractscalar_u_u = 0;
	 cl::Kernel * k_kernelcontractscalarorbital = 0;
	 cl::Kernel * k_kernelcontractmesons = 0;
	 cl::Kernel * k_kernelcontractmesons_v_v = 0;
	 cl::Kernel * k_kernelcontractmesons_s_v = 0;
	 cl::Kernel * k_kernelcontractmesons_v_s = 0;
	 cl::Kernel * k_kernelcontractmesonsorbital = 0;
	 cl::Kernel * k_kernelcontractradmesons = 0;
	 cl::Kernel * k_kernelcontractradmesonsorbital = 0;
	 cl::Kernel * k_kernelcontractradmesons_f_u = 0;
	 cl::Kernel * k_kernelcontractradmesons_u_f = 0;
	 cl::Kernel * k_kernelcontract3radmesons = 0;
	 int prepare_kernels(const DeviceInterface * dev){
		 FILE * input = fopen("binfiles/Contractions.bin","rb");
		 if(!input){
			 	std::cerr << "Loading binary file binfiles/Contractions.bin failed \n";
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

		 k_kernelone = new cl::Kernel(*bProgram, "kernelone", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelone\n";
			 return FAILURE;
		 }

		 k_kernelone_c = new cl::Kernel(*bProgram, "kernelone_c", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelone_c\n";
			 return FAILURE;
		 }

		 k_kernelcontractscalar = new cl::Kernel(*bProgram, "kernelcontractscalar", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcontractscalar\n";
			 return FAILURE;
		 }

		 k_kernelcontractscalar_f_u = new cl::Kernel(*bProgram, "kernelcontractscalar_f_u", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcontractscalar_f_u\n";
			 return FAILURE;
		 }

		 k_kernelcontractscalar_u_f = new cl::Kernel(*bProgram, "kernelcontractscalar_u_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcontractscalar_u_f\n";
			 return FAILURE;
		 }

		 k_kernelcontractscalar_u_u = new cl::Kernel(*bProgram, "kernelcontractscalar_u_u", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcontractscalar_u_u\n";
			 return FAILURE;
		 }

		 k_kernelcontractscalarorbital = new cl::Kernel(*bProgram, "kernelcontractscalarorbital", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcontractscalarorbital\n";
			 return FAILURE;
		 }

		 k_kernelcontractmesons = new cl::Kernel(*bProgram, "kernelcontractmesons", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcontractmesons\n";
			 return FAILURE;
		 }

		 k_kernelcontractmesons_v_v = new cl::Kernel(*bProgram, "kernelcontractmesons_v_v", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcontractmesons_v_v\n";
			 return FAILURE;
		 }

		 k_kernelcontractmesons_s_v = new cl::Kernel(*bProgram, "kernelcontractmesons_s_v", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcontractmesons_s_v\n";
			 return FAILURE;
		 }

		 k_kernelcontractmesons_v_s = new cl::Kernel(*bProgram, "kernelcontractmesons_v_s", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcontractmesons_v_s\n";
			 return FAILURE;
		 }

		 k_kernelcontractmesonsorbital = new cl::Kernel(*bProgram, "kernelcontractmesonsorbital", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcontractmesonsorbital\n";
			 return FAILURE;
		 }

		 k_kernelcontractradmesons = new cl::Kernel(*bProgram, "kernelcontractradmesons", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcontractradmesons\n";
			 return FAILURE;
		 }

		 k_kernelcontractradmesonsorbital = new cl::Kernel(*bProgram, "kernelcontractradmesonsorbital", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcontractradmesonsorbital\n";
			 return FAILURE;
		 }

		 k_kernelcontractradmesons_f_u = new cl::Kernel(*bProgram, "kernelcontractradmesons_f_u", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcontractradmesons_f_u\n";
			 return FAILURE;
		 }

		 k_kernelcontractradmesons_u_f = new cl::Kernel(*bProgram, "kernelcontractradmesons_u_f", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcontractradmesons_u_f\n";
			 return FAILURE;
		 }

		 k_kernelcontract3radmesons = new cl::Kernel(*bProgram, "kernelcontract3radmesons", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel kernelcontract3radmesons\n";
			 return FAILURE;
		 }

	 return 0;
	 }



	 int kernelone(const DeviceInterface * dev, Stream<float> * a){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kernelone->setArg(0, *(*a)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelone, cl::NullRange, cl::NDRange(a->GetD1(),a->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 a->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelone_c(const DeviceInterface * dev, Stream<float2> * a){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 err = k_kernelone_c->setArg(0, *(*a)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelone_c, cl::NullRange, cl::NDRange(a->GetD1(),a->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 a->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelcontractscalar(const DeviceInterface * dev, Stream<float> * tensor1, Stream<float> * tensor2, Stream<float2> * propagator1, Stream<float2> * propagator2, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((tensor1->GetEvent()));
		 err = k_kernelcontractscalar->setArg(0, *(*tensor1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(tensor2 != tensor1)
			 evvec->push_back((tensor2->GetEvent()));
		 err = k_kernelcontractscalar->setArg(1, *(*tensor2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((propagator1->GetEvent()));
		 err = k_kernelcontractscalar->setArg(2, *(*propagator1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator2 != propagator1)
			 evvec->push_back((propagator2->GetEvent()));
		 err = k_kernelcontractscalar->setArg(3, *(*propagator2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcontractscalar->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcontractscalar, cl::NullRange, cl::NDRange(tensor1->GetD1(),tensor1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelcontractscalar_f_u(const DeviceInterface * dev, Stream<float> * tensor1, Stream<float2> * propagator1, Stream<float2> * propagator2, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((tensor1->GetEvent()));
		 err = k_kernelcontractscalar_f_u->setArg(0, *(*tensor1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((propagator1->GetEvent()));
		 err = k_kernelcontractscalar_f_u->setArg(1, *(*propagator1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator2 != propagator1)
			 evvec->push_back((propagator2->GetEvent()));
		 err = k_kernelcontractscalar_f_u->setArg(2, *(*propagator2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcontractscalar_f_u->setArg(3, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcontractscalar_f_u, cl::NullRange, cl::NDRange(tensor1->GetD1(),tensor1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelcontractscalar_u_f(const DeviceInterface * dev, Stream<float2> * propagator1, Stream<float> * tensor2, Stream<float2> * propagator2, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((propagator1->GetEvent()));
		 err = k_kernelcontractscalar_u_f->setArg(0, *(*propagator1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((tensor2->GetEvent()));
		 err = k_kernelcontractscalar_u_f->setArg(1, *(*tensor2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator2 != propagator1)
			 evvec->push_back((propagator2->GetEvent()));
		 err = k_kernelcontractscalar_u_f->setArg(2, *(*propagator2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcontractscalar_u_f->setArg(3, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcontractscalar_u_f, cl::NullRange, cl::NDRange(propagator1->GetD1(),propagator1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelcontractscalar_u_u(const DeviceInterface * dev, Stream<float2> * propagator1, Stream<float2> * propagator2, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((propagator1->GetEvent()));
		 err = k_kernelcontractscalar_u_u->setArg(0, *(*propagator1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator2 != propagator1)
			 evvec->push_back((propagator2->GetEvent()));
		 err = k_kernelcontractscalar_u_u->setArg(1, *(*propagator2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcontractscalar_u_u->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcontractscalar_u_u, cl::NullRange, cl::NDRange(propagator1->GetD1(),propagator1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelcontractscalarorbital(const DeviceInterface * dev, Stream<float> * tensor1, Stream<float> * tensor2, Stream<float> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((tensor1->GetEvent()));
		 err = k_kernelcontractscalarorbital->setArg(0, *(*tensor1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(tensor2 != tensor1)
			 evvec->push_back((tensor2->GetEvent()));
		 err = k_kernelcontractscalarorbital->setArg(1, *(*tensor2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(result != tensor1)
			if(result != tensor2)
				 evvec->push_back((result->GetEvent()));
		 err = k_kernelcontractscalarorbital->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcontractscalarorbital, cl::NullRange, cl::NDRange(tensor1->GetD1(),tensor1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 delete evvec;
	 return 0;
	 }

	 int kernelcontractmesons(const DeviceInterface * dev, Stream<float4> * tensor1, Stream<float4> * tensor2, Stream<float2> * propagator1, Stream<float2> * propagator2, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((tensor1->GetEvent()));
		 err = k_kernelcontractmesons->setArg(0, *(*tensor1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(tensor2 != tensor1)
			 evvec->push_back((tensor2->GetEvent()));
		 err = k_kernelcontractmesons->setArg(1, *(*tensor2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((propagator1->GetEvent()));
		 err = k_kernelcontractmesons->setArg(2, *(*propagator1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator2 != propagator1)
			 evvec->push_back((propagator2->GetEvent()));
		 err = k_kernelcontractmesons->setArg(3, *(*propagator2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcontractmesons->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcontractmesons, cl::NullRange, cl::NDRange(tensor1->GetD1(),tensor1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelcontractmesons_v_v(const DeviceInterface * dev, Stream<float4> * propagator1real, Stream<float4> * propagator1imag, Stream<float4> * propagator2real, Stream<float4> * propagator2imag, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((propagator1real->GetEvent()));
		 err = k_kernelcontractmesons_v_v->setArg(0, *(*propagator1real)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator1imag != propagator1real)
			 evvec->push_back((propagator1imag->GetEvent()));
		 err = k_kernelcontractmesons_v_v->setArg(1, *(*propagator1imag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator2real != propagator1real)
			if(propagator2real != propagator1imag)
				 evvec->push_back((propagator2real->GetEvent()));
		 err = k_kernelcontractmesons_v_v->setArg(2, *(*propagator2real)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator2imag != propagator1real)
			if(propagator2imag != propagator1imag)
				if(propagator2imag != propagator2real)
					 evvec->push_back((propagator2imag->GetEvent()));
		 err = k_kernelcontractmesons_v_v->setArg(3, *(*propagator2imag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcontractmesons_v_v->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcontractmesons_v_v, cl::NullRange, cl::NDRange(propagator1real->GetD1(),propagator1real->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelcontractmesons_s_v(const DeviceInterface * dev, Stream<float4> * tensor1, Stream<float2> * propagator1, Stream<float4> * propagator2real, Stream<float4> * propagator2imag, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((tensor1->GetEvent()));
		 err = k_kernelcontractmesons_s_v->setArg(0, *(*tensor1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((propagator1->GetEvent()));
		 err = k_kernelcontractmesons_s_v->setArg(1, *(*propagator1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator2real != tensor1)
			 evvec->push_back((propagator2real->GetEvent()));
		 err = k_kernelcontractmesons_s_v->setArg(2, *(*propagator2real)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator2imag != tensor1)
			if(propagator2imag != propagator2real)
				 evvec->push_back((propagator2imag->GetEvent()));
		 err = k_kernelcontractmesons_s_v->setArg(3, *(*propagator2imag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcontractmesons_s_v->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcontractmesons_s_v, cl::NullRange, cl::NDRange(tensor1->GetD1(),tensor1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelcontractmesons_v_s(const DeviceInterface * dev, Stream<float4> * tensor2, Stream<float4> * propagator1real, Stream<float4> * propagator1imag, Stream<float2> * propagator2, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((tensor2->GetEvent()));
		 err = k_kernelcontractmesons_v_s->setArg(0, *(*tensor2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator1real != tensor2)
			 evvec->push_back((propagator1real->GetEvent()));
		 err = k_kernelcontractmesons_v_s->setArg(1, *(*propagator1real)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator1imag != tensor2)
			if(propagator1imag != propagator1real)
				 evvec->push_back((propagator1imag->GetEvent()));
		 err = k_kernelcontractmesons_v_s->setArg(2, *(*propagator1imag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((propagator2->GetEvent()));
		 err = k_kernelcontractmesons_v_s->setArg(3, *(*propagator2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcontractmesons_v_s->setArg(4, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcontractmesons_v_s, cl::NullRange, cl::NDRange(tensor2->GetD1(),tensor2->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelcontractmesonsorbital(const DeviceInterface * dev, Stream<float4> * tensor1, Stream<float4> * tensor2, Stream<float> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((tensor1->GetEvent()));
		 err = k_kernelcontractmesonsorbital->setArg(0, *(*tensor1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(tensor2 != tensor1)
			 evvec->push_back((tensor2->GetEvent()));
		 err = k_kernelcontractmesonsorbital->setArg(1, *(*tensor2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcontractmesonsorbital->setArg(2, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcontractmesonsorbital, cl::NullRange, cl::NDRange(tensor1->GetD1(),tensor1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelcontractradmesons(const DeviceInterface * dev, Stream<float44> * tensor1, Stream<float44> * tensor2, Stream<float44> * gperp, Stream<float2> * propagator1, Stream<float2> * propagator2, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((tensor1->GetEvent()));
		 err = k_kernelcontractradmesons->setArg(0, *(*tensor1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(tensor2 != tensor1)
			 evvec->push_back((tensor2->GetEvent()));
		 err = k_kernelcontractradmesons->setArg(1, *(*tensor2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(gperp != tensor1)
			if(gperp != tensor2)
				 evvec->push_back((gperp->GetEvent()));
		 err = k_kernelcontractradmesons->setArg(2, *(*gperp)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((propagator1->GetEvent()));
		 err = k_kernelcontractradmesons->setArg(3, *(*propagator1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(propagator2 != propagator1)
			 evvec->push_back((propagator2->GetEvent()));
		 err = k_kernelcontractradmesons->setArg(4, *(*propagator2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcontractradmesons->setArg(5, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcontractradmesons, cl::NullRange, cl::NDRange(tensor1->GetD1(),tensor1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelcontractradmesonsorbital(const DeviceInterface * dev, Stream<float44> * tensor1, Stream<float44> * tensor2, Stream<float44> * gperp, Stream<float> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((tensor1->GetEvent()));
		 err = k_kernelcontractradmesonsorbital->setArg(0, *(*tensor1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(tensor2 != tensor1)
			 evvec->push_back((tensor2->GetEvent()));
		 err = k_kernelcontractradmesonsorbital->setArg(1, *(*tensor2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(gperp != tensor1)
			if(gperp != tensor2)
				 evvec->push_back((gperp->GetEvent()));
		 err = k_kernelcontractradmesonsorbital->setArg(2, *(*gperp)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcontractradmesonsorbital->setArg(3, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcontractradmesonsorbital, cl::NullRange, cl::NDRange(tensor1->GetD1(),tensor1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelcontractradmesons_f_u(const DeviceInterface * dev, Stream<float44> * tensor1, Stream<float2> * propagator1, Stream<float44> * gperp, Stream<float44> * p2real, Stream<float44> * p2imag, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((tensor1->GetEvent()));
		 err = k_kernelcontractradmesons_f_u->setArg(0, *(*tensor1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((propagator1->GetEvent()));
		 err = k_kernelcontractradmesons_f_u->setArg(1, *(*propagator1)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(gperp != tensor1)
			 evvec->push_back((gperp->GetEvent()));
		 err = k_kernelcontractradmesons_f_u->setArg(2, *(*gperp)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p2real != tensor1)
			if(p2real != gperp)
				 evvec->push_back((p2real->GetEvent()));
		 err = k_kernelcontractradmesons_f_u->setArg(3, *(*p2real)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p2imag != tensor1)
			if(p2imag != gperp)
				if(p2imag != p2real)
					 evvec->push_back((p2imag->GetEvent()));
		 err = k_kernelcontractradmesons_f_u->setArg(4, *(*p2imag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcontractradmesons_f_u->setArg(5, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcontractradmesons_f_u, cl::NullRange, cl::NDRange(tensor1->GetD1(),tensor1->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelcontractradmesons_u_f(const DeviceInterface * dev, Stream<float44> * p1real, Stream<float44> * p1imag, Stream<float44> * gperp, Stream<float44> * tensor2, Stream<float2> * propagator2, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((p1real->GetEvent()));
		 err = k_kernelcontractradmesons_u_f->setArg(0, *(*p1real)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p1imag != p1real)
			 evvec->push_back((p1imag->GetEvent()));
		 err = k_kernelcontractradmesons_u_f->setArg(1, *(*p1imag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(gperp != p1real)
			if(gperp != p1imag)
				 evvec->push_back((gperp->GetEvent()));
		 err = k_kernelcontractradmesons_u_f->setArg(2, *(*gperp)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(tensor2 != p1real)
			if(tensor2 != p1imag)
				if(tensor2 != gperp)
					 evvec->push_back((tensor2->GetEvent()));
		 err = k_kernelcontractradmesons_u_f->setArg(3, *(*tensor2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 evvec->push_back((propagator2->GetEvent()));
		 err = k_kernelcontractradmesons_u_f->setArg(4, *(*propagator2)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcontractradmesons_u_f->setArg(5, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcontractradmesons_u_f, cl::NullRange, cl::NDRange(p1real->GetD1(),p1real->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 result->SetEvent(event);

		 delete evvec;
	 return 0;
	 }

	 int kernelcontract3radmesons(const DeviceInterface * dev, Stream<float44> * gperp, Stream<float44> * p1real, Stream<float44> * p1imag, Stream<float44> * p2real, Stream<float44> * p2imag, Stream<float2> * result){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((gperp->GetEvent()));
		 err = k_kernelcontract3radmesons->setArg(0, *(*gperp)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p1real != gperp)
			 evvec->push_back((p1real->GetEvent()));
		 err = k_kernelcontract3radmesons->setArg(1, *(*p1real)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p1imag != gperp)
			if(p1imag != p1real)
				 evvec->push_back((p1imag->GetEvent()));
		 err = k_kernelcontract3radmesons->setArg(2, *(*p1imag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p2real != gperp)
			if(p2real != p1real)
				if(p2real != p1imag)
					 evvec->push_back((p2real->GetEvent()));
		 err = k_kernelcontract3radmesons->setArg(3, *(*p2real)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		if(p2imag != gperp)
			if(p2imag != p1real)
				if(p2imag != p1imag)
					if(p2imag != p2real)
						 evvec->push_back((p2imag->GetEvent()));
		 err = k_kernelcontract3radmesons->setArg(4, *(*p2imag)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = k_kernelcontract3radmesons->setArg(5, *(*result)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_kernelcontract3radmesons, cl::NullRange, cl::NDRange(gperp->GetD1(),gperp->GetD2()), cl::NullRange, evvec, &event );
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
