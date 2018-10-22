/*/// \file Propagators.br*/
#pragma OPENCL EXTENSION cl_amd_fp64 : enable



/* Breit-Wigner propagator */
__kernel void kernelbreitwigner(__global float * mx2in, float mr, float mr2, float wr, __global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];

	float diff = mr2-mx2;
	float denom = diff*diff + wr*wr*mr2;
	if (wr<0) {
		output[i].x = 1/sqrt(denom);
		output[i].y = 0;
    }
    else if (wr<10) {
		output[i].x = diff/denom;
		output[i].y = wr*mr/denom;
	}
	else { /* phase space */
		output[i].x = 1;
		output[i].y = 0;
	}
}


/* gaussian */
/* the phase information is dropped */
__kernel void kernelgaussian(__global float * mx2in, float mr, float mr2, float wr, __global out float2 * output)
{
	uint i = get_global_id(0);
	float mx = sqrt(mx2in[i]);
	float diff = mx - mr;
	float denom = 2*wr*wr;

	output[i].x = exp(-diff*diff/denom/2);
	output[i].y = 0;
}

/* f(x, m, w) = 1/(x*x - m*m - imw)
   g(x, m, w) = 1/(m*m - x*x - imw)
   -> g(x, m, w) = -f(x, m, -w)
   -> Dg(x, m, w)/Dm = -Df(x, m, -w)/Dm    Equation(a)
   -> Dg(x, m, w)/Dw = Df(x, m, w)/Dw      Equation(b) */
/* Breit-Wigner propagator: derivative wrt resonance mass */
__kernel void kerneldbreitwignerdmass(__global float * mx2in, float mr, float mr2, float wr, __global out float2 * output)
{
	uint i = get_global_id(0);
	wr *= -1; /* w -> -w */
	float mx2 = mx2in[i];
	float mx4 = mx2*mx2;
	float mr4 = mr2*mr2;
	float gr2 = wr*wr;
	float denomcommon =  mx4 - 2.0f*mx2*mr2 + mr4;
	float denom = denomcommon + mr2*gr2;
	float denom2 = denom*denom;

	/* change sign according to Eq(a) */
	output[i].x = -1.0f * 2.0f*mr*(denomcommon - mx2*gr2)/denom2;
	output[i].y = -1.0f * wr*(mx4-2.0f*mx2*mr2-3.0f*mr4-gr2*mr2)/denom2;
}

/* Breit-Wigner propagator: derivative wrt resonance width */
__kernel void kerneldbreitwignerdwidth(__global float * mx2in, float mr, float mr2, float wr, __global out float2 * output)
{
	uint i = get_global_id(0);
	wr *= -1; /* w -> -w */
	float mx2 = mx2in[i];
	float mx4 = mx2*mx2;
	float mr4 = mr2*mr2;
	float gr2 = wr*wr;
	float denomcommon =  mx4 - 2.0f*mx2*mr2 + mr4;
	float denom = denomcommon + mr2*gr2;
	float denom2 = denom*denom;

	/* according to Eq(b) */
	output[i].x = -2.0f *(mx2-mr2)*wr*mr2/denom2;
	output[i].y = mr*(denomcommon -mr2*gr2)/denom2;
}


/* Breit-Wigner propagator: derivative of magnitude squared wrt to mass */
__kernel void kerneldbw2dmass(__global float * mx2in, float mr, float mr2, float wr, __global out float * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float mx4 = mx2*mx2;
	float mr4 = mr2*mr2;
	float wr2 = wr*wr;

	float denom = mx4 + 2.0f*mx2*mr2 + mr4 + wr2*mr2;

	output[i] = 2.0f*mr*(2.0f*mx2 - 2.0f*mr2 - wr2)/(denom*denom);
}

/* Breit-Wigner propagator: derivative of magnitude squared wrt to width */
__kernel void kerneldbw2dwidth(__global float * mx2in, float mr, float mr2, float wr, __global out float * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float mx4 = mx2*mx2;
	float mr4 = mr2*mr2;
	float wr2 = wr*wr;

	float denom = mx4 + 2.0f*mx2*mr2 + mr4 + wr2*mr2;

	output[i] = -2.0f*wr*mr2/(denom*denom);
}

float fundecaymomentum(float mr2, float m1_2, float m2_2){
	float mr = sqrt(mr2);
	float poly = mr2*mr2 + m1_2*m1_2 + m2_2*m2_2 - 2*m1_2*mr2 -2*m2_2*mr2 -2*m1_2*m2_2;
	float ret = sqrt(poly)/(2*mr);
	if(sqrt(m1_2) +sqrt(m2_2) > mr)
		ret = 0.0f;
	return ret;
}


/* Mass dependent Breit-Wigner propagator - angular momentum 0 */
__kernel void kernelmassdependentbreitwigner0(__global float * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, __global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float diff = mr2-mx2;
	float p_s = fundecaymomentum(mx2, m1_2,m2_2);
	float mx   = sqrt(mx2); /* square root of s */
	float ws   = wr*(mr2/mx2)*(p_s/pmr); /*mass dependent width */
	float denom = diff*diff + mx2*ws*ws; /* common denominator*/
	output[i].x = diff/denom; /* real part*/
	output[i].y = mx*ws/denom; /* imaginary part*/
}

/* Mass dependent Breit-Wigner propagator - angular momentum 1*/
__kernel void kernelmassdependentbreitwigner1(__global float * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, __global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float p_s = fundecaymomentum(mx2, m1_2,m2_2);
	float ppart= (p_s/pmr); /* Momentum dependent part */
	float ppart3 = ppart*ppart*ppart;
	float diff = mr2-mx2;
	float mx   = sqrt(mx2); /* square root of s*/
	float ws   = wr*(mr2/mx2)*ppart3; /*mass dependent width */
	float denom = diff*diff + mx2*ws*ws; /* common denominator*/
	output[i].x = diff/denom; /* real part*/
	output[i].y = mx*ws/denom; /* imaginary part*/
}

/* Mass dependent Breit-Wigner propagator - angular momentum 2 */
__kernel void kernelmassdependentbreitwigner2(__global float * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2,__global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float p_s = fundecaymomentum(mx2, m1_2,m2_2);
	float ppart= (p_s/pmr); /* Momentum dependent part*/
	float ppart2 = ppart*ppart;
	float diff = mr2-mx2;
	float mx   = sqrt(mx2); /* square root of s*/
	float ppart5 = ppart2*ppart2*ppart;
	float ws   = wr*(mr2/mx2)*ppart5; /* mass dependent width */
	float denom = diff*diff + mx2*ws*ws; /* common denominator*/
	output[i].x = diff/denom; /* real part*/
	output[i].y = mx*ws/denom; /* imaginary part*/
}

/*  Mass dependent Breit-Wigner propagator - angular momentum 3   */
__kernel void kernelmassdependentbreitwigner3(__global float * mx2in,  float mr, float mr2, float wr, float pmr, float m1_2, float m2_2,__global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float p_s = fundecaymomentum(mx2, m1_2,m2_2);
	float ppart= (p_s/pmr); /* Momentum dependent part */
	float ppart3 = ppart*ppart*ppart;
	float diff = mr2-mx2;
	float mx   = sqrt(mx2); /* square root of s */
	float ppart7 = ppart3*ppart3*ppart;
	float ws   = wr*(mr2/mx2)*ppart7; /* mass dependent width  */
	float denom = diff*diff + mx2*ws*ws; /* common denominator */
	output[i].x = diff/denom; /* real part */
	output[i].y = mx*ws/denom; /* imaginary part */
}

/* Mass dependent Breit-Wigner propagator - angular momentum 4  */
__kernel void kernelmassdependentbreitwigner4(__global float * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2,__global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float p_s = fundecaymomentum(mx2, m1_2,m2_2);
	float ppart= (p_s/pmr); /* Momentum dependent part */
	float ppart2 = ppart*ppart;
	float ppart4 = ppart2*ppart2;
	float diff = mr2-mx2;
	float mx   = sqrt(mx2); /* square root of s */
	float ppart9 = ppart4*ppart4*ppart;
	float ws   = wr*(mr2/mx2)*ppart9; /* mass dependent width  */
	float denom = diff*diff + mx2*ws*ws; /* common denominator */
	output[i].x = diff/denom; /* real part */
	output[i].y = mx*ws/denom; /* imaginary part */
}

/* Derivative wrt. width of mass dependent Breit-Wigner propagator - angular momentum 0 */
__kernel void kernelmassdependentbreitwigner0dwidth(__global float * mx2in,  float mr, float mr2, float wr, float pmr, float m1_2, float m2_2,__global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float diff = mx2-mr2;
	float p_s = fundecaymomentum(mx2, m1_2,m2_2);
	float mx   = sqrt(mx2); /* square root of s */
	float ww   = (mr2/mx2)*(p_s/pmr); 
	float ws   = wr*ww;
	float denom = diff*diff + mx2*ws*ws; /* common denominator */
	float denom2 = denom*denom;
	float realnom = -diff - mr2*ww;
	float imagnom = mx*ww*(denom - mx2*ws);
	output[i].x = realnom/denom2; /* real part */
	output[i].y = imagnom/denom2; /* imaginary part */
}

/* Derivative wrt. width of mass dependent Breit-Wigner propagator - angular momentum 1 */
__kernel void kernelmassdependentbreitwigner1dwidth(__global float * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2,__global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float p_s = fundecaymomentum(mx2, m1_2,m2_2);
	float ppart= (p_s/pmr); /* Momentum dependent part */
	float diff = mx2-mr2;
	float ppart3 = ppart*ppart*ppart;
	float mx   = sqrt(mx2); /* square root of s */
	float ww   = (mr2/mx2)*ppart3; 
	float ws   = wr*ww;
	float denom = diff*diff + mx2*ws*ws; /* common denominator */
	float denom2 = denom*denom;
	float realnom = -diff - mr2*ww;
	float imagnom = mx*ww*(denom - mx2*ws);
	output[i].x = realnom/denom2; /* real part */
	output[i].y = imagnom/denom2; /* imaginary part */
}

/* Derivative wrt. width of mass dependent Breit-Wigner propagator - angular momentum 2 */
__kernel void kernelmassdependentbreitwigner2dwidth(__global float * mx2in,  float mr, float mr2, float wr, float pmr, float m1_2, float m2_2,__global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float p_s = fundecaymomentum(mx2, m1_2,m2_2);
	float ppart= (p_s/pmr); /* Momentum dependent part */
	float diff = mx2-mr2;
	float ppart2 = ppart*ppart;
	float mx   = sqrt(mx2); /* square root of s */
	float ppart5 = ppart2*ppart2*ppart;
	float ww   = (mr2/mx2)*ppart5; 
	float ws   = wr*ww;
	float denom = diff*diff + mx2*ws*ws; /* common denominator */
	float denom2 = denom*denom;
	float realnom = -diff - mr2*ww;
	float imagnom = mx*ww*(denom - mx2*ws);
	output[i].x = realnom/denom2; /* real part */
	output[i].y = imagnom/denom2; /* imaginary part */
}

/* Derivative wrt. width of mass dependent Breit-Wigner propagator - angular momentum 3 */
__kernel void kernelmassdependentbreitwigner3dwidth(__global float * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2,__global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float p_s = fundecaymomentum(mx2, m1_2,m2_2);
	float ppart= (p_s/pmr); /* Momentum dependent part */
	float diff = mx2-mr2;
	float ppart3 = ppart*ppart*ppart;
	float mx   = sqrt(mx2); /* square root of s */
	float ppart7 = ppart3*ppart3*ppart;
	float ww   = (mr2/mx2)*ppart7; 
	float ws   = wr*ww;
	float denom = diff*diff + mx2*ws*ws; /* common denominator */
	float denom2 = denom*denom;
	float realnom = -diff - mr2*ww;
	float imagnom = mx*ww*(denom - mx2*ws);
	output[i].x = realnom/denom2; /* real part */
	output[i].y = imagnom/denom2; /* imaginary part */
}

/* Derivative wrt. width of mass dependent Breit-Wigner propagator - angular momentum 4 */
__kernel void kernelmassdependentbreitwigner4dwidth(__global float * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2,__global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float p_s = fundecaymomentum(mx2, m1_2,m2_2);
	float ppart= (p_s/pmr); /* Momentum dependent part */
	float diff = mx2-mr2;
	float ppart3 = ppart*ppart*ppart;
	float mx   = sqrt(mx2); /* square root of s */
	float ppart9 = ppart3*ppart3*ppart3;
	float ww   = (mr2/mx2)*ppart9; 
	float ws   = wr*ww;
	float denom = diff*diff + mx2*ws*ws; /* common denominator */
	float denom2 = denom*denom;
	float realnom = -diff - mr2*ww;
	float imagnom = mx*ww*(denom - mx2*ws);
	output[i].x = realnom/denom2; /* real part */
	output[i].y = imagnom/denom2; /* imaginary part */
}

/* Derivative wrt. mass of mass dependent Breit-Wigner propagator - angular momentum 0 */
__kernel void kernelmassdependentbreitwigner0dmass(__global float * mx2in,  float mr, float mr2, float wr, float pmr, float m1_2, float m2_2,__global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float ps = fundecaymomentum(mx2, m1_2,m2_2);
	float mx = sqrt(mx2);
	float mx4 =mx2*mx2;
	float mx2mr2 = mx2*mr2;
	float wr2 = wr*wr;
	float mr4 = mr2*mr2;
	float pmr2 = pmr*pmr;
	float denreal = mx4 -2.0f*mx2mr2 +mr4 - wr2*mr4*ps*ps/(mx2*pmr2);
	float denimag =2.0f/pmr * ( mx*wr*mr2*ps - mr4 * wr * ps /mx);
	float nomreal = -2.0f * mr;
	float nomimag = 3.0f*wr*mr*ps/(mx*pmr) - wr*ps*(mr2*mr-m1_2*mr-m2_2*mr)/(2.0f*mx*pmr*pmr2);
	float denom = denreal*denreal + denimag*denimag;
	output[i].x =(nomreal*denreal +nomimag*denimag)/denom;
   	output[i].y =(nomimag*denreal - nomreal*denimag)/denom;
}

/* Derivative wrt. mass of mass dependent Breit-Wigner propagator - angular momentum 1 */
__kernel void kernelmassdependentbreitwigner1dmass(__global float * mx2in,  float mr, float mr2, float wr, float pmr, float m1_2, float m2_2,__global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float ps = fundecaymomentum(mx2, m1_2,m2_2);
	float mx = sqrt(mx2);
	float mx4 =mx2*mx2;
	float mx2mr2 = mx2*mr2;
	float ps3 = ps*ps*ps;
	float wr2 = wr*wr;
	float mr4 = mr2*mr2;
	float pmr2 = pmr*pmr;
	float pmr3 = pmr*pmr2;
	float pmr5 = pmr2*pmr3;
	float denreal = mx4 -2.0f*mx2mr2 +mr4 - wr2*mr4*ps3*ps3/(mx2*pmr5*pmr);
	float denimag =2.0f/pmr3 * ( mx*wr*mr2*ps3 - mr4 * wr * ps3 /mx);
	float nomreal = -2.0f * mr;
	float nomimag = 5.0f*wr*mr*ps3/(mx*pmr3) - 3.0f*wr*ps3*(mr2*mr-m1_2*mr-m2_2*mr)/(2.0f*mx*pmr5);
	float denom = denreal*denreal + denimag*denimag;
	output[i].x =(nomreal*denreal +nomimag*denimag)/denom;
   	output[i].y =(nomimag*denreal - nomreal*denimag)/denom;
}

/* Derivative wrt. mass of mass dependent Breit-Wigner propagator - angular momentum 2 */
__kernel void kernelmassdependentbreitwigner2dmass(__global float * mx2in,  float mr, float mr2, float wr, float pmr, float m1_2, float m2_2,__global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float ps = fundecaymomentum(mx2, m1_2,m2_2);
	float mx = sqrt(mx2);
	float mx4 =mx2*mx2;
	float mx2mr2 = mx2*mr2;
	float ps2 = ps*ps;
	float ps3 = ps2*ps;
	float ps5 = ps2*ps2*ps;
	float wr2 = wr*wr;
	float mr4 = mr2*mr2;
	float pmr2 = pmr*pmr;
	float pmr3 = pmr*pmr2;
	float pmr5 = pmr2*pmr3;
	float pmr7 = pmr5*pmr2;
	float denreal = mx4 -2.0f*mx2mr2 +mr4 - wr2*mr4*ps5*ps5/(mx2*pmr5*pmr5);
	float denimag =2.0f/pmr5 * ( mx*wr*mr2*ps5 - mr4 * wr * ps5 /mx);
	float nomreal = -2.0f * mr;
	float nomimag = 7.0f*wr*mr*ps3/(mx*pmr3) - 5.0f*wr*ps5*(mr2*mr-m1_2*mr-m2_2*mr)/(2.0f*mx*pmr7);
	float denom = denreal*denreal + denimag*denimag;
	output[i].x =(nomreal*denreal +nomimag*denimag)/denom;
   	output[i].y =(nomimag*denreal - nomreal*denimag)/denom;
}

/* Derivative wrt. mass of mass dependent Breit-Wigner propagator - angular momentum 3 */
__kernel void kernelmassdependentbreitwigner3dmass(__global float * mx2in,  float mr, float mr2, float wr, float pmr, float m1_2, float m2_2,__global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float ps = fundecaymomentum(mx2, m1_2,m2_2);
	float mx = sqrt(mx2);
	float mx4 =mx2*mx2;
	float mx2mr2 = mx2*mr2;
	float ps2 = ps*ps;
	float ps3 = ps2*ps;
	float ps5 = ps2*ps2*ps;
	float ps7 = ps5*ps2;
	float wr2 = wr*wr;
	float mr4 = mr2*mr2;
	float pmr2 = pmr*pmr;
	float pmr3 = pmr*pmr2;
	float pmr5 = pmr2*pmr3;
	float pmr7 = pmr5*pmr2;
	float pmr9 = pmr7*pmr2;
	float denreal = mx4 -2.0f*mx2mr2 +mr4 - wr2*mr4*ps7*ps7/(mx2*pmr7*pmr7);
	float denimag =2.0f/pmr7 * ( mx*wr*mr2*ps7 - mr4 * wr * ps7 /mx);
	float nomreal = -2.0f * mr;
	float nomimag = 9.0f*wr*mr*ps5/(mx*pmr5) - 5.0f*wr*ps7*(mr2*mr-m1_2*mr-m2_2*mr)/(2.0f*mx*pmr9);
	float denom = denreal*denreal + denimag*denimag;
	output[i].x =(nomreal*denreal +nomimag*denimag)/denom;
   	output[i].y =(nomimag*denreal - nomreal*denimag)/denom;
}

/* Derivative wrt. mass of mass dependent Breit-Wigner propagator - angular momentum 4 */
__kernel void kernelmassdependentbreitwigner4dmass(__global float * mx2in,  float mr, float mr2, float wr, float pmr, float m1_2, float m2_2,__global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float ps = fundecaymomentum(mx2, m1_2,m2_2);
	float mx = sqrt(mx2);
	float mx4 =mx2*mx2;
	float mx2mr2 = mx2*mr2;
	float ps2 = ps*ps;
	float ps3 = ps2*ps;
	float ps5 = ps2*ps2*ps;
	float ps7 = ps5*ps2;
	float ps9 = ps7*ps2;
	float wr2 = wr*wr;
	float mr4 = mr2*mr2;
	float pmr2 = pmr*pmr;
	float pmr3 = pmr*pmr2;
	float pmr5 = pmr2*pmr3;
	float pmr7 = pmr5*pmr2;
	float pmr9 = pmr7*pmr2;
	float pmr11 = pmr9*pmr2;
	float denreal = mx4 -2.0f*mx2mr2 +mr4 - wr2*mr4*ps9*ps9/(mx2*pmr9*pmr9);
	float denimag =2.0f/pmr9 * ( mx*wr*mr2*ps9 - mr4 * wr * ps9 /mx);
	float nomreal = -2.0f * mr;
	float nomimag = 11.0f*wr*mr*ps7/(mx*pmr7) - 7.0f*wr*ps9*(mr2*mr-m1_2*mr-m2_2*mr)/(2.0f*mx*pmr11);
	float denom = denreal*denreal + denimag*denimag;
	output[i].x =(nomreal*denreal +nomimag*denimag)/denom;
   	output[i].y =(nomimag*denreal - nomreal*denimag)/denom;
}

/* Derivative wrt. width of mass dependent Breit-Wigner propagator magnitude squared - angular momentum 0 */
__kernel void kerneldmassdependentbreitwigner20dwidth(__global float * mx2in,  float mr, float mr2, float g, float pmr, float m1_2, float m2_2,__global out float * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	  float ps = fundecaymomentum(mx2, m1_2,m2_2);
      float mx4 = mx2*mx2;
      float mr4 = mr2*mr2;
      float g2 = g*g;
      float mr6 = mr4*mr2;
      float t11 = 1/mx4;
      float ps2 = ps*ps;
      float m2_4 = m2_2*m2_2;
      float m1_4 = m1_2*m1_2;
      float t25 = 1.0f/(-2.0f*mr2*m1_2+m2_4-2.0f*mr2*m2_2-2.0f*m1_2*m2_2+mr4+m1_4);
      float t29 = mx4-2.0f*mr2*mx2+mr4+4.0f*t25*ps2*t11*mr6*g2*mx2;
      float t30 = t29*t29;
      output[i] = -8.0f*t25*ps2*t11*mr6*g*mx2/t30;
 }
 
 /* Derivative wrt. width of mass dependent Breit-Wigner propagator magnitude squared - angular momentum 1 */
__kernel void kerneldmassdependentbreitwigner21dwidth(__global float * mx2in,  float mr, float mr2, float g, float pmr, float m1_2, float m2_2,__global out float * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	  float ps = fundecaymomentum(mx2, m1_2,m2_2);
      float mx4 = mx2*mx2;
      float mr4 = mr2*mr2;
      float g2 = g*g;
      float mr8 = mr4*mr4;
      float mr10 = mr8*mr2;
      float t12 = 1/mx4;
      float ps2 = ps*ps;
      float ps4 = ps2*ps2;
      float ps6 = ps4*ps2;
      float m2_4 = m2_2*m2_2;
      float m1_4 = m1_2*m1_2;
      float t27 = -2.0f*mr2*m1_2+m2_4-2.0f*mr2*m2_2-2.0f*m1_2*m2_2+mr4+m1_4;
      float t28 = t27*t27;
      float t30 = 1.0f/t28/t27;
      float t34 = mx4-2.0f*mr2*mx2+mr4+64.0f*t30*ps6*t12*mr10*g2*mx2;
      float t35 = t34*t34;
      output[i] = -128.0f*t30*ps6*t12*mr10*g*mx2/t35;
 }
 
 /* Derivative wrt. width of mass dependent Breit-Wigner propagator magnitude squared - angular momentum 2 */
__kernel void kerneldmassdependentbreitwigner22dwidth(__global float * mx2in,  float mr, float mr2, float g, float pmr, float m1_2, float m2_2,__global out float * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
 	  float ps = fundecaymomentum(mx2, m1_2,m2_2);
      float mx4 = mx2*mx2;
      float mr4 = mr2*mr2;
      float g2 = g*g;
      float mr8 = mr4*mr4;
      float mr14 = mr8*mr4*mr2;
      float t13 = 1.0f/mx4;
      float ps2 = ps*ps;
      float ps4 = ps2*ps2;
      float ps8 = ps4*ps4;
      float ps10 = ps8*ps2;
      float m2_4 = m2_2*m2_2;
      float m1_4 = m1_2*m1_2;
      float t29 = -2.0f*mr2*m1_2+m2_4-2.0f*mr2*m2_2-2.0f*m1_2*m2_2+mr4+m1_4;
      float t30 = t29*t29;
      float t31 = t30*t30;
      float t33 = 1.0f/t31/t29;
      float t37 = mx4-2.0f*mr2*mx2+mr4+1024.0f*t33*ps10*t13*mr14*g2*mx2;
      float t38 = t37*t37;
      output[i] = -2048.0f*t33*ps10*t13*mr14*g*mx2/t38;
     
 
 }
 
 
/* Derivative wrt. width of mass dependent Breit-Wigner propagator magnitude squared - angular momentum 3 */
__kernel void kerneldmassdependentbreitwigner23dwidth(__global float * mx2in,  float mr, float mr2, float g, float pmr, float m1_2, float m2_2,__global out float * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
   	  float ps = fundecaymomentum(mx2, m1_2,m2_2);
      float mx4 = mx2*mx2;
      float mr4 = mr2*mr2;
      float g2 = g*g;
      float mr8 = mr4*mr4;
      float mr16 = mr8*mr8;
      float mr18 = mr16*mr2;
      float t13 = 1.0f/mx4;
      float ps2 = ps*ps;
      float ps4 = ps2*ps2;
      float ps8 = ps4*ps4;
      float ps14 = ps8*ps4*ps2;
      float m2_4 = m2_2*m2_2;
      float m1_4 = m1_2*m1_2;
      float t30 = -2.0f*mr2*m1_2+m2_4-2.0f*mr2*m2_2-2.0f*m1_2*m2_2+mr4+m1_4;
      float t31 = t30*t30;
      float t33 = t31*t31;
      float t35 = 1.0f/t33/t31/t30;
      float t39 = mx4-2.0f*mr2*mx2+mr4+16384.0f*t35*ps14*t13*mr18*g2*mx2;
      float t40 = t39*t39;
      output[i] = -32768.0f*t35*ps14*t13*mr18*g*mx2/t40;
}

/* Derivative wrt. width of mass dependent Breit-Wigner propagator magnitude squared - angular momentum 4 */
__kernel void kerneldmassdependentbreitwigner24dwidth(__global float * mx2in,  float mr, float mr2, float g, float pmr, float m1_2, float m2_2,__global out float * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float ps = fundecaymomentum(mx2, m1_2,m2_2);
    float   mx4 = mx2*mx2;
    float  mr4 = mr2*mr2;
    float   g2 = g*g;
    float   mr8 = mr4*mr4;
    float   mr16 = mr8*mr8;
    float   mr22 = mr16*mr4*mr2;
    float   t14 = 1.0f/mx4;
    float   ps2 = ps*ps;
    float   ps4 = ps2*ps2;
    float   ps8 = ps4*ps4;
    float   ps16 = ps8*ps8;
    float   ps18 = ps16*ps2;
    float   m2_4 = m2_2*m2_2;
    float   m1_4 = m1_2*m1_2;
    float   t31 = -2.0f*mr2*m1_2+m2_4-2.0f*mr2*m2_2-2.0f*m1_2*m2_2+mr4+m1_4;
    float   t32 = t31*t31;
    float   t33 = t32*t32;
    float   t34 = t33*t33;
    float   t36 = 1.0f/t34/t31;
    float   t40 = mx4-2.0f*mr2*mx2+mr4+262144.0f*t36*ps18*t14*mr22*g2*mx2;
    float   t41 = t40*t40;
    output[i] = -524288.0f*t36*ps18*t14*mr22*g*mx2/t41;
}

/* flatte for f980 and a980 */
float2 irho(float mr2, float m1_2, float m2_2){
	float mr = sqrt(mr2);
	float poly = mr2*mr2 + m1_2*m1_2 + m2_2*m2_2 - 2*m1_2*mr2 -2*m2_2*mr2 -2*m1_2*m2_2;
    float2 ret;
	if(poly>=0) {
        ret.x = 2.0f*sqrt(poly)/(2.0f*mr2);
        ret.y = 0;
    }
    else {
        ret.x = 0;
        ret.y = 2.0f*sqrt(-1.0f*poly)/(2.0f*mr2);
    }
	return ret;
}

/* two channels */
__kernel void kernelflatte2(__global float * mx2in, float mr, float mr2, float g1, float m1a, float m1b, float g2, float m2a, float m2b, __global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float diff = mr2-mx2;/* m*m-s */
	g2 = g2*g1;
	float2 ps1 = irho(mx2, m1a*m1a, m1b*m1b);
	float2 ps2 = irho(mx2, m2a*m2a, m2b*m2b);
	float2 iws = g1*ps1+g2*ps2; /*mass dependent width */
    
    diff += iws.y;
    float ws = iws.x;
	float denom = diff*diff + ws*ws; /* common denominator*/
	
    output[i].x = diff/denom; /* real part*/
	output[i].y = ws/denom; /* imaginary part*/
}

/* three channels */
__kernel void kernelflatte3(__global float * mx2in, float mr, float mr2, float g1, float m1a, float m1b, float g2, float m2a, float m2b, float g3, float m3a, float m3b, __global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float diff = mr2-mx2;/* m*m-s */
	g2 = g2*g1;
	g3 = g3*g1;
	float2 ps1 = irho(mx2, m1a*m1a, m1b*m1b);
	float2 ps2 = irho(mx2, m2a*m2a, m2b*m2b);
	float2 ps3 = irho(mx2, m3a*m3a, m3b*m3b);
	float2 iws = g1*ps1+g2*ps2+g3*ps3; /*mass dependent width */
	
    diff += iws.y;
    float ws = iws.x;
	float denom = diff*diff + ws*ws; /* common denominator*/
	
    output[i].x = diff/denom; /* real part*/
	output[i].y = ws/denom; /* imaginary part*/
}

