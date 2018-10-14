/*
 * GPURuncounter.cpp
 *
 *  Created on: Dec 3, 2008
 *      Author: nberger
 */

#include "GPURuncounter.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

GPURuncounter::~GPURuncounter() {
	delete [] mname;
}
GPURuncounter::GPURuncounter(char * name) {
	mruncounter = 0;
	mfitcounter = 0;

	mname = new char[strlen(name)+13];
	sprintf(mname,"%s_counter.cnt",name);

	ifstream infile;
	infile.open(mname);
	if(!infile){ // file does not exist, create it
		ofstream outfile(mname);
		if(!outfile){
			cout << "ERROR: Cannot create file " << mname << endl;
		} else {
			outfile << "1" << endl;
			outfile << "0" << endl;
			outfile.close();
		}
	} else {
		infile >> mruncounter;
		infile >> mfitcounter;
		if(infile.bad()){
			cout << "ERROR reading from file " << mname << endl;
		} else {
			mruncounter++;
			WriteFile();
		}
	}
}

void GPURuncounter::ReadFile() const{
	mruncounter = 0;
	mfitcounter = 0;
	ifstream infile;
	infile.open(mname);
	if(!infile){ // file does not exist, abort
		cout << "ERROR: Cannot read file " << mname << endl;
		return;
	} else {
		infile >> mruncounter;
		infile >> mfitcounter;
		if(infile.bad()){
			cout << "ERROR reading from file " << mname << endl;
		}
	}
}

void GPURuncounter::WriteFile(){
	ofstream outfile(mname);
	if(!outfile){
		cout << "ERROR: Cannot create file " << mname << endl;
	} else {
		outfile << mruncounter << endl;
		outfile << mfitcounter << endl;
		outfile.close();
	}
}

GPURuncounter * GPURuncounter::GetInstance(char * name) {
	if(minstance ==0)
		minstance = new GPURuncounter(name);
	return minstance;
}

GPURuncounter * GPURuncounter::minstance =0;
