/*
 * Contractions.cl
 *
 *  Created on: Dec 6, 2010
 *      Author: nberger
 */

#pragma OPENCL EXTENSION cl_amd_fp64 : enable

#ifndef F44STRUCTS
#define F44STRUCTS

typedef struct {
  float4  c;
  float4  d;
  float4  e;
  float4  f;
} float44;

#endif

#ifndef F444STRUCTS
#define F444STRUCTS

typedef struct {
  float4  cc;
  float4  cd;
  float4  ce;
  float4  cf;
  float4  dc;
  float4  dd;
  float4  de;
  float4  df;
  float4  ec;
  float4  ed;
  float4  ee;
  float4  ef;
  float4  fc;
  float4  fd;
  float4  fe;
  float4  ff;
} float444;

#endif

/* create a unity stream */
__kernel void kernelone(__global out float * a){
	uint i = get_global_id(0);
	a[i] = 1.0f;
}

/* create a unity stream */
__kernel void kernelone_c(__global out float2 * a){
	uint i = get_global_id(0);
	a[i].x = 1.0f;
	a[i].y = 0.0f;
}


 __kernel void kernelcontractscalar(__global float * tensor1, __global float * tensor2, __global float2 * propagator1, __global float2 * propagator2, __global out float2 * result)
{
	uint i = get_global_id(0);
	float tensorsum = tensor1[i]*tensor2[i];
	result[i].x = tensorsum*(propagator1[i].x*propagator2[i].x+propagator1[i].y*propagator2[i].y);
	result[i].y = tensorsum*(-propagator1[i].x*propagator2[i].y+propagator1[i].y*propagator2[i].x);
}


__kernel void kernelcontractscalar_f_u(__global float * tensor1, __global float2 * propagator1, __global float2 * propagator2, __global out float2 * result)
{
	uint i = get_global_id(0);
 	float tensorsum = tensor1[i];
 	result[i].x = tensorsum*(propagator1[i].x*propagator2[i].x+propagator1[i].y*propagator2[i].y);
 	result[i].y = tensorsum*(-propagator1[i].x*propagator2[i].y+propagator1[i].y*propagator2[i].x);
 }


__kernel void kernelcontractscalar_u_f( __global float2 * propagator1, __global float * tensor2, __global float2 * propagator2, __global out float2 * result)
{
	uint i = get_global_id(0);
 	float tensorsum = tensor2[i];
 	result[i].x = tensorsum*(propagator1[i].x*propagator2[i].x+propagator1[i].y*propagator2[i].y);
 	result[i].y = tensorsum*(-propagator1[i].x*propagator2[i].y+propagator1[i].y*propagator2[i].x);
 }

__kernel void kernelcontractscalar_u_u( __global float2 * propagator1, __global float2 * propagator2, __global out float2 * result)
{
	uint i = get_global_id(0);
 	result[i].x = (propagator1[i].x*propagator2[i].x+propagator1[i].y*propagator2[i].y);
 	result[i].y = (-propagator1[i].x*propagator2[i].y+propagator1[i].y*propagator2[i].x);
 }



/* Multiplication of two real numbers*/
 __kernel void kernelcontractscalarorbital(__global float * tensor1, __global float * tensor2, __global  float * result)
{
	 uint i = get_global_id(0);
	result[i] = tensor1[i]*tensor2[i];
}

/* Multiplication of two complex and a real number obtained from summing the 1 and 2 components of two vectors.*/
 __kernel void kernelcontractmesons(__global float4 * tensor1, __global float4 * tensor2, __global float2 * propagator1, __global float2 * propagator2, __global out float2 * result)
{
	 uint i = get_global_id(0);
	float tensorsum = 0.5f*(tensor1[i].x*tensor2[i].x + tensor1[i].y*tensor2[i].y);
	result[i].x = tensorsum*(propagator1[i].x*propagator2[i].x+propagator1[i].y*propagator2[i].y);
	result[i].y = tensorsum*(-propagator1[i].x*propagator2[i].y+propagator1[i].y*propagator2[i].x);
}

 __kernel void kernelcontractmesons_v_v(__global float4 * propagator1real, __global float4 * propagator1imag, __global float4 * propagator2real, __global float4 * propagator2imag, __global out float2 * result)
{
	 uint i = get_global_id(0);
	float4 r = (propagator1real[i]*propagator2real[i]+propagator1imag[i]*propagator2imag[i]);
	float4 im = (-propagator1real[i]*propagator2imag[i]+propagator1imag[i]*propagator2real[i]);
	result[i].x = 0.5f*(r.x + r.y);
	result[i].y = 0.5f*(im.x + im.y);
}

