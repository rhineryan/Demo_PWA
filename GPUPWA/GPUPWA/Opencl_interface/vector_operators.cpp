/*
 * vector_operators.cpp
 *
 *  Created on: Dec 6, 2010
 *      Author: nberger
 */

#include "vector_operators.h"

ostream& operator <<(ostream& os, const cl_float2 p){
	os <<"(" << p.x << ", " << p.y << ")";
	return os;
}

ostream& operator <<(ostream& os, const cl_float4 p){
	os <<"(" << p.x << ", " << p.y << ", " << p.z << ", " << p.w << ")";
	return os;
}

ostream& operator <<(ostream& os, const cl_float16 p){
	os <<"((" << p.s0 << ", " << p.s1 << ", " << p.s2 << ", " << p.s3 << ")," << endl;
	os <<" (" << p.s4 << ", " << p.s5 << ", " << p.s6 << ", " << p.s7 << ")," << endl;
	os <<" (" << p.s8 << ", " << p.s9 << ", " << p.sA << ", " << p.sB << ")," << endl;
	os <<" (" << p.sC << ", " << p.sD << ", " << p.sE << ", " << p.sF << "))";
	return os;
}

ostream& operator <<(ostream& os, const float44 p){
	os <<"((" << p.c.x << ", " << p.c.y << ", " << p.c.z << ", " << p.c.w << ")," << endl;
	os <<" (" << p.d.x << ", " << p.d.y << ", " << p.d.z << ", " << p.d.w << ")," << endl;
	os <<" (" << p.e.x << ", " << p.e.y << ", " << p.e.z << ", " << p.e.w << ")," << endl;
	os <<" (" << p.f.x << ", " << p.f.y << ", " << p.f.z << ", " << p.f.w << "))";
	return os;
}

ostream& operator <<(ostream& os, const float444 p){
	os <<"(((" << p.cc.x << ", " << p.cc.y << ", " << p.cc.z << ", " << p.cc.w << ")," << endl;
	os <<"  (" << p.cd.x << ", " << p.cd.y << ", " << p.cd.z << ", " << p.cd.w << ")," << endl;
	os <<"  (" << p.ce.x << ", " << p.ce.y << ", " << p.ce.z << ", " << p.ce.w << ")," << endl;
	os <<"  (" << p.cf.x << ", " << p.cf.y << ", " << p.cf.z << ", " << p.cf.w << "))" << endl;

	os <<" ((" << p.dc.x << ", " << p.dc.y << ", " << p.dc.z << ", " << p.dc.w << ")," << endl;
	os <<"  (" << p.dd.x << ", " << p.dd.y << ", " << p.dd.z << ", " << p.dd.w << ")," << endl;
	os <<"  (" << p.de.x << ", " << p.de.y << ", " << p.de.z << ", " << p.de.w << ")," << endl;
	os <<"  (" << p.df.x << ", " << p.df.y << ", " << p.df.z << ", " << p.df.w << "))" << endl;

	os <<" ((" << p.ec.x << ", " << p.ec.y << ", " << p.ec.z << ", " << p.ec.w << ")," << endl;
	os <<"  (" << p.ed.x << ", " << p.ed.y << ", " << p.ed.z << ", " << p.ed.w << ")," << endl;
	os <<"  (" << p.ee.x << ", " << p.ee.y << ", " << p.ee.z << ", " << p.ee.w << ")," << endl;
	os <<"  (" << p.ef.x << ", " << p.ef.y << ", " << p.ef.z << ", " << p.ef.w << "))" << endl;

	os <<" ((" << p.fc.x << ", " << p.fc.y << ", " << p.fc.z << ", " << p.fc.w << ")," << endl;
	os <<"  (" << p.fd.x << ", " << p.fd.y << ", " << p.fd.z << ", " << p.fd.w << ")," << endl;
	os <<"  (" << p.fe.x << ", " << p.fe.y << ", " << p.fe.z << ", " << p.fe.w << ")," << endl;
	os <<"  (" << p.ff.x << ", " << p.ff.y << ", " << p.ff.z << ", " << p.ff.w << ")))" << endl;

	return os;
}


ostream& operator <<(ostream& os, const cl_double2 p){
	os <<"(" << p.x << ", " << p.y << ")";
	return os;
}

cl_float add (cl_float & lhs,  cl_float & rhs){
	cl_float res;
	res = lhs + rhs;
	return res;
}

cl_float2 add (cl_float2 & lhs,  cl_float2 & rhs){
	cl_float2 res;
	res.x = lhs.x + rhs.x;
	res.y = lhs.y + rhs.y;
	return res;
}

cl_float4 add (cl_float4 & lhs,  cl_float4 & rhs){
	cl_float4 res;
	res.x = lhs.x + rhs.x;
	res.y = lhs.y + rhs.y;
	res.z = lhs.z + rhs.z;
	res.w = lhs.w + rhs.w;
	return res;
}

cl_float16 add (cl_float16 & lhs,  cl_float16 & rhs){
	cl_float16 res;
	res.s0 = lhs.s0 + rhs.s0;
	res.s1 = lhs.s1 + rhs.s1;
	res.s2 = lhs.s2 + rhs.s2;
	res.s3 = lhs.s3 + rhs.s3;
	res.s4 = lhs.s4 + rhs.s4;
	res.s5 = lhs.s5 + rhs.s5;
	res.s6 = lhs.s6 + rhs.s6;
	res.s7 = lhs.s7 + rhs.s7;
	res.s8 = lhs.s8 + rhs.s8;
	res.s9 = lhs.s9 + rhs.s9;
	res.sA = lhs.sA + rhs.sA;
	res.sB = lhs.sB + rhs.sB;
	res.sC = lhs.sC + rhs.sC;
	res.sD = lhs.sD + rhs.sD;
	res.sE = lhs.sE + rhs.sE;
	res.sF = lhs.sF + rhs.sF;
	return res;
}

cl_double add (cl_double & lhs,  cl_double & rhs){
	cl_double res;
	res = lhs + rhs;
	return res;
}

cl_double2 add (cl_double2 & lhs,  cl_double2 & rhs){
	cl_double2 res;
	res.x = lhs.x + rhs.x;
	res.y = lhs.y + rhs.y;
	return res;
}
