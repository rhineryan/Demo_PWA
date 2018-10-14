


#include "float4444.h"


float4444 operator + (const float4444& lhs, const float4444 &rhs){

	float4444 r;

	for(int i=0; i < 16; i++){
		r[i] =lhs[i]+rhs[i];
	}
	return r;
}


float4444 operator - (const float4444 & lhs, const float4444 &rhs){

    float4444 r;

    for(int i=0; i < 16; i++){
    	r[i] =lhs[i]-rhs[i];
    }
	return r;
}



float4444 operator * (const float & lhs, const float4444 &rhs){

    float4444 r;
    for(int i=0; i < 16; i++){
       	r[i] =lhs * rhs[i];
    }
	return r;
}


float4444 operator * (const float4444 & lhs, const float &rhs){

  return(rhs*lhs) ;
}


float4444 operator - (const float4444 &rhs){
  float4444 r;
  for(int i=0; i < 16; i++){
    r[i] =-rhs[i];
  }
  return r;
}


float4444 operator / (const float4444 &lhs, const float& rhs){

  float4444 r;
  for(int i=0; i < 16; i++){
    r[i] =lhs[i]/rhs;
  }
  return r;
}


///outer product of rank2 const and rank2 const
float4444 operator %(const float44 &input1, const float44 &input2){

   float4444 output;
   output(0,0).c.x = input1.c.x*input2.c.x;
   output(0,0).c.y = input1.c.x*input2.c.y;
   output(0,0).c.z = input1.c.x*input2.c.z;
   output(0,0).c.w = input1.c.x*input2.c.w;
   output(0,0).d.x = input1.c.x*input2.d.x;
   output(0,0).d.y = input1.c.x*input2.d.y;
   output(0,0).d.z = input1.c.x*input2.d.z;
   output(0,0).d.w = input1.c.x*input2.d.w;
   output(0,0).e.x = input1.c.x*input2.e.x;
   output(0,0).e.y = input1.c.x*input2.e.y;
   output(0,0).e.z = input1.c.x*input2.e.z;
   output(0,0).e.w = input1.c.x*input2.e.w;
   output(0,0).f.x = input1.c.x*input2.f.x;
   output(0,0).f.y = input1.c.x*input2.f.y;
   output(0,0).f.z = input1.c.x*input2.f.z;
   output(0,0).f.w = input1.c.x*input2.f.w;

   output(0,1).c.x = input1.c.y*input2.c.x;
   output(0,1).c.y = input1.c.y*input2.c.y;
   output(0,1).c.z = input1.c.y*input2.c.z;
   output(0,1).c.w = input1.c.y*input2.c.w;
   output(0,1).d.x = input1.c.y*input2.d.x;
   output(0,1).d.y = input1.c.y*input2.d.y;
   output(0,1).d.z = input1.c.y*input2.d.z;
   output(0,1).d.w = input1.c.y*input2.d.w;
   output(0,1).e.x = input1.c.y*input2.e.x;
   output(0,1).e.y = input1.c.y*input2.e.y;
   output(0,1).e.z = input1.c.y*input2.e.z;
   output(0,1).e.w = input1.c.y*input2.e.w;
   output(0,1).f.x = input1.c.y*input2.f.x;
   output(0,1).f.y = input1.c.y*input2.f.y;
   output(0,1).f.z = input1.c.y*input2.f.z;
   output(0,1).f.w = input1.c.y*input2.f.w;

   output(0,2).c.x = input1.c.z*input2.c.x;
   output(0,2).c.y = input1.c.z*input2.c.y;
   output(0,2).c.z = input1.c.z*input2.c.z;
   output(0,2).c.w = input1.c.z*input2.c.w;
   output(0,2).d.x = input1.c.z*input2.d.x;
   output(0,2).d.y = input1.c.z*input2.d.y;
   output(0,2).d.z = input1.c.z*input2.d.z;
   output(0,2).d.w = input1.c.z*input2.d.w;
   output(0,2).e.x = input1.c.z*input2.e.x;
   output(0,2).e.y = input1.c.z*input2.e.y;
   output(0,2).e.z = input1.c.z*input2.e.z;
   output(0,2).e.w = input1.c.z*input2.e.w;
   output(0,2).f.x = input1.c.z*input2.f.x;
   output(0,2).f.y = input1.c.z*input2.f.y;
   output(0,2).f.z = input1.c.z*input2.f.z;
   output(0,2).f.w = input1.c.z*input2.f.w;

   output(0,3).c.x = input1.c.w*input2.c.x;
   output(0,3).c.y = input1.c.w*input2.c.y;
   output(0,3).c.z = input1.c.w*input2.c.z;
   output(0,3).c.w = input1.c.w*input2.c.w;
   output(0,3).d.x = input1.c.w*input2.d.x;
   output(0,3).d.y = input1.c.w*input2.d.y;
   output(0,3).d.z = input1.c.w*input2.d.z;
   output(0,3).d.w = input1.c.w*input2.d.w;
   output(0,3).e.x = input1.c.w*input2.e.x;
   output(0,3).e.y = input1.c.w*input2.e.y;
   output(0,3).e.z = input1.c.w*input2.e.z;
   output(0,3).e.w = input1.c.w*input2.e.w;
   output(0,3).f.x = input1.c.w*input2.f.x;
   output(0,3).f.y = input1.c.w*input2.f.y;
   output(0,3).f.z = input1.c.w*input2.f.z;
   output(0,3).f.w = input1.c.w*input2.f.w;

   output(1,0).c.x = input1.d.x*input2.c.x;
   output(1,0).c.y = input1.d.x*input2.c.y;
   output(1,0).c.z = input1.d.x*input2.c.z;
   output(1,0).c.w = input1.d.x*input2.c.w;
   output(1,0).d.x = input1.d.x*input2.d.x;
   output(1,0).d.y = input1.d.x*input2.d.y;
   output(1,0).d.z = input1.d.x*input2.d.z;
   output(1,0).d.w = input1.d.x*input2.d.w;
   output(1,0).e.x = input1.d.x*input2.e.x;
   output(1,0).e.y = input1.d.x*input2.e.y;
   output(1,0).e.z = input1.d.x*input2.e.z;
   output(1,0).e.w = input1.d.x*input2.e.w;
   output(1,0).f.x = input1.d.x*input2.f.x;
   output(1,0).f.y = input1.d.x*input2.f.y;
   output(1,0).f.z = input1.d.x*input2.f.z;
   output(1,0).f.w = input1.d.x*input2.f.w;

   output(1,1).c.x = input1.d.y*input2.c.x;
   output(1,1).c.y = input1.d.y*input2.c.y;
   output(1,1).c.z = input1.d.y*input2.c.z;
   output(1,1).c.w = input1.d.y*input2.c.w;
   output(1,1).d.x = input1.d.y*input2.d.x;
   output(1,1).d.y = input1.d.y*input2.d.y;
   output(1,1).d.z = input1.d.y*input2.d.z;
   output(1,1).d.w = input1.d.y*input2.d.w;
   output(1,1).e.x = input1.d.y*input2.e.x;
   output(1,1).e.y = input1.d.y*input2.e.y;
   output(1,1).e.z = input1.d.y*input2.e.z;
   output(1,1).e.w = input1.d.y*input2.e.w;
   output(1,1).f.x = input1.d.y*input2.f.x;
   output(1,1).f.y = input1.d.y*input2.f.y;
   output(1,1).f.z = input1.d.y*input2.f.z;
   output(1,1).f.w = input1.d.y*input2.f.w;

   output(1,2).c.x = input1.d.z*input2.c.x;
   output(1,2).c.y = input1.d.z*input2.c.y;
   output(1,2).c.z = input1.d.z*input2.c.z;
   output(1,2).c.w = input1.d.z*input2.c.w;
   output(1,2).d.x = input1.d.z*input2.d.x;
   output(1,2).d.y = input1.d.z*input2.d.y;
   output(1,2).d.z = input1.d.z*input2.d.z;
   output(1,2).d.w = input1.d.z*input2.d.w;
   output(1,2).e.x = input1.d.z*input2.e.x;
   output(1,2).e.y = input1.d.z*input2.e.y;
   output(1,2).e.z = input1.d.z*input2.e.z;
   output(1,2).e.w = input1.d.z*input2.e.w;
   output(1,2).f.x = input1.d.z*input2.f.x;
   output(1,2).f.y = input1.d.z*input2.f.y;
   output(1,2).f.z = input1.d.z*input2.f.z;
   output(1,2).f.w = input1.d.z*input2.f.w;

   output(1,3).c.x = input1.d.w*input2.c.x;
   output(1,3).c.y = input1.d.w*input2.c.y;
   output(1,3).c.z = input1.d.w*input2.c.z;
   output(1,3).c.w = input1.d.w*input2.c.w;
   output(1,3).d.x = input1.d.w*input2.d.x;
   output(1,3).d.y = input1.d.w*input2.d.y;
   output(1,3).d.z = input1.d.w*input2.d.z;
   output(1,3).d.w = input1.d.w*input2.d.w;
   output(1,3).e.x = input1.d.w*input2.e.x;
   output(1,3).e.y = input1.d.w*input2.e.y;
   output(1,3).e.z = input1.d.w*input2.e.z;
   output(1,3).e.w = input1.d.w*input2.e.w;
   output(1,3).f.x = input1.d.w*input2.f.x;
   output(1,3).f.y = input1.d.w*input2.f.y;
   output(1,3).f.z = input1.d.w*input2.f.z;
   output(1,3).f.w = input1.d.w*input2.f.w;

   output(2,0).c.x = input1.e.x*input2.c.x;
   output(2,0).c.y = input1.e.x*input2.c.y;
   output(2,0).c.z = input1.e.x*input2.c.z;
   output(2,0).c.w = input1.e.x*input2.c.w;
   output(2,0).d.x = input1.e.x*input2.d.x;
   output(2,0).d.y = input1.e.x*input2.d.y;
   output(2,0).d.z = input1.e.x*input2.d.z;
   output(2,0).d.w = input1.e.x*input2.d.w;
   output(2,0).e.x = input1.e.x*input2.e.x;
   output(2,0).e.y = input1.e.x*input2.e.y;
   output(2,0).e.z = input1.e.x*input2.e.z;
   output(2,0).e.w = input1.e.x*input2.e.w;
   output(2,0).f.x = input1.e.x*input2.f.x;
   output(2,0).f.y = input1.e.x*input2.f.y;
   output(2,0).f.z = input1.e.x*input2.f.z;
   output(2,0).f.w = input1.e.x*input2.f.w;

   output(2,1).c.x = input1.e.y*input2.c.x;
   output(2,1).c.y = input1.e.y*input2.c.y;
   output(2,1).c.z = input1.e.y*input2.c.z;
   output(2,1).c.w = input1.e.y*input2.c.w;
   output(2,1).d.x = input1.e.y*input2.d.x;
   output(2,1).d.y = input1.e.y*input2.d.y;
   output(2,1).d.z = input1.e.y*input2.d.z;
   output(2,1).d.w = input1.e.y*input2.d.w;
   output(2,1).e.x = input1.e.y*input2.e.x;
   output(2,1).e.y = input1.e.y*input2.e.y;
   output(2,1).e.z = input1.e.y*input2.e.z;
   output(2,1).e.w = input1.e.y*input2.e.w;
   output(2,1).f.x = input1.e.y*input2.f.x;
   output(2,1).f.y = input1.e.y*input2.f.y;
   output(2,1).f.z = input1.e.y*input2.f.z;
   output(2,1).f.w = input1.e.y*input2.f.w;

   output(2,2).c.x = input1.e.z*input2.c.x;
   output(2,2).c.y = input1.e.z*input2.c.y;
   output(2,2).c.z = input1.e.z*input2.c.z;
   output(2,2).c.w = input1.e.z*input2.c.w;
   output(2,2).d.x = input1.e.z*input2.d.x;
   output(2,2).d.y = input1.e.z*input2.d.y;
   output(2,2).d.z = input1.e.z*input2.d.z;
   output(2,2).d.w = input1.e.z*input2.d.w;
   output(2,2).e.x = input1.e.z*input2.e.x;
   output(2,2).e.y = input1.e.z*input2.e.y;
   output(2,2).e.z = input1.e.z*input2.e.z;
   output(2,2).e.w = input1.e.z*input2.e.w;
   output(2,2).f.x = input1.e.z*input2.f.x;
   output(2,2).f.y = input1.e.z*input2.f.y;
   output(2,2).f.z = input1.e.z*input2.f.z;
   output(2,2).f.w = input1.e.z*input2.f.w;

   output(2,3).c.x = input1.e.w*input2.c.x;
   output(2,3).c.y = input1.e.w*input2.c.y;
   output(2,3).c.z = input1.e.w*input2.c.z;
   output(2,3).c.w = input1.e.w*input2.c.w;
   output(2,3).d.x = input1.e.w*input2.d.x;
   output(2,3).d.y = input1.e.w*input2.d.y;
   output(2,3).d.z = input1.e.w*input2.d.z;
   output(2,3).d.w = input1.e.w*input2.d.w;
   output(2,3).e.x = input1.e.w*input2.e.x;
   output(2,3).e.y = input1.e.w*input2.e.y;
   output(2,3).e.z = input1.e.w*input2.e.z;
   output(2,3).e.w = input1.e.w*input2.e.w;
   output(2,3).f.x = input1.e.w*input2.f.x;
   output(2,3).f.y = input1.e.w*input2.f.y;
   output(2,3).f.z = input1.e.w*input2.f.z;
   output(2,3).f.w = input1.e.w*input2.f.w;

   output(3,0).c.x = input1.f.x*input2.c.x;
   output(3,0).c.y = input1.f.x*input2.c.y;
   output(3,0).c.z = input1.f.x*input2.c.z;
   output(3,0).c.w = input1.f.x*input2.c.w;
   output(3,0).d.x = input1.f.x*input2.d.x;
   output(3,0).d.y = input1.f.x*input2.d.y;
   output(3,0).d.z = input1.f.x*input2.d.z;
   output(3,0).d.w = input1.f.x*input2.d.w;
   output(3,0).e.x = input1.f.x*input2.e.x;
   output(3,0).e.y = input1.f.x*input2.e.y;
   output(3,0).e.z = input1.f.x*input2.e.z;
   output(3,0).e.w = input1.f.x*input2.e.w;
   output(3,0).f.x = input1.f.x*input2.f.x;
   output(3,0).f.y = input1.f.x*input2.f.y;
   output(3,0).f.z = input1.f.x*input2.f.z;
   output(3,0).f.w = input1.f.x*input2.f.w;

   output(3,1).c.x = input1.f.y*input2.c.x;
   output(3,1).c.y = input1.f.y*input2.c.y;
   output(3,1).c.z = input1.f.y*input2.c.z;
   output(3,1).c.w = input1.f.y*input2.c.w;
   output(3,1).d.x = input1.f.y*input2.d.x;
   output(3,1).d.y = input1.f.y*input2.d.y;
   output(3,1).d.z = input1.f.y*input2.d.z;
   output(3,1).d.w = input1.f.y*input2.d.w;
   output(3,1).e.x = input1.f.y*input2.e.x;
   output(3,1).e.y = input1.f.y*input2.e.y;
   output(3,1).e.z = input1.f.y*input2.e.z;
   output(3,1).e.w = input1.f.y*input2.e.w;
   output(3,1).f.x = input1.f.y*input2.f.x;
   output(3,1).f.y = input1.f.y*input2.f.y;
   output(3,1).f.z = input1.f.y*input2.f.z;
   output(3,1).f.w = input1.f.y*input2.f.w;

   output(3,2).c.x = input1.f.z*input2.c.x;
   output(3,2).c.y = input1.f.z*input2.c.y;
   output(3,2).c.z = input1.f.z*input2.c.z;
   output(3,2).c.w = input1.f.z*input2.c.w;
   output(3,2).d.x = input1.f.z*input2.d.x;
   output(3,2).d.y = input1.f.z*input2.d.y;
   output(3,2).d.z = input1.f.z*input2.d.z;
   output(3,2).d.w = input1.f.z*input2.d.w;
   output(3,2).e.x = input1.f.z*input2.e.x;
   output(3,2).e.y = input1.f.z*input2.e.y;
   output(3,2).e.z = input1.f.z*input2.e.z;
   output(3,2).e.w = input1.f.z*input2.e.w;
   output(3,2).f.x = input1.f.z*input2.f.x;
   output(3,2).f.y = input1.f.z*input2.f.y;
   output(3,2).f.z = input1.f.z*input2.f.z;
   output(3,2).f.w = input1.f.z*input2.f.w;

   output(3,3).c.x = input1.f.w*input2.c.x;
   output(3,3).c.y = input1.f.w*input2.c.y;
   output(3,3).c.z = input1.f.w*input2.c.z;
   output(3,3).c.w = input1.f.w*input2.c.w;
   output(3,3).d.x = input1.f.w*input2.d.x;
   output(3,3).d.y = input1.f.w*input2.d.y;
   output(3,3).d.z = input1.f.w*input2.d.z;
   output(3,3).d.w = input1.f.w*input2.d.w;
   output(3,3).e.x = input1.f.w*input2.e.x;
   output(3,3).e.y = input1.f.w*input2.e.y;
   output(3,3).e.z = input1.f.w*input2.e.z;
   output(3,3).e.w = input1.f.w*input2.e.w;
   output(3,3).f.x = input1.f.w*input2.f.x;
   output(3,3).f.y = input1.f.w*input2.f.y;
   output(3,3).f.z = input1.f.w*input2.f.z;
   output(3,3).f.w = input1.f.w*input2.f.w;

   return output;
}

