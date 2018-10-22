/// \file float44.h
#ifndef FLOAT44_H
#define FLOAT44_H

#ifndef CL
#include <CL/cl.hpp>

/// vector of two floats
typedef cl_float2 float2;
/// vector of three floats
typedef cl_float3 float3;
/// vector of four floats
typedef cl_float4 float4;
/// vector of sixteen floats
typedef cl_float16 float16;
/// Vector of two doubles
typedef cl_double2 double2;
#endif

#ifndef F44STRUCTS
#define F44STRUCTS
/// Struct holding four float4, representing a rank 4 tensor (or any 4x4 matrix)
/** Note that the members are named c, d, e, f and not x, y, z, w due to bugs in the brook compiler
 * and because it would be a huge pain to change it, we keep this tradition for the OpenCL version...
 */
typedef struct float44_t {
  /// first element
  float4  c;
  /// second element
  float4  d;
  /// third element
  float4  e;
  /// fourth element
  float4  f;
} float44;

#endif

/// add components of an int (does just the conversion to double)
double addcomponents(int & x);

/// add components of a float (does just the conversion to double)
double addcomponents(float & x);
/// add components of a double (does nothing)
double addcomponents(double & x);
/// add components of a float 2
double addcomponents(float2 & x);
/// add components of a float 3
double addcomponents(float3 & x);
/// add components of a float 4
double addcomponents(float4 & x);
/// add components of a float 16
double addcomponents(float16 & x);
/// add components of a float 44
double addcomponents(float44 & x);
/// add components of a double 2
double addcomponents(double2 & x);

/// build a double2 - replacement for the constructor...
double2 mdouble2(const double x, const double y);

/// build a float2 - replacement for the constructor...
float2 mfloat2(const float x, const float y);

/// build a float4 - replacement for the constructor...
float4 mfloat4(const float x, const float y, const float z, const float w);

/// build a float3 - replacement for the constructor...
float3 mfloat3(const float x, const float y, const float z);

/// Element-wise multiplication, NOT complex multiplication!
float2 operator * (const float2 &lhs, const float2 &rhs);

/// Multiply a float2 with a float
float2 operator * (const float2 &lhs, const float &rhs);
/// Multiply a float2 with a float
float2 operator * (const float &lhs, const float2 &rhs);

/// Element-wise multiplication, NOT complex multiplication!
double2 operator * (const double2 &lhs, const double2 &rhs);

/// Multiply a double2 with a float
double2 operator * (const double2 &lhs, const float &rhs);
/// Multiply a double2 with a float
double2 operator * (const float &lhs, const double2 &rhs);

/// Add two float2
float2 operator + (const float2 &lhs, const float2 &rhs);

/// Add two double2
double2 operator + (const double2 &lhs, const double2 &rhs);

/// Add two float4
float4 operator + (const float4 &lhs, const float4 &rhs);

/// Add two float16
float16 operator + (const float16 &lhs, const float16 &rhs);

/// Multiply a float16 with a float
float16 operator * (const float16 &lhs, const float &rhs);
/// Multiply a float16 with a float
float16 operator * (const float &lhs, const float16 &rhs);

/// Add two float44 (element wise)
float44 operator + (const float44 & lhs, const float44 &rhs);

/// Subtract two float4
float4 operator - (const float4 &lhs, const float4 &rhs);

/// Negate a float4
float4 operator - (const float4 &lhs);

/// Subtract two float44 (element wise)
float44 operator - (const float44 & lhs, const float44 &rhs);

/// Negate a float44 (element wise)
float44 operator - (const float44 &lhs);

/// Multiply a float4 with a float
float4 operator * (const float4 &lhs, const float &rhs);

/// Multiply a float with a float4
float4 operator * (const float &rhs, const float4 &lhs);

/// Multiply two float4 element wise
float4 operator * (const float4 &rhs, const float4 &lhs);

/// Multiply a float44 with a float
float44 operator * (const float44 & lhs, const float &rhs);

/// Multiply a float with a float44
float44 operator * (const float & rhs, const float44 &lhs);

/// Contract two float4 (scalar product)
float operator | (const float4 &lhs, const float4 &rhs);

/// Contract two float44 (both indices)
float operator | (const float44 &lhs, const float44 &rhs);

/// Contract a float4 and float44 (last index of the float44)
float4 operator | (const float4 &lhs, const float44 &rhs);

/// Contract a float44 with a float4 (last index of the float44)
float4 operator | (const float44 &lhs, const float4 &rhs);

/// Contract the respective last indices of two float44
float4 contract1 (const float44 &lhs, const float44 &rhs);

/// Outer product of two float4
float44 operator % (const float4 &lhs, const float4& rhs);

/// Divide a float4 by a float
float4 operator / (const float4 &lhs, const float& rhs);

/// Divide a float44 by a float
float44 operator / (const float44 &lhs, const float& rhs);

/// Transpose a float44
float44 transpose(const float44 &rhs);

/// Move the index of a float4
float4 moveindex(const float4 &rhs);

/// Move the last index of a float44
float44 movelastindex(const float44 &rhs);

/// Move the first index of a float44
float44 movefirstindex(const float44 &rhs);

/// Move both indices of a float44
float44 moveindices(const float44 &rhs);


#endif
