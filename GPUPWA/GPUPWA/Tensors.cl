/* \file Tensors.cl
//#define CL

//#pragma OPENCL EXTENSION cl_amd_fp64 : enable
//#include "float44.h"
//#include "float444.h"
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

/* Kernel used to copy stream*/
__kernel void kerneltensorcopy_2(__global float44 * input,  __global out float44 * output){
	uint pos = get_global_id(0);
	output[pos].c = input[pos].c;
	output[pos].d = input[pos].d;
	output[pos].e = input[pos].e;
	output[pos].f = input[pos].f;
}


/* Kernels used to assgin streams*/
__kernel void kerneltensorassign_c(__global float44 * p1, __global float44 * p2, __global float44 * p3, __global float44 * p4,  __global out float44 * output){
	uint i = get_global_id(0);
	output[i].c = p1[i].c;
	output[i].d = p2[i].c;
	output[i].e = p3[i].c;
	output[i].f = p4[i].c;
}	


/* Kernels used to assgin streams*/
__kernel void kerneltensorassign_d(__global float44 * p1, __global float44 * p2, __global float44 * p3, __global float44 * p4,  __global out float44 * output)
{
	uint i = get_global_id(0);
	output[i].c = p1[i].d;
	output[i].d = p2[i].d;
	output[i].e = p3[i].d;
	output[i].f = p4[i].d;
}

/* Kernels used to assgin streams*/
__kernel void kerneltensorassign_e(__global float44 * p1, __global float44 * p2, __global float44 * p3, __global float44 * p4,  __global out float44 * output)
{
	uint i = get_global_id(0);
	output[i].c = p1[i].e;
	output[i].d = p2[i].e;
	output[i].e = p3[i].e;
	output[i].f = p4[i].e;
}

/* Kernels used to assgin streams*/
__kernel void kerneltensorassign_f(__global float44 * p1, __global float44 * p2, __global float44 * p3, __global float44 * p4,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c = p1[i].f;
	output[i].d = p2[i].f;
	output[i].e = p3[i].f;
	output[i].f = p4[i].f;
}


			
__kernel void kerneltensorassign_0(__global float44 * input,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c.x = input[i].c.x;
	output[i].c.y = input[i].d.x;
	output[i].c.z = input[i].e.x;
	output[i].c.w = input[i].f.x;
}		


__kernel void kerneltensorassign_1(__global float44 * input,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].d.x = input[i].c.y;
	output[i].d.y = input[i].d.y;
	output[i].d.z = input[i].e.y;
	output[i].d.w = input[i].f.y;
}


__kernel void	kerneltensorassign_2(__global float44 * input,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].e.x = input[i].c.z;
	output[i].e.y = input[i].d.z;
	output[i].e.z = input[i].e.z;
	output[i].e.w = input[i].f.z;
}	



__kernel void kerneltensorassign_3(__global float44 * input,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].f.x = input[i].c.w;
	output[i].f.y = input[i].d.w;
	output[i].f.z = input[i].e.w;
	output[i].f.w = input[i].f.w;
}	

__kernel void kernelgetfloat_1(__global float4 * input, float i, __global out float * output)
{
	 uint ind = get_global_id(0);
     if(0==i) output[ind] = input[ind].x;
     if(1==i) output[ind] = input[ind].y;
     if(2==i) output[ind] = input[ind].z;
     if(3==i) output[ind] = input[ind].w;
}

__kernel void kernelgetfloat_2(__global float44 * input, uint i, uint j,  __global out float * output)
{
	 uint index = get_global_id(0);
     if(0==i && 0==j) output[index] = input[index].c.x;
     if(0==i && 1==j) output[index] = input[index].c.y;
     if(0==i && 2==j) output[index] = input[index].c.z;
     if(0==i && 3==j) output[index] = input[index].c.w;
	  
     if(1==i && 0==j) output[index] = input[index].d.x;
     if(1==i && 1==j) output[index] = input[index].d.y;
     if(1==i && 2==j) output[index] = input[index].d.z;
     if(1==i && 3==j) output[index] = input[index].d.w;
		  
     if(2==i && 0==j) output[index] = input[index].e.x;
     if(2==i && 1==j) output[index] = input[index].e.y;
     if(2==i && 2==j) output[index] = input[index].e.z;
     if(2==i && 3==j) output[index] = input[index].e.w;

     if(3==i && 0==j) output[index] = input[index].f.x;
     if(3==i && 1==j) output[index] = input[index].f.y;
     if(3==i && 2==j) output[index] = input[index].f.z;
     if(3==i && 3==j) output[index] = input[index].f.w;
}

__kernel void kerneltensormake_2(__global float * in1, __global float * in2, __global float * in3, __global  float * in4,
								 __global float * in5, __global float * in6, __global float * in7, __global float * in8,
								 __global float * in9, __global float * in10, __global float * in11, __global float * in12,
								 __global float * in13, __global float * in14, __global float * in15, __global float * in16,
								 __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c.x = in1[i];
	output[i].c.y = in2[i];
	output[i].c.z = in3[i];
	output[i].c.w = in4[i];

	output[i].d.x = in5[i];
	output[i].d.y = in6[i];
	output[i].d.z = in7[i];
	output[i].d.w = in8[i];

	output[i].e.x = in9[i];
	output[i].e.y = in10[i];
	output[i].e.z = in11[i];
	output[i].e.w = in12[i];

	output[i].f.x = in13[i];
	output[i].f.y = in14[i];
	output[i].f.z = in15[i];
	output[i].f.w = in16[i];
	
}

__kernel void kerneltensormake_2_1(__global float4 * in1,  __global float4 * in2, __global float4 * in3, __global float4 * in4, __global out float44 * output)
{
	uint i = get_global_id(0);
	output[i].c = in1[i];
	output[i].d = in2[i];
	output[i].e = in3[i];
	output[i].f = in4[i];
}

__kernel void kerneltensormake_3(__global float4 * in1, __global float4 * in2, __global float4 * in3, __global float4 * in4,
			 __global float4 * in5, __global float4 * in6, __global float4 * in7, __global float4 * in8,
			 __global float4 * in9, __global float4 * in10, __global float4 * in11, __global float4 * in12,
			 __global float4 * in13, __global float4 * in14, __global float4 * in15, __global float4 * in16, __global out float444 *output)
{
	uint i = get_global_id(0);

	output[i].cc = in1[i];
	output[i].cd = in2[i];
	output[i].ce = in3[i];
	output[i].cf = in4[i];

	output[i].dc = in5[i];
	output[i].dd = in6[i];
	output[i].de = in7[i];
	output[i].df = in8[i];

	output[i].ec = in9[i];
	output[i].ed = in10[i];
	output[i].ee = in11[i];
	output[i].ef = in12[i];

	output[i].fc = in13[i];
	output[i].fd = in14[i];
	output[i].fe = in15[i];
	output[i].ff = in16[i];

}

__kernel void kernelgetvector_2(__global float44 * input, uint i, __global out float4 * output)
{
	 uint ind = get_global_id(0);
     if(0==i) output[ind] = input[ind].c;
     if(1==i) output[ind] = input[ind].d;
     if(2==i) output[ind] = input[ind].e;
     if(3==i) output[ind] = input[ind].f;
}

__kernel void kernelgetvector_3(__global float444 * input, uint i, uint j, __global out float4 * output)
{
	 uint ind = get_global_id(0);
     if(0==i && 0==j) output[ind] = input[ind].cc;
     if(0==i && 1==j) output[ind] = input[ind].cd;
     if(0==i && 2==j) output[ind] = input[ind].ce;
     if(0==i && 3==j) output[ind] = input[ind].cf;

     if(1==i && 0==j) output[ind] = input[ind].dc;
     if(1==i && 1==j) output[ind] = input[ind].dd;
     if(1==i && 2==j) output[ind] = input[ind].de;
     if(1==i && 3==j) output[ind] = input[ind].df;

     if(2==i && 0==j) output[ind] = input[ind].ec;
     if(2==i && 1==j) output[ind] = input[ind].ed;
     if(2==i && 2==j) output[ind] = input[ind].ee;
     if(2==i && 3==j) output[ind] = input[ind].ef;

     if(3==i && 0==j) output[ind] = input[ind].fc;
     if(3==i && 1==j) output[ind] = input[ind].fd;
     if(3==i && 2==j) output[ind] = input[ind].fe;
     if(3==i && 3==j) output[ind] = input[ind].ff;
}

__kernel void kernelgetfloat44_3(__global float444 * input, uint i, __global out float44 * output)
{
	uint ind = get_global_id(0);
    if(0==i){
    	output[ind].c = input[ind].cc;
    	output[ind].d = input[ind].cd;
    	output[ind].e = input[ind].ce;
    	output[ind].f = input[ind].cf;
   	}
    if(1==i){
    	output[ind].c = input[ind].dc;
    	output[ind].d = input[ind].dd;
    	output[ind].e = input[ind].de;
    	output[ind].f = input[ind].df;
   	}
   	 if(2==i){
    	output[ind].c = input[ind].ec;
    	output[ind].d = input[ind].ed;
    	output[ind].e = input[ind].ee;
    	output[ind].f = input[ind].ef;
   	}
   	 if(3==i){
    	output[ind].c = input[ind].fc;
    	output[ind].d = input[ind].fd;
    	output[ind].e = input[ind].fe;
    	output[ind].f = input[ind].ff;
   	}
}

/* Adding scalars */
__kernel void kerneltensoradd_0_0(__global float * input1, __global float * input2,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = input1[i] + input2[i];
}

/* Kernel to add 16 scalar streams*/
__kernel void kerneltensoradd_0_16(__global float * p1, __global float * p2, __global float * p3, __global float * p4, __global float * p5, __global float * p6, __global float * p7, __global float * p8,
						         __global float * p9, __global float * p10, __global float * p11, __global float * p12, __global float * p13, __global float * p14, __global float * p15, __global float * p16,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = p1[i] + p2[i] + p3[i] + p4[i] + p5[i] + p6[i] + p7[i] + p8[i] + p9[i] +p10[i] + p11[i] + p12[i] + p13[i] + p14[i] + p15[i] + p16[i];
}


/* Kernel to add 16 vector streams*/
__kernel void kerneltensoradd_4_16(__global float4 * p00, __global float4 * p01, __global float4 * p02, __global float4 * p03,
				 __global float4 * p10, __global float4 * p11, __global float4 * p12, __global float4 * p13,
				 __global float4 * p20, __global float4 * p21, __global float4 * p22, __global float4 * p23,
				 __global float4 * p30, __global float4 * p31, __global float4 * p32, __global float4 * p33,  __global out float4 * output)
{
	 uint i = get_global_id(0);
	output[i].x = p00[i].x + p01[i].y + p02[i].z + p03[i].w;
	output[i].y = p10[i].x + p11[i].y + p12[i].z + p13[i].w;
	output[i].z = p20[i].x + p21[i].y + p22[i].z + p23[i].w;
	output[i].w = p30[i].x + p31[i].y + p32[i].z + p33[i].w;
}



/* Kernel to add 4 scalar streams*/
__kernel void kerneltensoradd_0_4(__global float * p1, __global float * p2, __global float * p3, __global float * p4,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = p1[i] + p2[i] + p3[i] + p4[i];
}


/* Adding scalars*/
__kernel void kerneltensoradd_0_f(__global float * input1, float input2,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = input1[i] + input2;
}
/* Adding vectors*/
__kernel void kerneltensoradd_1_1(__global float4 * input1, __global float4 * input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);
	output[i] = input1[i] + input2[i];
}
/* Adding vectors*/
__kernel void kerneltensoradd_1_f(__global float4 * input1, float4 input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);
	output[i] = input1[i] + input2;
}
/* Adding second rank tensors*/
__kernel void kerneltensoradd_2_2(__global float44 * input1, __global float44 * input2,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c = input1[i].c + input2[i].c;
	output[i].d = input1[i].d + input2[i].d;
	output[i].e = input1[i].e + input2[i].e;
	output[i].f = input1[i].f + input2[i].f;
}

/* Adding second rank tensors*/
__kernel void kerneltensoradd_2_f44(__global float44 * input1, float44 input2,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c = input1[i].c + input2.c;
	output[i].d = input1[i].d + input2.d;
	output[i].e = input1[i].e + input2.e;
	output[i].f = input1[i].f + input2.f;
}

/* Adding third rank tensors*/
__kernel void kerneltensoradd_3_3(__global float444 * input1, __global float444 * input2,  __global out float444 * output)
{
	 uint i = get_global_id(0);
	output[i].cc = input1[i].cc + input2[i].cc;
	output[i].cd = input1[i].cd + input2[i].cd;
	output[i].ce = input1[i].ce + input2[i].ce;
	output[i].cf = input1[i].cf + input2[i].cf;
	
	output[i].dc = input1[i].dc + input2[i].dc;
	output[i].dd = input1[i].dd + input2[i].dd;
	output[i].de = input1[i].de + input2[i].de;
	output[i].df = input1[i].df + input2[i].df;

	output[i].ec = input1[i].ec + input2[i].ec;
	output[i].ed = input1[i].ed + input2[i].ed;
	output[i].ee = input1[i].ee + input2[i].ee;
	output[i].ef = input1[i].ef + input2[i].ef;

	output[i].fc = input1[i].fc + input2[i].fc;
	output[i].fd = input1[i].fd + input2[i].fd;
	output[i].fe = input1[i].fe + input2[i].fe;
	output[i].ff = input1[i].ff + input2[i].ff;

}

/* Adding third rank tensors*/
__kernel void kerneltensoradd_3_f(__global float444 * input1, float444 input2,  __global out float444 * output)
{
	 uint i = get_global_id(0);
	output[i].cc = input1[i].cc + input2.cc;
	output[i].cd = input1[i].cd + input2.cd;
	output[i].ce = input1[i].ce + input2.ce;
	output[i].cf = input1[i].cf + input2.cf;

	output[i].dc = input1[i].dc + input2.dc;
	output[i].dd = input1[i].dd + input2.dd;
	output[i].de = input1[i].de + input2.de;
	output[i].df = input1[i].df + input2.df;

	output[i].ec = input1[i].ec + input2.ec;
	output[i].ed = input1[i].ed + input2.ed;
	output[i].ee = input1[i].ee + input2.ee;
	output[i].ef = input1[i].ef + input2.ef;

	output[i].fc = input1[i].fc + input2.fc;
	output[i].fd = input1[i].fd + input2.fd;
	output[i].fe = input1[i].fe + input2.fe;
	output[i].ff = input1[i].ff + input2.ff;

}

/* Subtracting scalars */
__kernel void kerneltensorsub_0_0(__global float * input1, __global float * input2,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = input1[i] - input2[i];
}
__kernel void kerneltensorsub_0_f(__global float * input1, float input2,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = input1[i] - input2;
}
__kernel void kerneltensorsub_f_0(float input1, __global float * input2,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = input1 - input2[i];
}
/* Subtracting vectors */
__kernel void kerneltensorsub_1_1(__global float4 * input1, __global float4 * input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);
	output[i] = input1[i] - input2[i];
}
__kernel void kerneltensorsub_1_f(__global float4 * input1, float4 input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);
	output[i] = input1[i] - input2;
}
__kernel void kerneltensorsub_f_1(float4 input1, __global float4 * input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);
	output[i] = input1 - input2[i];
}

/* Subtracting second rank tensors */
__kernel void kerneltensorsub_2_2(__global float44 * input1, __global float44 * input2,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c = input1[i].c - input2[i].c;
	output[i].d = input1[i].d - input2[i].d;
	output[i].e = input1[i].e - input2[i].e;
	output[i].f = input1[i].f - input2[i].f;
}

/* Subtracting second rank tensors */
__kernel void kerneltensorsub_2_f(__global float44 * input1, float44 input2,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c = input1[i].c - input2.c;
	output[i].d = input1[i].d - input2.d;
	output[i].e = input1[i].e - input2.e;
	output[i].f = input1[i].f - input2.f;
}

/* Subtracting second rank tensors*/
__kernel void kerneltensorsub_f_2(float44 input1, __global float44 * input2,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c = input1.c - input2[i].c;
	output[i].d = input1.d - input2[i].d;
	output[i].e = input1.e - input2[i].e;
	output[i].f = input1.f - input2[i].f;
}