///outer product of vector const and rank3 const
float4444 operator %(const float4 &input1, const float444 &input2){
	float4444 output;
	output(0,0).c = input1.x*input2.cc;
	output(0,0).d = input1.x*input2.cd;
	output(0,0).e = input1.x*input2.ce;
	output(0,0).f = input1.x*input2.cf;

	output(0,1).c = input1.x*input2.dc;
	output(0,1).d = input1.x*input2.dd;
	output(0,1).e = input1.x*input2.de;
	output(0,1).f = input1.x*input2.df;

	output(0,2).c = input1.x*input2.ec;
	output(0,2).d = input1.x*input2.ed;
	output(0,2).e = input1.x*input2.ee;
	output(0,2).f = input1.x*input2.ef;

	output(0,3).c = input1.x*input2.fc;
	output(0,3).d = input1.x*input2.fd;
	output(0,3).e = input1.x*input2.fe;
	output(0,3).f = input1.x*input2.ff;

	output(1,0).c = input1.y*input2.cc;
	output(1,0).d = input1.y*input2.cd;
	output(1,0).e = input1.y*input2.ce;
	output(1,0).f = input1.y*input2.cf;

	output(1,1).c = input1.y*input2.dc;
	output(1,1).d = input1.y*input2.dd;
	output(1,1).e = input1.y*input2.de;
	output(1,1).f = input1.y*input2.df;

	output(1,2).c = input1.y*input2.ec;
	output(1,2).d = input1.y*input2.ed;
	output(1,2).e = input1.y*input2.ee;
	output(1,2).f = input1.y*input2.ef;

	output(1,3).c = input1.y*input2.fc;
	output(1,3).d = input1.y*input2.fd;
	output(1,3).e = input1.y*input2.fe;
	output(1,3).f = input1.y*input2.ff;

	output(2,0).c = input1.z*input2.cc;
	output(2,0).d = input1.z*input2.cd;
	output(2,0).e = input1.z*input2.ce;
	output(2,0).f = input1.z*input2.cf;

	output(2,1).c = input1.z*input2.dc;
	output(2,1).d = input1.z*input2.dd;
	output(2,1).e = input1.z*input2.de;
	output(2,1).f = input1.z*input2.df;

	output(2,2).c = input1.z*input2.ec;
	output(2,2).d = input1.z*input2.ed;
	output(2,2).e = input1.z*input2.ee;
	output(2,2).f = input1.z*input2.ef;

	output(2,3).c = input1.z*input2.fc;
	output(2,3).d = input1.z*input2.fd;
	output(2,3).e = input1.z*input2.fe;
	output(2,3).f = input1.z*input2.ff;

	output(3,0).c = input1.w*input2.cc;
	output(3,0).d = input1.w*input2.cd;
	output(3,0).e = input1.w*input2.ce;
	output(3,0).f = input1.w*input2.cf;

	output(3,1).c = input1.w*input2.dc;
	output(3,1).d = input1.w*input2.dd;
	output(3,1).e = input1.w*input2.de;
	output(3,1).f = input1.w*input2.df;

	output(3,2).c = input1.w*input2.ec;
	output(3,2).d = input1.w*input2.ed;
	output(3,2).e = input1.w*input2.ee;
	output(3,2).f = input1.w*input2.ef;

	output(3,3).c = input1.w*input2.fc;
	output(3,3).d = input1.w*input2.fd;
	output(3,3).e = input1.w*input2.fe;
	output(3,3).f = input1.w*input2.ff;
	return output;
}

