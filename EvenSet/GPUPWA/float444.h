/// \file float444.h
#ifndef FLOAT444_H
#define FLOAT444_H

#ifndef CL
#include <CL/cl.hpp>
#include "float44.h"
#include <string>
#endif

#ifndef F444STRUCTS
#define F444STRUCTS
/// Struct to hold 16 float4, representing a rank 3 tensor (a 4x4x4 matrix)
/** The use of the letters c to f to denote elements (instead of x,y,z,w)
 * was made necessary by a bug in earlier versions of the Brook compiler
 * and now it is too much work to change this....
 */
typedef struct float444_t {
  /// 0-0 element
  float4  cc;
  /// 0-1 element
  float4  cd;
  /// 0-2 element
  float4  ce;
  /// 0-3 element
  float4  cf;
  /// 1-0 element
  float4  dc;
  /// 1-1 element
  float4  dd;
  /// 1-2 element
  float4  de;
  /// 1-3 element
  float4  df;
  /// 2-0 element
  float4  ec;
  /// 2-1 element
  float4  ed;
  /// 2-2 element
  float4  ee;
  /// 2-3 element
  float4  ef;
  /// 3-0 element
  float4  fc;
  /// 3-1 element
  float4  fd;
  /// 3-2 element
  float4  fe;
  /// 3-3 element
  float4  ff;
} float444;

#endif

/// add components of a float 44
double addcomponents(float444 & x);

/// Add two float444
float444 operator + (const float444& lhs, const float444 &rhs);
/// Subtract two float444
float444 operator - (const float444 & lhs, const float444 &rhs);
/// Negate a float444
float444 operator - (const float444 &lhs);

/// Multiply a float444 with a float
float444 operator * (const float444 & lhs, const float &rhs);
/// Multiply a float with a float444
float444 operator * (const float & rhs, const float444 &lhs);


/// Contract two float444 (all indices)
float operator | (const float444 &lhs, const float444 &rhs);

/// Contract a float4 and a float444 (last index of the float444
float44 operator | (const float4 &lhs, const float444 &rhs);
/// Contract a float444 and a float4 (last index of the float444)
float44 operator | (const float444 &lhs, const float4 &rhs);

/// Contract a float444 and a float44 (last two indices of float444)
float4 operator | (const float444 &lhs, const float44 &rhs);
/// Contract a float44 and a float444 (last two indices of the float444)
float4 operator | (const float44 &lhs, const float444 &rhs);

/// Divide a float444 by a float
float444 operator / (const float444 &lhs, const float& rhs);


/// Outer product of float44 and float4
float444 operator % (const float44 &lhs, const float4 &rhs);
/// Outer product of float44 and float4
float444 operator % (const float4 &lhs, const float44 &rhs);

/// Generic transpose of a float444
float444 transpose(const float444 &A, std::string sequence="123");
/// Transpose a float444
float444  transpose_213(const float444 &A);
/// Transpose a float444
float444  transpose_132(const float444 &A);
/// Transpose a float444
float444  transpose_231(const float444 &A);
/// Transpose a float444
float444  transpose_312(const float444 &A);
/// Transpose a float444
float444  transpose_321(const float444 &A);

/// Move all indices of a float444
float444 moveindices(const float444 &rhs);
/// Move the last index of a float444
float444 movelastindex(const float444 &rhs);
/// Move the middle index of a float444
float444 movemiddleindex(const float444 &rhs);
/// Move the first index of a float444
float444 movefirstindex(const float444 &rhs);


#endif
