/*
 * GPUFactorizedRadiativePartialWave.cpp
 *
 *  Created on: May 9, 2011
 *      Author: nberger
 */

#include "GPUFactorizedRadiativePartialWave.h"
#include "GPUUnFactorizedRadiativePartialWave.h"

#ifdef USECPU
#include "Contractions_cpu.h"
using namespace Contractions_CPU;
#else
#include "Contractions.h"
using namespace Contractions_GPU;
#endif


GPUFactorizedRadiativePartialWave::GPUFactorizedRadiativePartialWave(GPUStreamTensor<float44> & _orbitalTensor,
																	 GPUScalarPropagator & _propagator,
																	 char * _name):
																	 GPUFactorizedPartialWave<float44>(_orbitalTensor,
																			 _propagator, _name)
{


}

GPUFactorizedRadiativePartialWave::~GPUFactorizedRadiativePartialWave() {

}


GPUDataStream<float2> * GPUFactorizedRadiativePartialWave::Contract(GPUPartialWave * wave2, unsigned int streamindex, unsigned int block){
	unsigned int length = mOrbitalTensor.GetLength(streamindex,block);
	GPUDataStream<float2> * aiaj = new GPUDataStream<float2>(mOrbitalTensor.GetList()->GetDeviceInterface(), length);

	//cout << "In contract: length " << length << " streamindex "<< streamindex <<" block " << block << endl;

  //cout<<"XXXXX--I am in contract part-a"<<endl;
	GPUFactorizedRadiativePartialWave * castwave2 = dynamic_cast<GPUFactorizedRadiativePartialWave *>(wave2);
	if(castwave2){
    //cout<<"IIbg: "<<"wave1 "<<this->GetName()<<'\t'<<"  wave2 "<<wave2->GetName()<<endl;
		kernelcontractradmesons (mOrbitalTensor.GetList()->GetDeviceInterface(),
								mOrbitalTensor(streamindex,block),
								(castwave2->GetTensor())(streamindex,block),
								(*mg_perp_stream)(streamindex,block),
								mPropagator(streamindex,block),
								(castwave2->GetPropagator())(streamindex,block),
								aiaj);
    //cout<<"IIend: "<<"wave1 "<<this->GetName()<<'\t'<<"  wave2 "<<wave2->GetName()<<endl;
		return aiaj;
	}
  cout<<"XXXXX--I am in contract part-b"<<endl;

	GPUUnFactorizedRadiativePartialWave * ucastwave2 = dynamic_cast<GPUUnFactorizedRadiativePartialWave *>(wave2);
	if(ucastwave2){
		kernelcontractradmesons_f_u(mOrbitalTensor.GetList()->GetDeviceInterface(),
									mOrbitalTensor(streamindex,block),
									mPropagator(streamindex,block),
									(*mg_perp_stream)(streamindex,block),
									(ucastwave2->GetPropagator().realpart(streamindex,block)),
									(ucastwave2->GetPropagator().imagpart(streamindex,block)),
									aiaj);
		return aiaj;
	}
  cout<<"XXXXX--I am in contract part-c"<<endl;

	cout << "Contraction for this combination of wave types not implemented, aborting!" << endl;
	exit(-1);

	// Dummy statement to avoid compiler warnings
	return aiaj;
}


GPUDataStream<float> * GPUFactorizedRadiativePartialWave::ContractOrbital(GPUPartialWave * wave2, unsigned int streamindex, unsigned int block){
	unsigned int length = mOrbitalTensor.GetLength(streamindex,block);
	GPUDataStream<float> * aiaj = new GPUDataStream<float>(mOrbitalTensor.GetList()->GetDeviceInterface(), length);

	GPUFactorizedRadiativePartialWave * castwave2 = dynamic_cast<GPUFactorizedRadiativePartialWave *>(wave2);
	if(castwave2){
		kernelcontractradmesonsorbital(mOrbitalTensor.GetList()->GetDeviceInterface(),
								mOrbitalTensor(streamindex,block),
								(castwave2->GetTensor())(streamindex,block),
								(*mg_perp_stream)(streamindex,block),
								aiaj);
		return aiaj;
	}

	return 0;
}


/// Check whether a wave combination has a parameter independent part
bool GPUFactorizedRadiativePartialWave::HasContractOrbital(GPUPartialWave * wave){
	GPUFactorizedRadiativePartialWave * castwave2 = dynamic_cast<GPUFactorizedRadiativePartialWave *>(wave);
	if(castwave2)
		return true;

	return false;
}
