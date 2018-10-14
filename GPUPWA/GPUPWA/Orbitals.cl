/* Orbital tensor kernels */
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


__kernel void kernel4orbitaltensor(__global float4 * rt, int i, int j,  __global float44 * delp, __global out float44 * result){
  
  uint pos = get_global_id(0);
  
  float rt2 = -rt[pos].x*rt[pos].x - rt[pos].y*rt[pos].y - rt[pos].z*rt[pos].z + rt[pos].w*rt[pos].w;
  float rt4 = rt2*rt2;

  if(0==i && 0==j){
 	result[pos].c = rt[pos].x*rt[pos].x*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].c.x*rt[pos].x*rt[pos] +delp[pos].c.x*rt[pos].x*rt[pos] + delp[pos].c.x*rt[pos].x*rt[pos] + delp[pos].c*rt[pos].x*rt[pos].x + delp[pos].c*rt[pos].x*rt[pos].x + delp[pos].c*rt[pos].x*rt[pos].x) + rt4/35.0f*(delp[pos].c.x*delp[pos].c + delp[pos].c.x*delp[pos].c + delp[pos].c.x*delp[pos].c);
  	result[pos].d = rt[pos].x*rt[pos].x*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].c.x*rt[pos].y*rt[pos] +delp[pos].c.y*rt[pos].x*rt[pos] + delp[pos].d.x*rt[pos].x*rt[pos] + delp[pos].c*rt[pos].x*rt[pos].y + delp[pos].c*rt[pos].y*rt[pos].x + delp[pos].d*rt[pos].x*rt[pos].x) + rt4/35.0f*(delp[pos].c.x*delp[pos].d + delp[pos].c.y*delp[pos].c + delp[pos].d.x*delp[pos].c);				        
 	result[pos].e = rt[pos].x*rt[pos].x*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].c.x*rt[pos].z*rt[pos] +delp[pos].c.z*rt[pos].x*rt[pos] + delp[pos].e.x*rt[pos].x*rt[pos] + delp[pos].c*rt[pos].x*rt[pos].z + delp[pos].c*rt[pos].z*rt[pos].x + delp[pos].e*rt[pos].x*rt[pos].x) + rt4/35.0f*(delp[pos].c.x*delp[pos].e + delp[pos].c.z*delp[pos].c + delp[pos].e.x*delp[pos].c);
 	result[pos].f = rt[pos].x*rt[pos].x*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].c.x*rt[pos].w*rt[pos] +delp[pos].c.w*rt[pos].x*rt[pos] + delp[pos].f.x*rt[pos].x*rt[pos] + delp[pos].c*rt[pos].x*rt[pos].w + delp[pos].c*rt[pos].w*rt[pos].x + delp[pos].f*rt[pos].x*rt[pos].x) + rt4/35.0f*(delp[pos].c.x*delp[pos].f + delp[pos].c.w*delp[pos].c + delp[pos].f.x*delp[pos].c);
  }

 if(0==i && 1==j){
  result[pos].c = rt[pos].x*rt[pos].y*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].c.y*rt[pos].x*rt[pos] +delp[pos].d.x*rt[pos].x*rt[pos] + delp[pos].c.x*rt[pos].y*rt[pos] + delp[pos].c*rt[pos].y*rt[pos].x + delp[pos].d*rt[pos].x*rt[pos].x + delp[pos].c*rt[pos].x*rt[pos].y) + rt4/35.0f*(delp[pos].c.y*delp[pos].c + delp[pos].d.x*delp[pos].c + delp[pos].c.x*delp[pos].d);
  result[pos].d = rt[pos].x*rt[pos].y*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].c.y*rt[pos].y*rt[pos] +delp[pos].d.y*rt[pos].x*rt[pos] + delp[pos].d.x*rt[pos].y*rt[pos] + delp[pos].c*rt[pos].y*rt[pos].y + delp[pos].d*rt[pos].y*rt[pos].x + delp[pos].d*rt[pos].x*rt[pos].y) + rt4/35.0f*(delp[pos].c.y*delp[pos].d + delp[pos].d.y*delp[pos].c + delp[pos].d.x*delp[pos].d);
  result[pos].e = rt[pos].x*rt[pos].y*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].c.y*rt[pos].z*rt[pos] +delp[pos].d.z*rt[pos].x*rt[pos] + delp[pos].e.x*rt[pos].y*rt[pos] + delp[pos].c*rt[pos].y*rt[pos].z + delp[pos].d*rt[pos].z*rt[pos].x + delp[pos].e*rt[pos].x*rt[pos].y) + rt4/35.0f*(delp[pos].c.y*delp[pos].e + delp[pos].d.z*delp[pos].c + delp[pos].e.x*delp[pos].d);
  result[pos].f = rt[pos].x*rt[pos].y*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].c.y*rt[pos].w*rt[pos] +delp[pos].d.w*rt[pos].x*rt[pos] + delp[pos].f.x*rt[pos].y*rt[pos] + delp[pos].c*rt[pos].y*rt[pos].w + delp[pos].d*rt[pos].w*rt[pos].x + delp[pos].f*rt[pos].x*rt[pos].y) + rt4/35.0f*(delp[pos].c.y*delp[pos].f + delp[pos].d.w*delp[pos].c + delp[pos].f.x*delp[pos].d);
 }

 if(0==i && 2==j){
  result[pos].c = rt[pos].x*rt[pos].z*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].c.z*rt[pos].x*rt[pos] +delp[pos].e.x*rt[pos].x*rt[pos] + delp[pos].c.x*rt[pos].z*rt[pos] + delp[pos].c*rt[pos].z*rt[pos].x + delp[pos].e*rt[pos].x*rt[pos].x + delp[pos].c*rt[pos].x*rt[pos].z) + rt4/35.0f*(delp[pos].c.z*delp[pos].c + delp[pos].e.x*delp[pos].c + delp[pos].c.x*delp[pos].e);
  result[pos].d = rt[pos].x*rt[pos].z*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].c.z*rt[pos].y*rt[pos] +delp[pos].e.y*rt[pos].x*rt[pos] + delp[pos].d.x*rt[pos].z*rt[pos] + delp[pos].c*rt[pos].z*rt[pos].y + delp[pos].e*rt[pos].y*rt[pos].x + delp[pos].d*rt[pos].x*rt[pos].z) + rt4/35.0f*(delp[pos].c.z*delp[pos].d + delp[pos].e.y*delp[pos].c + delp[pos].d.x*delp[pos].e);
  result[pos].e = rt[pos].x*rt[pos].z*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].c.z*rt[pos].z*rt[pos] +delp[pos].e.z*rt[pos].x*rt[pos] + delp[pos].e.x*rt[pos].z*rt[pos] + delp[pos].c*rt[pos].z*rt[pos].z + delp[pos].e*rt[pos].z*rt[pos].x + delp[pos].e*rt[pos].x*rt[pos].z) + rt4/35.0f*(delp[pos].c.z*delp[pos].e + delp[pos].e.z*delp[pos].c + delp[pos].e.x*delp[pos].e);
  result[pos].f = rt[pos].x*rt[pos].z*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].c.z*rt[pos].w*rt[pos] +delp[pos].e.w*rt[pos].x*rt[pos] + delp[pos].f.x*rt[pos].z*rt[pos] + delp[pos].c*rt[pos].z*rt[pos].w + delp[pos].e*rt[pos].w*rt[pos].x + delp[pos].f*rt[pos].x*rt[pos].z) + rt4/35.0f*(delp[pos].c.z*delp[pos].f + delp[pos].e.w*delp[pos].c + delp[pos].f.x*delp[pos].e);
}

 if(0==i && 3==j){
  result[pos].c = rt[pos].x*rt[pos].w*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].c.w*rt[pos].x*rt[pos] +delp[pos].f.x*rt[pos].x*rt[pos] + delp[pos].c.x*rt[pos].w*rt[pos] + delp[pos].c*rt[pos].w*rt[pos].x + delp[pos].f*rt[pos].x*rt[pos].x + delp[pos].c*rt[pos].x*rt[pos].w) + rt4/35.0f*(delp[pos].c.w*delp[pos].c + delp[pos].f.x*delp[pos].c + delp[pos].c.x*delp[pos].f);
  result[pos].d = rt[pos].x*rt[pos].w*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].c.w*rt[pos].y*rt[pos] +delp[pos].f.y*rt[pos].x*rt[pos] + delp[pos].d.x*rt[pos].w*rt[pos] + delp[pos].c*rt[pos].w*rt[pos].y + delp[pos].f*rt[pos].y*rt[pos].x + delp[pos].d*rt[pos].x*rt[pos].w) + rt4/35.0f*(delp[pos].c.w*delp[pos].d + delp[pos].f.y*delp[pos].c + delp[pos].d.x*delp[pos].f);
  result[pos].e = rt[pos].x*rt[pos].w*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].c.w*rt[pos].z*rt[pos] +delp[pos].f.z*rt[pos].x*rt[pos] + delp[pos].e.x*rt[pos].w*rt[pos] + delp[pos].c*rt[pos].w*rt[pos].z + delp[pos].f*rt[pos].z*rt[pos].x + delp[pos].e*rt[pos].x*rt[pos].w) + rt4/35.0f*(delp[pos].c.w*delp[pos].e + delp[pos].f.z*delp[pos].c + delp[pos].e.x*delp[pos].f);
  result[pos].f = rt[pos].x*rt[pos].w*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].c.w*rt[pos].w*rt[pos] +delp[pos].f.w*rt[pos].x*rt[pos] + delp[pos].f.x*rt[pos].w*rt[pos] + delp[pos].c*rt[pos].w*rt[pos].w + delp[pos].f*rt[pos].w*rt[pos].x + delp[pos].f*rt[pos].x*rt[pos].w) + rt4/35.0f*(delp[pos].c.w*delp[pos].f + delp[pos].f.w*delp[pos].c + delp[pos].f.x*delp[pos].f);

}


  if(1==i && 0==j){
  result[pos].c = rt[pos].y*rt[pos].x*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].d.x*rt[pos].x*rt[pos] +delp[pos].c.x*rt[pos].y*rt[pos] + delp[pos].c.y*rt[pos].x*rt[pos] + delp[pos].d*rt[pos].x*rt[pos].x + delp[pos].c*rt[pos].x*rt[pos].y + delp[pos].c*rt[pos].y*rt[pos].x) + rt4/35.0f*(delp[pos].d.x*delp[pos].c + delp[pos].c.x*delp[pos].d + delp[pos].c.y*delp[pos].c);
  result[pos].d = rt[pos].y*rt[pos].x*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].d.x*rt[pos].y*rt[pos] +delp[pos].c.y*rt[pos].y*rt[pos] + delp[pos].d.y*rt[pos].x*rt[pos] + delp[pos].d*rt[pos].x*rt[pos].y + delp[pos].c*rt[pos].y*rt[pos].y + delp[pos].d*rt[pos].y*rt[pos].x) + rt4/35.0f*(delp[pos].d.x*delp[pos].d + delp[pos].c.y*delp[pos].d + delp[pos].d.y*delp[pos].c);
  result[pos].e = rt[pos].y*rt[pos].x*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].d.x*rt[pos].z*rt[pos] +delp[pos].c.z*rt[pos].y*rt[pos] + delp[pos].e.y*rt[pos].x*rt[pos] + delp[pos].d*rt[pos].x*rt[pos].z + delp[pos].c*rt[pos].z*rt[pos].y + delp[pos].e*rt[pos].y*rt[pos].x) + rt4/35.0f*(delp[pos].d.x*delp[pos].e + delp[pos].c.z*delp[pos].d + delp[pos].e.y*delp[pos].c);
  result[pos].f = rt[pos].y*rt[pos].x*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].d.x*rt[pos].w*rt[pos] +delp[pos].c.w*rt[pos].y*rt[pos] + delp[pos].f.y*rt[pos].x*rt[pos] + delp[pos].d*rt[pos].x*rt[pos].w + delp[pos].c*rt[pos].w*rt[pos].y + delp[pos].f*rt[pos].y*rt[pos].x) + rt4/35.0f*(delp[pos].d.x*delp[pos].f + delp[pos].c.w*delp[pos].d + delp[pos].f.y*delp[pos].c);
}


 if(1==i && 1==j){
  result[pos].c = rt[pos].y*rt[pos].y*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].d.y*rt[pos].x*rt[pos] +delp[pos].d.x*rt[pos].y*rt[pos] + delp[pos].c.y*rt[pos].y*rt[pos] + delp[pos].d*rt[pos].y*rt[pos].x + delp[pos].d*rt[pos].x*rt[pos].y + delp[pos].c*rt[pos].y*rt[pos].y) + rt4/35.0f*(delp[pos].d.y*delp[pos].c + delp[pos].d.x*delp[pos].d + delp[pos].c.y*delp[pos].d);
  result[pos].d = rt[pos].y*rt[pos].y*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].d.y*rt[pos].y*rt[pos] +delp[pos].d.y*rt[pos].y*rt[pos] + delp[pos].d.y*rt[pos].y*rt[pos] + delp[pos].d*rt[pos].y*rt[pos].y + delp[pos].d*rt[pos].y*rt[pos].y + delp[pos].d*rt[pos].y*rt[pos].y) + rt4/35.0f*(delp[pos].d.y*delp[pos].d + delp[pos].d.y*delp[pos].d + delp[pos].d.y*delp[pos].d);
  result[pos].e = rt[pos].y*rt[pos].y*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].d.y*rt[pos].z*rt[pos] +delp[pos].d.z*rt[pos].y*rt[pos] + delp[pos].e.y*rt[pos].y*rt[pos] + delp[pos].d*rt[pos].y*rt[pos].z + delp[pos].d*rt[pos].z*rt[pos].y + delp[pos].e*rt[pos].y*rt[pos].y) + rt4/35.0f*(delp[pos].d.y*delp[pos].e + delp[pos].d.z*delp[pos].d + delp[pos].e.y*delp[pos].d);
  result[pos].f = rt[pos].y*rt[pos].y*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].d.y*rt[pos].w*rt[pos] +delp[pos].d.w*rt[pos].y*rt[pos] + delp[pos].f.y*rt[pos].y*rt[pos] + delp[pos].d*rt[pos].y*rt[pos].w + delp[pos].d*rt[pos].w*rt[pos].y + delp[pos].f*rt[pos].y*rt[pos].y) + rt4/35.0f*(delp[pos].d.y*delp[pos].f + delp[pos].d.w*delp[pos].d + delp[pos].f.y*delp[pos].d);
 }

	
  if(1==i && 2==j){
  result[pos].c = rt[pos].y*rt[pos].z*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].d.z*rt[pos].x*rt[pos] +delp[pos].e.x*rt[pos].y*rt[pos] + delp[pos].c.y*rt[pos].z*rt[pos] + delp[pos].d*rt[pos].z*rt[pos].x + delp[pos].e*rt[pos].x*rt[pos].y + delp[pos].c*rt[pos].y*rt[pos].z) + rt4/35.0f*(delp[pos].d.z*delp[pos].c + delp[pos].e.x*delp[pos].d + delp[pos].c.y*delp[pos].e);	
   result[pos].d = rt[pos].y*rt[pos].z*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].d.z*rt[pos].y*rt[pos] +delp[pos].e.y*rt[pos].y*rt[pos] + delp[pos].d.y*rt[pos].z*rt[pos] + delp[pos].d*rt[pos].z*rt[pos].y + delp[pos].e*rt[pos].y*rt[pos].y + delp[pos].d*rt[pos].y*rt[pos].z) + rt4/35.0f*(delp[pos].d.z*delp[pos].d + delp[pos].e.y*delp[pos].d + delp[pos].d.y*delp[pos].e);
   result[pos].e = rt[pos].y*rt[pos].z*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].d.z*rt[pos].z*rt[pos] +delp[pos].e.z*rt[pos].y*rt[pos] + delp[pos].e.y*rt[pos].z*rt[pos] + delp[pos].d*rt[pos].z*rt[pos].z + delp[pos].e*rt[pos].z*rt[pos].y + delp[pos].e*rt[pos].y*rt[pos].z) + rt4/35.0f*(delp[pos].d.z*delp[pos].e + delp[pos].e.z*delp[pos].d + delp[pos].e.y*delp[pos].e);
   result[pos].f = rt[pos].y*rt[pos].z*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].d.z*rt[pos].w*rt[pos] +delp[pos].e.w*rt[pos].y*rt[pos] + delp[pos].f.y*rt[pos].z*rt[pos] + delp[pos].d*rt[pos].z*rt[pos].w + delp[pos].e*rt[pos].w*rt[pos].y + delp[pos].f*rt[pos].y*rt[pos].z) + rt4/35.0f*(delp[pos].d.z*delp[pos].f + delp[pos].e.w*delp[pos].d + delp[pos].f.y*delp[pos].e);
}


 if(1==i && 3==j){
   result[pos].c = rt[pos].y*rt[pos].w*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].d.w*rt[pos].x*rt[pos] +delp[pos].f.x*rt[pos].y*rt[pos] + delp[pos].c.y*rt[pos].w*rt[pos] + delp[pos].d*rt[pos].w*rt[pos].x + delp[pos].f*rt[pos].x*rt[pos].y + delp[pos].c*rt[pos].y*rt[pos].w) + rt4/35.0f*(delp[pos].d.w*delp[pos].c + delp[pos].f.x*delp[pos].d + delp[pos].c.y*delp[pos].f);
   result[pos].d = rt[pos].y*rt[pos].w*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].d.w*rt[pos].y*rt[pos] +delp[pos].f.y*rt[pos].y*rt[pos] + delp[pos].d.y*rt[pos].w*rt[pos] + delp[pos].d*rt[pos].w*rt[pos].y + delp[pos].f*rt[pos].y*rt[pos].y + delp[pos].d*rt[pos].y*rt[pos].w) + rt4/35.0f*(delp[pos].d.w*delp[pos].d + delp[pos].f.y*delp[pos].d + delp[pos].d.y*delp[pos].f);
   result[pos].e = rt[pos].y*rt[pos].w*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].d.w*rt[pos].z*rt[pos] +delp[pos].f.z*rt[pos].y*rt[pos] + delp[pos].e.y*rt[pos].w*rt[pos] + delp[pos].d*rt[pos].w*rt[pos].z + delp[pos].f*rt[pos].z*rt[pos].y + delp[pos].e*rt[pos].y*rt[pos].w) + rt4/35.0f*(delp[pos].d.w*delp[pos].e + delp[pos].f.z*delp[pos].d + delp[pos].e.y*delp[pos].f);
   result[pos].f = rt[pos].y*rt[pos].w*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].d.w*rt[pos].w*rt[pos] +delp[pos].f.w*rt[pos].y*rt[pos] + delp[pos].f.y*rt[pos].w*rt[pos] + delp[pos].d*rt[pos].w*rt[pos].w + delp[pos].f*rt[pos].w*rt[pos].y + delp[pos].f*rt[pos].y*rt[pos].w) + rt4/35.0f*(delp[pos].d.w*delp[pos].f + delp[pos].f.w*delp[pos].d + delp[pos].f.y*delp[pos].f);
}



  if(2==i && 0==j){
    result[pos].c = rt[pos].z*rt[pos].x*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].e.x*rt[pos].x*rt[pos] +delp[pos].c.x*rt[pos].z*rt[pos] + delp[pos].c.z*rt[pos].x*rt[pos] + delp[pos].e*rt[pos].x*rt[pos].x + delp[pos].c*rt[pos].x*rt[pos].z + delp[pos].c*rt[pos].z*rt[pos].x) + rt4/35.0f*(delp[pos].e.x*delp[pos].c + delp[pos].c.x*delp[pos].e + delp[pos].c.z*delp[pos].c);
    result[pos].d = rt[pos].z*rt[pos].x*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].e.x*rt[pos].y*rt[pos] +delp[pos].c.y*rt[pos].z*rt[pos] + delp[pos].d.z*rt[pos].x*rt[pos] + delp[pos].e*rt[pos].x*rt[pos].y + delp[pos].c*rt[pos].y*rt[pos].z + delp[pos].d*rt[pos].z*rt[pos].x) + rt4/35.0f*(delp[pos].e.x*delp[pos].d + delp[pos].c.y*delp[pos].e + delp[pos].d.z*delp[pos].c);
    result[pos].e = rt[pos].z*rt[pos].x*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].e.x*rt[pos].z*rt[pos] +delp[pos].c.z*rt[pos].z*rt[pos] + delp[pos].e.z*rt[pos].x*rt[pos] + delp[pos].e*rt[pos].x*rt[pos].z + delp[pos].c*rt[pos].z*rt[pos].z + delp[pos].e*rt[pos].z*rt[pos].x) + rt4/35.0f*(delp[pos].e.x*delp[pos].e + delp[pos].c.z*delp[pos].e + delp[pos].e.z*delp[pos].c);
    result[pos].f = rt[pos].z*rt[pos].x*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].e.x*rt[pos].w*rt[pos] +delp[pos].c.w*rt[pos].z*rt[pos] + delp[pos].f.z*rt[pos].x*rt[pos] + delp[pos].e*rt[pos].x*rt[pos].w + delp[pos].c*rt[pos].w*rt[pos].z + delp[pos].f*rt[pos].z*rt[pos].x) + rt4/35.0f*(delp[pos].e.x*delp[pos].f + delp[pos].c.w*delp[pos].e + delp[pos].f.z*delp[pos].c);
}
	
    if(2==i && 1==j){
    result[pos].c = rt[pos].z*rt[pos].y*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].e.y*rt[pos].x*rt[pos] +delp[pos].d.x*rt[pos].z*rt[pos] + delp[pos].c.z*rt[pos].y*rt[pos] + delp[pos].e*rt[pos].y*rt[pos].x + delp[pos].d*rt[pos].x*rt[pos].z + delp[pos].c*rt[pos].z*rt[pos].y) + rt4/35.0f*(delp[pos].e.y*delp[pos].c + delp[pos].d.x*delp[pos].e + delp[pos].c.z*delp[pos].d);
    result[pos].d = rt[pos].z*rt[pos].y*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].e.y*rt[pos].y*rt[pos] +delp[pos].d.y*rt[pos].z*rt[pos] + delp[pos].d.z*rt[pos].y*rt[pos] + delp[pos].e*rt[pos].y*rt[pos].y + delp[pos].d*rt[pos].y*rt[pos].z + delp[pos].d*rt[pos].z*rt[pos].y) + rt4/35.0f*(delp[pos].e.y*delp[pos].d + delp[pos].d.y*delp[pos].e + delp[pos].d.z*delp[pos].d);
    result[pos].e = rt[pos].z*rt[pos].y*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].e.y*rt[pos].z*rt[pos] +delp[pos].d.z*rt[pos].z*rt[pos] + delp[pos].e.z*rt[pos].y*rt[pos] + delp[pos].e*rt[pos].y*rt[pos].z + delp[pos].d*rt[pos].z*rt[pos].z + delp[pos].e*rt[pos].z*rt[pos].y) + rt4/35.0f*(delp[pos].e.y*delp[pos].e + delp[pos].d.z*delp[pos].e + delp[pos].e.z*delp[pos].d);
    result[pos].f = rt[pos].z*rt[pos].y*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].e.y*rt[pos].w*rt[pos] +delp[pos].d.w*rt[pos].z*rt[pos] + delp[pos].f.z*rt[pos].y*rt[pos] + delp[pos].e*rt[pos].y*rt[pos].w + delp[pos].d*rt[pos].w*rt[pos].z + delp[pos].f*rt[pos].z*rt[pos].y) + rt4/35.0f*(delp[pos].e.y*delp[pos].f + delp[pos].d.w*delp[pos].e + delp[pos].f.z*delp[pos].d);
}
 
   if(2==i && 2==j){
   result[pos].c = rt[pos].z*rt[pos].z*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].e.z*rt[pos].x*rt[pos] +delp[pos].e.x*rt[pos].z*rt[pos] + delp[pos].c.z*rt[pos].z*rt[pos] + delp[pos].e*rt[pos].z*rt[pos].x + delp[pos].e*rt[pos].x*rt[pos].z + delp[pos].c*rt[pos].z*rt[pos].z) + rt4/35.0f*(delp[pos].e.z*delp[pos].c + delp[pos].e.x*delp[pos].e + delp[pos].c.z*delp[pos].e);
   result[pos].d = rt[pos].z*rt[pos].z*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].e.z*rt[pos].y*rt[pos] +delp[pos].e.y*rt[pos].z*rt[pos] + delp[pos].d.z*rt[pos].z*rt[pos] + delp[pos].e*rt[pos].z*rt[pos].y + delp[pos].e*rt[pos].y*rt[pos].z + delp[pos].d*rt[pos].z*rt[pos].z) + rt4/35.0f*(delp[pos].e.z*delp[pos].d + delp[pos].e.y*delp[pos].e + delp[pos].d.z*delp[pos].e);
   result[pos].e = rt[pos].z*rt[pos].z*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].e.z*rt[pos].z*rt[pos] +delp[pos].e.z*rt[pos].z*rt[pos] + delp[pos].e.z*rt[pos].z*rt[pos] + delp[pos].e*rt[pos].z*rt[pos].z + delp[pos].e*rt[pos].z*rt[pos].z + delp[pos].e*rt[pos].z*rt[pos].z) + rt4/35.0f*(delp[pos].e.z*delp[pos].e + delp[pos].e.z*delp[pos].e + delp[pos].e.z*delp[pos].e);
   result[pos].f = rt[pos].z*rt[pos].z*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].e.z*rt[pos].w*rt[pos] +delp[pos].e.w*rt[pos].z*rt[pos] + delp[pos].f.z*rt[pos].z*rt[pos] + delp[pos].e*rt[pos].z*rt[pos].w + delp[pos].e*rt[pos].w*rt[pos].z + delp[pos].f*rt[pos].z*rt[pos].z) + rt4/35.0f*(delp[pos].e.z*delp[pos].f + delp[pos].e.w*delp[pos].e + delp[pos].f.z*delp[pos].e);
}
   if(2==i && 3==j){
   result[pos].c = rt[pos].z*rt[pos].w*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].e.w*rt[pos].x*rt[pos] +delp[pos].f.x*rt[pos].z*rt[pos] + delp[pos].c.z*rt[pos].w*rt[pos] + delp[pos].e*rt[pos].w*rt[pos].x + delp[pos].f*rt[pos].x*rt[pos].z + delp[pos].c*rt[pos].z*rt[pos].w) + rt4/35.0f*(delp[pos].e.w*delp[pos].c + delp[pos].f.x*delp[pos].e + delp[pos].c.z*delp[pos].f);
   result[pos].d = rt[pos].z*rt[pos].w*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].e.w*rt[pos].y*rt[pos] +delp[pos].f.y*rt[pos].z*rt[pos] + delp[pos].d.z*rt[pos].w*rt[pos] + delp[pos].e*rt[pos].w*rt[pos].y + delp[pos].f*rt[pos].y*rt[pos].z + delp[pos].d*rt[pos].z*rt[pos].w) + rt4/35.0f*(delp[pos].e.w*delp[pos].d + delp[pos].f.y*delp[pos].e + delp[pos].d.z*delp[pos].f);
   result[pos].e = rt[pos].z*rt[pos].w*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].e.w*rt[pos].z*rt[pos] +delp[pos].f.z*rt[pos].z*rt[pos] + delp[pos].e.z*rt[pos].w*rt[pos] + delp[pos].e*rt[pos].w*rt[pos].z + delp[pos].f*rt[pos].z*rt[pos].z + delp[pos].e*rt[pos].z*rt[pos].w) + rt4/35.0f*(delp[pos].e.w*delp[pos].e + delp[pos].f.z*delp[pos].e + delp[pos].e.z*delp[pos].f);		
   result[pos].f = rt[pos].z*rt[pos].w*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].e.w*rt[pos].w*rt[pos] +delp[pos].f.w*rt[pos].z*rt[pos] + delp[pos].f.z*rt[pos].w*rt[pos] + delp[pos].e*rt[pos].w*rt[pos].w + delp[pos].f*rt[pos].w*rt[pos].z + delp[pos].f*rt[pos].z*rt[pos].w) + rt4/35.0f*(delp[pos].e.w*delp[pos].f + delp[pos].f.w*delp[pos].e + delp[pos].f.z*delp[pos].f);
}


  if(3==i && 0==j){
  result[pos].c = rt[pos].w*rt[pos].x*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].f.x*rt[pos].x*rt[pos] +delp[pos].c.x*rt[pos].w*rt[pos] + delp[pos].c.w*rt[pos].x*rt[pos] + delp[pos].f*rt[pos].x*rt[pos].x + delp[pos].c*rt[pos].x*rt[pos].w + delp[pos].c*rt[pos].w*rt[pos].x) + rt4/35.0f*(delp[pos].f.x*delp[pos].c + delp[pos].c.x*delp[pos].f + delp[pos].c.w*delp[pos].c);
  result[pos].d = rt[pos].w*rt[pos].x*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].f.x*rt[pos].y*rt[pos] +delp[pos].c.y*rt[pos].w*rt[pos] + delp[pos].d.w*rt[pos].x*rt[pos] + delp[pos].f*rt[pos].x*rt[pos].y + delp[pos].c*rt[pos].y*rt[pos].w + delp[pos].d*rt[pos].w*rt[pos].x) + rt4/35.0f*(delp[pos].f.x*delp[pos].d + delp[pos].c.y*delp[pos].f + delp[pos].d.w*delp[pos].c);
  result[pos].e = rt[pos].w*rt[pos].x*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].f.x*rt[pos].z*rt[pos] +delp[pos].c.z*rt[pos].w*rt[pos] + delp[pos].e.w*rt[pos].x*rt[pos] + delp[pos].f*rt[pos].x*rt[pos].z + delp[pos].c*rt[pos].z*rt[pos].w + delp[pos].e*rt[pos].w*rt[pos].x) + rt4/35.0f*(delp[pos].f.x*delp[pos].e + delp[pos].c.z*delp[pos].f + delp[pos].e.w*delp[pos].c);
  result[pos].f = rt[pos].w*rt[pos].x*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].f.x*rt[pos].w*rt[pos] +delp[pos].c.w*rt[pos].w*rt[pos] + delp[pos].f.w*rt[pos].x*rt[pos] + delp[pos].f*rt[pos].x*rt[pos].w + delp[pos].c*rt[pos].w*rt[pos].w + delp[pos].f*rt[pos].w*rt[pos].x) + rt4/35.0f*(delp[pos].f.x*delp[pos].f + delp[pos].c.w*delp[pos].f + delp[pos].f.w*delp[pos].c);
}
	
  if(3==i && 1==j){	
  result[pos].c = rt[pos].w*rt[pos].y*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].f.y*rt[pos].x*rt[pos] +delp[pos].d.x*rt[pos].w*rt[pos] + delp[pos].c.w*rt[pos].y*rt[pos] + delp[pos].f*rt[pos].y*rt[pos].x + delp[pos].d*rt[pos].x*rt[pos].w + delp[pos].c*rt[pos].w*rt[pos].y) + rt4/35.0f*(delp[pos].f.y*delp[pos].c + delp[pos].d.x*delp[pos].f + delp[pos].c.w*delp[pos].d);
  result[pos].d = rt[pos].w*rt[pos].y*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].f.y*rt[pos].y*rt[pos] +delp[pos].d.y*rt[pos].w*rt[pos] + delp[pos].d.w*rt[pos].y*rt[pos] + delp[pos].f*rt[pos].y*rt[pos].y + delp[pos].d*rt[pos].y*rt[pos].w + delp[pos].d*rt[pos].w*rt[pos].y) + rt4/35.0f*(delp[pos].f.y*delp[pos].d + delp[pos].d.y*delp[pos].f + delp[pos].d.w*delp[pos].d);
  result[pos].e = rt[pos].w*rt[pos].y*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].f.y*rt[pos].z*rt[pos] +delp[pos].d.z*rt[pos].w*rt[pos] + delp[pos].e.w*rt[pos].y*rt[pos] + delp[pos].f*rt[pos].y*rt[pos].z + delp[pos].d*rt[pos].z*rt[pos].w + delp[pos].e*rt[pos].w*rt[pos].y) + rt4/35.0f*(delp[pos].f.y*delp[pos].e + delp[pos].d.z*delp[pos].f + delp[pos].e.w*delp[pos].d);
  result[pos].f = rt[pos].w*rt[pos].y*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].f.y*rt[pos].w*rt[pos] +delp[pos].d.w*rt[pos].w*rt[pos] + delp[pos].f.w*rt[pos].y*rt[pos] + delp[pos].f*rt[pos].y*rt[pos].w + delp[pos].d*rt[pos].w*rt[pos].w + delp[pos].f*rt[pos].w*rt[pos].y) + rt4/35.0f*(delp[pos].f.y*delp[pos].f + delp[pos].d.w*delp[pos].f + delp[pos].f.w*delp[pos].d);
}

   if(3==i && 2==j){
   result[pos].c = rt[pos].w*rt[pos].z*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].f.z*rt[pos].x*rt[pos] +delp[pos].e.x*rt[pos].w*rt[pos] + delp[pos].c.w*rt[pos].z*rt[pos] + delp[pos].f*rt[pos].z*rt[pos].x + delp[pos].e*rt[pos].x*rt[pos].w + delp[pos].c*rt[pos].w*rt[pos].z) + rt4/35.0f*(delp[pos].f.z*delp[pos].c + delp[pos].e.x*delp[pos].f + delp[pos].c.w*delp[pos].e);
   result[pos].d = rt[pos].w*rt[pos].z*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].f.z*rt[pos].y*rt[pos] +delp[pos].e.y*rt[pos].w*rt[pos] + delp[pos].d.w*rt[pos].z*rt[pos] + delp[pos].f*rt[pos].z*rt[pos].y + delp[pos].e*rt[pos].y*rt[pos].w + delp[pos].d*rt[pos].w*rt[pos].z) + rt4/35.0f*(delp[pos].f.z*delp[pos].d + delp[pos].e.y*delp[pos].f + delp[pos].d.w*delp[pos].e);
   result[pos].e = rt[pos].w*rt[pos].z*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].f.z*rt[pos].z*rt[pos] +delp[pos].e.z*rt[pos].w*rt[pos] + delp[pos].e.w*rt[pos].z*rt[pos] + delp[pos].f*rt[pos].z*rt[pos].z + delp[pos].e*rt[pos].z*rt[pos].w + delp[pos].e*rt[pos].w*rt[pos].z) + rt4/35.0f*(delp[pos].f.z*delp[pos].e + delp[pos].e.z*delp[pos].f + delp[pos].e.w*delp[pos].e);
   result[pos].f = rt[pos].w*rt[pos].z*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].f.z*rt[pos].w*rt[pos] +delp[pos].e.w*rt[pos].w*rt[pos] + delp[pos].f.w*rt[pos].z*rt[pos] + delp[pos].f*rt[pos].z*rt[pos].w + delp[pos].e*rt[pos].w*rt[pos].w + delp[pos].f*rt[pos].w*rt[pos].z) + rt4/35.0f*(delp[pos].f.z*delp[pos].f + delp[pos].e.w*delp[pos].f + delp[pos].f.w*delp[pos].e);		
}
	
  if(3==i && 3==j){
  result[pos].c = rt[pos].w*rt[pos].w*rt[pos].x*rt[pos] - rt2/7.0f *(delp[pos].f.w*rt[pos].x*rt[pos] +delp[pos].f.x*rt[pos].w*rt[pos] + delp[pos].c.w*rt[pos].w*rt[pos] + delp[pos].f*rt[pos].w*rt[pos].x + delp[pos].f*rt[pos].x*rt[pos].w + delp[pos].c*rt[pos].w*rt[pos].w) + rt4/35.0f*(delp[pos].f.w*delp[pos].c + delp[pos].f.x*delp[pos].f + delp[pos].c.w*delp[pos].f);
  result[pos].d = rt[pos].w*rt[pos].w*rt[pos].y*rt[pos] - rt2/7.0f *(delp[pos].f.w*rt[pos].y*rt[pos] +delp[pos].f.y*rt[pos].w*rt[pos] + delp[pos].d.w*rt[pos].w*rt[pos] + delp[pos].f*rt[pos].w*rt[pos].y + delp[pos].f*rt[pos].y*rt[pos].w + delp[pos].d*rt[pos].w*rt[pos].w) + rt4/35.0f*(delp[pos].f.w*delp[pos].d + delp[pos].f.y*delp[pos].f + delp[pos].d.w*delp[pos].f);
  result[pos].e = rt[pos].w*rt[pos].w*rt[pos].z*rt[pos] - rt2/7.0f *(delp[pos].f.w*rt[pos].z*rt[pos] +delp[pos].f.z*rt[pos].w*rt[pos] + delp[pos].e.w*rt[pos].w*rt[pos] + delp[pos].f*rt[pos].w*rt[pos].z + delp[pos].f*rt[pos].z*rt[pos].w + delp[pos].e*rt[pos].w*rt[pos].w) + rt4/35.0f*(delp[pos].f.w*delp[pos].e + delp[pos].f.z*delp[pos].f + delp[pos].e.w*delp[pos].f);
  result[pos].f = rt[pos].w*rt[pos].w*rt[pos].w*rt[pos] - rt2/7.0f *(delp[pos].f.w*rt[pos].w*rt[pos] +delp[pos].f.w*rt[pos].w*rt[pos] + delp[pos].f.w*rt[pos].w*rt[pos] + delp[pos].f*rt[pos].w*rt[pos].w + delp[pos].f*rt[pos].w*rt[pos].w + delp[pos].f*rt[pos].w*rt[pos].w) + rt4/35.0f*(delp[pos].f.w*delp[pos].f + delp[pos].f.w*delp[pos].f + delp[pos].f.w*delp[pos].f);
}

}