/* Subtracting third rank tensors */
__kernel void kerneltensorsub_3_3(__global float444 * input1, __global float444 * input2,  __global out float444 * output)
{
	 uint i = get_global_id(0);
	output[i].cc = input1[i].cc - input2[i].cc;
	output[i].cd = input1[i].cd - input2[i].cd;
	output[i].ce = input1[i].ce - input2[i].ce;
	output[i].cf = input1[i].cf - input2[i].cf;
	
	output[i].dc = input1[i].dc - input2[i].dc;
	output[i].dd = input1[i].dd - input2[i].dd;
	output[i].de = input1[i].de - input2[i].de;
	output[i].df = input1[i].df - input2[i].df;

	output[i].ec = input1[i].ec - input2[i].ec;
	output[i].ed = input1[i].ed - input2[i].ed;
	output[i].ee = input1[i].ee - input2[i].ee;
	output[i].ef = input1[i].ef - input2[i].ef;

	output[i].fc = input1[i].fc - input2[i].fc;
	output[i].fd = input1[i].fd - input2[i].fd;
	output[i].fe = input1[i].fe - input2[i].fe;
	output[i].ff = input1[i].ff - input2[i].ff;

}

/* Subtracting third rank tensors*/
__kernel void kerneltensorsub_3_f(__global float444 * input1, float444 input2,  __global out float444 * output)
{
	 uint i = get_global_id(0);
	output[i].cc = input1[i].cc - input2.cc;
	output[i].cd = input1[i].cd - input2.cd;
	output[i].ce = input1[i].ce - input2.ce;
	output[i].cf = input1[i].cf - input2.cf;

	output[i].dc = input1[i].dc - input2.dc;
	output[i].dd = input1[i].dd - input2.dd;
	output[i].de = input1[i].de - input2.de;
	output[i].df = input1[i].df - input2.df;

	output[i].ec = input1[i].ec - input2.ec;
	output[i].ed = input1[i].ed - input2.ed;
	output[i].ee = input1[i].ee - input2.ee;
	output[i].ef = input1[i].ef - input2.ef;

	output[i].fc = input1[i].fc - input2.fc;
	output[i].fd = input1[i].fd - input2.fd;
	output[i].fe = input1[i].fe - input2.fe;
	output[i].ff = input1[i].ff - input2.ff;

}

/* Subtracting third rank tensors */
__kernel void kerneltensorsub_f_3(float444 input1, __global float444 * input2,  __global out float444 * output)
{
	 uint i = get_global_id(0);
	output[i].cc = input1.cc - input2[i].cc;
	output[i].cd = input1.cd - input2[i].cd;
	output[i].ce = input1.ce - input2[i].ce;
	output[i].cf = input1.cf - input2[i].cf;

	output[i].dc = input1.dc - input2[i].dc;
	output[i].dd = input1.dd - input2[i].dd;
	output[i].de = input1.de - input2[i].de;
	output[i].df = input1.df - input2[i].df;

	output[i].ec = input1.ec - input2[i].ec;
	output[i].ed = input1.ed - input2[i].ed;
	output[i].ee = input1.ee - input2[i].ee;
	output[i].ef = input1.ef - input2[i].ef;

	output[i].fc = input1.fc - input2[i].fc;
	output[i].fd = input1.fd - input2[i].fd;
	output[i].fe = input1.fe - input2[i].fe;
	output[i].ff = input1.ff - input2[i].ff;

}

/* Multiplying scalars */
__kernel void kerneltensormult_0_0(__global float * input1, __global float * input2,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = input1[i]*input2[i];
}
/* Multiplying scalars*/
__kernel void kerneltensormult_0_f(__global float * input1, float input2,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = input1[i]*input2;
}

/* Multiplying scalars with vecors*/
__kernel void kerneltensormult_0_1(__global float * input1, __global float4 * input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);
	output[i] = input1[i]*input2[i];
}
/* Multiplying scalars with vecors*/
__kernel void kerneltensormult_0_f4(__global float * input1, float4 input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);
	output[i] = input1[i]*input2;
}
/* Multiplying scalars with vecors*/
__kernel void kerneltensormult_f_1(float input1, __global float4 * input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);
	output[i] = input1*input2[i];
}

/* Multiplying scalars with second rank tensors*/
__kernel void kerneltensormult_0_2(__global float * input1, __global float44 * input2,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c = input1[i]*input2[i].c;
	output[i].d = input1[i]*input2[i].d;
	output[i].e = input1[i]*input2[i].e;
	output[i].f = input1[i]*input2[i].f;
}

/* Multiplying scalars with second rank tensors*/
__kernel void kerneltensormult_0_f44(__global float * input1, float44 input2,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c = input1[i]*input2.c;
	output[i].d = input1[i]*input2.d;
	output[i].e = input1[i]*input2.e;
	output[i].f = input1[i]*input2.f;
}

/* Multiplying scalars taken from float44 with second rank tensors*/
__kernel void kerneltensormult_0i_2(__global float44 * inx, int i, int j, __global float44 * input2,  __global out float44 * output)
{
	 uint index = get_global_id(0);
	float4 indexed;
	float input1;
	if(i == 0)
		indexed = inx[index].c;
	if(i == 1)
		indexed = inx[index].d;
	if(i == 2)
		indexed = inx[index].e;
	if(i == 3)
		indexed = inx[index].f;
		
	if(j == 0)
		input1 = indexed.x;
	if(j == 1)
		input1 = indexed.y;
	if(j == 2)
		input1 = indexed.z;
	if(j == 3)
		input1 = indexed.w;	

	output[index].c = input1*input2[index].c;
	output[index].d = input1*input2[index].d;
	output[index].e = input1*input2[index].e;
	output[index].f = input1*input2[index].f;
}

__kernel void kerneltensormult_0i_f44(__global float44 * inx, int i, int j, float44 input2,  __global out float44 * output)
{
	 uint index = get_global_id(0);
	float4 indexed;
	float input1;
	if(i == 0)
		indexed = inx[index].c;
	if(i == 1)
		indexed = inx[index].d;
	if(i == 2)
		indexed = inx[index].e;
	if(i == 3)
		indexed = inx[index].f;

	if(j == 0)
		input1 = indexed.x;
	if(j == 1)
		input1 = indexed.y;
	if(j == 2)
		input1 = indexed.z;
	if(j == 3)
		input1 = indexed.w;

	output[index].c = input1*input2.c;
	output[index].d = input1*input2.d;
	output[index].e = input1*input2.e;
	output[index].f = input1*input2.f;
}


/* Multiplying scalars with second rank tensors*/
__kernel void kerneltensormult_f_2(float input1, __global float44 * input2,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c = input1*input2[i].c;
	output[i].d = input1*input2[i].d;
	output[i].e = input1*input2[i].e;
	output[i].f = input1*input2[i].f;
}

/* Multiplying scalars taken from float44 with second rank tensors*/
__kernel void kerneltensormult_fi_2(float44 inx, int i, int j, __global float44 * input2,  __global out float44 * output)
{
	 uint index = get_global_id(0);
	float4 indexed;
	float input1;
	if(i == 0)
		indexed = inx.c;
	if(i == 1)
		indexed = inx.d;
	if(i == 2)
		indexed = inx.e;
	if(i == 3)
		indexed = inx.f;
		
	if(j == 0)
		input1 = indexed.x;
	if(j == 1)
		input1 = indexed.y;
	if(j == 2)
		input1 = indexed.z;
	if(j == 3)
		input1 = indexed.w;

	output[index].c = input1*input2[index].c;
	output[index].d = input1*input2[index].d;
	output[index].e = input1*input2[index].e;
	output[index].f = input1*input2[index].f;
}


/* multiplying scalar stream wirh three rank tensor stream*/
__kernel void kerneltensormult_0_3(__global float * input1, __global float444 * input2,  __global out float444 * output){
	 uint i = get_global_id(0);

	output[i].cc = input1[i]*input2[i].cc;
	output[i].cd = input1[i]*input2[i].cd;
	output[i].ce = input1[i]*input2[i].ce;
    output[i].cf = input1[i]*input2[i].cf;

	output[i].dc = input1[i]*input2[i].dc;
	output[i].dd = input1[i]*input2[i].dd;
	output[i].de = input1[i]*input2[i].de;
    output[i].df = input1[i]*input2[i].df;

	output[i].ec = input1[i]*input2[i].ec;
	output[i].ed = input1[i]*input2[i].ed;
	output[i].ee = input1[i]*input2[i].ee;
    output[i].ef = input1[i]*input2[i].ef;

	output[i].fc = input1[i]*input2[i].fc;
	output[i].fd = input1[i]*input2[i].fd;
	output[i].fe = input1[i]*input2[i].fe;
    output[i].ff = input1[i]*input2[i].ff;
}


/* multiplying scalar const with three rank tensor steam*/
__kernel void kerneltensormult_f_3(float input1, __global float444 * input2,  __global out float444 * output){
	 uint i = get_global_id(0);
	
	output[i].cc = input1*input2[i].cc;
	output[i].cd = input1*input2[i].cd;
	output[i].ce = input1*input2[i].ce;
    output[i].cf = input1*input2[i].cf;

	output[i].dc = input1*input2[i].dc;
	output[i].dd = input1*input2[i].dd;
	output[i].de = input1*input2[i].de;
    output[i].df = input1*input2[i].df;

	output[i].ec = input1*input2[i].ec;
	output[i].ed = input1*input2[i].ed;
	output[i].ee = input1*input2[i].ee;
    output[i].ef = input1*input2[i].ef;

	output[i].fc = input1*input2[i].fc;
	output[i].fd = input1*input2[i].fd;
	output[i].fe = input1*input2[i].fe;
    output[i].ff = input1*input2[i].ff;

}

/* multiplying scalar stream wirh three rank tensor const*/
__kernel void kerneltensormult_0_f444(__global float * input1, float444 input2,  __global out float444 * output){
	 uint i = get_global_id(0);

	output[i].cc = input1[i]*input2.cc;
	output[i].cd = input1[i]*input2.cd;
	output[i].ce = input1[i]*input2.ce;
    output[i].cf = input1[i]*input2.cf;

	output[i].dc = input1[i]*input2.dc;
	output[i].dd = input1[i]*input2.dd;
	output[i].de = input1[i]*input2.de;
    output[i].df = input1[i]*input2.df;

	output[i].ec = input1[i]*input2.ec;
	output[i].ed = input1[i]*input2.ed;
	output[i].ee = input1[i]*input2.ee;
    output[i].ef = input1[i]*input2.ef;

	output[i].fc = input1[i]*input2.fc;
	output[i].fd = input1[i]*input2.fd;
	output[i].fe = input1[i]*input2.fe;
    output[i].ff = input1[i]*input2.ff;
}


/* Dividing scalars*/
__kernel void kerneltensordiv_0_0(__global float * input1, __global float * input2,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = input1[i]/input2[i];
}
/* Dividing scalars*/
__kernel void kerneltensordiv_f_0(float input1, __global float * input2,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = input1/input2[i];
}

/* Dividing scalars with vecors*/
__kernel void kerneltensordiv_1_0(__global float4 * input1, __global float * input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);
	output[i] = input1[i]/input2[i];
}

/* Dividing scalars with vecors*/
__kernel void kerneltensordiv_f4_0(float4 input1, __global float * input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);
	output[i] = input1/input2[i];
}


/* Dividing scalars with second rank tensors*/
__kernel void kerneltensordiv_2_0(__global float44 * input1, __global float * input2,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c = input1[i].c/input2[i];
	output[i].d = input1[i].d/input2[i];
	output[i].e = input1[i].e/input2[i];
	output[i].f = input1[i].f/input2[i];
}


/* Dividing second rank tensors by float*/
__kernel void kerneltensordiv_2_f(__global float44 * input1, float input2,  __global out float44 * output){
	 uint i = get_global_id(0);
      
	output[i].c = input1[i].c/input2;
	output[i].d = input1[i].d/input2;
	output[i].e = input1[i].e/input2;
	output[i].f = input1[i].f/input2;
}

/* Dividing second rank tensors by float*/
__kernel void kerneltensordiv_f44_0(float44 input1, __global float * input2,  __global out float44 * output){
	 uint i = get_global_id(0);

	output[i].c = input1.c/input2[i];
	output[i].d = input1.d/input2[i];
	output[i].e = input1.e/input2[i];
	output[i].f = input1.f/input2[i];
}




/* Dividing third rank tensors by scalars*/
__kernel void kerneltensordiv_3_0(__global float444 * input1, __global float * input2,  __global out float444 * output)
{
	 uint i = get_global_id(0);
	
	output[i].cc = input1[i].cc/input2[i];
	output[i].cd = input1[i].cd/input2[i];
	output[i].ce = input1[i].ce/input2[i];
    output[i].cf = input1[i].cf/input2[i];

	output[i].dc = input1[i].dc/input2[i];
	output[i].dd = input1[i].dd/input2[i];
	output[i].de = input1[i].de/input2[i];
    output[i].df = input1[i].df/input2[i];

	output[i].ec = input1[i].ec/input2[i];
	output[i].ed = input1[i].ed/input2[i];
	output[i].ee = input1[i].ee/input2[i];
    output[i].ef = input1[i].ef/input2[i];

	output[i].fc = input1[i].fc/input2[i];
	output[i].fd = input1[i].fd/input2[i];
	output[i].fe = input1[i].fe/input2[i];
    output[i].ff = input1[i].ff/input2[i];

}

/* Dividing third rank tensors by float*/
__kernel void kerneltensordiv_3_f(__global float444 * input1, float input2,  __global out float444 * output)
{
	 uint i = get_global_id(0);
		
	output[i].cc = input1[i].cc/input2;
	output[i].cd = input1[i].cd/input2;
	output[i].ce = input1[i].ce/input2;
    output[i].cf = input1[i].cf/input2;

	output[i].dc = input1[i].dc/input2;
	output[i].dd = input1[i].dd/input2;
	output[i].de = input1[i].de/input2;
    output[i].df = input1[i].df/input2;

	output[i].ec = input1[i].ec/input2;
	output[i].ed = input1[i].ed/input2;
	output[i].ee = input1[i].ee/input2;
    output[i].ef = input1[i].ef/input2;

	output[i].fc = input1[i].fc/input2;
	output[i].fd = input1[i].fd/input2;
	output[i].fe = input1[i].fe/input2;
    output[i].ff = input1[i].ff/input2;


}

/* Dividing third rank tensors by scalars*/
__kernel void kerneltensordiv_f444_0(float444 input1, __global float * input2,  __global out float444 * output)
{
	 uint i = get_global_id(0);

	output[i].cc = input1.cc/input2[i];
	output[i].cd = input1.cd/input2[i];
	output[i].ce = input1.ce/input2[i];
    output[i].cf = input1.cf/input2[i];

	output[i].dc = input1.dc/input2[i];
	output[i].dd = input1.dd/input2[i];
	output[i].de = input1.de/input2[i];
    output[i].df = input1.df/input2[i];

	output[i].ec = input1.ec/input2[i];
	output[i].ed = input1.ed/input2[i];
	output[i].ee = input1.ee/input2[i];
    output[i].ef = input1.ef/input2[i];

	output[i].fc = input1.fc/input2[i];
	output[i].fd = input1.fd/input2[i];
	output[i].fe = input1.fe/input2[i];
    output[i].ff = input1.ff/input2[i];

}


__kernel void kerneltensorouter_1_1(__global float4 * input1, __global float4 * input2,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c.x = input1[i].x*input2[i].x;
	output[i].c.y = input1[i].x*input2[i].y;
	output[i].c.z = input1[i].x*input2[i].z;
	output[i].c.w = input1[i].x*input2[i].w;

	output[i].d.x = input1[i].y*input2[i].x;
	output[i].d.y = input1[i].y*input2[i].y;
	output[i].d.z = input1[i].y*input2[i].z;
	output[i].d.w = input1[i].y*input2[i].w;

	output[i].e.x = input1[i].z*input2[i].x;
	output[i].e.y = input1[i].z*input2[i].y;
	output[i].e.z = input1[i].z*input2[i].z;
	output[i].e.w = input1[i].z*input2[i].w;

	output[i].f.x = input1[i].w*input2[i].x;
	output[i].f.y = input1[i].w*input2[i].y;
	output[i].f.z = input1[i].w*input2[i].z;
	output[i].f.w = input1[i].w*input2[i].w;
}

__kernel void kerneltensorouter_1_f4(__global float4 * input1, float4 input2,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c.x = input1[i].x*input2.x;
	output[i].c.y = input1[i].x*input2.y;
	output[i].c.z = input1[i].x*input2.z;
	output[i].c.w = input1[i].x*input2.w;

	output[i].d.x = input1[i].y*input2.x;
	output[i].d.y = input1[i].y*input2.y;
	output[i].d.z = input1[i].y*input2.z;
	output[i].d.w = input1[i].y*input2.w;

	output[i].e.x = input1[i].z*input2.x;
	output[i].e.y = input1[i].z*input2.y;
	output[i].e.z = input1[i].z*input2.z;
	output[i].e.w = input1[i].z*input2.w;

	output[i].f.x = input1[i].w*input2.x;
	output[i].f.y = input1[i].w*input2.y;
	output[i].f.z = input1[i].w*input2.z;
	output[i].f.w = input1[i].w*input2.w;

}