__kernel void kernelcontractmesons_s_v(__global float4 * tensor1, __global float2 * propagator1, __global float4 * propagator2real, __global float4 * propagator2imag, __global  out float2 * result)
{
	uint i = get_global_id(0);
	float4 r,im;
	float4 propagator1real = tensor1[i] * propagator1[i].x;
	float4 propagator1imag = tensor1[i] * propagator1[i].y;
	r = (propagator1real*propagator2real[i]+propagator1imag*propagator2imag[i]);
	im = (-propagator1real*propagator2imag[i]+propagator1imag*propagator2real[i]);
	result[i].x = 0.5f*(r.x + r.y);
	result[i].y = 0.5f*(im.x + im.y);
}

__kernel void kernelcontractmesons_v_s(__global float4 * tensor2, __global float4 * propagator1real, __global float4 * propagator1imag, __global float2 * propagator2, __global out float2 * result)
{
	uint i = get_global_id(0);
	float4 r,im;
	float4 propagator2real = tensor2[i] * propagator2[i].x;
	float4 propagator2imag = tensor2[i] * propagator2[i].y;
	r = (propagator1real[i]*propagator2real+propagator1imag[i]*propagator2imag);
	im = (-propagator1real[i]*propagator2imag+propagator1imag[i]*propagator2real);
	result[i].x = 0.5f*(r.x + r.y);
	result[i].y = 0.5f*(im.x + im.y);
}



/* a real number obtained from summing the 1 and 2 components of two vectors.*/
 __kernel void kernelcontractmesonsorbital(__global float4 * tensor1, __global float4 * tensor2,  __global out  float * result)
{
	 uint i = get_global_id(0);
	result[i] = 0.5f*(tensor1[i].x*tensor2[i].x + tensor1[i].y*tensor2[i].y);
}