///outer product of vector const and rank3 const
float4444 operator %(const float444 &input1, const float4 &input2){
	float4444 output;
	output(0,0).c = input1.cc.x*input2;
	output(0,0).d = input1.cc.y*input2;
	output(0,0).e = input1.cc.z*input2;
	output(0,0).f = input1.cc.w*input2;

	output(0,1).c = input1.cd.x*input2;
	output(0,1).d = input1.cd.y*input2;
	output(0,1).e = input1.cd.z*input2;
	output(0,1).f = input1.cd.w*input2;

	output(0,2).c = input1.ce.x*input2;
	output(0,2).d = input1.ce.y*input2;
	output(0,2).e = input1.ce.z*input2;
	output(0,2).f = input1.ce.w*input2;

	output(0,3).c = input1.cf.x*input2;
	output(0,3).d = input1.cf.y*input2;
	output(0,3).e = input1.cf.z*input2;
	output(0,3).f = input1.cf.w*input2;

	output(1,0).c = input1.dc.x*input2;
	output(1,0).d = input1.dc.y*input2;
	output(1,0).e = input1.dc.z*input2;
	output(1,0).f = input1.dc.w*input2;

	output(1,1).c = input1.dd.x*input2;
	output(1,1).d = input1.dd.y*input2;
	output(1,1).e = input1.dd.z*input2;
	output(1,1).f = input1.dd.w*input2;

	output(1,2).c = input1.de.x*input2;
	output(1,2).d = input1.de.y*input2;
	output(1,2).e = input1.de.z*input2;
	output(1,2).f = input1.de.w*input2;

	output(1,3).c = input1.df.x*input2;
	output(1,3).d = input1.df.y*input2;
	output(1,3).e = input1.df.z*input2;
	output(1,3).f = input1.df.w*input2;

	output(2,0).c = input1.ec.x*input2;
	output(2,0).d = input1.ec.y*input2;
	output(2,0).e = input1.ec.z*input2;
	output(2,0).f = input1.ec.w*input2;

	output(2,1).c = input1.ed.x*input2;
	output(2,1).d = input1.ed.y*input2;
	output(2,1).e = input1.ed.z*input2;
	output(2,1).f = input1.ed.w*input2;

	output(2,2).c = input1.ee.x*input2;
	output(2,2).d = input1.ee.y*input2;
	output(2,2).e = input1.ee.z*input2;
	output(2,2).f = input1.ee.w*input2;

	output(2,3).c = input1.ef.x*input2;
	output(2,3).d = input1.ef.y*input2;
	output(2,3).e = input1.ef.z*input2;
	output(2,3).f = input1.ef.w*input2;

	output(3,0).c = input1.fc.x*input2;
	output(3,0).d = input1.fc.y*input2;
	output(3,0).e = input1.fc.z*input2;
	output(3,0).f = input1.fc.w*input2;

	output(3,1).c = input1.fd.x*input2;
	output(3,1).d = input1.fd.y*input2;
	output(3,1).e = input1.fd.z*input2;
	output(3,1).f = input1.fd.w*input2;

	output(3,2).c = input1.fe.x*input2;
	output(3,2).d = input1.fe.y*input2;
	output(3,2).e = input1.fe.z*input2;
	output(3,2).f = input1.fe.w*input2;

	output(3,3).c = input1.ff.x*input2;
	output(3,3).d = input1.ff.y*input2;
	output(3,3).e = input1.ff.z*input2;
	output(3,3).f = input1.ff.w*input2;
	return output;
}