__kernel void kerneltensorouter_f4_1( float4 input1, __global float4 * input2,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c.x = input1.x*input2[i].x;
	output[i].c.y = input1.x*input2[i].y;
	output[i].c.z = input1.x*input2[i].z;
	output[i].c.w = input1.x*input2[i].w;

	output[i].d.x = input1.y*input2[i].x;
	output[i].d.y = input1.y*input2[i].y;
	output[i].d.z = input1.y*input2[i].z;
	output[i].d.w = input1.y*input2[i].w;


	output[i].e.x = input1.z*input2[i].x;
	output[i].e.y = input1.z*input2[i].y;
	output[i].e.z = input1.z*input2[i].z;
	output[i].e.w = input1.z*input2[i].w;

	output[i].f.x = input1.w*input2[i].x;
	output[i].f.y = input1.w*input2[i].y;
	output[i].f.z = input1.w*input2[i].z;
	output[i].f.w = input1.w*input2[i].w;
}

__kernel void kerneltensorouter_2_1(__global float44 * input1, __global float4* input2,  __global out float444 * output){
	 uint i = get_global_id(0);

	output[i].cc.x = input1[i].c.x*input2[i].x;
	output[i].cc.y = input1[i].c.x*input2[i].y;
	output[i].cc.z = input1[i].c.x*input2[i].z;
	output[i].cc.w = input1[i].c.x*input2[i].w;
    output[i].cd.x = input1[i].c.y*input2[i].x;
	output[i].cd.y = input1[i].c.y*input2[i].y;
	output[i].cd.z = input1[i].c.y*input2[i].z;
	output[i].cd.w = input1[i].c.y*input2[i].w;
	output[i].ce.x = input1[i].c.z*input2[i].x;
	output[i].ce.y = input1[i].c.z*input2[i].y;
	output[i].ce.z = input1[i].c.z*input2[i].z;
	output[i].ce.w = input1[i].c.z*input2[i].w;
    output[i].cf.x = input1[i].c.w*input2[i].x;
	output[i].cf.y = input1[i].c.w*input2[i].y;
	output[i].cf.z = input1[i].c.w*input2[i].z;
	output[i].cf.w = input1[i].c.w*input2[i].w;

    output[i].dc.x = input1[i].d.x*input2[i].x;
	output[i].dc.y = input1[i].d.x*input2[i].y;
	output[i].dc.z = input1[i].d.x*input2[i].z;
	output[i].dc.w = input1[i].d.x*input2[i].w;
    output[i].dd.x = input1[i].d.y*input2[i].x;
	output[i].dd.y = input1[i].d.y*input2[i].y;
	output[i].dd.z = input1[i].d.y*input2[i].z;
	output[i].dd.w = input1[i].d.y*input2[i].w;
	output[i].de.x = input1[i].d.z*input2[i].x;
	output[i].de.y = input1[i].d.z*input2[i].y;
	output[i].de.z = input1[i].d.z*input2[i].z;
	output[i].de.w = input1[i].d.z*input2[i].w;
    output[i].df.x = input1[i].d.w*input2[i].x;
	output[i].df.y = input1[i].d.w*input2[i].y;
	output[i].df.z = input1[i].d.w*input2[i].z;
	output[i].df.w = input1[i].d.w*input2[i].w;

   	output[i].ec.x = input1[i].e.x*input2[i].x;
	output[i].ec.y = input1[i].e.x*input2[i].y;
	output[i].ec.z = input1[i].e.x*input2[i].z;
	output[i].ec.w = input1[i].e.x*input2[i].w;
    output[i].ed.x = input1[i].e.y*input2[i].x;
	output[i].ed.y = input1[i].e.y*input2[i].y;
	output[i].ed.z = input1[i].e.y*input2[i].z;
	output[i].ed.w = input1[i].e.y*input2[i].w;
	output[i].ee.x = input1[i].e.z*input2[i].x;
	output[i].ee.y = input1[i].e.z*input2[i].y;
	output[i].ee.z = input1[i].e.z*input2[i].z;
	output[i].ee.w = input1[i].e.z*input2[i].w;
    output[i].ef.x = input1[i].e.w*input2[i].x;
	output[i].ef.y = input1[i].e.w*input2[i].y;
	output[i].ef.z = input1[i].e.w*input2[i].z;
	output[i].ef.w = input1[i].e.w*input2[i].w;

	output[i].fc.x = input1[i].f.x*input2[i].x;
	output[i].fc.y = input1[i].f.x*input2[i].y;
	output[i].fc.z = input1[i].f.x*input2[i].z;
	output[i].fc.w = input1[i].f.x*input2[i].w;
    output[i].fd.x = input1[i].f.y*input2[i].x;
	output[i].fd.y = input1[i].f.y*input2[i].y;
	output[i].fd.z = input1[i].f.y*input2[i].z;
	output[i].fd.w = input1[i].f.y*input2[i].w;
	output[i].fe.x = input1[i].f.z*input2[i].x;
	output[i].fe.y = input1[i].f.z*input2[i].y;
	output[i].fe.z = input1[i].f.z*input2[i].z;
	output[i].fe.w = input1[i].f.z*input2[i].w;
    output[i].ff.x = input1[i].f.w*input2[i].x;
	output[i].ff.y = input1[i].f.w*input2[i].y;
	output[i].ff.z = input1[i].f.w*input2[i].z;
	output[i].ff.w = input1[i].f.w*input2[i].w;
}


/* Kernel for outer product of rank2 stream and vector const*/
__kernel void kerneltensorouter_2_f4(__global float44 * input1, float4 input2,  __global out float444 * output){
	 uint i = get_global_id(0);

	output[i].cc.x = input1[i].c.x*input2.x;
	output[i].cc.y = input1[i].c.x*input2.y;
	output[i].cc.z = input1[i].c.x*input2.z;
	output[i].cc.w = input1[i].c.x*input2.w;
    output[i].cd.x = input1[i].c.y*input2.x;
	output[i].cd.y = input1[i].c.y*input2.y;
	output[i].cd.z = input1[i].c.y*input2.z;
	output[i].cd.w = input1[i].c.y*input2.w;
	output[i].ce.x = input1[i].c.z*input2.x;
	output[i].ce.y = input1[i].c.z*input2.y;
	output[i].ce.z = input1[i].c.z*input2.z;
	output[i].ce.w = input1[i].c.z*input2.w;
    output[i].cf.x = input1[i].c.w*input2.x;
	output[i].cf.y = input1[i].c.w*input2.y;
	output[i].cf.z = input1[i].c.w*input2.z;
	output[i].cf.w = input1[i].c.w*input2.w;

    output[i].dc.x = input1[i].d.x*input2.x;
	output[i].dc.y = input1[i].d.x*input2.y;
	output[i].dc.z = input1[i].d.x*input2.z;
	output[i].dc.w = input1[i].d.x*input2.w;
    output[i].dd.x = input1[i].d.y*input2.x;
	output[i].dd.y = input1[i].d.y*input2.y;
	output[i].dd.z = input1[i].d.y*input2.z;
	output[i].dd.w = input1[i].d.y*input2.w;
	output[i].de.x = input1[i].d.z*input2.x;
	output[i].de.y = input1[i].d.z*input2.y;
	output[i].de.z = input1[i].d.z*input2.z;
	output[i].de.w = input1[i].d.z*input2.w;
    output[i].df.x = input1[i].d.w*input2.x;
	output[i].df.y = input1[i].d.w*input2.y;
	output[i].df.z = input1[i].d.w*input2.z;
	output[i].df.w = input1[i].d.w*input2.w;

   	output[i].ec.x = input1[i].e.x*input2.x;
	output[i].ec.y = input1[i].e.x*input2.y;
	output[i].ec.z = input1[i].e.x*input2.z;
	output[i].ec.w = input1[i].e.x*input2.w;
    output[i].ed.x = input1[i].e.y*input2.x;
	output[i].ed.y = input1[i].e.y*input2.y;
	output[i].ed.z = input1[i].e.y*input2.z;
	output[i].ed.w = input1[i].e.y*input2.w;
	output[i].ee.x = input1[i].e.z*input2.x;
	output[i].ee.y = input1[i].e.z*input2.y;
	output[i].ee.z = input1[i].e.z*input2.z;
	output[i].ee.w = input1[i].e.z*input2.w;
    output[i].ef.x = input1[i].e.w*input2.x;
	output[i].ef.y = input1[i].e.w*input2.y;
	output[i].ef.z = input1[i].e.w*input2.z;
	output[i].ef.w = input1[i].e.w*input2.w;

	output[i].fc.x = input1[i].f.x*input2.x;
	output[i].fc.y = input1[i].f.x*input2.y;
	output[i].fc.z = input1[i].f.x*input2.z;
	output[i].fc.w = input1[i].f.x*input2.w;
    output[i].fd.x = input1[i].f.y*input2.x;
	output[i].fd.y = input1[i].f.y*input2.y;
	output[i].fd.z = input1[i].f.y*input2.z;
	output[i].fd.w = input1[i].f.y*input2.w;
	output[i].fe.x = input1[i].f.z*input2.x;
	output[i].fe.y = input1[i].f.z*input2.y;
	output[i].fe.z = input1[i].f.z*input2.z;
	output[i].fe.w = input1[i].f.z*input2.w;
    output[i].ff.x = input1[i].f.w*input2.x;
	output[i].ff.y = input1[i].f.w*input2.y;
	output[i].ff.z = input1[i].f.w*input2.z;
	output[i].ff.w = input1[i].f.w*input2.w;
}

__kernel void kerneltensorouter_f44_1(float44 input1, __global float4* input2,  __global out float444 * output){
	 uint i = get_global_id(0);

	output[i].cc.x = input1.c.x*input2[i].x;
	output[i].cc.y = input1.c.x*input2[i].y;
	output[i].cc.z = input1.c.x*input2[i].z;
	output[i].cc.w = input1.c.x*input2[i].w;
    output[i].cd.x = input1.c.y*input2[i].x;
	output[i].cd.y = input1.c.y*input2[i].y;
	output[i].cd.z = input1.c.y*input2[i].z;
	output[i].cd.w = input1.c.y*input2[i].w;
	output[i].ce.x = input1.c.z*input2[i].x;
	output[i].ce.y = input1.c.z*input2[i].y;
	output[i].ce.z = input1.c.z*input2[i].z;
	output[i].ce.w = input1.c.z*input2[i].w;
    output[i].cf.x = input1.c.w*input2[i].x;
	output[i].cf.y = input1.c.w*input2[i].y;
	output[i].cf.z = input1.c.w*input2[i].z;
	output[i].cf.w = input1.c.w*input2[i].w;

    output[i].dc.x = input1.d.x*input2[i].x;
	output[i].dc.y = input1.d.x*input2[i].y;
	output[i].dc.z = input1.d.x*input2[i].z;
	output[i].dc.w = input1.d.x*input2[i].w;
    output[i].dd.x = input1.d.y*input2[i].x;
	output[i].dd.y = input1.d.y*input2[i].y;
	output[i].dd.z = input1.d.y*input2[i].z;
	output[i].dd.w = input1.d.y*input2[i].w;
	output[i].de.x = input1.d.z*input2[i].x;
	output[i].de.y = input1.d.z*input2[i].y;
	output[i].de.z = input1.d.z*input2[i].z;
	output[i].de.w = input1.d.z*input2[i].w;
    output[i].df.x = input1.d.w*input2[i].x;
	output[i].df.y = input1.d.w*input2[i].y;
	output[i].df.z = input1.d.w*input2[i].z;
	output[i].df.w = input1.d.w*input2[i].w;

   	output[i].ec.x = input1.e.x*input2[i].x;
	output[i].ec.y = input1.e.x*input2[i].y;
	output[i].ec.z = input1.e.x*input2[i].z;
	output[i].ec.w = input1.e.x*input2[i].w;
    output[i].ed.x = input1.e.y*input2[i].x;
	output[i].ed.y = input1.e.y*input2[i].y;
	output[i].ed.z = input1.e.y*input2[i].z;
	output[i].ed.w = input1.e.y*input2[i].w;
	output[i].ee.x = input1.e.z*input2[i].x;
	output[i].ee.y = input1.e.z*input2[i].y;
	output[i].ee.z = input1.e.z*input2[i].z;
	output[i].ee.w = input1.e.z*input2[i].w;
    output[i].ef.x = input1.e.w*input2[i].x;
	output[i].ef.y = input1.e.w*input2[i].y;
	output[i].ef.z = input1.e.w*input2[i].z;
	output[i].ef.w = input1.e.w*input2[i].w;

	output[i].fc.x = input1.f.x*input2[i].x;
	output[i].fc.y = input1.f.x*input2[i].y;
	output[i].fc.z = input1.f.x*input2[i].z;
	output[i].fc.w = input1.f.x*input2[i].w;
    output[i].fd.x = input1.f.y*input2[i].x;
	output[i].fd.y = input1.f.y*input2[i].y;
	output[i].fd.z = input1.f.y*input2[i].z;
	output[i].fd.w = input1.f.y*input2[i].w;
	output[i].fe.x = input1.f.z*input2[i].x;
	output[i].fe.y = input1.f.z*input2[i].y;
	output[i].fe.z = input1.f.z*input2[i].z;
	output[i].fe.w = input1.f.z*input2[i].w;
    output[i].ff.x = input1.f.w*input2[i].x;
	output[i].ff.y = input1.f.w*input2[i].y;
	output[i].ff.z = input1.f.w*input2[i].z;
	output[i].ff.w = input1.f.w*input2[i].w;
}

__kernel void kerneltensorouter_1_2(__global float4 * lhs, __global float44 * rhs, __global out float444 * output){
	uint i = get_global_id(0);
	output[i].cc = lhs[i].x*rhs[i].c;
	output[i].cd = lhs[i].x*rhs[i].d;
	output[i].ce = lhs[i].x*rhs[i].e;
	output[i].cf = lhs[i].x*rhs[i].f;

	output[i].dc = lhs[i].y*rhs[i].c;
	output[i].dd = lhs[i].y*rhs[i].d;
	output[i].de = lhs[i].y*rhs[i].e;
	output[i].df = lhs[i].y*rhs[i].f;

	output[i].ec = lhs[i].z*rhs[i].c;
	output[i].ed = lhs[i].z*rhs[i].d;
	output[i].ee = lhs[i].z*rhs[i].e;
	output[i].ef = lhs[i].z*rhs[i].f;

	output[i].fc = lhs[i].w*rhs[i].c;
	output[i].fd = lhs[i].w*rhs[i].d;
	output[i].fe = lhs[i].w*rhs[i].e;
	output[i].ff = lhs[i].w*rhs[i].f;
}

__kernel void kerneltensorouter_f4_2(float4 lhs, __global float44 * rhs, __global out float444 *output){
	uint i = get_global_id(0);
	output[i].cc = lhs.x*rhs[i].c;
	output[i].cd = lhs.x*rhs[i].d;
	output[i].ce = lhs.x*rhs[i].e;
	output[i].cf = lhs.x*rhs[i].f;

	output[i].dc = lhs.y*rhs[i].c;
	output[i].dd = lhs.y*rhs[i].d;
	output[i].de = lhs.y*rhs[i].e;
	output[i].df = lhs.y*rhs[i].f;

	output[i].ec = lhs.z*rhs[i].c;
	output[i].ed = lhs.z*rhs[i].d;
	output[i].ee = lhs.z*rhs[i].e;
	output[i].ef = lhs.z*rhs[i].f;

	output[i].fc = lhs.w*rhs[i].c;
	output[i].fd = lhs.w*rhs[i].d;
	output[i].fe = lhs.w*rhs[i].e;
	output[i].ff = lhs.w*rhs[i].f;
}

