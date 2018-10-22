#include "GPUPropagatorSigma.h"
#include <cassert>
#include <cmath>
#ifdef USECPU
#include "Propagators_cpu.h"
using namespace Propagators_CPU;
#else
#include "Propagators.h"
using namespace Propagators_GPU;
#endif



GPUPropagatorSigma::GPUPropagatorSigma(char * name, GPUStreamScalar & _mx2):
		GPUBasicPropagator(name, _mx2, std::vector<char**>(0,(char **)0), 0){
}

GPUPropagatorSigma::~GPUPropagatorSigma(void)
{
}


GPUDataStream<float2> * GPUPropagatorSigma::operator()(int index, int block){
	assert(index < mx2.GetNStreams());
	assert((int)mstream.size() > index);
	if(CacheValid(index)){
		//cout << "Cache valid!" << endl;
		if(mstream[index][block]){
			return mstream[index][block];
		}
	} else {
		//cout << "Cache invalid!" << endl;
		InvalidateCache(index);
	}
	Stream<float> * mx2stream = mx2(index, block);

	mstream[index][block] = new GPUDataStream<float2>(mList->GetDeviceInterface(), mx2.GetLength(index, block));

	//cout << index << " : " << block << " Calling with mass: " << mass <<" , g1: " << g1 << " and g2: " << g2 << endl;

	kernelsigma(mList->GetDeviceInterface(), mx2stream, mstream[index][block]);
	return mstream[index][block];
};
