/*
 * GPUUnFactorizedRadiativePartialWave.cpp
 *
 *  Created on: May 9, 2011
 *      Author: nberger
 */

#include "GPUUnFactorizedRadiativePartialWave.h"
#include "GPUFactorizedRadiativePartialWave.h"

#ifdef USECPU
#include "Contractions_cpu.h"
using namespace Contractions_CPU;
#else
#include "Contractions.h"
using namespace Contractions_GPU;
#endif

GPUUnFactorizedRadiativePartialWave::GPUUnFactorizedRadiativePartialWave(GPUPropagatorType<float44> & _propagator, char * _name):
	GPUUnFactorizedPartialWave<float44>(_propagator, _name)
{

}

GPUUnFactorizedRadiativePartialWave::~GPUUnFactorizedRadiativePartialWave() {
}


GPUDataStream<float2> * GPUUnFactorizedRadiativePartialWave::Contract(GPUPartialWave * wave2, unsigned int streamindex, unsigned int block){
	int length = mPropagator.GetLength(streamindex,block);
	GPUDataStream<float2> * aiaj = new GPUDataStream<float2>(mPropagator.GetList()->GetDeviceInterface(), length);

	GPUUnFactorizedRadiativePartialWave * castwave2 = dynamic_cast<GPUUnFactorizedRadiativePartialWave *>(wave2);
	if(castwave2){
		kernelcontract3radmesons( mPropagator.GetList()->GetDeviceInterface(),
								 (*mg_perp_stream)(streamindex,block),
							 	  mPropagator.realpart(streamindex,block),
							 	  mPropagator.imagpart(streamindex,block),
							 	  castwave2->GetPropagator().realpart(streamindex,block),
							 	  castwave2->GetPropagator().imagpart(streamindex,block),
							 	  aiaj);
		return aiaj;
	}

	GPUFactorizedRadiativePartialWave * ucastwave2 = dynamic_cast<GPUFactorizedRadiativePartialWave *>(wave2);
	if(ucastwave2){
		kernelcontractradmesons_u_f(mPropagator.GetList()->GetDeviceInterface(),
									mPropagator.realpart(streamindex,block),
									mPropagator.imagpart(streamindex,block),
									(*mg_perp_stream)(streamindex,block),
									(ucastwave2->GetTensor())(streamindex,block),
									(ucastwave2->GetPropagator())(streamindex,block),
									aiaj);
		return aiaj;
	}

	cout << "Contraction for this combination of wave types not implemented, aborting!" << endl;
	exit(-1);

	// Dummy statement to avoid compiler warnings
	return aiaj;
}





