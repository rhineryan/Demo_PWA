/// \file float4444.h
#ifndef FLOAT4444_H
#define FLOAT4444_H

#include <CL/cl.hpp>
#include "float44.h"
#include <string>
#include "float444.h"
#include <iostream>


#include <cassert>

using namespace std;

/// A 4x4x4x4 matrix representing rank4 tensors
/** Implemented as a collection of sixteen 4x4 matrices. This implementation was chosen because the
 * number of in- and outputs to Brook kernels is limited and this allows for a straightforward splitting
 * of kernel tasks. It also makes sense in the OpenCL days...
 */
class float4444 {

public:
  /*
  float4444(){
    cout << "Constructor called" << endl;
    m = new float44[16];
    cout << "New done!" << endl;
    //  for(int i =0; i < 16; i++)
    //  m[i] = *new float44;
  };

  float4444(const float4444& x){
    cout << "Copy Constructor called" << endl;
    //m = new float44[16];
    //for(int i =0; i < 16; i++)
    //  m[i] = *new float44;
    for(int i =0; i < 16; i++) m[i] = x[i];
  };

  //~float4444(){delete[] m;};

  float4444& operator=(const float4444& rhs){
    cout << "Assignment Constructor called" << endl;
    if(this != &rhs){
      for(int i =0; i < 16; i++) m[i] = rhs[i];
    }
      return *this;
    
      };*/
    


	/// Access the xx element
	float44 &  xx(){return m[0];};
	/// Access the xy element
	float44 &  xy(){return m[1];};
	/// Access the xz element
	float44 &  xz(){return m[2];};
	/// Access the xw element
	float44 &  xw(){return m[3];};

	/// Access the yx element
	float44 &  yx(){return m[4];};
	/// Access the yy element
	float44 &  yy(){return m[5];};
	/// Access the yz element
	float44 &  yz(){return m[6];};
	/// Access the yw element
	float44 &  yw(){return m[7];};

	/// Access the zx element
	float44 &  zx(){return m[8];};
	/// Access the zy element
	float44 &  zy(){return m[9];};
	/// Access the zz element
	float44 &  zz(){return m[10];};
	/// Access the zw element
	float44 &  zw(){return m[11];};

	/// Access the wx element
	float44 &  wx(){return m[12];};
	/// Access the wy element
	float44 &  wy(){return m[13];};
	/// Access the wz element
	float44 &  wz(){return m[14];};
	/// Access the ww element
	float44 &  ww(){return m[15];};

	/// Get a float444 block (pick the first index 0-3)
	float444 block(int i) const{
		float444 output;
		output.cc = (*this)(i,0).c;
		output.cd = (*this)(i,0).d;
		output.ce = (*this)(i,0).e;
		output.cf = (*this)(i,0).f;

		output.dc = (*this)(i,1).c;
		output.dd = (*this)(i,1).d;
		output.de = (*this)(i,1).e;
		output.df = (*this)(i,1).f;

		output.ec = (*this)(i,2).c;
		output.ed = (*this)(i,2).d;
		output.ee = (*this)(i,2).e;
		output.ef = (*this)(i,2).f;

		output.fc = (*this)(i,3).c;
		output.fd = (*this)(i,3).d;
		output.fe = (*this)(i,3).e;
		output.ff = (*this)(i,3).f;

		return output;
	}
	/// Access one of the 16 float44 elements
	const float44 & operator[](int index) const {
		assert(index < 16);
		return m[index];
	}
	/// Access one of the 16 float44 elements
	float44 & operator[](int index) {
		assert(index < 16);
		return m[index];
	}
	/// Access one of the 16 float44 elements
	const float44 & operator()(int index) const {
		assert(index < 16);
		return m[index];
	}
	/// Access one of the 16 float44 elements
	float44 & operator()(int index)  {
		assert(index < 16);
		return m[index];
	}
	/// Access one of the 16 float44 elements by using two indices
	const float44 & operator()(int i1, int i2) const {
		assert(i1 < 4);
		assert(i2 < 4);
		return m[i1*4+i2];
	}
	/// Access one of the 16 float44 elements by using two indices
	float44 & operator()(int i1, int i2) {
		assert(i1 < 4);
		assert(i2 < 4);
		return m[i1*4+i2];
	}

protected:
	/// Array of float44 containing the data
	float44   m[16];

};