__kernel void kernel4orbitaltensorconst(__global float4 * rt, int i, int j,  float44 delp, __global out float44 * result){
  
  uint pos = get_global_id(0);
  
  float rt2 = -rt[pos].x*rt[pos].x - rt[pos].y*rt[pos].y - rt[pos].z*rt[pos].z + rt[pos].w*rt[pos].w;
  float rt4 = rt2*rt2;

  if(0==i && 0==j){
 	result[pos].c = rt[pos].x*rt[pos].x*rt[pos].x*rt[pos] - rt2/7.0f *(delp.c.x*rt[pos].x*rt[pos] +delp.c.x*rt[pos].x*rt[pos] + delp.c.x*rt[pos].x*rt[pos] + delp.c*rt[pos].x*rt[pos].x + delp.c*rt[pos].x*rt[pos].x + delp.c*rt[pos].x*rt[pos].x) + rt4/35.0f*(delp.c.x*delp.c + delp.c.x*delp.c + delp.c.x*delp.c);
  	result[pos].d = rt[pos].x*rt[pos].x*rt[pos].y*rt[pos] - rt2/7.0f *(delp.c.x*rt[pos].y*rt[pos] +delp.c.y*rt[pos].x*rt[pos] + delp.d.x*rt[pos].x*rt[pos] + delp.c*rt[pos].x*rt[pos].y + delp.c*rt[pos].y*rt[pos].x + delp.d*rt[pos].x*rt[pos].x) + rt4/35.0f*(delp.c.x*delp.d + delp.c.y*delp.c + delp.d.x*delp.c);				        
 	result[pos].e = rt[pos].x*rt[pos].x*rt[pos].z*rt[pos] - rt2/7.0f *(delp.c.x*rt[pos].z*rt[pos] +delp.c.z*rt[pos].x*rt[pos] + delp.e.x*rt[pos].x*rt[pos] + delp.c*rt[pos].x*rt[pos].z + delp.c*rt[pos].z*rt[pos].x + delp.e*rt[pos].x*rt[pos].x) + rt4/35.0f*(delp.c.x*delp.e + delp.c.z*delp.c + delp.e.x*delp.c);
 	result[pos].f = rt[pos].x*rt[pos].x*rt[pos].w*rt[pos] - rt2/7.0f *(delp.c.x*rt[pos].w*rt[pos] +delp.c.w*rt[pos].x*rt[pos] + delp.f.x*rt[pos].x*rt[pos] + delp.c*rt[pos].x*rt[pos].w + delp.c*rt[pos].w*rt[pos].x + delp.f*rt[pos].x*rt[pos].x) + rt4/35.0f*(delp.c.x*delp.f + delp.c.w*delp.c + delp.f.x*delp.c);
  }

 if(0==i && 1==j){
  result[pos].c = rt[pos].x*rt[pos].y*rt[pos].x*rt[pos] - rt2/7.0f *(delp.c.y*rt[pos].x*rt[pos] +delp.d.x*rt[pos].x*rt[pos] + delp.c.x*rt[pos].y*rt[pos] + delp.c*rt[pos].y*rt[pos].x + delp.d*rt[pos].x*rt[pos].x + delp.c*rt[pos].x*rt[pos].y) + rt4/35.0f*(delp.c.y*delp.c + delp.d.x*delp.c + delp.c.x*delp.d);
  result[pos].d = rt[pos].x*rt[pos].y*rt[pos].y*rt[pos] - rt2/7.0f *(delp.c.y*rt[pos].y*rt[pos] +delp.d.y*rt[pos].x*rt[pos] + delp.d.x*rt[pos].y*rt[pos] + delp.c*rt[pos].y*rt[pos].y + delp.d*rt[pos].y*rt[pos].x + delp.d*rt[pos].x*rt[pos].y) + rt4/35.0f*(delp.c.y*delp.d + delp.d.y*delp.c + delp.d.x*delp.d);
  result[pos].e = rt[pos].x*rt[pos].y*rt[pos].z*rt[pos] - rt2/7.0f *(delp.c.y*rt[pos].z*rt[pos] +delp.d.z*rt[pos].x*rt[pos] + delp.e.x*rt[pos].y*rt[pos] + delp.c*rt[pos].y*rt[pos].z + delp.d*rt[pos].z*rt[pos].x + delp.e*rt[pos].x*rt[pos].y) + rt4/35.0f*(delp.c.y*delp.e + delp.d.z*delp.c + delp.e.x*delp.d);
  result[pos].f = rt[pos].x*rt[pos].y*rt[pos].w*rt[pos] - rt2/7.0f *(delp.c.y*rt[pos].w*rt[pos] +delp.d.w*rt[pos].x*rt[pos] + delp.f.x*rt[pos].y*rt[pos] + delp.c*rt[pos].y*rt[pos].w + delp.d*rt[pos].w*rt[pos].x + delp.f*rt[pos].x*rt[pos].y) + rt4/35.0f*(delp.c.y*delp.f + delp.d.w*delp.c + delp.f.x*delp.d);
 }

 if(0==i && 2==j){
  result[pos].c = rt[pos].x*rt[pos].z*rt[pos].x*rt[pos] - rt2/7.0f *(delp.c.z*rt[pos].x*rt[pos] +delp.e.x*rt[pos].x*rt[pos] + delp.c.x*rt[pos].z*rt[pos] + delp.c*rt[pos].z*rt[pos].x + delp.e*rt[pos].x*rt[pos].x + delp.c*rt[pos].x*rt[pos].z) + rt4/35.0f*(delp.c.z*delp.c + delp.e.x*delp.c + delp.c.x*delp.e);
  result[pos].d = rt[pos].x*rt[pos].z*rt[pos].y*rt[pos] - rt2/7.0f *(delp.c.z*rt[pos].y*rt[pos] +delp.e.y*rt[pos].x*rt[pos] + delp.d.x*rt[pos].z*rt[pos] + delp.c*rt[pos].z*rt[pos].y + delp.e*rt[pos].y*rt[pos].x + delp.d*rt[pos].x*rt[pos].z) + rt4/35.0f*(delp.c.z*delp.d + delp.e.y*delp.c + delp.d.x*delp.e);
  result[pos].e = rt[pos].x*rt[pos].z*rt[pos].z*rt[pos] - rt2/7.0f *(delp.c.z*rt[pos].z*rt[pos] +delp.e.z*rt[pos].x*rt[pos] + delp.e.x*rt[pos].z*rt[pos] + delp.c*rt[pos].z*rt[pos].z + delp.e*rt[pos].z*rt[pos].x + delp.e*rt[pos].x*rt[pos].z) + rt4/35.0f*(delp.c.z*delp.e + delp.e.z*delp.c + delp.e.x*delp.e);
  result[pos].f = rt[pos].x*rt[pos].z*rt[pos].w*rt[pos] - rt2/7.0f *(delp.c.z*rt[pos].w*rt[pos] +delp.e.w*rt[pos].x*rt[pos] + delp.f.x*rt[pos].z*rt[pos] + delp.c*rt[pos].z*rt[pos].w + delp.e*rt[pos].w*rt[pos].x + delp.f*rt[pos].x*rt[pos].z) + rt4/35.0f*(delp.c.z*delp.f + delp.e.w*delp.c + delp.f.x*delp.e);
}

 if(0==i && 3==j){
  result[pos].c = rt[pos].x*rt[pos].w*rt[pos].x*rt[pos] - rt2/7.0f *(delp.c.w*rt[pos].x*rt[pos] +delp.f.x*rt[pos].x*rt[pos] + delp.c.x*rt[pos].w*rt[pos] + delp.c*rt[pos].w*rt[pos].x + delp.f*rt[pos].x*rt[pos].x + delp.c*rt[pos].x*rt[pos].w) + rt4/35.0f*(delp.c.w*delp.c + delp.f.x*delp.c + delp.c.x*delp.f);
  result[pos].d = rt[pos].x*rt[pos].w*rt[pos].y*rt[pos] - rt2/7.0f *(delp.c.w*rt[pos].y*rt[pos] +delp.f.y*rt[pos].x*rt[pos] + delp.d.x*rt[pos].w*rt[pos] + delp.c*rt[pos].w*rt[pos].y + delp.f*rt[pos].y*rt[pos].x + delp.d*rt[pos].x*rt[pos].w) + rt4/35.0f*(delp.c.w*delp.d + delp.f.y*delp.c + delp.d.x*delp.f);
  result[pos].e = rt[pos].x*rt[pos].w*rt[pos].z*rt[pos] - rt2/7.0f *(delp.c.w*rt[pos].z*rt[pos] +delp.f.z*rt[pos].x*rt[pos] + delp.e.x*rt[pos].w*rt[pos] + delp.c*rt[pos].w*rt[pos].z + delp.f*rt[pos].z*rt[pos].x + delp.e*rt[pos].x*rt[pos].w) + rt4/35.0f*(delp.c.w*delp.e + delp.f.z*delp.c + delp.e.x*delp.f);
  result[pos].f = rt[pos].x*rt[pos].w*rt[pos].w*rt[pos] - rt2/7.0f *(delp.c.w*rt[pos].w*rt[pos] +delp.f.w*rt[pos].x*rt[pos] + delp.f.x*rt[pos].w*rt[pos] + delp.c*rt[pos].w*rt[pos].w + delp.f*rt[pos].w*rt[pos].x + delp.f*rt[pos].x*rt[pos].w) + rt4/35.0f*(delp.c.w*delp.f + delp.f.w*delp.c + delp.f.x*delp.f);

}


  if(1==i && 0==j){
  result[pos].c = rt[pos].y*rt[pos].x*rt[pos].x*rt[pos] - rt2/7.0f *(delp.d.x*rt[pos].x*rt[pos] +delp.c.x*rt[pos].y*rt[pos] + delp.c.y*rt[pos].x*rt[pos] + delp.d*rt[pos].x*rt[pos].x + delp.c*rt[pos].x*rt[pos].y + delp.c*rt[pos].y*rt[pos].x) + rt4/35.0f*(delp.d.x*delp.c + delp.c.x*delp.d + delp.c.y*delp.c);
  result[pos].d = rt[pos].y*rt[pos].x*rt[pos].y*rt[pos] - rt2/7.0f *(delp.d.x*rt[pos].y*rt[pos] +delp.c.y*rt[pos].y*rt[pos] + delp.d.y*rt[pos].x*rt[pos] + delp.d*rt[pos].x*rt[pos].y + delp.c*rt[pos].y*rt[pos].y + delp.d*rt[pos].y*rt[pos].x) + rt4/35.0f*(delp.d.x*delp.d + delp.c.y*delp.d + delp.d.y*delp.c);
  result[pos].e = rt[pos].y*rt[pos].x*rt[pos].z*rt[pos] - rt2/7.0f *(delp.d.x*rt[pos].z*rt[pos] +delp.c.z*rt[pos].y*rt[pos] + delp.e.y*rt[pos].x*rt[pos] + delp.d*rt[pos].x*rt[pos].z + delp.c*rt[pos].z*rt[pos].y + delp.e*rt[pos].y*rt[pos].x) + rt4/35.0f*(delp.d.x*delp.e + delp.c.z*delp.d + delp.e.y*delp.c);
  result[pos].f = rt[pos].y*rt[pos].x*rt[pos].w*rt[pos] - rt2/7.0f *(delp.d.x*rt[pos].w*rt[pos] +delp.c.w*rt[pos].y*rt[pos] + delp.f.y*rt[pos].x*rt[pos] + delp.d*rt[pos].x*rt[pos].w + delp.c*rt[pos].w*rt[pos].y + delp.f*rt[pos].y*rt[pos].x) + rt4/35.0f*(delp.d.x*delp.f + delp.c.w*delp.d + delp.f.y*delp.c);
}


 if(1==i && 1==j){
  result[pos].c = rt[pos].y*rt[pos].y*rt[pos].x*rt[pos] - rt2/7.0f *(delp.d.y*rt[pos].x*rt[pos] +delp.d.x*rt[pos].y*rt[pos] + delp.c.y*rt[pos].y*rt[pos] + delp.d*rt[pos].y*rt[pos].x + delp.d*rt[pos].x*rt[pos].y + delp.c*rt[pos].y*rt[pos].y) + rt4/35.0f*(delp.d.y*delp.c + delp.d.x*delp.d + delp.c.y*delp.d);
  result[pos].d = rt[pos].y*rt[pos].y*rt[pos].y*rt[pos] - rt2/7.0f *(delp.d.y*rt[pos].y*rt[pos] +delp.d.y*rt[pos].y*rt[pos] + delp.d.y*rt[pos].y*rt[pos] + delp.d*rt[pos].y*rt[pos].y + delp.d*rt[pos].y*rt[pos].y + delp.d*rt[pos].y*rt[pos].y) + rt4/35.0f*(delp.d.y*delp.d + delp.d.y*delp.d + delp.d.y*delp.d);
  result[pos].e = rt[pos].y*rt[pos].y*rt[pos].z*rt[pos] - rt2/7.0f *(delp.d.y*rt[pos].z*rt[pos] +delp.d.z*rt[pos].y*rt[pos] + delp.e.y*rt[pos].y*rt[pos] + delp.d*rt[pos].y*rt[pos].z + delp.d*rt[pos].z*rt[pos].y + delp.e*rt[pos].y*rt[pos].y) + rt4/35.0f*(delp.d.y*delp.e + delp.d.z*delp.d + delp.e.y*delp.d);
  result[pos].f = rt[pos].y*rt[pos].y*rt[pos].w*rt[pos] - rt2/7.0f *(delp.d.y*rt[pos].w*rt[pos] +delp.d.w*rt[pos].y*rt[pos] + delp.f.y*rt[pos].y*rt[pos] + delp.d*rt[pos].y*rt[pos].w + delp.d*rt[pos].w*rt[pos].y + delp.f*rt[pos].y*rt[pos].y) + rt4/35.0f*(delp.d.y*delp.f + delp.d.w*delp.d + delp.f.y*delp.d);
 }

	
  if(1==i && 2==j){
  result[pos].c = rt[pos].y*rt[pos].z*rt[pos].x*rt[pos] - rt2/7.0f *(delp.d.z*rt[pos].x*rt[pos] +delp.e.x*rt[pos].y*rt[pos] + delp.c.y*rt[pos].z*rt[pos] + delp.d*rt[pos].z*rt[pos].x + delp.e*rt[pos].x*rt[pos].y + delp.c*rt[pos].y*rt[pos].z) + rt4/35.0f*(delp.d.z*delp.c + delp.e.x*delp.d + delp.c.y*delp.e);	
   result[pos].d = rt[pos].y*rt[pos].z*rt[pos].y*rt[pos] - rt2/7.0f *(delp.d.z*rt[pos].y*rt[pos] +delp.e.y*rt[pos].y*rt[pos] + delp.d.y*rt[pos].z*rt[pos] + delp.d*rt[pos].z*rt[pos].y + delp.e*rt[pos].y*rt[pos].y + delp.d*rt[pos].y*rt[pos].z) + rt4/35.0f*(delp.d.z*delp.d + delp.e.y*delp.d + delp.d.y*delp.e);
   result[pos].e = rt[pos].y*rt[pos].z*rt[pos].z*rt[pos] - rt2/7.0f *(delp.d.z*rt[pos].z*rt[pos] +delp.e.z*rt[pos].y*rt[pos] + delp.e.y*rt[pos].z*rt[pos] + delp.d*rt[pos].z*rt[pos].z + delp.e*rt[pos].z*rt[pos].y + delp.e*rt[pos].y*rt[pos].z) + rt4/35.0f*(delp.d.z*delp.e + delp.e.z*delp.d + delp.e.y*delp.e);
   result[pos].f = rt[pos].y*rt[pos].z*rt[pos].w*rt[pos] - rt2/7.0f *(delp.d.z*rt[pos].w*rt[pos] +delp.e.w*rt[pos].y*rt[pos] + delp.f.y*rt[pos].z*rt[pos] + delp.d*rt[pos].z*rt[pos].w + delp.e*rt[pos].w*rt[pos].y + delp.f*rt[pos].y*rt[pos].z) + rt4/35.0f*(delp.d.z*delp.f + delp.e.w*delp.d + delp.f.y*delp.e);
}


 if(1==i && 3==j){
   result[pos].c = rt[pos].y*rt[pos].w*rt[pos].x*rt[pos] - rt2/7.0f *(delp.d.w*rt[pos].x*rt[pos] +delp.f.x*rt[pos].y*rt[pos] + delp.c.y*rt[pos].w*rt[pos] + delp.d*rt[pos].w*rt[pos].x + delp.f*rt[pos].x*rt[pos].y + delp.c*rt[pos].y*rt[pos].w) + rt4/35.0f*(delp.d.w*delp.c + delp.f.x*delp.d + delp.c.y*delp.f);
   result[pos].d = rt[pos].y*rt[pos].w*rt[pos].y*rt[pos] - rt2/7.0f *(delp.d.w*rt[pos].y*rt[pos] +delp.f.y*rt[pos].y*rt[pos] + delp.d.y*rt[pos].w*rt[pos] + delp.d*rt[pos].w*rt[pos].y + delp.f*rt[pos].y*rt[pos].y + delp.d*rt[pos].y*rt[pos].w) + rt4/35.0f*(delp.d.w*delp.d + delp.f.y*delp.d + delp.d.y*delp.f);
   result[pos].e = rt[pos].y*rt[pos].w*rt[pos].z*rt[pos] - rt2/7.0f *(delp.d.w*rt[pos].z*rt[pos] +delp.f.z*rt[pos].y*rt[pos] + delp.e.y*rt[pos].w*rt[pos] + delp.d*rt[pos].w*rt[pos].z + delp.f*rt[pos].z*rt[pos].y + delp.e*rt[pos].y*rt[pos].w) + rt4/35.0f*(delp.d.w*delp.e + delp.f.z*delp.d + delp.e.y*delp.f);
   result[pos].f = rt[pos].y*rt[pos].w*rt[pos].w*rt[pos] - rt2/7.0f *(delp.d.w*rt[pos].w*rt[pos] +delp.f.w*rt[pos].y*rt[pos] + delp.f.y*rt[pos].w*rt[pos] + delp.d*rt[pos].w*rt[pos].w + delp.f*rt[pos].w*rt[pos].y + delp.f*rt[pos].y*rt[pos].w) + rt4/35.0f*(delp.d.w*delp.f + delp.f.w*delp.d + delp.f.y*delp.f);
}



  if(2==i && 0==j){
    result[pos].c = rt[pos].z*rt[pos].x*rt[pos].x*rt[pos] - rt2/7.0f *(delp.e.x*rt[pos].x*rt[pos] +delp.c.x*rt[pos].z*rt[pos] + delp.c.z*rt[pos].x*rt[pos] + delp.e*rt[pos].x*rt[pos].x + delp.c*rt[pos].x*rt[pos].z + delp.c*rt[pos].z*rt[pos].x) + rt4/35.0f*(delp.e.x*delp.c + delp.c.x*delp.e + delp.c.z*delp.c);
    result[pos].d = rt[pos].z*rt[pos].x*rt[pos].y*rt[pos] - rt2/7.0f *(delp.e.x*rt[pos].y*rt[pos] +delp.c.y*rt[pos].z*rt[pos] + delp.d.z*rt[pos].x*rt[pos] + delp.e*rt[pos].x*rt[pos].y + delp.c*rt[pos].y*rt[pos].z + delp.d*rt[pos].z*rt[pos].x) + rt4/35.0f*(delp.e.x*delp.d + delp.c.y*delp.e + delp.d.z*delp.c);
    result[pos].e = rt[pos].z*rt[pos].x*rt[pos].z*rt[pos] - rt2/7.0f *(delp.e.x*rt[pos].z*rt[pos] +delp.c.z*rt[pos].z*rt[pos] + delp.e.z*rt[pos].x*rt[pos] + delp.e*rt[pos].x*rt[pos].z + delp.c*rt[pos].z*rt[pos].z + delp.e*rt[pos].z*rt[pos].x) + rt4/35.0f*(delp.e.x*delp.e + delp.c.z*delp.e + delp.e.z*delp.c);
    result[pos].f = rt[pos].z*rt[pos].x*rt[pos].w*rt[pos] - rt2/7.0f *(delp.e.x*rt[pos].w*rt[pos] +delp.c.w*rt[pos].z*rt[pos] + delp.f.z*rt[pos].x*rt[pos] + delp.e*rt[pos].x*rt[pos].w + delp.c*rt[pos].w*rt[pos].z + delp.f*rt[pos].z*rt[pos].x) + rt4/35.0f*(delp.e.x*delp.f + delp.c.w*delp.e + delp.f.z*delp.c);
}
	
    if(2==i && 1==j){
    result[pos].c = rt[pos].z*rt[pos].y*rt[pos].x*rt[pos] - rt2/7.0f *(delp.e.y*rt[pos].x*rt[pos] +delp.d.x*rt[pos].z*rt[pos] + delp.c.z*rt[pos].y*rt[pos] + delp.e*rt[pos].y*rt[pos].x + delp.d*rt[pos].x*rt[pos].z + delp.c*rt[pos].z*rt[pos].y) + rt4/35.0f*(delp.e.y*delp.c + delp.d.x*delp.e + delp.c.z*delp.d);
    result[pos].d = rt[pos].z*rt[pos].y*rt[pos].y*rt[pos] - rt2/7.0f *(delp.e.y*rt[pos].y*rt[pos] +delp.d.y*rt[pos].z*rt[pos] + delp.d.z*rt[pos].y*rt[pos] + delp.e*rt[pos].y*rt[pos].y + delp.d*rt[pos].y*rt[pos].z + delp.d*rt[pos].z*rt[pos].y) + rt4/35.0f*(delp.e.y*delp.d + delp.d.y*delp.e + delp.d.z*delp.d);
    result[pos].e = rt[pos].z*rt[pos].y*rt[pos].z*rt[pos] - rt2/7.0f *(delp.e.y*rt[pos].z*rt[pos] +delp.d.z*rt[pos].z*rt[pos] + delp.e.z*rt[pos].y*rt[pos] + delp.e*rt[pos].y*rt[pos].z + delp.d*rt[pos].z*rt[pos].z + delp.e*rt[pos].z*rt[pos].y) + rt4/35.0f*(delp.e.y*delp.e + delp.d.z*delp.e + delp.e.z*delp.d);
    result[pos].f = rt[pos].z*rt[pos].y*rt[pos].w*rt[pos] - rt2/7.0f *(delp.e.y*rt[pos].w*rt[pos] +delp.d.w*rt[pos].z*rt[pos] + delp.f.z*rt[pos].y*rt[pos] + delp.e*rt[pos].y*rt[pos].w + delp.d*rt[pos].w*rt[pos].z + delp.f*rt[pos].z*rt[pos].y) + rt4/35.0f*(delp.e.y*delp.f + delp.d.w*delp.e + delp.f.z*delp.d);
}
 
   if(2==i && 2==j){
   result[pos].c = rt[pos].z*rt[pos].z*rt[pos].x*rt[pos] - rt2/7.0f *(delp.e.z*rt[pos].x*rt[pos] +delp.e.x*rt[pos].z*rt[pos] + delp.c.z*rt[pos].z*rt[pos] + delp.e*rt[pos].z*rt[pos].x + delp.e*rt[pos].x*rt[pos].z + delp.c*rt[pos].z*rt[pos].z) + rt4/35.0f*(delp.e.z*delp.c + delp.e.x*delp.e + delp.c.z*delp.e);
   result[pos].d = rt[pos].z*rt[pos].z*rt[pos].y*rt[pos] - rt2/7.0f *(delp.e.z*rt[pos].y*rt[pos] +delp.e.y*rt[pos].z*rt[pos] + delp.d.z*rt[pos].z*rt[pos] + delp.e*rt[pos].z*rt[pos].y + delp.e*rt[pos].y*rt[pos].z + delp.d*rt[pos].z*rt[pos].z) + rt4/35.0f*(delp.e.z*delp.d + delp.e.y*delp.e + delp.d.z*delp.e);
   result[pos].e = rt[pos].z*rt[pos].z*rt[pos].z*rt[pos] - rt2/7.0f *(delp.e.z*rt[pos].z*rt[pos] +delp.e.z*rt[pos].z*rt[pos] + delp.e.z*rt[pos].z*rt[pos] + delp.e*rt[pos].z*rt[pos].z + delp.e*rt[pos].z*rt[pos].z + delp.e*rt[pos].z*rt[pos].z) + rt4/35.0f*(delp.e.z*delp.e + delp.e.z*delp.e + delp.e.z*delp.e);
   result[pos].f = rt[pos].z*rt[pos].z*rt[pos].w*rt[pos] - rt2/7.0f *(delp.e.z*rt[pos].w*rt[pos] +delp.e.w*rt[pos].z*rt[pos] + delp.f.z*rt[pos].z*rt[pos] + delp.e*rt[pos].z*rt[pos].w + delp.e*rt[pos].w*rt[pos].z + delp.f*rt[pos].z*rt[pos].z) + rt4/35.0f*(delp.e.z*delp.f + delp.e.w*delp.e + delp.f.z*delp.e);
}
   if(2==i && 3==j){
   result[pos].c = rt[pos].z*rt[pos].w*rt[pos].x*rt[pos] - rt2/7.0f *(delp.e.w*rt[pos].x*rt[pos] +delp.f.x*rt[pos].z*rt[pos] + delp.c.z*rt[pos].w*rt[pos] + delp.e*rt[pos].w*rt[pos].x + delp.f*rt[pos].x*rt[pos].z + delp.c*rt[pos].z*rt[pos].w) + rt4/35.0f*(delp.e.w*delp.c + delp.f.x*delp.e + delp.c.z*delp.f);
   result[pos].d = rt[pos].z*rt[pos].w*rt[pos].y*rt[pos] - rt2/7.0f *(delp.e.w*rt[pos].y*rt[pos] +delp.f.y*rt[pos].z*rt[pos] + delp.d.z*rt[pos].w*rt[pos] + delp.e*rt[pos].w*rt[pos].y + delp.f*rt[pos].y*rt[pos].z + delp.d*rt[pos].z*rt[pos].w) + rt4/35.0f*(delp.e.w*delp.d + delp.f.y*delp.e + delp.d.z*delp.f);
   result[pos].e = rt[pos].z*rt[pos].w*rt[pos].z*rt[pos] - rt2/7.0f *(delp.e.w*rt[pos].z*rt[pos] +delp.f.z*rt[pos].z*rt[pos] + delp.e.z*rt[pos].w*rt[pos] + delp.e*rt[pos].w*rt[pos].z + delp.f*rt[pos].z*rt[pos].z + delp.e*rt[pos].z*rt[pos].w) + rt4/35.0f*(delp.e.w*delp.e + delp.f.z*delp.e + delp.e.z*delp.f);		
   result[pos].f = rt[pos].z*rt[pos].w*rt[pos].w*rt[pos] - rt2/7.0f *(delp.e.w*rt[pos].w*rt[pos] +delp.f.w*rt[pos].z*rt[pos] + delp.f.z*rt[pos].w*rt[pos] + delp.e*rt[pos].w*rt[pos].w + delp.f*rt[pos].w*rt[pos].z + delp.f*rt[pos].z*rt[pos].w) + rt4/35.0f*(delp.e.w*delp.f + delp.f.w*delp.e + delp.f.z*delp.f);
}


  if(3==i && 0==j){
  result[pos].c = rt[pos].w*rt[pos].x*rt[pos].x*rt[pos] - rt2/7.0f *(delp.f.x*rt[pos].x*rt[pos] +delp.c.x*rt[pos].w*rt[pos] + delp.c.w*rt[pos].x*rt[pos] + delp.f*rt[pos].x*rt[pos].x + delp.c*rt[pos].x*rt[pos].w + delp.c*rt[pos].w*rt[pos].x) + rt4/35.0f*(delp.f.x*delp.c + delp.c.x*delp.f + delp.c.w*delp.c);
  result[pos].d = rt[pos].w*rt[pos].x*rt[pos].y*rt[pos] - rt2/7.0f *(delp.f.x*rt[pos].y*rt[pos] +delp.c.y*rt[pos].w*rt[pos] + delp.d.w*rt[pos].x*rt[pos] + delp.f*rt[pos].x*rt[pos].y + delp.c*rt[pos].y*rt[pos].w + delp.d*rt[pos].w*rt[pos].x) + rt4/35.0f*(delp.f.x*delp.d + delp.c.y*delp.f + delp.d.w*delp.c);
  result[pos].e = rt[pos].w*rt[pos].x*rt[pos].z*rt[pos] - rt2/7.0f *(delp.f.x*rt[pos].z*rt[pos] +delp.c.z*rt[pos].w*rt[pos] + delp.e.w*rt[pos].x*rt[pos] + delp.f*rt[pos].x*rt[pos].z + delp.c*rt[pos].z*rt[pos].w + delp.e*rt[pos].w*rt[pos].x) + rt4/35.0f*(delp.f.x*delp.e + delp.c.z*delp.f + delp.e.w*delp.c);
  result[pos].f = rt[pos].w*rt[pos].x*rt[pos].w*rt[pos] - rt2/7.0f *(delp.f.x*rt[pos].w*rt[pos] +delp.c.w*rt[pos].w*rt[pos] + delp.f.w*rt[pos].x*rt[pos] + delp.f*rt[pos].x*rt[pos].w + delp.c*rt[pos].w*rt[pos].w + delp.f*rt[pos].w*rt[pos].x) + rt4/35.0f*(delp.f.x*delp.f + delp.c.w*delp.f + delp.f.w*delp.c);
}
	
  if(3==i && 1==j){	
  result[pos].c = rt[pos].w*rt[pos].y*rt[pos].x*rt[pos] - rt2/7.0f *(delp.f.y*rt[pos].x*rt[pos] +delp.d.x*rt[pos].w*rt[pos] + delp.c.w*rt[pos].y*rt[pos] + delp.f*rt[pos].y*rt[pos].x + delp.d*rt[pos].x*rt[pos].w + delp.c*rt[pos].w*rt[pos].y) + rt4/35.0f*(delp.f.y*delp.c + delp.d.x*delp.f + delp.c.w*delp.d);
  result[pos].d = rt[pos].w*rt[pos].y*rt[pos].y*rt[pos] - rt2/7.0f *(delp.f.y*rt[pos].y*rt[pos] +delp.d.y*rt[pos].w*rt[pos] + delp.d.w*rt[pos].y*rt[pos] + delp.f*rt[pos].y*rt[pos].y + delp.d*rt[pos].y*rt[pos].w + delp.d*rt[pos].w*rt[pos].y) + rt4/35.0f*(delp.f.y*delp.d + delp.d.y*delp.f + delp.d.w*delp.d);
  result[pos].e = rt[pos].w*rt[pos].y*rt[pos].z*rt[pos] - rt2/7.0f *(delp.f.y*rt[pos].z*rt[pos] +delp.d.z*rt[pos].w*rt[pos] + delp.e.w*rt[pos].y*rt[pos] + delp.f*rt[pos].y*rt[pos].z + delp.d*rt[pos].z*rt[pos].w + delp.e*rt[pos].w*rt[pos].y) + rt4/35.0f*(delp.f.y*delp.e + delp.d.z*delp.f + delp.e.w*delp.d);
  result[pos].f = rt[pos].w*rt[pos].y*rt[pos].w*rt[pos] - rt2/7.0f *(delp.f.y*rt[pos].w*rt[pos] +delp.d.w*rt[pos].w*rt[pos] + delp.f.w*rt[pos].y*rt[pos] + delp.f*rt[pos].y*rt[pos].w + delp.d*rt[pos].w*rt[pos].w + delp.f*rt[pos].w*rt[pos].y) + rt4/35.0f*(delp.f.y*delp.f + delp.d.w*delp.f + delp.f.w*delp.d);
}

   if(3==i && 2==j){
   result[pos].c = rt[pos].w*rt[pos].z*rt[pos].x*rt[pos] - rt2/7.0f *(delp.f.z*rt[pos].x*rt[pos] +delp.e.x*rt[pos].w*rt[pos] + delp.c.w*rt[pos].z*rt[pos] + delp.f*rt[pos].z*rt[pos].x + delp.e*rt[pos].x*rt[pos].w + delp.c*rt[pos].w*rt[pos].z) + rt4/35.0f*(delp.f.z*delp.c + delp.e.x*delp.f + delp.c.w*delp.e);
   result[pos].d = rt[pos].w*rt[pos].z*rt[pos].y*rt[pos] - rt2/7.0f *(delp.f.z*rt[pos].y*rt[pos] +delp.e.y*rt[pos].w*rt[pos] + delp.d.w*rt[pos].z*rt[pos] + delp.f*rt[pos].z*rt[pos].y + delp.e*rt[pos].y*rt[pos].w + delp.d*rt[pos].w*rt[pos].z) + rt4/35.0f*(delp.f.z*delp.d + delp.e.y*delp.f + delp.d.w*delp.e);
   result[pos].e = rt[pos].w*rt[pos].z*rt[pos].z*rt[pos] - rt2/7.0f *(delp.f.z*rt[pos].z*rt[pos] +delp.e.z*rt[pos].w*rt[pos] + delp.e.w*rt[pos].z*rt[pos] + delp.f*rt[pos].z*rt[pos].z + delp.e*rt[pos].z*rt[pos].w + delp.e*rt[pos].w*rt[pos].z) + rt4/35.0f*(delp.f.z*delp.e + delp.e.z*delp.f + delp.e.w*delp.e);
   result[pos].f = rt[pos].w*rt[pos].z*rt[pos].w*rt[pos] - rt2/7.0f *(delp.f.z*rt[pos].w*rt[pos] +delp.e.w*rt[pos].w*rt[pos] + delp.f.w*rt[pos].z*rt[pos] + delp.f*rt[pos].z*rt[pos].w + delp.e*rt[pos].w*rt[pos].w + delp.f*rt[pos].w*rt[pos].z) + rt4/35.0f*(delp.f.z*delp.f + delp.e.w*delp.f + delp.f.w*delp.e);		
}
	
  if(3==i && 3==j){
  result[pos].c = rt[pos].w*rt[pos].w*rt[pos].x*rt[pos] - rt2/7.0f *(delp.f.w*rt[pos].x*rt[pos] +delp.f.x*rt[pos].w*rt[pos] + delp.c.w*rt[pos].w*rt[pos] + delp.f*rt[pos].w*rt[pos].x + delp.f*rt[pos].x*rt[pos].w + delp.c*rt[pos].w*rt[pos].w) + rt4/35.0f*(delp.f.w*delp.c + delp.f.x*delp.f + delp.c.w*delp.f);
  result[pos].d = rt[pos].w*rt[pos].w*rt[pos].y*rt[pos] - rt2/7.0f *(delp.f.w*rt[pos].y*rt[pos] +delp.f.y*rt[pos].w*rt[pos] + delp.d.w*rt[pos].w*rt[pos] + delp.f*rt[pos].w*rt[pos].y + delp.f*rt[pos].y*rt[pos].w + delp.d*rt[pos].w*rt[pos].w) + rt4/35.0f*(delp.f.w*delp.d + delp.f.y*delp.f + delp.d.w*delp.f);
  result[pos].e = rt[pos].w*rt[pos].w*rt[pos].z*rt[pos] - rt2/7.0f *(delp.f.w*rt[pos].z*rt[pos] +delp.f.z*rt[pos].w*rt[pos] + delp.e.w*rt[pos].w*rt[pos] + delp.f*rt[pos].w*rt[pos].z + delp.f*rt[pos].z*rt[pos].w + delp.e*rt[pos].w*rt[pos].w) + rt4/35.0f*(delp.f.w*delp.e + delp.f.z*delp.f + delp.e.w*delp.f);
  result[pos].f = rt[pos].w*rt[pos].w*rt[pos].w*rt[pos] - rt2/7.0f *(delp.f.w*rt[pos].w*rt[pos] +delp.f.w*rt[pos].w*rt[pos] + delp.f.w*rt[pos].w*rt[pos] + delp.f*rt[pos].w*rt[pos].w + delp.f*rt[pos].w*rt[pos].w + delp.f*rt[pos].w*rt[pos].w) + rt4/35.0f*(delp.f.w*delp.f + delp.f.w*delp.f + delp.f.w*delp.f);
}

}


