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


// Multiplication of two complex numbers
 __kernel void kernelmultiplycomplex(__global float2 * in1, __global float2 * in2, __global out float2 * result)
{
	 uint pos = get_global_id(0);
	result[pos].x = (in1[pos].x*in2[pos].x-in1[pos].y*in2[pos].y);
	result[pos].y = (in1[pos].x*in2[pos].y+in1[pos].y*in2[pos].x);
}

// Addition of two complex numbers
 __kernel void kerneladdcomplex(__global float2 * in1, __global float2 * in2, __global out float2 * result)
{
	 uint pos = get_global_id(0);
	result[pos].x = in1[pos].x+in2[pos].x;
	result[pos].y = in1[pos].y+in2[pos].y;
}

// Multiplication of a complex and a real number
 __kernel void kernelmultiplycomplexf(__global float2 * in1, __global float * in2, __global out float2 * result)
{
	 uint pos = get_global_id(0);
	result[pos].x = in1[pos].x*in2[pos];
	result[pos].y = in1[pos].y*in2[pos];
}

// Split a complex number into real and imaginary part
__kernel void kernelcomplexsplit(__global float2 * myin, __global out float * real, __global out float * imag)
{
	uint pos = get_global_id(0);
	real[pos] = myin[pos].x;
	imag[pos] = myin[pos].y;
}

/*Multiply a complex vector with a complex scalar*/
__kernel void kerneltensormult_c4_c(__global float4 * lreal, __global float4 * limag, __global float * rreal, __global float * rimag, __global out float4 * resultreal, __global out float4 * resultimag)
{
	uint pos = get_global_id(0);
	resultreal[pos] = lreal[pos]*rreal[pos] - limag[pos]*rimag[pos];
	resultimag[pos] = lreal[pos]*rimag[pos] + limag[pos]*rreal[pos];
}

/*Multiply a vector with a complex scalar*/
__kernel void kerneltensormult_4_c(__global float4 * lreal, __global float * rreal, __global float * rimag, __global out float4 * resultreal, __global out float4 * resultimag)
{
	uint pos = get_global_id(0);
	resultreal[pos] = lreal[pos]*rreal[pos];
	resultimag[pos] = lreal[pos]*rimag[pos];
}


/*Multiply a complex tensor2 with a complex scalar*/
__kernel void kerneltensormult_c_c44(__global float * lreal, __global float * limag, __global float44 * rreal, __global float44 * rimag, __global out float44 * resultreal, __global out float44 * resultimag)
{
	uint pos = get_global_id(0);
	resultreal[pos].c = lreal[pos]*rreal[pos].c - limag[pos]*rimag[pos].c;
	resultreal[pos].d = lreal[pos]*rreal[pos].d - limag[pos]*rimag[pos].d;
	resultreal[pos].e = lreal[pos]*rreal[pos].e - limag[pos]*rimag[pos].e;
	resultreal[pos].f = lreal[pos]*rreal[pos].f - limag[pos]*rimag[pos].f;

	resultimag[pos].c = lreal[pos]*rimag[pos].c + limag[pos]*rreal[pos].c;
	resultimag[pos].d = lreal[pos]*rimag[pos].d + limag[pos]*rreal[pos].d;
	resultimag[pos].e = lreal[pos]*rimag[pos].e + limag[pos]*rreal[pos].e;
	resultimag[pos].f = lreal[pos]*rimag[pos].f + limag[pos]*rreal[pos].f;
}
