#include "GPUFactorizedPartialWave.h"
#include "GPUUnFactorizedPartialWave.h"
#include <cstring>

#ifdef USECPU
#include "Contractions_cpu.h"
using namespace Contractions_CPU;
#else
#include "Contractions.h"
using namespace Contractions_GPU;
#endif

template <typename T>
GPUFactorizedPartialWave<T>::GPUFactorizedPartialWave(GPUStreamTensor<T> & _orbitalTensor,
								  GPUScalarPropagator & _propagator,
								  char * _name):
								  GPUPartialWave(_propagator.GetParset(),
								  _propagator.GetNPars(),_name, _orbitalTensor.GetNSets()),
mOrbitalTensor(_orbitalTensor),
mPropagator(_propagator)
{
	for(unsigned int i=2; i < _propagator.GetNPars()+2; i++){
		mparnames[i] = _propagator.GetParameterNames()[i-2];
		mparindices[i] = _propagator.GetParameters()[i-2];
		for(unsigned int s=0; s <mnsets; s++)
			mlastvalues[s][i] = _propagator.GetLastValues(s)[i-2];
		//cout <<  "Creating wave " << _propagator.GetLastValues()[i-2] << endl;
	}
}

template <typename T>
GPUFactorizedPartialWave<T>::~GPUFactorizedPartialWave(void)
{
	delete[] mName;
}

template <>
GPUDataStream<float2> * GPUFactorizedPartialWave<float>::Contract(GPUPartialWave * wave2, unsigned int streamindex, unsigned int block){
	int length = mOrbitalTensor.GetLength(streamindex,block);
	GPUDataStream<float2> * aiaj = new GPUDataStream<float2>(mOrbitalTensor.GetList()->GetDeviceInterface(), length);

	GPUFactorizedPartialWave<float> * castwave2 = dynamic_cast<GPUFactorizedPartialWave<float> *>(wave2);
	if(castwave2){
		kernelcontractscalar(mOrbitalTensor.GetList()->GetDeviceInterface(),
							mOrbitalTensor(streamindex,block),
							(castwave2->GetTensor())(streamindex,block),
							mPropagator(streamindex,block),
							(castwave2->GetPropagator())(streamindex,block),
							aiaj);
		ValidateCache();
		castwave2->ValidateCache();
		return aiaj;
	}

	GPUUnFactorizedPartialWave<float> * ucastwave2 = dynamic_cast<GPUUnFactorizedPartialWave<float> *>(wave2);
	if(ucastwave2){
		kernelcontractscalar_f_u(mOrbitalTensor.GetList()->GetDeviceInterface(),
									mOrbitalTensor(streamindex,block),
									mPropagator(streamindex,block),
									ucastwave2->GetPropagator()(streamindex,block),
									aiaj);
		ValidateCache();
		ucastwave2->ValidateCache();
		return aiaj;
	}

	cout << "Contraction for this combination of wave types not implemented, aborting!" << endl;
	exit(-1);

	// Dummy statement to avoid compiler warnings
	return aiaj;
}

template <>
GPUDataStream<float2> * GPUFactorizedPartialWave<float4>::Contract(GPUPartialWave * wave2, unsigned int streamindex, unsigned int block){
	int length = mOrbitalTensor.GetLength(streamindex,block);
	GPUDataStream<float2> * aiaj = new GPUDataStream<float2>(mOrbitalTensor.GetList()->GetDeviceInterface(), length);

	GPUFactorizedPartialWave<float4> * castwave2 = dynamic_cast<GPUFactorizedPartialWave<float4> *>(wave2);
	if(castwave2){
		kernelcontractmesons(mOrbitalTensor.GetList()->GetDeviceInterface(),
							mOrbitalTensor(streamindex,block),
							(castwave2->GetTensor())(streamindex,block),
							mPropagator(streamindex,block),
							(castwave2->GetPropagator())(streamindex,block),
							aiaj);
		ValidateCache();
		castwave2->ValidateCache();
		return aiaj;
	}

	GPUUnFactorizedPartialWave<float4> * ucastwave2 = dynamic_cast<GPUUnFactorizedPartialWave<float4> *>(wave2);
	if(ucastwave2){
		kernelcontractmesons_s_v(mOrbitalTensor.GetList()->GetDeviceInterface(),
									mOrbitalTensor(streamindex,block),
									mPropagator(streamindex,block),
									(ucastwave2->GetPropagator().realpart(streamindex,block)),
									(ucastwave2->GetPropagator().imagpart(streamindex,block)),
									aiaj);
		ValidateCache();
		ucastwave2->ValidateCache();
		return aiaj;
	}

	cout << "Contraction for this combination of wave types not implemented, aborting!" << endl;
	exit(-1);

	// Dummy statement to avoid compiler warnings
	return aiaj;
}