/* four channels */
__kernel void kernelflatte4(__global float * mx2in, float mr, float mr2, float g1, float m1a, float m1b, float g2, float m2a, float m2b, float g3, float m3a, float m3b, float g4, float m4a, float m4b, __global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	float diff = mr2-mx2;/* m*m-s */
	g2 = g2*g1;
	g3 = g3*g1;
	g4 = g4*g1;
	float2 ps1 = irho(mx2, m1a*m1a, m1b*m1b);
	float2 ps2 = irho(mx2, m2a*m2a, m2b*m2b);
	float2 ps3 = irho(mx2, m3a*m3a, m3b*m3b);
	float2 ps4 = irho(mx2, m4a*m4a, m4b*m4b);
	float2 iws = g1*ps1+g2*ps2+g3*ps3+g4*ps4; /*mass dependent width */
	
    diff += iws.y;
    float ws = iws.x;
	float denom = diff*diff + ws*ws; /* common denominator*/
	
	output[i].x = diff/denom; /* real part*/
	output[i].y = ws/denom; /* imaginary part*/
}
/* end for flatte */

/* for sigma(500) */
float rho4pi(float s){
  //float mpi=0.13957018;
  float mpi=0.13957f;
  float tmp=1.0f-16.0f*mpi*mpi/s;
  if(tmp<=0) return 0.0f;
  else return sqrt(tmp)/(1.0f+exp(9.8f-3.5f*s));
}

float rho2pi(float s){
  //float mpi=0.13957018;
  float mpi=0.13957f;
  if(s<=4.0f*mpi*mpi) return 0.0f;
  else return sqrt(1.0f-4.0f*mpi*mpi/s);
}

__kernel void kernelsigma(__global float * mx2in, __global out float2 * output){
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
  float mr = 0.9264f;
  float mr2 = mr*mr;
  float diff = mr2-mx2;/* m*m-s */
  //float mpi=0.13957018;
  float mpi=0.13957f;
  float g1=(0.5843f+1.6663f*mx2)*(mx2-mpi*mpi/2.0f)/(mr2-mpi*mpi/2.0f)*exp(-(mx2-mr2)/1.082f);
  float g2=0.0024f;
  float w1=g1*rho2pi(mx2)/rho2pi(mr2);
  float w2=g2*rho4pi(mx2)/rho4pi(mr2);
  float ws=mr*(w1+w2);
  float denom=diff*diff+ws*ws;
  output[i].x=diff/denom;
  output[i].y=ws/denom;
}
/* end for sigma(500) */

/* for K-matrix as in partial wave analysis in K-matrix formalism by S.U.Chung and e.t. */
/*break up momentum (square)*/

float fundecaymomentum2(float mr2, float m1_2, float m2_2){
	float mr = sqrt(mr2);
	float poly = mr2*mr2 + m1_2*m1_2 + m2_2*m2_2 - 2*m1_2*mr2 -2*m2_2*mr2 -2*m1_2*m2_2;
	float ret = poly/(4.0f*mr2);
	if(sqrt(m1_2) +sqrt(m2_2) > mr)
		ret = 0.0f;
	return ret;
}
/*Blatt-Weisskopf barrier factors */
float f0(float q2){
       return 1.0f;
}
float f1(float q2){
       float z=q2/(0.22f/3.0f);
       float ret =sqrt(2.0f*z/(z+1.0f));
       return ret;
}
float f2(float q2){
       float z=q2/(0.22f/3.0f);
       float ret =sqrt(13.0f*z*z/((z-3.0f)*(z-3.0f)+9.0f*z));
       return ret;
}
float f3(float q2){
       float z=q2/(0.22f/3.0f);
       float ret =sqrt(277.0f*z*z*z/(z*(z-15.0f)*(z-15.0f)+9.0f*(2.0f*z-5.0f)));
       return ret;
}
float f4(float q2){
       float z=q2/(0.22f/3.0f);
       float ret =sqrt(12746.0f*z*z*z*z/((z*z-45.0f*z+105)*(z*z-45.0f*z+105.0f)+25.0f*z*(2.0f*z-21.0f)*(2.0f*z-21.0f)));
       return ret;
}
/* mass dependent width for l=0*/
float gamma0(float m_2, float mr, float wr, float m1_2, float m2_2) {
      float q=fundecaymomentum2(m_2, m1_2, m2_2);
      float q0=fundecaymomentum2(mr*mr, m1_2, m2_2);
      float gamma=wr*mr/sqrt(m_2)*q/q0;
      return gamma;
}
/* mass dependent width for l=1*/
float gamma1(float m_2, float mr, float wr, float m1_2, float m2_2) {
      float q=fundecaymomentum2(m_2, m1_2, m2_2);
      float q0=fundecaymomentum2(mr*mr, m1_2, m2_2);
      float b1=f1(q)/f1(q0);
      float gamma=wr*mr/sqrt(m_2)*q/q0*b1*b1;
      return gamma;
}
/* mass dependent width for l=2*/
float gamma2(float m_2, float mr, float wr, float m1_2, float m2_2) {
      float q=fundecaymomentum2(m_2, m1_2, m2_2);
      float q0=fundecaymomentum2(mr*mr, m1_2, m2_2);
      float b2=f2(q)/f2(q0);
      float gamma=wr*mr/sqrt(m_2)*q/q0*b2*b2;
      return gamma;
}
/* mass dependent width for l=3*/
float gamma3(float m_2, float mr, float wr, float m1_2, float m2_2) {
      float q=fundecaymomentum2(m_2,m1_2, m2_2);
      float q0=fundecaymomentum2(mr*mr,m1_2, m2_2);
      float b3=f3(q)/f3(q0);
      float gamma=wr*mr/sqrt(m_2)*q/q0*b3*b3;
      return gamma;
}
/* mass dependent width for l=4*/
float gamma4(float m_2, float mr, float wr, float m1_2, float m2_2) {
      float q=fundecaymomentum2(m_2, m1_2, m2_2);
      float q0=fundecaymomentum2(mr*mr, m1_2, m2_2);
      float b4=f4(q)/f4(q0);
      float gamma=wr*mr/sqrt(m_2)*q/q0*b4*b4;
      return gamma;
}
/*K-matrix of 2 scalar resonances in 1 channel */
float K_2_scalar(float m_2, float mr1, float wr1, float mr2, float wr2, float c, float m1_2, float m2_2){
     float width1=gamma0(m_2, mr1, wr1, m1_2, m2_2);
     float width2=gamma0(m_2, mr2, wr2, m1_2, m2_2);
     float k1= mr1*width1/(mr1*mr1-m_2);
     float k2= mr2*width2/(mr2*mr2-m_2);
     float k=k1+k2+c;
     return k;
}
/*P-vector of 2 scalar resonances in 1 channel */
float2 P_2_scalar(float m_2, float mr1, float wr1, float x1, float y1, float mr2, float wr2, float x2, float y2, float2 d, float m1_2, float m2_2){
    float width1=gamma0(m_2, mr1, wr1, m1_2, m2_2);	
    float width2=gamma0(m_2, mr2, wr2, m1_2, m2_2);
    float r1= sqrt(mr1*width1)/(mr1*mr1-m_2);
    float2 p1;
    p1.x= r1*x1;
    p1.y= r1*y1;
    float r2= sqrt(mr2*width2)/(mr2*mr2-m_2);
    float2 p2;
    p2.x= r2*x2;
    p2.y= r2*y2;     
    float2 p=p1+p2+d;
    return p;
}
/*F-function of 2 scalar resonances in 1 channel */
float2 F_2_scalar(float m_2, float mr1, float wr1, float x1, float y1, float mr2, float wr2, float x2, float y2, float c, float2 d, float m1_2, float m2_2){
     float width1=gamma0(m_2, mr1, wr1, m1_2, m2_2);
     float width2=gamma0(m_2, mr2, wr2, m1_2, m2_2);
     float d1=mr1*mr1-m_2;
     float d2=mr2*mr2-m_2;
     float n1=mr1*width1;
     float n2=mr2*width2;
     float k1= n1/d1;
     float k2= n2/d2;
     float k=k1+k2+c;
     float r1= sqrt(n1)/d1;
     float2 p1;
     p1.x= r1*x1;
     p1.y= r1*y1;
     float r2= sqrt(n2)/d2;
     float2 p2;
     p2.x= r2*x2;
     p2.y= r2*y2;     
     float2 p=p1+p2+d;
     float2 f;
     float dom=1.0f+k*k;
     f.x=(p.x-p.y*k)/dom;
     f.y=p.y+p.x*k;
     return f;
}
float2 F_n_scalar(int n, float m_2, float* mr, float* wr, float* x, float* y, float c, float cs, float2 d,float2 ds, float m1_2, float m2_2){

     float k=0.0f;
     float2 p=(float2)(0.0f,0.0f);
     float width_,r_,n_,d_,q_,qr_;
     for (int i=0;i<n;i=i+1){
          q_=fundecaymomentum2(m_2, m1_2, m2_2);
          qr_=fundecaymomentum2(mr[i]*mr[i], m1_2, m2_2);
          width_=wr[i]*mr[i]/sqrt(m_2)*q_/qr_;
          d_=mr[i]*mr[i]-m_2;
          n_=mr[i]*width_;
          k += n_/d_;
          r_=sqrt(n_)/d_;
          p.x += r_*x[i];
          p.y += r_*y[i];

     } 
     k=k+c+cs*m_2;
     p=p+d+ds*m_2;
     float2 f;
     float dom=1.0f+k*k;
     f.x=(p.x-p.y*k)/dom;
     f.y=p.y+p.x*k;
     return f;
}

__kernel void kernelfnscalarzou(__global float * mx2in, uint n, __global float4 *par, float c, float cs, float2 d,float2 ds, float m1_2, float m2_2, __global out float2 * output)
{
        uint index = get_global_id(0);
        float k=0.0f;
        float px=0.0f;
        float py=0.0f;
        uint i;
        float m_2=mx2in[index];
        float rho_=sqrt(1.0f-4.0f*m1_2/m_2);
	float d_;	  
        float g_;
	float r_;
        for (i=0;i<n;i=i+1){
        g_=sqrt(par[i].x*par[i].y/rho_);/* g_= par[i].y; */
	d_=par[i].x*par[i].x-m_2;
	r_=g_/d_;
	k=k+g_*r_;
	px=px+par[i].z*r_;
	py=py+par[i].w*r_;
        } 
	k=k+c+cs*m_2;
	px=px+d.x+ds.x*m_2;
	py=py+d.y+ds.y*m_2;
	float dom= 1.0f+rho_*rho_*k*k;
       /* F of K */
        output[index].x=(px-rho_*k*py)/dom; 
        output[index].y= (px*rho_*k+py)/dom; 
       /* T of K */
       /* output[index].x=(k)/dom; */
       /* output[index].y= (k*rho_*k)/dom; */ 
}
__kernel void kernelfnscalarcm2(__global float * mx2in, uint n, __global float4 *par, float c, float cs, float2 d,float2 ds, float m1_2, float m2_2, __global out float2 * output)
{
uint index = get_global_id(0);
  float m_2=mx2in[index];
float a1= par[0].z;
float b1= par[0].w;
float a2= par[1].z;
float b2= par[1].w;
float m1= par[0].x;
float w1= par[0].y;
float m2= par[1].x;
float w2= par[1].y;
float q=fundecaymomentum2(m_2, m1_2, m2_2);	
float q1=fundecaymomentum2(m1*m1, m1_2, m2_2);
float q2=fundecaymomentum2(m2*m2, m1_2, m2_2);
float g1= w1*m1/sqrt(m_2)*sqrt(q)/sqrt(q1);
float g2= w2*m2/sqrt(m_2)*sqrt(q)/sqrt(q2);
float tmp1=(m1*m1-m_2);
float tmp2=(m2*m2-m_2);
float tmp3=((-g1*g1/(m1*m1-m_2)-g2*g2/(m2*m2-m_2))*(-g1*g1/(m1*m1-m_2)-g2*g2/(m2*m2-m_2))+1.0f);
output[index].x=- (b1*g1*g1*g1)/(tmp1*tmp1*tmp3) - (b2*g2*g1*g1)/(tmp1*tmp2*tmp3)+(a1*g1)/(tmp1*tmp3)-(b1*g2*g2*g1)/(tmp1*tmp2*tmp3)+(a2*g2)/(tmp2*tmp3)-(b2*g2*g2*g2)/(tmp2*tmp2*tmp3);
output[index].y= (a1*g1*g1*g1)/(tmp1*tmp1*tmp3)+(a2*g2*g1)/(tmp1*tmp2*tmp3)+(b1*g1)/(tmp1*tmp3)+a1*g2*g2*g1/(tmp1*tmp2*tmp3)+(b2*g2)/(tmp2*tmp3)+(a2*g2*g2*g2)/(tmp2*tmp2*tmp3);
}

__kernel void kernelfnscalarcm(__global float * mx2in, uint n, __global float4 *par, float c, float cs, float2 d,float2 ds, float m1_2, float m2_2, __global out float2 * output){
uint index = get_global_id(0);
float m_2=mx2in[index];
uint i;
float k=0.0f;
float px=0.0f;
float py=0.0f;
float q0=fundecaymomentum(m_2, m1_2, m2_2);
float rho0=q0/sqrt(m_2);
for (i=0;i<n;i=i+1){
float q=fundecaymomentum(par[i].x*par[i].x, m1_2, m2_2);
/*float rho=q/par[i].x; */
/*float gamma=par[i].y/rho;*/
/*float g_2=par[i].x*gamma;*/
/*float dom=par[i].x*par[i].x-m_2;*/
/*float r=g_2/dom;*/
float r=par[i].x*(par[i].y*par[i].x/q)/(par[i].x*par[i].x-m_2);
k=k+r;
px=px+par[i].z*r;
py=py+par[i].w*r;
}
k=k+c+cs*m_2;
px=px+d.x+ds.x*m_2;
py=py+d.y+ds.y*m_2;

float dom_= 1.0f+rho0*rho0*k*k;
/* F of K */
output[index].x=(px-rho0*k*py)/dom_; 
output[index].y= (px*rho0*k+py)/dom_; 
/* T of K */
/* output[index].x=(k)/dom_; */
/* output[index].y= (k*rho0*k)/dom_;*/  
}

__kernel void kernelfnscalarchung(__global float * mx2in, uint n, __global float4 *par, float c, float cs, float2 d,float2 ds, float m1_2, float m2_2, __global out float2 * output)
{
uint index = get_global_id(0);
float m_2=mx2in[index];

uint i;
float k=0.0f;
float px=0.0f;
float py=0.0f;
float tbwx=0.0f;
float tbwy=0.0f;
float q0=fundecaymomentum(m_2, m1_2, m2_2);
for (i=0;i<n;i=i+1){
float q=fundecaymomentum(par[i].x*par[i].x, m1_2, m2_2);
float g_2=par[i].x*par[i].y*par[i].x/sqrt(m_2)*q0/q; /* f(90) */
float dom = par[i].x*par[i].x-m_2;
float r = par[i].x*par[i].y/dom;  /* f(102) */
k=k+g_2/dom;  /* f(89) */
px=px+par[i].z*r;
py=py+par[i].w*r;
/*float bwd=dom*dom+g_2*g_2;*/
/*tbwx=tbwx+ g_2*dom/bwd;*/
/*tbwy=tbwy+ g_2*g_2/bwd;*/
}
k=k+c+cs*m_2;
px=px+d.x+ds.x*m_2;
py=py+d.y+ds.y*m_2;

/* F of P K */
 output[index].x=(px-py*k)/(1.0f+k*k); 
 output[index].y=(px*k+py)/(1.0f+k*k);

/* T of K*/
/* output[index].x=(k)/(1.0f+k*k); */ 
/* output[index].y=(k*k)/(1.0f+k*k); */

/* T of BW*/
/*output[index].x=tbwx;*/
/*output[index].y=tbwy;*/

}