__kernel void kerneltensorouter_1_f44(__global float4 * lhs, float44 rhs, __global out float444 * output){
	uint i = get_global_id(0);
	output[i].cc = lhs[i].x*rhs.c;
	output[i].cd = lhs[i].x*rhs.d;
	output[i].ce = lhs[i].x*rhs.e;
	output[i].cf = lhs[i].x*rhs.f;

	output[i].dc = lhs[i].y*rhs.c;
	output[i].dd = lhs[i].y*rhs.d;
	output[i].de = lhs[i].y*rhs.e;
	output[i].df = lhs[i].y*rhs.f;

	output[i].ec = lhs[i].z*rhs.c;
	output[i].ed = lhs[i].z*rhs.d;
	output[i].ee = lhs[i].z*rhs.e;
	output[i].ef = lhs[i].z*rhs.f;

	output[i].fc = lhs[i].w*rhs.c;
	output[i].fd = lhs[i].w*rhs.d;
	output[i].fe = lhs[i].w*rhs.e;
	output[i].ff = lhs[i].w*rhs.f;
}

__kernel void kerneltensorneg_0(__global float * input,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = - input[i];
}

__kernel void kerneltensorneg_1(__global float4 * input,  __global out float4 * output)
{
	 uint i = get_global_id(0);
	output[i] = - input[i];
}

__kernel void kerneltensorneg_2(__global float44 * input,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	output[i].c = - input[i].c;
	output[i].d = - input[i].d;
	output[i].e = - input[i].e;
	output[i].f = - input[i].f;
}

__kernel void kerneltensorneg_3(__global float444 * input,  __global out float444 * output)
{
	 uint i = get_global_id(0);
	output[i].cc = input[i].cc;
	output[i].cd = input[i].cd;
	output[i].ce = input[i].ce;
    output[i].cf = input[i].cf;

	output[i].dc = input[i].dc;
	output[i].dd = input[i].dd;
	output[i].de = input[i].de;
    output[i].df = input[i].df;

	output[i].ec = input[i].ec;
	output[i].ed = input[i].ed;
	output[i].ee = input[i].ee;
    output[i].ef = input[i].ef;

	output[i].fc = input[i].fc;
	output[i].fd = input[i].fd;
	output[i].fe = input[i].fe;
    output[i].ff = input[i].ff;
}

__kernel void kerneltensorsqrt_0(__global float * input,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = sqrt(input[i]);
}

__kernel void kerneltensorsin_0(__global float * input,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = sin(input[i]);
}

__kernel void kerneltensorcos_0(__global float * input,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = cos(input[i]);
}

__kernel void kerneltensortan_0(__global float * input,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = sin(input[i])/cos(input[i]);
}

__kernel void kerneltensorexp_0(__global float * input,  __global out float * output)
{
	 uint i = get_global_id(0);
	output[i] = exp(input[i]);
}


__kernel void kerneltensortrans_2(__global float44 * input,  __global out float44 * output)
{
	 uint i = get_global_id(0);

	output[i] = input[i];

	output[i].c.y = input[i].d.x;
	output[i].d.x = input[i].c.y;
	output[i].c.z = input[i].e.x;
	output[i].e.x = input[i].c.z;
	output[i].c.w = input[i].f.x;
	output[i].f.x = input[i].c.w;
	output[i].d.z = input[i].e.y;
	output[i].e.y = input[i].d.z;
	output[i].d.w = input[i].f.y;
	output[i].f.y = input[i].d.w;
	output[i].e.w = input[i].f.z;
	output[i].f.z = input[i].e.w;
}




__kernel void kerneltensortrans_3_213(__global float444 * input,  __global out float444 * output)
{
	 uint i = get_global_id(0);
       output[i] = input[i];

       output[i].cd.x = input[i].dc.x;
       output[i].dc.x = input[i].cd.x;
       output[i].ce.x = input[i].ec.x;
       output[i].ec.x = input[i].ce.x;
       output[i].cf.x = input[i].fc.x;
       output[i].fc.x = input[i].cf.x;
       output[i].de.x = input[i].ed.x;
       output[i].ed.x = input[i].de.x;
       output[i].df.x = input[i].fd.x;
       output[i].fd.x = input[i].df.x;
       output[i].ef.x = input[i].fe.x;
       output[i].fe.x = input[i].ef.x;

       output[i].cd.y = input[i].dc.y;
       output[i].dc.y = input[i].cd.y;
       output[i].ce.y = input[i].ec.y;
       output[i].ec.y = input[i].ce.y;
       output[i].cf.y = input[i].fc.y;
       output[i].fc.y = input[i].cf.y;
       output[i].de.y = input[i].ed.y;
       output[i].ed.y = input[i].de.y;
       output[i].df.y = input[i].fd.y;
       output[i].fd.y = input[i].df.y;
       output[i].ef.y = input[i].fe.y;
       output[i].fe.y = input[i].ef.y;

       output[i].cd.z = input[i].dc.z;
       output[i].dc.z = input[i].cd.z;
       output[i].ce.z = input[i].ec.z;
       output[i].ec.z = input[i].ce.z;
       output[i].cf.z = input[i].fc.z;
       output[i].fc.z = input[i].cf.z;
       output[i].de.z = input[i].ed.z;
       output[i].ed.z = input[i].de.z;
       output[i].df.z = input[i].fd.z;
       output[i].fd.z = input[i].df.z;
       output[i].ef.z = input[i].fe.z;
       output[i].fe.z = input[i].ef.z;


       output[i].cd.w = input[i].dc.w;
       output[i].dc.w = input[i].cd.w;
       output[i].ce.w = input[i].ec.w;
       output[i].ec.w = input[i].ce.w;
       output[i].cf.w = input[i].fc.w;
       output[i].fc.w = input[i].cf.w;
       output[i].de.w = input[i].ed.w;
       output[i].ed.w = input[i].de.w;
       output[i].df.w = input[i].fd.w;
       output[i].fd.w = input[i].df.w;
       output[i].ef.w = input[i].fe.w;
       output[i].fe.w = input[i].ef.w;

}



__kernel void kerneltensortrans_3_132(__global float444 * input,  __global out float444 * output)
{
	 uint i = get_global_id(0);
		output[i] = input[i];
		output[i].cc.y = input[i].cd.x;
                output[i].cd.x = input[i].cc.y;
                output[i].cc.z = input[i].ce.x;
                output[i].ce.x = input[i].cc.z;
		output[i].cc.w = input[i].cf.x;
                output[i].cf.x = input[i].cc.w;
		output[i].cd.z = input[i].ce.y;
		output[i].ce.y = input[i].cd.z;
		output[i].cd.w = input[i].cf.y;
		output[i].cf.y = input[i].cd.w;
		output[i].ce.w = input[i].cf.z;
		output[i].cf.z = input[i].ce.w;

		output[i].dc.y = input[i].dd.x;
                output[i].dd.x = input[i].dc.y;
                output[i].dc.z = input[i].de.x;
                output[i].de.x = input[i].dc.z;
		output[i].dc.w = input[i].df.x;
                output[i].df.x = input[i].dc.w;
	 	output[i].dd.z = input[i].de.y;
		output[i].de.y = input[i].dd.z;
		output[i].dd.w = input[i].df.y;
		output[i].df.y = input[i].dd.w;
		output[i].de.w = input[i].df.z;
		output[i].df.z = input[i].de.w;

		output[i].ec.y = input[i].ed.x;
                output[i].ed.x = input[i].ec.y;
                output[i].ec.z = input[i].ee.x;
                output[i].ee.x = input[i].ec.z;
		output[i].ec.w = input[i].ef.x;
                output[i].ef.x = input[i].ec.w;
		output[i].ed.z = input[i].ee.y;
		output[i].ee.y = input[i].ed.z;
		output[i].ed.w = input[i].ef.y;
		output[i].ef.y = input[i].ed.w;
		output[i].ee.w = input[i].ef.z;
		output[i].ef.z = input[i].ee.w;

		output[i].fc.y = input[i].fd.x;
                output[i].fd.x = input[i].fc.y;
                output[i].fc.z = input[i].fe.x;
                output[i].fe.x = input[i].fc.z;
       		output[i].fc.w = input[i].ff.x;
                output[i].ff.x = input[i].fc.w;
		output[i].fd.z = input[i].fe.y;
		output[i].fe.y = input[i].fd.z;
		output[i].fd.w = input[i].ff.y;
		output[i].ff.y = input[i].fd.w;
		output[i].fe.w = input[i].ff.z;
		output[i].ff.z = input[i].fe.w;

}

__kernel void kernelmoveindex_1(__global float4 * input,  __global out float4 * output){
	 uint i = get_global_id(0);
	output[i].xyz = -input[i].xyz;
	output[i].w   =  input[i].w;
}

__kernel void kernelmovelastindex_2(__global float44 * input,  __global out float44 * output){
	 uint i = get_global_id(0);
	output[i].c.xyz = -input[i].c.xyz;
	output[i].c.w   =  input[i].c.w;

	output[i].d.xyz = -input[i].d.xyz;
	output[i].d.w   =  input[i].d.w;

	output[i].e.xyz = -input[i].e.xyz;
	output[i].e.w   =  input[i].e.w;

	output[i].f.xyz = -input[i].f.xyz;
	output[i].f.w   =  input[i].f.w;
}



__kernel void kernelmovefirstindex_2(__global float44 * input,  __global out float44 * output){
	 uint i = get_global_id(0);
	output[i].c = - input[i].c;
	output[i].d = - input[i].d;
	output[i].e = - input[i].e;
	output[i].f =  input[i].f;
}

__kernel void kernelmoveindices_2(__global float44 * input,  __global out float44 * output){
	 uint i = get_global_id(0);
	output[i].c.xyz = input[i].c.xyz;
	output[i].c.w =  -input[i].c.w;

	output[i].d.xyz = input[i].d.xyz;
	output[i].d.w =  -input[i].d.w;

	output[i].e.xyz = input[i].e.xyz;
	output[i].e.w =  -input[i].e.w;

	output[i].f.xyz = -input[i].f.xyz;
	output[i].f.w =  input[i].f.w;
}

__kernel void kernelmoveindices_3(__global float444 * input,  __global out float444 * output){
	 uint i = get_global_id(0);
	output[i].cc.xyz = -input[i].cc.xyz;
	output[i].cc.w =  input[i].cc.w;

	output[i].cd.xyz = -input[i].cd.xyz;
	output[i].cd.w =  input[i].cd.w;

	output[i].ce.xyz = -input[i].ce.xyz;
	output[i].ce.w =  input[i].ce.w;

	output[i].cf.xyz = input[i].cf.xyz;
	output[i].cf.w   = -input[i].cf.w;


	output[i].dc.xyz = -input[i].dc.xyz;
	output[i].dc.w =  input[i].dc.w;

	output[i].dd.xyz = -input[i].dd.xyz;
	output[i].dd.w =  input[i].dd.w;

	output[i].de.xyz = -input[i].de.xyz;
	output[i].de.w =  input[i].de.w;

	output[i].df.xyz = input[i].df.xyz;
	output[i].df.w =  -input[i].df.w;


	output[i].ec.xyz = -input[i].ec.xyz;
	output[i].ec.w =  input[i].ec.w;

	output[i].ed.xyz = -input[i].ed.xyz;
	output[i].ed.w =  input[i].ed.w;

	output[i].ee.xyz = -input[i].ee.xyz;
	output[i].ee.w =  input[i].ee.w;

	output[i].ef.xyz = input[i].ef.xyz;
	output[i].ef.w =  -input[i].ef.w;


	output[i].fc.xyz = input[i].fc.xyz;
	output[i].fc.w =  -input[i].fc.w;

	output[i].fd.xyz = input[i].fd.xyz;
	output[i].fd.w =  -input[i].fd.w;

	output[i].fe.xyz = input[i].fe.xyz;
	output[i].fe.w =  -input[i].fe.w;

	output[i].ff.xyz = -input[i].ff.xyz;
	output[i].ff.w =  input[i].ff.w;
}

__kernel void kernelmovelastindex_3(__global float444 * input,  __global out float444 * output){
	 uint i = get_global_id(0);
	output[i].cc.xyz = -input[i].cc.xyz;
	output[i].cc.w =  input[i].cc.w;

	output[i].cd.xyz = -input[i].cd.xyz;
	output[i].cd.w =  input[i].cd.w;

	output[i].ce.xyz = -input[i].ce.xyz;
	output[i].ce.w =  input[i].ce.w;

	output[i].cf.xyz = -input[i].cf.xyz;
	output[i].cf.w =  input[i].cf.w;


	output[i].dc.xyz = -input[i].dc.xyz;
	output[i].dc.w =  input[i].dc.w;

	output[i].dd.xyz = -input[i].dd.xyz;
	output[i].dd.w =  input[i].dd.w;

	output[i].de.xyz = -input[i].de.xyz;
	output[i].de.w =  input[i].de.w;

	output[i].df.xyz = -input[i].df.xyz;
	output[i].df.w =  input[i].df.w;


	output[i].ec.xyz = -input[i].ec.xyz;
	output[i].ec.w =  input[i].ec.w;

	output[i].ed.xyz = -input[i].ed.xyz;
	output[i].ed.w =  input[i].ed.w;

	output[i].ee.xyz = -input[i].ee.xyz;
	output[i].ee.w =  input[i].ee.w;

	output[i].ef.xyz = -input[i].ef.xyz;
	output[i].ef.w =  input[i].ef.w;

	output[i].fc.xyz = -input[i].fc.xyz;
	output[i].fc.w =  input[i].fc.w;

	output[i].fd.xyz = -input[i].fd.xyz;
	output[i].fd.w =  input[i].fd.w;

	output[i].fe.xyz = -input[i].fe.xyz;
	output[i].fe.w =  input[i].fe.w;

	output[i].ff.xyz = -input[i].ff.xyz;
	output[i].ff.w =  input[i].ff.w;
}


__kernel void kernelmovemiddleindex_3(__global float444 * input,  __global out float444 * output){
	 uint i = get_global_id(0);
	output[i].cc = - input[i].cc;
	output[i].cd = - input[i].cd;
	output[i].ce = - input[i].ce;
	output[i].cf =  input[i].cf;

	output[i].dc = - input[i].dc;
	output[i].dd = - input[i].dd;
	output[i].de = - input[i].de;
	output[i].df =  input[i].df;

	output[i].ec = - input[i].ec;
	output[i].ed = - input[i].ed;
	output[i].ee = - input[i].ee;
	output[i].ef =  input[i].ef;

	output[i].fc = - input[i].fc;
	output[i].fd = - input[i].fd;
	output[i].fe = - input[i].fe;
	output[i].ff =  input[i].ff;
}


__kernel void kernelmovefirstindex_3(__global float444 * input,  __global out float444 * output){
	 uint i = get_global_id(0);
	output[i].cc = - input[i].cc;
	output[i].cd = - input[i].cd;
	output[i].ce = - input[i].ce;
	output[i].cf = - input[i].cf;

	output[i].dc = - input[i].dc;
	output[i].dd = - input[i].dd;
	output[i].de = - input[i].de;
	output[i].df = - input[i].df;

	output[i].ec = - input[i].ec;
	output[i].ed = - input[i].ed;
	output[i].ee = - input[i].ee;
	output[i].ef = - input[i].ef;

	output[i].fc =  input[i].fc;
	output[i].fd =  input[i].fd;
	output[i].fe =  input[i].fe;
	output[i].ff =  input[i].ff;
}