/* Contraction __kernel for radiative decay to mesons */
 __kernel void kernelcontractradmesons(__global float44 * tensor1, __global float44 * tensor2, __global float44 * gperp, __global float2 * propagator1, __global float2 * propagator2, __global out float2 * result)
{
	uint i = get_global_id(0);
	float44 sumoneindex;
	float4 sumtwoindex;
	float tensorsum;
	/* Lines commented out do not contribute to the result */
	sumoneindex.c.x = tensor1[i].c.x*gperp[i].c.x + tensor1[i].c.y*gperp[i].d.x + tensor1[i].c.z*gperp[i].e.x;/* + tensor1[i]c.w*gperp[i].f.x;*/
	sumoneindex.d.x = tensor1[i].d.x*gperp[i].c.x + tensor1[i].d.y*gperp[i].d.x + tensor1[i].d.z*gperp[i].e.x;/* + tensor1[i].d.w*gperp[i].f.x;*/
	/*sumoneindex.f.x = tensor1[i].f.x*gperp[i].c.x + tensor1[i].f.y*gperp[i].d.x + tensor1[i].f.z*gperp[i].e.x + tensor1[i].f.w*gperp[i].f.x;*/

	sumoneindex.c.y = tensor1[i].c.x*gperp[i].c.y + tensor1[i].c.y*gperp[i].d.y + tensor1[i].c.z*gperp[i].e.y;/* + tensor1[i].c.w*gperp[i].f.y;*/
	sumoneindex.d.y = tensor1[i].d.x*gperp[i].c.y + tensor1[i].d.y*gperp[i].d.y + tensor1[i].d.z*gperp[i].e.y;/* + tensor1[i].d.w*gperp[i].f.y;*/
	/*sumoneindex.e.y = tensor1[i].e.x*gperp[i].c.y + tensor1[i].e.y*gperp[i].d.y + tensor1[i].e.z*gperp[i].e.y;// + tensor1[i].e.w*gperp[i].f.y;*/
	/*sumoneindex.f.y = tensor1[i].f.x*gperp[i].c.y + tensor1[i].f.y*gperp[i].d.y + tensor1[i].f.z*gperp[i].e.y + tensor1[i].f.w*gperp[i].f.y;*/

	sumoneindex.c.z = tensor1[i].c.x*gperp[i].c.z + tensor1[i].c.y*gperp[i].d.z + tensor1[i].c.z*gperp[i].e.z;/* + tensor1[i].c.w*gperp[i].f.z;*/
	sumoneindex.d.z = tensor1[i].d.x*gperp[i].c.z + tensor1[i].d.y*gperp[i].d.z + tensor1[i].d.z*gperp[i].e.z;/* + tensor1[i].d.w*gperp[i].f.z;*/
	/*sumoneindex.e.z = tensor1[i].e.x*gperp[i].c.z + tensor1[i].e.y*gperp[i].d.z + tensor1[i].e.z*gperp[i].e.z;// + tensor1[i].e.w*gperp[i].f.z;*/
	/*sumoneindex.f.z = tensor1[i].f.x*gperp[i].c.z + tensor1[i].f.y*gperp[i].d.z + tensor1[i].f.z*gperp[i].e.z + tensor1[i].f.w*gperp[i].f.z;*/

	sumoneindex.c.w = 0.0f;/*tensor1[i].c.x*gperp[i].c.w + tensor1[i].c.y*gperp[i].d.w + tensor1[i].c.z*gperp[i].e.w + tensor1[i].c.w*gperp[i].f.w;*/
	sumoneindex.d.w = 0.0f;/*tensor1[i].d.x*gperp[i].c.w + tensor1[i].d.y*gperp[i].d.w + tensor1[i].d.z*gperp[i].e.w + tensor1[i].d.w*gperp[i].f.w;*/
	/*sumoneindex.e.w = 0.0f;//tensor1[i].e.x*gperp[i].c.w + tensor1[i].e.y*gperp[i].d.w + tensor1[i].e.z*gperp[i].e.w + tensor1[i].e.w*gperp[i].f.w;*/
	/*sumoneindex.f.x = tensor1[i].f.x*gperp[i].c.w + tensor1[i].f.y*gperp[i].d.w + tensor1[i].f.z*gperp[i].e.w + tensor1[i].f.w*gperp[i].f.w;*/

	sumtwoindex.x = sumoneindex.c.x*tensor2[i].c.x + sumoneindex.c.y*tensor2[i].c.y + sumoneindex.c.z*tensor2[i].c.z;/* + sumoneindex.c.w*tensor2[i].c.w;*/
	sumtwoindex.y = sumoneindex.d.x*tensor2[i].d.x + sumoneindex.d.y*tensor2[i].d.y + sumoneindex.d.z*tensor2[i].d.z;/* + sumoneindex.d.w*tensor2[i].d.w;*/
	/*sumtwoindex.z = sumoneindex.e.x*tensor2[i].e.x + sumoneindex.e.y*tensor2[i].e.y + sumoneindex.e.z*tensor2[i].e.z;// + sumoneindex.e.w*tensor2[i].e.w;*/
	/*sumtwoindex.w = sumoneindex.f.x*tensor2[i].f.x + sumoneindex.f.y*tensor2[i].f.y + sumoneindex.f.z*tensor2[i].f.z + sumoneindex.f.w*tensor2[i].f.w;*/


	tensorsum = -0.5f*(sumtwoindex.x+sumtwoindex.y);
	result[i].x = tensorsum*(propagator1[i].x*propagator2[i].x+propagator1[i].y*propagator2[i].y);
	result[i].y = tensorsum*(-propagator1[i].x*propagator2[i].y+propagator1[i].y*propagator2[i].x);
}