/// contraction, output is scalar const
float operator | (const float4444 &A, const float4444 &B){

	float sum =0;
	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			int sign = 1;
			if(i==3)
				sign = -sign;
			if(j==3)
				sign = -sign;
			sum += sign * (A(i,j)|B(i,j));
		}
	}
	return sum;
}

float4 operator | (const float4444 &A, const float444 &B){

	float4 r;

	float sum[4] = {0,0,0,0};
	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			int sign = 1;
			if(i==3)
				sign = -sign;
			if(j==3)
				sign = -sign;
			sum[i] += sign*(A.block(i)|B);
		}
	}


	r.x = sum[0];
	r.y = sum[1];
	r.z = sum[2];
	r.w = sum[3];
	return r;

}




float44 operator | (const float4444 &A, const float44 &B){

	float44 r;
	r.c.x =  A(0,0)|B;
   	r.c.y =  A(0,1)|B;
	r.c.z =  A(0,2)|B;
	r.c.w =  A(0,3)|B;
	r.d.x =  A(1,0)|B;
	r.d.y =  A(1,1)|B;
	r.d.z =  A(1,2)|B;
	r.d.w =  A(1,3)|B;
	r.e.x =  A(2,0)|B;
	r.e.y =  A(2,1)|B;
	r.e.z =  A(2,2)|B;
	r.e.w =  A(2,3)|B;
	r.f.x =  A(3,0)|B;
	r.f.y =  A(3,1)|B;
	r.f.z =  A(3,2)|B;
	r.f.w =  A(3,3)|B;
	return r;
}




