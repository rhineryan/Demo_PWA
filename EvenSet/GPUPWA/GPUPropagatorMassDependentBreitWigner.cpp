/*
 * GPUPropagatorMassDependentBreitWigner.cpp
 *
 *  Created on: Feb 16, 2009
 *      Author: nberger
 */

#include "GPUPropagatorMassDependentBreitWigner.h"
#include <cassert>
#include <cmath>
#ifdef USECPU
#include "Propagators_cpu.h"
using namespace Propagators_CPU;
#else
#include "Propagators.h"
using namespace Propagators_GPU;
#endif

GPUPropagatorMassDependentBreitWigner::GPUPropagatorMassDependentBreitWigner(char * name,
		   GPUStreamScalar & _mx2,
		  int _l,
		  float _m_1,
		  float _m_2):GPUBasicPropagator(name,_mx2,std::vector<char**>(2,(char**)0),2),m_l(_l),m1_2(_m_1*_m_1),m2_2(_m_2*_m_2){
	assert(m_l >= 0 && m_l <= 4);

	unsigned int sl = strlen(name);
	char ** p1 = new char*;
	char ** p2 = new char*;

	*p1 = new char[sl+8];
	*p2 = new char[sl+8];
	sprintf(*p1,"%s_%s",name,"mass");
	sprintf(*p2,"%s_%s",name,"width");
	mparnames[0] = p1;
	mparnames[1] = p2;
}

GPUPropagatorMassDependentBreitWigner::~GPUPropagatorMassDependentBreitWigner() {
}


GPUDataStream<float2> * GPUPropagatorMassDependentBreitWigner::operator()(int index, int block){
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

	double mass = GetParameterValue(0);
	double width = GetParameterValue(1);
	float pmr = p_mr(mass);

	mstream[index][block] = new GPUDataStream<float2>(mList->GetDeviceInterface(), mx2.GetLength(index, block));
	switch(m_l){
	case 0:
		kernelmassdependentbreitwigner0(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mstream[index][block]);
		break;
	case 1:
		kernelmassdependentbreitwigner1(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mstream[index][block]);
		break;
	case 2:
		kernelmassdependentbreitwigner2(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mstream[index][block]);
		break;
	case 3:
		kernelmassdependentbreitwigner3(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mstream[index][block]);
		break;
	case 4:
		kernelmassdependentbreitwigner4(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mstream[index][block]);
		break;
	default:
		cout << m_l << " is an invalid value for the angular momentum!" << endl;
		assert(0);
		break;
	}
	//mstream[index][block]->error();
	//mlength[index][block] = mx2.GetLength(index, block);
	SetLastValue(index, 0, mass);
	SetLastValue(index, 1, width);
	//print2Stream(mstream[index][block], mlength[index][block]);
	return mstream[index][block];

};


// Get a stream of the derivative of the propagator with regards to the mass
GPUDataStream<float2> * GPUPropagatorMassDependentBreitWigner::GetMassDerivative(int index, int block){
	assert(index < mx2.GetNStreams());
	assert((int)mDmass.size() > index);
	if(CacheValid(index)){
		if(mDmass[index][block])
			return mDmass[index][block];
	} else {
		InvalidateCache(index);
	}
	Stream<float> * mx2stream = mx2(index, block);
	double mass = GetParameterValue(0);
	double width = GetParameterValue(1);

	mDmass[index][block] = new GPUDataStream<float2>(mList->GetDeviceInterface(), mx2.GetLength(index, block));

	float pmr = p_mr(mass);

	switch(m_l){
		case 0:
			kernelmassdependentbreitwigner0dwidth(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mDmass[index][block]);
			break;
		case 1:
			kernelmassdependentbreitwigner1dwidth(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mDmass[index][block]);
			break;
		case 2:
			kernelmassdependentbreitwigner2dwidth(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mDmass[index][block]);
			break;
		case 3:
			kernelmassdependentbreitwigner3dwidth(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mDmass[index][block]);
			break;
		case 4:
			kernelmassdependentbreitwigner4dwidth(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mDmass[index][block]);
			break;
		default:
			cout << m_l << " is an invalid value for the angular momentum!" << endl;
			assert(0);
			break;
		}


	//mDmass[index][block]->error();
	//mlength[index][block] = mx2.GetLength(index, block);
	SetLastValue(index, 0, mass);
	SetLastValue(index, 1, width);
	return mDmass[index][block];

}
// Get a stream of the derivative of the propagator with regards to the width
GPUDataStream<float2> * GPUPropagatorMassDependentBreitWigner::GetWidthDerivative(int index, int block){
	assert(index < mx2.GetNStreams());
	assert((int)mDwidth.size() > index);
	if(CacheValid(index)){
		if(mDwidth[index][block])
			return mDwidth[index][block];
	} else {
		InvalidateCache(index);
	}
	Stream<float> * mx2stream = mx2(index, block);
	double mass = GetParameterValue(0);
	double width = GetParameterValue(1);

	mDwidth[index][block] = new GPUDataStream<float2>(mList->GetDeviceInterface(), mx2.GetLength(index, block));

	float pmr = p_mr(mass);

	switch(m_l){
		case 0:
			kernelmassdependentbreitwigner0dwidth(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mDwidth[index][block]);
			break;
		case 1:
			kernelmassdependentbreitwigner1dwidth(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mDwidth[index][block]);
			break;
		case 2:
			kernelmassdependentbreitwigner2dwidth(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mDwidth[index][block]);
			break;
		case 3:
			kernelmassdependentbreitwigner3dwidth(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mDwidth[index][block]);
			break;
		case 4:
			kernelmassdependentbreitwigner4dwidth(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mDwidth[index][block]);
			break;
		default:
			cout << m_l << " is an invalid value for the angular momentum!" << endl;
			assert(0);
			break;
		}


	//mDwidth[index][block]->error();
	//mlength[index][block] = mx2.GetLength(index, block);
	SetLastValue(index, 0, mass);
	SetLastValue(index, 1, width);
	return mDwidth[index][block];
}

