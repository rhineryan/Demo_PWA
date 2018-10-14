/* Summing.cl  -- kernels for summing streams
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

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

__kernel void int_sum_16(__global int * in, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < 16; i++){
		 sum += (double)(in[pos*16+i]);
	 }
	 result[pos] = sum;
}
__kernel void int_sum_N(__global int * in, uint offset, uint resultoffset, uint n, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < n; i++){
		 sum += (double)(in[pos*n+i+offset]);
	 }
	 result[pos+resultoffset] = sum;
}
__kernel void int_sum2d_16(__global int * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j]);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void int_sum2d_N(__global int * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset]);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
__kernel void int_sum2d_16_weighted(__global float4 * weights, __global int * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j]);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void int_sum2d_N_weighted(__global float4 * weights,__global int * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset]);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
__kernel void float_sum_16(__global float * in, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < 16; i++){
		 sum += (double)(in[pos*16+i]);
	 }
	 result[pos] = sum;
}
__kernel void float_sum_N(__global float * in, uint offset, uint resultoffset, uint n, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < n; i++){
		 sum += (double)(in[pos*n+i+offset]);
	 }
	 result[pos+resultoffset] = sum;
}
__kernel void float_sum2d_16(__global float * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j]);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void float_sum2d_N(__global float * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset]);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
__kernel void float_sum2d_16_weighted(__global float4 * weights, __global float * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j]);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void float_sum2d_N_weighted(__global float4 * weights,__global float * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset]);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
__kernel void double_sum_16(__global double * in, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < 16; i++){
		 sum += (double)(in[pos*16+i]);
	 }
	 result[pos] = sum;
}
__kernel void double_sum_N(__global double * in, uint offset, uint resultoffset, uint n, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < n; i++){
		 sum += (double)(in[pos*n+i+offset]);
	 }
	 result[pos+resultoffset] = sum;
}
__kernel void double_sum2d_16(__global double * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j]);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void double_sum2d_N(__global double * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset]);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
__kernel void double_sum2d_16_weighted(__global float4 * weights, __global double * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j]);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void double_sum2d_N_weighted(__global float4 * weights,__global double * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset]);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
__kernel void double2_sum_16(__global double2 * in, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < 16; i++){
		 sum += (double)(in[pos*16+i].x);
		 sum += (double)(in[pos*16+i].y);
	 }
	 result[pos] = sum;
}
__kernel void double2_sum_N(__global double2 * in, uint offset, uint resultoffset, uint n, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < n; i++){
		 sum += (double)(in[pos*n+i+offset].x);
		 sum += (double)(in[pos*n+i+offset].y);
	 }
	 result[pos+resultoffset] = sum;
}
__kernel void double2_sumcomponents_16(__global double2 * in, __global out double * result_0, __global out double * result_1){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum_0 = 0.0;
	 double sum_1 = 0.0;
	 for(i=0; i < 16; i++){
		 sum_0 += (double)(in[pos*16+i].x);
		 sum_1 += (double)(in[pos*16+i].y);
	 }
	 result_0[pos] = sum_0;
	 result_1[pos] = sum_1;
}


__kernel void double2_sumcomponents_N(__global double2 * in, uint offset, uint resultoffset, uint n, __global out double * result_0, __global out double * result_1){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum_0 = 0.0;
	 double sum_1 = 0.0;
	 for(i=0; i < n; i++){
		 sum_0 += (double)(in[pos*n+i+offset].x);
		 sum_1 += (double)(in[pos*n+i+offset].y);
	 }
	 result_0[pos+resultoffset] = sum_0;
	 result_1[pos+resultoffset] = sum_1;
}


__kernel void double2_sumcomponents_weighted_16(__global double2 * in, __global float * weights, __global out double * result_0, __global out double * result_1){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum_0 = 0.0;
	 double sum_1 = 0.0;
	 for(i=0; i < 16; i++){
		 sum_0 += (double)(in[pos*16+i].x*weights[pos*16+i]);
		 sum_1 += (double)(in[pos*16+i].y*weights[pos*16+i]);
	 }
	 result_0[pos] = sum_0;
	 result_1[pos] = sum_1;
}


__kernel void double2_sumcomponents_weighted_N(__global double2 * in, __global float * weights, uint offset, uint resultoffset, uint n, __global out double * result_0, __global out double * result_1){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum_0 = 0.0;
	 double sum_1 = 0.0;
	 for(i=0; i < n; i++){
		 sum_0 += (double)(in[pos*n+i].x*weights[pos*n+i+offset]);
		 sum_1 += (double)(in[pos*n+i].y*weights[pos*n+i+offset]);
	 }
	 result_0[pos+resultoffset] = sum_0;
	 result_1[pos+resultoffset] = sum_1;
}


__kernel void double2_sum2d_16(__global double2 * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].y);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void double2_sum2d_N(__global double2 * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].y);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
__kernel void double2_sum2d_16_weighted(__global float4 * weights, __global double2 * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].y);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void double2_sum2d_N_weighted(__global float4 * weights,__global double2 * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].y);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
__kernel void float2_sum_16(__global float2 * in, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < 16; i++){
		 sum += (double)(in[pos*16+i].x);
		 sum += (double)(in[pos*16+i].y);
	 }
	 result[pos] = sum;
}
__kernel void float2_sum_N(__global float2 * in, uint offset, uint resultoffset, uint n, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < n; i++){
		 sum += (double)(in[pos*n+i+offset].x);
		 sum += (double)(in[pos*n+i+offset].y);
	 }
	 result[pos+resultoffset] = sum;
}
__kernel void float2_sumcomponents_16(__global float2 * in, __global out double * result_0, __global out double * result_1){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum_0 = 0.0;
	 double sum_1 = 0.0;
	 for(i=0; i < 16; i++){
		 sum_0 += (double)(in[pos*16+i].x);
		 sum_1 += (double)(in[pos*16+i].y);
	 }
	 result_0[pos] = sum_0;
	 result_1[pos] = sum_1;
}


__kernel void float2_sumcomponents_N(__global float2 * in, uint offset, uint resultoffset, uint n, __global out double * result_0, __global out double * result_1){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum_0 = 0.0;
	 double sum_1 = 0.0;
	 for(i=0; i < n; i++){
		 sum_0 += (double)(in[pos*n+i+offset].x);
		 sum_1 += (double)(in[pos*n+i+offset].y);
	 }
	 result_0[pos+resultoffset] = sum_0;
	 result_1[pos+resultoffset] = sum_1;
}


__kernel void float2_sumcomponents_weighted_16(__global float2 * in, __global float * weights, __global out double * result_0, __global out double * result_1){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum_0 = 0.0;
	 double sum_1 = 0.0;
	 for(i=0; i < 16; i++){
		 sum_0 += (double)(in[pos*16+i].x*weights[pos*16+i]);
		 sum_1 += (double)(in[pos*16+i].y*weights[pos*16+i]);
	 }
	 result_0[pos] = sum_0;
	 result_1[pos] = sum_1;
}


__kernel void float2_sumcomponents_weighted_N(__global float2 * in, __global float * weights, uint offset, uint resultoffset, uint n, __global out double * result_0, __global out double * result_1){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum_0 = 0.0;
	 double sum_1 = 0.0;
	 for(i=0; i < n; i++){
		 sum_0 += (double)(in[pos*n+i].x*weights[pos*n+i+offset]);
		 sum_1 += (double)(in[pos*n+i].y*weights[pos*n+i+offset]);
	 }
	 result_0[pos+resultoffset] = sum_0;
	 result_1[pos+resultoffset] = sum_1;
}


__kernel void float2_sum2d_16(__global float2 * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].y);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void float2_sum2d_N(__global float2 * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].y);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
__kernel void float2_sum2d_16_weighted(__global float4 * weights, __global float2 * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].y);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void float2_sum2d_N_weighted(__global float4 * weights,__global float2 * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].y);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
__kernel void float4_sum_16(__global float4 * in, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < 16; i++){
		 sum += (double)(in[pos*16+i].x);
		 sum += (double)(in[pos*16+i].y);
		 sum += (double)(in[pos*16+i].z);
		 sum += (double)(in[pos*16+i].w);
	 }
	 result[pos] = sum;
}
__kernel void float4_sum_N(__global float4 * in, uint offset, uint resultoffset, uint n, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < n; i++){
		 sum += (double)(in[pos*n+i+offset].x);
		 sum += (double)(in[pos*n+i+offset].y);
		 sum += (double)(in[pos*n+i+offset].z);
		 sum += (double)(in[pos*n+i+offset].w);
	 }
	 result[pos+resultoffset] = sum;
}
__kernel void float4_sumcomponents_16(__global float4 * in, __global out double * result_0, __global out double * result_1, __global out double * result_2, __global out double * result_3){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum_0 = 0.0;
	 double sum_1 = 0.0;
	 double sum_2 = 0.0;
	 double sum_3 = 0.0;
	 for(i=0; i < 16; i++){
		 sum_0 += (double)(in[pos*16+i].x);
		 sum_1 += (double)(in[pos*16+i].y);
		 sum_2 += (double)(in[pos*16+i].z);
		 sum_3 += (double)(in[pos*16+i].w);
	 }
	 result_0[pos] = sum_0;
	 result_1[pos] = sum_1;
	 result_2[pos] = sum_2;
	 result_3[pos] = sum_3;
}


__kernel void float4_sumcomponents_N(__global float4 * in, uint offset, uint resultoffset, uint n, __global out double * result_0, __global out double * result_1, __global out double * result_2, __global out double * result_3){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum_0 = 0.0;
	 double sum_1 = 0.0;
	 double sum_2 = 0.0;
	 double sum_3 = 0.0;
	 for(i=0; i < n; i++){
		 sum_0 += (double)(in[pos*n+i+offset].x);
		 sum_1 += (double)(in[pos*n+i+offset].y);
		 sum_2 += (double)(in[pos*n+i+offset].z);
		 sum_3 += (double)(in[pos*n+i+offset].w);
	 }
	 result_0[pos+resultoffset] = sum_0;
	 result_1[pos+resultoffset] = sum_1;
	 result_2[pos+resultoffset] = sum_2;
	 result_3[pos+resultoffset] = sum_3;
}


__kernel void float4_sumcomponents_weighted_16(__global float4 * in, __global float * weights, __global out double * result_0, __global out double * result_1, __global out double * result_2, __global out double * result_3){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum_0 = 0.0;
	 double sum_1 = 0.0;
	 double sum_2 = 0.0;
	 double sum_3 = 0.0;
	 for(i=0; i < 16; i++){
		 sum_0 += (double)(in[pos*16+i].x*weights[pos*16+i]);
		 sum_1 += (double)(in[pos*16+i].y*weights[pos*16+i]);
		 sum_2 += (double)(in[pos*16+i].z*weights[pos*16+i]);
		 sum_3 += (double)(in[pos*16+i].w*weights[pos*16+i]);
	 }
	 result_0[pos] = sum_0;
	 result_1[pos] = sum_1;
	 result_2[pos] = sum_2;
	 result_3[pos] = sum_3;
}


__kernel void float4_sumcomponents_weighted_N(__global float4 * in, __global float * weights, uint offset, uint resultoffset, uint n, __global out double * result_0, __global out double * result_1, __global out double * result_2, __global out double * result_3){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum_0 = 0.0;
	 double sum_1 = 0.0;
	 double sum_2 = 0.0;
	 double sum_3 = 0.0;
	 for(i=0; i < n; i++){
		 sum_0 += (double)(in[pos*n+i].x*weights[pos*n+i+offset]);
		 sum_1 += (double)(in[pos*n+i].y*weights[pos*n+i+offset]);
		 sum_2 += (double)(in[pos*n+i].z*weights[pos*n+i+offset]);
		 sum_3 += (double)(in[pos*n+i].w*weights[pos*n+i+offset]);
	 }
	 result_0[pos+resultoffset] = sum_0;
	 result_1[pos+resultoffset] = sum_1;
	 result_2[pos+resultoffset] = sum_2;
	 result_3[pos+resultoffset] = sum_3;
}


__kernel void float4_sum2d_16(__global float4 * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].w);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void float4_sum2d_N(__global float4 * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].w);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
__kernel void float4_sum2d_16_weighted(__global float4 * weights, __global float4 * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].w);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void float4_sum2d_N_weighted(__global float4 * weights,__global float4 * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].w);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
__kernel void float44_sum_16(__global float44 * in, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < 16; i++){
		 sum += (double)(in[pos*16+i].c.x);
		 sum += (double)(in[pos*16+i].c.y);
		 sum += (double)(in[pos*16+i].c.z);
		 sum += (double)(in[pos*16+i].c.w);
		 sum += (double)(in[pos*16+i].d.x);
		 sum += (double)(in[pos*16+i].d.y);
		 sum += (double)(in[pos*16+i].d.z);
		 sum += (double)(in[pos*16+i].d.w);
		 sum += (double)(in[pos*16+i].e.x);
		 sum += (double)(in[pos*16+i].e.y);
		 sum += (double)(in[pos*16+i].e.z);
		 sum += (double)(in[pos*16+i].e.w);
		 sum += (double)(in[pos*16+i].f.x);
		 sum += (double)(in[pos*16+i].f.y);
		 sum += (double)(in[pos*16+i].f.z);
		 sum += (double)(in[pos*16+i].f.w);
	 }
	 result[pos] = sum;
}
__kernel void float44_sum_N(__global float44 * in, uint offset, uint resultoffset, uint n, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < n; i++){
		 sum += (double)(in[pos*n+i+offset].c.x);
		 sum += (double)(in[pos*n+i+offset].c.y);
		 sum += (double)(in[pos*n+i+offset].c.z);
		 sum += (double)(in[pos*n+i+offset].c.w);
		 sum += (double)(in[pos*n+i+offset].d.x);
		 sum += (double)(in[pos*n+i+offset].d.y);
		 sum += (double)(in[pos*n+i+offset].d.z);
		 sum += (double)(in[pos*n+i+offset].d.w);
		 sum += (double)(in[pos*n+i+offset].e.x);
		 sum += (double)(in[pos*n+i+offset].e.y);
		 sum += (double)(in[pos*n+i+offset].e.z);
		 sum += (double)(in[pos*n+i+offset].e.w);
		 sum += (double)(in[pos*n+i+offset].f.x);
		 sum += (double)(in[pos*n+i+offset].f.y);
		 sum += (double)(in[pos*n+i+offset].f.z);
		 sum += (double)(in[pos*n+i+offset].f.w);
	 }
	 result[pos+resultoffset] = sum;
}
__kernel void float44_sum2d_16(__global float44 * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j].c.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].c.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].c.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].c.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].d.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].d.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].d.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].d.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].e.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].e.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].e.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].e.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].f.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].f.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].f.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].f.w);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void float44_sum2d_N(__global float44 * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].c.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].c.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].c.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].c.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].d.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].d.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].d.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].d.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].e.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].e.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].e.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].e.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].f.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].f.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].f.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].f.w);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
__kernel void float44_sum2d_16_weighted(__global float4 * weights, __global float44 * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j].c.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].c.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].c.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].c.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].d.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].d.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].d.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].d.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].e.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].e.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].e.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].e.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].f.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].f.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].f.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].f.w*weights[pos*16+i].w);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void float44_sum2d_N_weighted(__global float4 * weights,__global float44 * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].c.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].c.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].c.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].c.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].d.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].d.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].d.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].d.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].e.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].e.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].e.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].e.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].f.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].f.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].f.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].f.w*weights[pos*n+i].w);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
__kernel void float444_sum_16(__global float444 * in, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < 16; i++){
		 sum += (double)(in[pos*16+i].cc.x);
		 sum += (double)(in[pos*16+i].cc.y);
		 sum += (double)(in[pos*16+i].cc.z);
		 sum += (double)(in[pos*16+i].cc.w);
		 sum += (double)(in[pos*16+i].cd.x);
		 sum += (double)(in[pos*16+i].cd.y);
		 sum += (double)(in[pos*16+i].cd.z);
		 sum += (double)(in[pos*16+i].cd.w);
		 sum += (double)(in[pos*16+i].ce.x);
		 sum += (double)(in[pos*16+i].ce.y);
		 sum += (double)(in[pos*16+i].ce.z);
		 sum += (double)(in[pos*16+i].ce.w);
		 sum += (double)(in[pos*16+i].cf.x);
		 sum += (double)(in[pos*16+i].cf.y);
		 sum += (double)(in[pos*16+i].cf.z);
		 sum += (double)(in[pos*16+i].cf.w);
		 sum += (double)(in[pos*16+i].dc.x);
		 sum += (double)(in[pos*16+i].dc.y);
		 sum += (double)(in[pos*16+i].dc.z);
		 sum += (double)(in[pos*16+i].dc.w);
		 sum += (double)(in[pos*16+i].dd.x);
		 sum += (double)(in[pos*16+i].dd.y);
		 sum += (double)(in[pos*16+i].dd.z);
		 sum += (double)(in[pos*16+i].dd.w);
		 sum += (double)(in[pos*16+i].de.x);
		 sum += (double)(in[pos*16+i].de.y);
		 sum += (double)(in[pos*16+i].de.z);
		 sum += (double)(in[pos*16+i].de.w);
		 sum += (double)(in[pos*16+i].df.x);
		 sum += (double)(in[pos*16+i].df.y);
		 sum += (double)(in[pos*16+i].df.z);
		 sum += (double)(in[pos*16+i].df.w);
		 sum += (double)(in[pos*16+i].ec.x);
		 sum += (double)(in[pos*16+i].ec.y);
		 sum += (double)(in[pos*16+i].ec.z);
		 sum += (double)(in[pos*16+i].ec.w);
		 sum += (double)(in[pos*16+i].ed.x);
		 sum += (double)(in[pos*16+i].ed.y);
		 sum += (double)(in[pos*16+i].ed.z);
		 sum += (double)(in[pos*16+i].ed.w);
		 sum += (double)(in[pos*16+i].ee.x);
		 sum += (double)(in[pos*16+i].ee.y);
		 sum += (double)(in[pos*16+i].ee.z);
		 sum += (double)(in[pos*16+i].ee.w);
		 sum += (double)(in[pos*16+i].ef.x);
		 sum += (double)(in[pos*16+i].ef.y);
		 sum += (double)(in[pos*16+i].ef.z);
		 sum += (double)(in[pos*16+i].ef.w);
		 sum += (double)(in[pos*16+i].fc.x);
		 sum += (double)(in[pos*16+i].fc.y);
		 sum += (double)(in[pos*16+i].fc.z);
		 sum += (double)(in[pos*16+i].fc.w);
		 sum += (double)(in[pos*16+i].fd.x);
		 sum += (double)(in[pos*16+i].fd.y);
		 sum += (double)(in[pos*16+i].fd.z);
		 sum += (double)(in[pos*16+i].fd.w);
		 sum += (double)(in[pos*16+i].fe.x);
		 sum += (double)(in[pos*16+i].fe.y);
		 sum += (double)(in[pos*16+i].fe.z);
		 sum += (double)(in[pos*16+i].fe.w);
		 sum += (double)(in[pos*16+i].ff.x);
		 sum += (double)(in[pos*16+i].ff.y);
		 sum += (double)(in[pos*16+i].ff.z);
		 sum += (double)(in[pos*16+i].ff.w);
	 }
	 result[pos] = sum;
}
__kernel void float444_sum_N(__global float444 * in, uint offset, uint resultoffset, uint n, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i;
	 double sum = 0.0;
	 for(i=0; i < n; i++){
		 sum += (double)(in[pos*n+i+offset].cc.x);
		 sum += (double)(in[pos*n+i+offset].cc.y);
		 sum += (double)(in[pos*n+i+offset].cc.z);
		 sum += (double)(in[pos*n+i+offset].cc.w);
		 sum += (double)(in[pos*n+i+offset].cd.x);
		 sum += (double)(in[pos*n+i+offset].cd.y);
		 sum += (double)(in[pos*n+i+offset].cd.z);
		 sum += (double)(in[pos*n+i+offset].cd.w);
		 sum += (double)(in[pos*n+i+offset].ce.x);
		 sum += (double)(in[pos*n+i+offset].ce.y);
		 sum += (double)(in[pos*n+i+offset].ce.z);
		 sum += (double)(in[pos*n+i+offset].ce.w);
		 sum += (double)(in[pos*n+i+offset].cf.x);
		 sum += (double)(in[pos*n+i+offset].cf.y);
		 sum += (double)(in[pos*n+i+offset].cf.z);
		 sum += (double)(in[pos*n+i+offset].cf.w);
		 sum += (double)(in[pos*n+i+offset].dc.x);
		 sum += (double)(in[pos*n+i+offset].dc.y);
		 sum += (double)(in[pos*n+i+offset].dc.z);
		 sum += (double)(in[pos*n+i+offset].dc.w);
		 sum += (double)(in[pos*n+i+offset].dd.x);
		 sum += (double)(in[pos*n+i+offset].dd.y);
		 sum += (double)(in[pos*n+i+offset].dd.z);
		 sum += (double)(in[pos*n+i+offset].dd.w);
		 sum += (double)(in[pos*n+i+offset].de.x);
		 sum += (double)(in[pos*n+i+offset].de.y);
		 sum += (double)(in[pos*n+i+offset].de.z);
		 sum += (double)(in[pos*n+i+offset].de.w);
		 sum += (double)(in[pos*n+i+offset].df.x);
		 sum += (double)(in[pos*n+i+offset].df.y);
		 sum += (double)(in[pos*n+i+offset].df.z);
		 sum += (double)(in[pos*n+i+offset].df.w);
		 sum += (double)(in[pos*n+i+offset].ec.x);
		 sum += (double)(in[pos*n+i+offset].ec.y);
		 sum += (double)(in[pos*n+i+offset].ec.z);
		 sum += (double)(in[pos*n+i+offset].ec.w);
		 sum += (double)(in[pos*n+i+offset].ed.x);
		 sum += (double)(in[pos*n+i+offset].ed.y);
		 sum += (double)(in[pos*n+i+offset].ed.z);
		 sum += (double)(in[pos*n+i+offset].ed.w);
		 sum += (double)(in[pos*n+i+offset].ee.x);
		 sum += (double)(in[pos*n+i+offset].ee.y);
		 sum += (double)(in[pos*n+i+offset].ee.z);
		 sum += (double)(in[pos*n+i+offset].ee.w);
		 sum += (double)(in[pos*n+i+offset].ef.x);
		 sum += (double)(in[pos*n+i+offset].ef.y);
		 sum += (double)(in[pos*n+i+offset].ef.z);
		 sum += (double)(in[pos*n+i+offset].ef.w);
		 sum += (double)(in[pos*n+i+offset].fc.x);
		 sum += (double)(in[pos*n+i+offset].fc.y);
		 sum += (double)(in[pos*n+i+offset].fc.z);
		 sum += (double)(in[pos*n+i+offset].fc.w);
		 sum += (double)(in[pos*n+i+offset].fd.x);
		 sum += (double)(in[pos*n+i+offset].fd.y);
		 sum += (double)(in[pos*n+i+offset].fd.z);
		 sum += (double)(in[pos*n+i+offset].fd.w);
		 sum += (double)(in[pos*n+i+offset].fe.x);
		 sum += (double)(in[pos*n+i+offset].fe.y);
		 sum += (double)(in[pos*n+i+offset].fe.z);
		 sum += (double)(in[pos*n+i+offset].fe.w);
		 sum += (double)(in[pos*n+i+offset].ff.x);
		 sum += (double)(in[pos*n+i+offset].ff.y);
		 sum += (double)(in[pos*n+i+offset].ff.z);
		 sum += (double)(in[pos*n+i+offset].ff.w);
	 }
	 result[pos+resultoffset] = sum;
}
__kernel void float444_sum2d_16(__global float444 * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j].cc.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].cc.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].cc.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].cc.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].cd.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].cd.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].cd.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].cd.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].ce.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].ce.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].ce.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].ce.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].cf.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].cf.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].cf.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].cf.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].dc.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].dc.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].dc.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].dc.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].dd.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].dd.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].dd.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].dd.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].de.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].de.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].de.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].de.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].df.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].df.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].df.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].df.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].ec.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].ec.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].ec.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].ec.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].ed.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].ed.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].ed.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].ed.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].ee.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].ee.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].ee.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].ee.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].ef.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].ef.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].ef.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].ef.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].fc.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].fc.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].fc.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].fc.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].fd.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].fd.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].fd.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].fd.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].fe.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].fe.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].fe.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].fe.w);
			 sum += (double)(in[pos*16*d1+i*d1+j].ff.x);
			 sum += (double)(in[pos*16*d1+i*d1+j].ff.y);
			 sum += (double)(in[pos*16*d1+i*d1+j].ff.z);
			 sum += (double)(in[pos*16*d1+i*d1+j].ff.w);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void float444_sum2d_N(__global float444 * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cc.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cc.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cc.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cc.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cd.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cd.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cd.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cd.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ce.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ce.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ce.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ce.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cf.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cf.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cf.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cf.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dc.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dc.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dc.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dc.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dd.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dd.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dd.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dd.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].de.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].de.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].de.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].de.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].df.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].df.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].df.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].df.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ec.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ec.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ec.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ec.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ed.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ed.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ed.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ed.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ee.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ee.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ee.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ee.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ef.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ef.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ef.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ef.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fc.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fc.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fc.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fc.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fd.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fd.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fd.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fd.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fe.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fe.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fe.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fe.w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ff.x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ff.y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ff.z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ff.w);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
__kernel void float444_sum2d_16_weighted(__global float4 * weights, __global float444 * in, uint d1, __global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < 16; i++){
			 sum += (double)(in[pos*16*d1+i*d1+j].cc.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].cc.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].cc.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].cc.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].cd.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].cd.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].cd.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].cd.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].ce.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].ce.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].ce.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].ce.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].cf.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].cf.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].cf.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].cf.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].dc.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].dc.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].dc.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].dc.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].dd.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].dd.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].dd.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].dd.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].de.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].de.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].de.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].de.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].df.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].df.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].df.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].df.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].ec.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].ec.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].ec.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].ec.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].ed.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].ed.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].ed.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].ed.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].ee.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].ee.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].ee.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].ee.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].ef.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].ef.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].ef.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].ef.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].fc.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].fc.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].fc.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].fc.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].fd.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].fd.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].fd.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].fd.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].fe.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].fe.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].fe.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].fe.w*weights[pos*16+i].w);
			 sum += (double)(in[pos*16*d1+i*d1+j].ff.x*weights[pos*16+i].x);
			 sum += (double)(in[pos*16*d1+i*d1+j].ff.y*weights[pos*16+i].y);
			 sum += (double)(in[pos*16*d1+i*d1+j].ff.z*weights[pos*16+i].z);
			 sum += (double)(in[pos*16*d1+i*d1+j].ff.w*weights[pos*16+i].w);
		 }
		 result[pos*d1+j] = sum;
	}
}
__kernel void float444_sum2d_N_weighted(__global float4 * weights,__global float444 * in, uint d1, uint offset, uint resultoffset, uint n,__global out double * result){
	 uint pos = get_global_id(0);
	 uint i,j;
	 double sum;
	 for(j=0; j < d1; j++){
		 sum =0.0;
		 for(i=0; i < n; i++){
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cc.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cc.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cc.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cc.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cd.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cd.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cd.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cd.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ce.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ce.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ce.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ce.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cf.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cf.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cf.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].cf.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dc.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dc.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dc.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dc.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dd.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dd.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dd.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].dd.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].de.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].de.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].de.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].de.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].df.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].df.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].df.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].df.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ec.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ec.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ec.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ec.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ed.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ed.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ed.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ed.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ee.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ee.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ee.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ee.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ef.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ef.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ef.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ef.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fc.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fc.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fc.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fc.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fd.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fd.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fd.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fd.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fe.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fe.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fe.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].fe.w*weights[pos*n+i].w);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ff.x*weights[pos*n+i].x);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ff.y*weights[pos*n+i].y);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ff.z*weights[pos*n+i].z);
			 sum += (double)(in[pos*n*d1+i*d1+j+offset].ff.w*weights[pos*n+i].w);
		 }
		 result[pos*d1+j+resultoffset] = sum;
	}
}