/* lorentz boost: boost vector1 to vector 2*/
 __kernel void kernellorentzboost(__global float4 * vector1, __global float4 * vector2,  __global out float4 * output)
{
	 uint i = get_global_id(0);

	float bx=-vector2[i].x/vector2[i].w;
	float by=-vector2[i].y/vector2[i].w;
	float bz=-vector2[i].z/vector2[i].w;
	float bp2=bx*bx+by*by+bz*bz;
	float gamma=(bp2>=1)?0.0f:1.0f / sqrt(1.0f - bp2);
	float bgamma=gamma * gamma / (1.0f + gamma);

	output[i].x = (1+bgamma*bx*bx) *vector1[i].x+(bgamma*bx*by) *vector1[i].y+(bgamma*bx*bz) *vector1[i].z+(gamma*bx) *vector1[i].w;
	output[i].y =(bgamma*bx*by) *vector1[i].x+(1+bgamma*by*by) *vector1[i].y+(bgamma*by*bz) *vector1[i].z+(gamma*by) *vector1[i].w;
	output[i].z = (bgamma*bx*bz) *vector1[i].x+(bgamma*by*bz) *vector1[i].y+(1+bgamma*bz*bz)*vector1[i].z+(gamma*bz) *vector1[i].w;
	output[i].w = (gamma*bx) *vector1[i].x+(gamma*by) *vector1[i].y+(gamma*bz) *vector1[i].z+gamma *vector1[i].w;
}

 /* lorentz rotation: rotatez-axis to vector 2*/
 __kernel void kernellorentzrotation(__global float4 * vector1, __global float4 * vector2,  __global out float4 * output)
 {
	 uint i = get_global_id(0);
	float pt=sqrt(vector2[i].x*vector2[i].x+vector2[i].y*vector2[i].y);
	float pp=sqrt(vector2[i].x*vector2[i].x+vector2[i].y*vector2[i].y+vector2[i].z*vector2[i].z);

	float sp;
	float cp;
	float st;
	float ct;

	if(pt==0.0f){
		sp = 0.0f;
		cp = 1.0f;
	} else {
		sp = vector2[i].y/pt;
		cp = vector2[i].x/pt;
	}

	if(pp==0.0f){
		st = 0.0f;
		ct = 1.0f;
	} else {
		st = pt/pp;
		ct = vector2[i].z/pp;
	}

	output[i].x = cp*ct *vector1[i].x+sp*ct *vector1[i].y-st *vector1[i].z;
	output[i].y = -sp *vector1[i].x+cp *vector1[i].y;
	output[i].z = cp*st *vector1[i].x+sp*st*vector1[i].y+ct *vector1[i].z;
	output[i].w = vector1[i].w;


 }


 __kernel void kerneltensorphi_1(__global float4 * input,  __global out float * output)
{
	 uint i = get_global_id(0);

	float sign  =1.0f;
	float pt = sqrt(input[i].x*input[i].x+input[i].y*input[i].y);
	if(input[i].y < 0.0f)
		sign = -1.0f;
	if( pt!=0.0f){
		output[i] = sign*acos(input[i].x/pt);
	}else{
		output[i] =sign*1.5708f ;
	}
}


  __kernel void kerneltensorcostheta_1(__global float4 * input,   __global out float * output)
{
	 uint i = get_global_id(0);
	float p3= sqrt(input[i].x*input[i].x+input[i].y*input[i].y+input[i].z*input[i].z);
	if (p3!=0.0f){
	output[i] = input[i].z/p3;
	}
	else{
		output[i] =1.0f;
	}

}


/* Scalar product of vectors*/
__kernel void kerneltensorcontract_1_1(__global float4 * input1, __global float4 * input2,  __global out float * output)
{
	 uint i = get_global_id(0);
	float4 m = input1[i]*input2[i];
	output[i] = -m.x-m.y-m.z+m.w;
}
__kernel void kerneltensorcontract_1_f(__global float4 * input1, float4 input2,  __global out float * output)
{
	 uint i = get_global_id(0);
	float4 m = input1[i]*input2;
	output[i] = -m.x-m.y-m.z+m.w;
}

/* Contraction of vectors and tensors*/
__kernel void kerneltensorcontract_2_1(__global float44 * input1, __global float4 * input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);
	output[i].x = -input1[i].c.x *input2[i].x-input1[i].c.y *input2[i].y-input1[i].c.z *input2[i].z+input1[i].c.w *input2[i].w;
	output[i].y = -input1[i].d.x *input2[i].x-input1[i].d.y *input2[i].y-input1[i].d.z *input2[i].z+input1[i].d.w *input2[i].w;
	output[i].z = -input1[i].e.x *input2[i].x-input1[i].e.y *input2[i].y-input1[i].e.z *input2[i].z+input1[i].e.w *input2[i].w;
	output[i].w = -input1[i].f.x *input2[i].x-input1[i].f.y *input2[i].y-input1[i].f.z *input2[i].z+input1[i].f.w *input2[i].w;
}

__kernel void kerneltensorcontract_f44_1(float44 input1, __global float4 * input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);
	output[i].x = -input1.c.x *input2[i].x-input1.c.y *input2[i].y-input1.c.z *input2[i].z+input1.c.w *input2[i].w;
	output[i].y = -input1.d.x *input2[i].x-input1.d.y *input2[i].y-input1.d.z *input2[i].z+input1.d.w *input2[i].w;
	output[i].z = -input1.e.x *input2[i].x-input1.e.y *input2[i].y-input1.e.z *input2[i].z+input1.e.w *input2[i].w;
	output[i].w = -input1.f.x *input2[i].x-input1.f.y *input2[i].y-input1.f.z *input2[i].z+input1.f.w *input2[i].w;
}

__kernel void kerneltensorcontract_2_f4(__global float44 * input1, float4 input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);
	output[i].x = -input1[i].c.x *input2.x-input1[i].c.y *input2.y-input1[i].c.z *input2.z+input1[i].c.w *input2.w;
	output[i].y = -input1[i].d.x *input2.x-input1[i].d.y *input2.y-input1[i].d.z *input2.z+input1[i].d.w *input2.w;
	output[i].z = -input1[i].e.x *input2.x-input1[i].e.y *input2.y-input1[i].e.z *input2.z+input1[i].e.w *input2.w;
	output[i].w = -input1[i].f.x *input2.x-input1[i].f.y *input2.y-input1[i].f.z *input2.z+input1[i].f.w *input2.w;
}


/* Scalar product of second rank tensors*/
__kernel void kerneltensorcontract_2_2(__global float44 * input1, __global float44 * input2,  __global out float * output)
{
	 uint i = get_global_id(0);
	float44 m;
	m.c = input1[i].c*input2[i].c;
	m.d = input1[i].d*input2[i].d;
	m.e = input1[i].e*input2[i].e;
	m.f = input1[i].f*input2[i].f;
	output[i] = m.c.x+m.c.y+m.c.z-m.c.w +
			 m.d.x+m.d.y+m.d.z-m.d.w +
			 m.e.x+m.e.y+m.e.z-m.e.w -
			 m.f.x-m.f.y-m.f.z+m.f.w;
}

/* Scalar product of second rank tensors*/
__kernel void kerneltensorcontract_2_f44(__global float44 * input1, float44  input2,  __global out float * output)
{
	 uint i = get_global_id(0);
	float44 m;
	m.c = input1[i].c*input2.c;
	m.d = input1[i].d*input2.d;
	m.e = input1[i].e*input2.e;
	m.f = input1[i].f*input2.f;
	output[i] = m.c.x+m.c.y+m.c.z-m.c.w +
			 m.d.x+m.d.y+m.d.z-m.d.w +
			 m.e.x+m.e.y+m.e.z-m.e.w -
			 m.f.x-m.f.y-m.f.z+m.f.w;
}


/* contraction of second rank tensors, output is rank 2 tensor*/
__kernel void kerneltensorcontract2_2_2(__global float44 * p1, __global float44 * p2,  __global out float44 * output)
{
	 uint i = get_global_id(0);
        output[i].c.x = -p1[i].c.x*p2[i].c.x - p1[i].c.y*p2[i].c.y - p1[i].c.z*p2[i].c.z + p1[i].c.w*p2[i].c.w;
	output[i].c.y = -p1[i].c.x*p2[i].d.x - p1[i].c.y*p2[i].d.y - p1[i].c.z*p2[i].d.z + p1[i].c.w*p2[i].d.w;
	output[i].c.z = -p1[i].c.x*p2[i].e.x - p1[i].c.y*p2[i].e.y - p1[i].c.z*p2[i].e.z + p1[i].c.w*p2[i].e.w;
	output[i].c.w = -p1[i].c.x*p2[i].f.x - p1[i].c.y*p2[i].f.y - p1[i].c.z*p2[i].f.z + p1[i].c.w*p2[i].f.w;

        output[i].d.x = -p1[i].d.x*p2[i].c.x - p1[i].d.y*p2[i].c.y - p1[i].d.z*p2[i].c.z + p1[i].d.w*p2[i].c.w;
        output[i].d.y = -p1[i].d.x*p2[i].d.x - p1[i].d.y*p2[i].d.y - p1[i].d.z*p2[i].d.z + p1[i].d.w*p2[i].d.w;
        output[i].d.z = -p1[i].d.x*p2[i].e.x - p1[i].d.y*p2[i].e.y - p1[i].d.z*p2[i].e.z + p1[i].d.w*p2[i].e.w;
        output[i].d.w = -p1[i].d.x*p2[i].f.x - p1[i].d.y*p2[i].f.y - p1[i].d.z*p2[i].f.z + p1[i].d.w*p2[i].f.w;

        output[i].e.x = -p1[i].e.x*p2[i].c.x - p1[i].e.y*p2[i].c.y - p1[i].e.z*p2[i].c.z + p1[i].e.w*p2[i].c.w;
        output[i].e.y = -p1[i].e.x*p2[i].d.x - p1[i].e.y*p2[i].d.y - p1[i].e.z*p2[i].d.z + p1[i].e.w*p2[i].d.w;
        output[i].e.z = -p1[i].e.x*p2[i].e.x - p1[i].e.y*p2[i].e.y - p1[i].e.z*p2[i].e.z + p1[i].e.w*p2[i].e.w;
	output[i].e.w = -p1[i].e.x*p2[i].f.x - p1[i].e.y*p2[i].f.y - p1[i].e.z*p2[i].f.z + p1[i].e.w*p2[i].f.w;

        output[i].f.x = -p1[i].f.x*p2[i].c.x - p1[i].f.y*p2[i].c.y - p1[i].f.z*p2[i].c.z + p1[i].f.w*p2[i].c.w;
	output[i].f.y = -p1[i].f.x*p2[i].d.x - p1[i].f.y*p2[i].d.y - p1[i].f.z*p2[i].d.z + p1[i].f.w*p2[i].d.w;
	output[i].f.z = -p1[i].f.x*p2[i].e.x - p1[i].f.y*p2[i].e.y - p1[i].f.z*p2[i].e.z + p1[i].f.w*p2[i].e.w;
	output[i].f.w = -p1[i].f.x*p2[i].f.x - p1[i].f.y*p2[i].f.y - p1[i].f.z*p2[i].f.z + p1[i].f.w*p2[i].f.w;
 }

__kernel void kerneltensorcontract2_2_f44(__global float44 * p1, float44 p2,  __global out float44 * output)
{
	 uint i = get_global_id(0);
        output[i].c.x = -p1[i].c.x*p2.c.x - p1[i].c.y*p2.c.y - p1[i].c.z*p2.c.z + p1[i].c.w*p2.c.w;
	output[i].c.y = -p1[i].c.x*p2.d.x - p1[i].c.y*p2.d.y - p1[i].c.z*p2.d.z + p1[i].c.w*p2.d.w;
	output[i].c.z = -p1[i].c.x*p2.e.x - p1[i].c.y*p2.e.y - p1[i].c.z*p2.e.z + p1[i].c.w*p2.e.w;
	output[i].c.w = -p1[i].c.x*p2.f.x - p1[i].c.y*p2.f.y - p1[i].c.z*p2.f.z + p1[i].c.w*p2.f.w;

        output[i].d.x = -p1[i].d.x*p2.c.x - p1[i].d.y*p2.c.y - p1[i].d.z*p2.c.z + p1[i].d.w*p2.c.w;
        output[i].d.y = -p1[i].d.x*p2.d.x - p1[i].d.y*p2.d.y - p1[i].d.z*p2.d.z + p1[i].d.w*p2.d.w;
        output[i].d.z = -p1[i].d.x*p2.e.x - p1[i].d.y*p2.e.y - p1[i].d.z*p2.e.z + p1[i].d.w*p2.e.w;
        output[i].d.w = -p1[i].d.x*p2.f.x - p1[i].d.y*p2.f.y - p1[i].d.z*p2.f.z + p1[i].d.w*p2.f.w;

        output[i].e.x = -p1[i].e.x*p2.c.x - p1[i].e.y*p2.c.y - p1[i].e.z*p2.c.z + p1[i].e.w*p2.c.w;
        output[i].e.y = -p1[i].e.x*p2.d.x - p1[i].e.y*p2.d.y - p1[i].e.z*p2.d.z + p1[i].e.w*p2.d.w;
        output[i].e.z = -p1[i].e.x*p2.e.x - p1[i].e.y*p2.e.y - p1[i].e.z*p2.e.z + p1[i].e.w*p2.e.w;
	output[i].e.w = -p1[i].e.x*p2.f.x - p1[i].e.y*p2.f.y - p1[i].e.z*p2.f.z + p1[i].e.w*p2.f.w;

        output[i].f.x = -p1[i].f.x*p2.c.x - p1[i].f.y*p2.c.y - p1[i].f.z*p2.c.z + p1[i].f.w*p2.c.w;
	output[i].f.y = -p1[i].f.x*p2.d.x - p1[i].f.y*p2.d.y - p1[i].f.z*p2.d.z + p1[i].f.w*p2.d.w;
	output[i].f.z = -p1[i].f.x*p2.e.x - p1[i].f.y*p2.e.y - p1[i].f.z*p2.e.z + p1[i].f.w*p2.e.w;
	output[i].f.w = -p1[i].f.x*p2.f.x - p1[i].f.y*p2.f.y - p1[i].f.z*p2.f.z + p1[i].f.w*p2.f.w;
 }


__kernel void kerneltensorcontract2_f44_2(float44 p1, __global float44 * p2,  __global out float44 * output)
{
	 uint i = get_global_id(0);
	 output[i].c.x = -p1.c.x*p2[i].c.x - p1.c.y*p2[i].c.y - p1.c.z*p2[i].c.z + p1.c.w*p2[i].c.w;
	 output[i].c.y = -p1.c.x*p2[i].d.x - p1.c.y*p2[i].d.y - p1.c.z*p2[i].d.z + p1.c.w*p2[i].d.w;
	 output[i].c.z = -p1.c.x*p2[i].e.x - p1.c.y*p2[i].e.y - p1.c.z*p2[i].e.z + p1.c.w*p2[i].e.w;
	 output[i].c.w = -p1.c.x*p2[i].f.x - p1.c.y*p2[i].f.y - p1.c.z*p2[i].f.z + p1.c.w*p2[i].f.w;

	 output[i].d.x = -p1.d.x*p2[i].c.x - p1.d.y*p2[i].c.y - p1.d.z*p2[i].c.z + p1.d.w*p2[i].c.w;
	 output[i].d.y = -p1.d.x*p2[i].d.x - p1.d.y*p2[i].d.y - p1.d.z*p2[i].d.z + p1.d.w*p2[i].d.w;
	 output[i].d.z = -p1.d.x*p2[i].e.x - p1.d.y*p2[i].e.y - p1.d.z*p2[i].e.z + p1.d.w*p2[i].e.w;
	 output[i].d.w = -p1.d.x*p2[i].f.x - p1.d.y*p2[i].f.y - p1.d.z*p2[i].f.z + p1.d.w*p2[i].f.w;

	 output[i].e.x = -p1.e.x*p2[i].c.x - p1.e.y*p2[i].c.y - p1.e.z*p2[i].c.z + p1.e.w*p2[i].c.w;
	 output[i].e.y = -p1.e.x*p2[i].d.x - p1.e.y*p2[i].d.y - p1.e.z*p2[i].d.z + p1.e.w*p2[i].d.w;
	 output[i].e.z = -p1.e.x*p2[i].e.x - p1.e.y*p2[i].e.y - p1.e.z*p2[i].e.z + p1.e.w*p2[i].e.w;
	 output[i].e.w = -p1.e.x*p2[i].f.x - p1.e.y*p2[i].f.y - p1.e.z*p2[i].f.z + p1.e.w*p2[i].f.w;

	 output[i].f.x = -p1.f.x*p2[i].c.x - p1.f.y*p2[i].c.y - p1.f.z*p2[i].c.z + p1.f.w*p2[i].c.w;
	 output[i].f.y = -p1.f.x*p2[i].d.x - p1.f.y*p2[i].d.y - p1.f.z*p2[i].d.z + p1.f.w*p2[i].d.w;
	 output[i].f.z = -p1.f.x*p2[i].e.x - p1.f.y*p2[i].e.y - p1.f.z*p2[i].e.z + p1.f.w*p2[i].e.w;
	 output[i].f.w = -p1.f.x*p2[i].f.x - p1.f.y*p2[i].f.y - p1.f.z*p2[i].f.z + p1.f.w*p2[i].f.w;
 }


