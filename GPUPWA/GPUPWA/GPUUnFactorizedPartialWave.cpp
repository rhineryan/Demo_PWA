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
GPUUnFactorizedPartialWave<T>::GPUUnFactorizedPartialWave(
								  GPUPropagatorType<T> & _propagator,
								  char * _name):
								  GPUPartialWave(_propagator.GetParset(),
								  _propagator.GetNPars(),_name, _propagator.GetNSets()),
mPropagator(_propagator)
{
	for(unsigned int i=2; i < _propagator.GetNPars()+2; i++){
		mparnames[i] = _propagator.GetParameterNames()[i-2];
		mparindices[i] = _propagator.GetParameters()[i-2];
		//mlastvalues[i] = _propagator.GetLastValues()[i-2];
		for(unsigned int s=0; s <mnsets; s++)
			mlastvalues[s][i] = _propagator.GetLastValues(s)[i-2];
		//cout <<  "Creating wave " << _propagator.GetLastValues()[i-2] << endl;
	}
}

template <typename T>
GPUUnFactorizedPartialWave<T>::~GPUUnFactorizedPartialWave(void)
{
}

template <>
GPUDataStream<float2> * GPUUnFactorizedPartialWave<float>::Contract(GPUPartialWave * wave2, unsigned int streamindex, unsigned int block){
	int length = mPropagator.GetLength(streamindex,block);
	GPUDataStream<float2> * aiaj = new GPUDataStream<float2>(mPropagator.GetList()->GetDeviceInterface(), length);

	GPUFactorizedPartialWave<float> * castwave2 = dynamic_cast<GPUFactorizedPartialWave<float> *>(wave2);
	if(castwave2){
		kernelcontractscalar_u_f(mPropagator.GetList()->GetDeviceInterface(),
							 mPropagator(streamindex,block),
							 castwave2->GetTensor()(streamindex,block),
							 castwave2->GetPropagator()(streamindex,block),
							 aiaj);
		return aiaj;
	}

	GPUUnFactorizedPartialWave<float> * ucastwave2 = dynamic_cast<GPUUnFactorizedPartialWave<float> *>(wave2);
	if(ucastwave2){
		kernelcontractscalar_u_u(mPropagator.GetList()->GetDeviceInterface(),
								mPropagator(streamindex,block),
								(ucastwave2->GetPropagator())(streamindex,block),
								aiaj);
		return aiaj;
	}

	cout << "Contraction for this combination of wave types not implemented, aborting!" << endl;
	exit(-1);

	// Dummy statement to avoid compiler warnings
	return aiaj;
}



template <>
GPUDataStream<float2> * GPUUnFactorizedPartialWave<float4>::Contract(GPUPartialWave * wave2, unsigned int streamindex, unsigned int block){
	int length = mPropagator.GetLength(streamindex,block);
	GPUDataStream<float2> * aiaj = new GPUDataStream<float2>(mPropagator.GetList()->GetDeviceInterface(), length);

	GPUFactorizedPartialWave<float4> * castwave2 = dynamic_cast<GPUFactorizedPartialWave<float4> *>(wave2);
	if(castwave2){
		kernelcontractmesons_v_s(mPropagator.GetList()->GetDeviceInterface(),
				                 castwave2->GetTensor()(streamindex,block),
				                 mPropagator.realpart(streamindex,block),
				                 mPropagator.imagpart(streamindex,block),
				                 castwave2->GetPropagator()(streamindex,block),
				                 aiaj);
		return aiaj;
	}

	GPUUnFactorizedPartialWave<float4> * ucastwave2 = dynamic_cast<GPUUnFactorizedPartialWave<float4> *>(wave2);
	if(ucastwave2){
		kernelcontractmesons_v_v(mPropagator.GetList()->GetDeviceInterface(),
								mPropagator.realpart(streamindex,block),
								mPropagator.imagpart(streamindex,block),
								ucastwave2->GetPropagator().realpart(streamindex,block),
								ucastwave2->GetPropagator().imagpart(streamindex,block),
								aiaj);
		return aiaj;
	}

	cout << "Contraction for this combination of wave types not implemented, aborting!" << endl;
	exit(-1);

	// Dummy statement to avoid compiler warnings
	return aiaj;
}

// dummy function, overriden by derived classes
template <>
GPUDataStream<float2> * GPUUnFactorizedPartialWave<float44>::Contract(GPUPartialWave * wave2, unsigned int streamindex, unsigned int block){
	assert(0);
	return 0;
}

template class GPUUnFactorizedPartialWave<float>;
template class GPUUnFactorizedPartialWave<float4>;
template class GPUUnFactorizedPartialWave<float44>;
