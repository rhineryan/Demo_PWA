/*
 *  Makesumkernels.cpp
 *
 *  Produce kernels for summing over all kinds of data types
 *
 *  uses a rather wild mix of C++ and C I/O, both languages not particularly well
 *  suited to parsing and text generation...
 *
 *  Created on: Dec. 1st, 2010
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

#define FAILURE -1
#define SUCCESS 0

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;

int main(int argc, char* argv[]){

	cout << "OpenCL sum kernel generator" << endl;
	cout << "2010 Niklaus Berger, IHEP Beijing" << endl;

	if(argc < 2){
		cout << "Usage:" << endl;
		cout << "makesumkernels kernelfile" << endl;
		return -1;
	}

	char * suffix = strstr(argv[1], ".cl");
	if(suffix == NULL){
		cout << "Argument 2 should be a *.cl file" << endl;
		return -1;
	}
	char * name = argv[1];


	vector<string> xyzwelements;
	vector<string> cdefelements;
	vector<string> ccffelements;

	xyzwelements.push_back("x");
	xyzwelements.push_back("y");
	xyzwelements.push_back("z");
	xyzwelements.push_back("w");

	cdefelements.push_back("c");
	cdefelements.push_back("d");
	cdefelements.push_back("e");
	cdefelements.push_back("f");

	ccffelements.push_back("cc");
	ccffelements.push_back("cd");
	ccffelements.push_back("ce");
	ccffelements.push_back("cf");
	ccffelements.push_back("dc");
	ccffelements.push_back("dd");
	ccffelements.push_back("de");
	ccffelements.push_back("df");
	ccffelements.push_back("ec");
	ccffelements.push_back("ed");
	ccffelements.push_back("ee");
	ccffelements.push_back("ef");
	ccffelements.push_back("fc");
	ccffelements.push_back("fd");
	ccffelements.push_back("fe");
	ccffelements.push_back("ff");


	// List the types for summing
	vector<string> typenames;
	vector<unsigned int>    nelements;
	vector<bool> float4elements;

	// List the names of the elements
	vector<vector<string> *> elements;

	typenames.push_back("int");
	nelements.push_back(1);
	elements.push_back(0);
	float4elements.push_back(false);

	typenames.push_back("float");
	nelements.push_back(1);
	elements.push_back(0);
	float4elements.push_back(false);

	typenames.push_back("double");
	nelements.push_back(1);
	elements.push_back(0);
	float4elements.push_back(false);

	typenames.push_back("double2");
	nelements.push_back(2);
	elements.push_back(&xyzwelements);
	float4elements.push_back(false);

	typenames.push_back("float2");
	nelements.push_back(2);
	elements.push_back(&xyzwelements);
	float4elements.push_back(false);

	typenames.push_back("float4");
	nelements.push_back(4);
	elements.push_back(&xyzwelements);
	float4elements.push_back(false);

	typenames.push_back("float44");
	nelements.push_back(4);
	elements.push_back(&cdefelements);
	float4elements.push_back(true);

	typenames.push_back("float444");
	nelements.push_back(16);
	elements.push_back(&ccffelements);
	float4elements.push_back(true);


	// Create the .cl file
	FILE * clfile = fopen(name, "w");
	if(!clfile){
		cerr << "Could not open " <<  name << " for writing, aborting!" << endl;
		return FAILURE;
	}

	// Some comments to begin with
	fprintf(clfile,"/* %s  -- kernels for summing streams\n", name);
	fprintf(clfile," THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */\n\n");

	// Enable AMD's double precision extension
	fprintf(clfile,"#pragma OPENCL EXTENSION cl_amd_fp64 : enable\n\n");

	// Define our own structs
	fprintf(clfile,"#ifndef F44STRUCTS   \n");
	fprintf(clfile,"#define F44STRUCTS   \n\n");
	fprintf(clfile,"typedef struct {   \n");
	fprintf(clfile,"\t float4  c;\n");
	fprintf(clfile,"\t float4  d;\n");
	fprintf(clfile,"\t float4  e;\n");
	fprintf(clfile,"\t float4  f;\n");
	fprintf(clfile,"} float44;   \n");
	fprintf(clfile,"#endif   \n\n");

	fprintf(clfile,"#ifndef F444STRUCTS   \n");
	fprintf(clfile,"#define F444STRUCTS   \n");
	fprintf(clfile,"typedef struct {   \n");
	fprintf(clfile,"\t  float4  cc;  \n");
	fprintf(clfile,"\t  float4  cd;  \n");
	fprintf(clfile,"\t  float4  ce;  \n");
	fprintf(clfile,"\t  float4  cf;  \n");
	fprintf(clfile,"\t  float4  dc;  \n");
	fprintf(clfile,"\t  float4  dd;  \n");
	fprintf(clfile,"\t  float4  de;  \n");
	fprintf(clfile,"\t  float4  df;  \n");
	fprintf(clfile,"\t  float4  ec;  \n");
	fprintf(clfile,"\t  float4  ed;  \n");
	fprintf(clfile,"\t  float4  ee;  \n");
	fprintf(clfile,"\t  float4  ef;  \n");
	fprintf(clfile,"\t  float4  fc;  \n");
	fprintf(clfile,"\t  float4  fd;  \n");
	fprintf(clfile,"\t  float4  fe;  \n");
	fprintf(clfile,"\t  float4  ff;  \n");

	fprintf(clfile,"} float444;   \n\n");
	fprintf(clfile,"#endif \n\n");

	for(unsigned int i = 0; i < typenames.size();i++){
		// Write a kernel to sum all the components into one in blocks of 16
		fprintf(clfile, "__kernel void %s_sum_16(__global %s * in, __global out double * result){\n",typenames[i].data(), typenames[i].data());
		fprintf(clfile, "\t uint pos = get_global_id(0);\n");
		fprintf(clfile, "\t uint i;\n");
		fprintf(clfile, "\t double sum = 0.0;\n");
		fprintf(clfile, "\t for(i=0; i < 16; i++){\n");
		if(float4elements[i]){
			for(unsigned int j=0; j < nelements[i]; j++){
				if(elements[i]){
					fprintf(clfile, "\t\t sum += (double)(in[pos*16+i].%s.x);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t sum += (double)(in[pos*16+i].%s.y);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t sum += (double)(in[pos*16+i].%s.z);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t sum += (double)(in[pos*16+i].%s.w);\n",(*(elements[i]))[j].data());
				} else {
					fprintf(clfile, "\t\t sum += (double)(in[pos*16+i].x);\n");
					fprintf(clfile, "\t\t sum += (double)(in[pos*16+i].y);\n");
					fprintf(clfile, "\t\t sum += (double)(in[pos*16+i].z);\n");
					fprintf(clfile, "\t\t sum += (double)(in[pos*16+i].w);\n");
				}
			}
		} else {
			for(unsigned int j=0; j < nelements[i]; j++){
				if(elements[i])
					fprintf(clfile, "\t\t sum += (double)(in[pos*16+i].%s);\n",(*(elements[i]))[j].data());
				else
					fprintf(clfile, "\t\t sum += (double)(in[pos*16+i]);\n");
			}
		}
		fprintf(clfile, "\t }\n");
		fprintf(clfile, "\t result[pos] = sum;\n");
		fprintf(clfile, "}\n");



		// Write a kernel to sum all the components into one in blocks of N
		fprintf(clfile, "__kernel void %s_sum_N(__global %s * in, uint offset, uint resultoffset, uint n, __global out double * result){\n",typenames[i].data(), typenames[i].data());
		fprintf(clfile, "\t uint pos = get_global_id(0);\n");
		fprintf(clfile, "\t uint i;\n");
		fprintf(clfile, "\t double sum = 0.0;\n");
		fprintf(clfile, "\t for(i=0; i < n; i++){\n");
		if(float4elements[i]){
			for(unsigned int j=0; j < nelements[i]; j++){
				if(elements[i]){
					fprintf(clfile, "\t\t sum += (double)(in[pos*n+i+offset].%s.x);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t sum += (double)(in[pos*n+i+offset].%s.y);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t sum += (double)(in[pos*n+i+offset].%s.z);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t sum += (double)(in[pos*n+i+offset].%s.w);\n",(*(elements[i]))[j].data());
				} else {
					fprintf(clfile, "\t\t sum += (double)(in[pos*n+i+offset].x);\n");
					fprintf(clfile, "\t\t sum += (double)(in[pos*n+i+offset].y);\n");
					fprintf(clfile, "\t\t sum += (double)(in[pos*n+i+offset].z);\n");
					fprintf(clfile, "\t\t sum += (double)(in[pos*n+i+offset].w);\n");
				}
			}
		} else {
			for(unsigned int j=0; j < nelements[i]; j++){
				if(elements[i])
					fprintf(clfile, "\t\t sum += (double)(in[pos*n+i+offset].%s);\n",(*(elements[i]))[j].data());
				else
					fprintf(clfile, "\t\t sum += (double)(in[pos*n+i+offset]);\n");
			}
		}
		fprintf(clfile, "\t }\n");
		fprintf(clfile, "\t result[pos+resultoffset] = sum;\n");
		fprintf(clfile, "}\n");



		// Write a kernel to sum componentwise in blocks of 16
		unsigned int ne = nelements[i];
			if(float4elements[i])
				ne = ne*4;
		if(elements[i] && ne < 16){ // There is a limit to the number of kernel arguments on certain devices
			fprintf(clfile, "__kernel void %s_sumcomponents_16(__global %s * in",typenames[i].data(), typenames[i].data());
			for(unsigned int k = 0; k < ne; k++)
				fprintf(clfile, ", __global out double * result_%i",k);
			fprintf(clfile, "){\n");
			fprintf(clfile, "\t uint pos = get_global_id(0);\n");
			fprintf(clfile, "\t uint i;\n");
			for(unsigned int k = 0; k < ne; k++)
				fprintf(clfile, "\t double sum_%i = 0.0;\n",k);
			fprintf(clfile, "\t for(i=0; i < 16; i++){\n");
			if(float4elements[i]){
				for(unsigned int j=0; j < nelements[i]; j++){
					if(elements[i]){
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].%s.x);\n", j*4,   (*(elements[i]))[j].data());
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].%s.y);\n", j*4+1, (*(elements[i]))[j].data());
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].%s.z);\n", j*4+2, (*(elements[i]))[j].data());
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].%s.w);\n", j*4+3, (*(elements[i]))[j].data());
					} else {
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].x);\n", j*4  );
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].y);\n", j*4+1);
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].z);\n", j*4+2);
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].w);\n", j*4+3);
					}
				}
			} else {
				for(unsigned int j=0; j < nelements[i]; j++){
					if(elements[i])
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].%s);\n",j,(*(elements[i]))[j].data());
					else
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i]);\n",j);
				}
			}
			fprintf(clfile, "\t }\n");
			for(unsigned int k = 0; k < ne; k++)
				fprintf(clfile, "\t result_%i[pos] = sum_%i;\n",k,k);
			fprintf(clfile, "}\n\n\n");
		}

		// Write a kernel to sum componentwise in blocks of N
		if(elements[i] && ne < 16){ // There is a limit to the number of kernel arguments on certain devices
			fprintf(clfile, "__kernel void %s_sumcomponents_N(__global %s * in, uint offset, uint resultoffset, uint n",typenames[i].data(), typenames[i].data());
			for(unsigned int k = 0; k < ne; k++)
				fprintf(clfile, ", __global out double * result_%i",k);
			fprintf(clfile, "){\n");
			fprintf(clfile, "\t uint pos = get_global_id(0);\n");
			fprintf(clfile, "\t uint i;\n");
			for(unsigned int k = 0; k < ne; k++)
				fprintf(clfile, "\t double sum_%i = 0.0;\n",k);
			fprintf(clfile, "\t for(i=0; i < n; i++){\n");
			if(float4elements[i]){
				for(unsigned int j=0; j < nelements[i]; j++){
					if(elements[i]){
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i+offset].%s.x);\n", j*4,   (*(elements[i]))[j].data());
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i+offset].%s.y);\n", j*4+1, (*(elements[i]))[j].data());
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i+offset].%s.z);\n", j*4+2, (*(elements[i]))[j].data());
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i+offset].%s.w);\n", j*4+3, (*(elements[i]))[j].data());
					} else {
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i+offset].x);\n", j*4  );
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i+offset].y);\n", j*4+1);
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i+offset].z);\n", j*4+2);
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i+offset].w);\n", j*4+3);
					}
				}
			} else {
				for(unsigned int j=0; j < nelements[i]; j++){
					if(elements[i])
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i+offset].%s);\n",j,(*(elements[i]))[j].data());
					else
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i+offset]);\n",j);
				}
			}
			fprintf(clfile, "\t }\n");
			for(unsigned int k = 0; k < ne; k++)
				fprintf(clfile, "\t result_%i[pos+resultoffset] = sum_%i;\n",k,k);
			fprintf(clfile, "}\n\n\n");
		}


		// Write a kernel to sum componentwise in blocks of 16
		if(elements[i] && ne < 16){ // There is a limit to the number of kernel arguments on certain devices
			fprintf(clfile, "__kernel void %s_sumcomponents_weighted_16(__global %s * in, __global float * weights",typenames[i].data(), typenames[i].data());
			for(unsigned int k = 0; k < ne; k++)
				fprintf(clfile, ", __global out double * result_%i",k);
			fprintf(clfile, "){\n");
			fprintf(clfile, "\t uint pos = get_global_id(0);\n");
			fprintf(clfile, "\t uint i;\n");
			for(unsigned int k = 0; k < ne; k++)
				fprintf(clfile, "\t double sum_%i = 0.0;\n",k);
			fprintf(clfile, "\t for(i=0; i < 16; i++){\n");
			if(float4elements[i]){
				for(unsigned int j=0; j < nelements[i]; j++){
					if(elements[i]){
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].%s.x*weights[pos*16+i]);\n", j*4,   (*(elements[i]))[j].data());
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].%s.y*weights[pos*16+i]);\n", j*4+1, (*(elements[i]))[j].data());
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].%s.z*weights[pos*16+i]);\n", j*4+2, (*(elements[i]))[j].data());
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].%s.w*weights[pos*16+i]);\n", j*4+3, (*(elements[i]))[j].data());
					} else {
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].x*weights[pos*16+i]);\n", j*4  );
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].y*weights[pos*16+i]);\n", j*4+1);
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].z*weights[pos*16+i]);\n", j*4+2);
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].w*weights[pos*16+i]);\n", j*4+3);
					}
				}
			} else {
				for(unsigned int j=0; j < nelements[i]; j++){
					if(elements[i])
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i].%s*weights[pos*16+i]);\n",j,(*(elements[i]))[j].data());
					else
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*16+i]);\n",j);
				}
			}
			fprintf(clfile, "\t }\n");
			for(unsigned int k = 0; k < ne; k++)
				fprintf(clfile, "\t result_%i[pos] = sum_%i;\n",k,k);
			fprintf(clfile, "}\n\n\n");
		}

		// Write a kernel to sum componentwise in blocks of N
		if(elements[i] && ne < 16){ // There is a limit to the number of kernel arguments on certain devices
			fprintf(clfile, "__kernel void %s_sumcomponents_weighted_N(__global %s * in, __global float * weights, uint offset, uint resultoffset, uint n",typenames[i].data(), typenames[i].data());
			for(unsigned int k = 0; k < ne; k++)
				fprintf(clfile, ", __global out double * result_%i",k);
			fprintf(clfile, "){\n");
			fprintf(clfile, "\t uint pos = get_global_id(0);\n");
			fprintf(clfile, "\t uint i;\n");
			for(unsigned int k = 0; k < ne; k++)
				fprintf(clfile, "\t double sum_%i = 0.0;\n",k);
			fprintf(clfile, "\t for(i=0; i < n; i++){\n");
			if(float4elements[i]){
				for(unsigned int j=0; j < nelements[i]; j++){
					if(elements[i]){
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i].%s.x*weights[pos*n+i+offset]);\n", j*4,   (*(elements[i]))[j].data());
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i].%s.y*weights[pos*n+i+offset]);\n", j*4+1, (*(elements[i]))[j].data());
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i].%s.z*weights[pos*n+i+offset]);\n", j*4+2, (*(elements[i]))[j].data());
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i].%s.w*weights[pos*n+i+offset]);\n", j*4+3, (*(elements[i]))[j].data());
					} else {
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i].x*weights[pos*n+i+offset]);\n", j*4  );
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i].y*weights[pos*n+i+offset]);\n", j*4+1);
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i].z*weights[pos*n+i+offset]);\n", j*4+2);
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i].w*weights[pos*n+i+offset]);\n", j*4+3);
					}
				}
			} else {
				for(unsigned int j=0; j < nelements[i]; j++){
					if(elements[i])
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i].%s*weights[pos*n+i+offset]);\n",j,(*(elements[i]))[j].data());
					else
						fprintf(clfile, "\t\t sum_%i += (double)(in[pos*n+i+offset]);\n",j);
				}
			}
			fprintf(clfile, "\t }\n");
			for(unsigned int k = 0; k < ne; k++)
				fprintf(clfile, "\t result_%i[pos+resultoffset] = sum_%i;\n",k,k);
			fprintf(clfile, "}\n\n\n");
		}


		///////////

		// Write a kernel to sum all the components into one in blocks of 16 (2d array)
		fprintf(clfile, "__kernel void %s_sum2d_16(__global %s * in, uint d1, __global out double * result){\n",typenames[i].data(), typenames[i].data());
		fprintf(clfile, "\t uint pos = get_global_id(0);\n");
		fprintf(clfile, "\t uint i,j;\n");
		fprintf(clfile, "\t double sum;\n");
		fprintf(clfile, "\t for(j=0; j < d1; j++){\n");
		fprintf(clfile, "\t\t sum =0.0;\n");
		fprintf(clfile, "\t\t for(i=0; i < 16; i++){\n");
		if(float4elements[i]){
			for(unsigned int j=0; j < nelements[i]; j++){
				if(elements[i]){
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].%s.x);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].%s.y);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].%s.z);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].%s.w);\n",(*(elements[i]))[j].data());
				} else {
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].x);\n");
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].y);\n");
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].z);\n");
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].w);\n");
				}
			}
		} else {
			for(unsigned int j=0; j < nelements[i]; j++){
				if(elements[i])
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].%s);\n",(*(elements[i]))[j].data());
				else
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j]);\n");
			}
		}
		fprintf(clfile, "\t\t }\n");
		fprintf(clfile, "\t\t result[pos*d1+j] = sum;\n");
		fprintf(clfile, "\t}\n");
		fprintf(clfile, "}\n");


		// Write a kernel to sum all the components into one in blocks of N (2d array)
		fprintf(clfile, "__kernel void %s_sum2d_N(__global %s * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){\n",typenames[i].data(), typenames[i].data());
		fprintf(clfile, "\t uint pos = get_global_id(0);\n");
		fprintf(clfile, "\t uint i,j;\n");
		fprintf(clfile, "\t double sum;\n");
		fprintf(clfile, "\t for(j=0; j < d1; j++){\n");
		fprintf(clfile, "\t\t sum =0.0;\n");
		fprintf(clfile, "\t\t for(i=0; i < n; i++){\n");
		if(float4elements[i]){
			for(unsigned int j=0; j < nelements[i]; j++){
				if(elements[i]){
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].%s.x);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].%s.y);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].%s.z);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].%s.w);\n",(*(elements[i]))[j].data());
				} else {
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].x);\n");
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].y);\n");
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].z);\n");
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].w);\n");
				}
			}
		} else {
			for(unsigned int j=0; j < nelements[i]; j++){
				if(elements[i])
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].%s);\n",(*(elements[i]))[j].data());
				else
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset]);\n");
			}
		}
		fprintf(clfile, "\t\t }\n");
		fprintf(clfile, "\t\t result[pos*d1+j+resultoffset] = sum;\n");
		fprintf(clfile, "\t}\n");
		fprintf(clfile, "}\n");


		//////////////////////////////////////////////////////

		// Write a kernel to sum all the components weighted into one in blocks of 16 (2d array)
		fprintf(clfile, "__kernel void %s_sum2d_16_weighted(__global float4 * weights, __global %s * in, uint d1, __global out double * result){\n",typenames[i].data(), typenames[i].data());
		fprintf(clfile, "\t uint pos = get_global_id(0);\n");
		fprintf(clfile, "\t uint i,j;\n");
		fprintf(clfile, "\t double sum;\n");
		fprintf(clfile, "\t for(j=0; j < d1; j++){\n");
		fprintf(clfile, "\t\t sum =0.0;\n");
		fprintf(clfile, "\t\t for(i=0; i < 16; i++){\n");
		if(float4elements[i]){
			for(unsigned int j=0; j < nelements[i]; j++){
				if(elements[i]){
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].%s.x*weights[pos*16+i].x);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].%s.y*weights[pos*16+i].y);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].%s.z*weights[pos*16+i].z);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].%s.w*weights[pos*16+i].w);\n",(*(elements[i]))[j].data());
				} else {
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].x*weights[pos*16+i].x);\n");
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].y*weights[pos*16+i].y);\n");
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].z*weights[pos*16+i].z);\n");
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].w*weights[pos*16+i].w);\n");
				}
			}
		} else {
			for(unsigned int j=0; j < nelements[i]; j++){
				if(elements[i])
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j].%s);\n",(*(elements[i]))[j].data());
				else
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*16*d1+i*d1+j]);\n");
			}
		}
		fprintf(clfile, "\t\t }\n");
		fprintf(clfile, "\t\t result[pos*d1+j] = sum;\n");
		fprintf(clfile, "\t}\n");
		fprintf(clfile, "}\n");


		// Write a kernel to sum all the components weighted into one in blocks of N (2d array)
		fprintf(clfile, "__kernel void %s_sum2d_N_weighted(__global float4 * weights,__global %s * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){\n",typenames[i].data(), typenames[i].data());
		fprintf(clfile, "\t uint pos = get_global_id(0);\n");
		fprintf(clfile, "\t uint i,j;\n");
		fprintf(clfile, "\t double sum;\n");
		fprintf(clfile, "\t for(j=0; j < d1; j++){\n");
		fprintf(clfile, "\t\t sum =0.0;\n");
		fprintf(clfile, "\t\t for(i=0; i < n; i++){\n");
		if(float4elements[i]){
			for(unsigned int j=0; j < nelements[i]; j++){
				if(elements[i]){
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].%s.x*weights[pos*n+i].x);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].%s.y*weights[pos*n+i].y);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].%s.z*weights[pos*n+i].z);\n",(*(elements[i]))[j].data());
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].%s.w*weights[pos*n+i].w);\n",(*(elements[i]))[j].data());
				} else {
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].x*weights[pos*n+i].x);\n");
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].y*weights[pos*n+i].y);\n");
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].z*weights[pos*n+i].z);\n");
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].w*weights[pos*n+i].w);\n");
				}
			}
		} else {
			for(unsigned int j=0; j < nelements[i]; j++){
				if(elements[i])
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset].%s);\n",(*(elements[i]))[j].data());
				else
					fprintf(clfile, "\t\t\t sum += (double)(in[pos*n*d1+i*d1+j+offset]);\n");
			}
		}
		fprintf(clfile, "\t\t }\n");
		fprintf(clfile, "\t\t result[pos*d1+j+resultoffset] = sum;\n");
		fprintf(clfile, "\t}\n");
		fprintf(clfile, "}\n");

	}

	fclose(clfile);

	return SUCCESS;
}