/* dispersive correction 2016-03-25 */
__const float dispersive_correction_EtaPi[2701] = 
{
0.559952, 0.557936, 0.55592, 0.553904, 0.551889, 0.549874, 0.547859,
0.545845, 0.543832, 0.541819, 0.539807, 0.537795, 0.535784, 0.533774,
0.531764, 0.529756, 0.527748, 0.525741, 0.523735, 0.52173, 0.519726,
0.517723, 0.515721, 0.51372, 0.51172, 0.509722, 0.507724, 0.505728,
0.503734, 0.50174, 0.499748, 0.497758, 0.495768, 0.493781, 0.491794,
0.48981, 0.487827, 0.485845, 0.483865, 0.481887, 0.47991, 0.477935,
0.475962, 0.473991, 0.472021, 0.470054, 0.468088, 0.466124, 0.464162,
0.462202, 0.460243, 0.458287, 0.456333, 0.454381, 0.452431, 0.450483,
0.448537, 0.446594, 0.444652, 0.442713, 0.440776, 0.438841, 0.436909,
0.434979, 0.433051, 0.431125, 0.429202, 0.427282, 0.425363, 0.423447,
0.421534, 0.419623, 0.417714, 0.415808, 0.413905, 0.412004, 0.410106,
0.40821, 0.406317, 0.404426, 0.402538, 0.400653, 0.398771, 0.396891,
0.395014, 0.39314, 0.391268, 0.389399, 0.387533, 0.38567, 0.38381,
0.381952, 0.380098, 0.378246, 0.376397, 0.374551, 0.372708, 0.370868,
0.369031, 0.367196, 0.365365, 0.363537, 0.361712, 0.35989, 0.35807,
0.356254, 0.354441, 0.352631, 0.350824, 0.349021, 0.34722, 0.345423,
0.343628, 0.341837, 0.340049, 0.338264, 0.336482, 0.334704, 0.332929,
0.331156, 0.329388, 0.327622, 0.32586, 0.324101, 0.322345, 0.320592,
0.318843, 0.317097, 0.315355, 0.313615, 0.311879, 0.310147, 0.308417,
0.306692, 0.304969, 0.30325, 0.301534, 0.299822, 0.298113, 0.296407,
0.294705, 0.293006, 0.291311, 0.289619, 0.287931, 0.286246, 0.284564,
0.282887, 0.281212, 0.279541, 0.277873, 0.276209, 0.274549, 0.272892,
0.271238, 0.269588, 0.267942, 0.266299, 0.264659, 0.263024, 0.261391,
0.259763, 0.258137, 0.256516, 0.254898, 0.253283, 0.251672, 0.250065,
0.248461, 0.246861, 0.245265, 0.243672, 0.242082, 0.240497, 0.238915,
0.237336, 0.235761, 0.23419, 0.232623, 0.231059, 0.229498, 0.227942,
0.226389, 0.224839, 0.223293, 0.221751, 0.220213, 0.218678, 0.217147,
0.21562, 0.214096, 0.212576, 0.211059, 0.209546, 0.208037, 0.206532,
0.20503, 0.203532, 0.202038, 0.200547, 0.19906, 0.197577, 0.196097,
0.194621, 0.193149, 0.19168, 0.190216, 0.188754, 0.187297, 0.185843,
0.184393, 0.182947, 0.181504, 0.180065, 0.17863, 0.177198, 0.17577,
0.174346, 0.172926, 0.171509, 0.170096, 0.168686, 0.167281, 0.165879,
0.164481, 0.163086, 0.161695, 0.160308, 0.158925, 0.157545, 0.156169,
0.154796, 0.153428, 0.152063, 0.150702, 0.149344, 0.14799, 0.14664,
0.145294, 0.143951, 0.142612, 0.141276, 0.139945, 0.138617, 0.137293,
0.135972, 0.134655, 0.133342, 0.132032, 0.130726, 0.129424, 0.128126,
0.126831, 0.12554, 0.124252, 0.122968, 0.121688, 0.120412, 0.119139,
0.11787, 0.116604, 0.115342, 0.114084, 0.11283, 0.111579, 0.110332,
0.109088, 0.107848, 0.106612, 0.105379, 0.10415, 0.102925, 0.101703,
0.100485, 0.0992709, 0.0980601, 0.0968529, 0.0956494, 0.0944494,
0.0932531, 0.0920604, 0.0908713, 0.0896858, 0.0885039, 0.0873256,
0.0861509, 0.0849798, 0.0838122, 0.0826483, 0.081488, 0.0803312,
0.079178, 0.0780284, 0.0768824, 0.07574, 0.0746011, 0.0734657,
0.072334, 0.0712057, 0.0700811, 0.06896, 0.0678424, 0.0667283,
0.0656178, 0.0645109, 0.0634074, 0.0623075, 0.0612112, 0.0601183,
0.0590289, 0.0579431, 0.0568608, 0.0557819, 0.0547066, 0.0536348,
0.0525664, 0.0515016, 0.0504402, 0.0493823, 0.0483279, 0.0472769,
0.0462294, 0.0451854, 0.0441448, 0.0431077, 0.0420741, 0.0410438,
0.0400171, 0.0389937, 0.0379738, 0.0369573, 0.0359443, 0.0349346,
0.0339284, 0.0329256, 0.0319262, 0.0309302, 0.0299376, 0.0289483,
0.0279625, 0.0269801, 0.026001, 0.0250253, 0.024053, 0.023084,
0.0221184, 0.0211561, 0.0201972, 0.0192417, 0.0182895, 0.0173406,
0.016395, 0.0154528, 0.0145139, 0.0135783, 0.012646, 0.0117171,
0.0107914, 0.00986903, 0.00894995, 0.00803416, 0.00712164,
0.00621241, 0.00530644, 0.00440374, 0.0035043, 0.00260812,
0.00171519, 0.0008255, -0.0000609453, -0.000944155, -0.00182413,
-0.00270089, -0.00357442, -0.00444474, -0.00531185, -0.00617576,
-0.00703647, -0.00789398, -0.0087483, -0.00959944, -0.0104474,
-0.0112922, -0.0121338, -0.0129723, -0.0138076, -0.0146397,
-0.0154687, -0.0162946, -0.0171173, -0.0179369, -0.0187534,
-0.0195668, -0.020377, -0.0211842, -0.0219882, -0.0227891, -0.023587,
-0.0243817, -0.0251734, -0.025962, -0.0267476, -0.02753, -0.0283095,
-0.0290858, -0.0298591, -0.0306294, -0.0313966, -0.0321608,
-0.032922, -0.0336802, -0.0344353, -0.0351875, -0.0359366,
-0.0366828, -0.0374259, -0.0381661, -0.0389033, -0.0396375,
-0.0403687, -0.041097, -0.0418223, -0.0425447, -0.0432641,
-0.0439806, -0.0446942, -0.0454048, -0.0461125, -0.0468173,
-0.0475192, -0.0482181, -0.0489142, -0.0496074, -0.0502977,
-0.0509851, -0.0516696, -0.0523513, -0.0530301, -0.053706,
-0.0543791, -0.0550494, -0.0557168, -0.0563813, -0.057043, -0.057702,
-0.058358, -0.0590113, -0.0596618, -0.0603095, -0.0609543,
-0.0615964, -0.0622357, -0.0628723, -0.063506, -0.064137, -0.0647653,
-0.0653907, -0.0660135, -0.0666335, -0.0672507, -0.0678652,
-0.068477, -0.0690861, -0.0696925, -0.0702962, -0.0708971,
-0.0714954, -0.072091, -0.0726839, -0.0732741, -0.0738617,
-0.0744465, -0.0750288, -0.0756083, -0.0761853, -0.0767596,
-0.0773312, -0.0779002, -0.0784666, -0.0790304, -0.0795916,
-0.0801502, -0.0807061, -0.0812595, -0.0818103, -0.0823585,
-0.0829041, -0.0834472, -0.0839877, -0.0845256, -0.085061,
-0.0855938, -0.0861241, -0.0866519, -0.0871772, -0.0876999,
-0.0882201, -0.0887378, -0.0892529, -0.0897656, -0.0902758,
-0.0907835, -0.0912888, -0.0917915, -0.0922918, -0.0927896,
-0.093285, -0.0937779, -0.0942684, -0.0947564, -0.095242, -0.0957252,
-0.0962059, -0.0966843, -0.0971602, -0.0976337, -0.0981049,
-0.0985736, -0.0990399, -0.0995039, -0.0999655, -0.100425, -0.100882,
-0.101336, -0.101788, -0.102238, -0.102686, -0.103131, -0.103574,
-0.104014, -0.104452, -0.104888, -0.105322, -0.105753, -0.106182,
-0.106609, -0.107033, -0.107455, -0.107875, -0.108293, -0.108708,
-0.109121, -0.109532, -0.109941, -0.110347, -0.110751, -0.111153,
-0.111553, -0.111951, -0.112346, -0.112739, -0.11313, -0.113519,
-0.113905, -0.11429, -0.114672, -0.115052, -0.11543, -0.115806,
-0.116179, -0.116551, -0.11692, -0.117287, -0.117652, -0.118015,
-0.118376, -0.118735, -0.119092, -0.119446, -0.119799, -0.120149,
-0.120498, -0.120844, -0.121188, -0.12153, -0.12187, -0.122208,
-0.122544, -0.122878, -0.12321, -0.12354, -0.123868, -0.124194,
-0.124518, -0.12484, -0.12516, -0.125478, -0.125794, -0.126107,
-0.126419, -0.126729, -0.127037, -0.127344, -0.127648, -0.12795,
-0.12825, -0.128548, -0.128845, -0.129139, -0.129432, -0.129723,
-0.130011, -0.130298, -0.130583, -0.130866, -0.131147, -0.131427,
-0.131704, -0.13198, -0.132253, -0.132525, -0.132795, -0.133063,
-0.13333, -0.133594, -0.133857, -0.134118, -0.134377, -0.134634,
-0.134889, -0.135143, -0.135395, -0.135645, -0.135893, -0.136139,
-0.136384, -0.136627, -0.136868, -0.137107, -0.137345, -0.137581,
-0.137815, -0.138048, -0.138278, -0.138507, -0.138735, -0.13896,
-0.139184, -0.139406, -0.139627, -0.139845, -0.140062, -0.140278,
-0.140491, -0.140703, -0.140914, -0.141123, -0.14133, -0.141535,
-0.141739, -0.141941, -0.142141, -0.14234, -0.142538, -0.142733,
-0.142927, -0.14312, -0.14331, -0.1435, -0.143687, -0.143873,
-0.144058, -0.144241, -0.144422, -0.144602, -0.14478, -0.144956,
-0.145132, -0.145305, -0.145477, -0.145647, -0.145816, -0.145984,
-0.14615, -0.146314, -0.146477, -0.146638, -0.146798, -0.146957,
-0.147113, -0.147269, -0.147423, -0.147575, -0.147726, -0.147876,
-0.148024, -0.14817, -0.148315, -0.148459, -0.148601, -0.148742,
-0.148882, -0.14902, -0.149156, -0.149291, -0.149425, -0.149557,
-0.149688, -0.149818, -0.149946, -0.150073, -0.150198, -0.150322,
-0.150445, -0.150566, -0.150686, -0.150805, -0.150922, -0.151038,
-0.151152, -0.151265, -0.151377, -0.151488, -0.151597, -0.151705,
-0.151811, -0.151917, -0.152021, -0.152123, -0.152225, -0.152325,
-0.152424, -0.152521, -0.152617, -0.152712, -0.152806, -0.152899,
-0.15299, -0.15308, -0.153168, -0.153256, -0.153342, -0.153427,
-0.153511, -0.153593, -0.153675, -0.153755, -0.153834, -0.153911,
-0.153988, -0.154063, -0.154137, -0.15421, -0.154282, -0.154353,
-0.154422, -0.15449, -0.154557, -0.154623, -0.154688, -0.154751,
-0.154814, -0.154875, -0.154935, -0.154994, -0.155052, -0.155109,
-0.155165, -0.155219, -0.155273, -0.155325, -0.155376, -0.155426,
-0.155475, -0.155523, -0.15557, -0.155616, -0.15566, -0.155704,
-0.155747, -0.155788, -0.155828, -0.155868, -0.155906, -0.155943,
-0.15598, -0.156015, -0.156049, -0.156082, -0.156114, -0.156145,
-0.156175, -0.156204, -0.156232, -0.156259, -0.156285, -0.15631,
-0.156334, -0.156357, -0.15638, -0.156401, -0.156421, -0.15644,
-0.156458, -0.156475, -0.156491, -0.156507, -0.156521, -0.156534,
-0.156547, -0.156558, -0.156569, -0.156579, -0.156587, -0.156595,
-0.156602, -0.156608, -0.156613, -0.156617, -0.15662, -0.156622,
-0.156624, -0.156624, -0.156624, -0.156623, -0.156621, -0.156618,
-0.156614, -0.156609, -0.156603, -0.156597, -0.15659, -0.156581,
-0.156572, -0.156562, -0.156552, -0.15654, -0.156528, -0.156515,
-0.1565, -0.156486, -0.15647, -0.156453, -0.156436, -0.156418,
-0.156399, -0.156379, -0.156359, -0.156337, -0.156315, -0.156292,
-0.156268, -0.156244, -0.156219, -0.156193, -0.156166, -0.156138,
-0.15611, -0.156081, -0.156051, -0.15602, -0.155989, -0.155957,
-0.155924, -0.155891, -0.155856, -0.155821, -0.155785, -0.155749,
-0.155712, -0.155674, -0.155635, -0.155596, -0.155556, -0.155515,
-0.155474, -0.155431, -0.155389, -0.155345, -0.155301, -0.155256,
-0.15521, -0.155164, -0.155117, -0.15507, -0.155021, -0.154972,
-0.154923, -0.154873, -0.154822, -0.15477, -0.154718, -0.154665,
-0.154612, -0.154558, -0.154503, -0.154447, -0.154392, -0.154335,
-0.154278, -0.15422, -0.154161, -0.154102, -0.154043, -0.153982,
-0.153921, -0.15386, -0.153798, -0.153735, -0.153672, -0.153608,
-0.153544, -0.153479, -0.153413, -0.153347, -0.15328, -0.153213,
-0.153145, -0.153077, -0.153008, -0.152938, -0.152868, -0.152798,
-0.152726, -0.152655, -0.152582, -0.15251, -0.152436, -0.152362,
-0.152288, -0.152213, -0.152138, -0.152062, -0.151985, -0.151908,
-0.151831, -0.151753, -0.151674, -0.151595, -0.151516, -0.151436,
-0.151355, -0.151274, -0.151193, -0.151111, -0.151029, -0.150946,
-0.150862, -0.150778, -0.150694, -0.150609, -0.150524, -0.150438,
-0.150352, -0.150266, -0.150178, -0.150091, -0.150003, -0.149914,
-0.149826, -0.149736, -0.149647, -0.149556, -0.149466, -0.149375,
-0.149283, -0.149191, -0.149099, -0.149006, -0.148913, -0.148819,
-0.148725, -0.148631, -0.148536, -0.148441, -0.148345, -0.148249,
-0.148153, -0.148056, -0.147959, -0.147861, -0.147763, -0.147665,
-0.147566, -0.147467, -0.147368, -0.147268, -0.147168, -0.147067,
-0.146966, -0.146865, -0.146763, -0.146661, -0.146559, -0.146456,
-0.146353, -0.146249, -0.146146, -0.146041, -0.145937, -0.145832,
-0.145727, -0.145621, -0.145516, -0.145409, -0.145303, -0.145196,
-0.145089, -0.144981, -0.144874, -0.144766, -0.144657, -0.144548,
-0.144439, -0.14433, -0.14422, -0.14411, -0.144, -0.14389, -0.143779,
-0.143668, -0.143556, -0.143444, -0.143332, -0.14322, -0.143108,
-0.142995, -0.142882, -0.142768, -0.142654, -0.14254, -0.142426,
-0.142312, -0.142197, -0.142082, -0.141967, -0.141851, -0.141735,
-0.141619, -0.141503, -0.141386, -0.14127, -0.141152, -0.141035,
-0.140918, -0.1408, -0.140682, -0.140563, -0.140445, -0.140326,
-0.140207, -0.140088, -0.139969, -0.139849, -0.139729, -0.139609,
-0.139489, -0.139368, -0.139247, -0.139126, -0.139005, -0.138884,
-0.138762, -0.13864, -0.138518, -0.138396, -0.138274, -0.138151,
-0.138028, -0.137905, -0.137782, -0.137659, -0.137535, -0.137412,
-0.137288, -0.137163, -0.137039, -0.136915, -0.13679, -0.136665,
-0.13654, -0.136415, -0.13629, -0.136164, -0.136038, -0.135912,
-0.135786, -0.13566, -0.135534, -0.135407, -0.135281, -0.135154,
-0.135027, -0.1349, -0.134772, -0.134645, -0.134517, -0.13439,
-0.134262, -0.134134, -0.134006, -0.133877, -0.133749, -0.13362,
-0.133492, -0.133363, -0.133234, -0.133105, -0.132976, -0.132846,
-0.132717, -0.132587, -0.132457, -0.132328, -0.132198, -0.132068,
-0.131937, -0.131807, -0.131677, -0.131546, -0.131415, -0.131285,
-0.131154, -0.131023, -0.130892, -0.130761, -0.130629, -0.130498,
-0.130367, -0.130235, -0.130103, -0.129972, -0.12984, -0.129708,
-0.129576, -0.129444, -0.129312, -0.129179, -0.129047, -0.128915,
-0.128782, -0.12865, -0.128517, -0.128384, -0.128251, -0.128118,
-0.127986, -0.127852, -0.127719, -0.127586, -0.127453, -0.12732,
-0.127186, -0.127053, -0.126919, -0.126786, -0.126652, -0.126519,
-0.126385, -0.126251, -0.126117, -0.125983, -0.125849, -0.125716,
-0.125581, -0.125447, -0.125313, -0.125179, -0.125045, -0.124911,
-0.124776, -0.124642, -0.124508, -0.124373, -0.124239, -0.124104,
-0.12397, -0.123835, -0.123701, -0.123566, -0.123431, -0.123297,
-0.123162, -0.123027, -0.122893, -0.122758, -0.122623, -0.122488,
-0.122354, -0.122219, -0.122084, -0.121949, -0.121814, -0.121679,
-0.121544, -0.121409, -0.121274, -0.121139, -0.121004, -0.120869,
-0.120734, -0.120599, -0.120464, -0.12033, -0.120195, -0.12006,
-0.119925, -0.11979, -0.119655, -0.11952, -0.119385, -0.11925,
-0.119115, -0.11898, -0.118845, -0.11871, -0.118575, -0.11844,
-0.118305, -0.11817, -0.118035, -0.1179, -0.117765, -0.11763,
-0.117496, -0.117361, -0.117226, -0.117091, -0.116956, -0.116822,
-0.116687, -0.116552, -0.116418, -0.116283, -0.116148, -0.116014,
-0.115879, -0.115745, -0.11561, -0.115476, -0.115341, -0.115207,
-0.115073, -0.114938, -0.114804, -0.11467, -0.114535, -0.114401,
-0.114267, -0.114133, -0.113999, -0.113865, -0.113731, -0.113597,
-0.113463, -0.113329, -0.113195, -0.113062, -0.112928, -0.112794,
-0.112661, -0.112527, -0.112393, -0.11226, -0.112126, -0.111993,
-0.11186, -0.111727, -0.111593, -0.11146, -0.111327, -0.111194,
-0.111061, -0.110928, -0.110795, -0.110662, -0.11053, -0.110397,
-0.110264, -0.110132, -0.109999, -0.109867, -0.109734, -0.109602,
-0.10947, -0.109338, -0.109205, -0.109073, -0.108941, -0.108809,
-0.108678, -0.108546, -0.108414, -0.108282, -0.108151, -0.108019,
-0.107888, -0.107757, -0.107625, -0.107494, -0.107363, -0.107232,
-0.107101, -0.10697, -0.106839, -0.106709, -0.106578, -0.106447,
-0.106317, -0.106186, -0.106056, -0.105926, -0.105796, -0.105666,
-0.105536, -0.105406, -0.105276, -0.105146, -0.105016, -0.104887,
-0.104757, -0.104628, -0.104499, -0.104369, -0.10424, -0.104111,
-0.103982, -0.103854, -0.103725, -0.103596, -0.103467, -0.103339,
-0.103211, -0.103082, -0.102954, -0.102826, -0.102698, -0.10257,
-0.102442, -0.102314, -0.102187, -0.102059, -0.101932, -0.101805,
-0.101677, -0.10155, -0.101423, -0.101296, -0.101169, -0.101043,
-0.100916, -0.100789, -0.100663, -0.100537, -0.10041, -0.100284,
-0.100158, -0.100032, -0.0999066, -0.0997809, -0.0996553, -0.0995299,
-0.0994045, -0.0992792, -0.0991541, -0.099029, -0.0989041,
-0.0987792, -0.0986545, -0.0985299, -0.0984054, -0.098281,
-0.0981567, -0.0980325, -0.0979084, -0.0977845, -0.0976606,
-0.0975369, -0.0974133, -0.0972898, -0.0971664, -0.0970431, -0.09692,
-0.0967969, -0.096674, -0.0965512, -0.0964285, -0.0963059,
-0.0961834, -0.0960611, -0.0959388, -0.0958167, -0.0956947,
-0.0955728, -0.0954511, -0.0953294, -0.0952079, -0.0950865,
-0.0949652, -0.0948441, -0.094723, -0.0946021, -0.0944813,
-0.0943606, -0.09424, -0.0941196, -0.0939993, -0.0938791, -0.093759,
-0.093639, -0.0935192, -0.0933995, -0.0932799, -0.0931605,
-0.0930411, -0.0929219, -0.0928028, -0.0926838, -0.092565,
-0.0924463, -0.0923277, -0.0922092, -0.0920909, -0.0919727,
-0.0918546, -0.0917367, -0.0916188, -0.0915011, -0.0913835,
-0.0912661, -0.0911488, -0.0910316, -0.0909145, -0.0907976,
-0.0906808, -0.0905641, -0.0904475, -0.0903311, -0.0902148,
-0.0900986, -0.0899826, -0.0898667, -0.0897509, -0.0896353,
-0.0895198, -0.0894044, -0.0892891, -0.089174, -0.089059, -0.0889442,
-0.0888294, -0.0887148, -0.0886004, -0.0884861, -0.0883719,
-0.0882578, -0.0881439, -0.0880301, -0.0879164, -0.0878029,
-0.0876894, -0.0875762, -0.087463, -0.08735, -0.0872372, -0.0871244,
-0.0870118, -0.0868994, -0.086787, -0.0866748, -0.0865628,
-0.0864509, -0.0863391, -0.0862274, -0.0861159, -0.0860045,
-0.0858932, -0.0857821, -0.0856711, -0.0855603, -0.0854496,
-0.085339, -0.0852286, -0.0851183, -0.0850081, -0.0848981,
-0.0847882, -0.0846784, -0.0845688, -0.0844593, -0.08435, -0.0842408,
-0.0841317, -0.0840228, -0.083914, -0.0838053, -0.0836968,
-0.0835884, -0.0834802, -0.0833721, -0.0832641, -0.0831562,
-0.0830485, -0.082941, -0.0828336, -0.0827263, -0.0826191,
-0.0825121, -0.0824053, -0.0822985, -0.0821919, -0.0820855,
-0.0819792, -0.081873, -0.081767, -0.0816611, -0.0815553, -0.0814497,
-0.0813442, -0.0812389, -0.0811337, -0.0810286, -0.0809237,
-0.0808189, -0.0807142, -0.0806097, -0.0805054, -0.0804011,
-0.080297, -0.0801931, -0.0800893, -0.0799856, -0.0798821,
-0.0797787, -0.0796754, -0.0795723, -0.0794693, -0.0793665,
-0.0792638, -0.0791612, -0.0790588, -0.0789565, -0.0788544,
-0.0787524, -0.0786505, -0.0785488, -0.0784472, -0.0783458,
-0.0782445, -0.0781433, -0.0780423, -0.0779414, -0.0778407,
-0.0777401, -0.0776396, -0.0775393, -0.0774391, -0.077339,
-0.0772391, -0.0771394, -0.0770397, -0.0769403, -0.0768409,
-0.0767417, -0.0766426, -0.0765437, -0.0764449, -0.0763463,
-0.0762478, -0.0761494, -0.0760511, -0.0759531, -0.0758551,
-0.0757573, -0.0756596, -0.0755621, -0.0754647, -0.0753674,
-0.0752703, -0.0751733, -0.0750765, -0.0749798, -0.0748832,
-0.0747868, -0.0746905, -0.0745944, -0.0744984, -0.0744025,
-0.0743068, -0.0742112, -0.0741157, -0.0740204, -0.0739252,
-0.0738302, -0.0737353, -0.0736405, -0.0735459, -0.0734514,
-0.0733571, -0.0732629, -0.0731688, -0.0730749, -0.0729811,
-0.0728874, -0.0727939, -0.0727005, -0.0726073, -0.0725142,
-0.0724212, -0.0723284, -0.0722357, -0.0721432, -0.0720507,
-0.0719585, -0.0718663, -0.0717743, -0.0716825, -0.0715907,
-0.0714991, -0.0714077, -0.0713164, -0.0712252, -0.0711341,
-0.0710432, -0.0709525, -0.0708618, -0.0707713, -0.070681,
-0.0705907, -0.0705006, -0.0704107, -0.0703209, -0.0702312,
-0.0701416, -0.0700522, -0.069963, -0.0698738, -0.0697848, -0.069696,
-0.0696072, -0.0695186, -0.0694302, -0.0693418, -0.0692536,
-0.0691656, -0.0690777, -0.0689899, -0.0689022, -0.0688147,
-0.0687273, -0.0686401, -0.0685529, -0.068466, -0.0683791,
-0.0682924, -0.0682058, -0.0681194, -0.068033, -0.0679469,
-0.0678608, -0.0677749, -0.0676891, -0.0676035, -0.067518,
-0.0674326, -0.0673473, -0.0672622, -0.0671772, -0.0670924,
-0.0670076, -0.0669231, -0.0668386, -0.0667543, -0.0666701,
-0.066586, -0.0665021, -0.0664183, -0.0663346, -0.0662511,
-0.0661677, -0.0660844, -0.0660013, -0.0659183, -0.0658354,
-0.0657526, -0.06567, -0.0655875, -0.0655052, -0.0654229, -0.0653408,
-0.0652589, -0.065177, -0.0650953, -0.0650137, -0.0649323,
-0.0648509, -0.0647698, -0.0646887, -0.0646078, -0.0645269,
-0.0644463, -0.0643657, -0.0642853, -0.064205, -0.0641248,
-0.0640448, -0.0639649, -0.0638851, -0.0638054, -0.0637259,
-0.0636465, -0.0635672, -0.0634881, -0.0634091, -0.0633302,
-0.0632514, -0.0631728, -0.0630943, -0.0630159, -0.0629376,
-0.0628595, -0.0627815, -0.0627036, -0.0626258, -0.0625482,
-0.0624707, -0.0623933, -0.062316, -0.0622389, -0.0621619, -0.062085,
-0.0620082, -0.0619316, -0.0618551, -0.0617787, -0.0617024,
-0.0616263, -0.0615503, -0.0614744, -0.0613986, -0.0613229,
-0.0612474, -0.061172, -0.0610967, -0.0610216, -0.0609465,
-0.0608716, -0.0607968, -0.0607222, -0.0606476, -0.0605732,
-0.0604989, -0.0604247, -0.0603506, -0.0602767, -0.0602029,
-0.0601292, -0.0600556, -0.0599821, -0.0599088, -0.0598356,
-0.0597625, -0.0596895, -0.0596166, -0.0595439, -0.0594713,
-0.0593988, -0.0593264, -0.0592541, -0.059182, -0.05911, -0.0590381,
-0.0589663, -0.0588946, -0.058823, -0.0587516, -0.0586803,
-0.0586091, -0.058538, -0.058467, -0.0583962, -0.0583255, -0.0582549,
-0.0581844, -0.058114, -0.0580437, -0.0579736, -0.0579035,
-0.0578336, -0.0577638, -0.0576941, -0.0576245, -0.0575551,
-0.0574857, -0.0574165, -0.0573474, -0.0572784, -0.0572095,
-0.0571408, -0.0570721, -0.0570036, -0.0569351, -0.0568668,
-0.0567986, -0.0567305, -0.0566626, -0.0565947, -0.056527,
-0.0564593, -0.0563918, -0.0563244, -0.0562571, -0.0561899,
-0.0561228, -0.0560559, -0.055989, -0.0559223, -0.0558556,
-0.0557891, -0.0557227, -0.0556564, -0.0555902, -0.0555242,
-0.0554582, -0.0553923, -0.0553266, -0.055261, -0.0551954, -0.05513,
-0.0550647, -0.0549995, -0.0549344, -0.0548694, -0.0548046,
-0.0547398, -0.0546752, -0.0546106, -0.0545462, -0.0544818,
-0.0544176, -0.0543535, -0.0542895, -0.0542256, -0.0541618,
-0.0540981, -0.0540345, -0.053971, -0.0539077, -0.0538444,
-0.0537813, -0.0537182, -0.0536553, -0.0535924, -0.0535297,
-0.0534671, -0.0534045, -0.0533421, -0.0532798, -0.0532176,
-0.0531555, -0.0530935, -0.0530316, -0.0529698, -0.0529081,
-0.0528465, -0.052785, -0.0527237, -0.0526624, -0.0526012,
-0.0525402, -0.0524792, -0.0524183, -0.0523576, -0.0522969,
-0.0522363, -0.0521759, -0.0521155, -0.0520553, -0.0519951,
-0.0519351, -0.0518751, -0.0518153, -0.0517555, -0.0516959,
-0.0516363, -0.0515769, -0.0515175, -0.0514583, -0.0513991,
-0.0513401, -0.0512811, -0.0512223, -0.0511635, -0.0511049,
-0.0510463, -0.0509879, -0.0509295, -0.0508712, -0.0508131,
-0.050755, -0.0506971, -0.0506392, -0.0505814, -0.0505237,
-0.0504662, -0.0504087, -0.0503513, -0.050294, -0.0502368,
-0.0501797, -0.0501227, -0.0500658, -0.050009, -0.0499523,
-0.0498957, -0.0498392, -0.0497828, -0.0497264, -0.0496702,
-0.049614, -0.049558, -0.0495021, -0.0494462, -0.0493904, -0.0493348,
-0.0492792, -0.0492237, -0.0491683, -0.049113, -0.0490578,
-0.0490027, -0.0489477, -0.0488928, -0.0488379, -0.0487832,
-0.0487285, -0.048674, -0.0486195, -0.0485652, -0.0485109,
-0.0484567, -0.0484026, -0.0483486, -0.0482947, -0.0482408,
-0.0481871, -0.0481334, -0.0480799, -0.0480264, -0.0479731,
-0.0479198, -0.0478666, -0.0478135, -0.0477604, -0.0477075,
-0.0476547, -0.0476019, -0.0475493, -0.0474967, -0.0474442,
-0.0473918, -0.0473395, -0.0472873, -0.0472351, -0.0471831,
-0.0471311, -0.0470793, -0.0470275, -0.0469758, -0.0469242,
-0.0468726, -0.0468212, -0.0467699, -0.0467186, -0.0466674,
-0.0466163, -0.0465653, -0.0465144, -0.0464635, -0.0464128,
-0.0463621, -0.0463115, -0.046261, -0.0462106, -0.0461603, -0.04611,
-0.0460599, -0.0460098, -0.0459598, -0.0459099, -0.0458601,
-0.0458103, -0.0457607, -0.0457111, -0.0456616, -0.0456122,
-0.0455629, -0.0455136, -0.0454645, -0.0454154, -0.0453664,
-0.0453175, -0.0452686, -0.0452199, -0.0451712, -0.0451226,
-0.0450741, -0.0450257, -0.0449773, -0.044929, -0.0448809,
-0.0448327, -0.0447847, -0.0447368, -0.0446889, -0.0446411,
-0.0445934, -0.0445458, -0.0444982, -0.0444508, -0.0444034,
-0.0443561, -0.0443088, -0.0442617, -0.0442146, -0.0441676,
-0.0441207, -0.0440738, -0.0440271, -0.0439804, -0.0439338,
-0.0438872, -0.0438408, -0.0437944, -0.0437481, -0.0437019,
-0.0436557, -0.0436096, -0.0435637, -0.0435177, -0.0434719,
-0.0434261, -0.0433804, -0.0433348, -0.0432893, -0.0432438,
-0.0431984, -0.0431531, -0.0431079, -0.0430627, -0.0430176,
-0.0429726, -0.0429277, -0.0428828, -0.042838, -0.0427933,
-0.0427486, -0.0427041, -0.0426596, -0.0426151, -0.0425708,
-0.0425265, -0.0424823, -0.0424382, -0.0423941, -0.0423501,
-0.0423062, -0.0422624, -0.0422186, -0.0421749, -0.0421313,
-0.0420877, -0.0420442, -0.0420008, -0.0419575, -0.0419142,
-0.041871, -0.0418279, -0.0417848, -0.0417419, -0.0416989,
-0.0416561, -0.0416133, -0.0415706, -0.041528, -0.0414854,
-0.0414429, -0.0414005, -0.0413581, -0.0413159, -0.0412736,
-0.0412315, -0.0411894, -0.0411474, -0.0411055, -0.0410636,
-0.0410218, -0.04098, -0.0409384, -0.0408968, -0.0408552, -0.0408138,
-0.0407724, -0.040731, -0.0406898, -0.0406486, -0.0406074,
-0.0405664, -0.0405254, -0.0404845, -0.0404436, -0.0404028,
-0.0403621, -0.0403214, -0.0402808, -0.0402403, -0.0401998,
-0.0401594, -0.0401191, -0.0400788, -0.0400386, -0.0399984,
-0.0399584, -0.0399184, -0.0398784, -0.0398385, -0.0397987,
-0.039759, -0.0397193, -0.0396796, -0.0396401, -0.0396006,
-0.0395612, -0.0395218, -0.0394825, -0.0394432, -0.0394041,
-0.0393649, -0.0393259, -0.0392869, -0.039248, -0.0392091,
-0.0391703, -0.0391316, -0.0390929, -0.0390543, -0.0390157,
-0.0389772, -0.0389388, -0.0389004, -0.0388621, -0.0388239,
-0.0387857, -0.0387476, -0.0387095, -0.0386715, -0.0386335,
-0.0385957, -0.0385578, -0.0385201, -0.0384824, -0.0384447,
-0.0384072, -0.0383696, -0.0383322, -0.0382948, -0.0382574,
-0.0382202, -0.0381829, -0.0381458, -0.0381087, -0.0380716,
-0.0380346, -0.0379977, -0.0379608, -0.037924, -0.0378873,
-0.0378506, -0.037814, -0.0377774, -0.0377409, -0.0377044, -0.037668,
-0.0376316, -0.0375954, -0.0375591, -0.0375229, -0.0374868,
-0.0374508, -0.0374148, -0.0373788, -0.0373429, -0.0373071,
-0.0372713, -0.0372356, -0.0371999, -0.0371643, -0.0371288,
-0.0370933, -0.0370578, -0.0370224, -0.0369871, -0.0369518,
-0.0369166, -0.0368815, -0.0368463, -0.0368113, -0.0367763,
-0.0367413, -0.0367065, -0.0366716, -0.0366368, -0.0366021,
-0.0365674, -0.0365328, -0.0364983, -0.0364637, -0.0364293,
-0.0363949, -0.0363605, -0.0363262, -0.036292, -0.0362578,
-0.0362237, -0.0361896, -0.0361556, -0.0361216, -0.0360877,
-0.0360538, -0.03602, -0.0359862, -0.0359525, -0.0359188, -0.0358852,
-0.0358516, -0.0358181, -0.0357847, -0.0357513, -0.0357179,
-0.0356846, -0.0356514, -0.0356182, -0.035585, -0.0355519,
-0.0355189, -0.0354859, -0.035453, -0.0354201, -0.0353872,
-0.0353544, -0.0353217, -0.035289, -0.0352564, -0.0352238,
-0.0351912, -0.0351587, -0.0351263, -0.0350939, -0.0350616,
-0.0350293, -0.034997, -0.0349648, -0.0349327, -0.0349006,
-0.0348685, -0.0348365, -0.0348046, -0.0347727, -0.0347408,
-0.034709, -0.0346773, -0.0346456, -0.0346139, -0.0345823,
-0.0345507, -0.0345192, -0.0344877, -0.0344563, -0.034425,
-0.0343936, -0.0343623, -0.0343311, -0.0342999, -0.0342688,
-0.0342377, -0.0342067, -0.0341757, -0.0341447, -0.0341138,
-0.034083, -0.0340522, -0.0340214, -0.0339907, -0.03396, -0.0339294,
-0.0338988, -0.0338683, -0.0338378, -0.0338073, -0.033777,
-0.0337466, -0.0337163, -0.033686, -0.0336558, -0.0336257,
-0.0335955, -0.0335655, -0.0335354, -0.0335054, -0.0334755,
-0.0334456, -0.0334157, -0.0333859, -0.0333562, -0.0333264,
-0.0332968, -0.0332671, -0.0332375, -0.033208, -0.0331785, -0.033149,
-0.0331196, -0.0330902, -0.0330609, -0.0330316, -0.0330024,
-0.0329732, -0.032944, -0.0329149, -0.0328859, -0.0328568,
-0.0328279, -0.0327989, -0.03277, -0.0327412, -0.0327123, -0.0326836,
-0.0326549, -0.0326262, -0.0325975, -0.0325689, -0.0325404,
-0.0325118, -0.0324834, -0.0324549, -0.0324265, -0.0323982,
-0.0323699, -0.0323416, -0.0323134, -0.0322852, -0.0322571,
-0.032229, -0.0322009, -0.0321729, -0.0321449, -0.0321169, -0.032089,
-0.0320612, -0.0320334, -0.0320056, -0.0319779, -0.0319502,
-0.0319225, -0.0318949, -0.0318673, -0.0318398, -0.0318123,
-0.0317848, -0.0317574, -0.03173, -0.0317027, -0.0316754, -0.0316481,
-0.0316209, -0.0315937, -0.0315666, -0.0315395, -0.0315124,
-0.0314854, -0.0314584, -0.0314314, -0.0314045, -0.0313776,
-0.0313508, -0.031324, -0.0312973, -0.0312705, -0.0312439,
-0.0312172, -0.0311906, -0.0311641, -0.0311375, -0.031111,
-0.0310846, -0.0310582, -0.0310318, -0.0310055, -0.0309792,
-0.0309529, -0.0309267, -0.0309005, -0.0308743, -0.0308482,
-0.0308221, -0.0307961, -0.0307701, -0.0307441, -0.0307182,
-0.0306923, -0.0306664, -0.0306406, -0.0306148, -0.0305891,
-0.0305634, -0.0305377, -0.030512, -0.0304864, -0.0304609,
-0.0304353, -0.0304098, -0.0303844, -0.030359, -0.0303336,
-0.0303082, -0.0302829, -0.0302576, -0.0302324, -0.0302071,
-0.030182, -0.0301568, -0.0301317, -0.0301067, -0.0300816,
-0.0300566, -0.0300316, -0.0300067, -0.0299818, -0.029957,
-0.0299321, -0.0299073, -0.0298826, -0.0298578, -0.0298332,
-0.0298085, -0.0297839, -0.0297593, -0.0297347, -0.0297102,
-0.0296857, -0.0296613, -0.0296369, -0.0296125, -0.0295881,
-0.0295638, -0.0295395, -0.0295153, -0.029491, -0.0294669,
-0.0294427, -0.0294186, -0.0293945, -0.0293705, -0.0293464,
-0.0293225, -0.0292985, -0.0292746, -0.0292507, -0.0292268,
-0.029203, -0.0291792, -0.0291555, -0.0291317, -0.029108, -0.0290844,
-0.0290608, -0.0290372, -0.0290136, -0.0289901, -0.0289666,
-0.0289431, -0.0289197, -0.0288963, -0.0288729, -0.0288495,
-0.0288262, -0.028803, -0.0287797, -0.0287565, -0.0287333,
-0.0287102, -0.028687, -0.0286639, -0.0286409, -0.0286179,
-0.0285949, -0.0285719, -0.028549, -0.0285261, -0.0285032,
-0.0284803, -0.0284575, -0.0284347, -0.028412, -0.0283893,
-0.0283666, -0.0283439, -0.0283213, -0.0282987, -0.0282761,
-0.0282536, -0.0282311, -0.0282086, -0.0281862, -0.0281637,
-0.0281413, -0.028119, -0.0280967, -0.0280744, -0.0280521,
-0.0280298, -0.0280076, -0.0279855, -0.0279633, -0.0279412,
-0.0279191, -0.027897, -0.027875, -0.027853, -0.027831, -0.027809,
-0.0277871, -0.0277652, -0.0277434, -0.0277215, -0.0276997,
-0.027678, -0.0276562, -0.0276345, -0.0276128, -0.0275911,
-0.0275695, -0.0275479, -0.0275263, -0.0275048, -0.0274833,
-0.0274618, -0.0274403, -0.0274189, -0.0273975, -0.0273761,
-0.0273547, -0.0273334, -0.0273121, -0.0272908, -0.0272696,
-0.0272484, -0.0272272, -0.027206, -0.0271849, -0.0271638,
-0.0271427, -0.0271217, -0.0271007, -0.0270797, -0.0270587,
-0.0270378, -0.0270168, -0.026996, -0.0269751, -0.0269543,
-0.0269335, -0.0269127, -0.0268919, -0.0268712, -0.0268505,
-0.0268298, -0.0268092, -0.0267886, -0.026768, -0.0267474,
-0.0267269, -0.0267064, -0.0266859, -0.0266654, -0.026645,
-0.0266246, -0.0266042, -0.0265838, -0.0265635, -0.0265432,
-0.0265229, -0.0265027, -0.0264824, -0.0264622, -0.0264421,
-0.0264219, -0.0264018, -0.0263817, -0.0263616, -0.0263416,
-0.0263215, -0.0263015, -0.0262816, -0.0262616, -0.0262417,
-0.0262218, -0.0262019, -0.0261821, -0.0261623, -0.0261425,
-0.0261227, -0.026103, -0.0260832, -0.0260635, -0.0260439,
-0.0260242, -0.0260046, -0.025985, -0.0259654, -0.0259459,
-0.0259263, -0.0259068, -0.0258874, -0.0258679, -0.0258485,
-0.0258291, -0.0258097, -0.0257904, -0.025771, -0.0257517,
-0.0257324, -0.0257132, -0.0256939, -0.0256747, -0.0256555,
-0.0256364, -0.0256172, -0.0255981, -0.025579, -0.02556, -0.0255409,
-0.0255219, -0.0255029, -0.0254839, -0.025465, -0.0254461,
-0.0254272, -0.0254083, -0.0253894, -0.0253706, -0.0253518,
-0.025333, -0.0253142, -0.0252955, -0.0252768, -0.0252581,
-0.0252394, -0.0252208, -0.0252021, -0.0251835, -0.0251649,
-0.0251464, -0.0251278, -0.0251093, -0.0250908, -0.0250724,
-0.0250539, -0.0250355, -0.0250171, -0.0249987, -0.0249804,
-0.024962, -0.0249437, -0.0249254, -0.0249072, -0.0248889,
-0.0248707, -0.0248525, -0.0248343, -0.0248162, -0.024798,
-0.0247799, -0.0247618, -0.0247438, -0.0247257, -0.0247077,
-0.0246897, -0.0246717, -0.0246538, -0.0246358, -0.0246179, -0.0246,
-0.0245821, -0.0245643, -0.0245465, -0.0245287, -0.0245109,
-0.0244931, -0.0244754, -0.0244576, -0.0244399, -0.0244223,
-0.0244046, -0.024387, -0.0243693, -0.0243517, -0.0243342,
-0.0243166, -0.0242991, -0.0242816
};

