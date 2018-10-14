#include "GPUOrbitalTensors.h"
#include "GPUComputedTensor.h"
#include <cmath>

GPUOrbitalTensors::GPUOrbitalTensors(GPUDataDependentObjectList * _list, GPUStreamVector & _pa, GPUStreamVector & _pb, GPUStreamVector & _pc, float _r):
	GPUDataDependentObject(_list), mstreampa(&_pa),mconstpa(0), mpb(_pb), mpc(_pc), mRadius(_r)
{
	mmetric = new GPUMetricTensor();
	mpa = mstreampa;
	MakeTensors();
}
GPUOrbitalTensors::GPUOrbitalTensors(GPUDataDependentObjectList * _list, GPUConstVector & _pa, GPUStreamVector & _pb, GPUStreamVector & _pc, float _r):
	GPUDataDependentObject(_list),  mstreampa(0),mconstpa(&_pa), mpb(_pb), mpc(_pc), mRadius(_r)
{
	mmetric = new GPUMetricTensor();
	mpa = mconstpa;
	MakeTensors();
}

GPUOrbitalTensors::GPUOrbitalTensors(GPUDataDependentObjectList * _list, float4 & _pa, GPUStreamVector & _pb, GPUStreamVector & _pc, float _r):
	GPUDataDependentObject(_list), mstreampa(0),mconstpa(new GPUConstVector(_pa)), mpb(_pb), mpc(_pc), mRadius(_r)
{
	mmetric = new GPUMetricTensor();
	mpa = mconstpa;
	MakeTensors();
}


GPUOrbitalTensors::~GPUOrbitalTensors(void)
{
	delete mmetric;
}

void GPUOrbitalTensors::Reset(int index){

	msb->Reset(index);
	msc->Reset(index);

	mr->Reset(index);

	if(mguv_tilde_pa_stream)
		mguv_tilde_pa_stream->Reset(index);
	mQ2abc->Reset(index);
	mr_tilde->Reset(index);
	mr_tilde2->Reset(index);
	mB1->Reset(index);
	mB2->Reset(index);
	mB3->Reset(index);
	mB4->Reset(index);

	mSpin1OrbitalTensor->Reset(index);
	mSpin2OrbitalTensor->Reset(index);
	mSpin3OrbitalTensor->Reset(index);
	mSpin4OrbitalTensor->Reset(index);
}

void GPUOrbitalTensors::Reset(int index, int block){

	msb->Reset(index, block);
	msc->Reset(index, block);

	mr->Reset(index, block);

	if(mguv_tilde_pa_stream)
		mguv_tilde_pa_stream->Reset(index, block);
	mQ2abc->Reset(index, block);
	mr_tilde->Reset(index, block);
	mr_tilde2->Reset(index, block);
	mB1->Reset(index, block);
	mB2->Reset(index, block);
	mB3->Reset(index, block);
	mB4->Reset(index, block);

	mSpin1OrbitalTensor->Reset(index, block);
	mSpin2OrbitalTensor->Reset(index, block);
	mSpin3OrbitalTensor->Reset(index);
	mSpin4OrbitalTensor->Reset(index);
}