/* Contraction __kernel for radiative decay to mesons -orbial part only*/
 __kernel void kernelcontractradmesonsorbital(__global float44 * tensor1, __global float44 * tensor2, __global float44 * gperp, __global out float * result)
{
	 uint i = get_global_id(0);
	float44 sumoneindex;
	float4 sumtwoindex;

	sumoneindex.c.x = tensor1[i].c.x*gperp[i].c.x + tensor1[i].c.y*gperp[i].d.x + tensor1[i].c.z*gperp[i].e.x;
	sumoneindex.d.x = tensor1[i].d.x*gperp[i].c.x + tensor1[i].d.y*gperp[i].d.x + tensor1[i].d.z*gperp[i].e.x;


	sumoneindex.c.y = tensor1[i].c.x*gperp[i].c.y + tensor1[i].c.y*gperp[i].d.y + tensor1[i].c.z*gperp[i].e.y;
	sumoneindex.d.y = tensor1[i].d.x*gperp[i].c.y + tensor1[i].d.y*gperp[i].d.y + tensor1[i].d.z*gperp[i].e.y;


	sumoneindex.c.z = tensor1[i].c.x*gperp[i].c.z + tensor1[i].c.y*gperp[i].d.z + tensor1[i].c.z*gperp[i].e.z;
	sumoneindex.d.z = tensor1[i].d.x*gperp[i].c.z + tensor1[i].d.y*gperp[i].d.z + tensor1[i].d.z*gperp[i].e.z;


	sumoneindex.c.w = 0.0f;
	sumoneindex.d.w = 0.0f;

	sumtwoindex.x = sumoneindex.c.x*tensor2[i].c.x + sumoneindex.c.y*tensor2[i].c.y + sumoneindex.c.z*tensor2[i].c.z;
	sumtwoindex.y = sumoneindex.d.x*tensor2[i].d.x + sumoneindex.d.y*tensor2[i].d.y + sumoneindex.d.z*tensor2[i].d.z;

	result[i] = -0.5f*(sumtwoindex.x+sumtwoindex.y);
}

 // Contraction kernel for radiative decay to mesons, factorized and unfactorized
   __kernel void kernelcontractradmesons_f_u(__global float44 * tensor1, __global float2 * propagator1, __global float44 * gperp,  __global float44 * p2real, __global float44 * p2imag, __global out float2 * result)
  {
 	  uint i = get_global_id(0);
  	float44 sumoneindexreal;
  	float2 sumtwoindexrealA;
  	float2 sumtwoindexrealB;
  	float44 sumoneindeximag;
  	float2 sumtwoindeximagA;
  	float2 sumtwoindeximagB;
  	float44 p1real;
  	float44 p1imag;

  	p1real.c = tensor1[i].c * propagator1[i].x;
  	p1real.d = tensor1[i].d * propagator1[i].x;
  	p1real.e = tensor1[i].e * propagator1[i].x;
  	p1real.f = tensor1[i].f * propagator1[i].x;

	p1imag.c = tensor1[i].c * propagator1[i].y;
  	p1imag.d = tensor1[i].d * propagator1[i].y;
  	p1imag.e = tensor1[i].e * propagator1[i].y;
  	p1imag.f = tensor1[i].f * propagator1[i].y;


  	sumoneindexreal.c.x = p1real.c.x*gperp[i].c.x + p1real.c.y*gperp[i].d.x + p1real.c.z*gperp[i].e.x;
  	sumoneindexreal.d.x = p1real.d.x*gperp[i].c.x + p1real.d.y*gperp[i].d.x + p1real.d.z*gperp[i].e.x;

  	sumoneindexreal.c.y = p1real.c.x*gperp[i].c.y + p1real.c.y*gperp[i].d.y + p1real.c.z*gperp[i].e.y;
  	sumoneindexreal.d.y = p1real.d.x*gperp[i].c.y + p1real.d.y*gperp[i].d.y + p1real.d.z*gperp[i].e.y;

  	sumoneindexreal.c.z = p1real.c.x*gperp[i].c.z + p1real.c.y*gperp[i].d.z + p1real.c.z*gperp[i].e.z;
  	sumoneindexreal.d.z = p1real.d.x*gperp[i].c.z + p1real.d.y*gperp[i].d.z + p1real.d.z*gperp[i].e.z;

  	sumoneindexreal.c.w = 0.0f;
  	sumoneindexreal.d.w = 0.0f;

  	sumoneindeximag.c.x = p1imag.c.x*gperp[i].c.x + p1imag.c.y*gperp[i].d.x + p1imag.c.z*gperp[i].e.x;
  	sumoneindeximag.d.x = p1imag.d.x*gperp[i].c.x + p1imag.d.y*gperp[i].d.x + p1imag.d.z*gperp[i].e.x;

  	sumoneindeximag.c.y = p1imag.c.x*gperp[i].c.y + p1imag.c.y*gperp[i].d.y + p1imag.c.z*gperp[i].e.y;
  	sumoneindeximag.d.y = p1imag.d.x*gperp[i].c.y + p1imag.d.y*gperp[i].d.y + p1imag.d.z*gperp[i].e.y;

  	sumoneindeximag.c.z = p1imag.c.x*gperp[i].c.z + p1imag.c.y*gperp[i].d.z + p1imag.c.z*gperp[i].e.z;
  	sumoneindeximag.d.z = p1imag.d.x*gperp[i].c.z + p1imag.d.y*gperp[i].d.z + p1imag.d.z*gperp[i].e.z;

  	sumoneindeximag.c.w = 0.0f;
  	sumoneindeximag.d.w = 0.0f;

  	sumtwoindexrealA.x = sumoneindexreal.c.x*p2real[i].c.x + sumoneindexreal.c.y*p2real[i].c.y + sumoneindexreal.c.z*p2real[i].c.z;
  	sumtwoindexrealB.x = sumoneindeximag.c.x*p2imag[i].c.x + sumoneindeximag.c.y*p2imag[i].c.y + sumoneindeximag.c.z*p2imag[i].c.z;

  	sumtwoindexrealA.y = sumoneindexreal.d.x*p2real[i].d.x + sumoneindexreal.d.y*p2real[i].d.y + sumoneindexreal.d.z*p2real[i].d.z;
  	sumtwoindexrealB.y = sumoneindeximag.d.x*p2imag[i].d.x + sumoneindeximag.d.y*p2imag[i].d.y + sumoneindeximag.d.z*p2imag[i].d.z;

  	sumtwoindeximagA.x = - sumoneindexreal.c.x*p2imag[i].c.x - sumoneindexreal.c.y*p2imag[i].c.y - sumoneindexreal.c.z*p2imag[i].c.z;
  	sumtwoindeximagB.x = sumoneindeximag.c.x*p2real[i].c.x + sumoneindeximag.c.y*p2real[i].c.y + sumoneindeximag.c.z*p2real[i].c.z;

  	sumtwoindeximagA.y = - sumoneindexreal.d.x*p2imag[i].d.x - sumoneindexreal.d.y*p2imag[i].d.y - sumoneindexreal.d.z*p2imag[i].d.z;
  	sumtwoindeximagB.y = sumoneindeximag.d.x*p2real[i].d.x + sumoneindeximag.d.y*p2real[i].d.y + sumoneindeximag.d.z*p2real[i].d.z;


  	result[i].x = -0.5f*(sumtwoindexrealA.x+sumtwoindexrealB.x+sumtwoindexrealA.y+sumtwoindexrealB.y);
  	result[i].y = -0.5f*(sumtwoindeximagA.x+sumtwoindeximagB.x+sumtwoindeximagA.y+sumtwoindeximagB.y);
  }


 // Contraction kernel for radiative decay to mesons, factorized and unfactorized