__const float dispersive_correction_KK[2701] = 
{
0.150747, 0.150958, 0.151171, 0.151384, 0.151599, 0.151815, 0.152031,
0.152249, 0.152468, 0.152688, 0.152909, 0.153131, 0.153354, 0.153578,
0.153803, 0.15403, 0.154257, 0.154486, 0.154716, 0.154947, 0.155179,
0.155412, 0.155646, 0.155882, 0.156119, 0.156357, 0.156596, 0.156837,
0.157078, 0.157321, 0.157565, 0.157811, 0.158057, 0.158305, 0.158555,
0.158805, 0.159057, 0.15931, 0.159565, 0.159821, 0.160078, 0.160336,
0.160596, 0.160857, 0.16112, 0.161384, 0.16165, 0.161917, 0.162185,
0.162455, 0.162726, 0.162999, 0.163273, 0.163549, 0.163826, 0.164105,
0.164385, 0.164667, 0.16495, 0.165235, 0.165522, 0.16581, 0.1661,
0.166391, 0.166684, 0.166979, 0.167276, 0.167574, 0.167874, 0.168175,
0.168478, 0.168783, 0.16909, 0.169399, 0.169709, 0.170021, 0.170335,
0.170651, 0.170969, 0.171289, 0.17161, 0.171934, 0.172259, 0.172586,
0.172916, 0.173247, 0.17358, 0.173916, 0.174253, 0.174592, 0.174934,
0.175278, 0.175624, 0.175972, 0.176322, 0.176674, 0.177029, 0.177385,
0.177745, 0.178106, 0.17847, 0.178836, 0.179204, 0.179575, 0.179948,
0.180324, 0.180702, 0.181082, 0.181465, 0.181851, 0.182239, 0.18263,
0.183023, 0.183419, 0.183818, 0.184219, 0.184624, 0.185031, 0.18544,
0.185853, 0.186268, 0.186687, 0.187108, 0.187532, 0.18796, 0.18839,
0.188823, 0.18926, 0.189699, 0.190142, 0.190588, 0.191037, 0.19149,
0.191946, 0.192405, 0.192868, 0.193334, 0.193803, 0.194277, 0.194753,
0.195234, 0.195718, 0.196206, 0.196697, 0.197193, 0.197692, 0.198195,
0.198703, 0.199214, 0.199729, 0.200249, 0.200772, 0.2013, 0.201833,
0.202369, 0.20291, 0.203456, 0.204006, 0.204561, 0.20512, 0.205685,
0.206254, 0.206828, 0.207407, 0.207991, 0.20858, 0.209174, 0.209774,
0.210379, 0.210989, 0.211605, 0.212226, 0.212854, 0.213487, 0.214125,
0.21477, 0.215421, 0.216078, 0.216742, 0.217412, 0.218088, 0.218771,
0.21946, 0.220157, 0.22086, 0.22157, 0.222288, 0.223013, 0.223745,
0.224485, 0.225233, 0.225989, 0.226752, 0.227524, 0.228304, 0.229093,
0.22989, 0.230696, 0.231511, 0.232335, 0.233169, 0.234012, 0.234864,
0.235727, 0.2366, 0.237483, 0.238377, 0.239282, 0.240198, 0.241125,
0.242064, 0.243014, 0.243977, 0.244952, 0.245939, 0.24694, 0.247954,
0.248981, 0.250023, 0.251078, 0.252149, 0.253234, 0.254335, 0.255452,
0.256585, 0.257735, 0.258902, 0.260087, 0.26129, 0.262511, 0.263752,
0.265013, 0.266294, 0.267596, 0.26892, 0.270266, 0.271636, 0.273029,
0.274448, 0.275891, 0.277362, 0.27886, 0.280386, 0.281942, 0.283528,
0.285146, 0.286797, 0.288483, 0.290205, 0.291964, 0.293762, 0.2956,
0.297482, 0.299408, 0.30138, 0.303402, 0.305476, 0.307604, 0.309789,
0.312035, 0.314345, 0.316722, 0.319172, 0.321699, 0.324308, 0.327004,
0.329794, 0.332685, 0.335686, 0.338805, 0.342053, 0.345442, 0.348986,
0.352701, 0.356606, 0.360724, 0.365083, 0.369717, 0.374669, 0.379993,
0.385761, 0.39207, 0.399058, 0.406933, 0.416031, 0.426971, 0.441169,
0.464204, 0.48829, 0.485582, 0.482883, 0.480192, 0.477511, 0.474839,
0.472176, 0.469522, 0.466877, 0.464241, 0.461613, 0.458995, 0.456386,
0.453785, 0.451193, 0.44861, 0.446035, 0.44347, 0.440913, 0.438365,
0.435825, 0.433294, 0.430772, 0.428259, 0.425754, 0.423257, 0.420769,
0.41829, 0.415819, 0.413357, 0.410903, 0.408457, 0.40602, 0.403592,
0.401171, 0.398759, 0.396356, 0.39396, 0.391573, 0.389194, 0.386824,
0.384461, 0.382107, 0.379761, 0.377423, 0.375094, 0.372772, 0.370459,
0.368153, 0.365856, 0.363566, 0.361285, 0.359012, 0.356746, 0.354489,
0.352239, 0.349998, 0.347764, 0.345538, 0.34332, 0.341109, 0.338907,
0.336712, 0.334525, 0.332346, 0.330175, 0.328011, 0.325855, 0.323706,
0.321565, 0.319432, 0.317307, 0.315189, 0.313078, 0.310975, 0.30888,
0.306792, 0.304711, 0.302638, 0.300573, 0.298514, 0.296464, 0.29442,
0.292384, 0.290356, 0.288334, 0.28632, 0.284313, 0.282314, 0.280321,
0.278336, 0.276358, 0.274388, 0.272424, 0.270468, 0.268518, 0.266576,
0.264641, 0.262713, 0.260792, 0.258878, 0.256971, 0.255072, 0.253179,
0.251293, 0.249414, 0.247541, 0.245676, 0.243818, 0.241966, 0.240122,
0.238284, 0.236453, 0.234629, 0.232811, 0.231001, 0.229197, 0.2274,
0.225609, 0.223825, 0.222048, 0.220277, 0.218514, 0.216756, 0.215006,
0.213261, 0.211524, 0.209793, 0.208068, 0.20635, 0.204639, 0.202934,
0.201235, 0.199543, 0.197857, 0.196178, 0.194505, 0.192838, 0.191178,
0.189524, 0.187877, 0.186235, 0.1846, 0.182972, 0.181349, 0.179733,
0.178123, 0.176519, 0.174921, 0.173329, 0.171744, 0.170165, 0.168592,
0.167024, 0.165463, 0.163908, 0.16236, 0.160817, 0.15928, 0.157749,
0.156224, 0.154705, 0.153192, 0.151685, 0.150184, 0.148688, 0.147199,
0.145715, 0.144238, 0.142766, 0.1413, 0.139839, 0.138385, 0.136936,
0.135493, 0.134056, 0.132624, 0.131199, 0.129778, 0.128364, 0.126955,
0.125552, 0.124154, 0.122762, 0.121376, 0.119995, 0.11862, 0.11725,
0.115886, 0.114527, 0.113174, 0.111826, 0.110484, 0.109147, 0.107816,
0.10649, 0.10517, 0.103854, 0.102545, 0.10124, 0.0999411, 0.0986474,
0.0973589, 0.0960758, 0.0947979, 0.0935254, 0.092258, 0.0909959,
0.089739, 0.0884874, 0.0872409, 0.0859996, 0.0847634, 0.0835324,
0.0823066, 0.0810858, 0.0798702, 0.0786596, 0.0774541, 0.0762537,
0.0750583, 0.073868, 0.0726827, 0.0715023, 0.070327, 0.0691566,
0.0679912, 0.0668308, 0.0656752, 0.0645246, 0.0633789, 0.062238,
0.0611021, 0.059971, 0.0588447, 0.0577233, 0.0566066, 0.0554948,
0.0543878, 0.0532856, 0.0521881, 0.0510953, 0.0500073, 0.048924,
0.0478454, 0.0467715, 0.0457023, 0.0446377, 0.0435778, 0.0425225,
0.0414718, 0.0404258, 0.0393843, 0.0383474, 0.0373151, 0.0362874,
0.0352642, 0.0342455, 0.0332313, 0.0322216, 0.0312164, 0.0302157,
0.0292194, 0.0282276, 0.0272402, 0.0262573, 0.0252787, 0.0243046,
0.0233348, 0.0223694, 0.0214083, 0.0204516, 0.0194992, 0.0185511,
0.0176073, 0.0166678, 0.0157326, 0.0148017, 0.013875, 0.0129525,
0.0120343, 0.0111202, 0.0102104, 0.00930476, 0.00840329, 0.00750598,
0.00661281, 0.00572378, 0.00483887, 0.00395808, 0.00308138,
0.00220876, 0.00134022, 0.00047573, -0.000384707, -0.00124111,
-0.00209349, -0.00294186, -0.00378624, -0.00462663, -0.00546304,
-0.0062955, -0.00712401, -0.00794858, -0.00876922, -0.00958596,
-0.0103988, -0.0112077, -0.0120128, -0.012814, -0.0136114,
-0.0144049, -0.0151946, -0.0159805, -0.0167626, -0.0175408,
-0.0183153, -0.0190861, -0.0198531, -0.0206163, -0.0213758,
-0.0221316, -0.0228837, -0.0236321, -0.0243767, -0.0251178,
-0.0258551, -0.0265888, -0.0273189, -0.0280454, -0.0287682,
-0.0294874, -0.030203, -0.0309151, -0.0316236, -0.0323285,
-0.0330299, -0.0337277, -0.034422, -0.0351128, -0.0358001,
-0.0364839, -0.0371643, -0.0378411, -0.0385145, -0.0391845,
-0.039851, -0.0405141, -0.0411738, -0.0418301, -0.042483, -0.0431325,
-0.0437787, -0.0444215, -0.0450609, -0.045697, -0.0463298,
-0.0469593, -0.0475855, -0.0482084, -0.048828, -0.0494443,
-0.0500574, -0.0506672, -0.0512738, -0.0518771, -0.0524773,
-0.0530742, -0.053668, -0.0542585, -0.0548459, -0.0554301,
-0.0560112, -0.0565891, -0.0571639, -0.0577355, -0.0583041,
-0.0588695, -0.0594319, -0.0599912, -0.0605474, -0.0611005,
-0.0616506, -0.0621977, -0.0627417, -0.0632827, -0.0638208,
-0.0643558, -0.0648878, -0.0654168, -0.0659429, -0.066466,
-0.0669862, -0.0675034, -0.0680177, -0.0685291, -0.0690375,
-0.0695431, -0.0700458, -0.0705456, -0.0710425, -0.0715366,
-0.0720278, -0.0725162, -0.0730018, -0.0734845, -0.0739645,
-0.0744416, -0.0749159, -0.0753875, -0.0758563, -0.0763223,
-0.0767856, -0.0772461, -0.0777039, -0.078159, -0.0786113, -0.079061,
-0.079508, -0.0799522, -0.0803938, -0.0808328, -0.081269, -0.0817027,
-0.0821336, -0.082562, -0.0829877, -0.0834109, -0.0838314,
-0.0842493, -0.0846646, -0.0850774, -0.0854876, -0.0858953,
-0.0863004, -0.0867029, -0.087103, -0.0875005, -0.0878955, -0.088288,
-0.088678, -0.0890655, -0.0894506, -0.0898332, -0.0902133, -0.090591,
-0.0909662, -0.091339, -0.0917094, -0.0920774, -0.092443, -0.0928061,
-0.0931669, -0.0935253, -0.0938814, -0.094235, -0.0945864,
-0.0949353, -0.095282, -0.0956263, -0.0959683, -0.096308, -0.0966454,
-0.0969805, -0.0973133, -0.0976438, -0.0979721, -0.0982981,
-0.0986219, -0.0989434, -0.0992627, -0.0995797, -0.0998946,
-0.100207, -0.100518, -0.100826, -0.101132, -0.101436, -0.101738,
-0.102037, -0.102334, -0.10263, -0.102923, -0.103214, -0.103503,
-0.103789, -0.104074, -0.104357, -0.104637, -0.104916, -0.105192,
-0.105466, -0.105738, -0.106008, -0.106277, -0.106543, -0.106807,
-0.107069, -0.107329, -0.107587, -0.107843, -0.108097, -0.108349,
-0.108599, -0.108847, -0.109093, -0.109338, -0.10958, -0.10982,
-0.110059, -0.110295, -0.11053, -0.110763, -0.110993, -0.111222,
-0.111449, -0.111674, -0.111898, -0.112119, -0.112339, -0.112557,
-0.112772, -0.112987, -0.113199, -0.113409, -0.113618, -0.113825,
-0.11403, -0.114233, -0.114435, -0.114634, -0.114832, -0.115028,
-0.115223, -0.115416, -0.115607, -0.115796, -0.115983, -0.116169,
-0.116353, -0.116536, -0.116716, -0.116895, -0.117073, -0.117248,
-0.117422, -0.117595, -0.117765, -0.117934, -0.118102, -0.118267,
-0.118432, -0.118594, -0.118755, -0.118914, -0.119072, -0.119228,
-0.119383, -0.119536, -0.119687, -0.119837, -0.119985, -0.120132,
-0.120277, -0.12042, -0.120562, -0.120703, -0.120842, -0.12098,
-0.121116, -0.12125, -0.121383, -0.121515, -0.121645, -0.121773,
-0.1219, -0.122026, -0.12215, -0.122273, -0.122394, -0.122514,
-0.122632, -0.122749, -0.122865, -0.122979, -0.123092, -0.123203,
-0.123313, -0.123421, -0.123529, -0.123634, -0.123739, -0.123842,
-0.123944, -0.124044, -0.124143, -0.12424, -0.124337, -0.124432,
-0.124525, -0.124618, -0.124709, -0.124799, -0.124887, -0.124974,
-0.12506, -0.125145, -0.125228, -0.12531, -0.125391, -0.12547,
-0.125548, -0.125625, -0.125701, -0.125775, -0.125849, -0.125921,
-0.125992, -0.126061, -0.12613, -0.126197, -0.126263, -0.126328,
-0.126391, -0.126454, -0.126515, -0.126575, -0.126634, -0.126692,
-0.126748, -0.126804, -0.126858, -0.126911, -0.126963, -0.127014,
-0.127064, -0.127113, -0.12716, -0.127207, -0.127252, -0.127296,
-0.127339, -0.127382, -0.127423, -0.127462, -0.127501, -0.127539,
-0.127576, -0.127611, -0.127646, -0.12768, -0.127712, -0.127744,
-0.127774, -0.127804, -0.127832, -0.127859, -0.127886, -0.127911,
-0.127936, -0.127959, -0.127981, -0.128003, -0.128023, -0.128043,
-0.128061, -0.128079, -0.128095, -0.128111, -0.128125, -0.128139,
-0.128152, -0.128164, -0.128175, -0.128185, -0.128194, -0.128202,
-0.128209, -0.128215, -0.128221, -0.128225, -0.128229, -0.128231,
-0.128233, -0.128234, -0.128234, -0.128233, -0.128232, -0.128229,
-0.128226, -0.128221, -0.128216, -0.12821, -0.128203, -0.128196,
-0.128187, -0.128178, -0.128168, -0.128157, -0.128145, -0.128132,
-0.128119, -0.128105, -0.12809, -0.128074, -0.128057, -0.12804,
-0.128022, -0.128003, -0.127983, -0.127963, -0.127941, -0.127919,
-0.127897, -0.127873, -0.127849, -0.127824, -0.127798, -0.127771,
-0.127744, -0.127716, -0.127688, -0.127658, -0.127628, -0.127597,
-0.127566, -0.127533, -0.1275, -0.127467, -0.127432, -0.127397,
-0.127362, -0.127325, -0.127288, -0.12725, -0.127212, -0.127173,
-0.127133, -0.127093, -0.127052, -0.12701, -0.126968, -0.126925,
-0.126881, -0.126837, -0.126792, -0.126746, -0.1267, -0.126653,
-0.126606, -0.126558, -0.126509, -0.12646, -0.12641, -0.12636,
-0.126308, -0.126257, -0.126205, -0.126152, -0.126098, -0.126044,
-0.12599, -0.125935, -0.125879, -0.125823, -0.125766, -0.125709,
-0.125651, -0.125592, -0.125533, -0.125474, -0.125413, -0.125353,
-0.125292, -0.12523, -0.125168, -0.125105, -0.125042, -0.124978,
-0.124913, -0.124849, -0.124783, -0.124717, -0.124651, -0.124584,
-0.124517, -0.124449, -0.124381, -0.124312, -0.124243, -0.124173,
-0.124102, -0.124032, -0.123961, -0.123889, -0.123817, -0.123744,
-0.123671, -0.123598, -0.123524, -0.123449, -0.123374, -0.123299,
-0.123223, -0.123147, -0.123071, -0.122994, -0.122916, -0.122838,
-0.12276, -0.122681, -0.122602, -0.122522, -0.122443, -0.122362,
-0.122281, -0.1222, -0.122119, -0.122037, -0.121954, -0.121871,
-0.121788, -0.121705, -0.121621, -0.121537, -0.121452, -0.121367,
-0.121281, -0.121196, -0.121109, -0.121023, -0.120936, -0.120849,
-0.120761, -0.120673, -0.120585, -0.120496, -0.120407, -0.120318,
-0.120228, -0.120138, -0.120048, -0.119957, -0.119866, -0.119775,
-0.119683, -0.119591, -0.119499, -0.119407, -0.119314, -0.11922,
-0.119127, -0.119033, -0.118939, -0.118844, -0.11875, -0.118655,
-0.118559, -0.118464, -0.118368, -0.118272, -0.118175, -0.118078,
-0.117981, -0.117884, -0.117786, -0.117688, -0.11759, -0.117492,
-0.117393, -0.117294, -0.117195, -0.117095, -0.116996, -0.116896,
-0.116795, -0.116695, -0.116594, -0.116493, -0.116392, -0.116291,
-0.116189, -0.116087, -0.115985, -0.115882, -0.11578, -0.115677,
-0.115574, -0.11547, -0.115367, -0.115263, -0.115159, -0.115055,
-0.11495, -0.114846, -0.114741, -0.114636, -0.114531, -0.114425,
-0.11432, -0.114214, -0.114108, -0.114001, -0.113895, -0.113788,
-0.113682, -0.113575, -0.113467, -0.11336, -0.113252, -0.113145,
-0.113037, -0.112929, -0.11282, -0.112712, -0.112603, -0.112495,
-0.112386, -0.112277, -0.112167, -0.112058, -0.111948, -0.111839,
-0.111729, -0.111619, -0.111508, -0.111398, -0.111287, -0.111177,
-0.111066, -0.110955, -0.110844, -0.110733, -0.110621, -0.11051,
-0.110398, -0.110287, -0.110175, -0.110063, -0.10995, -0.109838,
-0.109726, -0.109613, -0.109501, -0.109388, -0.109275, -0.109162,
-0.109049, -0.108936, -0.108822, -0.108709, -0.108595, -0.108482,
-0.108368, -0.108254, -0.10814, -0.108026, -0.107912, -0.107798,
-0.107683, -0.107569, -0.107454, -0.10734, -0.107225, -0.10711,
-0.106995, -0.10688, -0.106765, -0.10665, -0.106535, -0.106419,
-0.106304, -0.106189, -0.106073, -0.105957, -0.105842, -0.105726,
-0.10561, -0.105494, -0.105378, -0.105262, -0.105146, -0.10503,
-0.104914, -0.104798, -0.104681, -0.104565, -0.104449, -0.104332,
-0.104215, -0.104099, -0.103982, -0.103866, -0.103749, -0.103632,
-0.103515, -0.103398, -0.103281, -0.103164, -0.103047, -0.10293,
-0.102813, -0.102696, -0.102579, -0.102462, -0.102345, -0.102228,
-0.10211, -0.101993, -0.101876, -0.101758, -0.101641, -0.101524,
-0.101406, -0.101289, -0.101171, -0.101054, -0.100936, -0.100819,
-0.100701, -0.100584, -0.100466, -0.100349, -0.100231, -0.100113,
-0.0999957, -0.0998781, -0.0997605, -0.0996429, -0.0995252,
-0.0994076, -0.09929, -0.0991723, -0.0990547, -0.0989371, -0.0988194,
-0.0987018, -0.0985842, -0.0984665, -0.0983489, -0.0982313,
-0.0981137, -0.0979961, -0.0978785, -0.0977609, -0.0976434,
-0.0975258, -0.0974083, -0.0972908, -0.0971733, -0.0970558,
-0.0969383, -0.0968208, -0.0967034, -0.096586, -0.0964686,
-0.0963512, -0.0962338, -0.0961165, -0.0959992, -0.0958819,
-0.0957647, -0.0956475, -0.0955303, -0.0954131, -0.095296,
-0.0951789, -0.0950618, -0.0949447, -0.0948277, -0.0947108,
-0.0945938, -0.0944769, -0.0943601, -0.0942432, -0.0941264,
-0.0940097, -0.093893, -0.0937763, -0.0936597, -0.0935431,
-0.0934266, -0.0933101, -0.0931936, -0.0930772, -0.0929608,
-0.0928445, -0.0927283, -0.092612, -0.0924959, -0.0923798,
-0.0922637, -0.0921477, -0.0920317, -0.0919158, -0.0917999,
-0.0916841, -0.0915684, -0.0914527, -0.0913371, -0.0912215,
-0.091106, -0.0909905, -0.0908751, -0.0907598, -0.0906445,
-0.0905293, -0.0904141, -0.090299, -0.090184, -0.0900691, -0.0899542,
-0.0898393, -0.0897246, -0.0896099, -0.0894952, -0.0893807,
-0.0892662, -0.0891517, -0.0890374, -0.0889231, -0.0888089,
-0.0886947, -0.0885807, -0.0884667, -0.0883527, -0.0882389,
-0.0881251, -0.0880114, -0.0878978, -0.0877842, -0.0876708,
-0.0875574, -0.0874441, -0.0873308, -0.0872177, -0.0871046,
-0.0869916, -0.0868787, -0.0867658, -0.0866531, -0.0865404,
-0.0864278, -0.0863153, -0.0862029, -0.0860906, -0.0859783,
-0.0858662, -0.0857541, -0.0856421, -0.0855302, -0.0854184,
-0.0853066, -0.085195, -0.0850834, -0.084972, -0.0848606, -0.0847493,
-0.0846381, -0.084527, -0.084416, -0.0843051, -0.0841943, -0.0840835,
-0.0839729, -0.0838624, -0.0837519, -0.0836416, -0.0835313,
-0.0834212, -0.0833111, -0.0832011, -0.0830912, -0.0829815,
-0.0828718, -0.0827622, -0.0826527, -0.0825434, -0.0824341,
-0.0823249, -0.0822158, -0.0821068, -0.081998, -0.0818892,
-0.0817805, -0.0816719, -0.0815635, -0.0814551, -0.0813468,
-0.0812387, -0.0811306, -0.0810226, -0.0809148, -0.0808071,
-0.0806994, -0.0805919, -0.0804845, -0.0803771, -0.0802699,
-0.0801628, -0.0800558, -0.0799489, -0.0798421, -0.0797355,
-0.0796289, -0.0795224, -0.0794161, -0.0793099, -0.0792037,
-0.0790977, -0.0789918, -0.078886, -0.0787803, -0.0786747,
-0.0785693, -0.0784639, -0.0783587, -0.0782535, -0.0781485,
-0.0780436, -0.0779388, -0.0778342, -0.0777296, -0.0776252,
-0.0775208, -0.0774166, -0.0773125, -0.0772085, -0.0771046,
-0.0770009, -0.0768972, -0.0767937, -0.0766903, -0.076587,
-0.0764838, -0.0763808, -0.0762778, -0.076175, -0.0760723,
-0.0759697, -0.0758673, -0.0757649, -0.0756627, -0.0755605,
-0.0754586, -0.0753567, -0.0752549, -0.0751533, -0.0750518,
-0.0749504, -0.0748491, -0.0747479, -0.0746469, -0.074546,
-0.0744452, -0.0743445, -0.0742439, -0.0741435, -0.0740432,
-0.073943, -0.0738429, -0.073743, -0.0736432, -0.0735435, -0.0734439,
-0.0733444, -0.0732451, -0.0731459, -0.0730468, -0.0729478,
-0.072849, -0.0727503, -0.0726517, -0.0725532, -0.0724549,
-0.0723566, -0.0722585, -0.0721606, -0.0720627, -0.071965,
-0.0718674, -0.0717699, -0.0716726, -0.0715753, -0.0714782,
-0.0713813, -0.0712844, -0.0711877, -0.0710911, -0.0709946,
-0.0708983, -0.0708021, -0.070706, -0.07061, -0.0705142, -0.0704184,
-0.0703229, -0.0702274, -0.0701321, -0.0700369, -0.0699418,
-0.0698468, -0.069752, -0.0696573, -0.0695627, -0.0694683, -0.069374,
-0.0692798, -0.0691857, -0.0690918, -0.068998, -0.0689043,
-0.0688107, -0.0687173, -0.068624, -0.0685308, -0.0684378,
-0.0683449, -0.0682521, -0.0681594, -0.0680669, -0.0679745,
-0.0678822, -0.0677901, -0.0676981, -0.0676062, -0.0675144,
-0.0674228, -0.0673313, -0.0672399, -0.0671486, -0.0670575,
-0.0669665, -0.0668757, -0.0667849, -0.0666943, -0.0666039,
-0.0665135, -0.0664233, -0.0663332, -0.0662433, -0.0661534,
-0.0660637, -0.0659742, -0.0658847, -0.0657954, -0.0657062,
-0.0656172, -0.0655282, -0.0654394, -0.0653508, -0.0652622,
-0.0651738, -0.0650855, -0.0649974, -0.0649093, -0.0648214,
-0.0647337, -0.064646, -0.0645585, -0.0644711, -0.0643839,
-0.0642968, -0.0642098, -0.0641229, -0.0640362, -0.0639496,
-0.0638631, -0.0637767, -0.0636905, -0.0636044, -0.0635184,
-0.0634326, -0.0633469, -0.0632613, -0.0631759, -0.0630906,
-0.0630054, -0.0629203, -0.0628354, -0.0627506, -0.0626659,
-0.0625813, -0.0624969, -0.0624126, -0.0623284, -0.0622444,
-0.0621605, -0.0620767, -0.0619931, -0.0619095, -0.0618261,
-0.0617429, -0.0616597, -0.0615767, -0.0614938, -0.0614111,
-0.0613284, -0.0612459, -0.0611635, -0.0610813, -0.0609992,
-0.0609172, -0.0608353, -0.0607536, -0.060672, -0.0605905,
-0.0605091, -0.0604279, -0.0603468, -0.0602658, -0.060185,
-0.0601042, -0.0600236, -0.0599432, -0.0598628, -0.0597826,
-0.0597025, -0.0596225, -0.0595427, -0.059463, -0.0593834,
-0.0593039, -0.0592246, -0.0591454, -0.0590663, -0.0589874,
-0.0589085, -0.0588298, -0.0587512, -0.0586728, -0.0585945,
-0.0585163, -0.0584382, -0.0583602, -0.0582824, -0.0582047,
-0.0581271, -0.0580497, -0.0579723, -0.0578951, -0.057818,
-0.0577411, -0.0576642, -0.0575875, -0.057511, -0.0574345,
-0.0573582, -0.0572819, -0.0572058, -0.0571299, -0.057054,
-0.0569783, -0.0569027, -0.0568272, -0.0567519, -0.0566767,
-0.0566016, -0.0565266, -0.0564517, -0.056377, -0.0563024,
-0.0562279, -0.0561535, -0.0560793, -0.0560051, -0.0559311,
-0.0558572, -0.0557835, -0.0557098, -0.0556363, -0.0555629,
-0.0554897, -0.0554165, -0.0553435, -0.0552705, -0.0551978,
-0.0551251, -0.0550525, -0.0549801, -0.0549078, -0.0548356,
-0.0547635, -0.0546916, -0.0546197, -0.054548, -0.0544764, -0.054405,
-0.0543336, -0.0542624, -0.0541913, -0.0541203, -0.0540494,
-0.0539786, -0.053908, -0.0538375, -0.0537671, -0.0536968,
-0.0536266, -0.0535566, -0.0534866, -0.0534168, -0.0533471,
-0.0532775, -0.0532081, -0.0531387, -0.0530695, -0.0530004,
-0.0529314, -0.0528625, -0.0527938, -0.0527251, -0.0526566,
-0.0525882, -0.0525199, -0.0524517, -0.0523836, -0.0523157,
-0.0522478, -0.0521801, -0.0521125, -0.052045, -0.0519776,
-0.0519104, -0.0518432, -0.0517762, -0.0517093, -0.0516425,
-0.0515758, -0.0515092, -0.0514428, -0.0513764, -0.0513102,
-0.0512441, -0.051178, -0.0511122, -0.0510464, -0.0509807,
-0.0509151, -0.0508497, -0.0507844, -0.0507191, -0.050654, -0.050589,
-0.0505242, -0.0504594, -0.0503947, -0.0503302, -0.0502657,
-0.0502014, -0.0501372, -0.0500731, -0.0500091, -0.0499452,
-0.0498814, -0.0498177, -0.0497542, -0.0496907, -0.0496274,
-0.0495642, -0.0495011, -0.0494381, -0.0493752, -0.0493124,
-0.0492497, -0.0491871, -0.0491246, -0.0490623, -0.049, -0.0489379,
-0.0488759, -0.0488139, -0.0487521, -0.0486904, -0.0486288,
-0.0485673, -0.0485059, -0.0484446, -0.0483835, -0.0483224,
-0.0482614, -0.0482006, -0.0481398, -0.0480792, -0.0480186,
-0.0479582, -0.0478979, -0.0478377, -0.0477775, -0.0477175,
-0.0476576, -0.0475978, -0.0475381, -0.0474785, -0.047419,
-0.0473596, -0.0473004, -0.0472412, -0.0471821, -0.0471231,
-0.0470643, -0.0470055, -0.0469468, -0.0468883, -0.0468298,
-0.0467715, -0.0467132, -0.0466551, -0.046597, -0.0465391,
-0.0464812, -0.0464235, -0.0463658, -0.0463083, -0.0462509,
-0.0461935, -0.0461363, -0.0460791, -0.0460221, -0.0459652,
-0.0459083, -0.0458516, -0.0457949, -0.0457384, -0.045682,
-0.0456256, -0.0455694, -0.0455132, -0.0454572, -0.0454013,
-0.0453454, -0.0452897, -0.045234, -0.0451785, -0.045123, -0.0450677,
-0.0450124, -0.0449572, -0.0449022, -0.0448472, -0.0447923,
-0.0447376, -0.0446829, -0.0446283, -0.0445738, -0.0445194,
-0.0444652, -0.044411, -0.0443569, -0.0443029, -0.044249, -0.0441951,
-0.0441414, -0.0440878, -0.0440343, -0.0439808, -0.0439275,
-0.0438742, -0.0438211, -0.043768, -0.0437151, -0.0436622,
-0.0436094, -0.0435567, -0.0435042, -0.0434517, -0.0433993,
-0.0433469, -0.0432947, -0.0432426, -0.0431906, -0.0431386,
-0.0430868, -0.043035, -0.0429833, -0.0429318, -0.0428803,
-0.0428289, -0.0427776, -0.0427264, -0.0426752, -0.0426242,
-0.0425733, -0.0425224, -0.0424717, -0.042421, -0.0423704,
-0.0423199, -0.0422695, -0.0422192, -0.042169, -0.0421188,
-0.0420688, -0.0420188, -0.041969, -0.0419192, -0.0418695,
-0.0418199, -0.0417704, -0.0417209, -0.0416716, -0.0416223,
-0.0415732, -0.0415241, -0.0414751, -0.0414262, -0.0413773,
-0.0413286, -0.04128, -0.0412314, -0.0411829, -0.0411345, -0.0410862,
-0.041038, -0.0409899, -0.0409418, -0.0408938, -0.040846, -0.0407982,
-0.0407505, -0.0407028, -0.0406553, -0.0406078, -0.0405605,
-0.0405132, -0.040466, -0.0404188, -0.0403718, -0.0403248, -0.040278,
-0.0402312, -0.0401845, -0.0401378, -0.0400913, -0.0400448,
-0.0399984, -0.0399521, -0.0399059, -0.0398598, -0.0398137,
-0.0397678, -0.0397219, -0.0396761, -0.0396303, -0.0395847,
-0.0395391, -0.0394936, -0.0394482, -0.0394029, -0.0393576,
-0.0393125, -0.0392674, -0.0392224, -0.0391775, -0.0391326,
-0.0390878, -0.0390431, -0.0389985, -0.038954, -0.0389095,
-0.0388652, -0.0388209, -0.0387766, -0.0387325, -0.0386884,
-0.0386444, -0.0386005, -0.0385567, -0.0385129, -0.0384692,
-0.0384256, -0.0383821, -0.0383387, -0.0382953, -0.038252,
-0.0382088, -0.0381656, -0.0381226, -0.0380796, -0.0380366,
-0.0379938, -0.037951, -0.0379083, -0.0378657, -0.0378232,
-0.0377807, -0.0377383, -0.037696, -0.0376537, -0.0376116,
-0.0375695, -0.0375274, -0.0374855, -0.0374436, -0.0374018,
-0.0373601, -0.0373184, -0.0372768, -0.0372353, -0.0371939,
-0.0371525, -0.0371112, -0.03707, -0.0370289, -0.0369878, -0.0369468,
-0.0369058, -0.036865, -0.0368242, -0.0367834, -0.0367428,
-0.0367022, -0.0366617, -0.0366213, -0.0365809, -0.0365406,
-0.0365004, -0.0364602, -0.0364201, -0.0363801, -0.0363402,
-0.0363003, -0.0362605, -0.0362207, -0.0361811, -0.0361415,
-0.0361019, -0.0360625, -0.0360231, -0.0359837, -0.0359445,
-0.0359053, -0.0358662, -0.0358271, -0.0357881, -0.0357492,
-0.0357104, -0.0356716, -0.0356329, -0.0355942, -0.0355556,
-0.0355171, -0.0354786, -0.0354403, -0.0354019, -0.0353637,
-0.0353255, -0.0352874, -0.0352493, -0.0352114, -0.0351734,
-0.0351356, -0.0350978, -0.0350601, -0.0350224, -0.0349848,
-0.0349473, -0.0349098, -0.0348724, -0.0348351, -0.0347978,
-0.0347606, -0.0347234, -0.0346863, -0.0346493, -0.0346124,
-0.0345755, -0.0345387, -0.0345019, -0.0344652, -0.0344286,
-0.034392, -0.0343555, -0.034319, -0.0342826, -0.0342463, -0.03421,
-0.0341738, -0.0341377, -0.0341016, -0.0340656, -0.0340297,
-0.0339938, -0.0339579, -0.0339222, -0.0338864, -0.0338508,
-0.0338152, -0.0337797, -0.0337442, -0.0337088, -0.0336735,
-0.0336382, -0.033603, -0.0335678, -0.0335327, -0.0334976,
-0.0334627, -0.0334277, -0.0333929, -0.0333581, -0.0333233,
-0.0332886, -0.033254, -0.0332194, -0.0331849, -0.0331504,
-0.0331161, -0.0330817, -0.0330474, -0.0330132, -0.032979,
-0.0329449, -0.0329109, -0.0328769, -0.032843, -0.0328091,
-0.0327753, -0.0327415, -0.0327078, -0.0326741, -0.0326406,
-0.032607, -0.0325735, -0.0325401, -0.0325068, -0.0324734,
-0.0324402, -0.032407, -0.0323738, -0.0323408, -0.0323077,
-0.0322747, -0.0322418, -0.032209, -0.0321761, -0.0321434,
-0.0321107, -0.032078, -0.0320455, -0.0320129, -0.0319804, -0.031948,
-0.0319156, -0.0318833, -0.031851, -0.0318188, -0.0317867,
-0.0317546, -0.0317225, -0.0316905, -0.0316586, -0.0316267,
-0.0315948, -0.0315631, -0.0315313, -0.0314996, -0.031468,
-0.0314364, -0.0314049, -0.0313734, -0.031342, -0.0313107,
-0.0312793, -0.0312481, -0.0312169, -0.0311857, -0.0311546,
-0.0311235, -0.0310925, -0.0310616, -0.0310307, -0.0309998,
-0.030969, -0.0309383, -0.0309076, -0.0308769, -0.0308463,
-0.0308158, -0.0307853, -0.0307548, -0.0307244, -0.0306941,
-0.0306638, -0.0306335, -0.0306033, -0.0305732, -0.0305431,
-0.030513, -0.030483, -0.0304531, -0.0304232, -0.0303933, -0.0303635,
-0.0303337, -0.030304, -0.0302744, -0.0302448, -0.0302152,
-0.0301857, -0.0301562, -0.0301268, -0.0300974, -0.0300681,
-0.0300388, -0.0300096, -0.0299804, -0.0299513, -0.0299222,
-0.0298931, -0.0298641, -0.0298352, -0.0298063, -0.0297774,
-0.0297486, -0.0297199, -0.0296912, -0.0296625, -0.0296339,
-0.0296053, -0.0295768, -0.0295483, -0.0295199, -0.0294915,
-0.0294631, -0.0294348, -0.0294066, -0.0293784, -0.0293502,
-0.0293221, -0.029294, -0.029266, -0.029238, -0.0292101, -0.0291822,
-0.0291543, -0.0291265, -0.0290988, -0.029071, -0.0290434,
-0.0290157, -0.0289882, -0.0289606, -0.0289331, -0.0289057,
-0.0288783, -0.0288509, -0.0288236, -0.0287963, -0.0287691,
-0.0287419, -0.0287147, -0.0286876, -0.0286606, -0.0286335,
-0.0286066, -0.0285796, -0.0285527, -0.0285259, -0.0284991,
-0.0284723, -0.0284456, -0.0284189, -0.0283923, -0.0283657,
-0.0283391, -0.0283126, -0.0282862, -0.0282597, -0.0282334,
-0.028207, -0.0281807, -0.0281544, -0.0281282, -0.028102, -0.0280759,
-0.0280498, -0.0280238, -0.0279977, -0.0279718, -0.0279458,
-0.0279199, -0.0278941, -0.0278683, -0.0278425, -0.0278168,
-0.0277911, -0.0277654, -0.0277398, -0.0277142, -0.0276887,
-0.0276632, -0.0276377, -0.0276123, -0.027587, -0.0275616,
-0.0275363, -0.0275111, -0.0274858, -0.0274607, -0.0274355,
-0.0274104, -0.0273854, -0.0273603, -0.0273354, -0.0273104,
-0.0272855, -0.0272606, -0.0272358, -0.027211, -0.0271862,
-0.0271615, -0.0271369, -0.0271122, -0.0270876, -0.027063,
-0.0270385, -0.027014, -0.0269896, -0.0269652, -0.0269408,
-0.0269164, -0.0268921, -0.0268679, -0.0268436, -0.0268194,
-0.0267953, -0.0267712, -0.0267471, -0.026723, -0.026699, -0.026675,
-0.0266511, -0.0266272, -0.0266033, -0.0265795, -0.0265557,
-0.026532, -0.0265083, -0.0264846, -0.0264609, -0.0264373,
-0.0264137, -0.0263902, -0.0263667, -0.0263432, -0.0263198,
-0.0262964, -0.026273, -0.0262497, -0.0262264, -0.0262031,
-0.0261799, -0.0261567, -0.0261336, -0.0261104, -0.0260874,
-0.0260643, -0.0260413, -0.0260183, -0.0259954, -0.0259724,
-0.0259496, -0.0259267, -0.0259039, -0.0258811, -0.0258584,
-0.0258357, -0.025813, -0.0257904, -0.0257678, -0.0257452,
-0.0257226, -0.0257001, -0.0256777, -0.0256552, -0.0256328,
-0.0256104, -0.0255881, -0.0255658, -0.0255435, -0.0255213,
-0.0254991, -0.0254769, -0.0254547, -0.0254326, -0.0254106,
-0.0253885, -0.0253665, -0.0253445, -0.0253226, -0.0253006,
-0.0252788, -0.0252569, -0.0252351, -0.0252133, -0.0251915,
-0.0251698, -0.0251481, -0.0251265, -0.0251048, -0.0250832,
-0.0250617, -0.0250401, -0.0250186, -0.0249971, -0.0249757,
-0.0249543, -0.0249329, -0.0249116, -0.0248902, -0.024869,
-0.0248477, -0.0248265, -0.0248053, -0.0247841, -0.024763,
-0.0247419, -0.0247208, -0.0246998, -0.0246788, -0.0246578,
-0.0246368, -0.0246159, -0.024595, -0.0245742, -0.0245533,
-0.0245325, -0.0245118, -0.024491, -0.0244703, -0.0244496, -0.024429,
-0.0244083, -0.0243878, -0.0243672, -0.0243467, -0.0243262,
-0.0243057, -0.0242852, -0.0242648, -0.0242444, -0.0242241,
-0.0242037, -0.0241834, -0.0241632, -0.0241429, -0.0241227,
-0.0241025, -0.0240824, -0.0240622, -0.0240421, -0.0240221,
-0.024002, -0.023982, -0.023962, -0.0239421, -0.0239221, -0.0239022,
-0.0238824, -0.0238625, -0.0238427, -0.0238229, -0.0238031,
-0.0237834, -0.0237637, -0.023744, -0.0237244, -0.0237047,
-0.0236851, -0.0236656, -0.023646, -0.0236265, -0.023607, -0.0235876,
-0.0235681, -0.0235487, -0.0235293, -0.02351, -0.0234907, -0.0234714,
-0.0234521, -0.0234329, -0.0234136, -0.0233945, -0.0233753,
-0.0233561, -0.023337, -0.023318, -0.0232989, -0.0232799, -0.0232609,
-0.0232419, -0.0232229, -0.023204, -0.0231851, -0.0231662,
-0.0231474, -0.0231285, -0.0231097, -0.023091, -0.0230722,
-0.0230535, -0.0230348, -0.0230162, -0.0229975, -0.0229789,
-0.0229603, -0.0229417, -0.0229232, -0.0229047, -0.0228862,
-0.0228677, -0.0228493, -0.0228309, -0.0228125, -0.0227941,
-0.0227758, -0.0227575, -0.0227392, -0.0227209, -0.0227027,
-0.0226844, -0.0226663, -0.0226481, -0.0226299, -0.0226118,
-0.0225937, -0.0225757, -0.0225576, -0.0225396, -0.0225216,
-0.0225036, -0.0224857, -0.0224678, -0.0224499, -0.022432,
-0.0224141, -0.0223963, -0.0223785, -0.0223607, -0.022343,
-0.0223253, -0.0223075, -0.0222899, -0.0222722, -0.0222546,
-0.022237, -0.0222194, -0.0222018, -0.0221843, -0.0221667,
-0.0221492, -0.0221318, -0.0221143, -0.0220969, -0.0220795,
-0.0220621, -0.0220448, -0.0220274, -0.0220101, -0.0219928,
-0.0219756, -0.0219583, -0.0219411, -0.0219239, -0.0219067,
-0.0218896, -0.0218725, -0.0218554, -0.0218383, -0.0218212,
-0.0218042, -0.0217872, -0.0217702, -0.0217532, -0.0217362,
-0.0217193, -0.0217024, -0.0216855, -0.0216687, -0.0216518,
-0.021635, -0.0216182, -0.0216015, -0.0215847, -0.021568, -0.0215513,
-0.0215346, -0.0215179, -0.0215013, -0.0214847, -0.0214681,
-0.0214515, -0.0214349, -0.0214184, -0.0214019, -0.0213854,
-0.0213689, -0.0213525, -0.0213361, -0.0213196, -0.0213033,
-0.0212869, -0.0212706, -0.0212542, -0.0212379, -0.0212217,
-0.0212054, -0.0211892, -0.021173, -0.0211568, -0.0211406
};