float444 operator | (const float4444 &A, const float4 &B){

	float444 r;
	r.cc = A(0,0)|B;
	r.cd = A(0,1)|B;
	r.ce = A(0,2)|B;
	r.cf = -A(0,3)|B;

	r.dc = A(1,0)|B;
	r.dd = A(1,1)|B;
	r.de = A(1,2)|B;
	r.df = -A(1,3)|B;

	r.ec = A(2,0)|B;
	r.ed = A(2,1)|B;
	r.ee = A(2,2)|B;
	r.ef = -A(2,3)|B;

	r.fc = -A(3,0)|B;
	r.fd = -A(3,1)|B;
	r.fe = -A(3,2)|B;
	r.ff = A(3,3)|B;

	return r;
}


float4 operator | (const float444 &A, const float4444 &B){

	return  (B|A);
}


float44 operator | (const float44 &A, float4444 &B){

	return (B|A);
}


float444 operator | (const float4 &A, float4444 &B){
	return (B|A);
}


float4444 operator|| (const float4444 &lhs, const float44 &rhs){
	float4444 r;
	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			r(i,j).c.x = lhs(i,j).c|rhs.c;
			r(i,j).c.y = lhs(i,j).c|rhs.d;
			r(i,j).c.z = lhs(i,j).c|rhs.e;
			r(i,j).c.w = lhs(i,j).c|rhs.f;

			r(i,j).d.x = lhs(i,j).d|rhs.c;
			r(i,j).d.y = lhs(i,j).d|rhs.d;
			r(i,j).d.z = lhs(i,j).d|rhs.e;
			r(i,j).d.w = lhs(i,j).d|rhs.f;

			r(i,j).e.x = lhs(i,j).e|rhs.c;
			r(i,j).e.y = lhs(i,j).e|rhs.d;
			r(i,j).e.z = lhs(i,j).e|rhs.e;
			r(i,j).e.w = lhs(i,j).e|rhs.f;

			r(i,j).f.x = lhs(i,j).f|rhs.c;
			r(i,j).f.y = lhs(i,j).f|rhs.d;
			r(i,j).f.z = lhs(i,j).f|rhs.e;
			r(i,j).f.w = lhs(i,j).f|rhs.f;
		}
	}
	return r;
}