__kernel void kernel3orbitaltensor(__global float4 * rt, __global float4 * pa, __global out float444 * result){
	
	uint pos = get_global_id(0);
	
	float pa2;
	float rt2;
	float4 gpac;
	float4 gpad;
	float4 gpae;
	float4 gpaf;
	
	pa2 = -pa[pos].x*pa[pos].x-pa[pos].y*pa[pos].y-pa[pos].z*pa[pos].z + pa[pos].w*pa[pos].w;
	rt2 = -rt[pos].x*rt[pos].x-rt[pos].y*rt[pos].y-rt[pos].z*rt[pos].z + rt[pos].w*rt[pos].w;

	
	gpac   =     -pa[pos].x*pa[pos]/pa2;
	gpac.x = gpac.x -1.0f;
	
	gpad   =     -pa[pos].y*pa[pos]/pa2;
	gpad.y = gpad.y -1.0f;
	
	gpae   =     -pa[pos].z*pa[pos]/pa2;
	gpae.z = gpae.z -1.0f;
	
	gpaf   =     -pa[pos].w*pa[pos]/pa2;
	gpaf.w = gpaf.w +1.0f;
	
	result[pos].cc.x = rt[pos].x*rt[pos].x*rt[pos].x - 0.2f*rt2*(gpac.x*rt[pos].x + gpac.x*rt[pos].x + gpac.x*rt[pos].x);
	result[pos].cc.y = rt[pos].x*rt[pos].x*rt[pos].y - 0.2f*rt2*(gpac.x*rt[pos].y + gpac.y*rt[pos].x + gpad.x*rt[pos].x);
	result[pos].cc.z = rt[pos].x*rt[pos].x*rt[pos].z - 0.2f*rt2*(gpac.x*rt[pos].z + gpac.z*rt[pos].x + gpae.x*rt[pos].x);
	result[pos].cc.w = rt[pos].x*rt[pos].x*rt[pos].w - 0.2f*rt2*(gpac.x*rt[pos].w + gpac.w*rt[pos].x + gpaf.x*rt[pos].x);
	
	result[pos].cd.x = rt[pos].x*rt[pos].y*rt[pos].x - 0.2f*rt2*(gpac.y*rt[pos].x + gpad.x*rt[pos].x + gpac.x*rt[pos].y);
	result[pos].cd.y = rt[pos].x*rt[pos].y*rt[pos].y - 0.2f*rt2*(gpac.y*rt[pos].y + gpad.y*rt[pos].x + gpad.x*rt[pos].y);
	result[pos].cd.z = rt[pos].x*rt[pos].y*rt[pos].z - 0.2f*rt2*(gpac.y*rt[pos].z + gpad.z*rt[pos].x + gpae.x*rt[pos].y);
	result[pos].cd.w = rt[pos].x*rt[pos].y*rt[pos].w - 0.2f*rt2*(gpac.y*rt[pos].w + gpad.w*rt[pos].x + gpaf.x*rt[pos].y);
	
	result[pos].ce.x = rt[pos].x*rt[pos].z*rt[pos].x - 0.2f*rt2*(gpac.z*rt[pos].x + gpae.x*rt[pos].x + gpac.x*rt[pos].z);
	result[pos].ce.y = rt[pos].x*rt[pos].z*rt[pos].y - 0.2f*rt2*(gpac.z*rt[pos].y + gpae.y*rt[pos].x + gpad.x*rt[pos].z);
	result[pos].ce.z = rt[pos].x*rt[pos].z*rt[pos].z - 0.2f*rt2*(gpac.z*rt[pos].z + gpae.z*rt[pos].x + gpae.x*rt[pos].z);
	result[pos].ce.w = rt[pos].x*rt[pos].z*rt[pos].w - 0.2f*rt2*(gpac.z*rt[pos].w + gpae.w*rt[pos].x + gpaf.x*rt[pos].z);
	
	result[pos].cf.x = rt[pos].x*rt[pos].w*rt[pos].x - 0.2f*rt2*(gpac.w*rt[pos].x + gpaf.x*rt[pos].x + gpac.x*rt[pos].w);
	result[pos].cf.y = rt[pos].x*rt[pos].w*rt[pos].y - 0.2f*rt2*(gpac.w*rt[pos].y + gpaf.y*rt[pos].x + gpad.x*rt[pos].w);
	result[pos].cf.z = rt[pos].x*rt[pos].w*rt[pos].z - 0.2f*rt2*(gpac.w*rt[pos].z + gpaf.z*rt[pos].x + gpae.x*rt[pos].w);
	result[pos].cf.w = rt[pos].x*rt[pos].w*rt[pos].w - 0.2f*rt2*(gpac.w*rt[pos].w + gpaf.w*rt[pos].x + gpaf.x*rt[pos].w);
	
	/**/
	result[pos].dc.x = rt[pos].y*rt[pos].x*rt[pos].x - 0.2f*rt2*(gpad.x*rt[pos].x + gpac.x*rt[pos].y + gpac.y*rt[pos].x);
	result[pos].dc.y = rt[pos].y*rt[pos].x*rt[pos].y - 0.2f*rt2*(gpad.x*rt[pos].y + gpac.y*rt[pos].y + gpad.y*rt[pos].x);
	result[pos].dc.z = rt[pos].y*rt[pos].x*rt[pos].z - 0.2f*rt2*(gpad.x*rt[pos].z + gpac.z*rt[pos].y + gpae.y*rt[pos].x);
	result[pos].dc.w = rt[pos].y*rt[pos].x*rt[pos].w - 0.2f*rt2*(gpad.x*rt[pos].w + gpac.w*rt[pos].y + gpaf.y*rt[pos].x);
	
	result[pos].dd.x = rt[pos].y*rt[pos].y*rt[pos].x - 0.2f*rt2*(gpad.y*rt[pos].x + gpad.x*rt[pos].y + gpac.y*rt[pos].y);
	result[pos].dd.y = rt[pos].y*rt[pos].y*rt[pos].y - 0.2f*rt2*(gpad.y*rt[pos].y + gpad.y*rt[pos].y + gpad.y*rt[pos].y);
	result[pos].dd.z = rt[pos].y*rt[pos].y*rt[pos].z - 0.2f*rt2*(gpad.y*rt[pos].z + gpad.z*rt[pos].y + gpae.y*rt[pos].y);
	result[pos].dd.w = rt[pos].y*rt[pos].y*rt[pos].w - 0.2f*rt2*(gpad.y*rt[pos].w + gpad.w*rt[pos].y + gpaf.y*rt[pos].y);
	
	result[pos].de.x = rt[pos].y*rt[pos].z*rt[pos].x - 0.2f*rt2*(gpad.z*rt[pos].x + gpae.x*rt[pos].y + gpac.y*rt[pos].z);
	result[pos].de.y = rt[pos].y*rt[pos].z*rt[pos].y - 0.2f*rt2*(gpad.z*rt[pos].y + gpae.y*rt[pos].y + gpad.y*rt[pos].z);
	result[pos].de.z = rt[pos].y*rt[pos].z*rt[pos].z - 0.2f*rt2*(gpad.z*rt[pos].z + gpae.z*rt[pos].y + gpae.y*rt[pos].z);
	result[pos].de.w = rt[pos].y*rt[pos].z*rt[pos].w - 0.2f*rt2*(gpad.z*rt[pos].w + gpae.w*rt[pos].y + gpaf.y*rt[pos].z);
	
	result[pos].df.x = rt[pos].y*rt[pos].w*rt[pos].x - 0.2f*rt2*(gpad.w*rt[pos].x + gpaf.x*rt[pos].y + gpac.y*rt[pos].w);
	result[pos].df.y = rt[pos].y*rt[pos].w*rt[pos].y - 0.2f*rt2*(gpad.w*rt[pos].y + gpaf.y*rt[pos].y + gpad.y*rt[pos].w);
	result[pos].df.z = rt[pos].y*rt[pos].w*rt[pos].z - 0.2f*rt2*(gpad.w*rt[pos].z + gpaf.z*rt[pos].y + gpae.y*rt[pos].w);
	result[pos].df.w = rt[pos].y*rt[pos].w*rt[pos].w - 0.2f*rt2*(gpad.w*rt[pos].w + gpaf.w*rt[pos].y + gpaf.y*rt[pos].w);
	
	/**/
	result[pos].ec.x = rt[pos].z*rt[pos].x*rt[pos].x - 0.2f*rt2*(gpae.x*rt[pos].x + gpac.x*rt[pos].z + gpac.z*rt[pos].x);
	result[pos].ec.y = rt[pos].z*rt[pos].x*rt[pos].y - 0.2f*rt2*(gpae.x*rt[pos].y + gpac.y*rt[pos].z + gpad.z*rt[pos].x);
	result[pos].ec.z = rt[pos].z*rt[pos].x*rt[pos].z - 0.2f*rt2*(gpae.x*rt[pos].z + gpac.z*rt[pos].z + gpae.z*rt[pos].x);
	result[pos].ec.w = rt[pos].z*rt[pos].x*rt[pos].w - 0.2f*rt2*(gpae.x*rt[pos].w + gpac.w*rt[pos].z + gpaf.z*rt[pos].x);
	
	result[pos].ed.x = rt[pos].z*rt[pos].y*rt[pos].x - 0.2f*rt2*(gpae.y*rt[pos].x + gpad.x*rt[pos].z + gpac.z*rt[pos].y);
	result[pos].ed.y = rt[pos].z*rt[pos].y*rt[pos].y - 0.2f*rt2*(gpae.y*rt[pos].y + gpad.y*rt[pos].z + gpad.z*rt[pos].y);
	result[pos].ed.z = rt[pos].z*rt[pos].y*rt[pos].z - 0.2f*rt2*(gpae.y*rt[pos].z + gpad.z*rt[pos].z + gpae.z*rt[pos].y);
	result[pos].ed.w = rt[pos].z*rt[pos].y*rt[pos].w - 0.2f*rt2*(gpae.y*rt[pos].w + gpad.w*rt[pos].z + gpaf.z*rt[pos].y);
	
	result[pos].ee.x = rt[pos].z*rt[pos].z*rt[pos].x - 0.2f*rt2*(gpae.z*rt[pos].x + gpae.x*rt[pos].z + gpac.z*rt[pos].z);
	result[pos].ee.y = rt[pos].z*rt[pos].z*rt[pos].y - 0.2f*rt2*(gpae.z*rt[pos].y + gpae.y*rt[pos].z + gpad.z*rt[pos].z);
	result[pos].ee.z = rt[pos].z*rt[pos].z*rt[pos].z - 0.2f*rt2*(gpae.z*rt[pos].z + gpae.z*rt[pos].z + gpae.z*rt[pos].z);
	result[pos].ee.w = rt[pos].z*rt[pos].z*rt[pos].w - 0.2f*rt2*(gpae.z*rt[pos].w + gpae.w*rt[pos].z + gpaf.z*rt[pos].z);
	
	result[pos].ef.x = rt[pos].z*rt[pos].w*rt[pos].x - 0.2f*rt2*(gpae.w*rt[pos].x + gpaf.x*rt[pos].z + gpac.z*rt[pos].w);
	result[pos].ef.y = rt[pos].z*rt[pos].w*rt[pos].y - 0.2f*rt2*(gpae.w*rt[pos].y + gpaf.y*rt[pos].z + gpad.z*rt[pos].w);
	result[pos].ef.z = rt[pos].z*rt[pos].w*rt[pos].z - 0.2f*rt2*(gpae.w*rt[pos].z + gpaf.z*rt[pos].z + gpae.z*rt[pos].w);
	result[pos].ef.w = rt[pos].z*rt[pos].w*rt[pos].w - 0.2f*rt2*(gpae.w*rt[pos].w + gpaf.w*rt[pos].z + gpaf.z*rt[pos].w);
	
	/**/
	result[pos].fc.x = rt[pos].w*rt[pos].x*rt[pos].x - 0.2f*rt2*(gpaf.x*rt[pos].x + gpac.x*rt[pos].w + gpac.w*rt[pos].x);
	result[pos].fc.y = rt[pos].w*rt[pos].x*rt[pos].y - 0.2f*rt2*(gpaf.x*rt[pos].y + gpac.y*rt[pos].w + gpad.w*rt[pos].x);
	result[pos].fc.z = rt[pos].w*rt[pos].x*rt[pos].z - 0.2f*rt2*(gpaf.x*rt[pos].z + gpac.z*rt[pos].w + gpae.w*rt[pos].x);
	result[pos].fc.w = rt[pos].w*rt[pos].x*rt[pos].w - 0.2f*rt2*(gpaf.x*rt[pos].w + gpac.w*rt[pos].w + gpaf.w*rt[pos].x);
	
	result[pos].fd.x = rt[pos].w*rt[pos].y*rt[pos].x - 0.2f*rt2*(gpaf.y*rt[pos].x + gpad.x*rt[pos].w + gpac.w*rt[pos].y);
	result[pos].fd.y = rt[pos].w*rt[pos].y*rt[pos].y - 0.2f*rt2*(gpaf.y*rt[pos].y + gpad.y*rt[pos].w + gpad.w*rt[pos].y);
	result[pos].fd.z = rt[pos].w*rt[pos].y*rt[pos].z - 0.2f*rt2*(gpaf.y*rt[pos].z + gpad.z*rt[pos].w + gpae.w*rt[pos].y);
	result[pos].fd.w = rt[pos].w*rt[pos].y*rt[pos].w - 0.2f*rt2*(gpaf.y*rt[pos].w + gpad.w*rt[pos].w + gpaf.w*rt[pos].y);

	result[pos].fe.x = rt[pos].w*rt[pos].z*rt[pos].x - 0.2f*rt2*(gpaf.z*rt[pos].x + gpae.x*rt[pos].w + gpac.w*rt[pos].z);
	result[pos].fe.y = rt[pos].w*rt[pos].z*rt[pos].y - 0.2f*rt2*(gpaf.z*rt[pos].y + gpae.y*rt[pos].w + gpad.w*rt[pos].z);
	result[pos].fe.z = rt[pos].w*rt[pos].z*rt[pos].z - 0.2f*rt2*(gpaf.z*rt[pos].z + gpae.z*rt[pos].w + gpae.w*rt[pos].z);
	result[pos].fe.w = rt[pos].w*rt[pos].z*rt[pos].w - 0.2f*rt2*(gpaf.z*rt[pos].w + gpae.w*rt[pos].w + gpaf.w*rt[pos].z);
	
	result[pos].ff.x = rt[pos].w*rt[pos].w*rt[pos].x - 0.2f*rt2*(gpaf.w*rt[pos].x + gpaf.x*rt[pos].w + gpac.w*rt[pos].w);
	result[pos].ff.y = rt[pos].w*rt[pos].w*rt[pos].y - 0.2f*rt2*(gpaf.w*rt[pos].y + gpaf.y*rt[pos].w + gpad.w*rt[pos].w);
	result[pos].ff.z = rt[pos].w*rt[pos].w*rt[pos].z - 0.2f*rt2*(gpaf.w*rt[pos].z + gpaf.z*rt[pos].w + gpae.w*rt[pos].w);
	result[pos].ff.w = rt[pos].w*rt[pos].w*rt[pos].w - 0.2f*rt2*(gpaf.w*rt[pos].w + gpaf.w*rt[pos].w + gpaf.w*rt[pos].w);
}


