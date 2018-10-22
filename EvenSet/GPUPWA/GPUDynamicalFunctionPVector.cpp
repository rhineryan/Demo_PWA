/*
 * GPUDynamicalFunctionPVector.cpp
 *
 *  Created on: April 8, 2011
 *      Author: liubj
 */

#include "GPUDynamicalFunctionPVector.h"
#include <cassert>
#include <cmath>
#ifdef USECPU
#include "Propagators_cpu.h"
using namespace Propagators_CPU;
#else
#include "Propagators.h"
using namespace Propagators_GPU;
#endif

GPUDynamicalFunctionPVector::GPUDynamicalFunctionPVector(char * name,
							 GPUStreamScalar & _mx2,
							 std::vector<char **> _parnames,
							 unsigned int _nresonances,
							 float _m_1,
							 float _m_2):GPUBasicPropagator(name,_mx2,_parnames, _parnames.size()),m_nresonances(_nresonances),m1_2(_m_1*_m_1),m2_2(_m_2*_m_2),mpars(0){
  assert((_nresonances*4+6)==_parnames.size());//each resonance have (m,w), (gx,gy); and there are 4 poly.terms (6 paramaters) in the P-vector c, cs, (dx,dy), (dsx, dsy);

}

GPUDynamicalFunctionPVector::~GPUDynamicalFunctionPVector() {
  delete mpars;
}


GPUDataStream<float2> * GPUDynamicalFunctionPVector::operator()(int index, int block){
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

	float4* temp=new float4[m_nresonances];
	for (unsigned int i=0;i<m_nresonances;i++){
	  float4 val=mfloat4(GetParameterValue(i*4), GetParameterValue(i*4+1), GetParameterValue(i*4+2)*cos(GetParameterValue(i*4+3)), GetParameterValue(i*4+2)*sin(GetParameterValue(i*4+3)) );
	  //	  cout<<"dbg::liubj:: "<<GetParameterValue(i*4)<<", "<<GetParameterValue(i*4+1)<<", "<<GetParameterValue(i*4+2)<<", "<<GetParameterValue(i*4+3)<<endl;
          temp[i]=val;
	}
        float c_=GetParameterValue(m_nresonances*4);
        float cs_=GetParameterValue(m_nresonances*4+1);
        float2 d_;
	d_.x =GetParameterValue(m_nresonances*4+2); 
	d_.y = GetParameterValue(m_nresonances*4+3);
	float2 ds_;
	ds_.x=GetParameterValue(m_nresonances*4+4);
	ds_.y=GetParameterValue(m_nresonances*4+5);

        if(mpars) delete mpars;
	mpars= new GPUDataStream<float4>(mList->GetDeviceInterface(), m_nresonances);
        mpars->Write(temp);
        mpars->GetEvent().wait();
        delete [] temp;

	mstream[index][block] = new GPUDataStream<float2>(mList->GetDeviceInterface(), mx2.GetLength(index, block));
	kernelfnscalarcm(mList->GetDeviceInterface(), mx2stream, m_nresonances, mpars,c_,cs_,d_,ds_, m1_2, m2_2, mstream[index][block]);


	//mstream[index][block]->error();
	//mlength[index][block] = mx2.GetLength(index, block);

	for (unsigned int i=0;i<m_nresonances*4+6;i++){
	  SetLastValue(index, i,GetParameterValue(i));
	}
	//print2Stream(mstream[index][block], mlength[index][block]);
	return mstream[index][block];

};