float4444 operator|| (const float44 &lhs, const float4444 &rhs){
	float4444 r;
	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			float4 l;
			if(i==0)
				l = lhs.c;
			if(i==1)
				l = lhs.d;
			if(i==2)
				l = lhs.e;
			if(i==3)
				l = lhs.f;
			r(i,j).c.x = l|rhs(j,0).c;
			r(i,j).c.y = l|rhs(j,0).d;
			r(i,j).c.z = l|rhs(j,0).e;
			r(i,j).c.w = l|rhs(j,0).f;

			r(i,j).d.x = l|rhs(j,1).c;
			r(i,j).d.y = l|rhs(j,1).d;
			r(i,j).d.z = l|rhs(j,1).e;
			r(i,j).d.w = l|rhs(j,1).f;

			r(i,j).e.x = l|rhs(j,2).c;
			r(i,j).e.y = l|rhs(j,2).d;
			r(i,j).e.z = l|rhs(j,2).e;
			r(i,j).e.w = l|rhs(j,2).f;

			r(i,j).f.x = l|rhs(j,3).c;
			r(i,j).f.y = l|rhs(j,3).d;
			r(i,j).f.z = l|rhs(j,3).e;
			r(i,j).f.w = l|rhs(j,3).f;

		}
	}
	return r;
}