/* contraction of third rank tensors and third rank tensors*/
__kernel void kerneltensorcontract_3_3(__global float444 * input1, __global float444 * input2,  __global out float * output)
{
	 uint i = get_global_id(0);

  output[i] = -input1[i].cc.x*input2[i].cc.x - input1[i].dc.x*input2[i].dc.x - input1[i].ec.x*input2[i].ec.x + input1[i].fc.x*input2[i].fc.x
		   -input1[i].cd.x*input2[i].cd.x - input1[i].dd.x*input2[i].dd.x - input1[i].ed.x*input2[i].ed.x + input1[i].fd.x*input2[i].fd.x
           -input1[i].ce.x*input2[i].ce.x - input1[i].de.x*input2[i].de.x - input1[i].ee.x*input2[i].ee.x + input1[i].fe.x*input2[i].fe.x
           +input1[i].cf.x*input2[i].cf.x + input1[i].df.x*input2[i].df.x + input1[i].ef.x*input2[i].ef.x - input1[i].ff.x*input2[i].ff.x

		   -input1[i].cc.y*input2[i].cc.y - input1[i].dc.y*input2[i].dc.y - input1[i].ec.y*input2[i].ec.y + input1[i].fc.y*input2[i].fc.y
		   -input1[i].cd.y*input2[i].cd.y - input1[i].dd.y*input2[i].dd.y - input1[i].ed.y*input2[i].ed.y + input1[i].fd.y*input2[i].fd.y
		   -input1[i].ce.y*input2[i].ce.y - input1[i].de.y*input2[i].de.y - input1[i].ee.y*input2[i].ee.y + input1[i].fe.y*input2[i].fe.y
		   +input1[i].cf.y*input2[i].cf.y + input1[i].df.y*input2[i].df.y + input1[i].ef.y*input2[i].ef.y - input1[i].ff.y*input2[i].ff.y

           -input1[i].cc.z*input2[i].cc.z - input1[i].dc.z*input2[i].dc.z - input1[i].ec.z*input2[i].ec.z + input1[i].fc.z*input2[i].fc.z
		   -input1[i].cd.z*input2[i].cd.z - input1[i].dd.z*input2[i].dd.z - input1[i].ed.z*input2[i].ed.z + input1[i].fd.z*input2[i].fd.z
		   -input1[i].ce.z*input2[i].ce.z - input1[i].de.z*input2[i].de.z - input1[i].ee.z*input2[i].ee.z + input1[i].fe.z*input2[i].fe.z
		   +input1[i].cf.z*input2[i].cf.z + input1[i].df.z*input2[i].df.z + input1[i].ef.z*input2[i].ef.z - input1[i].ff.z*input2[i].ff.z

		   +input1[i].cc.w*input2[i].cc.w + input1[i].dc.w*input2[i].dc.w + input1[i].ec.w*input2[i].ec.w - input1[i].fc.w*input2[i].fc.w
		   +input1[i].cd.w*input2[i].cd.w + input1[i].dd.w*input2[i].dd.w + input1[i].ed.w*input2[i].ed.w - input1[i].fd.w*input2[i].fd.w
		   +input1[i].ce.w*input2[i].ce.w + input1[i].de.w*input2[i].de.w + input1[i].ee.w*input2[i].ee.w - input1[i].fe.w*input2[i].fe.w
		   -input1[i].cf.w*input2[i].cf.w - input1[i].df.w*input2[i].df.w - input1[i].ef.w*input2[i].ef.w + input1[i].ff.w*input2[i].ff.w;

}

__kernel void kerneltensorcontract_3_f444(__global float444 * input1, float444 input2,  __global out float * output)
{
	 uint i = get_global_id(0);

  output[i] = -input1[i].cc.x*input2.cc.x - input1[i].dc.x*input2.dc.x - input1[i].ec.x*input2.ec.x + input1[i].fc.x*input2.fc.x
		   -input1[i].cd.x*input2.cd.x - input1[i].dd.x*input2.dd.x - input1[i].ed.x*input2.ed.x + input1[i].fd.x*input2.fd.x
           -input1[i].ce.x*input2.ce.x - input1[i].de.x*input2.de.x - input1[i].ee.x*input2.ee.x + input1[i].fe.x*input2.fe.x
           +input1[i].cf.x*input2.cf.x + input1[i].df.x*input2.df.x + input1[i].ef.x*input2.ef.x - input1[i].ff.x*input2.ff.x

		   -input1[i].cc.y*input2.cc.y - input1[i].dc.y*input2.dc.y - input1[i].ec.y*input2.ec.y + input1[i].fc.y*input2.fc.y
		   -input1[i].cd.y*input2.cd.y - input1[i].dd.y*input2.dd.y - input1[i].ed.y*input2.ed.y + input1[i].fd.y*input2.fd.y
		   -input1[i].ce.y*input2.ce.y - input1[i].de.y*input2.de.y - input1[i].ee.y*input2.ee.y + input1[i].fe.y*input2.fe.y
		   +input1[i].cf.y*input2.cf.y + input1[i].df.y*input2.df.y + input1[i].ef.y*input2.ef.y - input1[i].ff.y*input2.ff.y

           -input1[i].cc.z*input2.cc.z - input1[i].dc.z*input2.dc.z - input1[i].ec.z*input2.ec.z + input1[i].fc.z*input2.fc.z
		   -input1[i].cd.z*input2.cd.z - input1[i].dd.z*input2.dd.z - input1[i].ed.z*input2.ed.z + input1[i].fd.z*input2.fd.z
		   -input1[i].ce.z*input2.ce.z - input1[i].de.z*input2.de.z - input1[i].ee.z*input2.ee.z + input1[i].fe.z*input2.fe.z
		   +input1[i].cf.z*input2.cf.z + input1[i].df.z*input2.df.z + input1[i].ef.z*input2.ef.z - input1[i].ff.z*input2.ff.z

		   +input1[i].cc.w*input2.cc.w + input1[i].dc.w*input2.dc.w + input1[i].ec.w*input2.ec.w - input1[i].fc.w*input2.fc.w
		   +input1[i].cd.w*input2.cd.w + input1[i].dd.w*input2.dd.w + input1[i].ed.w*input2.ed.w - input1[i].fd.w*input2.fd.w
		   +input1[i].ce.w*input2.ce.w + input1[i].de.w*input2.de.w + input1[i].ee.w*input2.ee.w - input1[i].fe.w*input2.fe.w
		   -input1[i].cf.w*input2.cf.w - input1[i].df.w*input2.df.w - input1[i].ef.w*input2.ef.w + input1[i].ff.w*input2.ff.w;

}






/* Contraction of third rank 3 stream  and vector stream*/
__kernel void kerneltensorcontract_3_1(__global float444 * input1, __global float4 * input2,  __global out float44 * output)
{
	 uint i = get_global_id(0);

    output[i].c.x = -input1[i].cc.x*input2[i].x - input1[i].cc.y*input2[i].y - input1[i].cc.z*input2[i].z + input1[i].cc.w*input2[i].w;
    output[i].c.y = -input1[i].cd.x*input2[i].x - input1[i].cd.y*input2[i].y - input1[i].cd.z*input2[i].z + input1[i].cd.w*input2[i].w;
    output[i].c.z = -input1[i].ce.x*input2[i].x - input1[i].ce.y*input2[i].y - input1[i].ce.z*input2[i].z + input1[i].ce.w*input2[i].w;
    output[i].c.w = -input1[i].cf.x*input2[i].x - input1[i].cf.y*input2[i].y - input1[i].cf.z*input2[i].z + input1[i].cf.w*input2[i].w;

    output[i].d.x = -input1[i].dc.x*input2[i].x - input1[i].dc.y*input2[i].y - input1[i].dc.z*input2[i].z + input1[i].dc.w*input2[i].w;
    output[i].d.y = -input1[i].dd.x*input2[i].x - input1[i].dd.y*input2[i].y - input1[i].dd.z*input2[i].z + input1[i].dd.w*input2[i].w;
    output[i].d.z = -input1[i].de.x*input2[i].x - input1[i].de.y*input2[i].y - input1[i].de.z*input2[i].z + input1[i].de.w*input2[i].w;
    output[i].d.w = -input1[i].df.x*input2[i].x - input1[i].df.y*input2[i].y - input1[i].df.z*input2[i].z + input1[i].df.w*input2[i].w;

    output[i].e.x = -input1[i].ec.x*input2[i].x - input1[i].ec.y*input2[i].y - input1[i].ec.z*input2[i].z + input1[i].ec.w*input2[i].w;
    output[i].e.y = -input1[i].ed.x*input2[i].x - input1[i].ed.y*input2[i].y - input1[i].ed.z*input2[i].z + input1[i].ed.w*input2[i].w;
    output[i].e.z = -input1[i].ee.x*input2[i].x - input1[i].ee.y*input2[i].y - input1[i].ee.z*input2[i].z + input1[i].ee.w*input2[i].w;
    output[i].e.w = -input1[i].ef.x*input2[i].x - input1[i].ef.y*input2[i].y - input1[i].ef.z*input2[i].z + input1[i].ef.w*input2[i].w;

    output[i].f.x = -input1[i].fc.x*input2[i].x - input1[i].fc.y*input2[i].y - input1[i].fc.z*input2[i].z + input1[i].fc.w*input2[i].w;
    output[i].f.y = -input1[i].fd.x*input2[i].x - input1[i].fd.y*input2[i].y - input1[i].fd.z*input2[i].z + input1[i].fd.w*input2[i].w;
    output[i].f.z = -input1[i].fe.x*input2[i].x - input1[i].fe.y*input2[i].y - input1[i].fe.z*input2[i].z + input1[i].fe.w*input2[i].w;
    output[i].f.w = -input1[i].ff.x*input2[i].x - input1[i].ff.y*input2[i].y - input1[i].ff.z*input2[i].z + input1[i].ff.w*input2[i].w;
}

__kernel void kerneltensorcontract_f444_1(float444 input1, __global float4 * input2,  __global out float44 * output)
{
	 uint i = get_global_id(0);

    output[i].c.x = -input1.cc.x*input2[i].x - input1.cc.y*input2[i].y - input1.cc.z*input2[i].z + input1.cc.w*input2[i].w;
    output[i].c.y = -input1.cd.x*input2[i].x - input1.cd.y*input2[i].y - input1.cd.z*input2[i].z + input1.cd.w*input2[i].w;
    output[i].c.z = -input1.ce.x*input2[i].x - input1.ce.y*input2[i].y - input1.ce.z*input2[i].z + input1.ce.w*input2[i].w;
    output[i].c.w = -input1.cf.x*input2[i].x - input1.cf.y*input2[i].y - input1.cf.z*input2[i].z + input1.cf.w*input2[i].w;

    output[i].d.x = -input1.dc.x*input2[i].x - input1.dc.y*input2[i].y - input1.dc.z*input2[i].z + input1.dc.w*input2[i].w;
    output[i].d.y = -input1.dd.x*input2[i].x - input1.dd.y*input2[i].y - input1.dd.z*input2[i].z + input1.dd.w*input2[i].w;
    output[i].d.z = -input1.de.x*input2[i].x - input1.de.y*input2[i].y - input1.de.z*input2[i].z + input1.de.w*input2[i].w;
    output[i].d.w = -input1.df.x*input2[i].x - input1.df.y*input2[i].y - input1.df.z*input2[i].z + input1.df.w*input2[i].w;

    output[i].e.x = -input1.ec.x*input2[i].x - input1.ec.y*input2[i].y - input1.ec.z*input2[i].z + input1.ec.w*input2[i].w;
    output[i].e.y = -input1.ed.x*input2[i].x - input1.ed.y*input2[i].y - input1.ed.z*input2[i].z + input1.ed.w*input2[i].w;
    output[i].e.z = -input1.ee.x*input2[i].x - input1.ee.y*input2[i].y - input1.ee.z*input2[i].z + input1.ee.w*input2[i].w;
    output[i].e.w = -input1.ef.x*input2[i].x - input1.ef.y*input2[i].y - input1.ef.z*input2[i].z + input1.ef.w*input2[i].w;

    output[i].f.x = -input1.fc.x*input2[i].x - input1.fc.y*input2[i].y - input1.fc.z*input2[i].z + input1.fc.w*input2[i].w;
    output[i].f.y = -input1.fd.x*input2[i].x - input1.fd.y*input2[i].y - input1.fd.z*input2[i].z + input1.fd.w*input2[i].w;
    output[i].f.z = -input1.fe.x*input2[i].x - input1.fe.y*input2[i].y - input1.fe.z*input2[i].z + input1.fe.w*input2[i].w;
    output[i].f.w = -input1.ff.x*input2[i].x - input1.ff.y*input2[i].y - input1.ff.z*input2[i].z + input1.ff.w*input2[i].w;
}


/* Contraction of third rank 3 stream and vector const*/
__kernel void kerneltensorcontract_3_f4(__global float444 * input1, float4 input2,  __global out float44 * output)
{
	 uint i = get_global_id(0);

    output[i].c.x = -input1[i].cc.x*input2.x - input1[i].cc.y*input2.y - input1[i].cc.z*input2.z + input1[i].cc.w*input2.w;
    output[i].c.y = -input1[i].cd.x*input2.x - input1[i].cd.y*input2.y - input1[i].cd.z*input2.z + input1[i].cd.w*input2.w;
    output[i].c.z = -input1[i].ce.x*input2.x - input1[i].ce.y*input2.y - input1[i].ce.z*input2.z + input1[i].ce.w*input2.w;
    output[i].c.w = -input1[i].cf.x*input2.x - input1[i].cf.y*input2.y - input1[i].cf.z*input2.z + input1[i].cf.w*input2.w;

	output[i].d.x = -input1[i].dc.x*input2.x - input1[i].dc.y*input2.y - input1[i].dc.z*input2.z + input1[i].dc.w*input2.w;
    output[i].d.y = -input1[i].dd.x*input2.x - input1[i].dd.y*input2.y - input1[i].dd.z*input2.z + input1[i].dd.w*input2.w;
    output[i].d.z = -input1[i].de.x*input2.x - input1[i].de.y*input2.y - input1[i].de.z*input2.z + input1[i].de.w*input2.w;
    output[i].d.w = -input1[i].df.x*input2.x - input1[i].df.y*input2.y - input1[i].df.z*input2.z + input1[i].df.w*input2.w;

	output[i].e.x = -input1[i].ec.x*input2.x - input1[i].ec.y*input2.y - input1[i].ec.z*input2.z + input1[i].ec.w*input2.w;
    output[i].e.y = -input1[i].ed.x*input2.x - input1[i].ed.y*input2.y - input1[i].ed.z*input2.z + input1[i].ed.w*input2.w;
    output[i].e.z = -input1[i].ee.x*input2.x - input1[i].ee.y*input2.y - input1[i].ee.z*input2.z + input1[i].ee.w*input2.w;
    output[i].e.w = -input1[i].ef.x*input2.x - input1[i].ef.y*input2.y - input1[i].ef.z*input2.z + input1[i].ef.w*input2.w;


    output[i].f.x = -input1[i].fc.x*input2.x - input1[i].fc.y*input2.y - input1[i].fc.z*input2.z + input1[i].fc.w*input2.w;
    output[i].f.y = -input1[i].fd.x*input2.x - input1[i].fd.y*input2.y - input1[i].fd.z*input2.z + input1[i].fd.w*input2.w;
    output[i].f.z = -input1[i].fe.x*input2.x - input1[i].fe.y*input2.y - input1[i].fe.z*input2.z + input1[i].fe.w*input2.w;
    output[i].f.w = -input1[i].ff.x*input2.x - input1[i].ff.y*input2.y - input1[i].ff.z*input2.z + input1[i].ff.w*input2.w;

}


/* Contraction of third rank 3 stream and rank 2 stream*/
__kernel void kerneltensorcontract_3_2(__global float444 * input1, __global float44 * input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);

    output[i].x = input1[i].cc.x*input2[i].c.x + input1[i].cd.x*input2[i].d.x + input1[i].ce.x*input2[i].e.x - input1[i].cf.x*input2[i].f.x
              +input1[i].cc.y*input2[i].c.y + input1[i].cd.y*input2[i].d.y + input1[i].ce.y*input2[i].e.y - input1[i].cf.y*input2[i].f.y
              +input1[i].cc.z*input2[i].c.z + input1[i].cd.z*input2[i].d.z + input1[i].ce.z*input2[i].e.z - input1[i].cf.z*input2[i].f.z
              -input1[i].cc.w*input2[i].c.w - input1[i].cd.w*input2[i].d.w - input1[i].ce.w*input2[i].e.w + input1[i].cf.w*input2[i].f.w;

    output[i].y = input1[i].dc.x*input2[i].c.x + input1[i].dd.x*input2[i].d.x + input1[i].de.x*input2[i].e.x - input1[i].df.x*input2[i].f.x
              +input1[i].dc.y*input2[i].c.y + input1[i].dd.y*input2[i].d.y + input1[i].de.y*input2[i].e.y - input1[i].df.y*input2[i].f.y
              +input1[i].dc.z*input2[i].c.z + input1[i].dd.z*input2[i].d.z + input1[i].de.z*input2[i].e.z - input1[i].df.z*input2[i].f.z
              -input1[i].dc.w*input2[i].c.w - input1[i].dd.w*input2[i].d.w - input1[i].de.w*input2[i].e.w + input1[i].df.w*input2[i].f.w;

    output[i].z = input1[i].ec.x*input2[i].c.x + input1[i].ed.x*input2[i].d.x + input1[i].ee.x*input2[i].e.x - input1[i].ef.x*input2[i].f.x
              +input1[i].ec.y*input2[i].c.y + input1[i].ed.y*input2[i].d.y + input1[i].ee.y*input2[i].e.y - input1[i].ef.y*input2[i].f.y
              +input1[i].ec.z*input2[i].c.z + input1[i].ed.z*input2[i].d.z + input1[i].ee.z*input2[i].e.z - input1[i].ef.z*input2[i].f.z
              -input1[i].ec.w*input2[i].c.w - input1[i].ed.w*input2[i].d.w - input1[i].ee.w*input2[i].e.w + input1[i].ef.w*input2[i].f.w;

    output[i].w = input1[i].fc.x*input2[i].c.x + input1[i].fd.x*input2[i].d.x + input1[i].fe.x*input2[i].e.x - input1[i].ff.x*input2[i].f.x
              +input1[i].fc.y*input2[i].c.y + input1[i].fd.y*input2[i].d.y + input1[i].fe.y*input2[i].e.y - input1[i].ff.y*input2[i].f.y
              +input1[i].fc.z*input2[i].c.z + input1[i].fd.z*input2[i].d.z + input1[i].fe.z*input2[i].e.z - input1[i].ff.z*input2[i].f.z
              -input1[i].fc.w*input2[i].c.w - input1[i].fd.w*input2[i].d.w - input1[i].fe.w*input2[i].e.w + input1[i].ff.w*input2[i].f.w;

}


