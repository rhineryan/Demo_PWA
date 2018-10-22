/*
 * GPUIndexStream.cpp
 *
 *  Created on: Sep 8, 2009
 *      Author: nberger
 */

#include "GPUIndexStream.h"

GPUIndexStream::GPUIndexStream(const DeviceInterface * dev, unsigned int n, unsigned int stride):GPUDataStream<float>(dev,n) {
	  float * temp = new float[n];
	  for(unsigned int i=0; i < n; i++)
	    temp[i] = (float)(i*stride);
	  this->Write(temp);
	  delete [] temp;
}

GPUIndexStream::~GPUIndexStream() {}


GPU2DIndexStream::GPU2DIndexStream(const DeviceInterface * dev, unsigned int n, unsigned int m, unsigned int stride):GPUDataStream<float2>(dev, n,m) {
	float2 * temp = (float2 *)(new float[n*m*2]);
	for(unsigned int i=0; i < n; i++){
		for(unsigned int j=0; j < m; j++){
	      temp[i+j*n].x = (float)(i*stride);
	      temp[i+j*n].y = (float)(j);
	    }
	  }
	  this->Write(temp);
	  delete [] temp;
}

GPUGradientIndexStream::GPUGradientIndexStream(const DeviceInterface * dev, std::vector<int> pnums):GPUDataStream<int>(dev, pnums.size()){
	unsigned int d2  = pnums.size();
	bool addminus =false;
	if(pnums[0] == 0)
		addminus = true;
	int * temp = new int[d2];
	for(unsigned int j=0; j < d2; j++){
		int k = pnums[j];
		if(j==0 && addminus)
			k = -1;
		temp[j] = k;

	}
	this->Write(temp);
	mevent.wait();
	delete temp;
}



GPU2DIndexStream::~GPU2DIndexStream() {}

GPUGradientIndexStream::~GPUGradientIndexStream() {}

GPU3DIndexStream::GPU3DIndexStream(const DeviceInterface * dev, unsigned int n, unsigned int m):GPUDataStream<float3>(dev, n, (m+1)*m/2) {
	float3 * temp = (float3*)new float[3*n*(m+1)*m/2];
	for(unsigned int i=0; i < n; i++){
		unsigned int b =0;
		for(unsigned int j=0; j < m; j++){
			for(unsigned int k=j; k < m; k++){
				temp[i+b*n] = mfloat3(i,j,k);
				b++;
			}
		}
	}

	this->Read(temp);
	delete [] temp;
}



GPU3DIndexStream::~GPU3DIndexStream() {}

