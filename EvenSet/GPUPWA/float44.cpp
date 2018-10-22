

#include "float44.h"

// add components of an int (does just the conversion to double)
double addcomponents(int & x){
	return (double)x;
}

// add components of a float (does just the conversion to double)
double addcomponents(float & x){
	return (double)x;
}
// add components of a double (does nothing)
double addcomponents(double & x){
	return x;
}
// add components of a float 2
double addcomponents(float2 & x){
	return (double)x.x + (double)x.y;
}

// add components of a float 4
double addcomponents(float4 & x){
	return (double)x.x + (double)x.y + (double)x.z + (double)x.w;
}

// add components of a float 16
double addcomponents(float16 & x){
	return (double)x.s0 + (double)x.s1 + (double)x.s2 + (double)x.s3
	     + (double)x.s4 + (double)x.s5 + (double)x.s6 + (double)x.s7
	     + (double)x.s8 + (double)x.s9 + (double)x.sA + (double)x.sB
	     + (double)x.sC + (double)x.sD + (double)x.sE + (double)x.sF  ;
}

// add components of a float 44
double addcomponents(float44 & x){
	double a,b,c,d;
	a = (double)x.c.x + (double)x.c.y + (double)x.c.z + (double)x.c.w;
	b = (double)x.d.x + (double)x.d.y + (double)x.d.z + (double)x.d.w;
	c = (double)x.e.x + (double)x.e.y + (double)x.e.z + (double)x.e.w;
	d = (double)x.f.x + (double)x.f.y + (double)x.f.z + (double)x.f.w;

	return a+b+c+d;
}
// add components of a double 2
double addcomponents(double2 & x){
	return x.x + x.y;
}


// build a double2 - replacement for the constructor...
double2 mdouble2(const double x, const double y){
	double2 r;
	r.x = x;
	r.y = y;
	return r;

}

// build a float2 - replacement for the constructor...
float2 mfloat2(const float x, const float y){
	float2 r;
	r.x = x;
	r.y = y;
	return r;

}

// build a float3 - replacement for the constructor...
float3 mfloat3(const float x, const float y, const float z){
	float3 r;
	r.x = x;
	r.y = y;
	r.z = z;
	return r;

}

// build a float4 - replacement for the constructor...
float4 mfloat4(const float x, const float y, const float z, const float w){
	float4 r;
	r.x = x;
	r.y = y;
	r.z = z;
	r.w = w;
	return r;

}


float2 operator * (const float2 &lhs, const float2 &rhs){
    float2 res;
    res.x = lhs.x*rhs.x;
    res.y = lhs.y*rhs.y;
    return res;

}

float2 operator * (const float2 &lhs, const float &rhs){
    float2 res;
    res.x = lhs.x*rhs;
    res.y = lhs.y*rhs;
    return res;
}

float2 operator * (const float &lhs, const float2 &rhs){
    float2 res;
    res.x = lhs*rhs.x;
    res.y = lhs*rhs.y;
    return res;
}

double2 operator * (const double2 &lhs, const double2 &rhs){
	  double2 res;
	  res.x = lhs.x*rhs.x;
	  res.y = lhs.y*rhs.y;
	  return res;
}

double2 operator * (const double2 &lhs, const float &rhs){
    double2 res;
    res.x = lhs.x*rhs;
    res.y = lhs.y*rhs;
    return res;
}

double2 operator * (const float &lhs, const double2 &rhs){
    double2 res;
    res.x = lhs*rhs.x;
    res.y = lhs*rhs.y;
    return res;
}


float2 operator + (const float2 &lhs, const float2 &rhs){
    float2 res;
    res.x = lhs.x+rhs.x;
    res.y = lhs.y+rhs.y;
    return res;
}

double2 operator + (const double2 &lhs, const double2 &rhs){
    double2 res;
    res.x = lhs.x+rhs.x;
    res.y = lhs.y+rhs.y;
    return res;
}


float4 operator + (const float4 &lhs, const float4 &rhs){
    float4 res;
    res.x = lhs.x+rhs.x;
    res.y = lhs.y+rhs.y;
    res.z = lhs.z+rhs.z;
    res.w = lhs.w+rhs.w;
    return res;
}

float16 operator + (const float16 &lhs, const float16 &rhs){
    float16 res;
    res.s0 = lhs.s0+rhs.s0;
    res.s1 = lhs.s1+rhs.s1;
    res.s2 = lhs.s2+rhs.s2;
    res.s3 = lhs.s3+rhs.s3;
    res.s4 = lhs.s4+rhs.s4;
    res.s5 = lhs.s5+rhs.s5;
    res.s6 = lhs.s6+rhs.s6;
    res.s7 = lhs.s7+rhs.s7;
    res.s8 = lhs.s8+rhs.s8;
    res.s9 = lhs.s9+rhs.s9;
    res.sA = lhs.sA+rhs.sA;
    res.sB = lhs.sB+rhs.sB;
    res.sC = lhs.sC+rhs.sC;
    res.sD = lhs.sD+rhs.sD;
    res.sE = lhs.sE+rhs.sE;
    res.sF = lhs.sF+rhs.sF;
    return res;
}