__kernel void kerneltensorcontract_3_f44(__global float444 * input1, float44 input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);

    output[i].x = input1[i].cc.x*input2.c.x + input1[i].cd.x*input2.d.x + input1[i].ce.x*input2.e.x - input1[i].cf.x*input2.f.x
              +input1[i].cc.y*input2.c.y + input1[i].cd.y*input2.d.y + input1[i].ce.y*input2.e.y - input1[i].cf.y*input2.f.y
              +input1[i].cc.z*input2.c.z + input1[i].cd.z*input2.d.z + input1[i].ce.z*input2.e.z - input1[i].cf.z*input2.f.z
              -input1[i].cc.w*input2.c.w - input1[i].cd.w*input2.d.w - input1[i].ce.w*input2.e.w + input1[i].cf.w*input2.f.w;

    output[i].y = input1[i].dc.x*input2.c.x + input1[i].dd.x*input2.d.x + input1[i].de.x*input2.e.x - input1[i].df.x*input2.f.x
              +input1[i].dc.y*input2.c.y + input1[i].dd.y*input2.d.y + input1[i].de.y*input2.e.y - input1[i].df.y*input2.f.y
              +input1[i].dc.z*input2.c.z + input1[i].dd.z*input2.d.z + input1[i].de.z*input2.e.z - input1[i].df.z*input2.f.z
              -input1[i].dc.w*input2.c.w - input1[i].dd.w*input2.d.w - input1[i].de.w*input2.e.w + input1[i].df.w*input2.f.w;

    output[i].z = input1[i].ec.x*input2.c.x + input1[i].ed.x*input2.d.x + input1[i].ee.x*input2.e.x - input1[i].ef.x*input2.f.x
              +input1[i].ec.y*input2.c.y + input1[i].ed.y*input2.d.y + input1[i].ee.y*input2.e.y - input1[i].ef.y*input2.f.y
              +input1[i].ec.z*input2.c.z + input1[i].ed.z*input2.d.z + input1[i].ee.z*input2.e.z - input1[i].ef.z*input2.f.z
              -input1[i].ec.w*input2.c.w - input1[i].ed.w*input2.d.w - input1[i].ee.w*input2.e.w + input1[i].ef.w*input2.f.w;

    output[i].w = input1[i].fc.x*input2.c.x + input1[i].fd.x*input2.d.x + input1[i].fe.x*input2.e.x - input1[i].ff.x*input2.f.x
              +input1[i].fc.y*input2.c.y + input1[i].fd.y*input2.d.y + input1[i].fe.y*input2.e.y - input1[i].ff.y*input2.f.y
              +input1[i].fc.z*input2.c.z + input1[i].fd.z*input2.d.z + input1[i].fe.z*input2.e.z - input1[i].ff.z*input2.f.z
              -input1[i].fc.w*input2.c.w - input1[i].fd.w*input2.d.w - input1[i].fe.w*input2.e.w + input1[i].ff.w*input2.f.w;

}

/* added by mintj */
__kernel void kerneltensorcontract_2_3_sign(__global float44 * input1, __global float444 * input2, int sign, __global out float4 * output)
{
	 uint i = get_global_id(0);

    output[i].x = input2[i].cc.x*input1[i].c.x + input2[i].cd.x*input1[i].d.x + input2[i].ce.x*input1[i].e.x - input2[i].cf.x*input1[i].f.x
              +input2[i].cc.y*input1[i].c.y + input2[i].cd.y*input1[i].d.y + input2[i].ce.y*input1[i].e.y - input2[i].cf.y*input1[i].f.y
              +input2[i].cc.z*input1[i].c.z + input2[i].cd.z*input1[i].d.z + input2[i].ce.z*input1[i].e.z - input2[i].cf.z*input1[i].f.z
              -input2[i].cc.w*input1[i].c.w - input2[i].cd.w*input1[i].d.w - input2[i].ce.w*input1[i].e.w + input2[i].cf.w*input1[i].f.w;

    output[i].y = input2[i].dc.x*input1[i].c.x + input2[i].dd.x*input1[i].d.x + input2[i].de.x*input1[i].e.x - input2[i].df.x*input1[i].f.x
              +input2[i].dc.y*input1[i].c.y + input2[i].dd.y*input1[i].d.y + input2[i].de.y*input1[i].e.y - input2[i].df.y*input1[i].f.y
              +input2[i].dc.z*input1[i].c.z + input2[i].dd.z*input1[i].d.z + input2[i].de.z*input1[i].e.z - input2[i].df.z*input1[i].f.z
              -input2[i].dc.w*input1[i].c.w - input2[i].dd.w*input1[i].d.w - input2[i].de.w*input1[i].e.w + input2[i].df.w*input1[i].f.w;

    output[i].z = input2[i].ec.x*input1[i].c.x + input2[i].ed.x*input1[i].d.x + input2[i].ee.x*input1[i].e.x - input2[i].ef.x*input1[i].f.x
              +input2[i].ec.y*input1[i].c.y + input2[i].ed.y*input1[i].d.y + input2[i].ee.y*input1[i].e.y - input2[i].ef.y*input1[i].f.y
              +input2[i].ec.z*input1[i].c.z + input2[i].ed.z*input1[i].d.z + input2[i].ee.z*input1[i].e.z - input2[i].ef.z*input1[i].f.z
              -input2[i].ec.w*input1[i].c.w - input2[i].ed.w*input1[i].d.w - input2[i].ee.w*input1[i].e.w + input2[i].ef.w*input1[i].f.w;

    output[i].w = input2[i].fc.x*input1[i].c.x + input2[i].fd.x*input1[i].d.x + input2[i].fe.x*input1[i].e.x - input2[i].ff.x*input1[i].f.x
              +input2[i].fc.y*input1[i].c.y + input2[i].fd.y*input1[i].d.y + input2[i].fe.y*input1[i].e.y - input2[i].ff.y*input1[i].f.y
              +input2[i].fc.z*input1[i].c.z + input2[i].fd.z*input1[i].d.z + input2[i].fe.z*input1[i].e.z - input2[i].ff.z*input1[i].f.z
              -input2[i].fc.w*input1[i].c.w - input2[i].fd.w*input1[i].d.w - input2[i].fe.w*input1[i].e.w + input2[i].ff.w*input1[i].f.w;
	output[i].x *= sign;
	output[i].y *= sign;
	output[i].z *= sign;
	output[i].w *= sign;
}

__kernel void kerneltensorcontract_2_3(__global float44 * input1, __global float444 * input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);

    output[i].x = input2[i].cc.x*input1[i].c.x + input2[i].cd.x*input1[i].d.x + input2[i].ce.x*input1[i].e.x - input2[i].cf.x*input1[i].f.x
              +input2[i].cc.y*input1[i].c.y + input2[i].cd.y*input1[i].d.y + input2[i].ce.y*input1[i].e.y - input2[i].cf.y*input1[i].f.y
              +input2[i].cc.z*input1[i].c.z + input2[i].cd.z*input1[i].d.z + input2[i].ce.z*input1[i].e.z - input2[i].cf.z*input1[i].f.z
              -input2[i].cc.w*input1[i].c.w - input2[i].cd.w*input1[i].d.w - input2[i].ce.w*input1[i].e.w + input2[i].cf.w*input1[i].f.w;

    output[i].y = input2[i].dc.x*input1[i].c.x + input2[i].dd.x*input1[i].d.x + input2[i].de.x*input1[i].e.x - input2[i].df.x*input1[i].f.x
              +input2[i].dc.y*input1[i].c.y + input2[i].dd.y*input1[i].d.y + input2[i].de.y*input1[i].e.y - input2[i].df.y*input1[i].f.y
              +input2[i].dc.z*input1[i].c.z + input2[i].dd.z*input1[i].d.z + input2[i].de.z*input1[i].e.z - input2[i].df.z*input1[i].f.z
              -input2[i].dc.w*input1[i].c.w - input2[i].dd.w*input1[i].d.w - input2[i].de.w*input1[i].e.w + input2[i].df.w*input1[i].f.w;

    output[i].z = input2[i].ec.x*input1[i].c.x + input2[i].ed.x*input1[i].d.x + input2[i].ee.x*input1[i].e.x - input2[i].ef.x*input1[i].f.x
              +input2[i].ec.y*input1[i].c.y + input2[i].ed.y*input1[i].d.y + input2[i].ee.y*input1[i].e.y - input2[i].ef.y*input1[i].f.y
              +input2[i].ec.z*input1[i].c.z + input2[i].ed.z*input1[i].d.z + input2[i].ee.z*input1[i].e.z - input2[i].ef.z*input1[i].f.z
              -input2[i].ec.w*input1[i].c.w - input2[i].ed.w*input1[i].d.w - input2[i].ee.w*input1[i].e.w + input2[i].ef.w*input1[i].f.w;

    output[i].w = input2[i].fc.x*input1[i].c.x + input2[i].fd.x*input1[i].d.x + input2[i].fe.x*input1[i].e.x - input2[i].ff.x*input1[i].f.x
              +input2[i].fc.y*input1[i].c.y + input2[i].fd.y*input1[i].d.y + input2[i].fe.y*input1[i].e.y - input2[i].ff.y*input1[i].f.y
              +input2[i].fc.z*input1[i].c.z + input2[i].fd.z*input1[i].d.z + input2[i].fe.z*input1[i].e.z - input2[i].ff.z*input1[i].f.z
              -input2[i].fc.w*input1[i].c.w - input2[i].fd.w*input1[i].d.w - input2[i].fe.w*input1[i].e.w + input2[i].ff.w*input1[i].f.w;

}


__kernel void kerneltensorcontract_2_f444(__global float44 * input1, float444 input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);

    output[i].x = input2.cc.x*input1[i].c.x + input2.cd.x*input1[i].d.x + input2.ce.x*input1[i].e.x - input2.cf.x*input1[i].f.x
              +input2.cc.y*input1[i].c.y + input2.cd.y*input1[i].d.y + input2.ce.y*input1[i].e.y - input2.cf.y*input1[i].f.y
              +input2.cc.z*input1[i].c.z + input2.cd.z*input1[i].d.z + input2.ce.z*input1[i].e.z - input2.cf.z*input1[i].f.z
              -input2.cc.w*input1[i].c.w - input2.cd.w*input1[i].d.w - input2.ce.w*input1[i].e.w + input2.cf.w*input1[i].f.w;

    output[i].y = input2.dc.x*input1[i].c.x + input2.dd.x*input1[i].d.x + input2.de.x*input1[i].e.x - input2.df.x*input1[i].f.x
              +input2.dc.y*input1[i].c.y + input2.dd.y*input1[i].d.y + input2.de.y*input1[i].e.y - input2.df.y*input1[i].f.y
              +input2.dc.z*input1[i].c.z + input2.dd.z*input1[i].d.z + input2.de.z*input1[i].e.z - input2.df.z*input1[i].f.z
              -input2.dc.w*input1[i].c.w - input2.dd.w*input1[i].d.w - input2.de.w*input1[i].e.w + input2.df.w*input1[i].f.w;

    output[i].z = input2.ec.x*input1[i].c.x + input2.ed.x*input1[i].d.x + input2.ee.x*input1[i].e.x - input2.ef.x*input1[i].f.x
              +input2.ec.y*input1[i].c.y + input2.ed.y*input1[i].d.y + input2.ee.y*input1[i].e.y - input2.ef.y*input1[i].f.y
              +input2.ec.z*input1[i].c.z + input2.ed.z*input1[i].d.z + input2.ee.z*input1[i].e.z - input2.ef.z*input1[i].f.z
              -input2.ec.w*input1[i].c.w - input2.ed.w*input1[i].d.w - input2.ee.w*input1[i].e.w + input2.ef.w*input1[i].f.w;

    output[i].w = input2.fc.x*input1[i].c.x + input2.fd.x*input1[i].d.x + input2.fe.x*input1[i].e.x - input2.ff.x*input1[i].f.x
              +input2.fc.y*input1[i].c.y + input2.fd.y*input1[i].d.y + input2.fe.y*input1[i].e.y - input2.ff.y*input1[i].f.y
              +input2.fc.z*input1[i].c.z + input2.fd.z*input1[i].d.z + input2.fe.z*input1[i].e.z - input2.ff.z*input1[i].f.z
              -input2.fc.w*input1[i].c.w - input2.fd.w*input1[i].d.w - input2.fe.w*input1[i].e.w + input2.ff.w*input1[i].f.w;

}

__kernel void kerneltensorcontract_f44_3(float44 input1, __global float444 * input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);

    output[i].x = input2[i].cc.x*input1.c.x + input2[i].cd.x*input1.d.x + input2[i].ce.x*input1.e.x - input2[i].cf.x*input1.f.x
              +input2[i].cc.y*input1.c.y + input2[i].cd.y*input1.d.y + input2[i].ce.y*input1.e.y - input2[i].cf.y*input1.f.y
              +input2[i].cc.z*input1.c.z + input2[i].cd.z*input1.d.z + input2[i].ce.z*input1.e.z - input2[i].cf.z*input1.f.z
              -input2[i].cc.w*input1.c.w - input2[i].cd.w*input1.d.w - input2[i].ce.w*input1.e.w + input2[i].cf.w*input1.f.w;

    output[i].y = input2[i].dc.x*input1.c.x + input2[i].dd.x*input1.d.x + input2[i].de.x*input1.e.x - input2[i].df.x*input1.f.x
              +input2[i].dc.y*input1.c.y + input2[i].dd.y*input1.d.y + input2[i].de.y*input1.e.y - input2[i].df.y*input1.f.y
              +input2[i].dc.z*input1.c.z + input2[i].dd.z*input1.d.z + input2[i].de.z*input1.e.z - input2[i].df.z*input1.f.z
              -input2[i].dc.w*input1.c.w - input2[i].dd.w*input1.d.w - input2[i].de.w*input1.e.w + input2[i].df.w*input1.f.w;

    output[i].z = input2[i].ec.x*input1.c.x + input2[i].ed.x*input1.d.x + input2[i].ee.x*input1.e.x - input2[i].ef.x*input1.f.x
              +input2[i].ec.y*input1.c.y + input2[i].ed.y*input1.d.y + input2[i].ee.y*input1.e.y - input2[i].ef.y*input1.f.y
              +input2[i].ec.z*input1.c.z + input2[i].ed.z*input1.d.z + input2[i].ee.z*input1.e.z - input2[i].ef.z*input1.f.z
              -input2[i].ec.w*input1.c.w - input2[i].ed.w*input1.d.w - input2[i].ee.w*input1.e.w + input2[i].ef.w*input1.f.w;

    output[i].w = input2[i].fc.x*input1.c.x + input2[i].fd.x*input1.d.x + input2[i].fe.x*input1.e.x - input2[i].ff.x*input1.f.x
              +input2[i].fc.y*input1.c.y + input2[i].fd.y*input1.d.y + input2[i].fe.y*input1.e.y - input2[i].ff.y*input1.f.y
              +input2[i].fc.z*input1.c.z + input2[i].fd.z*input1.d.z + input2[i].fe.z*input1.e.z - input2[i].ff.z*input1.f.z
              -input2[i].fc.w*input1.c.w - input2[i].fd.w*input1.d.w - input2[i].fe.w*input1.e.w + input2[i].ff.w*input1.f.w;

}