void GPUOrbitalTensors::MakeTensors()
{
	// relative momentum
	mr = &(mpb-mpc);

	// "Masses" of particles
	if(mstreampa)
		msa = &(*mstreampa|*mstreampa);
	else
		msa = &(*mconstpa|*mconstpa);

	msb = &(mpb|mpb);
	msc = &(mpc|mpc);


	// Q^2_abc
	if(mstreampa){
		GPUStreamScalar & satemp = (*mstreampa|*mstreampa);
		GPUStreamScalar & top = (satemp + *msb - *msc);
		mQ2abc = &(top*top/(4.0f*satemp) -(*msb));
	} else {
		GPUConstScalar & satemp = (*mconstpa|*mconstpa);
		GPUStreamScalar & top = (satemp + *msb - *msc);
		mQ2abc = &(top*top/(4.0f*satemp) -(*msb));

	}
	GPUStreamScalar & Q2abc = *mQ2abc;

	// Barrier factors
	//float Q_0 = sqrt(0.22/3.0);//0.197321f/mRadius;
	float Q_0 = 0.197321f/mRadius;
	float Q_02 = Q_0*Q_0;
	float Q_04 = Q_02*Q_02;
	float Q_06 = Q_04*Q_02;
	float Q_08 = Q_04*Q_04;

	GPUStreamScalar & Q4abc = Q2abc*Q2abc;
	GPUStreamScalar & Q6abc = Q4abc*Q2abc;
	GPUStreamScalar & Q8abc = Q4abc*Q4abc;
	mB1 = &sqrt(2.0f/(Q2abc + Q_02));
	mB2 = &sqrt(13.0f/(Q4abc + (3.0f*Q_02)*Q2abc + 9.0f*Q_04));
	mB3 = &sqrt(277.0f/(Q6abc + (6.0f*Q_02)*Q4abc + (45.0f*Q_04)*Q2abc + 225.0f*Q_06));
	mB4 = &sqrt(12746.0f/(Q8abc + (10.0f*Q_02)*Q6abc + (135.0f*Q_04)*Q4abc + (1575.0f*Q_06)*Q2abc + 11025.0f*Q_08));

	/*cout << "B2 (sqrt(13)) = " << sqrt(13.0) << endl;
	(*mB2)()->print();
	cout << "B4 (sqrt(12746)) =" << sqrt(12746.0) <<  endl;
	(*mB4)()->print();*/


	// Things dependent on relative Momentum
	// Momenta are vectors (lower indices), uv stand for lower, UV for upper indices.
	if(mstreampa){
		mguv_tilde_pa_stream = &(*mmetric - (*mstreampa%*mstreampa)/(*mstreampa|*mstreampa));
		mguv_tilde_pa_const = 0;
		mr_tilde = &((*mguv_tilde_pa_stream)|(*mr));
	} else {
		mguv_tilde_pa_const  = &(*mmetric - (*mconstpa%*mconstpa)/(*mconstpa|*mconstpa));
		mguv_tilde_pa_stream = 0;
		mr_tilde = &((*mguv_tilde_pa_const)|(*mr));
	}

	mr_tilde2 = &(*mr_tilde|*mr_tilde);





	// Orbital Tensors

	mSpin1OrbitalTensor = & ((*mr_tilde) * (*mB1));
	GPUStreamTensor3* gr_tilde;
	GPUStreamTensor3* gr_tilde_231;
	GPUStreamTensor3* gr_tilde_312;
	GPUStreamTensor4* gr2_tilde;
	GPUStreamTensor4* gr2_tilde_1324;
//	GPUStreamTensor4* gr2_tilde_1423;
//	GPUStreamTensor4* gr2_tilde_2314;
//	GPUStreamTensor4* gr2_tilde_2413;
	GPUStreamTensor4* gr2_tilde_3412;
//	GPUStreamTensor4* gr2_tilde_4132;
	GPUStreamTensor4* gr2_tilde_1342;
	GPUStreamTensor4* gr2_tilde_3124;
	GPUStreamTensor4* gr2_tilde_3142;

	GPUStreamTensor4* guv2_tilde;
	GPUStreamTensor4* guv2_tilde_1324;
	GPUStreamTensor4* guv2_tilde_1423;
	GPUStreamTensor4* guv2_tilde_1342;

	///
	GPUStreamTensor3* gr_tilde_const;
	GPUStreamTensor3* gr_tilde_231_const;
	GPUStreamTensor3* gr_tilde_312_const;
	GPUStreamTensor4* gr2_tilde_const;
	GPUStreamTensor4* gr2_tilde_1324_const;
//	GPUStreamTensor4* gr2_tilde_1423_const;
//	GPUStreamTensor4* gr2_tilde_2314_const;
//	GPUStreamTensor4* gr2_tilde_2413_const;
	GPUStreamTensor4* gr2_tilde_3412_const;
	GPUStreamTensor4* gr2_tilde_1342_const;
	GPUStreamTensor4* gr2_tilde_3124_const;
	GPUStreamTensor4 *gr2_tilde_3142_const;

	GPUConstTensor4* guv2_tilde_const;
	GPUConstTensor4* guv2_tilde_1324_const;
//	GPUConstTensor4* guv2_tilde_1423_const;
	GPUConstTensor4* guv2_tilde_1342_const;

	if(mstreampa){
	  gr_tilde       = &((*mguv_tilde_pa_stream)%(*mr_tilde));
	  gr_tilde_231   = &(trans_231(*gr_tilde));
	  gr_tilde_312   = &(trans_312(*gr_tilde));

	  gr2_tilde      = &((*mguv_tilde_pa_stream)%((*mr_tilde)%(*mr_tilde)));
	  gr2_tilde_1324 = &(trans_1324(*gr2_tilde));
	  //gr2_tilde_1423 = &(trans_1423(*gr2_tilde));
	  //gr2_tilde_2314 = &(trans_2314(*gr2_tilde));
	  //gr2_tilde_2413 = &(trans_2413(*gr2_tilde));
	  gr2_tilde_3412 = &(trans_3412(*gr2_tilde));
	  gr2_tilde_3124 = &(trans_3124(*gr2_tilde));
	  //gr2_tilde_4132 = &(trans_4132(*gr2_tilde));
	  gr2_tilde_1342 = &(trans_1342(*gr2_tilde));
	  gr2_tilde_3142 = &(trans_3142(*gr2_tilde));

	  guv2_tilde      =  &((*mguv_tilde_pa_stream)%(*mguv_tilde_pa_stream));
	  guv2_tilde_1324 =  &(trans_1324(*guv2_tilde));
	  guv2_tilde_1423 =  &(trans_1423(*guv2_tilde));
	  guv2_tilde_1342 =  &(trans_1342(*guv2_tilde));


	  /// spin 2
	  mSpin2OrbitalTensor = & ((((*mr_tilde)%(*mr_tilde)) - 1.0f/3.0f * (*mr_tilde2) * (*mguv_tilde_pa_stream))*(*mB2));
	  //mr_tilde2->Print();
	  //mguv_tilde_pa_stream->Print();
	  /// spin 3
	  ///GPUStreamTensor3 & Spin3OrbitalTensor =  (((*mr_tilde)%(*mr_tilde)%(*mr_tilde) - 1.0f/5.0f * (*mr_tilde2) * (*gr_tilde + *gr_tilde_231 + *gr_tilde_312))*(*mB3));
	  mSpin3OrbitalTensor = &(spin3orbitaltensor(*mr_tilde,  *mstreampa)*(*mB3));

	  //GPUStreamTensor3 & diff = Spin3OrbitalTensor - *mSpin3OrbitalTensor;

	  //diff.Print(5);

	  /// spin 4
          /* mSpin4OrbitalTensor = & ((((*mr_tilde)%(*mr_tilde))%((*mr_tilde)%(*mr_tilde)) - 1.0f/7.0f * (*mr_tilde2) * (*gr2_tilde + *gr2_tilde_1324 + *gr2_tilde_1342 + *gr2_tilde_3124 + *gr2_tilde_3142 + *gr2_tilde_3412) + 1.0f/35.0f * (*mr_tilde2)*(*mr_tilde2) * (*guv2_tilde + *guv2_tilde_1324 + *guv2_tilde_1342))*(*mB4));
          */
	  mSpin4OrbitalTensor = &(spin4orbitaltensor(*mr_tilde,  *mguv_tilde_pa_stream)*(*mB4));


	} else {

	  gr_tilde_const       = &((*mguv_tilde_pa_const)%(*mr_tilde));
	  gr_tilde_231_const   = & (trans_231(*gr_tilde_const));
	  gr_tilde_312_const   = & (trans_312(*gr_tilde_const));
	  gr2_tilde_const      = &((*mguv_tilde_pa_const)%((*mr_tilde)%(*mr_tilde)));
	  gr2_tilde_1324_const = &(trans_1324(*gr2_tilde_const));
	  //gr2_tilde_1423_const = &(trans_1423(*gr2_tilde_const));
	  //gr2_tilde_2314_const = &(trans_2314(*gr2_tilde_const));
	  //gr2_tilde_2413_const = &(trans_2413(*gr2_tilde_const));
	  gr2_tilde_3412_const = &(trans_3412(*gr2_tilde_const));
	  gr2_tilde_1342_const = &(trans_3412(*gr2_tilde_const));
	  gr2_tilde_3124_const = &(trans_3412(*gr2_tilde_const));
	  gr2_tilde_3142_const = &(trans_3412(*gr2_tilde_const));


	  guv2_tilde_const      =  &((*mguv_tilde_pa_const)%(*mguv_tilde_pa_const));
	  guv2_tilde_1324_const =  &(trans_1324(*guv2_tilde_const));
	  //guv2_tilde_1423_const =  &(trans_1423(*guv2_tilde_const));
          guv2_tilde_1342_const =  &(trans_1342(*guv2_tilde_const));

	  ///
	  mSpin2OrbitalTensor = & ((((*mr_tilde)%(*mr_tilde)) - 1.0f/3.0f * (*mr_tilde2) * (*mguv_tilde_pa_const))*(*mB2));
          ///
	  //Spin3OrbitalTensor = & (((*mr_tilde)%(*mr_tilde)%(*mr_tilde) - 1.0f/5.0f * (*mr_tilde2) * (*gr_tilde_const + *gr_tilde_231_const + *gr_tilde_312_const))*(*mB3));
	  ///mSpin4OrbitalTensor = & ((((*mr_tilde)%(*mr_tilde))%((*mr_tilde)%(*mr_tilde)) - 1.0f/7.0f * (*mr_tilde2) * (*gr2_tilde_const + *gr2_tilde_1324_const + *gr2_tilde_1342_const + *gr2_tilde_3124_const + *gr2_tilde_3142_const + *gr2_tilde_3412_const) + 1.0f/35.0f * (*mr_tilde2)*(*mr_tilde2) * (*guv2_tilde_const + *guv2_tilde_1324_const + *guv2_tilde_1342_const))*(*mB4));
	  mSpin3OrbitalTensor = &(spin3orbitaltensor(*mr_tilde,  *mconstpa)*(*mB3));

	  mSpin4OrbitalTensor = &(spin4orbitaltensor(*mr_tilde,  *mguv_tilde_pa_const)*(*mB4));
          //std::cout<<" mSpin4OrbitalTensor2: "<<std::endl;
	  //mSpin4OrbitalTensor->Print();
	}
}

GPUStreamTensor4 & GPUOrbitalTensors::Spin3ProjectTensor2(GPUStreamTensor2& T){
	assert(mguv_tilde_pa_stream);
	return 	spin3projecttensor2(*mguv_tilde_pa_stream,T);
}