float16 operator * (const float16 &lhs, const float &rhs){
    float16 res;
    res.s0 = lhs.s0*rhs;
    res.s1 = lhs.s1*rhs;
    res.s2 = lhs.s2*rhs;
    res.s3 = lhs.s3*rhs;
    res.s4 = lhs.s4*rhs;
    res.s5 = lhs.s5*rhs;
    res.s6 = lhs.s6*rhs;
    res.s7 = lhs.s7*rhs;
    res.s8 = lhs.s8*rhs;
    res.s9 = lhs.s9*rhs;
    res.sA = lhs.sA*rhs;
    res.sB = lhs.sB*rhs;
    res.sC = lhs.sC*rhs;
    res.sD = lhs.sD*rhs;
    res.sE = lhs.sE*rhs;
    res.sF = lhs.sF*rhs;
    return res;
}

float16 operator * (const float &lhs, const float16 &rhs){
    float16 res;
    res.s0 = lhs*rhs.s0;
    res.s1 = lhs*rhs.s1;
    res.s2 = lhs*rhs.s2;
    res.s3 = lhs*rhs.s3;
    res.s4 = lhs*rhs.s4;
    res.s5 = lhs*rhs.s5;
    res.s6 = lhs*rhs.s6;
    res.s7 = lhs*rhs.s7;
    res.s8 = lhs*rhs.s8;
    res.s9 = lhs*rhs.s9;
    res.sA = lhs*rhs.sA;
    res.sB = lhs*rhs.sB;
    res.sC = lhs*rhs.sC;
    res.sD = lhs*rhs.sD;
    res.sE = lhs*rhs.sE;
    res.sF = lhs*rhs.sF;
    return res;
}

float44 operator + (const float44 & lhs, const float44 &rhs) {
	float44 temp;
	temp.c = lhs.c+rhs.c;
	temp.d = lhs.d+rhs.d;
	temp.e = lhs.e+rhs.e;
	temp.f = lhs.f+rhs.f;
	return temp;
}

float4 operator - (const float4 &lhs, const float4 &rhs){
	 float4 res;
	 res.x = lhs.x-rhs.x;
	 res.y = lhs.y-rhs.y;
	 res.z = lhs.z-rhs.z;
	 res.w = lhs.w-rhs.w;
	 return res;

}

float4 operator - (const float4 &lhs){
	  float4 res;
	  res.x = -lhs.x;
	  res.y = -lhs.y;
	  res.z = -lhs.z;
	  res.w = -lhs.w;
	  return res;

}

float44 operator - (const float44 & lhs, const float44 &rhs) {
	float44 temp;
	temp.c = lhs.c-rhs.c;
	temp.d = lhs.d-rhs.d;
	temp.e = lhs.e-rhs.e;
	temp.f = lhs.f-rhs.f;
	return temp;
}

float44 operator - (const float44 & lhs) {
	float44 temp;
	temp.c = -lhs.c;
	temp.d = -lhs.d;
	temp.e = -lhs.e;
	temp.f = -lhs.f;
	return temp;
}

float4 operator * (const float4 &lhs, const float &rhs){
	 float4 res;
	 res.x = lhs.x*rhs;
	 res.y = lhs.y*rhs;
	 res.z = lhs.z*rhs;
	 res.w = lhs.w*rhs;
	 return res;

}

float4 operator * (const float &lhs, const float4 &rhs){
	  float4 res;
	  res.x = lhs*rhs.x;
	  res.y = lhs*rhs.y;
	  res.z = lhs*rhs.z;
	  res.w = lhs*rhs.w;
	  return res;

}

float4 operator * (const float4 &rhs, const float4 &lhs){
	  float4 res;
	  res.x = lhs.x*rhs.x;
	  res.y = lhs.y*rhs.y;
	  res.z = lhs.z*rhs.z;
	  res.w = lhs.w*rhs.w;
	  return res;
}

float44 operator * (const float44 & lhs, const float &rhs) {
	float44 temp;
	temp.c = lhs.c*rhs;
	temp.d = lhs.d*rhs;
	temp.e = lhs.e*rhs;
	temp.f = lhs.f*rhs;
	return temp;
}

float44 operator * (const float & rhs, const float44 &lhs) {
	float44 temp;
	temp.c = lhs.c*rhs;
	temp.d = lhs.d*rhs;
	temp.e = lhs.e*rhs;
	temp.f = lhs.f*rhs;
	return temp;
}

float operator | (const float4 &lhs, const float4 &rhs){
	return	-lhs.x*rhs.x
			-lhs.y*rhs.y
		    -lhs.z*rhs.z
		    +lhs.w*rhs.w;
}

