#include "GPUPropagatorA980.h"
#include <cassert>
#include <cmath>
#ifdef USECPU
#include "Propagators_cpu.h"
using namespace Propagators_CPU;
#else
#include "Propagators.h"
using namespace Propagators_GPU;
#endif



GPUPropagatorA980::GPUPropagatorA980(char * name,
                                           GPUStreamScalar & _mx2,
                                           float _m1a,
                                           float _m1b,
                                           float _m2a,
                                           float _m2b,
                                           float _m3a,
                                           float _m3b,
                                           float _m4a,
                                           float _m4b):
		GPUBasicPropagator(name, _mx2, std::vector<char**>(5,(char **)0), 5),m1a(_m1a),m1b(_m1b),m2a(_m2a),m2b(_m2b),
                                                                         m3a(_m3a),m3b(_m3b),m4a(_m4a),m4b(_m4b){

	unsigned int sl = strlen(name);
	char ** p1 = new char*;
	char ** p2 = new char*;
	char ** p3 = new char*;
	char ** p4 = new char*;
	char ** p5 = new char*;

	*p1 = new char[sl+8];
	*p2 = new char[sl+8];
	*p3 = new char[sl+8];
	*p4 = new char[sl+8];
	*p5 = new char[sl+8];
	sprintf(*p1,"%s_%s",name,"mass");
	sprintf(*p2,"%s_%s",name,"g1");
	sprintf(*p3,"%s_%s",name,"g2");
	sprintf(*p4,"%s_%s",name,"g3");
	sprintf(*p5,"%s_%s",name,"g4");
	mparnames[0] = p1;
	mparnames[1] = p2;
	mparnames[2] = p3;
	mparnames[3] = p4;
	mparnames[4] = p5;
}

GPUPropagatorA980::~GPUPropagatorA980(void)
{
}


GPUDataStream<float2> * GPUPropagatorA980::operator()(int index, int block){
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
	double mass = GetParameterValue(0);
	double g1   = GetParameterValue(1);
	double g2   = GetParameterValue(2);
	double g3   = GetParameterValue(3);
	double g4   = GetParameterValue(4);

	//cout << index << " : " << block << " Calling with mass: " << mass <<" , g1: " << g1 << " and g2: " << g2 << endl;

	kernel_a0980(mList->GetDeviceInterface(), mx2stream, mass, mass*mass, g1, m1a, m1b, g2, m2a, m2b, g3, m3a, m3b, g4, m4a, m4b, mstream[index][block]);
	SetLastValue(index, 0, mass);
	SetLastValue(index, 1, g1);
	SetLastValue(index, 2, g2);
	SetLastValue(index, 3, g3);
	SetLastValue(index, 4, g4);
	return mstream[index][block];
};