float4444 contract2 (const float4444 &A, const float4444 &B){

	float4444 r;

	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			r(i,j).c.x = A(i,j)|B(0,0);
			r(i,j).c.y = A(i,j)|B(0,1);
			r(i,j).c.w = A(i,j)|B(0,2);
			r(i,j).c.z = A(i,j)|B(0,3);

			r(i,j).d.x = A(i,j)|B(1,0);
			r(i,j).d.y = A(i,j)|B(1,1);
			r(i,j).d.w = A(i,j)|B(1,2);
			r(i,j).d.z = A(i,j)|B(1,3);

			r(i,j).e.x = A(i,j)|B(2,0);
			r(i,j).e.y = A(i,j)|B(2,1);
			r(i,j).e.w = A(i,j)|B(2,2);
			r(i,j).e.z = A(i,j)|B(2,3);

			r(i,j).f.x = A(i,j)|B(3,0);
			r(i,j).f.y = A(i,j)|B(3,1);
			r(i,j).f.w = A(i,j)|B(3,2);
			r(i,j).f.z = A(i,j)|B(3,3);
		}
	}
	return r;

}




float44 contract3 (const float4444 &A, const float4444 &B){

	float44 r;

	float sum[4][4];
	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			int sign = 1;
			if(i==3)
				sign = -sign;
			if(j==3)
				sign = -sign;
			sum[i][j] = sign*(A(i,j)|B(i,j));
		}
	}


	r.c.x = sum[0][0];
	r.c.y = sum[0][1];
	r.c.z = sum[0][2];
	r.c.w = sum[0][3];
	r.d.x = sum[1][0];
	r.d.y = sum[1][1];
	r.d.z = sum[1][2];
	r.d.w = sum[1][3];
	r.e.x = sum[2][0];
	r.e.y = sum[2][1];
	r.e.z = sum[2][2];
	r.e.w = sum[2][3];
	r.f.x = sum[3][0];
	r.f.y = sum[3][1];
	r.f.z = sum[3][2];
	r.f.w = sum[3][3];

	return r;

}




float4444 transpose(const float4444 &input, std::string sequence){
	float4444 output;
	if("2134" == sequence){
		for(int i=0; i < 4; i++){
			for(int j=0; j < 4; j++){
					output(i,j) = input(j,i);
			}
		}
	}

	else if("1324" == sequence){
		for(int i=0; i < 4; i++){
			output(i,0).c = input(i,0).c;
			output(i,0).d = input(i,1).c;
			output(i,0).e = input(i,2).c;
			output(i,0).f = input(i,3).c;

			output(i,1).c = input(i,0).d;
			output(i,1).d = input(i,1).d;
			output(i,1).e = input(i,2).d;
			output(i,1).f = input(i,3).d;

			output(i,2).c = input(i,0).e;
			output(i,2).d = input(i,1).e;
			output(i,2).e = input(i,2).e;
			output(i,2).f = input(i,3).e;

			output(i,3).c = input(i,0).f;
			output(i,3).d = input(i,1).f;
			output(i,3).e = input(i,2).f;
			output(i,3).f = input(i,3).f;
		}

	}
	else if("1243" == sequence){
		for(int i=0; i < 4; i++){
			for(int j=0; j < 4; j++){
				output(i,j).c.x = input(i,j).c.x;
				output(i,j).c.y = input(i,j).d.x;
				output(i,j).c.z = input(i,j).e.x;
				output(i,j).c.w = input(i,j).f.x;

				output(i,j).d.x = input(i,j).c.y;
				output(i,j).d.y = input(i,j).d.y;
				output(i,j).d.z = input(i,j).e.y;
				output(i,j).d.w = input(i,j).f.y;

				output(i,j).e.x = input(i,j).c.z;
				output(i,j).e.y = input(i,j).d.z;
				output(i,j).e.z = input(i,j).e.z;
				output(i,j).e.w = input(i,j).f.z;

				output(i,j).f.x = input(i,j).c.w;
				output(i,j).f.y = input(i,j).d.w;
				output(i,j).f.z = input(i,j).e.w;
				output(i,j).f.w = input(i,j).f.w;
			}
		}

	}
return output;
}




