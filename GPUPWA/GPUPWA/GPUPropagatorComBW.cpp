/*
 * GPUPropagatorComBW.cpp
 *
 *  Created on: July 9, 2017
 *      Author: xiongxa
 */

#include "GPUPropagatorComBW.h"
#include <cassert>
#include <cmath>
#ifdef USECPU
#include "Propagators_cpu.h"
using namespace Propagators_CPU;
#else
#include "Propagators.h"
using namespace Propagators_GPU;
#endif

GPUPropagatorComBW::GPUPropagatorComBW(char * name,
							 GPUStreamScalar & _mx2,
							 std::vector<char **> _parnames
							 ):GPUBasicPropagator(name,_mx2,_parnames, _parnames.size()),mpars(0){

}

GPUPropagatorComBW::~GPUPropagatorComBW() {
  delete mpars;
}


GPUDataStream<float2> * GPUPropagatorComBW::operator()(int index, int block){
	assert(index < mx2.GetNStreams());
	assert((int)mstream.size() > index);


	//cout << index << ": " << block << ": Mass: " << mass << " width " << width << endl;
	if(CacheValid(index)){
		if(mstream[index][block])
			return mstream[index][block];
	} else {
		InvalidateCache(index);
	}
	Stream<float> * mx2stream = mx2(index, block);

	float4* temp=new float4[1];
	  float4 val=mfloat4(GetParameterValue(0), GetParameterValue(1), GetParameterValue(2)*cos(GetParameterValue(3)), GetParameterValue(2)*sin(GetParameterValue(3)) );
	  //	  cout<<"dbg::liubj:: "<<GetParameterValue(i*4)<<", "<<GetParameterValue(i*4+1)<<", "<<GetParameterValue(i*4+2)<<", "<<GetParameterValue(i*4+3)<<endl;
          temp[0]=val;

        if(mpars) delete mpars;
	mpars= new GPUDataStream<float4>(mList->GetDeviceInterface(), 1);
        mpars->Write(temp);
        mpars->GetEvent().wait();
        delete [] temp;

	mstream[index][block] = new GPUDataStream<float2>(mList->GetDeviceInterface(), mx2.GetLength(index, block));
	kernelComBW(mList->GetDeviceInterface(), mx2stream, mpars, mstream[index][block]);


	for (unsigned int i=0;i<4;i++){
	  SetLastValue(index, i,GetParameterValue(i));
	}
	//print2Stream(mstream[index][block], mlength[index][block]);
	return mstream[index][block];

};