__const float dispersive_correction_KsKs[2701] = 
{
0.1477, 0.147903, 0.148107, 0.148311, 0.148517, 0.148723, 0.148931,
0.14914, 0.149349, 0.14956, 0.149771, 0.149984, 0.150197, 0.150412,
0.150628, 0.150844, 0.151062, 0.151281, 0.151501, 0.151722, 0.151944,
0.152167, 0.152391, 0.152617, 0.152843, 0.153071, 0.153299, 0.153529,
0.15376, 0.153993, 0.154226, 0.15446, 0.154696, 0.154933, 0.155171,
0.15541, 0.155651, 0.155893, 0.156136, 0.15638, 0.156626, 0.156872,
0.15712, 0.15737, 0.15762, 0.157872, 0.158126, 0.15838, 0.158636,
0.158894, 0.159152, 0.159412, 0.159674, 0.159936, 0.160201, 0.160466,
0.160733, 0.161002, 0.161272, 0.161543, 0.161816, 0.162091, 0.162367,
0.162644, 0.162923, 0.163204, 0.163486, 0.163769, 0.164054, 0.164341,
0.16463, 0.16492, 0.165211, 0.165505, 0.1658, 0.166097, 0.166395,
0.166695, 0.166997, 0.1673, 0.167606, 0.167913, 0.168222, 0.168532,
0.168845, 0.169159, 0.169476, 0.169794, 0.170114, 0.170436, 0.170759,
0.171085, 0.171413, 0.171743, 0.172074, 0.172408, 0.172744, 0.173082, 
0.173422, 0.173764, 0.174108, 0.174454, 0.174803, 0.175154, 0.175507,
0.175862, 0.176219, 0.176579, 0.176941, 0.177305, 0.177672, 0.178041,
0.178412, 0.178786, 0.179162, 0.179541, 0.179922, 0.180306, 0.180692,
0.181081, 0.181473, 0.181867, 0.182264, 0.182663, 0.183066, 0.183471,
0.183879, 0.184289, 0.184703, 0.185119, 0.185539, 0.185961, 0.186386,
0.186814, 0.187246, 0.18768, 0.188118, 0.188558, 0.189002, 0.18945,
0.1899, 0.190354, 0.190811, 0.191271, 0.191735, 0.192203, 0.192674,
0.193149, 0.193627, 0.194109, 0.194594, 0.195084, 0.195577, 0.196074,
0.196575, 0.19708, 0.197589, 0.198102, 0.198619, 0.19914, 0.199666,
0.200196, 0.20073, 0.201269, 0.201812, 0.20236, 0.202912, 0.203469,
0.204031, 0.204597, 0.205169, 0.205745, 0.206326, 0.206913, 0.207505,
0.208101, 0.208704, 0.209312, 0.209925, 0.210544, 0.211168, 0.211798,
0.212434, 0.213077, 0.213725, 0.214379, 0.21504, 0.215707, 0.21638,
0.21706, 0.217747, 0.21844, 0.219141, 0.219848, 0.220563, 0.221285,
0.222014, 0.222751, 0.223495, 0.224248, 0.225008, 0.225777, 0.226554,
0.227339, 0.228133, 0.228936, 0.229748, 0.230569, 0.231399, 0.232239,
0.233088, 0.233948, 0.234817, 0.235697, 0.236587, 0.237489, 0.238401,
0.239325, 0.24026, 0.241207, 0.242166, 0.243137, 0.244121, 0.245118,
0.246128, 0.247152, 0.24819, 0.249242, 0.250308, 0.25139, 0.252487,
0.2536, 0.254729, 0.255875, 0.257038, 0.258219, 0.259418, 0.260636,
0.261873, 0.263129, 0.264406, 0.265704, 0.267024, 0.268367, 0.269732,
0.271121, 0.272536, 0.273975, 0.275441, 0.276935, 0.278457, 0.280009,
0.281591, 0.283205, 0.284852, 0.286534, 0.288251, 0.290006, 0.2918,
0.293635, 0.295512, 0.297435, 0.299404, 0.301422, 0.303492, 0.305616,
0.307798, 0.310041, 0.312347, 0.314722, 0.31717, 0.319694, 0.322301,
0.324995, 0.327784, 0.330675, 0.333676, 0.336796, 0.340046, 0.343437,
0.346985, 0.350705, 0.354617, 0.358745, 0.363117, 0.367767, 0.372739,
0.37809, 0.383894, 0.390252, 0.397307, 0.405278, 0.414525, 0.425722,
0.440473, 0.466179, 0.484888, 0.482187, 0.479495, 0.476812, 0.474138,
0.471474, 0.468818, 0.466171, 0.463533, 0.460905, 0.458285, 0.455674,
0.453072, 0.450478, 0.447894, 0.445318, 0.442751, 0.440193, 0.437644,
0.435103, 0.432571, 0.430048, 0.427533, 0.425027, 0.422529, 0.42004,
0.41756, 0.415088, 0.412625, 0.41017, 0.407724, 0.405286, 0.402856,
0.400435, 0.398022, 0.395618, 0.393222, 0.390834, 0.388455, 0.386083,
0.38372, 0.381366, 0.379019, 0.376681, 0.37435, 0.372028, 0.369714,
0.367409, 0.365111, 0.362821, 0.360539, 0.358266, 0.356, 0.353742,
0.351492, 0.34925, 0.347016, 0.34479, 0.342572, 0.340362, 0.338159,
0.335964, 0.333777, 0.331598, 0.329427, 0.327263, 0.325107, 0.322959,
0.320818, 0.318685, 0.316559, 0.314441, 0.312331, 0.310228, 0.308133,
0.306045, 0.303965, 0.301893, 0.299827, 0.297769, 0.295719, 0.293676,
0.29164, 0.289612, 0.287591, 0.285578, 0.283571, 0.281572, 0.279581,
0.277596, 0.275619, 0.273649, 0.271686, 0.26973, 0.267782, 0.26584,
0.263906, 0.261979, 0.260058, 0.258145, 0.256239, 0.25434, 0.252448,
0.250563, 0.248685, 0.246814, 0.244949, 0.243092, 0.241242, 0.239398,
0.237561, 0.235731, 0.233908, 0.232092, 0.230282, 0.228479, 0.226683,
0.224894, 0.223111, 0.221335, 0.219566, 0.217803, 0.216047, 0.214298,
0.212555, 0.210819, 0.209089, 0.207366, 0.205649, 0.203939, 0.202235,
0.200538, 0.198847, 0.197163, 0.195485, 0.193814, 0.192149, 0.19049,
0.188838, 0.187192, 0.185552, 0.183918, 0.182291, 0.18067, 0.179056,
0.177447, 0.175845, 0.174249, 0.172659, 0.171075, 0.169498, 0.167926,
0.166361, 0.164802, 0.163248, 0.161701, 0.16016, 0.158625, 0.157096,
0.155573, 0.154056, 0.152545, 0.15104, 0.14954, 0.148047, 0.14656,
0.145078, 0.143602, 0.142132, 0.140668, 0.13921, 0.137757, 0.136311,
0.13487, 0.133435, 0.132005, 0.130581, 0.129163, 0.127751, 0.126344,
0.124943, 0.123548, 0.122158, 0.120774, 0.119395, 0.118022, 0.116655,
0.115293, 0.113936, 0.112585, 0.11124, 0.1099, 0.108565, 0.107236,
0.105913, 0.104595, 0.103282, 0.101974, 0.100672, 0.0993755,
0.0980841, 0.0967981, 0.0955173, 0.0942419, 0.0929717, 0.0917068,
0.0904471, 0.0891927, 0.0879435, 0.0866994, 0.0854606, 0.084227,
0.0829985, 0.0817751, 0.0805569, 0.0793437, 0.0781357, 0.0769328,
0.0757349, 0.0745421, 0.0733543, 0.0721715, 0.0709938, 0.0698211,
0.0686533, 0.0674905, 0.0663326, 0.0651797, 0.0640317, 0.0628886,
0.0617505, 0.0606171, 0.0594887, 0.0583651, 0.0572464, 0.0561324,
0.0550233, 0.053919, 0.0528194, 0.0517247, 0.0506346, 0.0495494,
0.0484688, 0.0473929, 0.0463218, 0.0452553, 0.0441935, 0.0431364,
0.0420839, 0.041036, 0.0399927, 0.0389541, 0.03792, 0.0368905,
0.0358655, 0.0348451, 0.0338293, 0.0328179, 0.0318111, 0.0308087,
0.0298109, 0.0288175, 0.0278285, 0.026844, 0.0258639, 0.0248882,
0.0239169, 0.02295, 0.0219875, 0.0210293, 0.0200755, 0.019126,
0.0181808, 0.01724, 0.0163034, 0.0153711, 0.0144431, 0.0135193,
0.0125998, 0.0116845, 0.0107734, 0.00986651, 0.00896382, 0.0080653,
0.00717094, 0.00628074, 0.00539467, 0.00451273, 0.00363491,
0.00276118, 0.00189154, 0.00102598, 0.000164475, -0.000692976,
-0.00154639, -0.00239578, -0.00324115, -0.00408253, -0.00491992,
-0.00575333, -0.00658278, -0.00740828, -0.00822984, -0.00904747,
-0.0098612, -0.010671, -0.0114769, -0.012279, -0.0130772, -0.0138715,
-0.014662, -0.0154487, -0.0162315, -0.0170106, -0.0177858,
-0.0185573, -0.019325, -0.0200889, -0.0208491, -0.0216056,
-0.0223583, -0.0231074, -0.0238527, -0.0245943, -0.0253323,
-0.0260666, -0.0267973, -0.0275243, -0.0282477, -0.0289675,
-0.0296836, -0.0303962, -0.0311052, -0.0318106, -0.0325125,
-0.0332108, -0.0339056, -0.0345969, -0.0352846, -0.0359689,
-0.0366496, -0.0373269, -0.0380007, -0.0386711, -0.039338,
-0.0400014, -0.0406615, -0.0413181, -0.0419714, -0.0426212,
-0.0432677, -0.0439108, -0.0445505, -0.0451869, -0.04582, -0.0464497,
-0.0470761, -0.0476993, -0.0483191, -0.0489357, -0.0495489,
-0.050159, -0.0507658, -0.0513693, -0.0519696, -0.0525667,
-0.0531606, -0.0537513, -0.0543388, -0.0549232, -0.0555044,
-0.0560824, -0.0566573, -0.057229, -0.0577977, -0.0583632,
-0.0589256, -0.059485, -0.0600412, -0.0605944, -0.0611446,
-0.0616916, -0.0622357, -0.0627767, -0.0633147, -0.0638497,
-0.0643817, -0.0649107, -0.0654368, -0.0659599, -0.06648, -0.0669971,
-0.0675114, -0.0680227, -0.0685311, -0.0690366, -0.0695392,
-0.0700389, -0.0705357, -0.0710297, -0.0715208, -0.0720091,
-0.0724945, -0.0729771, -0.0734569, -0.0739339, -0.074408,
-0.0748794, -0.0753481, -0.0758139, -0.076277, -0.0767373,
-0.0771949, -0.0776498, -0.078102, -0.0785514, -0.0789981,
-0.0794422, -0.0798836, -0.0803222, -0.0807583, -0.0811917,
-0.0816224, -0.0820505, -0.0824759, -0.0828988, -0.083319,
-0.0837367, -0.0841518, -0.0845642, -0.0849741, -0.0853815,
-0.0857863, -0.0861885, -0.0865883, -0.0869854, -0.0873801,
-0.0877723, -0.088162, -0.0885492, -0.0889339, -0.0893161,
-0.0896959, -0.0900732, -0.0904481, -0.0908205, -0.0911905,
-0.0915581, -0.0919233, -0.0922861, -0.0926465, -0.0930045,
-0.0933601, -0.0937134, -0.0940643, -0.0944129, -0.0947591,
-0.095103, -0.0954446, -0.0957839, -0.0961209, -0.0964555,
-0.0967879, -0.097118, -0.0974458, -0.0977714, -0.0980947,
-0.0984158, -0.0987346, -0.0990512, -0.0993656, -0.0996778,
-0.0999877, -0.100295, -0.100601, -0.100904, -0.101206, -0.101505,
-0.101802, -0.102096, -0.102389, -0.10268, -0.102968, -0.103254,
-0.103538, -0.10382, -0.1041, -0.104378, -0.104654, -0.104928,
-0.1052, -0.105469, -0.105737, -0.106002, -0.106266, -0.106527,
-0.106787, -0.107044, -0.1073, -0.107553, -0.107805, -0.108055,
-0.108302, -0.108548, -0.108791, -0.109033, -0.109273, -0.109511,
-0.109747, -0.109981, -0.110213, -0.110443, -0.110672, -0.110898,
-0.111123, -0.111346, -0.111566, -0.111786, -0.112003, -0.112218,
-0.112432, -0.112643, -0.112853, -0.113061, -0.113268, -0.113472,
-0.113675, -0.113876, -0.114075, -0.114272, -0.114468, -0.114662,
-0.114854, -0.115044, -0.115233, -0.11542, -0.115605, -0.115789,
-0.11597, -0.11615, -0.116329, -0.116506, -0.116681, -0.116854,
-0.117026, -0.117196, -0.117364, -0.117531, -0.117696, -0.11786,
-0.118022, -0.118182, -0.118341, -0.118498, -0.118654, -0.118808,
-0.11896, -0.119111, -0.11926, -0.119408, -0.119554, -0.119698,
-0.119841, -0.119983, -0.120123, -0.120261, -0.120398, -0.120533,
-0.120667, -0.1208, -0.120931, -0.12106, -0.121188, -0.121315,
-0.12144, -0.121563, -0.121685, -0.121806, -0.121925, -0.122043,
-0.12216, -0.122275, -0.122388, -0.1225, -0.122611, -0.122721,
-0.122828, -0.122935, -0.12304, -0.123144, -0.123247, -0.123348,
-0.123448, -0.123546, -0.123643, -0.123739, -0.123833, -0.123926,
-0.124018, -0.124109, -0.124198, -0.124286, -0.124372, -0.124458,
-0.124542, -0.124624, -0.124706, -0.124786, -0.124865, -0.124943,
-0.125019, -0.125094, -0.125168, -0.125241, -0.125312, -0.125383,
-0.125452, -0.12552, -0.125586, -0.125652, -0.125716, -0.125779,
-0.125841, -0.125902, -0.125961, -0.12602, -0.126077, -0.126133,
-0.126188, -0.126242, -0.126294, -0.126346, -0.126396, -0.126446,
-0.126494, -0.126541, -0.126587, -0.126632, -0.126675, -0.126718,
-0.12676, -0.1268, -0.12684, -0.126878, -0.126915, -0.126952,
-0.126987, -0.127021, -0.127054, -0.127086, -0.127117, -0.127147,
-0.127176, -0.127204, -0.127231, -0.127257, -0.127282, -0.127306,
-0.127329, -0.12735, -0.127371, -0.127391, -0.12741, -0.127428,
-0.127446, -0.127462, -0.127477, -0.127491, -0.127504, -0.127517,
-0.127528, -0.127538, -0.127548, -0.127556, -0.127564, -0.127571,
-0.127577, -0.127582, -0.127586, -0.127589, -0.127591, -0.127593,
-0.127593, -0.127593, -0.127592, -0.127589, -0.127586, -0.127583,
-0.127578, -0.127572, -0.127566, -0.127559, -0.127551, -0.127542,
-0.127532, -0.127522, -0.12751, -0.127498, -0.127485, -0.127471,
-0.127457, -0.127441, -0.127425, -0.127408, -0.127391, -0.127372,
-0.127353, -0.127333, -0.127312, -0.12729, -0.127268, -0.127245,
-0.127221, -0.127196, -0.127171, -0.127145, -0.127118, -0.12709,
-0.127062, -0.127033, -0.127003, -0.126973, -0.126942, -0.12691,
-0.126877, -0.126844, -0.12681, -0.126775, -0.12674, -0.126704,
-0.126667, -0.12663, -0.126592, -0.126553, -0.126514, -0.126474,
-0.126433, -0.126392, -0.12635, -0.126307, -0.126264, -0.12622,
-0.126175, -0.12613, -0.126084, -0.126038, -0.125991, -0.125943,
-0.125895, -0.125846, -0.125797, -0.125747, -0.125696, -0.125645,
-0.125593, -0.12554, -0.125487, -0.125434, -0.125379, -0.125325,
-0.125269, -0.125213, -0.125157, -0.1251, -0.125042, -0.124984,
-0.124925, -0.124866, -0.124806, -0.124746, -0.124685, -0.124624,
-0.124562, -0.1245, -0.124437, -0.124373, -0.124309, -0.124245,
-0.12418, -0.124114, -0.124048, -0.123982, -0.123915, -0.123847,
-0.123779, -0.123711, -0.123642, -0.123572, -0.123502, -0.123432,
-0.123361, -0.12329, -0.123218, -0.123146, -0.123073, -0.123,
-0.122926, -0.122852, -0.122777, -0.122702, -0.122627, -0.122551,
-0.122475, -0.122398, -0.122321, -0.122244, -0.122166, -0.122087,
-0.122008, -0.121929, -0.121849, -0.121769, -0.121689, -0.121608,
-0.121527, -0.121445, -0.121363, -0.121281, -0.121198, -0.121115,
-0.121031, -0.120947, -0.120863, -0.120778, -0.120693, -0.120607,
-0.120522, -0.120435, -0.120349, -0.120262, -0.120175, -0.120087,
-0.119999, -0.119911, -0.119822, -0.119733, -0.119644, -0.119554,
-0.119464, -0.119374, -0.119283, -0.119192, -0.119101, -0.119009,
-0.118917, -0.118825, -0.118732, -0.118639, -0.118546, -0.118453,
-0.118359, -0.118265, -0.11817, -0.118075, -0.11798, -0.117885,
-0.117789, -0.117694, -0.117597, -0.117501, -0.117404, -0.117307,
-0.11721, -0.117112, -0.117014, -0.116916, -0.116818, -0.116719,
-0.11662, -0.116521, -0.116422, -0.116322, -0.116222, -0.116122,
-0.116022, -0.115921, -0.11582, -0.115719, -0.115618, -0.115516,
-0.115414, -0.115312, -0.11521, -0.115107, -0.115004, -0.114901,
-0.114798, -0.114695, -0.114591, -0.114487, -0.114383, -0.114279,
-0.114174, -0.11407, -0.113965, -0.11386, -0.113754, -0.113649,
-0.113543, -0.113437, -0.113331, -0.113225, -0.113118, -0.113012,
-0.112905, -0.112798, -0.11269, -0.112583, -0.112475, -0.112368,
-0.11226, -0.112152, -0.112043, -0.111935, -0.111826, -0.111718,
-0.111609, -0.111499, -0.11139, -0.111281, -0.111171, -0.111062,
-0.110952, -0.110842, -0.110731, -0.110621, -0.110511, -0.1104,
-0.110289, -0.110178, -0.110067, -0.109956, -0.109845, -0.109734,
-0.109622, -0.10951, -0.109399, -0.109287, -0.109175, -0.109062,
-0.10895, -0.108838, -0.108725, -0.108612, -0.1085, -0.108387,
-0.108274, -0.108161, -0.108047, -0.107934, -0.107821, -0.107707,
-0.107594, -0.10748, -0.107366, -0.107252, -0.107138, -0.107024,
-0.10691, -0.106796, -0.106681, -0.106567, -0.106452, -0.106338,
-0.106223, -0.106108, -0.105993, -0.105878, -0.105763, -0.105648,
-0.105533, -0.105418, -0.105302, -0.105187, -0.105071, -0.104956,
-0.10484, -0.104725, -0.104609, -0.104493, -0.104377, -0.104261,
-0.104145, -0.104029, -0.103913, -0.103797, -0.103681, -0.103565,
-0.103449, -0.103332, -0.103216, -0.103099, -0.102983, -0.102866,
-0.10275, -0.102633, -0.102517, -0.1024, -0.102283, -0.102167,
-0.10205, -0.101933, -0.101816, -0.101699, -0.101582, -0.101466,
-0.101349, -0.101232, -0.101115, -0.100998, -0.100881, -0.100763,
-0.100646, -0.100529, -0.100412, -0.100295, -0.100178, -0.100061,
-0.0999435, -0.0998263, -0.0997091, -0.0995919, -0.0994746,
-0.0993574, -0.0992402, -0.0991229, -0.0990057, -0.0988884,
-0.0987711, -0.0986539, -0.0985366, -0.0984194, -0.0983021,
-0.0981849, -0.0980676, -0.0979504, -0.0978331, -0.0977159,
-0.0975987, -0.0974815, -0.0973643, -0.0972471, -0.0971299,
-0.0970127, -0.0968956, -0.0967784, -0.0966613, -0.0965442,
-0.0964271, -0.0963101, -0.096193, -0.096076, -0.095959, -0.095842,
-0.095725, -0.0956081, -0.0954912, -0.0953743, -0.0952574,
-0.0951406, -0.0950238, -0.094907, -0.0947903, -0.0946736,
-0.0945569, -0.0944402, -0.0943236, -0.094207, -0.0940905, -0.093974,
-0.0938575, -0.0937411, -0.0936247, -0.0935083, -0.093392,
-0.0932757, -0.0931595, -0.0930433, -0.0929272, -0.0928111,
-0.092695, -0.092579, -0.0924631, -0.0923471, -0.0922313, -0.0921155,
-0.0919997, -0.091884, -0.0917683, -0.0916527, -0.0915371,
-0.0914216, -0.0913062, -0.0911908, -0.0910754, -0.0909602,
-0.0908449, -0.0907298, -0.0906146, -0.0904996, -0.0903846,
-0.0902697, -0.0901548, -0.09004, -0.0899252, -0.0898105, -0.0896959,
-0.0895814, -0.0894669, -0.0893525, -0.0892381, -0.0891238,
-0.0890096, -0.0888954, -0.0887813, -0.0886673, -0.0885534,
-0.0884395, -0.0883257, -0.088212, -0.0880983, -0.0879847,
-0.0878712, -0.0877578, -0.0876444, -0.0875311, -0.0874179,
-0.0873048, -0.0871917, -0.0870787, -0.0869658, -0.086853,
-0.0867403, -0.0866276, -0.086515, -0.0864025, -0.0862901,
-0.0861777, -0.0860655, -0.0859533, -0.0858412, -0.0857292,
-0.0856173, -0.0855055, -0.0853937, -0.0852821, -0.0851705,
-0.085059, -0.0849476, -0.0848363, -0.0847251, -0.0846139,
-0.0845029, -0.0843919, -0.0842811, -0.0841703, -0.0840596,
-0.083949, -0.0838385, -0.0837281, -0.0836178, -0.0835076,
-0.0833975, -0.0832875, -0.0831775, -0.0830677, -0.082958,
-0.0828483, -0.0827388, -0.0826293, -0.08252, -0.0824107, -0.0823015,
-0.0821925, -0.0820835, -0.0819747, -0.0818659, -0.0817573,
-0.0816487, -0.0815402, -0.0814319, -0.0813236, -0.0812155,
-0.0811074, -0.0809995, -0.0808917, -0.0807839, -0.0806763,
-0.0805688, -0.0804613, -0.080354, -0.0802468, -0.0801397,
-0.0800327, -0.0799258, -0.079819, -0.0797123, -0.0796058,
-0.0794993, -0.0793929, -0.0792867, -0.0791805, -0.0790745,
-0.0789686, -0.0788628, -0.0787571, -0.0786515, -0.078546,
-0.0784406, -0.0783354, -0.0782302, -0.0781252, -0.0780203,
-0.0779154, -0.0778107, -0.0777062, -0.0776017, -0.0774973,
-0.0773931, -0.0772889, -0.0771849, -0.077081, -0.0769772,
-0.0768735, -0.07677, -0.0766665, -0.0765632, -0.07646, -0.0763569,
-0.0762539, -0.076151, -0.0760483, -0.0759457, -0.0758432,
-0.0757408, -0.0756385, -0.0755363, -0.0754343, -0.0753324,
-0.0752305, -0.0751289, -0.0750273, -0.0749258, -0.0748245,
-0.0747233, -0.0746222, -0.0745212, -0.0744204, -0.0743197,
-0.074219, -0.0741186, -0.0740182, -0.0739179, -0.0738178,
-0.0737178, -0.0736179, -0.0735182, -0.0734185, -0.073319,
-0.0732196, -0.0731203, -0.0730212, -0.0729222, -0.0728233,
-0.0727245, -0.0726258, -0.0725273, -0.0724289, -0.0723306,
-0.0722324, -0.0721344, -0.0720364, -0.0719386, -0.071841,
-0.0717434, -0.071646, -0.0715487, -0.0714515, -0.0713545,
-0.0712576, -0.0711608, -0.0710641, -0.0709676, -0.0708711,
-0.0707748, -0.0706787, -0.0705826, -0.0704867, -0.0703909,
-0.0702952, -0.0701997, -0.0701043, -0.070009, -0.0699138,
-0.0698188, -0.0697239, -0.0696291, -0.0695345, -0.0694399,
-0.0693455, -0.0692513, -0.0691571, -0.0690631, -0.0689692,
-0.0688754, -0.0687818, -0.0686883, -0.0685949, -0.0685016,
-0.0684085, -0.0683155, -0.0682226, -0.0681299, -0.0680373,
-0.0679448, -0.0678524, -0.0677602, -0.0676681, -0.0675761,
-0.0674842, -0.0673925, -0.0673009, -0.0672095, -0.0671181,
-0.0670269, -0.0669358, -0.0668449, -0.0667541, -0.0666634,
-0.0665728, -0.0664824, -0.066392, -0.0663019, -0.0662118,
-0.0661219, -0.0660321, -0.0659424, -0.0658529, -0.0657635,
-0.0656742, -0.065585, -0.065496, -0.0654071, -0.0653184, -0.0652297,
-0.0651412, -0.0650528, -0.0649646, -0.0648765, -0.0647885,
-0.0647006, -0.0646129, -0.0645252, -0.0644378, -0.0643504,
-0.0642632, -0.0641761, -0.0640891, -0.0640023, -0.0639156,
-0.063829, -0.0637426, -0.0636562, -0.0635701, -0.063484, -0.0633981,
-0.0633122, -0.0632266, -0.063141, -0.0630556, -0.0629703,
-0.0628851, -0.0628001, -0.0627152, -0.0626304, -0.0625458,
-0.0624612, -0.0623768, -0.0622926, -0.0622084, -0.0621244,
-0.0620405, -0.0619568, -0.0618732, -0.0617897, -0.0617063,
-0.061623, -0.0615399, -0.0614569, -0.0613741, -0.0612913,
-0.0612087, -0.0611263, -0.0610439, -0.0609617, -0.0608796,
-0.0607976, -0.0607158, -0.0606341, -0.0605525, -0.060471,
-0.0603897, -0.0603085, -0.0602274, -0.0601465, -0.0600656,
-0.0599849, -0.0599044, -0.0598239, -0.0597436, -0.0596634,
-0.0595833, -0.0595034, -0.0594236, -0.0593439, -0.0592643,
-0.0591849, -0.0591056, -0.0590264, -0.0589473, -0.0588684,
-0.0587896, -0.0587109, -0.0586324, -0.0585539, -0.0584756,
-0.0583974, -0.0583194, -0.0582415, -0.0581637, -0.058086,
-0.0580084, -0.057931, -0.0578537, -0.0577765, -0.0576994,
-0.0576225, -0.0575457, -0.057469, -0.0573925, -0.057316, -0.0572397,
-0.0571635, -0.0570874, -0.0570115, -0.0569357, -0.05686, -0.0567844,
-0.056709, -0.0566336, -0.0565584, -0.0564833, -0.0564084,
-0.0563336, -0.0562588, -0.0561842, -0.0561098, -0.0560354,
-0.0559612, -0.0558871, -0.0558131, -0.0557393, -0.0556655,
-0.0555919, -0.0555184, -0.055445, -0.0553718, -0.0552987,
-0.0552256, -0.0551528, -0.05508, -0.0550073, -0.0549348, -0.0548624,
-0.0547901, -0.054718, -0.0546459, -0.054574, -0.0545022, -0.0544305,
-0.0543589, -0.0542875, -0.0542161, -0.0541449, -0.0540738,
-0.0540029, -0.053932, -0.0538613, -0.0537907, -0.0537202,
-0.0536498, -0.0535795, -0.0535094, -0.0534393, -0.0533694,
-0.0532996, -0.05323, -0.0531604, -0.053091, -0.0530217, -0.0529525,
-0.0528834, -0.0528144, -0.0527455, -0.0526768, -0.0526082,
-0.0525397, -0.0524713, -0.052403, -0.0523349, -0.0522668,
-0.0521989, -0.0521311, -0.0520634, -0.0519958, -0.0519283,
-0.051861, -0.0517938, -0.0517266, -0.0516596, -0.0515927, -0.051526,
-0.0514593, -0.0513928, -0.0513263, -0.05126, -0.0511938, -0.0511277,
-0.0510617, -0.0509958, -0.0509301, -0.0508644, -0.0507989,
-0.0507335, -0.0506682, -0.050603, -0.0505379, -0.0504729,
-0.0504081, -0.0503433, -0.0502787, -0.0502142, -0.0501498,
-0.0500854, -0.0500213, -0.0499572, -0.0498932, -0.0498293,
-0.0497656, -0.049702, -0.0496384, -0.049575, -0.0495117, -0.0494485,
-0.0493854, -0.0493224, -0.0492596, -0.0491968, -0.0491341,
-0.0490716, -0.0490092, -0.0489468, -0.0488846, -0.0488225,
-0.0487605, -0.0486986, -0.0486368, -0.0485751, -0.0485135,
-0.0484521, -0.0483907, -0.0483295, -0.0482683, -0.0482073,
-0.0481463, -0.0480855, -0.0480248, -0.0479642, -0.0479037,
-0.0478433, -0.047783, -0.0477228, -0.0476627, -0.0476027,
-0.0475428, -0.047483, -0.0474234, -0.0473638, -0.0473043, -0.047245,
-0.0471857, -0.0471266, -0.0470675, -0.0470086, -0.0469498,
-0.046891, -0.0468324, -0.0467739, -0.0467154, -0.0466571,
-0.0465989, -0.0465408, -0.0464827, -0.0464248, -0.046367,
-0.0463093, -0.0462517, -0.0461942, -0.0461368, -0.0460795,
-0.0460223, -0.0459651, -0.0459081, -0.0458512, -0.0457944,
-0.0457377, -0.0456811, -0.0456246, -0.0455682, -0.0455119,
-0.0454557, -0.0453996, -0.0453436, -0.0452877, -0.0452318,
-0.0451761, -0.0451205, -0.045065, -0.0450096, -0.0449542, -0.044899,
-0.0448439, -0.0447889, -0.0447339, -0.0446791, -0.0446244,
-0.0445697, -0.0445152, -0.0444607, -0.0444064, -0.0443521,
-0.0442979, -0.0442439, -0.0441899, -0.044136, -0.0440822,
-0.0440286, -0.043975, -0.0439215, -0.0438681, -0.0438148,
-0.0437616, -0.0437084, -0.0436554, -0.0436025, -0.0435497,
-0.0434969, -0.0434443, -0.0433917, -0.0433392, -0.0432869,
-0.0432346, -0.0431824, -0.0431303, -0.0430783, -0.0430264,
-0.0429746, -0.0429229, -0.0428712, -0.0428197, -0.0427682,
-0.0427169, -0.0426656, -0.0426144, -0.0425634, -0.0425124,
-0.0424614, -0.0424106, -0.0423599, -0.0423093, -0.0422587,
-0.0422083, -0.0421579, -0.0421076, -0.0420574, -0.0420073,
-0.0419573, -0.0419074, -0.0418576, -0.0418078, -0.0417582,
-0.0417086, -0.0416591, -0.0416097, -0.0415604, -0.0415112,
-0.0414621, -0.041413, -0.0413641, -0.0413152, -0.0412664,
-0.0412177, -0.0411691, -0.0411206, -0.0410721, -0.0410238,
-0.0409755, -0.0409273, -0.0408792, -0.0408312, -0.0407833,
-0.0407354, -0.0406877, -0.04064, -0.0405924, -0.0405449, -0.0404975,
-0.0404502, -0.0404029, -0.0403557, -0.0403087, -0.0402617,
-0.0402147, -0.0401679, -0.0401211, -0.0400745, -0.0400279,
-0.0399814, -0.039935, -0.0398886, -0.0398424, -0.0397962,
-0.0397501, -0.0397041, -0.0396581, -0.0396123, -0.0395665,
-0.0395208, -0.0394752, -0.0394297, -0.0393842, -0.0393389,
-0.0392936, -0.0392484, -0.0392032, -0.0391582, -0.0391132,
-0.0390683, -0.0390235, -0.0389788, -0.0389341, -0.0388896,
-0.0388451, -0.0388007, -0.0387563, -0.0387121, -0.0386679,
-0.0386238, -0.0385798, -0.0385358, -0.0384919, -0.0384481,
-0.0384044, -0.0383608, -0.0383172, -0.0382737, -0.0382303,
-0.038187, -0.0381437, -0.0381006, -0.0380575, -0.0380144,
-0.0379715, -0.0379286, -0.0378858, -0.0378431, -0.0378004,
-0.0377578, -0.0377153, -0.0376729, -0.0376306, -0.0375883,
-0.0375461, -0.0375039, -0.0374619, -0.0374199, -0.037378,
-0.0373362, -0.0372944, -0.0372527, -0.0372111, -0.0371695,
-0.0371281, -0.0370867, -0.0370454, -0.0370041, -0.0369629,
-0.0369218, -0.0368808, -0.0368398, -0.0367989, -0.0367581,
-0.0367173, -0.0366767, -0.0366361, -0.0365955, -0.0365551,
-0.0365147, -0.0364743, -0.0364341, -0.0363939, -0.0363538,
-0.0363137, -0.0362738, -0.0362339, -0.036194, -0.0361543,
-0.0361146, -0.0360749, -0.0360354, -0.0359959, -0.0359565,
-0.0359171, -0.0358778, -0.0358386, -0.0357995, -0.0357604,
-0.0357214, -0.0356824, -0.0356436, -0.0356048, -0.035566,
-0.0355273, -0.0354887, -0.0354502, -0.0354117, -0.0353733,
-0.035335, -0.0352967, -0.0352585, -0.0352204, -0.0351823,
-0.0351443, -0.0351063, -0.0350685, -0.0350306, -0.0349929,
-0.0349552, -0.0349176, -0.03488, -0.0348426, -0.0348051, -0.0347678,
-0.0347305, -0.0346933, -0.0346561, -0.034619, -0.034582, -0.034545,
-0.0345081, -0.0344712, -0.0344345, -0.0343977, -0.0343611,
-0.0343245, -0.034288, -0.0342515, -0.0342151, -0.0341787,
-0.0341425, -0.0341062, -0.0340701, -0.034034, -0.033998, -0.033962,
-0.0339261, -0.0338902, -0.0338545, -0.0338187, -0.0337831,
-0.0337475, -0.0337119, -0.0336764, -0.033641, -0.0336057,
-0.0335704, -0.0335351, -0.0335, -0.0334648, -0.0334298, -0.0333948,
-0.0333598, -0.033325, -0.0332901, -0.0332554, -0.0332207, -0.033186,
-0.0331514, -0.0331169, -0.0330825, -0.033048, -0.0330137,
-0.0329794, -0.0329452, -0.032911, -0.0328769, -0.0328428,
-0.0328088, -0.0327749, -0.032741, -0.0327071, -0.0326734,
-0.0326397, -0.032606, -0.0325724, -0.0325389, -0.0325054,
-0.0324719, -0.0324386, -0.0324052, -0.032372, -0.0323388,
-0.0323056, -0.0322725, -0.0322395, -0.0322065, -0.0321736,
-0.0321407, -0.0321079, -0.0320751, -0.0320424, -0.0320097,
-0.0319771, -0.0319446, -0.0319121, -0.0318797, -0.0318473,
-0.031815, -0.0317827, -0.0317505, -0.0317183, -0.0316862,
-0.0316541, -0.0316221, -0.0315902, -0.0315583, -0.0315264,
-0.0314946, -0.0314629, -0.0314312, -0.0313996, -0.031368,
-0.0313365, -0.031305, -0.0312736, -0.0312422, -0.0312109,
-0.0311796, -0.0311484, -0.0311172, -0.0310861, -0.0310551,
-0.0310241, -0.0309931, -0.0309622, -0.0309313, -0.0309005,
-0.0308698, -0.0308391, -0.0308084, -0.0307778, -0.0307473,
-0.0307168, -0.0306863, -0.0306559, -0.0306256, -0.0305953,
-0.030565, -0.0305348, -0.0305047, -0.0304746, -0.0304445,
-0.0304145, -0.0303846, -0.0303547, -0.0303248, -0.030295,
-0.0302652, -0.0302355, -0.0302059, -0.0301762, -0.0301467,
-0.0301172, -0.0300877, -0.0300583, -0.0300289, -0.0299996,
-0.0299703, -0.0299411, -0.0299119, -0.0298828, -0.0298537,
-0.0298246, -0.0297956, -0.0297667, -0.0297378, -0.0297089,
-0.0296801, -0.0296514, -0.0296227, -0.029594, -0.0295654,
-0.0295368, -0.0295083, -0.0294798, -0.0294514, -0.029423,
-0.0293946, -0.0293664, -0.0293381, -0.0293099, -0.0292817,
-0.0292536, -0.0292256, -0.0291975, -0.0291695, -0.0291416,
-0.0291137, -0.0290859, -0.0290581, -0.0290303, -0.0290026,
-0.0289749, -0.0289473, -0.0289197, -0.0288922, -0.0288647,
-0.0288373, -0.0288099, -0.0287825, -0.0287552, -0.0287279,
-0.0287007, -0.0286735, -0.0286464, -0.0286193, -0.0285922,
-0.0285652, -0.0285382, -0.0285113, -0.0284844, -0.0284576,
-0.0284308, -0.028404, -0.0283773, -0.0283506, -0.028324, -0.0282974,
-0.0282709, -0.0282444, -0.0282179, -0.0281915, -0.0281651,
-0.0281388, -0.0281125, -0.0280862, -0.02806, -0.0280338, -0.0280077,
-0.0279816, -0.0279556, -0.0279295, -0.0279036, -0.0278777,
-0.0278518, -0.0278259, -0.0278001, -0.0277744, -0.0277486,
-0.0277229, -0.0276973, -0.0276717, -0.0276461, -0.0276206,
-0.0275951, -0.0275697, -0.0275443, -0.0275189, -0.0274936,
-0.0274683, -0.027443, -0.0274178, -0.0273927, -0.0273675,
-0.0273424, -0.0273174, -0.0272924, -0.0272674, -0.0272425,
-0.0272176, -0.0271927, -0.0271679, -0.0271431, -0.0271183,
-0.0270936, -0.027069, -0.0270443, -0.0270197, -0.0269952,
-0.0269707, -0.0269462, -0.0269218, -0.0268973, -0.026873,
-0.0268486, -0.0268244, -0.0268001, -0.0267759, -0.0267517,
-0.0267276, -0.0267034, -0.0266794, -0.0266553, -0.0266313,
-0.0266074, -0.0265835, -0.0265596, -0.0265357, -0.0265119,
-0.0264881, -0.0264644, -0.0264407, -0.026417, -0.0263934,
-0.0263698, -0.0263462, -0.0263227, -0.0262992, -0.0262757,
-0.0262523, -0.0262289, -0.0262056, -0.0261822, -0.026159,
-0.0261357, -0.0261125, -0.0260893, -0.0260662, -0.0260431, -0.02602,
-0.025997, -0.025974, -0.025951, -0.0259281, -0.0259052, -0.0258823,
-0.0258595, -0.0258367, -0.0258139, -0.0257912, -0.0257685,
-0.0257458, -0.0257232, -0.0257006, -0.025678, -0.0256555, -0.025633,
-0.0256106, -0.0255881, -0.0255657, -0.0255434, -0.0255211,
-0.0254988, -0.0254765, -0.0254543, -0.0254321, -0.0254099,
-0.0253878, -0.0253657, -0.0253436, -0.0253216, -0.0252996,
-0.0252776, -0.0252557, -0.0252338, -0.0252119, -0.0251901,
-0.0251683, -0.0251465, -0.0251248, -0.0251031, -0.0250814,
-0.0250597, -0.0250381, -0.0250165, -0.024995, -0.0249735, -0.024952,
-0.0249305, -0.0249091, -0.0248877, -0.0248663, -0.024845,
-0.0248237, -0.0248024, -0.0247812, -0.02476, -0.0247388, -0.0247176,
-0.0246965, -0.0246754, -0.0246544, -0.0246334, -0.0246124,
-0.0245914, -0.0245705, -0.0245496, -0.0245287, -0.0245079,
-0.024487, -0.0244663, -0.0244455, -0.0244248, -0.0244041,
-0.0243834, -0.0243628, -0.0243422, -0.0243216, -0.0243011,
-0.0242805, -0.0242601, -0.0242396, -0.0242192, -0.0241988,
-0.0241784, -0.0241581, -0.0241377, -0.0241175, -0.0240972,
-0.024077, -0.0240568, -0.0240366, -0.0240165, -0.0239964,
-0.0239763, -0.0239562, -0.0239362, -0.0239162, -0.0238962,
-0.0238763, -0.0238564, -0.0238365, -0.0238166, -0.0237968,
-0.023777, -0.0237572, -0.0237375, -0.0237178, -0.0236981,
-0.0236784, -0.0236588, -0.0236392, -0.0236196, -0.0236001,
-0.0235805, -0.023561, -0.0235416, -0.0235221, -0.0235027,
-0.0234833, -0.023464, -0.0234446, -0.0234253, -0.0234061,
-0.0233868, -0.0233676, -0.0233484, -0.0233292, -0.0233101,
-0.0232909, -0.0232719, -0.0232528, -0.0232338, -0.0232147,
-0.0231958, -0.0231768, -0.0231579, -0.023139, -0.0231201,
-0.0231012, -0.0230824, -0.0230636, -0.0230448, -0.0230261,
-0.0230073, -0.0229886, -0.02297, -0.0229513, -0.0229327, -0.0229141,
-0.0228955, -0.022877, -0.0228584, -0.0228399, -0.0228215, -0.022803,
-0.0227846, -0.0227662, -0.0227478, -0.0227295, -0.0227112,
-0.0226929, -0.0226746, -0.0226564, -0.0226382, -0.02262, -0.0226018,
-0.0225836, -0.0225655, -0.0225474, -0.0225294, -0.0225113,
-0.0224933, -0.0224753, -0.0224573, -0.0224394, -0.0224214,
-0.0224035, -0.0223857, -0.0223678, -0.02235, -0.0223322, -0.0223144,
-0.0222966, -0.0222789, -0.0222612, -0.0222435, -0.0222258,
-0.0222082, -0.0221906, -0.022173, -0.0221554, -0.0221379,
-0.0221204, -0.0221029, -0.0220854, -0.0220679, -0.0220505,
-0.0220331, -0.0220157, -0.0219984, -0.021981, -0.0219637,
-0.0219464, -0.0219292, -0.0219119, -0.0218947, -0.0218775,
-0.0218603, -0.0218432, -0.021826, -0.0218089, -0.0217918,
-0.0217748, -0.0217577, -0.0217407, -0.0217237, -0.0217068,
-0.0216898, -0.0216729, -0.021656, -0.0216391, -0.0216222,
-0.0216054, -0.0215886, -0.0215718, -0.021555, -0.0215383,
-0.0215215, -0.0215048, -0.0214882, -0.0214715, -0.0214549,
-0.0214382, -0.0214216, -0.0214051, -0.0213885, -0.021372,
-0.0213555, -0.021339, -0.0213225, -0.0213061, -0.0212896,
-0.0212732, -0.0212568, -0.0212405, -0.0212241, -0.0212078,
-0.0211915, -0.0211752, -0.021159, -0.0211428, -0.0211265,
-0.0211103, -0.0210942
};