/// 23 transpose of float4444
float4444  transpose_4123(const float4444 &A){
	float4444 B;
	B = transpose(transpose(transpose(A,"1243"),"1324"),"2134");
	return B;
}

float4444  transpose_1423(const float4444 & A){
	float4444 B;
	B = transpose(transpose(A,"1243"),"1324");
	return B;
}

float4444  transpose_1243(const float4444 & A){
	float4444 B;
	B = transpose(A,"1243");
	return B;
}

//float4444  trans_1234(const float4444 & lhs);

float4444  transpose_4213(const float4444 & A){
	float4444 B;
	B = transpose(transpose(transpose(transpose(A,"1243"),"2134"),"1324"),"2134");
	return B;
}

float4444  transpose_2413(const float4444 & A){
	float4444 B;
	B = transpose(transpose(transpose(A,"2134"),"1243"),"1324");
	return B;
}


float4444  transpose_2143(const float4444 & A){
	float4444 B;
	B = transpose(transpose(A,"1243"),"2134");
	return B;
}

float4444  transpose_2134(const float4444 & A){
	float4444 B;
	B = transpose(A,"2134");
	return B;
}

float4444  transpose_4132(const float4444 & A){
	float4444 B;
	B = transpose(transpose(transpose(transpose(A,"1324"),"1243"),"1324"),"2134");
	return B;
}

float4444  transpose_1432(const float4444 & A){
	float4444 B;
	B = transpose(transpose(transpose(A,"1243"),"1324"),"1243");
	return B;
}

float4444  transpose_1342(const float4444 & A){
	float4444 B;
	B = transpose(transpose(A,"1324"),"1243");
	return B;
}

float4444  transpose_1324(const float4444 & A){
	float4444 B;
	B = transpose(A,"1324");
	return B;
}

float4444  transpose_4231(const float4444 & A){
	float4444 B;
	B = transpose(transpose(transpose(transpose(transpose(A,"2134"),"1324"),"1243"),"1324"),"2134");
	return B;
}

float4444  transpose_2431(const float4444 & A){
	float4444 B;
	B = transpose(transpose(transpose(transpose(A,"2134"),"1324"),"1243"),"1324");
	return B;
}

float4444  transpose_2341(const float4444 & A){
	float4444 B;
	B = transpose(transpose(transpose(A,"2134"),"1324"),"1243");
	return B;
}

float4444  transpose_2314(const float4444 & A){
	float4444 B;
	B = transpose(transpose(A,"2134"),"1324");
	return B;
}

float4444  transpose_4312(const float4444 & A){
	float4444 B;
	B = transpose(transpose(transpose(transpose(transpose(A,"1324"),"1324"),"2134"),"1243"),"1324");
	return B;
}

float4444  transpose_3412(const float4444 & A){
	float4444 B;
	B = transpose(transpose(transpose(transpose(transpose(A,"1324"),"1243"),"2134"),"1243"),"1324");
	return B;
}

float4444  transpose_3142(const float4444 & A){
	float4444 B;
	B = transpose(transpose(transpose(A,"1324"),"2134"),"1243");
	return B;
}

float4444  transpose_3124(const float4444 & A){
	float4444 B;
	B = transpose(transpose(A,"1324"),"2134");
	return B;
}

float4444  transpose_4321(const float4444 & A){
	float4444 B;
	B = transpose(transpose(transpose(transpose(transpose(transpose(A,"1243"),"1324"),"2134"),"1243"),"1324"),"1243");
	return B;
}

float4444  transpose_3421(const float4444 & A){
	float4444 B;
	B = transpose(transpose(transpose(transpose(transpose(A,"1324"),"2134"),"1243"),"1324"),"1243");
	return B;
}

float4444  transpose_3241(const float4444 & A){
	float4444 B;
	B = transpose(transpose(transpose(transpose(A,"2134"),"1324"),"1243"),"2134");
	return B;
}

float4444  transpose_3214(const float4444 & A){
	float4444 B;
	B = transpose(transpose(transpose(A,"1324"),"2134"),"1324");
	return B;
}


float4444 movelastindex(const float4444 &input){
	float4444 output;
	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			output(i,j) = -input(i,j);
			output(i,j).c.w = input(i,j).c.w;
			output(i,j).d.w = input(i,j).d.w;
			output(i,j).e.w = input(i,j).e.w;
			output(i,j).f.w = input(i,j).f.w;
		}
	}
	return output;
}




float4444 moveindices(const float4444 &input){

	float4444 output;
	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			output(i,j) = input(i,j);
			output(i,j).f = -input(i,j).f;
			output(i,j).c.w = -input(i,j).c.w;
			output(i,j).d.w = -input(i,j).d.w;
			output(i,j).e.w = -input(i,j).e.w;
			output(i,j).f.w = input(i,j).f.w;
		}
	}
	return output;
}