__kernel void kerneltensorcontract_f444_2(float444 input1, __global float44 * input2,  __global out float4 * output)
{
	 uint i = get_global_id(0);

    output[i].x = input1.cc.x*input2[i].c.x + input1.cd.x*input2[i].d.x + input1.ce.x*input2[i].e.x - input1.cf.x*input2[i].f.x
              +input1.cc.y*input2[i].c.y + input1.cd.y*input2[i].d.y + input1.ce.y*input2[i].e.y - input1.cf.y*input2[i].f.y
              +input1.cc.z*input2[i].c.z + input1.cd.z*input2[i].d.z + input1.ce.z*input2[i].e.z - input1.cf.z*input2[i].f.z
              -input1.cc.w*input2[i].c.w - input1.cd.w*input2[i].d.w - input1.ce.w*input2[i].e.w + input1.cf.w*input2[i].f.w;

    output[i].y = input1.dc.x*input2[i].c.x + input1.dd.x*input2[i].d.x + input1.de.x*input2[i].e.x - input1.df.x*input2[i].f.x
              +input1.dc.y*input2[i].c.y + input1.dd.y*input2[i].d.y + input1.de.y*input2[i].e.y - input1.df.y*input2[i].f.y
              +input1.dc.z*input2[i].c.z + input1.dd.z*input2[i].d.z + input1.de.z*input2[i].e.z - input1.df.z*input2[i].f.z
              -input1.dc.w*input2[i].c.w - input1.dd.w*input2[i].d.w - input1.de.w*input2[i].e.w + input1.df.w*input2[i].f.w;

    output[i].z = input1.ec.x*input2[i].c.x + input1.ed.x*input2[i].d.x + input1.ee.x*input2[i].e.x - input1.ef.x*input2[i].f.x
              +input1.ec.y*input2[i].c.y + input1.ed.y*input2[i].d.y + input1.ee.y*input2[i].e.y - input1.ef.y*input2[i].f.y
              +input1.ec.z*input2[i].c.z + input1.ed.z*input2[i].d.z + input1.ee.z*input2[i].e.z - input1.ef.z*input2[i].f.z
              -input1.ec.w*input2[i].c.w - input1.ed.w*input2[i].d.w - input1.ee.w*input2[i].e.w + input1.ef.w*input2[i].f.w;

    output[i].w = input1.fc.x*input2[i].c.x + input1.fd.x*input2[i].d.x + input1.fe.x*input2[i].e.x - input1.ff.x*input2[i].f.x
              +input1.fc.y*input2[i].c.y + input1.fd.y*input2[i].d.y + input1.fe.y*input2[i].e.y - input1.ff.y*input2[i].f.y
              +input1.fc.z*input2[i].c.z + input1.fd.z*input2[i].d.z + input1.fe.z*input2[i].e.z - input1.ff.z*input2[i].f.z
              -input1.fc.w*input2[i].c.w - input1.fd.w*input2[i].d.w - input1.fe.w*input2[i].e.w + input1.ff.w*input2[i].f.w;

}


/* contraction of third rank 3 stream and rank 3 stream, output is rank 2 stream*/
__kernel void kerneltensorcontract2_3_3(__global float444 * input1, __global float444 * input2,   __global out float44 * output){
	 uint i = get_global_id(0);

     output[i].c.x = input1[i].cc.x*input2[i].cc.x + input1[i].cc.y*input2[i].cc.y + input1[i].cc.z*input2[i].cc.z - input1[i].cc.w*input2[i].cc.w
		 +input1[i].cd.x*input2[i].cd.x + input1[i].cd.y*input2[i].cd.y + input1[i].cd.z*input2[i].cd.z - input1[i].cd.w*input2[i].cd.w
		 +input1[i].ce.x*input2[i].ce.x + input1[i].ce.y*input2[i].ce.y + input1[i].ce.z*input2[i].ce.z - input1[i].ce.w*input2[i].ce.w
		 -input1[i].cf.x*input2[i].cf.x - input1[i].cf.y*input2[i].cf.y - input1[i].cf.z*input2[i].cf.z + input1[i].cf.w*input2[i].cf.w;

     output[i].c.y = input1[i].cc.x*input2[i].dc.x + input1[i].cc.y*input2[i].dc.y + input1[i].cc.z*input2[i].dc.z - input1[i].cc.w*input2[i].dc.w
		 +input1[i].cd.x*input2[i].dd.x + input1[i].cd.y*input2[i].dd.y + input1[i].cd.z*input2[i].dd.z - input1[i].cd.w*input2[i].dd.w
		 +input1[i].ce.x*input2[i].de.x + input1[i].ce.y*input2[i].de.y + input1[i].ce.z*input2[i].de.z - input1[i].ce.w*input2[i].de.w
		 -input1[i].cf.x*input2[i].df.x - input1[i].cf.y*input2[i].df.y - input1[i].cf.z*input2[i].df.z + input1[i].cf.w*input2[i].df.w;

     output[i].c.z = input1[i].cc.x*input2[i].ec.x + input1[i].cc.y*input2[i].ec.y + input1[i].cc.z*input2[i].ec.z - input1[i].cc.w*input2[i].ec.w
		 +input1[i].cd.x*input2[i].ed.x + input1[i].cd.y*input2[i].ed.y + input1[i].cd.z*input2[i].ed.z - input1[i].cd.w*input2[i].ed.w
		 +input1[i].ce.x*input2[i].ee.x + input1[i].ce.y*input2[i].ee.y + input1[i].ce.z*input2[i].ee.z - input1[i].ce.w*input2[i].ee.w
		 -input1[i].cf.x*input2[i].ef.x - input1[i].cf.y*input2[i].ef.y - input1[i].cf.z*input2[i].ef.z + input1[i].cf.w*input2[i].ef.w;

     output[i].c.w = input1[i].cc.x*input2[i].fc.x + input1[i].cc.y*input2[i].fc.y + input1[i].cc.z*input2[i].fc.z - input1[i].cc.w*input2[i].fc.w
		 +input1[i].cd.x*input2[i].fd.x + input1[i].cd.y*input2[i].fd.y + input1[i].cd.z*input2[i].fd.z - input1[i].cd.w*input2[i].fd.w
		 +input1[i].ce.x*input2[i].fe.x + input1[i].ce.y*input2[i].fe.y + input1[i].ce.z*input2[i].fe.z - input1[i].ce.w*input2[i].fe.w
		 -input1[i].cf.x*input2[i].ff.x - input1[i].cf.y*input2[i].ff.y - input1[i].cf.z*input2[i].ff.z + input1[i].cf.w*input2[i].ff.w;


     output[i].d.x = input1[i].dc.x*input2[i].cc.x + input1[i].dc.y*input2[i].cc.y + input1[i].dc.z*input2[i].cc.z - input1[i].dc.w*input2[i].cc.w
		 +input1[i].dd.x*input2[i].cd.x + input1[i].dd.y*input2[i].cd.y + input1[i].dd.z*input2[i].cd.z - input1[i].dd.w*input2[i].cd.w
		 +input1[i].de.x*input2[i].ce.x + input1[i].de.y*input2[i].ce.y + input1[i].de.z*input2[i].ce.z - input1[i].de.w*input2[i].ce.w
		 -input1[i].df.x*input2[i].cf.x - input1[i].df.y*input2[i].cf.y - input1[i].df.z*input2[i].cf.z + input1[i].df.w*input2[i].cf.w;

     output[i].d.y = input1[i].dc.x*input2[i].dc.x + input1[i].dc.y*input2[i].dc.y + input1[i].dc.z*input2[i].dc.z - input1[i].dc.w*input2[i].dc.w
		 +input1[i].dd.x*input2[i].dd.x + input1[i].dd.y*input2[i].dd.y + input1[i].dd.z*input2[i].dd.z - input1[i].dd.w*input2[i].dd.w
		 +input1[i].de.x*input2[i].de.x + input1[i].de.y*input2[i].de.y + input1[i].de.z*input2[i].de.z - input1[i].de.w*input2[i].de.w
		 -input1[i].df.x*input2[i].df.x - input1[i].df.y*input2[i].df.y - input1[i].df.z*input2[i].df.z + input1[i].df.w*input2[i].df.w;

     output[i].d.z = input1[i].dc.x*input2[i].ec.x + input1[i].dc.y*input2[i].ec.y + input1[i].dc.z*input2[i].ec.z - input1[i].dc.w*input2[i].ec.w
		 +input1[i].dd.x*input2[i].ed.x + input1[i].dd.y*input2[i].ed.y + input1[i].dd.z*input2[i].ed.z - input1[i].dd.w*input2[i].ed.w
		 +input1[i].de.x*input2[i].ee.x + input1[i].de.y*input2[i].ee.y + input1[i].de.z*input2[i].ee.z - input1[i].de.w*input2[i].ee.w
		 -input1[i].df.x*input2[i].ef.x - input1[i].df.y*input2[i].ef.y - input1[i].df.z*input2[i].ef.z + input1[i].df.w*input2[i].ef.w;

     output[i].d.w = input1[i].dc.x*input2[i].fc.x + input1[i].dc.y*input2[i].fc.y + input1[i].dc.z*input2[i].fc.z - input1[i].dc.w*input2[i].fc.w
		 +input1[i].dd.x*input2[i].fd.x + input1[i].dd.y*input2[i].fd.y + input1[i].dd.z*input2[i].fd.z - input1[i].dd.w*input2[i].fd.w
		 +input1[i].de.x*input2[i].fe.x + input1[i].de.y*input2[i].fe.y + input1[i].de.z*input2[i].fe.z - input1[i].de.w*input2[i].fe.w
		 -input1[i].df.x*input2[i].ff.x - input1[i].df.y*input2[i].ff.y - input1[i].df.z*input2[i].ff.z + input1[i].df.w*input2[i].ff.w;


     output[i].e.x = input1[i].ec.x*input2[i].cc.x + input1[i].ec.y*input2[i].cc.y + input1[i].ec.z*input2[i].cc.z - input1[i].ec.w*input2[i].cc.w
		 +input1[i].ed.x*input2[i].cd.x + input1[i].ed.y*input2[i].cd.y + input1[i].ed.z*input2[i].cd.z - input1[i].ed.w*input2[i].cd.w
		 +input1[i].ee.x*input2[i].ce.x + input1[i].ee.y*input2[i].ce.y + input1[i].ee.z*input2[i].ce.z - input1[i].ee.w*input2[i].ce.w
		 -input1[i].ef.x*input2[i].cf.x - input1[i].ef.y*input2[i].cf.y - input1[i].ef.z*input2[i].cf.z + input1[i].ef.w*input2[i].cf.w;

     output[i].e.y = input1[i].ec.x*input2[i].dc.x + input1[i].ec.y*input2[i].dc.y + input1[i].ec.z*input2[i].dc.z - input1[i].ec.w*input2[i].dc.w
		 +input1[i].ed.x*input2[i].dd.x + input1[i].ed.y*input2[i].dd.y + input1[i].ed.z*input2[i].dd.z - input1[i].ed.w*input2[i].dd.w
		 +input1[i].ee.x*input2[i].de.x + input1[i].ee.y*input2[i].de.y + input1[i].ee.z*input2[i].de.z - input1[i].ee.w*input2[i].de.w
		 -input1[i].ef.x*input2[i].df.x - input1[i].ef.y*input2[i].df.y - input1[i].ef.z*input2[i].df.z + input1[i].ef.w*input2[i].df.w;

     output[i].e.z = input1[i].ec.x*input2[i].ec.x + input1[i].ec.y*input2[i].ec.y + input1[i].ec.z*input2[i].ec.z - input1[i].ec.w*input2[i].ec.w
		 +input1[i].ed.x*input2[i].ed.x + input1[i].ed.y*input2[i].ed.y + input1[i].ed.z*input2[i].ed.z - input1[i].ed.w*input2[i].ed.w
		 +input1[i].ee.x*input2[i].ee.x + input1[i].ee.y*input2[i].ee.y + input1[i].ee.z*input2[i].ee.z - input1[i].ee.w*input2[i].ee.w
		 -input1[i].ef.x*input2[i].ef.x - input1[i].ef.y*input2[i].ef.y - input1[i].ef.z*input2[i].ef.z + input1[i].ef.w*input2[i].ef.w;

     output[i].e.w = input1[i].ec.x*input2[i].fc.x + input1[i].ec.y*input2[i].fc.y + input1[i].ec.z*input2[i].fc.z - input1[i].ec.w*input2[i].fc.w
		 +input1[i].ed.x*input2[i].fd.x + input1[i].ed.y*input2[i].fd.y + input1[i].ed.z*input2[i].fd.z - input1[i].ed.w*input2[i].fd.w
		 +input1[i].ee.x*input2[i].fe.x + input1[i].ee.y*input2[i].fe.y + input1[i].ee.z*input2[i].fe.z - input1[i].ee.w*input2[i].fe.w
		 -input1[i].ef.x*input2[i].ff.x - input1[i].ef.y*input2[i].ff.y - input1[i].ef.z*input2[i].ff.z + input1[i].ef.w*input2[i].ff.w;


     output[i].f.x = input1[i].fc.x*input2[i].cc.x + input1[i].fc.y*input2[i].cc.y + input1[i].fc.z*input2[i].cc.z - input1[i].fc.w*input2[i].cc.w
		 +input1[i].fd.x*input2[i].cd.x + input1[i].fd.y*input2[i].cd.y + input1[i].fd.z*input2[i].cd.z - input1[i].fd.w*input2[i].cd.w
		 +input1[i].fe.x*input2[i].ce.x + input1[i].fe.y*input2[i].ce.y + input1[i].fe.z*input2[i].ce.z - input1[i].fe.w*input2[i].ce.w
		 -input1[i].ff.x*input2[i].cf.x - input1[i].ff.y*input2[i].cf.y - input1[i].ff.z*input2[i].cf.z + input1[i].ff.w*input2[i].cf.w;

     output[i].f.y = input1[i].fc.x*input2[i].dc.x + input1[i].fc.y*input2[i].dc.y + input1[i].fc.z*input2[i].dc.z - input1[i].fc.w*input2[i].dc.w
		 +input1[i].fd.x*input2[i].dd.x + input1[i].fd.y*input2[i].dd.y + input1[i].fd.z*input2[i].dd.z - input1[i].fd.w*input2[i].dd.w
		 +input1[i].fe.x*input2[i].de.x + input1[i].fe.y*input2[i].de.y + input1[i].fe.z*input2[i].de.z - input1[i].fe.w*input2[i].de.w
		 -input1[i].ff.x*input2[i].df.x - input1[i].ff.y*input2[i].df.y - input1[i].ff.z*input2[i].df.z + input1[i].ff.w*input2[i].df.w;

     output[i].f.z = input1[i].fc.x*input2[i].ec.x + input1[i].fc.y*input2[i].ec.y + input1[i].fc.z*input2[i].ec.z - input1[i].fc.w*input2[i].ec.w
		 +input1[i].fd.x*input2[i].ed.x + input1[i].fd.y*input2[i].ed.y + input1[i].fd.z*input2[i].ed.z - input1[i].fd.w*input2[i].ed.w
		 +input1[i].fe.x*input2[i].ee.x + input1[i].fe.y*input2[i].ee.y + input1[i].fe.z*input2[i].ee.z - input1[i].fe.w*input2[i].ee.w
		 -input1[i].ff.x*input2[i].ef.x - input1[i].ff.y*input2[i].ef.y - input1[i].ff.z*input2[i].ef.z + input1[i].ff.w*input2[i].ef.w;

     output[i].f.w = input1[i].fc.x*input2[i].fc.x + input1[i].fc.y*input2[i].fc.y + input1[i].fc.z*input2[i].fc.z - input1[i].fc.w*input2[i].fc.w
		 +input1[i].fd.x*input2[i].fd.x + input1[i].fd.y*input2[i].fd.y + input1[i].fd.z*input2[i].fd.z - input1[i].fd.w*input2[i].fd.w
		 +input1[i].fe.x*input2[i].fe.x + input1[i].fe.y*input2[i].fe.y + input1[i].fe.z*input2[i].fe.z - input1[i].fe.w*input2[i].fe.w
		 -input1[i].ff.x*input2[i].ff.x - input1[i].ff.y*input2[i].ff.y - input1[i].ff.z*input2[i].ff.z + input1[i].ff.w*input2[i].ff.w;
 }