__const float dispersive_correction_EtapPi[2701] = 
{
0.118715, 0.118832, 0.118949, 0.119066, 0.119184, 0.119303, 0.119422,
0.119541, 0.119661, 0.119781, 0.119902, 0.120023, 0.120145, 0.120267,
0.120389, 0.120512, 0.120636, 0.12076, 0.120884, 0.121009, 0.121135,
0.12126, 0.121387, 0.121514, 0.121641, 0.121769, 0.121897, 0.122026,
0.122155, 0.122285, 0.122415, 0.122546, 0.122677, 0.122809, 0.122941,
0.123074, 0.123208, 0.123341, 0.123476, 0.123611, 0.123746, 0.123882,
0.124019, 0.124156, 0.124293, 0.124432, 0.12457, 0.12471, 0.124849,
0.12499, 0.125131, 0.125272, 0.125414, 0.125557, 0.1257, 0.125844,
0.125988, 0.126133, 0.126279, 0.126425, 0.126572, 0.126719, 0.126867,
0.127015, 0.127164, 0.127314, 0.127465, 0.127616, 0.127767, 0.127919,
0.128072, 0.128226, 0.12838, 0.128535, 0.12869, 0.128846, 0.129003,
0.12916, 0.129318, 0.129477, 0.129636, 0.129796, 0.129957, 0.130119,
0.130281, 0.130443, 0.130607, 0.130771, 0.130936, 0.131102, 0.131268,
0.131435, 0.131603, 0.131771, 0.13194, 0.13211, 0.132281, 0.132452,
0.132625, 0.132798, 0.132971, 0.133146, 0.133321, 0.133497, 0.133674,
0.133851, 0.13403, 0.134209, 0.134389, 0.134569, 0.134751, 0.134933,
0.135117, 0.135301, 0.135486, 0.135671, 0.135858, 0.136045, 0.136233,
0.136423, 0.136613, 0.136803, 0.136995, 0.137188, 0.137381, 0.137576,
0.137771, 0.137967, 0.138165, 0.138363, 0.138562, 0.138762, 0.138963,
0.139164, 0.139367, 0.139571, 0.139776, 0.139982, 0.140188, 0.140396,
0.140605, 0.140814, 0.141025, 0.141237, 0.14145, 0.141664, 0.141879,
0.142095, 0.142312, 0.14253, 0.142749, 0.142969, 0.14319, 0.143413,
0.143637, 0.143861, 0.144087, 0.144314, 0.144542, 0.144772, 0.145002,
0.145234, 0.145466, 0.145701, 0.145936, 0.146172, 0.14641, 0.146649,
0.146889, 0.14713, 0.147373, 0.147617, 0.147862, 0.148109, 0.148357,
0.148606, 0.148856, 0.149108, 0.149361, 0.149616, 0.149872, 0.150129,
0.150388, 0.150648, 0.15091, 0.151173, 0.151437, 0.151703, 0.151971,
0.15224, 0.15251, 0.152782, 0.153056, 0.153331, 0.153607, 0.153885,
0.154165, 0.154446, 0.154729, 0.155014, 0.1553, 0.155588, 0.155878,
0.156169, 0.156462, 0.156757, 0.157053, 0.157352, 0.157652, 0.157953,
0.158257, 0.158563, 0.15887, 0.159179, 0.15949, 0.159803, 0.160118,
0.160435, 0.160754, 0.161075, 0.161397, 0.161722, 0.162049, 0.162378,
0.162709, 0.163042, 0.163378, 0.163715, 0.164055, 0.164397, 0.164741,
0.165087, 0.165436, 0.165786, 0.16614, 0.166495, 0.166853, 0.167214,
0.167576, 0.167942, 0.168309, 0.16868, 0.169053, 0.169428, 0.169806,
0.170187, 0.17057, 0.170956, 0.171345, 0.171736, 0.172131, 0.172528,
0.172928, 0.173331, 0.173737, 0.174146, 0.174557, 0.174972, 0.17539,
0.175812, 0.176236, 0.176663, 0.177094, 0.177528, 0.177966, 0.178407,
0.178851, 0.179298, 0.17975, 0.180205, 0.180663, 0.181125, 0.181591,
0.182061, 0.182534, 0.183011, 0.183493, 0.183978, 0.184467, 0.184961,
0.185458, 0.18596, 0.186466, 0.186977, 0.187492, 0.188011, 0.188536,
0.189064, 0.189598, 0.190136, 0.190679, 0.191227, 0.19178, 0.192338,
0.192902, 0.19347, 0.194044, 0.194624, 0.195209, 0.1958, 0.196396,
0.196999, 0.197607, 0.198221, 0.198842, 0.199469, 0.200102, 0.200742,
0.201388, 0.202042, 0.202702, 0.203369, 0.204043, 0.204725, 0.205414,
0.206111, 0.206816, 0.207528, 0.208249, 0.208978, 0.209715, 0.210462,
0.211217, 0.211981, 0.212754, 0.213536, 0.214329, 0.215131, 0.215944,
0.216766, 0.2176, 0.218444, 0.2193, 0.220167, 0.221045, 0.221936,
0.222839, 0.223755, 0.224684, 0.225627, 0.226583, 0.227553, 0.228538,
0.229538, 0.230554, 0.231585, 0.232634, 0.233699, 0.234781, 0.235882,
0.237002, 0.238141, 0.2393, 0.24048, 0.241681, 0.242905, 0.244152,
0.245423, 0.24672, 0.248042, 0.249392, 0.25077, 0.252177, 0.253616,
0.255087, 0.256592, 0.258133, 0.259712, 0.261329, 0.262989, 0.264692,
0.266442, 0.268241, 0.270093, 0.272, 0.273967, 0.275998, 0.278097,
0.28027, 0.282523, 0.284862, 0.287296, 0.289833, 0.292484, 0.295263,
0.298182, 0.301261, 0.304522, 0.307992, 0.311706, 0.31571, 0.320068,
0.324867, 0.330241, 0.336405, 0.343754, 0.353191, 0.368281, 0.383965,
0.382808, 0.381649, 0.380486, 0.379321, 0.378153, 0.376982, 0.375808,
0.374632, 0.373453, 0.372272, 0.371088, 0.369902, 0.368714, 0.367523,
0.366329, 0.365134, 0.363936, 0.362736, 0.361534, 0.360329, 0.359123,
0.357915, 0.356704, 0.355492, 0.354278, 0.353062, 0.351844, 0.350624,
0.349403, 0.34818, 0.346955, 0.345729, 0.344501, 0.343271, 0.34204,
0.340807, 0.339574, 0.338338, 0.337101, 0.335863, 0.334624, 0.333383,
0.332142, 0.330899, 0.329655, 0.328409, 0.327163, 0.325916, 0.324667,
0.323418, 0.322168, 0.320917, 0.319665, 0.318412, 0.317158, 0.315904,
0.314648, 0.313393, 0.312136, 0.310879, 0.309621, 0.308363, 0.307104,
0.305844, 0.304585, 0.303324, 0.302064, 0.300802, 0.299541, 0.298279,
0.297017, 0.295755, 0.294492, 0.293229, 0.291966, 0.290703, 0.28944,
0.288176, 0.286913, 0.285649, 0.284386, 0.283122, 0.281859, 0.280596,
0.279333, 0.278069, 0.276806, 0.275544, 0.274281, 0.273019, 0.271757,
0.270495, 0.269233, 0.267972, 0.266711, 0.265451, 0.264191, 0.262931,
0.261672, 0.260414, 0.259156, 0.257898, 0.256641, 0.255385, 0.254129,
0.252874, 0.251619, 0.250365, 0.249112, 0.247859, 0.246608, 0.245357,
0.244107, 0.242857, 0.241609, 0.240361, 0.239114, 0.237868, 0.236623,
0.235379, 0.234136, 0.232894, 0.231652, 0.230412, 0.229173, 0.227935,
0.226698, 0.225462, 0.224227, 0.222994, 0.221761, 0.22053, 0.219299,
0.218071, 0.216843, 0.215616, 0.214391, 0.213167, 0.211944, 0.210723,
0.209503, 0.208284, 0.207067, 0.205851, 0.204637, 0.203424, 0.202212,
0.201002, 0.199793, 0.198586, 0.19738, 0.196176, 0.194973, 0.193772,
0.192572, 0.191374, 0.190178, 0.188983, 0.18779, 0.186598, 0.185408,
0.18422, 0.183033, 0.181848, 0.180665, 0.179484, 0.178304, 0.177126,
0.17595, 0.174776, 0.173603, 0.172432, 0.171263, 0.170096, 0.168931,
0.167767, 0.166605, 0.165446, 0.164288, 0.163132, 0.161978, 0.160826,
0.159676, 0.158528, 0.157381, 0.156237, 0.155095, 0.153955, 0.152816,
0.15168, 0.150546, 0.149414, 0.148284, 0.147156, 0.14603, 0.144906,
0.143784, 0.142664, 0.141547, 0.140431, 0.139318, 0.138207, 0.137098,
0.135991, 0.134886, 0.133784, 0.132684, 0.131585, 0.13049, 0.129396,
0.128304, 0.127215, 0.126128, 0.125044, 0.123961, 0.122881, 0.121803,
0.120727, 0.119654, 0.118583, 0.117514, 0.116448, 0.115384, 0.114322,
0.113263, 0.112205, 0.111151, 0.110098, 0.109048, 0.108001, 0.106955,
0.105913, 0.104872, 0.103834, 0.102798, 0.101765, 0.100734,
0.0997058, 0.0986798, 0.0976562, 0.0966351, 0.0956164, 0.0946002,
0.0935864, 0.0925751, 0.0915662, 0.0905599, 0.089556, 0.0885546,
0.0875556, 0.0865592, 0.0855653, 0.0845739, 0.0835849, 0.0825985,
0.0816146, 0.0806333, 0.0796544, 0.0786781, 0.0777043, 0.0767331,
0.0757644, 0.0747982, 0.0738346, 0.0728736, 0.0719151, 0.0709592,
0.0700058, 0.069055, 0.0681068, 0.0671611, 0.066218, 0.0652776,
0.0643396, 0.0634043, 0.0624716, 0.0615415, 0.0606139, 0.059689,
0.0587666, 0.0578469, 0.0569298, 0.0560152, 0.0551033, 0.054194,
0.0532874, 0.0523833, 0.0514819, 0.050583, 0.0496868, 0.0487933,
0.0479023, 0.047014, 0.0461284, 0.0452453, 0.0443649, 0.0434871,
0.042612, 0.0417395, 0.0408697, 0.0400025, 0.0391379, 0.038276,
0.0374167, 0.0365601, 0.0357061, 0.0348548, 0.0340061, 0.03316,
0.0323167, 0.0314759, 0.0306379, 0.0298024, 0.0289697, 0.0281396,
0.0273121, 0.0264873, 0.0256651, 0.0248456, 0.0240288, 0.0232146,
0.0224031, 0.0215942, 0.020788, 0.0199845, 0.0191836, 0.0183853,
0.0175897, 0.0167968, 0.0160065, 0.0152189, 0.0144339, 0.0136516,
0.0128719, 0.0120949, 0.0113205, 0.0105488, 0.00977976, 0.00901334,
0.00824958, 0.00748846, 0.00673, 0.00597417, 0.00522099, 0.00447046,
0.00372257, 0.00297732, 0.00223471, 0.00149473, 0.000757401,
0.0000227043, -0.000709357, -0.00143879, -0.00216558, -0.00288975,
-0.00361128, -0.00433019, -0.00504647, -0.00576013, -0.00647116,
-0.00717958, -0.00788537, -0.00858855, -0.00928911, -0.00998706,
-0.0106824, -0.0113751, -0.0120652, -0.0127528, -0.0134377, -0.01412,
-0.0147997, -0.0154768, -0.0161513, -0.0168232, -0.0174926,
-0.0181593, -0.0188235, -0.0194851, -0.0201441, -0.0208005,
-0.0214543, -0.0221056, -0.0227543, -0.0234005, -0.024044, -0.024685,
-0.0253235, -0.0259594, -0.0265927, -0.0272235, -0.0278518,
-0.0284775, -0.0291006, -0.0297212, -0.0303393, -0.0309548,
-0.0315679, -0.0321783, -0.0327863, -0.0333917, -0.0339947,
-0.0345951, -0.035193, -0.0357884, -0.0363812, -0.0369716,
-0.0375595, -0.0381449, -0.0387278, -0.0393082, -0.0398861,
-0.0404616, -0.0410345, -0.041605, -0.0421731, -0.0427386,
-0.0433017, -0.0438623, -0.0444205, -0.0449762, -0.0455295,
-0.0460803, -0.0466287, -0.0471747, -0.0477182, -0.0482593,
-0.0487979, -0.0493342, -0.049868, -0.0503994, -0.0509284, -0.051455,
-0.0519791, -0.0525009, -0.0530203, -0.0535373, -0.0540519,
-0.0545641, -0.055074, -0.0555815, -0.0560866, -0.0565893,
-0.0570897, -0.0575877, -0.0580834, -0.0585767, -0.0590677,
-0.0595563, -0.0600426, -0.0605266, -0.0610082, -0.0614875,
-0.0619645, -0.0624392, -0.0629115, -0.0633816, -0.0638493,
-0.0643148, -0.064778, -0.0652389, -0.0656975, -0.0661538,
-0.0666078, -0.0670596, -0.0675091, -0.0679563, -0.0684013,
-0.068844, -0.0692845, -0.0697228, -0.0701588, -0.0705925,
-0.0710241, -0.0714534, -0.0718805, -0.0723054, -0.0727281,
-0.0731485, -0.0735668, -0.0739829, -0.0743967, -0.0748084,
-0.0752179, -0.0756253, -0.0760304, -0.0764334, -0.0768343,
-0.0772329, -0.0776294, -0.0780238, -0.078416, -0.0788061,
-0.0791941, -0.0795799, -0.0799636, -0.0803452, -0.0807247,
-0.081102, -0.0814773, -0.0818504, -0.0822215, -0.0825905,
-0.0829574, -0.0833222, -0.0836849, -0.0840456, -0.0844042,
-0.0847607, -0.0851152, -0.0854677, -0.085818, -0.0861664,
-0.0865127, -0.086857, -0.0871993, -0.0875395, -0.0878778, -0.088214,
-0.0885482, -0.0888804, -0.0892107, -0.0895389, -0.0898652,
-0.0901895, -0.0905118, -0.0908321, -0.0911505, -0.0914669,
-0.0917814, -0.0920939, -0.0924045, -0.0927131, -0.0930198,
-0.0933246, -0.0936274, -0.0939284, -0.0942274, -0.0945245,
-0.0948198, -0.0951131, -0.0954045, -0.0956941, -0.0959818,
-0.0962675, -0.0965515, -0.0968335, -0.0971137, -0.0973921,
-0.0976686, -0.0979432, -0.0982161, -0.098487, -0.0987562,
-0.0990235, -0.099289, -0.0995527, -0.0998146, -0.100075, -0.100333,
-0.10059, -0.100844, -0.101097, -0.101348, -0.101598, -0.101845,
-0.102091, -0.102335, -0.102578, -0.102818, -0.103057, -0.103294,
-0.10353, -0.103763, -0.103995, -0.104226, -0.104454, -0.104681,
-0.104906, -0.10513, -0.105351, -0.105571, -0.10579, -0.106007,
-0.106222, -0.106435, -0.106647, -0.106857, -0.107065, -0.107272,
-0.107477, -0.107681, -0.107883, -0.108083, -0.108282, -0.108479,
-0.108674, -0.108868, -0.109061, -0.109251, -0.10944, -0.109628,
-0.109814, -0.109998, -0.110181, -0.110362, -0.110542, -0.11072,
-0.110897, -0.111072, -0.111245, -0.111418, -0.111588, -0.111757,
-0.111925, -0.112091, -0.112255, -0.112418, -0.112579, -0.112739,
-0.112898, -0.113055, -0.113211, -0.113365, -0.113517, -0.113669,
-0.113818, -0.113967, -0.114114, -0.114259, -0.114403, -0.114546,
-0.114687, -0.114826, -0.114965, -0.115102, -0.115237, -0.115371,
-0.115504, -0.115636, -0.115766, -0.115894, -0.116021, -0.116147,
-0.116272, -0.116395, -0.116517, -0.116637, -0.116756, -0.116874,
-0.116991, -0.117106, -0.11722, -0.117332, -0.117443, -0.117553,
-0.117662, -0.117769, -0.117875, -0.11798, -0.118083, -0.118185,
-0.118286, -0.118386, -0.118484, -0.118581, -0.118677, -0.118772,
-0.118865, -0.118957, -0.119048, -0.119138, -0.119227, -0.119314,
-0.1194, -0.119485, -0.119568, -0.119651, -0.119732, -0.119812,
-0.119891, -0.119968, -0.120045, -0.12012, -0.120194, -0.120267,
-0.120339, -0.12041, -0.12048, -0.120548, -0.120615, -0.120681,
-0.120746, -0.12081, -0.120873, -0.120935, -0.120995, -0.121055,
-0.121113, -0.12117, -0.121226, -0.121282, -0.121336, -0.121388,
-0.12144, -0.121491, -0.121541, -0.121589, -0.121637, -0.121684,
-0.121729, -0.121773, -0.121817, -0.121859, -0.121901, -0.121941,
-0.12198, -0.122019, -0.122056, -0.122092, -0.122127, -0.122162,
-0.122195, -0.122227, -0.122259, -0.122289, -0.122318, -0.122347,
-0.122374, -0.122401, -0.122426, -0.122451, -0.122474, -0.122497,
-0.122519, -0.12254, -0.12256, -0.122578, -0.122596, -0.122614,
-0.12263, -0.122645, -0.122659, -0.122673, -0.122685, -0.122697,
-0.122708, -0.122718, -0.122727, -0.122735, -0.122742, -0.122749,
-0.122754, -0.122759, -0.122763, -0.122766, -0.122768, -0.122769,
-0.122769, -0.122769, -0.122768, -0.122766, -0.122763, -0.122759,
-0.122754, -0.122749, -0.122743, -0.122736, -0.122728, -0.12272,
-0.12271, -0.1227, -0.122689, -0.122678, -0.122665, -0.122652,
-0.122638, -0.122623, -0.122608, -0.122591, -0.122574, -0.122556,
-0.122538, -0.122519, -0.122499, -0.122478, -0.122456, -0.122434,
-0.122411, -0.122387, -0.122363, -0.122338, -0.122312, -0.122286,
-0.122259, -0.122231, -0.122202, -0.122173, -0.122143, -0.122112,
-0.122081, -0.122049, -0.122016, -0.121983, -0.121949, -0.121914,
-0.121879, -0.121843, -0.121806, -0.121769, -0.121731, -0.121692,
-0.121653, -0.121613, -0.121573, -0.121532, -0.12149, -0.121448,
-0.121405, -0.121361, -0.121317, -0.121272, -0.121227, -0.121181,
-0.121135, -0.121087, -0.12104, -0.120991, -0.120943, -0.120893,
-0.120843, -0.120792, -0.120741, -0.120689, -0.120637, -0.120584,
-0.120531, -0.120477, -0.120422, -0.120367, -0.120312, -0.120256,
-0.120199, -0.120142, -0.120084, -0.120026, -0.119967, -0.119908,
-0.119848, -0.119787, -0.119727, -0.119665, -0.119603, -0.119541,
-0.119478, -0.119415, -0.119351, -0.119287, -0.119222, -0.119157,
-0.119091, -0.119025, -0.118958, -0.118891, -0.118823, -0.118755,
-0.118686, -0.118617, -0.118548, -0.118478, -0.118408, -0.118337,
-0.118266, -0.118194, -0.118122, -0.118049, -0.117976, -0.117903,
-0.117829, -0.117754, -0.11768, -0.117605, -0.117529, -0.117453,
-0.117377, -0.1173, -0.117223, -0.117145, -0.117067, -0.116989,
-0.11691, -0.116831, -0.116752, -0.116672, -0.116591, -0.116511,
-0.11643, -0.116348, -0.116266, -0.116184, -0.116102, -0.116019,
-0.115936, -0.115852, -0.115768, -0.115684, -0.115599, -0.115514,
-0.115429, -0.115343, -0.115257, -0.115171, -0.115084, -0.114997,
-0.11491, -0.114822, -0.114734, -0.114646, -0.114557, -0.114468,
-0.114379, -0.114289, -0.114199, -0.114109, -0.114019, -0.113928,
-0.113837, -0.113745, -0.113654, -0.113562, -0.11347, -0.113377,
-0.113284, -0.113191, -0.113098, -0.113004, -0.11291, -0.112816,
-0.112721, -0.112626, -0.112531, -0.112436, -0.112341, -0.112245,
-0.112149, -0.112052, -0.111956, -0.111859, -0.111762, -0.111665,
-0.111567, -0.111469, -0.111371, -0.111273, -0.111174, -0.111076,
-0.110977, -0.110877, -0.110778, -0.110678, -0.110578, -0.110478,
-0.110378, -0.110277, -0.110177, -0.110076, -0.109974, -0.109873,
-0.109772, -0.10967, -0.109568, -0.109466, -0.109363, -0.109261,
-0.109158, -0.109055, -0.108952, -0.108848, -0.108745, -0.108641,
-0.108537, -0.108433, -0.108329, -0.108224, -0.10812, -0.108015,
-0.10791, -0.107805, -0.1077, -0.107594, -0.107489, -0.107383,
-0.107277, -0.107171, -0.107065, -0.106958, -0.106852, -0.106745,
-0.106638, -0.106531, -0.106424, -0.106317, -0.106209, -0.106102,
-0.105994, -0.105886, -0.105778, -0.10567, -0.105562, -0.105453,
-0.105345, -0.105236, -0.105128, -0.105019, -0.10491, -0.104801,
-0.104691, -0.104582, -0.104473, -0.104363, -0.104253, -0.104144,
-0.104034, -0.103924, -0.103814, -0.103703, -0.103593, -0.103483,
-0.103372, -0.103262, -0.103151, -0.10304, -0.102929, -0.102818,
-0.102707, -0.102596, -0.102485, -0.102374, -0.102262, -0.102151,
-0.102039, -0.101928, -0.101816, -0.101704, -0.101592, -0.10148,
-0.101368, -0.101256, -0.101144, -0.101032, -0.10092, -0.100807,
-0.100695, -0.100583, -0.10047, -0.100357, -0.100245, -0.100132,
-0.100019, -0.0999066, -0.0997938, -0.0996809, -0.0995679,
-0.0994549, -0.0993419, -0.0992288, -0.0991157, -0.0990025,
-0.0988893, -0.0987761, -0.0986628, -0.0985495, -0.0984361,
-0.0983227, -0.0982093, -0.0980959, -0.0979824, -0.0978689,
-0.0977553, -0.0976417, -0.0975281, -0.0974145, -0.0973009,
-0.0971872, -0.0970735, -0.0969598, -0.0968461, -0.0967323,
-0.0966185, -0.0965048, -0.096391, -0.0962772, -0.0961633,
-0.0960495, -0.0959357, -0.0958218, -0.095708, -0.0955941,
-0.0954802, -0.0953663, -0.0952525, -0.0951386, -0.0950247,
-0.0949108, -0.094797, -0.0946831, -0.0945692, -0.0944553,
-0.0943415, -0.0942276, -0.0941138, -0.0939999, -0.0938861,
-0.0937723, -0.0936585, -0.0935447, -0.0934309, -0.0933171,
-0.0932033, -0.0930896, -0.0929759, -0.0928622, -0.0927485,
-0.0926348, -0.0925212, -0.0924076, -0.092294, -0.0921804,
-0.0920668, -0.0919533, -0.0918398, -0.0917264, -0.0916129,
-0.0914995, -0.0913861, -0.0912728, -0.0911595, -0.0910462,
-0.0909329, -0.0908197, -0.0907065, -0.0905934, -0.0904803,
-0.0903672, -0.0902542, -0.0901412, -0.0900282, -0.0899153,
-0.0898024, -0.0896896, -0.0895768, -0.0894641, -0.0893514,
-0.0892388, -0.0891262, -0.0890136, -0.0889011, -0.0887887,
-0.0886763, -0.0885639, -0.0884516, -0.0883394, -0.0882272,
-0.088115, -0.0880029, -0.0878909, -0.0877789, -0.087667, -0.0875551,
-0.0874433, -0.0873316, -0.0872199, -0.0871083, -0.0869967,
-0.0868852, -0.0867738, -0.0866624, -0.0865511, -0.0864398,
-0.0863287, -0.0862175, -0.0861065, -0.0859955, -0.0858846,
-0.0857737, -0.085663, -0.0855523, -0.0854416, -0.085331, -0.0852205,
-0.0851101, -0.0849998, -0.0848895, -0.0847793, -0.0846692,
-0.0845591, -0.0844491, -0.0843392, -0.0842294, -0.0841196, -0.08401,
-0.0839004, -0.0837909, -0.0836814, -0.0835721, -0.0834628,
-0.0833536, -0.0832445, -0.0831355, -0.0830265, -0.0829177,
-0.0828089, -0.0827002, -0.0825916, -0.0824831, -0.0823746,
-0.0822663, -0.082158, -0.0820499, -0.0819418, -0.0818338,
-0.0817259, -0.081618, -0.0815103, -0.0814027, -0.0812951,
-0.0811877, -0.0810803, -0.080973, -0.0808659, -0.0807588,
-0.0806518, -0.0805449, -0.0804381, -0.0803314, -0.0802248,
-0.0801183, -0.0800118, -0.0799055, -0.0797993, -0.0796932,
-0.0795871, -0.0794812, -0.0793754, -0.0792697, -0.079164,
-0.0790585, -0.0789531, -0.0788477, -0.0787425, -0.0786374,
-0.0785323, -0.0784274, -0.0783226, -0.0782179, -0.0781133,
-0.0780088, -0.0779044, -0.0778001, -0.0776959, -0.0775918,
-0.0774878, -0.0773839, -0.0772801, -0.0771765, -0.0770729,
-0.0769695, -0.0768661, -0.0767629, -0.0766598, -0.0765568,
-0.0764538, -0.076351, -0.0762484, -0.0761458, -0.0760433, -0.075941,
-0.0758387, -0.0757366, -0.0756345, -0.0755326, -0.0754308,
-0.0753291, -0.0752276, -0.0751261, -0.0750247, -0.0749235,
-0.0748224, -0.0747214, -0.0746205, -0.0745197, -0.074419,
-0.0743185, -0.074218, -0.0741177, -0.0740175, -0.0739174,
-0.0738175, -0.0737176, -0.0736179, -0.0735182, -0.0734187,
-0.0733193, -0.0732201, -0.0731209, -0.0730219, -0.072923,
-0.0728242, -0.0727255, -0.0726269, -0.0725285, -0.0724302,
-0.0723319, -0.0722339, -0.0721359, -0.0720381, -0.0719403,
-0.0718427, -0.0717452, -0.0716479, -0.0715506, -0.0714535,
-0.0713565, -0.0712596, -0.0711629, -0.0710662, -0.0709697,
-0.0708733, -0.0707771, -0.0706809, -0.0705849, -0.070489,
-0.0703932, -0.0702976, -0.070202, -0.0701066, -0.0700113,
-0.0699162, -0.0698211, -0.0697262, -0.0696314, -0.0695368,
-0.0694422, -0.0693478, -0.0692535, -0.0691594, -0.0690653,
-0.0689714, -0.0688776, -0.0687839, -0.0686904, -0.068597,
-0.0685037, -0.0684105, -0.0683175, -0.0682245, -0.0681318,
-0.0680391, -0.0679466, -0.0678541, -0.0677619, -0.0676697,
-0.0675777, -0.0674857, -0.067394, -0.0673023, -0.0672108,
-0.0671194, -0.0670281, -0.066937, -0.0668459, -0.0667551,
-0.0666643, -0.0665736, -0.0664831, -0.0663927, -0.0663025,
-0.0662124, -0.0661224, -0.0660325, -0.0659427, -0.0658531,
-0.0657636, -0.0656743, -0.065585, -0.0654959, -0.0654069,
-0.0653181, -0.0652294, -0.0651408, -0.0650523, -0.0649639,
-0.0648757, -0.0647876, -0.0646997, -0.0646119, -0.0645242,
-0.0644366, -0.0643491, -0.0642618, -0.0641746, -0.0640876,
-0.0640006, -0.0639138, -0.0638272, -0.0637406, -0.0636542,
-0.0635679, -0.0634817, -0.0633957, -0.0633098, -0.063224,
-0.0631384, -0.0630529, -0.0629675, -0.0628822, -0.0627971,
-0.0627121, -0.0626272, -0.0625424, -0.0624578, -0.0623733,
-0.0622889, -0.0622047, -0.0621206, -0.0620366, -0.0619528,
-0.061869, -0.0617854, -0.061702, -0.0616186, -0.0615354, -0.0614523,
-0.0613694, -0.0612865, -0.0612038, -0.0611213, -0.0610388,
-0.0609565, -0.0608743, -0.0607922, -0.0607103, -0.0606285,
-0.0605468, -0.0604653, -0.0603838, -0.0603025, -0.0602214,
-0.0601403, -0.0600594, -0.0599786, -0.059898, -0.0598174, -0.059737,
-0.0596568, -0.0595766, -0.0594966, -0.0594167, -0.0593369,
-0.0592573, -0.0591777, -0.0590984, -0.0590191, -0.0589399,
-0.0588609, -0.0587821, -0.0587033, -0.0586247, -0.0585462,
-0.0584678, -0.0583895, -0.0583114, -0.0582334, -0.0581555,
-0.0580778, -0.0580001, -0.0579226, -0.0578453, -0.057768,
-0.0576909, -0.0576139, -0.057537, -0.0574603, -0.0573836,
-0.0573071, -0.0572308, -0.0571545, -0.0570784, -0.0570024,
-0.0569265, -0.0568508, -0.0567751, -0.0566996, -0.0566243,
-0.056549, -0.0564739, -0.0563989, -0.056324, -0.0562492, -0.0561746,
-0.0561001, -0.0560257, -0.0559514, -0.0558773, -0.0558033,
-0.0557294, -0.0556556, -0.055582, -0.0555084, -0.055435, -0.0553617,
-0.0552886, -0.0552155, -0.0551426, -0.0550698, -0.0549972,
-0.0549246, -0.0548522, -0.0547799, -0.0547077, -0.0546356,
-0.0545637, -0.0544919, -0.0544202, -0.0543486, -0.0542771,
-0.0542058, -0.0541346, -0.0540635, -0.0539925, -0.0539216,
-0.0538509, -0.0537803, -0.0537098, -0.0536394, -0.0535691,
-0.053499, -0.053429, -0.0533591, -0.0532893, -0.0532196, -0.0531501,
-0.0530806, -0.0530113, -0.0529422, -0.0528731, -0.0528041,
-0.0527353, -0.0526666, -0.052598, -0.0525295, -0.0524611,
-0.0523929, -0.0523248, -0.0522567, -0.0521888, -0.0521211,
-0.0520534, -0.0519859, -0.0519184, -0.0518511, -0.0517839,
-0.0517168, -0.0516499, -0.051583, -0.0515163, -0.0514497,
-0.0513832, -0.0513168, -0.0512505, -0.0511844, -0.0511183,
-0.0510524, -0.0509866, -0.0509209, -0.0508553, -0.0507898,
-0.0507245, -0.0506592, -0.0505941, -0.0505291, -0.0504642,
-0.0503994, -0.0503347, -0.0502701, -0.0502057, -0.0501413,
-0.0500771, -0.050013, -0.049949, -0.0498851, -0.0498213, -0.0497577,
-0.0496941, -0.0496307, -0.0495673, -0.0495041, -0.049441, -0.049378,
-0.0493151, -0.0492523, -0.0491897, -0.0491271, -0.0490647,
-0.0490023, -0.0489401, -0.048878, -0.048816, -0.0487541, -0.0486923,
-0.0486306, -0.048569, -0.0485076, -0.0484462, -0.048385, -0.0483238,
-0.0482628, -0.0482019, -0.0481411, -0.0480803, -0.0480197,
-0.0479592, -0.0478989, -0.0478386, -0.0477784, -0.0477183,
-0.0476584, -0.0475985, -0.0475388, -0.0474791, -0.0474196,
-0.0473602, -0.0473009, -0.0472416, -0.0471825, -0.0471235,
-0.0470646, -0.0470058, -0.0469471, -0.0468885, -0.0468301,
-0.0467717, -0.0467134, -0.0466552, -0.0465972, -0.0465392,
-0.0464813, -0.0464236, -0.0463659, -0.0463084, -0.0462509,
-0.0461936, -0.0461363, -0.0460792, -0.0460221, -0.0459652,
-0.0459083, -0.0458516, -0.045795, -0.0457384, -0.045682, -0.0456257,
-0.0455694, -0.0455133, -0.0454573, -0.0454013, -0.0453455,
-0.0452898, -0.0452341, -0.0451786, -0.0451232, -0.0450679,
-0.0450126, -0.0449575, -0.0449024, -0.0448475, -0.0447927,
-0.0447379, -0.0446833, -0.0446287, -0.0445743, -0.0445199,
-0.0444657, -0.0444115, -0.0443575, -0.0443035, -0.0442497,
-0.0441959, -0.0441422, -0.0440886, -0.0440352, -0.0439818,
-0.0439285, -0.0438753, -0.0438222, -0.0437692, -0.0437163,
-0.0436635, -0.0436108, -0.0435582, -0.0435056, -0.0434532,
-0.0434009, -0.0433486, -0.0432965, -0.0432444, -0.0431925,
-0.0431406, -0.0430888, -0.0430371, -0.0429856, -0.0429341,
-0.0428827, -0.0428313, -0.0427801, -0.042729, -0.042678, -0.042627,
-0.0425762, -0.0425254, -0.0424747, -0.0424242, -0.0423737,
-0.0423233, -0.042273, -0.0422227, -0.0421726, -0.0421226,
-0.0420726, -0.0420228, -0.041973, -0.0419233, -0.0418738,
-0.0418243, -0.0417749, -0.0417255, -0.0416763, -0.0416272,
-0.0415781, -0.0415291, -0.0414803, -0.0414315, -0.0413828,
-0.0413342, -0.0412856, -0.0412372, -0.0411888, -0.0411406,
-0.0410924, -0.0410443, -0.0409963, -0.0409484, -0.0409005,
-0.0408528, -0.0408051, -0.0407575, -0.04071, -0.0406626, -0.0406153,
-0.0405681, -0.0405209, -0.0404739, -0.0404269, -0.04038, -0.0403332,
-0.0402864, -0.0402398, -0.0401932, -0.0401468, -0.0401004,
-0.040054, -0.0400078, -0.0399617, -0.0399156, -0.0398696,
-0.0398237, -0.0397779, -0.0397322, -0.0396865, -0.039641,
-0.0395955, -0.0395501, -0.0395047, -0.0394595, -0.0394143,
-0.0393692, -0.0393242, -0.0392793, -0.0392345, -0.0391897,
-0.039145, -0.0391004, -0.0390559, -0.0390115, -0.0389671,
-0.0389228, -0.0388786, -0.0388345, -0.0387904, -0.0387465,
-0.0387026, -0.0386588, -0.038615, -0.0385714, -0.0385278,
-0.0384843, -0.0384409, -0.0383976, -0.0383543, -0.0383111,
-0.038268, -0.038225, -0.038182, -0.0381391, -0.0380963, -0.0380536,
-0.0380109, -0.0379684, -0.0379258, -0.0378834, -0.0378411,
-0.0377988, -0.0377566, -0.0377145, -0.0376724, -0.0376305,
-0.0375886, -0.0375467, -0.037505, -0.0374633, -0.0374217,
-0.0373802, -0.0373387, -0.0372973, -0.037256, -0.0372148,
-0.0371736, -0.0371325, -0.0370915, -0.0370506, -0.0370097,
-0.0369689, -0.0369282, -0.0368875, -0.0368469, -0.0368064,
-0.036766, -0.0367256, -0.0366853, -0.0366451, -0.0366049,
-0.0365649, -0.0365248, -0.0364849, -0.036445, -0.0364052,
-0.0363655, -0.0363258, -0.0362862, -0.0362467, -0.0362073,
-0.0361679, -0.0361286, -0.0360893, -0.0360502, -0.0360111,
-0.035972, -0.0359331, -0.0358942, -0.0358553, -0.0358166,
-0.0357779, -0.0357392, -0.0357007, -0.0356622, -0.0356238,
-0.0355854, -0.0355471, -0.0355089, -0.0354707, -0.0354327,
-0.0353946, -0.0353567, -0.0353188, -0.035281, -0.0352432,
-0.0352055, -0.0351679, -0.0351303, -0.0350928, -0.0350554,
-0.0350181, -0.0349808, -0.0349435, -0.0349064, -0.0348693,
-0.0348322, -0.0347952, -0.0347583, -0.0347215, -0.0346847,
-0.034648, -0.0346113, -0.0345747, -0.0345382, -0.0345018,
-0.0344654, -0.034429, -0.0343928, -0.0343565, -0.0343204,
-0.0342843, -0.0342483, -0.0342123, -0.0341764, -0.0341406,
-0.0341048, -0.0340691, -0.0340335, -0.0339979, -0.0339624,
-0.0339269, -0.0338915, -0.0338561, -0.0338209, -0.0337856,
-0.0337505, -0.0337154, -0.0336803, -0.0336454, -0.0336104,
-0.0335756, -0.0335408, -0.033506, -0.0334714, -0.0334367,
-0.0334022, -0.0333677, -0.0333332, -0.0332989, -0.0332645,
-0.0332303, -0.0331961, -0.0331619, -0.0331278, -0.0330938,
-0.0330598, -0.0330259, -0.032992, -0.0329582, -0.0329245,
-0.0328908, -0.0328572, -0.0328236, -0.0327901, -0.0327567,
-0.0327233, -0.0326899, -0.0326566, -0.0326234, -0.0325902,
-0.0325571, -0.0325241, -0.0324911, -0.0324581, -0.0324252,
-0.0323924, -0.0323596, -0.0323269, -0.0322942, -0.0322616,
-0.032229, -0.0321965, -0.0321641, -0.0321317, -0.0320994,
-0.0320671, -0.0320348, -0.0320027, -0.0319705, -0.0319385,
-0.0319065, -0.0318745, -0.0318426, -0.0318107, -0.0317789,
-0.0317472, -0.0317155, -0.0316839, -0.0316523, -0.0316207,
-0.0315893, -0.0315578, -0.0315265, -0.0314951, -0.0314639,
-0.0314327, -0.0314015, -0.0313704, -0.0313393, -0.0313083,
-0.0312773, -0.0312464, -0.0312156, -0.0311848, -0.031154,
-0.0311233, -0.0310927, -0.0310621, -0.0310315, -0.031001,
-0.0309706, -0.0309402, -0.0309098, -0.0308796, -0.0308493,
-0.0308191, -0.030789, -0.0307589, -0.0307288, -0.0306988,
-0.0306689, -0.030639, -0.0306091, -0.0305793, -0.0305496,
-0.0305199, -0.0304902, -0.0304606, -0.0304311, -0.0304016,
-0.0303721, -0.0303427, -0.0303133, -0.030284, -0.0302548,
-0.0302256, -0.0301964, -0.0301673, -0.0301382, -0.0301092,
-0.0300802, -0.0300513, -0.0300224, -0.0299935, -0.0299647,
-0.029936, -0.0299073, -0.0298787, -0.0298501, -0.0298215, -0.029793,
-0.0297645, -0.0297361, -0.0297077, -0.0296794, -0.0296511,
-0.0296229, -0.0295947, -0.0295666, -0.0295385, -0.0295104,
-0.0294824, -0.0294545, -0.0294266, -0.0293987, -0.0293709,
-0.0293431, -0.0293153, -0.0292877, -0.02926, -0.0292324, -0.0292049,
-0.0291773, -0.0291499, -0.0291224, -0.0290951, -0.0290677,
-0.0290404, -0.0290132, -0.028986, -0.0289588, -0.0289317,
-0.0289046, -0.0288776, -0.0288506, -0.0288237, -0.0287968,
-0.0287699, -0.0287431, -0.0287163, -0.0286896, -0.0286629,
-0.0286362, -0.0286096, -0.0285831, -0.0285566, -0.0285301,
-0.0285036, -0.0284772, -0.0284509, -0.0284246, -0.0283983,
-0.0283721, -0.0283459, -0.0283197, -0.0282936, -0.0282676,
-0.0282416, -0.0282156, -0.0281896, -0.0281637, -0.0281379,
-0.0281121, -0.0280863, -0.0280606, -0.0280349, -0.0280092,
-0.0279836, -0.027958, -0.0279325, -0.027907, -0.0278815, -0.0278561,
-0.0278307, -0.0278054, -0.0277801, -0.0277548, -0.0277296,
-0.0277044, -0.0276793, -0.0276542, -0.0276291, -0.0276041,
-0.0275791, -0.0275542, -0.0275293, -0.0275044, -0.0274796,
-0.0274548, -0.02743, -0.0274053, -0.0273806, -0.027356, -0.0273314,
-0.0273068, -0.0272823, -0.0272578, -0.0272334, -0.027209,
-0.0271846, -0.0271603, -0.027136, -0.0271117, -0.0270875,
-0.0270633, -0.0270391, -0.027015, -0.0269909, -0.0269669,
-0.0269429, -0.0269189, -0.026895, -0.0268711, -0.0268473,
-0.0268234, -0.0267996, -0.0267759, -0.0267522, -0.0267285,
-0.0267049, -0.0266813, -0.0266577, -0.0266342, -0.0266107,
-0.0265872, -0.0265638, -0.0265404, -0.026517, -0.0264937,
-0.0264704, -0.0264472, -0.026424, -0.0264008, -0.0263776,
-0.0263545, -0.0263315, -0.0263084, -0.0262854, -0.0262624,
-0.0262395, -0.0262166, -0.0261937, -0.0261709, -0.0261481,
-0.0261253, -0.0261026, -0.0260799, -0.0260572, -0.0260346,
-0.026012, -0.0259895, -0.0259669, -0.0259444, -0.025922, -0.0258995,
-0.0258771, -0.0258548, -0.0258325, -0.0258102, -0.0257879,
-0.0257657, -0.0257435, -0.0257213, -0.0256992, -0.0256771,
-0.025655, -0.025633, -0.025611, -0.025589, -0.0255671, -0.0255452,
-0.0255233, -0.0255015, -0.0254797, -0.0254579, -0.0254361,
-0.0254144, -0.0253927, -0.0253711, -0.0253495, -0.0253279,
-0.0253063, -0.0252848, -0.0252633, -0.0252419, -0.0252205,
-0.0251991, -0.0251777, -0.0251564, -0.0251351, -0.0251138,
-0.0250925, -0.0250713, -0.0250502, -0.025029, -0.0250079,
-0.0249868, -0.0249657, -0.0249447, -0.0249237, -0.0249028,
-0.0248818, -0.0248609, -0.02484, -0.0248192, -0.0247984, -0.0247776,
-0.0247568, -0.0247361, -0.0247154, -0.0246948, -0.0246741,
-0.0246535, -0.0246329, -0.0246124, -0.0245919, -0.0245714,
-0.0245509, -0.0245305, -0.0245101, -0.0244897, -0.0244694,
-0.0244491, -0.0244288, -0.0244085, -0.0243883, -0.0243681,
-0.0243479, -0.0243278, -0.0243077, -0.0242876, -0.0242675,
-0.0242475, -0.0242275, -0.0242075, -0.0241876, -0.0241677,
-0.0241478, -0.0241279, -0.0241081, -0.0240883, -0.0240685,
-0.0240488, -0.0240291, -0.0240094, -0.0239897, -0.0239701,
-0.0239505, -0.0239309, -0.0239113, -0.0238918
};