float operator | (const float44 & lhs, const float44 &rhs) {
	float44 m;
	m.c = lhs.c*rhs.c;
	m.d = lhs.d*rhs.d;
	m.e = lhs.e*rhs.e;
	m.f = lhs.f*rhs.f;
	return   m.c.x+m.c.y+m.c.z-m.c.w +
			 m.d.x+m.d.y+m.d.z-m.d.w +
			 m.e.x+m.e.y+m.e.z-m.e.w -
			 m.f.x-m.f.y-m.f.z+m.f.w;
}

float4 operator | (const float4 &lhs, const float44 &rhs){
	return rhs|lhs;
}

float4 operator | (const float44 &lhs, const float4 &rhs){
	float4 output;
	output.x = -lhs.c.x *rhs.x-lhs.c.y *rhs.y-lhs.c.z *rhs.z+lhs.c.w *rhs.w;
	output.y = -lhs.d.x *rhs.x-lhs.d.y *rhs.y-lhs.d.z *rhs.z+lhs.d.w *rhs.w;
	output.z = -lhs.e.x *rhs.x-lhs.e.y *rhs.y-lhs.e.z *rhs.z+lhs.e.w *rhs.w;
	output.w = -lhs.f.x *rhs.x-lhs.f.y *rhs.y-lhs.f.z *rhs.z+lhs.f.w *rhs.w;
	return output;
}

float4 contract1 (const float44 &lhs, const float44 &rhs){
	float4 output;
	output.x = -lhs.c.x *rhs.c.x-lhs.c.y *rhs.c.y-lhs.c.z *rhs.c.z+lhs.c.w *rhs.c.w;
	output.y = -lhs.d.x *rhs.d.x-lhs.d.y *rhs.d.y-lhs.d.z *rhs.d.z+lhs.d.w *rhs.d.w;
	output.z = -lhs.e.x *rhs.e.x-lhs.e.y *rhs.e.y-lhs.e.z *rhs.e.z+lhs.e.w *rhs.e.w;
	output.w = -lhs.f.x *rhs.e.x-lhs.f.y *rhs.e.y-lhs.f.z *rhs.e.z+lhs.f.w *rhs.e.w;
	return output;
}


float44 operator % (const float4 &input1, const float4& input2){
	float44 output;
	output.c.x = input1.x*input2.x;
	output.c.y = input1.x*input2.y;
	output.c.z = input1.x*input2.z;
	output.c.w = input1.x*input2.w;

	output.d.x = input1.y*input2.x;
	output.d.y = input1.y*input2.y;
	output.d.z = input1.y*input2.z;
	output.d.w = input1.y*input2.w;

	output.e.x = input1.z*input2.x;
	output.e.y = input1.z*input2.y;
	output.e.z = input1.z*input2.z;
	output.e.w = input1.z*input2.w;

	output.f.x = input1.w*input2.x;
	output.f.y = input1.w*input2.y;
	output.f.z = input1.w*input2.z;
	output.f.w = input1.w*input2.w;
	return output;
}


float4 operator / (const float4 &lhs, const float &rhs){
    float4 res;
    res.x = lhs.x/rhs;
    res.y = lhs.y/rhs;
    res.z = lhs.z/rhs;
    res.w = lhs.w/rhs;
    return res;

}

float44 operator / (const float44 & lhs, const float &rhs) {
	float44 m;
	m.c = lhs.c/rhs;
	m.d = lhs.d/rhs;
	m.e = lhs.e/rhs;
	m.f = lhs.f/rhs;
	return m;
}

float44 transpose (const float44 &lhs){

	float44 r;

	r = lhs;
	r.c.y = lhs.d.x;
	r.d.x = lhs.c.y;
	r.c.z = lhs.e.x;
	r.e.x = lhs.c.z;
	r.c.w = lhs.f.x;
	r.f.x = lhs.c.w;
	r.d.z = lhs.e.y;
	r.e.y = lhs.d.z;
	r.d.w = lhs.f.y;
	r.f.y = lhs.d.w;
	r.e.w = lhs.f.z;
	r.f.z = lhs.e.w;

	return r;
}


float4 moveindex(const float4 &input){
	float4 output;
	output = -input;
	output.w =  input.w;
	return output;
}

float44 movelastindex(const float44 &input){
	float44 output;
	output.c = -input.c;
	output.c.w =  input.c.w;

	output.d = -input.d;
	output.d.w =  input.d.w;

	output.e = -input.e;
	output.e.w =  input.e.w;

	output.f = -input.f;
	output.f.w =  input.f.w;

	return output;
}

float44 movefirstindex(const float44 &input){
	float44 output;

	output.c = - input.c;
	output.d = - input.d;
	output.e = - input.e;
	output.f =  input.f;

	return output;

}

float44 moveindices(const float44 &input){
	float44 output;

	output.c = input.c;
	output.c.w =  -input.c.w;

	output.d = input.d;
	output.d.w =  -input.d.w;

	output.e = input.e;
	output.e.w =  -input.e.w;

	output.f = -input.f;
	output.f.w =  input.f.w;

	return output;

}
