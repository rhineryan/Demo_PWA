#include "GPUMetricTensor.h"

GPUMetricTensor::GPUMetricTensor(void)
{

	mdata[0].c = mfloat4(-1.0f,0.0f,0.0f,0.0f);
	mdata[0].d = mfloat4(0.0f,-1.0f,0.0f,0.0f);
	mdata[0].e = mfloat4(0.0f,0.0f,-1.0f,0.0f);
	mdata[0].f = mfloat4(0.0f,0.0f,0.0f,1.0f);
}

GPUMetricTensor::~GPUMetricTensor(void)
{
}