int get_id(float x)
{
	int id = 1000*x - 700;
	return (x < 0.7 || x > 3.4) ? (x < 0.7 ? 0 : 2700) : id;
}

float get_ratio(float x)
{
	int id = get_id(x);
	return (x < 0.7 || x > 3.4) ? 1 : 701 + id - 1000*x;
}

float rho(float mr2, float m1_2, float m2_2){
	float mr = sqrt(mr2);
	float poly = mr2*mr2 + m1_2*m1_2 + m2_2*m2_2 - 2*m1_2*mr2 -2*m2_2*mr2 -2*m1_2*m2_2;
    float ret;
	if(poly>=0) {
        ret = 2.0f*sqrt(poly)/(2.0f*mr2);
    }
    else {
        ret = 0;
    }
	return ret;
}

/* four channels */
__kernel void kernel_a0980(__global float * mx2in, float mr, float mr2, float g1, float m1a, float m1b, float g2, float m2a, float m2b, float g3, float m3a, float m3b, float g4, float m4a, float m4b, __global out float2 * output)
{
	uint i = get_global_id(0);
	float mx2 = mx2in[i];
	g2 = g2*g1;
	g3 = g3*g1;
	g4 = g4*g1;

	// PI(s)
	int id1, id2;
	float r1, r2;
	id1 = get_id(sqrt(mx2));
	id2 = id1+1;
	r1 = get_ratio(sqrt(mx2));
	r2 = 1-r1;
	float PI_1s = dispersive_correction_EtaPi[id1]*r1 + dispersive_correction_EtaPi[id2]*r2;
	float PI_2s = dispersive_correction_KK[id1]*r1 + dispersive_correction_KK[id2]*r2;
	float PI_3s = dispersive_correction_KsKs[id1]*r1 + dispersive_correction_KsKs[id2]*r2;
	float PI_4s = dispersive_correction_EtapPi[id1]*r1 + dispersive_correction_EtapPi[id2]*r2;
	
	// PI(m*m)
	id1 = get_id(mr);
	id2 = id1+1;
	r1 = get_ratio(mr);
	r2 = 1-r1;
	float PI_1m2 = dispersive_correction_EtaPi[id1]*r1 + dispersive_correction_EtaPi[id2]*r2;
	float PI_2m2 = dispersive_correction_KK[id1]*r1 + dispersive_correction_KK[id2]*r2;
	float PI_3m2 = dispersive_correction_KsKs[id1]*r1 + dispersive_correction_KsKs[id2]*r2;
	float PI_4m2 = dispersive_correction_EtapPi[id1]*r1 + dispersive_correction_EtapPi[id2]*r2;

	float diff = mr2 - mx2 - g1*(PI_1s-PI_1m2) - g2*(PI_2s-PI_2m2) - g3*(PI_3s-PI_3m2) - g4*(PI_4s-PI_4m2);

	float ps1 = rho(mx2, m1a*m1a, m1b*m1b);
	float ps2 = rho(mx2, m2a*m2a, m2b*m2b);
	float ps3 = rho(mx2, m3a*m3a, m3b*m3b);
	float ps4 = rho(mx2, m4a*m4a, m4b*m4b);
	float ws = g1*ps1 + g2*ps2 + g3*ps3 + g4*ps4; /*mass dependent width */
	
	float denom = diff*diff + ws*ws; /* common denominator*/
	
	output[i].x = diff/denom; /* real part*/
	output[i].y = ws/denom; /* imaginary part*/
}