// Get a stream of the derivative of the |propagator|^2 with regards to the mass
GPUDataStream<float> * GPUPropagatorMassDependentBreitWigner::GetAbsMassDerivative(int index, int block){
	cout << "TODO!" << endl;
	assert(0);
	assert(index < mx2.GetNStreams());
	assert((int)mAbsDmass.size() > index);
	if(CacheValid(index)){
		if(mAbsDmass[index][block])
			return mAbsDmass[index][block];
	} else {
		InvalidateCache(index);
	}
	Stream<float> * mx2stream = mx2(index, block);
	double mass = GetParameterValue(0);
	double width = GetParameterValue(1);
	mAbsDmass[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), mx2.GetLength(index, block));
	kerneldbw2dmass(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, mAbsDmass[index][block]);
	//mAbsDmass[index][block]->error();
	//mlength[index][block] = mx2.GetLength(index, block);
	SetLastValue(index, 0, mass);
	SetLastValue(index, 1, width);
	return mAbsDmass[index][block];

}
// Get a stream of the derivative of the |propagator|^2 with regards to the width
GPUDataStream<float> * GPUPropagatorMassDependentBreitWigner::GetAbsWidthDerivative(int index, int block){
	assert(index < mx2.GetNStreams());
	assert((int)mAbsDwidth.size() > index);
	if(CacheValid(index)){
		if(mAbsDwidth[index][block])
			return mAbsDwidth[index][block];
	} else {
		InvalidateCache(index);
	}
	Stream<float> * mx2stream = mx2(index, block);
	double mass = GetParameterValue(0);
	double width = GetParameterValue(1);
	mAbsDwidth[index][block] = new GPUDataStream<float>(mList->GetDeviceInterface(), mx2.GetLength(index, block));
	float pmr = p_mr(mass);

		switch(m_l){
			case 0:
				kerneldmassdependentbreitwigner20dwidth(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mAbsDwidth[index][block]);
				break;
			case 1:
				kerneldmassdependentbreitwigner21dwidth(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mAbsDwidth[index][block]);
				break;
			case 2:
				kerneldmassdependentbreitwigner22dwidth(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mAbsDwidth[index][block]);
				break;
			case 3:
				kerneldmassdependentbreitwigner23dwidth(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mAbsDwidth[index][block]);
				break;
			case 4:
				kerneldmassdependentbreitwigner24dwidth(mList->GetDeviceInterface(), mx2stream,mass, mass*mass, width, pmr, m1_2, m2_2, mAbsDwidth[index][block]);
				break;
			default:
				cout << m_l << " is an invalid value for the angular momentum!" << endl;
				assert(0);
				break;
			}

	//mAbsDwidth[index][block]->error();
	//mlength[index][block] = mx2.GetLength(index,block);
	SetLastValue(index, 0, mass);
	SetLastValue(index, 1, width);
	return mAbsDwidth[index][block];




}

float GPUPropagatorMassDependentBreitWigner::p_mr(float mr){
	if(sqrt(m1_2)+sqrt(m2_2) >= mr)
		return 0;
	float mr2 = mr*mr;
	float poly = mr2*mr2 + m1_2*m1_2 + m2_2*m2_2
				- 2*m1_2*mr2 -2*m2_2*mr2 -2*m1_2*m2_2;
	return sqrt(poly)/(2*mr);
}