__kernel void kernel3orbitaltensorconst(__global float4 * rt, float4 pa, __global out float444 * result){
	
	uint pos = get_global_id(0);
	
	float pa2;
	float rt2;
	float4 gpac;
	float4 gpad;
	float4 gpae;
	float4 gpaf;
	
	pa2 = -pa.x*pa.x-pa.y*pa.y-pa.z*pa.z + pa.w*pa.w;
	rt2 = -rt[pos].x*rt[pos].x-rt[pos].y*rt[pos].y-rt[pos].z*rt[pos].z + rt[pos].w*rt[pos].w;

	
	gpac   =     -pa.x*pa/pa2;
	gpac.x = gpac.x -1.0f;
	
	gpad   =     -pa.y*pa/pa2;
	gpad.y = gpad.y -1.0f;
	
	gpae   =     -pa.z*pa/pa2;
	gpae.z = gpae.z -1.0f;
	
	gpaf   =     -pa.w*pa/pa2;
	gpaf.w = gpaf.w +1.0f;
	
	result[pos].cc.x = rt[pos].x*rt[pos].x*rt[pos].x - 0.2f*rt2*(gpac.x*rt[pos].x + gpac.x*rt[pos].x + gpac.x*rt[pos].x);
	result[pos].cc.y = rt[pos].x*rt[pos].x*rt[pos].y - 0.2f*rt2*(gpac.x*rt[pos].y + gpac.y*rt[pos].x + gpad.x*rt[pos].x);
	result[pos].cc.z = rt[pos].x*rt[pos].x*rt[pos].z - 0.2f*rt2*(gpac.x*rt[pos].z + gpac.z*rt[pos].x + gpae.x*rt[pos].x);
	result[pos].cc.w = rt[pos].x*rt[pos].x*rt[pos].w - 0.2f*rt2*(gpac.x*rt[pos].w + gpac.w*rt[pos].x + gpaf.x*rt[pos].x);
	
	result[pos].cd.x = rt[pos].x*rt[pos].y*rt[pos].x - 0.2f*rt2*(gpac.y*rt[pos].x + gpad.x*rt[pos].x + gpac.x*rt[pos].y);
	result[pos].cd.y = rt[pos].x*rt[pos].y*rt[pos].y - 0.2f*rt2*(gpac.y*rt[pos].y + gpad.y*rt[pos].x + gpad.x*rt[pos].y);
	result[pos].cd.z = rt[pos].x*rt[pos].y*rt[pos].z - 0.2f*rt2*(gpac.y*rt[pos].z + gpad.z*rt[pos].x + gpae.x*rt[pos].y);
	result[pos].cd.w = rt[pos].x*rt[pos].y*rt[pos].w - 0.2f*rt2*(gpac.y*rt[pos].w + gpad.w*rt[pos].x + gpaf.x*rt[pos].y);
	
	result[pos].ce.x = rt[pos].x*rt[pos].z*rt[pos].x - 0.2f*rt2*(gpac.z*rt[pos].x + gpae.x*rt[pos].x + gpac.x*rt[pos].z);
	result[pos].ce.y = rt[pos].x*rt[pos].z*rt[pos].y - 0.2f*rt2*(gpac.z*rt[pos].y + gpae.y*rt[pos].x + gpad.x*rt[pos].z);
	result[pos].ce.z = rt[pos].x*rt[pos].z*rt[pos].z - 0.2f*rt2*(gpac.z*rt[pos].z + gpae.z*rt[pos].x + gpae.x*rt[pos].z);
	result[pos].ce.w = rt[pos].x*rt[pos].z*rt[pos].w - 0.2f*rt2*(gpac.z*rt[pos].w + gpae.w*rt[pos].x + gpaf.x*rt[pos].z);
	
	result[pos].cf.x = rt[pos].x*rt[pos].w*rt[pos].x - 0.2f*rt2*(gpac.w*rt[pos].x + gpaf.x*rt[pos].x + gpac.x*rt[pos].w);
	result[pos].cf.y = rt[pos].x*rt[pos].w*rt[pos].y - 0.2f*rt2*(gpac.w*rt[pos].y + gpaf.y*rt[pos].x + gpad.x*rt[pos].w);
	result[pos].cf.z = rt[pos].x*rt[pos].w*rt[pos].z - 0.2f*rt2*(gpac.w*rt[pos].z + gpaf.z*rt[pos].x + gpae.x*rt[pos].w);
	result[pos].cf.w = rt[pos].x*rt[pos].w*rt[pos].w - 0.2f*rt2*(gpac.w*rt[pos].w + gpaf.w*rt[pos].x + gpaf.x*rt[pos].w);
	
	/**/
	result[pos].dc.x = rt[pos].y*rt[pos].x*rt[pos].x - 0.2f*rt2*(gpad.x*rt[pos].x + gpac.x*rt[pos].y + gpac.y*rt[pos].x);
	result[pos].dc.y = rt[pos].y*rt[pos].x*rt[pos].y - 0.2f*rt2*(gpad.x*rt[pos].y + gpac.y*rt[pos].y + gpad.y*rt[pos].x);
	result[pos].dc.z = rt[pos].y*rt[pos].x*rt[pos].z - 0.2f*rt2*(gpad.x*rt[pos].z + gpac.z*rt[pos].y + gpae.y*rt[pos].x);
	result[pos].dc.w = rt[pos].y*rt[pos].x*rt[pos].w - 0.2f*rt2*(gpad.x*rt[pos].w + gpac.w*rt[pos].y + gpaf.y*rt[pos].x);
	
	result[pos].dd.x = rt[pos].y*rt[pos].y*rt[pos].x - 0.2f*rt2*(gpad.y*rt[pos].x + gpad.x*rt[pos].y + gpac.y*rt[pos].y);
	result[pos].dd.y = rt[pos].y*rt[pos].y*rt[pos].y - 0.2f*rt2*(gpad.y*rt[pos].y + gpad.y*rt[pos].y + gpad.y*rt[pos].y);
	result[pos].dd.z = rt[pos].y*rt[pos].y*rt[pos].z - 0.2f*rt2*(gpad.y*rt[pos].z + gpad.z*rt[pos].y + gpae.y*rt[pos].y);
	result[pos].dd.w = rt[pos].y*rt[pos].y*rt[pos].w - 0.2f*rt2*(gpad.y*rt[pos].w + gpad.w*rt[pos].y + gpaf.y*rt[pos].y);
	
	result[pos].de.x = rt[pos].y*rt[pos].z*rt[pos].x - 0.2f*rt2*(gpad.z*rt[pos].x + gpae.x*rt[pos].y + gpac.y*rt[pos].z);
	result[pos].de.y = rt[pos].y*rt[pos].z*rt[pos].y - 0.2f*rt2*(gpad.z*rt[pos].y + gpae.y*rt[pos].y + gpad.y*rt[pos].z);
	result[pos].de.z = rt[pos].y*rt[pos].z*rt[pos].z - 0.2f*rt2*(gpad.z*rt[pos].z + gpae.z*rt[pos].y + gpae.y*rt[pos].z);
	result[pos].de.w = rt[pos].y*rt[pos].z*rt[pos].w - 0.2f*rt2*(gpad.z*rt[pos].w + gpae.w*rt[pos].y + gpaf.y*rt[pos].z);
	
	result[pos].df.x = rt[pos].y*rt[pos].w*rt[pos].x - 0.2f*rt2*(gpad.w*rt[pos].x + gpaf.x*rt[pos].y + gpac.y*rt[pos].w);
	result[pos].df.y = rt[pos].y*rt[pos].w*rt[pos].y - 0.2f*rt2*(gpad.w*rt[pos].y + gpaf.y*rt[pos].y + gpad.y*rt[pos].w);
	result[pos].df.z = rt[pos].y*rt[pos].w*rt[pos].z - 0.2f*rt2*(gpad.w*rt[pos].z + gpaf.z*rt[pos].y + gpae.y*rt[pos].w);
	result[pos].df.w = rt[pos].y*rt[pos].w*rt[pos].w - 0.2f*rt2*(gpad.w*rt[pos].w + gpaf.w*rt[pos].y + gpaf.y*rt[pos].w);
	
	/**/
	result[pos].ec.x = rt[pos].z*rt[pos].x*rt[pos].x - 0.2f*rt2*(gpae.x*rt[pos].x + gpac.x*rt[pos].z + gpac.z*rt[pos].x);
	result[pos].ec.y = rt[pos].z*rt[pos].x*rt[pos].y - 0.2f*rt2*(gpae.x*rt[pos].y + gpac.y*rt[pos].z + gpad.z*rt[pos].x);
	result[pos].ec.z = rt[pos].z*rt[pos].x*rt[pos].z - 0.2f*rt2*(gpae.x*rt[pos].z + gpac.z*rt[pos].z + gpae.z*rt[pos].x);
	result[pos].ec.w = rt[pos].z*rt[pos].x*rt[pos].w - 0.2f*rt2*(gpae.x*rt[pos].w + gpac.w*rt[pos].z + gpaf.z*rt[pos].x);
	
	result[pos].ed.x = rt[pos].z*rt[pos].y*rt[pos].x - 0.2f*rt2*(gpae.y*rt[pos].x + gpad.x*rt[pos].z + gpac.z*rt[pos].y);
	result[pos].ed.y = rt[pos].z*rt[pos].y*rt[pos].y - 0.2f*rt2*(gpae.y*rt[pos].y + gpad.y*rt[pos].z + gpad.z*rt[pos].y);
	result[pos].ed.z = rt[pos].z*rt[pos].y*rt[pos].z - 0.2f*rt2*(gpae.y*rt[pos].z + gpad.z*rt[pos].z + gpae.z*rt[pos].y);
	result[pos].ed.w = rt[pos].z*rt[pos].y*rt[pos].w - 0.2f*rt2*(gpae.y*rt[pos].w + gpad.w*rt[pos].z + gpaf.z*rt[pos].y);
	
	result[pos].ee.x = rt[pos].z*rt[pos].z*rt[pos].x - 0.2f*rt2*(gpae.z*rt[pos].x + gpae.x*rt[pos].z + gpac.z*rt[pos].z);
	result[pos].ee.y = rt[pos].z*rt[pos].z*rt[pos].y - 0.2f*rt2*(gpae.z*rt[pos].y + gpae.y*rt[pos].z + gpad.z*rt[pos].z);
	result[pos].ee.z = rt[pos].z*rt[pos].z*rt[pos].z - 0.2f*rt2*(gpae.z*rt[pos].z + gpae.z*rt[pos].z + gpae.z*rt[pos].z);
	result[pos].ee.w = rt[pos].z*rt[pos].z*rt[pos].w - 0.2f*rt2*(gpae.z*rt[pos].w + gpae.w*rt[pos].z + gpaf.z*rt[pos].z);
	
	result[pos].ef.x = rt[pos].z*rt[pos].w*rt[pos].x - 0.2f*rt2*(gpae.w*rt[pos].x + gpaf.x*rt[pos].z + gpac.z*rt[pos].w);
	result[pos].ef.y = rt[pos].z*rt[pos].w*rt[pos].y - 0.2f*rt2*(gpae.w*rt[pos].y + gpaf.y*rt[pos].z + gpad.z*rt[pos].w);
	result[pos].ef.z = rt[pos].z*rt[pos].w*rt[pos].z - 0.2f*rt2*(gpae.w*rt[pos].z + gpaf.z*rt[pos].z + gpae.z*rt[pos].w);
	result[pos].ef.w = rt[pos].z*rt[pos].w*rt[pos].w - 0.2f*rt2*(gpae.w*rt[pos].w + gpaf.w*rt[pos].z + gpaf.z*rt[pos].w);
	
	/**/
	result[pos].fc.x = rt[pos].w*rt[pos].x*rt[pos].x - 0.2f*rt2*(gpaf.x*rt[pos].x + gpac.x*rt[pos].w + gpac.w*rt[pos].x);
	result[pos].fc.y = rt[pos].w*rt[pos].x*rt[pos].y - 0.2f*rt2*(gpaf.x*rt[pos].y + gpac.y*rt[pos].w + gpad.w*rt[pos].x);
	result[pos].fc.z = rt[pos].w*rt[pos].x*rt[pos].z - 0.2f*rt2*(gpaf.x*rt[pos].z + gpac.z*rt[pos].w + gpae.w*rt[pos].x);
	result[pos].fc.w = rt[pos].w*rt[pos].x*rt[pos].w - 0.2f*rt2*(gpaf.x*rt[pos].w + gpac.w*rt[pos].w + gpaf.w*rt[pos].x);
	
	result[pos].fd.x = rt[pos].w*rt[pos].y*rt[pos].x - 0.2f*rt2*(gpaf.y*rt[pos].x + gpad.x*rt[pos].w + gpac.w*rt[pos].y);
	result[pos].fd.y = rt[pos].w*rt[pos].y*rt[pos].y - 0.2f*rt2*(gpaf.y*rt[pos].y + gpad.y*rt[pos].w + gpad.w*rt[pos].y);
	result[pos].fd.z = rt[pos].w*rt[pos].y*rt[pos].z - 0.2f*rt2*(gpaf.y*rt[pos].z + gpad.z*rt[pos].w + gpae.w*rt[pos].y);
	result[pos].fd.w = rt[pos].w*rt[pos].y*rt[pos].w - 0.2f*rt2*(gpaf.y*rt[pos].w + gpad.w*rt[pos].w + gpaf.w*rt[pos].y);

	result[pos].fe.x = rt[pos].w*rt[pos].z*rt[pos].x - 0.2f*rt2*(gpaf.z*rt[pos].x + gpae.x*rt[pos].w + gpac.w*rt[pos].z);
	result[pos].fe.y = rt[pos].w*rt[pos].z*rt[pos].y - 0.2f*rt2*(gpaf.z*rt[pos].y + gpae.y*rt[pos].w + gpad.w*rt[pos].z);
	result[pos].fe.z = rt[pos].w*rt[pos].z*rt[pos].z - 0.2f*rt2*(gpaf.z*rt[pos].z + gpae.z*rt[pos].w + gpae.w*rt[pos].z);
	result[pos].fe.w = rt[pos].w*rt[pos].z*rt[pos].w - 0.2f*rt2*(gpaf.z*rt[pos].w + gpae.w*rt[pos].w + gpaf.w*rt[pos].z);
	
	result[pos].ff.x = rt[pos].w*rt[pos].w*rt[pos].x - 0.2f*rt2*(gpaf.w*rt[pos].x + gpaf.x*rt[pos].w + gpac.w*rt[pos].w);
	result[pos].ff.y = rt[pos].w*rt[pos].w*rt[pos].y - 0.2f*rt2*(gpaf.w*rt[pos].y + gpaf.y*rt[pos].w + gpad.w*rt[pos].w);
	result[pos].ff.z = rt[pos].w*rt[pos].w*rt[pos].z - 0.2f*rt2*(gpaf.w*rt[pos].z + gpaf.z*rt[pos].w + gpae.w*rt[pos].w);
	result[pos].ff.w = rt[pos].w*rt[pos].w*rt[pos].w - 0.2f*rt2*(gpaf.w*rt[pos].w + gpaf.w*rt[pos].w + gpaf.w*rt[pos].w);
}