/// Dummy fuctions, overridden by derived classes but neede in linking
template <>
GPUDataStream<float2> * GPUFactorizedPartialWave<float44>::Contract(GPUPartialWave * wave2, unsigned int streamindex, unsigned int block){
	assert(0);
	return 0;
}

template <>
GPUDataStream<float> * GPUFactorizedPartialWave<float44>::ContractOrbital(GPUPartialWave * wave2, unsigned int streamindex, unsigned int block){
	assert(0);
	return 0;
}

template <>
GPUDataStream<float> * GPUFactorizedPartialWave<float>::ContractOrbital(GPUPartialWave * wave2, unsigned int streamindex, unsigned int block){
	int length = mOrbitalTensor.GetLength(streamindex,block);
	GPUDataStream<float> * aiaj = new GPUDataStream<float>(mOrbitalTensor.GetList()->GetDeviceInterface(), length);

	GPUFactorizedPartialWave<float> * castwave2 = dynamic_cast<GPUFactorizedPartialWave<float> *>(wave2);
	if(castwave2){
		kernelcontractscalarorbital(mOrbitalTensor.GetList()->GetDeviceInterface(),
							mOrbitalTensor(streamindex,block),
							(castwave2->GetTensor())(streamindex,block),
							aiaj);
		return aiaj;
	}

	return 0;
}

template <>
GPUDataStream<float> * GPUFactorizedPartialWave<float4>::ContractOrbital(GPUPartialWave * wave2, unsigned int streamindex, unsigned int block){
	int length = mOrbitalTensor.GetLength(streamindex,block);
	GPUDataStream<float> * aiaj = new GPUDataStream<float>(mOrbitalTensor.GetList()->GetDeviceInterface(), length);

	GPUFactorizedPartialWave<float4> * castwave2 = dynamic_cast<GPUFactorizedPartialWave<float4> *>(wave2);
	if(castwave2){
		kernelcontractmesonsorbital(mOrbitalTensor.GetList()->GetDeviceInterface(),
							mOrbitalTensor(streamindex,block),
							(castwave2->GetTensor())(streamindex,block),
							aiaj);
		return aiaj;
	}

	return 0;
}

/// Check whether a wave combination has a parameter independent part
template <>
bool GPUFactorizedPartialWave<float>::HasContractOrbital(GPUPartialWave * wave){
	GPUFactorizedPartialWave<float> * castwave2 = dynamic_cast<GPUFactorizedPartialWave<float> *>(wave);
	if(castwave2){
		return true;
	}
	return false;

}


/// Check whether a wave combination has a parameter independent part
template <>
bool GPUFactorizedPartialWave<float4>::HasContractOrbital(GPUPartialWave * wave){
	GPUFactorizedPartialWave<float4> * castwave2 = dynamic_cast<GPUFactorizedPartialWave<float4> *>(wave);
	if(castwave2){
		return true;
	}
	return false;
}

template <>
bool GPUFactorizedPartialWave<float44>::HasContractOrbital(GPUPartialWave * wave){
	GPUFactorizedPartialWave<float44> * castwave2 = dynamic_cast<GPUFactorizedPartialWave<float44> *>(wave);
	if(castwave2){
		return true;
	}
	return false;
}

template class GPUFactorizedPartialWave<float>;
template class GPUFactorizedPartialWave<float4>;
template class GPUFactorizedPartialWave<float44>;
//template class GPUPartialWave<float44>;