__kernel void kernelcontractradmesons_u_f(__global float44 * p1real, __global float44 * p1imag, __global float44 * gperp, __global float44 * tensor2, __global float2 * propagator2,  __global out float2 * result)
    {
		uint i = get_global_id(0);
    	float44 sumoneindexreal;
    	float2 sumtwoindexrealA;
    	float2 sumtwoindexrealB;
    	float44 sumoneindeximag;
    	float2 sumtwoindeximagA;
    	float2 sumtwoindeximagB;
    	float44 p2real;
    	float44 p2imag;

    	p2real.c = tensor2[i].c * propagator2[i].x;
    	p2real.d = tensor2[i].d * propagator2[i].x;
    	p2real.e = tensor2[i].e * propagator2[i].x;
    	p2real.f = tensor2[i].f * propagator2[i].x;

    	p2imag.c = tensor2[i].c * propagator2[i].y;
    	p2imag.d = tensor2[i].d * propagator2[i].y;
    	p2imag.e = tensor2[i].e * propagator2[i].y;
    	p2imag.f = tensor2[i].f * propagator2[i].y;


    	sumoneindexreal.c.x = p1real[i].c.x*gperp[i].c.x + p1real[i].c.y*gperp[i].d.x + p1real[i].c.z*gperp[i].e.x;
    	sumoneindexreal.d.x = p1real[i].d.x*gperp[i].c.x + p1real[i].d.y*gperp[i].d.x + p1real[i].d.z*gperp[i].e.x;

    	sumoneindexreal.c.y = p1real[i].c.x*gperp[i].c.y + p1real[i].c.y*gperp[i].d.y + p1real[i].c.z*gperp[i].e.y;
    	sumoneindexreal.d.y = p1real[i].d.x*gperp[i].c.y + p1real[i].d.y*gperp[i].d.y + p1real[i].d.z*gperp[i].e.y;

    	sumoneindexreal.c.z = p1real[i].c.x*gperp[i].c.z + p1real[i].c.y*gperp[i].d.z + p1real[i].c.z*gperp[i].e.z;
    	sumoneindexreal.d.z = p1real[i].d.x*gperp[i].c.z + p1real[i].d.y*gperp[i].d.z + p1real[i].d.z*gperp[i].e.z;

    	sumoneindexreal.c.w = 0.0f;
    	sumoneindexreal.d.w = 0.0f;

    	sumoneindeximag.c.x = p1imag[i].c.x*gperp[i].c.x + p1imag[i].c.y*gperp[i].d.x + p1imag[i].c.z*gperp[i].e.x;
    	sumoneindeximag.d.x = p1imag[i].d.x*gperp[i].c.x + p1imag[i].d.y*gperp[i].d.x + p1imag[i].d.z*gperp[i].e.x;

    	sumoneindeximag.c.y = p1imag[i].c.x*gperp[i].c.y + p1imag[i].c.y*gperp[i].d.y + p1imag[i].c.z*gperp[i].e.y;
    	sumoneindeximag.d.y = p1imag[i].d.x*gperp[i].c.y + p1imag[i].d.y*gperp[i].d.y + p1imag[i].d.z*gperp[i].e.y;

    	sumoneindeximag.c.z = p1imag[i].c.x*gperp[i].c.z + p1imag[i].c.y*gperp[i].d.z + p1imag[i].c.z*gperp[i].e.z;
    	sumoneindeximag.d.z = p1imag[i].d.x*gperp[i].c.z + p1imag[i].d.y*gperp[i].d.z + p1imag[i].d.z*gperp[i].e.z;

    	sumoneindeximag.c.w = 0.0f;
    	sumoneindeximag.d.w = 0.0f;

    	sumtwoindexrealA.x = sumoneindexreal.c.x*p2real.c.x + sumoneindexreal.c.y*p2real.c.y + sumoneindexreal.c.z*p2real.c.z;
    	sumtwoindexrealB.x = sumoneindeximag.c.x*p2imag.c.x + sumoneindeximag.c.y*p2imag.c.y + sumoneindeximag.c.z*p2imag.c.z;

    	sumtwoindexrealA.y = sumoneindexreal.d.x*p2real.d.x + sumoneindexreal.d.y*p2real.d.y + sumoneindexreal.d.z*p2real.d.z;
    	sumtwoindexrealB.y = sumoneindeximag.d.x*p2imag.d.x + sumoneindeximag.d.y*p2imag.d.y + sumoneindeximag.d.z*p2imag.d.z;

    	sumtwoindeximagA.x = - sumoneindexreal.c.x*p2imag.c.x - sumoneindexreal.c.y*p2imag.c.y - sumoneindexreal.c.z*p2imag.c.z;
    	sumtwoindeximagB.x = sumoneindeximag.c.x*p2real.c.x + sumoneindeximag.c.y*p2real.c.y + sumoneindeximag.c.z*p2real.c.z;

    	sumtwoindeximagA.y = - sumoneindexreal.d.x*p2imag.d.x - sumoneindexreal.d.y*p2imag.d.y - sumoneindexreal.d.z*p2imag.d.z;
    	sumtwoindeximagB.y = sumoneindeximag.d.x*p2real.d.x + sumoneindeximag.d.y*p2real.d.y + sumoneindeximag.d.z*p2real.d.z;


    	result[i].x = -0.5f*(sumtwoindexrealA.x+sumtwoindexrealB.x+sumtwoindexrealA.y+sumtwoindexrealB.y);
    	result[i].y = -0.5f*(sumtwoindeximagA.x+sumtwoindeximagB.x+sumtwoindeximagA.y+sumtwoindeximagB.y);
    }



 // Contraction kernel for radiative decay to three mesons
  __kernel void kernelcontract3radmesons(__global float44 * gperp, __global float44 * p1real, __global float44 * p1imag, __global float44 * p2real, __global float44 * p2imag, __global out float2 * result)
 {
	  uint i = get_global_id(0);
 	float44 sumoneindexreal;
 	float2 sumtwoindexrealA;
 	float2 sumtwoindexrealB;
 	float44 sumoneindeximag;
 	float2 sumtwoindeximagA;
 	float2 sumtwoindeximagB;

 	sumoneindexreal.c.x = p1real[i].c.x*gperp[i].c.x + p1real[i].c.y*gperp[i].d.x + p1real[i].c.z*gperp[i].e.x;
 	sumoneindexreal.d.x = p1real[i].d.x*gperp[i].c.x + p1real[i].d.y*gperp[i].d.x + p1real[i].d.z*gperp[i].e.x;

 	sumoneindexreal.c.y = p1real[i].c.x*gperp[i].c.y + p1real[i].c.y*gperp[i].d.y + p1real[i].c.z*gperp[i].e.y;
 	sumoneindexreal.d.y = p1real[i].d.x*gperp[i].c.y + p1real[i].d.y*gperp[i].d.y + p1real[i].d.z*gperp[i].e.y;

 	sumoneindexreal.c.z = p1real[i].c.x*gperp[i].c.z + p1real[i].c.y*gperp[i].d.z + p1real[i].c.z*gperp[i].e.z;
 	sumoneindexreal.d.z = p1real[i].d.x*gperp[i].c.z + p1real[i].d.y*gperp[i].d.z + p1real[i].d.z*gperp[i].e.z;

 	sumoneindexreal.c.w = 0.0f;
 	sumoneindexreal.d.w = 0.0f;

 	sumoneindeximag.c.x = p1imag[i].c.x*gperp[i].c.x + p1imag[i].c.y*gperp[i].d.x + p1imag[i].c.z*gperp[i].e.x;
 	sumoneindeximag.d.x = p1imag[i].d.x*gperp[i].c.x + p1imag[i].d.y*gperp[i].d.x + p1imag[i].d.z*gperp[i].e.x;

 	sumoneindeximag.c.y = p1imag[i].c.x*gperp[i].c.y + p1imag[i].c.y*gperp[i].d.y + p1imag[i].c.z*gperp[i].e.y;
 	sumoneindeximag.d.y = p1imag[i].d.x*gperp[i].c.y + p1imag[i].d.y*gperp[i].d.y + p1imag[i].d.z*gperp[i].e.y;

 	sumoneindeximag.c.z = p1imag[i].c.x*gperp[i].c.z + p1imag[i].c.y*gperp[i].d.z + p1imag[i].c.z*gperp[i].e.z;
 	sumoneindeximag.d.z = p1imag[i].d.x*gperp[i].c.z + p1imag[i].d.y*gperp[i].d.z + p1imag[i].d.z*gperp[i].e.z;

 	sumoneindeximag.c.w = 0.0f;
 	sumoneindeximag.d.w = 0.0f;

 	sumtwoindexrealA.x = sumoneindexreal.c.x*p2real[i].c.x + sumoneindexreal.c.y*p2real[i].c.y + sumoneindexreal.c.z*p2real[i].c.z;
 	sumtwoindexrealB.x = sumoneindeximag.c.x*p2imag[i].c.x + sumoneindeximag.c.y*p2imag[i].c.y + sumoneindeximag.c.z*p2imag[i].c.z;

 	sumtwoindexrealA.y = sumoneindexreal.d.x*p2real[i].d.x + sumoneindexreal.d.y*p2real[i].d.y + sumoneindexreal.d.z*p2real[i].d.z;
 	sumtwoindexrealB.y = sumoneindeximag.d.x*p2imag[i].d.x + sumoneindeximag.d.y*p2imag[i].d.y + sumoneindeximag.d.z*p2imag[i].d.z;

 	sumtwoindeximagA.x = - sumoneindexreal.c.x*p2imag[i].c.x - sumoneindexreal.c.y*p2imag[i].c.y - sumoneindexreal.c.z*p2imag[i].c.z;
 	sumtwoindeximagB.x = sumoneindeximag.c.x*p2real[i].c.x + sumoneindeximag.c.y*p2real[i].c.y + sumoneindeximag.c.z*p2real[i].c.z;

 	sumtwoindeximagA.y = - sumoneindexreal.d.x*p2imag[i].d.x - sumoneindexreal.d.y*p2imag[i].d.y - sumoneindexreal.d.z*p2imag[i].d.z;
 	sumtwoindeximagB.y = sumoneindeximag.d.x*p2real[i].d.x + sumoneindeximag.d.y*p2real[i].d.y + sumoneindeximag.d.z*p2real[i].d.z;


 	result[i].x = -0.5f*(sumtwoindexrealA.x+sumtwoindexrealB.x+sumtwoindexrealA.y+sumtwoindexrealB.y);
 	result[i].y = -0.5f*(sumtwoindeximagA.x+sumtwoindeximagB.x+sumtwoindeximagA.y+sumtwoindeximagB.y);
 }
