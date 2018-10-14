#include "GPUPWACalculator.h"
#include <cassert>

GPUPWACalculator::GPUPWACalculator(GPUPartialWaveAnalysis * _ana,  std::vector<GPUDataStream<float4> **> _Weights):
	mAna(_ana), mdev(_ana->GetDeviceInterface()), mWeights(_Weights)
{
}


GPUPWACalculator::~GPUPWACalculator(void)
{
}