__kernel void kernelspinproject3_2_2(__global float44 * gtin, __global float44 * Tin, uint i, uint j,__global out float44 * result){

	uint pos = get_global_id(0);
	float44 gt = gtin[pos];
	float44 Tt = Tin[pos];
	uint k,l,m,n;

	uint mu, mup, nu, nup, lu, lup;

	float p[256];
	float g[16];
	float T[16];

	float sum[16];

	g[0]  = gt.c.x;
	g[1]  = gt.c.y;
	g[2]  = gt.c.z;
	g[3]  = gt.c.w;

	g[4]  = gt.d.x;
	g[5]  = gt.d.y;
	g[6]  = gt.d.z;
	g[7]  = gt.d.w;

	g[8]  = gt.e.x;
	g[9]  = gt.e.y;
	g[10] = gt.e.z;
	g[11] = gt.e.w;

	g[12] = gt.f.x;
	g[13] = gt.f.y;
	g[14] = gt.f.z;
	g[15] = gt.f.w;

	T[0]  = Tt.c.x;
	T[1]  = Tt.c.y;
	T[2]  = Tt.c.z;
	T[3]  = Tt.c.w;

	T[4]  = Tt.d.x;
	T[5]  = Tt.d.y;
	T[6]  = Tt.d.z;
	T[7]  = Tt.d.w;

	T[8]  = Tt.e.x;
	T[9]  = Tt.e.y;
	T[10] = Tt.e.z;
	T[11] = Tt.e.w;

	T[12] = Tt.f.x;
	T[13] = Tt.f.y;
	T[14] = Tt.f.z;
	T[15] = Tt.f.w;

	for(k=0; k < 16; k++){
		sum[k] = 0;
	}

	for(k=0; k < 4; k++){
		for(l=0; l < 4; l++){
			for(m=0; m < 4; m++){
				for(n=0; n < 4; n++){
					/* Here we do some stuff to get closer to the notation in Zou and Bugg, eq. 21 */
					mu = i;
					nu = k;
					lu = l;
					mup = j;
					nup = m;
					lup = n;

					p[nu*64+lu*16+nup*4+lup] = -1.0f/6.0f * ( g[4*mu+mup] * g[4*nu+nup] * g[4*lu+lup] +
													  g[4*mu+mup] * g[4*nu+lup] * g[4*lu+nup] +
													  g[4*mu+nup] * g[4*nu+mup] * g[4*lu+lup] +
													  g[4*mu+nup] * g[4*nu+lup] * g[4*lu+mup] +
													  g[4*mu+lup] * g[4*nu+nup] * g[4*lu+mup] +
													  g[4*mu+lup] * g[4*nu+mup] * g[4*lu+nup] ) +
										 1.0f/15.0f * ( g[4*mu+nu] * g[4*mup+nup] * g[4*lu+lup] +
												  	  g[4*mu+nu] * g[4*nup+lup] * g[4*lu+mup] +
												  	  g[4*mu+nu] * g[4*mup+lup] * g[4*lu+nup] +
												  	  g[4*mu+lu] * g[4*mup+lup] * g[4*nu+nup] +
												  	  g[4*mu+lu] * g[4*mup+nup] * g[4*nu+lup] +
												  	  g[4*mu+lu] * g[4*nup+lup] * g[4*nu+mup] +
												  	  g[4*nu+lu] * g[4*nup+lup] * g[4*mu+mup] +
												  	  g[4*nu+lu] * g[4*mup+nup] * g[4*mu+lup] +
												  	  g[4*nu+lu] * g[4*mup+lup] * g[4*mu+nup]
										             );
				}
			}
		}
	}

	for(k=0; k < 4; k++){
		for(l=0; l < 4; l++){
			for(m=0; m < 4; m++){
				for(n=0; n < 4; n++){
					/* Here we do some stuff to get closer to the notation in Zou and Bugg, eq. 21 */
					nu = k;
					lu = l;
					nup = m;
					lup = n;

					sum[nup*4+lup] += p[nu*64+lu*16+nup*4+lup]*T[4*nu+lu];
				}
			}
		}
	}

	result[pos].c.x = sum[0];
	result[pos].c.y = sum[1];
	result[pos].c.z = sum[2];
	result[pos].c.w = sum[3];

	result[pos].d.x = sum[4];
	result[pos].d.y = sum[5];
	result[pos].d.z = sum[6];
	result[pos].d.w = sum[7];

	result[pos].e.x = sum[8];
	result[pos].e.y = sum[9];
	result[pos].e.z = sum[10];
	result[pos].e.w = sum[11];

	result[pos].f.x = sum[12];
	result[pos].f.y = sum[13];
	result[pos].f.z = sum[14];
	result[pos].f.w = sum[15];

}
