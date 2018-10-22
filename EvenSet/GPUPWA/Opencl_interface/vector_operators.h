/*
 * vector_operators.h
 *
 *  Created on: Aug 19, 2010
 *      Author: nberger
 */

#ifndef VECTOR_OPERATORS_H_
#define VECTOR_OPERATORS_H_

#include<iostream>
#include<CL/cl.hpp>
#include "../float44.h"
#include "../float444.h"

using namespace std;

ostream& operator <<(ostream& os, const cl_float2 p);

ostream& operator <<(ostream& os, const cl_float4 p);

ostream& operator <<(ostream& os, const cl_float16 p);

ostream& operator <<(ostream& os, const float44 p);

ostream& operator <<(ostream& os, const float444 p);


ostream& operator <<(ostream& os, const cl_double2 p);

cl_float add (cl_float & lhs,  cl_float & rhs);

cl_float2 add (cl_float2 & lhs,  cl_float2 & rhs);

cl_float4 add (cl_float4 & lhs,  cl_float4 & rhs);

cl_float16 add (cl_float16 & lhs,  cl_float16 & rhs);

cl_double add (cl_double & lhs,  cl_double & rhs);

cl_double2 add (cl_double2 & lhs,  cl_double2 & rhs);

#endif /* STREAMING_H_ */