/*For summing the BW in partial wave*/
/*constant width BW*/
float2 breitwigner(float mx2in, float mr, float mr2, float wr)
{
	float mx2 = mx2in;

  float2 output;
	float diff = mr2-mx2;
	float denom = diff*diff + wr*wr*mr2;
	if (wr<0) {
		output.x = 1/sqrt(denom);
		output.y = 0;
    }
    else if (wr<10) {
		output.x = diff/denom;
		output.y = wr*mr/denom;
	}
	else { /* phase space */
		output.x = 1;
		output.y = 0;
	}
  return output;
}

/*sigma*/
float2 Pr_sigma(float mx2in){
	float mx2 = mx2in;
  float mr = 0.9264f;
  float mr2 = mr*mr;
  float diff = mr2-mx2;/* m*m-s */
  //float mpi=0.13957018;
  float mpi=0.13957f;
  float g1=(0.5843f+1.6663f*mx2)*(mx2-mpi*mpi/2.0f)/(mr2-mpi*mpi/2.0f)*exp(-(mx2-mr2)/1.082f);
  float g2=0.0024f;
  float w1=g1*rho2pi(mx2)/rho2pi(mr2);
  float w2=g2*rho4pi(mx2)/rho4pi(mr2);
  float ws=mr*(w1+w2);
  float denom=diff*diff+ws*ws;
  float2 output;
  output.x=diff/denom;
  output.y=ws/denom;
  return output;
}

/*f0980*/
float2 Pr_f0980(float mx2in)
{
	float mx2 = mx2in;
  float mr = 0.965f;
  float mr2 = mr*mr;
  float g1 = 0.16500f;
  float m1a = 0.134977f;
  float m1b = 0.134977f;
  float g2 = 2.105f;
  float m2a = 0.493677f;
  float m2b = 0.493677f;
  float g3 = 2.105f;
  float m3a = 0.497614f;
  float m3b = 0.497614f;

	float diff = mr2-mx2;/* m*m-s */
	g2 = g2*g1;
	g3 = g3*g1;
	float2 ps1 = irho(mx2, m1a*m1a, m1b*m1b);
	float2 ps2 = irho(mx2, m2a*m2a, m2b*m2b);
	float2 ps3 = irho(mx2, m3a*m3a, m3b*m3b);
	float2 iws = g1*ps1+g2*ps2+g3*ps3; /*mass dependent width */
	
  diff += iws.y;
  float ws = iws.x;
	float denom = diff*diff + ws*ws; /* common denominator*/
	
  float2 output;
  output.x = diff/denom; /* real part*/
	output.y = ws/denom; /* imaginary part*/
  return output;
}

/* a0980 four channels */
float2 Pr_a0980(float mx2in)
{
	float mx2 = mx2in;
  float mr = 0.99550f;
  float mr2 = mr*mr;
  float g1 = 0.36800f;
  float m1a = 0.547853f;
  float m1b = 0.134977f;
  float g2 = 0.46550f;
  float m2a = 0.493677f;
  float m2b = 0.493677f;
  float g3 = 0.46550f;
  float m3a = 0.497614f;
  float m3b = 0.497614f;
  float g4 = 0.48900f;
  float m4a = 0.95778f;
  float m4b = 0.134977f;

	g2 = g2*g1;
	g3 = g3*g1;
	g4 = g4*g1;

	// PI(s)
	int id1, id2;
	float r1, r2;
	id1 = get_id(sqrt(mx2));
	id2 = id1+1;
	r1 = get_ratio(sqrt(mx2));
	r2 = 1-r1;
	float PI_1s = dispersive_correction_EtaPi[id1]*r1 + dispersive_correction_EtaPi[id2]*r2;
	float PI_2s = dispersive_correction_KK[id1]*r1 + dispersive_correction_KK[id2]*r2;
	float PI_3s = dispersive_correction_KsKs[id1]*r1 + dispersive_correction_KsKs[id2]*r2;
	float PI_4s = dispersive_correction_EtapPi[id1]*r1 + dispersive_correction_EtapPi[id2]*r2;
	
	// PI(m*m)
	id1 = get_id(mr);
	id2 = id1+1;
	r1 = get_ratio(mr);
	r2 = 1-r1;
	float PI_1m2 = dispersive_correction_EtaPi[id1]*r1 + dispersive_correction_EtaPi[id2]*r2;
	float PI_2m2 = dispersive_correction_KK[id1]*r1 + dispersive_correction_KK[id2]*r2;
	float PI_3m2 = dispersive_correction_KsKs[id1]*r1 + dispersive_correction_KsKs[id2]*r2;
	float PI_4m2 = dispersive_correction_EtapPi[id1]*r1 + dispersive_correction_EtapPi[id2]*r2;

	float diff = mr2 - mx2 - g1*(PI_1s-PI_1m2) - g2*(PI_2s-PI_2m2) - g3*(PI_3s-PI_3m2) - g4*(PI_4s-PI_4m2);

	float ps1 = rho(mx2, m1a*m1a, m1b*m1b);
	float ps2 = rho(mx2, m2a*m2a, m2b*m2b);
	float ps3 = rho(mx2, m3a*m3a, m3b*m3b);
	float ps4 = rho(mx2, m4a*m4a, m4b*m4b);
	float ws = g1*ps1 + g2*ps2 + g3*ps3 + g4*ps4; /*mass dependent width */
	
	float denom = diff*diff + ws*ws; /* common denominator*/
	
  float2 output;
	output.x = diff/denom; /* real part*/
	output.y = ws/denom; /* imaginary part*/
  return output;
}

__kernel void kernelsumBW(__global float * mx123in,__global float * mx2in, uint n, __global float4 *par, float m1_2, float m2_2, __global out float2 * output){
uint index = get_global_id(0);
float m_123=mx123in[index];
float m_2=mx2in[index];
uint i;
float res_Re=0.0f;
float res_Im=0.0f;
float res_Retem=0.0f;
float res_Imtem=0.0f;
for (i=1;i<n;i=i+1){
  if(par[i].x == 1 && par[i].y == 1)
  {
    res_Retem = Pr_sigma(m_2).x*par[i].z - Pr_sigma(m_2).y*par[i].w;
    res_Imtem = Pr_sigma(m_2).x*par[i].w + Pr_sigma(m_2).y*par[i].z;
  }else 
  if(par[i].x == 2 && par[i].y == 2)
  {
    res_Retem = Pr_f0980(m_2).x*par[i].z - Pr_f0980(m_2).y*par[i].w;
    res_Imtem = Pr_f0980(m_2).x*par[i].w + Pr_f0980(m_2).y*par[i].z;
  }else
  if(par[i].x == 3 && par[i].y == 3)
  {
    res_Retem = Pr_a0980(m_2).x*par[i].z - Pr_a0980(m_2).y*par[i].w;
    res_Imtem = Pr_a0980(m_2).x*par[i].w + Pr_a0980(m_2).y*par[i].z;
  }else
  {
    float2 res_BW = breitwigner(m_2, par[i].x, par[i].x*par[i].x, par[i].y);
    res_Retem = (res_BW.x*par[i].z - res_BW.y*par[i].w);
    res_Imtem = (res_BW.x*par[i].w + res_BW.y*par[i].z);
  }
  res_Re = res_Re + res_Retem;
  res_Im = res_Im + res_Imtem;
}
float2 resx_BW = breitwigner(m_123, par[0].x, par[0].x*par[0].x, par[0].y);
float res_re1=0.0f;
float res_im1=0.0f;
res_re1 = res_Re * resx_BW.x - res_Im * resx_BW.y;
res_im1 = res_Re * resx_BW.y + res_Im * resx_BW.x;

output[index].x= res_re1;
output[index].y= res_im1;
}


/* Breit-Wigner + poly. part propagator */
__kernel void kernelComBW(__global float * mx2in, __global float4 *par, __global out float2 * output){
{
	uint i = get_global_id(0);
  float mr = par[0].x;
  float wr = par[0].y;
  float mr2 = mr*mr;

	float mx2 = mx2in[i];

	float diff = mr2-mx2;
	float denom = diff*diff + wr*wr*mr2;

  float2 Pr_Com;
  //Pr_Com.x = diff/denom + 4.4626*cos(0.8826); //paras obtained from the data fitting
  //Pr_Com.y = wr*mr/denom + 4.4626*sin(0.8826);
  Pr_Com.x = diff/denom; 
  Pr_Com.y = wr*mr/denom; 

  //output[i].x = (Pr_Com.x*par[0].z - Pr_Com.y*par[0].w);
  //output[i].y = (Pr_Com.x*par[0].w + Pr_Com.y*par[0].z);
  output[i].x = (Pr_Com.x + par[0].z);
  output[i].y = (Pr_Com.y + par[0].w);
	}
}


