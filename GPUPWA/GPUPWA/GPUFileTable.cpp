/*
 * GPUFileTable.cpp
 *
 *  Created on: Apr 24, 2009
 *      Author: nberger
 */

#include "GPUFileTable.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

using std::ifstream;
using std::cout;
using std::endl;
using std::string;

template <typename T>
GPUFileTable<T>::GPUFileTable(const char * filename, int nelements): mnelements(nelements) {
	mok = false;
	ifstream input(filename);
	if(input.fail()){
		cout << "Error opening " << filename << endl;
		return;
	}
	// count lines in the file
	mnevents =0;
	string line;
	while(!input.eof()) {
		getline(input,line);
		mnevents++;
	}
	input.seekg(0);

	// reserve memory
	mdata = new T*[mnelements];
	for(unsigned int i=0; i < mnelements; i++)
		mdata[i] = (T*)(new float[mnevents*datasize()]);



	for(unsigned int line =0; line < mnevents; line++){
		for(unsigned int element =0; element < mnelements; element++){
			for(unsigned int i =0; i < datasize(); i++){
				// This is not particularly nice, but should work with all the
				// data classes in GPUPWA (and has the advantage of being fast)
				input >> ((float*)&(mdata[element][line]))[i];
			}
			if(input.fail()){
				cout << "Error reading " << filename << endl;
				return;
			}
		}
	}
	if(input.eof())
		mok = true;
}

template <typename T>
GPUFileTable<T>::~GPUFileTable() {
	for(unsigned int i=0; i < mnelements; i++)
		delete[] mdata[i];
	delete[] mdata;
}

template <typename T>
unsigned int GPUFileTable<T>::datasize(){
	return sizeof(T)/sizeof(float);
}


//template <>
GPUFileTable<float4444>::GPUFileTable(const char * filename, int nelements): mnelements(nelements) {
	mok = false;
	ifstream input(filename);
	if(input.fail()){
		cout << "Error opening " << filename << endl;
		return;
	}
	// count lines in the file
	mnevents =0;
	string line;
	while(!input.eof()) {
		getline(input,line);
		mnevents++;
	}
	input.seekg(0);

	// reserve memory
	mdata = new float44*[mnelements*16];
	for(unsigned int i=0; i < mnelements*16; i++)
		mdata[i] = (float44*)(new float[mnevents*16]);



	for(unsigned int line =0; line < mnevents; line++){
		for(unsigned int element =0; element < mnelements; element++){
			for(unsigned int j =0; j < 16; j++){
				for(unsigned int i =0; i < 16; i++){
					// This is not particularly nice, but should work with all the
					// data classes in GPUPWA (and has the advantage of being fast)
					input >> ((float*)&(mdata[16*element+j][line]))[i];
				}
				if(input.fail()){
					cout << "Error reading " << filename << endl;
					return;
				}
			}
		}
	}
	if(input.eof())
		mok = true;

}

GPUFileTable<float4444>::~GPUFileTable() {
	for(unsigned int i=0; i < mnelements*16; i++)
		delete[] mdata[i];
	delete[] mdata;
}


unsigned int GPUFileTable<float4444>::datasize(){
	return sizeof(float4444)/sizeof(float);
}
