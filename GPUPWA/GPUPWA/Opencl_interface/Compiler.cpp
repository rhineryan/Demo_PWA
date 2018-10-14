/*
 * Compiler.cpp
 *
 *  Create binaries from OpenCL kernels and type safe initialisers and function calls
 *
 *  uses a rather wild mix of C++ and C I/O, botyh languages not particularly well
 *  suited to parsing and text generation...
 *
 *  Created on: Aug 12, 2010
 *      Author: nberger
 */


#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <cassert>
#include <string>

#include <CL/cl.hpp>

#include "KernelFile.h"
#include "DeviceInterface.h"
#include "Stream.h"


#define FAILURE -1
#define SUCCESS 0

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;

int main(int argc, char* argv[]){

	cout << "OpenCL kernel interface generator" << endl;
	cout << "2010 Niklaus Berger, IHEP Beijing" << endl;

	if(argc < 3){
		cout << "Usage:" << endl;
		cout << "compilekernels CPU/GPU kernelfile [options]" << endl;
		cout << "Supported options:" << endl;
		cout << "		-ev: Generate function prototypes requiring an explicit statement of the execution domain" << endl;
		cout << "       -nv: Use the khr_fp64 extension (nvidia, Apple) instead of the amd_fp_64 one " << endl;
		return -1;
	}
	int devtype =0; // 0 for undefined, 1 GPU, 2 CPU

	if(strcmp(argv[1], "GPU") == 0)
		devtype= 1;
	else if(strcmp(argv[1], "CPU") == 0)
		devtype = 2;
	else {
		cout << "Argument 1 should be either \"GPU\" or \"CPU\"" << endl;
		return -1;
	}
	assert(devtype);

	char * suffix = strstr(argv[2], ".cl");
	if(suffix == NULL){
		cout << "Argument 2 should be a *.cl file" << endl;
		return -1;
	}
	char * pathend = argv[2];
	char * xpos =argv[2];
	while((xpos = strstr(pathend, "/")))
	  pathend = xpos+1;
	
	unsigned int length = suffix - pathend;//argv[2];
	assert(length > 0);
	char name[length+1];
	strncpy(name, pathend,length);
	name[length] ='\0';
	cout << "Compiling and interfacing kernels in " << name << ".cl";
	if(devtype == 1)
		cout << " for the GPU" << endl;
	else
		cout << " for the CPU" << endl;

		
	bool evcount = false;
	bool nv = false;
	if(argc > 3){
		for(int i = 3; i < argc; i++){
			if(strcmp(argv[i], "-ev") == 0){
				cout << "Producing function prototypes with explicit event counts" << endl;
				evcount = true;
			}
			if(strcmp(argv[i], "-nv") == 0){
				cout << "Producing kernels for Nvidia floating point extensions" << endl;
				nv = true;
			}

	 	}
	}
		
		
	DeviceInterface * dev;
	if(devtype == 1)
		dev = new DeviceInterface(CL_DEVICE_TYPE_GPU);
	else
		dev = new DeviceInterface(CL_DEVICE_TYPE_CPU);

	if(dev->initialized() != OK){
		cerr << "Failed to initialize device - aborting!" << endl;
		return FAILURE;
	}

	KernelFile file;
	if (!file.open(argv[2])) {
		cerr << "We couldn't load CL source code in " << argv[2] << endl;
		return FAILURE;
	}

	cl_int err;

	cl::Program::Sources * sources;
	if(!nv){
	  //    cout << file.cleansource().data() << endl;

		sources = new cl::Program::Sources(1, std::make_pair(file.cleansource().data(), file.cleansource().size()));
		//	cout << "AMD" << endl;
	} else {
	  //	cout << "NVIDIA" << endl;
	//	cout << file.standardsource().data() << endl <<endl;
		sources = new cl::Program::Sources(1, std::make_pair(file.standardsource().data(), file.standardsource().size()));

	}

	cl::Program*    pProgram;
	pProgram = new cl::Program(*(dev->GetContext()), *sources, &err);
	if (err != CL_SUCCESS) {
		cerr << "Program::Program() failed (" << err << ")\n";
		return FAILURE;
	}
	//err = pProgram->build(*(dev->GetDevices()), "-I ~/workspace/GPUPWA_OpenCL/GPUPWA -I /usr/local/ati-stream-sdk-v2.2-lnx32/include/");
	err = pProgram->build(*(dev->GetDevices()));///, "-cl-opt-disable");
	if (err != CL_SUCCESS) {
		cerr << "Program::build() failed (" << err << ")\n";
		string str = pProgram->getBuildInfo<CL_PROGRAM_BUILD_LOG>((*(dev->GetDevices()))[0]);

		std::cout << " \n\t\t\tBUILD LOG\n";
		std::cout << " ************************************************\n";
		std::cout << str << std::endl;
		std::cout << " ************************************************\n";

		return FAILURE;
	}

	vector<size_t> svec;
	svec = pProgram->getInfo<CL_PROGRAM_BINARY_SIZES>();
	assert(svec[0]);

	//std::cout << svec.size() << std::endl;
	//for(unsigned int i=0; i < svec.size(); i++)
	// std::cout << svec[i] << std::endl;
	size_t size = svec[0];
	/*char * binary = new char[size];
	char * buffers[svec.size()];
	buffers[0] = binary;
	for(unsigned int i=1; i < svec.size(); i++)
	buffers[i] = 0;*/

	char * buffers[svec.size()];
	for(unsigned int i=0; i < svec.size(); i++)
	  buffers[i] = new char[svec[i]];

	//std::cout << sizeof(buffers[0]) << std::endl;
	err = clGetProgramInfo((*pProgram)(), CL_PROGRAM_BINARIES, sizeof(buffers), &buffers, NULL);

	char * binary = buffers[0];
	
	char binfilename[length+8+9];
	if(devtype == 1)
		sprintf(binfilename,"binfiles/%s.bin",name);
	else
		sprintf(binfilename,"binfiles/%s_cpu.bin",name);
	FILE * output = fopen(binfilename, "wb");
	if(!output){
		cerr << "Could not open " << binfilename << " for writing, aborting" << endl;
		return FAILURE;
	}
	fwrite(binary, sizeof(char),size,output);
	fclose(output);
	for(unsigned int i=0; i < svec.size(); i++)
	  delete buffers[i];
	cout << "Wrote " << binfilename << endl;

	// Create the .h and .cpp files
	char hfilename[length+6];
	if(devtype ==1)
		sprintf(hfilename,"%s.h",name);
	else
		sprintf(hfilename,"%s_cpu.h",name);
	FILE * headerfile = fopen(hfilename, "w");
	if(!headerfile){
		cerr << "Could not open " << hfilename << " for writing, aborting!" << endl;
		return FAILURE;
	}

	char cfilename[length+8];
	if(devtype ==1)
		sprintf(cfilename,"%s.cpp",name);
	else
		sprintf(cfilename,"%s_cpu.cpp",name);
	FILE * sourcefile = fopen(cfilename, "w");
	if(!sourcefile){
		cerr << "Could not open " << cfilename << " for writing, aborting!" << endl;
		return FAILURE;
	}

	vector<Signature *> sigs = file.signatures();
	if(sigs.size() == 0){
		cerr << "No kernel signatures found, aborting!" << endl;
		return FAILURE;
	}


	// Some comments to begin with
	fprintf(headerfile,"/* %s  -- header for interface functions to the kernels\n", hfilename);
	fprintf(headerfile," defined in %s, the corresponding binaries are in %s\n", argv[2], binfilename);
	fprintf(headerfile," THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */\n\n");

	fprintf(sourcefile,"/* %s  -- source for interface functions to the kernels\n", hfilename);
	fprintf(sourcefile," defined in %s, the corresponding binaries are in %s\n", argv[2], binfilename);
	fprintf(sourcefile," THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */\n\n");


	char sdev[] = "GPU";
	if(devtype == 2)
		sprintf(sdev,"CPU");

	//include protection
	fprintf(headerfile,"#ifndef HH%s_%sHH\n", name, sdev);
	fprintf(headerfile,"#define HH%s_%sHH\n\n\n", name, sdev);

	// Include the header in the source file
	fprintf(sourcefile,"#include\"%s\"\n",hfilename);
	// More headers
	fprintf(headerfile,"#include\"Stream.h\"\n");
	fprintf(headerfile,"#include\"DeviceInterface.h\"\n");
	fprintf(sourcefile,"#include\"KernelFile.h\"\n");

	fprintf(sourcefile,"#include<vector>\n");
	fprintf(sourcefile,"#include<iostream>\n");
	fprintf(sourcefile,"#include<cassert>\n");


	// Create a namespace
	fprintf(headerfile,"\n\nnamespace %s_%s{\n\n", name, sdev);
	fprintf(sourcefile,"\n\nnamespace %s_%s{\n\n", name, sdev);

	// init the (unfortunately) global pointers to the kernels
	for(unsigned int i=0; i < sigs.size();i++){
		fprintf(sourcefile,"\t cl::Kernel * k_%s = 0;\n", sigs[i]->GetName().data());
	}

	// Create the prepare_kernels fuction
	fprintf(headerfile,"\t int prepare_kernels(const DeviceInterface * dev);\n\n");

	fprintf(sourcefile,"\t int prepare_kernels(const DeviceInterface * dev){\n");

	fprintf(sourcefile,"\t\t FILE * input = fopen(\"%s\",\"rb\");\n",binfilename);
	fprintf(sourcefile,"\t\t if(!input){\n");
	fprintf(sourcefile,"\t\t\t 	std::cerr << \"Loading binary file %s failed \\n\";\n", binfilename);
	fprintf(sourcefile,"\t\t\t 	return FAILURE;\n");
	fprintf(sourcefile,"\t\t }\n");
	fprintf(sourcefile,"\t\t fseek(input, 0L, SEEK_END);\n");
	fprintf(sourcefile,"\t\t size_t size = ftell(input);\n");
	fprintf(sourcefile,"\t\t rewind(input);\n");
	fprintf(sourcefile,"\t\t cl_int err;\n");
	fprintf(sourcefile,"\t\t char * binary = new char[size];\n");


	fprintf(sourcefile,"\t\t fread(binary, sizeof(char), size, input);\n");
	fprintf(sourcefile,"\t\t fclose(input);\n");

	fprintf(sourcefile,"\t\t cl::Program::Binaries binaries;\n");
	fprintf(sourcefile,"\t\t std::vector<int> binstatus;\n");
	fprintf(sourcefile,"\t\t for(unsigned int d=0; d < (*(dev->GetDevices())).size(); d++){\n");
	fprintf(sourcefile,"\t\t\t binstatus.push_back(0);\n");
	fprintf(sourcefile,"\t\t\t binaries.push_back(std::make_pair(binary, size));\n");
	fprintf(sourcefile,"\t\t }\n");
	fprintf(sourcefile,"\t\t cl::Program * bProgram = new cl::Program(*(dev->GetContext()),\n");
	fprintf(sourcefile,"\t\t 						   *(dev->GetDevices()),\n");
	fprintf(sourcefile,"\t\t 						   binaries,\n");
	fprintf(sourcefile,"\t\t 						   &binstatus,\n");
	fprintf(sourcefile,"\t\t 						   &err);\n");
	fprintf(sourcefile,"\t\t if (err != CL_SUCCESS) {\n");
	fprintf(sourcefile,"\t\t\t 	std::cerr << \"Loading binaries failed (\" << err << \")\\n\";\n");
	fprintf(sourcefile,"\t\t\t 	return FAILURE;\n");
	fprintf(sourcefile,"\t\t }\n");

	fprintf(sourcefile,"\t\t err = bProgram->build(*(dev->GetDevices()));\n");
	fprintf(sourcefile,"\t\t if (err != CL_SUCCESS) {\n");
	fprintf(sourcefile,"\t\t 	std::cerr << \"Program::build() failed (\" << err << \")\\n\";\n");
	fprintf(sourcefile,"\t\t 	return FAILURE;\n");
	fprintf(sourcefile,"\t\t }\n\n");


	for(unsigned int i=0; i < sigs.size();i++){
		//Global pointers to the kernels - not extremely elegant,
		// but slightly mitigated by the use of a namespace
		fprintf(headerfile,"\t extern cl::Kernel * k_%s;\n", sigs[i]->GetName().data());

		fprintf(sourcefile,"\t\t k_%s = new cl::Kernel(*bProgram, \"%s\", &err);\n", sigs[i]->GetName().data(), sigs[i]->GetName().data());
		fprintf(sourcefile,"\t\t if (err != CL_SUCCESS) {\n");
		fprintf(sourcefile,"\t\t\t std::cerr << \"Kernel::Kernel() failed (\" << err << \") for kernel %s\\n\";\n", sigs[i]->GetName().data());
		fprintf(sourcefile,"\t\t\t return FAILURE;\n");
		fprintf(sourcefile,"\t\t }\n\n");
	}

	fprintf(sourcefile,"\t return 0;\n");
	fprintf(sourcefile,"\t }\n\n\n\n");

	for(unsigned int i=0; i < sigs.size();i++){
		// Functions setting the arguments and executing the kernels,
		// this is the main purpose of the "compiler" in the first place:
		// providing a type safe way to interface the GPU
		if(evcount){
			fprintf(headerfile,"\t int %s(const cl::NDRange & range, const DeviceInterface * dev, ", sigs[i]->GetName().data());
			fprintf(sourcefile,"\t int %s(const cl::NDRange & range, const DeviceInterface * dev, ", sigs[i]->GetName().data());
		} else {
			fprintf(headerfile,"\t int %s(const DeviceInterface * dev, ", sigs[i]->GetName().data());
			fprintf(sourcefile,"\t int %s(const DeviceInterface * dev, ", sigs[i]->GetName().data());
		}
		vector<bool> ptype;
		for(unsigned int j=0; j < sigs[i]->GetTypes().size(); j++){
			string tname;
			size_t loc = sigs[i]->GetType(j).find('*');
			if(loc != string::npos){
				// Pointer type - use a stream; first remove the pointer '*'
				// which should be at the end of the string
				tname = sigs[i]->GetType(j);
				tname.erase(loc);
				tname.insert(0,"Stream<");
				tname.append("> *");
				ptype.push_back(true);
			} else {
				tname = sigs[i]->GetType(j);
				ptype.push_back(false);
			}

			fprintf(headerfile,"%s %s", tname.data(), sigs[i]->GetArgument(j).data());
			fprintf(sourcefile,"%s %s", tname.data(), sigs[i]->GetArgument(j).data());

			if(j < sigs[i]->GetTypes().size()-1){
				fprintf(headerfile,", ");
				fprintf(sourcefile,", ");
			}
		}

		//fprintf(headerfile,"std::vector<cl::Event> *evvec =0, cl::Event * event = 0);\n\n");
		//fprintf(sourcefile,"std::vector<cl::Event> *evvec, cl::Event * event){\n\n");

		fprintf(headerfile,");\n\n");
		fprintf(sourcefile,"){\n\n");


		fprintf(sourcefile,"\t\t cl_int err;\n");
		fprintf(sourcefile,"\t\t std::vector<cl::Event> *evvec = new std::vector<cl::Event>();\n");
		fprintf(sourcefile,"\t\t cl::Event event = cl::Event();\n\n");


		string firststream = "";

		for(unsigned int j=0; j < sigs[i]->GetTypes().size(); j++){
			if(ptype[j]){
				if(firststream=="")
					firststream = sigs[i]->GetArgument(j);
				if(!sigs[i]->IsOutput(j)){
					//fprintf(sourcefile,"\t\t if(%s->GetEvent()){\n",sigs[i]->GetArgument(j).data());
					//fprintf(sourcefile,"\t\t if(%s->GetEvent().getInfo<CL_EVENT_COMMAND_EXECUTION_STATUS>(&err) != CL_COMPLETE && err == CL_SUCCESS)\n",
					//								sigs[i]->GetArgument(j).data());
					unsigned int ifcount =0;
					for(unsigned int k = 0; k < j; k++){
						if(ptype[k] && sigs[i]->GetType(j) == sigs[i]->GetType(k)){
							fprintf(sourcefile,"\t\t");
							for(unsigned int x =0; x < ifcount; x++)
								fprintf(sourcefile,"\t");
							fprintf(sourcefile, "if(%s != %s)\n", sigs[i]->GetArgument(j).data(), sigs[i]->GetArgument(k).data());
							ifcount++;
						}
					}
					for(unsigned int x =0; x < ifcount; x++)
						fprintf(sourcefile,"\t");
					fprintf(sourcefile,"\t\t evvec->push_back((%s->GetEvent()));\n",  sigs[i]->GetArgument(j).data());
					//fprintf(sourcefile,"\t\t }\n");
				}
				fprintf(sourcefile,"\t\t err = k_%s->setArg(%i, *(*%s)());\n",
											sigs[i]->GetName().data(),
											j,
											sigs[i]->GetArgument(j).data());
			} else {
				fprintf(sourcefile,"\t\t err = k_%s->setArg(%i, %s);\n",
										sigs[i]->GetName().data(),
										j,
										sigs[i]->GetArgument(j).data());
			}
			fprintf(sourcefile,"\t\t if (err != CL_SUCCESS) {\n");
			fprintf(sourcefile,"\t\t\t std::cerr << \"Kernel.SetArg() failed (\" << err << \")\\n\";\n");
			fprintf(sourcefile,"\t\t\t assert(0);\n");
			fprintf(sourcefile,"\t\t\t return FAILURE;\n");
			fprintf(sourcefile,"\t\t }\n\n");
		}
		assert(firststream != "");

		if(evcount){
			fprintf(sourcefile,"\t\t err = dev->GetQueue()->enqueueNDRangeKernel(*k_%s, cl::NullRange, range, cl::NullRange, evvec, &event );\n",
						sigs[i]->GetName().data());
		} else {
			fprintf(sourcefile,"\t\t err = dev->GetQueue()->enqueueNDRangeKernel(*k_%s, cl::NullRange, cl::NDRange(%s->GetD1(),%s->GetD2()), cl::NullRange, evvec, &event );\n",
						sigs[i]->GetName().data(),
						firststream.data(),
						firststream.data());
		}
	//	fprintf(sourcefile,"\t\t std::cout << \"Started kernel %s with arguments \";\n",sigs[i]->GetName().data());
	//	for(unsigned int j=0; j < sigs[i]->GetTypes().size(); j++){
	//		if(ptype[j])
	//			fprintf(sourcefile,"\t\t std::cout << %s << \", \";\n", sigs[i]->GetArgument(j).data());
	//	}
	//	fprintf(sourcefile,"\t\t std::cout << std::endl;\n");
		fprintf(sourcefile,"\t\t if (err != CL_SUCCESS) {\n");
		fprintf(sourcefile,"\t\t\t std::cerr << \"CommandQueue::enqueueNDRangeKernel() failed (\" << err << \")\\n\";\n");
		fprintf(sourcefile,"\t\t\t assert(0);\n");
		fprintf(sourcefile,"\t\t\t return FAILURE;\n");
		fprintf(sourcefile,"\t\t }\n\n");

		for(unsigned int j=0; j < sigs[i]->GetTypes().size(); j++){
			if(sigs[i]->IsOutput(j) && ptype[j]){
			//	fprintf(sourcefile,"\t\t if(%s->GetEvent()){\n",sigs[i]->GetArgument(j).data());
			//	fprintf(sourcefile,"\t\t\t delete %s->GetEvent();\n",sigs[i]->GetArgument(j).data());
			//	fprintf(sourcefile,"\t\t\t %s->GetEvent() =0;\n",sigs[i]->GetArgument(j).data());
			//	fprintf(sourcefile,"\t\t }\n\n");
		/*		fprintf(sourcefile,"\t\t event.getInfo<CL_EVENT_COMMAND_EXECUTION_STATUS>(&err);\n");
				fprintf(sourcefile,"\t\t if (err != CL_SUCCESS) {\n");
				fprintf(sourcefile,"\t\t\t std::cerr << \"Event.getInfo() failed (\" << err << \")\\n\";\n");
				fprintf(sourcefile,"\t\t\t assert(0);\n");
				fprintf(sourcefile,"\t\t\t return FAILURE;\n");
				fprintf(sourcefile,"\t\t }\n\n");*/
				fprintf(sourcefile,"\t\t %s->SetEvent(event);\n\n", sigs[i]->GetArgument(j).data());
			}
		}

		// added by fucd
		fprintf(sourcefile,"\t\t delete evvec;\n");
		
		fprintf(sourcefile,"\t return 0;\n");
		fprintf(sourcefile,"\t }\n\n"); // end function

/*
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
*/
	}




	// End of namespace
	fprintf(headerfile,"}\n");
	fprintf(sourcefile,"}\n");

	// End of include-protetction
	fprintf(headerfile,"#endif\n");

	fclose(headerfile);
	fclose(sourcefile);

	return SUCCESS;
}