/// Add two float4444
float4444 operator + (const float4444& lhs, const float4444 &rhs);
/// Subtract two float4444
float4444 operator - (const float4444 & lhs, const float4444 &rhs);
/// Negate a float4444
float4444 operator - (const float4444 &lhs);

/// Multiply a float4444 with a float
float4444 operator * (const float4444 & lhs, const float &rhs);
/// Multiply a float with a float4444
float4444 operator * (const float & rhs, const float4444 &lhs);


///outer product of float44 and float44
float4444 operator %(const float44 &lhs, const float44 &rhs);

///outer product of float444 and float4
float4444 operator %(const float444 &lhs, const float4 &rhs);
///outer product of float4 and float444
float4444 operator %(const float4 &lhs, const float444 &rhs);


/// contraction of const rank 4 tensor and const vector, output is rank 3 tensor
float444 operator | (const float4 &lhs, const float4444 &rhs);
/// contraction of const rank 4 tensor and const vector, output is rank 3 tensor
float444 operator | (const float4444 &lhs, const float4 &rhs);


/// contraction of const rank 4 tensor and const rank 2 tensor, output is rank 2 tensor
float44 operator | (const float4444 &lhs, const float44 &rhs);
/// contraction of const rank 4 tensor and const rank 2 tensor, output is rank 2 tensor
float44 operator | (const float44 &lhs, const float4444 &rhs);

/// contraction of const rank 4 tensor and const rank 3 tensor, output is vector
float4 operator | (const float4444 &lhs, const float444 &rhs);
/// contraction of const rank 4 tensor and const rank 3 tensor, output is vector
float4 operator | (const float444 &lhs, const float4444 &rhs);

/// contraction of const rank 4 tensor and const rank 4 tensor, output is float
float operator | (const float4444 &lhs, const float4444 &rhs);

/// contraction of one index of a const rank 4 tensor and a const rank two tensor, output is a rank 4 tensor
float4444 operator|| (const float4444 &lhs, const float44 &rhs);
/// contraction of one index of a const rank 2 tensor and a const rank 4 tensor, output is a rank 4 tensor
float4444 operator|| (const float44 &lhs, const float4444 &rhs);

// 23 transpose of float4444
/// Transpose a float4444
float4444  transpose_4123(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_1423(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_1243(const float4444 & lhs);

/// Transpose a float4444
float4444  transpose_4213(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_2413(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_2143(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_2134(const float4444 & lhs);

/// Transpose a float4444
float4444  transpose_4132(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_1432(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_1342(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_1324(const float4444 & lhs);

/// Transpose a float4444
float4444  transpose_4231(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_2431(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_2341(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_2314(const float4444 & lhs);

/// Transpose a float4444
float4444  transpose_4312(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_3412(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_3142(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_3124(const float4444 & lhs);

/// Transpose a float4444
float4444  transpose_4321(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_3421(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_3241(const float4444 & lhs);
/// Transpose a float4444
float4444  transpose_3214(const float4444 & lhs);


/// contraction of the last two indices of const rank 4 tensor and const rank 4 tensor, output is rank 4 tensor
float4444 contract2 (const float4444 &lhs, const float4444 &rhs);

/// contraction of the last three indices of const rank 4 tensor and const rank 4 tensor, output is rank 4 tensor
float44 contract3 (const float4444 &lhs, const float4444 &rhs);

/// Divide a float4444 by a float
float4444 operator / (const float4444 &lhs, const float& rhs);

/// Move all indices of a float4444
float4444 moveindices(const float4444 &input);
/// Move the last index of a float4444
float4444 movelastindex(const float4444 &input);
#endif
