/*  \file Ananlysis.br

//#include "brookanalysis.h"
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
 



__kernel void pwamult4(__global float4 * weight, __global float4 * lookupx, __global float4 * lookupy, __global float2 * parameters, uint n, float bgpar, float tcs, __global out float4 * dcs, __global out float4 * logdcs){
	/* Here we are: the core algorithm of the whole partial wave analysis thingy.
	 Weights contains event weights, Lookupx and Lookupy is the
	lookup table of the AiAj*'s that we have precomputed. Stored are 2 floats representing complex values for 
	the upper right half of the matrix, i.e. element 0 has position row 0, column 0 in the n x n matrix, 
	element 1 is 0,1, element n is at 1,1 etc. For diagonal elements, AiAi* is real, thus we add 
	AiAi* PiPi* (also real). For the off-diagonal elements, we look at AiAj*PiPj*+AjAi*PjPi* which is 
	also real; several terms will cancel. parameters contains the fit parameters, n the number of waves.
	bgpar is a phase space parameter. Output are the differential cross section (used for gradients) and 
	the contribution to the total log likelihood*/

	uint index = get_global_id(0);
	uint i;
	uint j;
	uint y;
	uint lookupsize = n*(n+1)/2;
	float4 tempsum;
	float parpart;
	float4 parpart4;
	uint ind = 0;
	float4 mydcs;
	//index.x = input;
	tempsum.x =0.0f;
	tempsum.y =0.0f;
	tempsum.z =0.0f;
	tempsum.w =0.0f;
	for(i=0; i < n; i=i+1){
		y = ind;
		parpart = (parameters[i].x*parameters[i].x+parameters[i].y*parameters[i].y);
		tempsum = tempsum + lookupx[index*lookupsize + y] * parpart;
		ind = ind + 1;
		for(j=i+1; j < n; j=j+1){
			y = ind;
			parpart4 = (2.0f * parameters[i].x * parameters[j].x) * lookupx[index*lookupsize + y];
			tempsum = tempsum + parpart4;
			parpart4 = (2.0f * parameters[i].y * parameters[j].y) * lookupx[index*lookupsize + y];
			tempsum = tempsum + parpart4;
			parpart4 = (2.0f * parameters[i].x * parameters[j].y) * lookupy[index*lookupsize + y];
			tempsum = tempsum + parpart4;
			parpart4 = (2.0f * parameters[i].y * parameters[j].x) * lookupy[index*lookupsize + y];
			tempsum = tempsum - parpart4;
			ind = ind + 1;
		}
	}
	mydcs = tempsum + bgpar;
	if(mydcs.x <= 0.0f)
	 mydcs.x = 0.000001f;
	if(mydcs.y <= 0.0f)
	 mydcs.y = 0.000001f;
	if(mydcs.z <= 0.0f)
	 mydcs.z = 0.000001f;
	if(mydcs.w <= 0.0f)
	 mydcs.w = 0.000001f;	
	/*dcs[index] = weight[index];*/
	dcs[index] = mydcs;
	logdcs[index] = -log(mydcs/tcs)* weight[index];
 }



__kernel void collectpropagators4(__global float2 * propagator, uint nwave, uint waveindex, __global out float4 * prop){
	/* Write a propagator to a lookup table at a specified waveindex */
	uint index = get_global_id(0);
	prop[2*waveindex + index*nwave*2].x = propagator[index*4].x;
	prop[2*waveindex + index*nwave*2].y = propagator[index*4+1].x;
	prop[2*waveindex + index*nwave*2].z = propagator[index*4+2].x;
	prop[2*waveindex + index*nwave*2].w = propagator[index*4+3].x;

	prop[2*waveindex+1 + index*nwave*2].x = propagator[index*4].y;
	prop[2*waveindex+1 + index*nwave*2].y = propagator[index*4+1].y;
	prop[2*waveindex+1 + index*nwave*2].z = propagator[index*4+2].y;
	prop[2*waveindex+1 + index*nwave*2].w = propagator[index*4+3].y;

} 



__kernel void freepwamult4(__global float4 * weight, __global float4 * lookup, __global float4 * propagator, __global float2 * parameters, uint n, float bgpar, float tcs, __global out float4 * dcs, __global out float4 * logdcs){
	/* Here we are: the core algorithm of the whole partial wave analysis thingy. Weights contains event weights, Lookup is the
	lookup table of the real parts of AiAj*'s that we have precomputed. Stored is a float representing values for 
	the upper right half of the matrix, i.e. element 0 has position row 0, column 0 in the n x n matrix, 
	element 1 is 0,1, element n is at 1,1 etc. Parameters contains the fit parameters, n the number of waves.
	bgpar is a phase space parameter. Output is the differential cross section */

	uint index = get_global_id(0);
	uint i;
	uint j;
	uint y;
	uint dex;
	float4 tempsum;
	float parpart;
	float4 parpart4;
	float4 proppart;
	float4 propix;
	float4 propiy;
	float4 propjx;
	float4 propjy;
	float4 propx;
	float4 propy;
	uint ind = 0;
	uint lookupsize = n*(n+1)/2;
	float4 mydcs;
	tempsum.x =0.0f;
	tempsum.y =0.0f;
	tempsum.z =0.0f;
	tempsum.w =0.0f;
	for(i=0; i < n; i=i+1){
		y = ind;
		parpart = (parameters[i].x*parameters[i].x+parameters[i].y*parameters[i].y);
		propix = propagator[2*i + index*n*2];
		dex = 2*i+1;
		propiy = propagator[dex + index*n*2];
		proppart = propix*propix + propiy*propiy;
		tempsum = tempsum + lookup[index*lookupsize+y] *proppart * parpart;
		ind = ind + 1;
		for(j=i+1; j < n; j=j+1){
			propjx = propagator[2*j + index*n*2];
			dex = 2*j+1;
			propjy = propagator[dex + index*n*2];
			propx = propix*propjx + propiy*propjy;
			propy = - propix*propjy + propiy*propjx;
			y = ind;
			parpart4 = (2.0f * parameters[i].x * parameters[j].x) ;
			tempsum = tempsum + parpart4* lookup[index*lookupsize+y] * propx;
			parpart4 = (2.0f * parameters[i].y * parameters[j].y); 
			tempsum = tempsum + parpart4* lookup[index*lookupsize+y] * propx;
			parpart4 = (2.0f * parameters[i].x * parameters[j].y) ;
			tempsum = tempsum + parpart4* lookup[index*lookupsize+y] * propy;
			parpart4 = (2.0f *parameters[i].y * parameters[j].x) ;
			tempsum = tempsum - parpart4* lookup[index*lookupsize+y] * propy;
			ind = ind + 1;
		}
	}
	mydcs = tempsum + bgpar;
	if(mydcs.x <= 0.0f)
	 mydcs.x = 0.000001f;
	if(mydcs.y <= 0.0f)
	 mydcs.y = 0.000001f;
	if(mydcs.z <= 0.0f)
	 mydcs.z = 0.000001f;
	if(mydcs.w <= 0.0f)
	 mydcs.w = 0.000001f;	
	dcs[index] = mydcs;
	logdcs[index] = -log(mydcs/tcs)* weight[index];
 }
 


 __kernel void freepwamult4tcs(__global float4 * lookup, __global float4 * propagator, __global float2 * parameters, uint n, __global out float4 * dcs){
	/* PWA matrix multiplication for the MC integral total cross section.  Weights contains event weights, Lookup is the
	lookup table of the real parts of AiAj*'s that we have precomputed. Stored is a float representing values for 
	the upper right half of the matrix, i.e. element 0 has position row 0, column 0 in the n x n matrix, 
	element 1 is 0,1, element n is at 1,1 etc. Parameters contains the fit parameters, n the number of waves.
	bgpar is a phase space parameter. Output is the differential cross section */

	 uint index = get_global_id(0);
	uint i;
	uint j;
	uint dex;
	uint y;
	uint lookupsize = n*(n+1)/2;
	float4 tempsum;
	float parpart;
	float4 parpart4;
	float4 proppart;
	float4 propix;
	float4 propiy;
	float4 propjx;
	float4 propjy;
	float4 propx;
	float4 propy;
	uint ind = 0;
	tempsum.x =0.0f;
	tempsum.y =0.0f;
	tempsum.z =0.0f;
	tempsum.w =0.0f;
	for(i=0; i < n; i=i+1){
		y = ind;
		parpart = (parameters[i].x*parameters[i].x+parameters[i].y*parameters[i].y);
		propix = propagator[2*i +index*n*2];
		dex = 2*i+1;
		propiy = propagator[dex + index*n*2];
		proppart = propix*propix + propiy*propiy;
		tempsum = tempsum + lookup[index*lookupsize+y] *proppart * parpart;
		ind = ind + 1;
		for(j=i+1; j < n; j=j+1){
			propjx = propagator[2*j + index*n*2];
			dex = 2*j+1;
			propjy = propagator[dex + index*n*2];
			propx = propix*propjx + propiy*propjy;
			propy = - propix*propjy + propiy*propjx;
			y = ind;
			parpart4 = (2.0f * parameters[i].x * parameters[j].x) ;
			tempsum = tempsum + parpart4* lookup[index*lookupsize+y] * propx;
			parpart4 = (2.0f * parameters[i].y * parameters[j].y); 
			tempsum = tempsum + parpart4* lookup[index*lookupsize+y] * propx;
			parpart4 = (2.0f * parameters[i].x * parameters[j].y) ;
			tempsum = tempsum + parpart4* lookup[index*lookupsize+y] * propy;
			parpart4 = (2.0f *parameters[i].y * parameters[j].x) ;
			tempsum = tempsum - parpart4* lookup[index*lookupsize+y] * propy;
			ind = ind + 1.0f;
		}
	}

	dcs[index] = tempsum;
 }
 


 __kernel void freepwamult4tcsweighted(__global float4 * weights, __global float4 * lookup, __global float4 * propagator, __global float2 * parameters, uint n, __global out float4 * dcs){
	/* PWA matrix multiplication for the MC integral total cross section.  Weights contains event weights, Lookup is the
	lookup table of the real parts of AiAj*'s that we have precomputed. Stored is a float representing values for 
	the upper right half of the matrix, i.e. element 0 has position row 0, column 0 in the n x n matrix, 
	element 1 is 0,1, element n is at 1,1 etc. Parameters contains the fit parameters, n the number of waves.
	bgpar is a phase space parameter. Output is the differential cross section */

	uint index = get_global_id(0);
	uint i;
	uint j;
	uint y;
	uint dex;
	uint lookupsize = n*(n+1)/2;
	float4 tempsum;
	float parpart;
	float4 parpart4;
	float4 proppart;
	float4 propix;
	float4 propiy;
	float4 propjx;
	float4 propjy;
	float4 propx;
	float4 propy;
	uint ind = 0;
	tempsum.x =0.0f;
	tempsum.y =0.0f;
	tempsum.z =0.0f;
	tempsum.w =0.0f;
	for(i=0; i < n; i=i+1){
		y = ind;
		parpart = (parameters[i].x*parameters[i].x+parameters[i].y*parameters[i].y);
		propix = propagator[2*i + index*n*2];
		dex = 2*i+1;
		propiy = propagator[dex + index*n*2];
		proppart = propix*propix + propiy*propiy;
		tempsum = tempsum + lookup[index*lookupsize+y] *proppart * parpart;
		ind = ind + 1;
		for(j=i+1; j < n; j=j+1){
			propjx = propagator[2*j + index*n*2];
			dex = 2*j+1;
			propjy = propagator[dex + index*n*2];
			propx = propix*propjx + propiy*propjy;
			propy = - propix*propjy + propiy*propjx;
			y = ind;
			parpart4 = (2.0f * parameters[i].x * parameters[j].x) ;
			tempsum = tempsum + parpart4* lookup[index*lookupsize+y] * propx;
			parpart4 = (2.0f * parameters[i].y * parameters[j].y); 
			tempsum = tempsum + parpart4* lookup[index*lookupsize+y] * propx;
			parpart4 = (2.0f * parameters[i].x * parameters[j].y) ;
			tempsum = tempsum + parpart4* lookup[index*lookupsize+y] * propy;
			parpart4 = (2.0f *parameters[i].y * parameters[j].x) ;
			tempsum = tempsum - parpart4* lookup[index*lookupsize+y] * propy;
			ind = ind + 1.0f;
		}
	}

	dcs[index] = tempsum*weights[index];
 }
 

__kernel void pwagradmult4all(__global int * input, __global float4 * weightin, __global float4 * dcsin, __global float4 * lookupx, __global float4 * lookupy, __global float2 * parameters, uint nwaves, uint ngrads,__global float * gradpar, float bgpar, float tcs, __global float * dtcsin, __global out float4 * grad, __global out float4 * innergrad){
	/*Calculate gradient with regards to gradpar of dcs*/
	uint n = nwaves;
	uint index = get_global_id(0);
	uint ev = index/ngrads;
	uint y = index%ngrads;
	uint2 parindex;
	uint2 parindex2;
	uint i;
	uint j;
	uint lookupsize = n*(n+1)/2;
	float4 tempsum;
	float4 temp;
	uint ind = 0;
	float2 pari;
	float2 parj;
	float pprod;
	float dphase;
	float4 numerator;
	float4 lupx;
	float4 lupy;
	float4 dcs = dcsin[ev];
	float4 weight = weightin[ev];
	float dtcs;
	if(input[y] < 0){
		dtcs = dtcsin[0];
		tempsum = (tcs-dtcs*dcs);
		innergrad[index] = tempsum/(tcs*tcs);
		grad[index] = -weight/dcs * tempsum/tcs;
	} else {	
		tempsum.x =0.0f;
		tempsum.y =0.0f;
		tempsum.z =0.0f;
		tempsum.w =0.0f;
		parindex.y = input[y];
		parindex2.y = input[y];
		for(i=0; i < n; i=i+1){
			parindex.x = 2*i;
			if(gradpar[parindex.y*2*n + parindex.x]){
				lupx = lookupx[ind + ev*lookupsize];
				lupy = lookupy[ind + ev*lookupsize];
				temp = lupx*(parameters[i].x);
				tempsum = tempsum + 2.0f * temp;
			}
			ind = ind + 1;
			for(j= i+1; j < n; j=j+1){
				parindex.x = 2*i;
				parindex2.x = 2*j;
				if(gradpar[parindex.y*2*n + parindex.x] && gradpar[parindex2.y*2*n + parindex2.x]){
					pari = parameters[i];
					parj = parameters[j];
					dphase = pari.y - parj.y;
					lupx = lookupx[ind + ev*lookupsize];
					lupy = lookupy[ind + ev*lookupsize];
					temp = (cos(dphase)*lupx - sin(dphase)*lupy);
					tempsum = tempsum + 4.0f*parameters[j].x*temp;
				} else {

					if(gradpar[parindex.y*2*n + parindex.x] ){
						pari = parameters[i];
						parj = parameters[j];
						dphase = pari.y - parj.y;
						lupx = lookupx[ind + ev*lookupsize];
						lupy = lookupy[ind + ev*lookupsize];
						temp = (cos(dphase)*lupx - sin(dphase)*lupy);
						tempsum = tempsum + 2.0f*parameters[j].x*temp;
					} else {
						if(gradpar[parindex2.y*2*n + parindex2.x]){
							pari = parameters[i];
							parj = parameters[j];
							dphase = pari.y - parj.y;

							lupx = lookupx[ind + ev*lookupsize];
							lupy = lookupy[ind + ev*lookupsize];
							temp = (cos(dphase)*lupx - sin(dphase)*lupy);
							tempsum = tempsum + 2.0f*parameters[i].x*temp;
						}
					}
				}
				parindex.x = 2*i +1;
				parindex2.x = 2*j +1;
				if(!(gradpar[parindex.y*2*n + parindex.x] && gradpar[parindex2.y*2*n + parindex2.x])){
					if(gradpar[parindex.y*2*n + parindex.x]){
						pari = parameters[i];
						parj = parameters[j];
						pprod = pari.x*parj.x;
						dphase = pari.y - parj.y;
						lupx = lookupx[ind + ev*lookupsize];
						lupy = lookupy[ind + ev*lookupsize];
						temp = (-sin(dphase)*lupx - cos(dphase)*lupy);
						tempsum = tempsum + 2.0f*pprod*temp;
					}
					if(gradpar[parindex2.y*2*n + parindex2.x]){
						pari = parameters[i];
						parj = parameters[j];
						pprod = pari.x*parj.x;
						dphase = pari.y - parj.y;
						lupx = lookupx[ind + ev*lookupsize];
						lupy = lookupy[ind + ev*lookupsize];
						temp = (-sin(dphase)*lupx - cos(dphase)*lupy);
						tempsum = tempsum - 2.0f*pprod*temp;
					}
				}
				ind = ind + 1;
				
			}
		}
	
		dtcs = dtcsin[input[y]];
		numerator = (tempsum*tcs - dtcs*(dcs));
		innergrad[index] =numerator/(tcs*tcs);
		//innergrad[index].x = tempsum.x;
		//innergrad[index].y = dcs.x;
		//innergrad[index].z = dtcs;
		//innergrad[index].w = weight.w;
		grad[index] = -numerator/(tcs*(dcs))*weight;
		//grad[index].x = lupx.x;
		//grad[index].y = lupy.x;
		//grad[index].z = temp.x;
		//grad[index].w = tempsum.x;
	}
 }


__kernel void kernelhessian(__global float * gradient1, __global float * gradient2, __global float * dcs, __global float * weight, float bgpar, float tcs, __global out float * hessian){
	uint i = get_global_id(0);
	float val = (dcs[i])/tcs;
	hessian[i] = gradient1[i]*gradient2[i]/(val*val)*weight[i];

}


__kernel void kernelhessian4all(__global float4 * gradients, __global float4 * dcs, __global float4 * weight, uint ngrad, float bgpar, float tcs, __global out float4 * hessian){
	uint i = get_global_id(0);
	uint msize = ngrad*(ngrad+1)/2;
	uint ev = i/msize;
	uint ind = i%msize;
	uint row = 0;
	uint col = 0;
	uint rowsize = ngrad;

	while(ind/rowsize){
		ind = ind -rowsize;
		rowsize--;
		row++;
	}
	col = row +ind%rowsize;

	float4 val = (dcs[ev])/tcs;
	float4 div = (val*val);
	float4 grad1 = gradients[col + ev*ngrad];
	float4 grad2 = gradients[row + ev*ngrad];
	hessian[i] = grad1*grad2/div*weight[ev];
	//hessian[i].x = grad1.x;
	//hessian[i].y = grad2.x;
	//hessian[i].z = val.x;
	//hessian[i].w = div.x;
}

/*
__kernel void pwamultdcsonly(__global float input<>, __global float2 lookup[][], __global float2 parameters[], float n, float bgpar, __global float dcs<>){
	
	float2 index;
	float i;
	float j;
	float tempsum =0.0f;
	float parpart;
	float ind = 0.0f;
	float2 pprod;
	float mydcs;
	index.x = input;
	for(i=0.0f; i < n; i=i+1.0f){
		index.y = ind;
		parpart = (parameters[i].x*parameters[i].x+parameters[i].y*parameters[i].y);
		tempsum = tempsum + lookup[index.y][index.x].x*parpart;
		ind = ind + 1.0f;
		for(j=i+1.0f; j < n; j=j+1.0f){
			index.y = ind;
			parpart = 2.0f * parameters[i].x * parameters[j].x * lookup[index.y][index.x].x;
			tempsum = tempsum + parpart;
			parpart = 2.0f * parameters[i].y * parameters[j].y * lookup[index.y][index.x].x; 
			tempsum = tempsum + parpart;
			parpart = 2.0f * parameters[i].x * parameters[j].y * lookup[index.y][index.x].y;
			tempsum = tempsum + parpart;
			parpart = 2.0f *parameters[i].y * parameters[j].x * lookup[index.y][index.x].y;
			tempsum = tempsum - parpart;

			ind = ind + 1.0f;
		}
	}
	mydcs = tempsum + bgpar;
	dcs = mydcs;
	
 }
*/

__kernel void pwamultdcsonly4(__global float4 * lookupx, __global float4 * lookupy, __global float2 * parameters, uint n, float bgpar, __global out float4 * dcs){
	
	uint index = get_global_id(0);
	uint i;
	uint j;
	uint y;
	uint lookupsize = n*(n+1)/2;
	float4 tempsum;
	float parpart;
	float4 presum;
	uint ind = 0;
	float4 mydcs;
	tempsum.x =0.0f;
	tempsum.y =0.0f;
	tempsum.z =0.0f;
	tempsum.w =0.0f;
	for(i=0; i < n; i=i+1){
		y = ind;
		parpart = (parameters[i].x*parameters[i].x+parameters[i].y*parameters[i].y);
		tempsum = tempsum + lookupx[y+index*lookupsize]*parpart;
		ind = ind + 1;
		for(j=i+1; j < n; j=j+1){
			y = ind;
			presum = 2.0f * parameters[i].x * parameters[j].x * lookupx[y+index*lookupsize];
			tempsum = tempsum + presum;
			presum = 2.0f * parameters[i].y * parameters[j].y * lookupx[y+index*lookupsize];
			tempsum = tempsum + presum;
			presum = 2.0f * parameters[i].x * parameters[j].y * lookupy[y+index*lookupsize];
			tempsum = tempsum + presum;
			presum = 2.0f *parameters[i].y * parameters[j].x * lookupy[y+index*lookupsize];
			tempsum = tempsum - presum;

			ind = ind + 1;
		}
	}
	mydcs = tempsum + bgpar;
	dcs[index] = mydcs;
 }

__kernel void pwamultdcsonly4weighted(__global float4 * lookupx, __global float4 * lookupy, __global float4 * weights, __global float2 * parameters, uint n, float bgpar, __global out float4 * dcs){

	uint index = get_global_id(0);
	uint i;
	uint j;
	uint y;
	uint lookupsize = n*(n+1)/2;
	float4 tempsum;
	float parpart;
	float4 presum;
	uint ind = 0;
	float4 mydcs;
	tempsum.x =0.0f;
	tempsum.y =0.0f;
	tempsum.z =0.0f;
	tempsum.w =0.0f;
	for(i=0; i < n; i=i+1){
		y = ind;
		parpart = (parameters[i].x*parameters[i].x+parameters[i].y*parameters[i].y);
		tempsum = tempsum + lookupx[y+index*lookupsize]*parpart;
		ind = ind + 1;
		for(j=i+1; j < n; j=j+1){
			y = ind;
			presum = 2.0f * parameters[i].x * parameters[j].x * lookupx[y+index*lookupsize];
			tempsum = tempsum + presum;
			presum = 2.0f * parameters[i].y * parameters[j].y * lookupx[y+index*lookupsize];
			tempsum = tempsum + presum;
			presum = 2.0f * parameters[i].x * parameters[j].y * lookupy[y+index*lookupsize];
			tempsum = tempsum + presum;
			presum = 2.0f *parameters[i].y * parameters[j].x * lookupy[y+index*lookupsize];
			tempsum = tempsum - presum;

			ind = ind + 1;
		}
	}
	mydcs = tempsum + bgpar;
	dcs[index] = mydcs*weights[index];
 }

__kernel void pwamultdcsonlyonewave4(__global float4 * lookupx, __global float2 * parameters, uint n, uint wavenumber, __global out float4 * dcs){
	
	uint index = get_global_id(0);
	uint i;
	uint j;
	uint y;
	uint lookupsize = n*(n+1)/2;
	float4 tempsum;
	float parpart;
	uint ind = 0;
	float4 mydcs;
	tempsum.x =0.0f;
	tempsum.y =0.0f;
	tempsum.z =0.0f;
	tempsum.w =0.0f;
	for(i=0; i < n; i=i+1){
		y = ind;
		if(wavenumber == i){
			parpart = (parameters[i].x*parameters[i].x+parameters[i].y*parameters[i].y);
			tempsum = tempsum + lookupx[y+index*lookupsize]*parpart;
		}
		ind = ind + 1.0f;
		for(j=i+1.0f; j < n; j=j+1.0f){
			ind = ind + 1.0f;
		}
	}
	mydcs = tempsum;
	dcs[index] = mydcs;
 }



__kernel void pwamultdcsonlytwowaves4(__global float4 * lookupx, __global float4 * lookupy, __global float2 * parameters, uint n, uint wave1, uint wave2, __global out float4 * dcs){
	
	uint index = get_global_id(0);
	uint i;
	uint j;
	uint y;
	uint lookupsize = n*(n+1)/2;
	float4 tempsum;
	float4 parpart;
	uint ind = 0;
	float4 mydcs;
	tempsum.x =0.0f;
	tempsum.y =0.0f;
	tempsum.z =0.0f;
	tempsum.w =0.0f;
	for(i=0; i < n; i=i+1){
		y = ind;
		ind = ind + 1;
		for(j=i+1; j < n; j=j+1){
			y = ind;
			if(wave1 == i && wave2 == j){
				parpart = 2.0f * parameters[i].x * parameters[j].x * lookupx[y+index*lookupsize];
				tempsum = tempsum + parpart;
				parpart = 2.0f * parameters[i].y * parameters[j].y * lookupx[y+index*lookupsize];
				tempsum = tempsum + parpart;
				parpart = 2.0f * parameters[i].x * parameters[j].y * lookupy[y+index*lookupsize];
				tempsum = tempsum + parpart;
				parpart = 2.0f *parameters[i].y * parameters[j].x * lookupy[y+index*lookupsize];
				tempsum = tempsum - parpart;
			}
			ind = ind + 1;
		}
	}
	mydcs = tempsum;
	dcs[index] = mydcs;
	
 }



__kernel void kernelmult_c_c_f(__global float2 * c1, __global float2 * c2, __global float * f, __global out float2 * result){
	uint i = get_global_id(0);
	result[i].x = f[i]*(c1[i].x*c2[i].x - c1[i].y*c2[i].y);
	result[i].y = f[i]*(c1[i].x*c2[i].y + c1[i].y*c2[i].x);
}

__kernel void kernelmult_c_cbar_f(__global float2 * c1, __global float2 * c2, __global float * f, __global  out float2 * result){
	uint i = get_global_id(0);
	result[i].x = f[i]*(c1[i].x*c2[i].x + c1[i].y*c2[i].y);
	result[i].y = f[i]*(-c1[i].x*c2[i].y + c1[i].y*c2[i].x);
}

__kernel void kernelmult_2c_cbar_f(__global float2 * c1, __global float2 * c2, __global float * f,  double2 pprodd, __global out float * result){
	uint i = get_global_id(0);
	float2 cprod = c1[i]*c2[i];
	float2 pprod;
	pprod.x = (float)(pprodd.x);
	pprod.y = (float)(pprodd.y);
	result[i] = f[i]*2.0f*(cprod.x*pprod.x + cprod.x*pprod.y + cprod.y*pprod.x +cprod.y*pprod.y);
}

__kernel void kernelmult_c2_f(__global float2 * c1, __global float * f, __global out float * result){
	uint i = get_global_id(0);
	result[i] = f[i]*(c1[i].x*c1[i].x + c1[i].y*c1[i].y);

}

__kernel void kernelsum16float2double(__global float4 * input, __global out double2 * result){
	uint i = get_global_id(0);
	double2 temp;
	uint i2;
	uint myindex;
	result[i].x =(double)0.0;
	result[i].y =(double)0.0;
	for(i2=0; i2 < 16; i2 = i2 +1){
		myindex = i*16 + i2;
		temp.x = (double)(input[myindex].x);
		temp.y = (double)(input[myindex].y);
		result[i].x = result[i].x + temp.x;
		result[i].y = result[i].y + temp.y;
		temp.x = (double)(input[myindex].z);
		temp.y = (double)(input[myindex].w);
		result[i].x = result[i].x + temp.x;
		result[i].y = result[i].y + temp.y;
	}
}

__kernel void kernelsum16float2double2d(__global float4 * input, uint n, __global out double2 * result){
	uint i = get_global_id(0);
	uint ev = i/n;
	uint ev2;
	uint y = i%n;
	double2 temp;
	uint i2;
	result[i].x =(double)0.0;
	result[i].y =(double)0.0;
	for(i2=0; i2 < 16; i2 = i2 +1){
		ev2 = ev + i2;
		temp.x = (double)(input[ev2*n+y].x);
		temp.y = (double)(input[ev2*n+y].y);
		result[i].x = result[i].x + temp.x;
		result[i].y = result[i].y + temp.y;
		temp.x = (double)(input[ev2*n+y].z);
		temp.y = (double)(input[ev2*n+y].w);
		result[i].x = result[i].x + temp.x;
		result[i].y = result[i].y + temp.y;
	}
}

__kernel void kernelweightedsumfloat2double(__global float * nin, __global float * weights, __global float2 * input, __global out double2 * result){
	uint i = get_global_id(0);
	uint n = (uint) nin[i];
	uint i2;
	uint myindex;
	result[i].x =(double)0.0;
	result[i].y =(double)0.0;
	for(i2=0; i2 < n; i2 = i2 +1){
		myindex = i*n + i2;
		result[i].x = result[i].x + (double)(weights[myindex]*input[myindex].x);
		result[i].y = result[i].y + (double)(weights[myindex]*input[myindex].y);
	}
}


__kernel void kernelsumfloat2double(__global float * nin, __global float2 * input, __global out double2 * result){
	uint i = get_global_id(0);
	uint n = (uint) nin[i];
	uint i2;
	uint myindex;
	result[i].x =(double)0.0;
	result[i].y =(double)0.0;
	for(i2=0; i2 < n; i2 = i2 +1){
		myindex = i*n + i2;
		result[i].x = result[i].x + (double)(input[myindex].x);
		result[i].y = result[i].y + (double)(input[myindex].y);
	}
}

__kernel void kernelsumdouble2double(__global float * nin, __global double2 * input, __global out double2 * result){
	uint i = get_global_id(0);
	uint n = (uint) nin[i];
	uint i2;
	uint myindex;
	result[i].x =(double)0.0;
	result[i].y =(double)0.0;
	for(i2=0.0f; i2 < n; i2 = i2 +1.0f){
		myindex = i*n + i2;
		result[i].x = result[i].x + input[myindex].x;
		result[i].y = result[i].y + input[myindex].y;
	}
}



__kernel void kernel4orbitaltensor(__global float4 * rtin, uint i, uint j, __global float44 * delpin, __global out float44 * result ){

	uint ind = get_global_id(0);

	float4 rt = rtin[ind];
	float44 delp = delpin[ind];

  float rt2 = -rt.x*rt.x - rt.y*rt.y - rt.z*rt.z + rt.w*rt.w;
  float rt4 = rt2*rt2;

  if(0==i && 0==j){
  result[ind].c = rt.x*rt.x*rt.x*rt - rt2/7.0f *(delp.c.x*rt.x*rt +delp.c.x*rt.x*rt + delp.c.x*rt.x*rt + delp.c*rt.x*rt.x + delp.c*rt.x*rt.x + delp.c*rt.x*rt.x) + rt4/35.0f*(delp.c.x*delp.c + delp.c.x*delp.c + delp.c.x*delp.c);


  result[ind].d = rt.x*rt.x*rt.y*rt - rt2/7.0f *(delp.c.x*rt.y*rt +delp.c.y*rt.x*rt + delp.d.x*rt.x*rt + delp.c*rt.x*rt.y + delp.c*rt.y*rt.x + delp.d*rt.x*rt.x) + rt4/35.0f*(delp.c.x*delp.d + delp.c.y*delp.c + delp.d.x*delp.c);
				        

  result[ind].e = rt.x*rt.x*rt.z*rt - rt2/7.0f *(delp.c.x*rt.z*rt +delp.c.z*rt.x*rt + delp.e.x*rt.x*rt + delp.c*rt.x*rt.z + delp.c*rt.z*rt.x + delp.e*rt.x*rt.x) + rt4/35.0f*(delp.c.x*delp.e + delp.c.z*delp.c + delp.e.x*delp.c);


  result[ind].f = rt.x*rt.x*rt.w*rt - rt2/7.0f *(delp.c.x*rt.w*rt +delp.c.w*rt.x*rt + delp.f.x*rt.x*rt + delp.c*rt.x*rt.w + delp.c*rt.w*rt.x + delp.f*rt.x*rt.x) + rt4/35.0f*(delp.c.x*delp.f + delp.c.w*delp.c + delp.f.x*delp.c);

}

 if(0==i && 1==j){

  result[ind].c = rt.x*rt.y*rt.x*rt - rt2/7.0f *(delp.c.y*rt.x*rt +delp.d.x*rt.x*rt + delp.c.x*rt.y*rt + delp.c*rt.y*rt.x + delp.d*rt.x*rt.x + delp.c*rt.x*rt.y) + rt4/35.0f*(delp.c.y*delp.c + delp.d.x*delp.c + delp.c.x*delp.d);

  result[ind].d = rt.x*rt.y*rt.y*rt - rt2/7.0f *(delp.c.y*rt.y*rt +delp.d.y*rt.x*rt + delp.d.x*rt.y*rt + delp.c*rt.y*rt.y + delp.d*rt.y*rt.x + delp.d*rt.x*rt.y) + rt4/35.0f*(delp.c.y*delp.d + delp.d.y*delp.c + delp.d.x*delp.d);

  result[ind].e = rt.x*rt.y*rt.z*rt - rt2/7.0f *(delp.c.y*rt.z*rt +delp.d.z*rt.x*rt + delp.e.x*rt.y*rt + delp.c*rt.y*rt.z + delp.d*rt.z*rt.x + delp.e*rt.x*rt.y) + rt4/35.0f*(delp.c.y*delp.e + delp.d.z*delp.c + delp.e.x*delp.d);

  result[ind].f = rt.x*rt.y*rt.w*rt - rt2/7.0f *(delp.c.y*rt.w*rt +delp.d.w*rt.x*rt + delp.f.x*rt.y*rt + delp.c*rt.y*rt.w + delp.d*rt.w*rt.x + delp.f*rt.x*rt.y) + rt4/35.0f*(delp.c.y*delp.f + delp.d.w*delp.c + delp.f.x*delp.d);
 }

 if(0==i && 2==j){

  result[ind].c = rt.x*rt.z*rt.x*rt - rt2/7.0f *(delp.c.z*rt.x*rt +delp.e.x*rt.x*rt + delp.c.x*rt.z*rt + delp.c*rt.z*rt.x + delp.e*rt.x*rt.x + delp.c*rt.x*rt.z) + rt4/35.0f*(delp.c.z*delp.c + delp.e.x*delp.c + delp.c.x*delp.e);

  result[ind].d = rt.x*rt.z*rt.y*rt - rt2/7.0f *(delp.c.z*rt.y*rt +delp.e.y*rt.x*rt + delp.d.x*rt.z*rt + delp.c*rt.z*rt.y + delp.e*rt.y*rt.x + delp.d*rt.x*rt.z) + rt4/35.0f*(delp.c.z*delp.d + delp.e.y*delp.c + delp.d.x*delp.e);

  result[ind].e = rt.x*rt.z*rt.z*rt - rt2/7.0f *(delp.c.z*rt.z*rt +delp.e.z*rt.x*rt + delp.e.x*rt.z*rt + delp.c*rt.z*rt.z + delp.e*rt.z*rt.x + delp.e*rt.x*rt.z) + rt4/35.0f*(delp.c.z*delp.e + delp.e.z*delp.c + delp.e.x*delp.e);

  result[ind].f = rt.x*rt.z*rt.w*rt - rt2/7.0f *(delp.c.z*rt.w*rt +delp.e.w*rt.x*rt + delp.f.x*rt.z*rt + delp.c*rt.z*rt.w + delp.e*rt.w*rt.x + delp.f*rt.x*rt.z) + rt4/35.0f*(delp.c.z*delp.f + delp.e.w*delp.c + delp.f.x*delp.e);
}

 if(0==i && 3==j){

  result[ind].c = rt.x*rt.w*rt.x*rt - rt2/7.0f *(delp.c.w*rt.x*rt +delp.f.x*rt.x*rt + delp.c.x*rt.w*rt + delp.c*rt.w*rt.x + delp.f*rt.x*rt.x + delp.c*rt.x*rt.w) + rt4/35.0f*(delp.c.w*delp.c + delp.f.x*delp.c + delp.c.x*delp.f);

  result[ind].d = rt.x*rt.w*rt.y*rt - rt2/7.0f *(delp.c.w*rt.y*rt +delp.f.y*rt.x*rt + delp.d.x*rt.w*rt + delp.c*rt.w*rt.y + delp.f*rt.y*rt.x + delp.d*rt.x*rt.w) + rt4/35.0f*(delp.c.w*delp.d + delp.f.y*delp.c + delp.d.x*delp.f);

  result[ind].e = rt.x*rt.w*rt.z*rt - rt2/7.0f *(delp.c.w*rt.z*rt +delp.f.z*rt.x*rt + delp.e.x*rt.w*rt + delp.c*rt.w*rt.z + delp.f*rt.z*rt.x + delp.e*rt.x*rt.w) + rt4/35.0f*(delp.c.w*delp.e + delp.f.z*delp.c + delp.e.x*delp.f);

  result[ind].f = rt.x*rt.w*rt.w*rt - rt2/7.0f *(delp.c.w*rt.w*rt +delp.f.w*rt.x*rt + delp.f.x*rt.w*rt + delp.c*rt.w*rt.w + delp.f*rt.w*rt.x + delp.f*rt.x*rt.w) + rt4/35.0f*(delp.c.w*delp.f + delp.f.w*delp.c + delp.f.x*delp.f);

}



  if(1==i && 0==j){

  result[ind].c = rt.y*rt.x*rt.x*rt - rt2/7.0f *(delp.d.x*rt.x*rt +delp.c.x*rt.y*rt + delp.c.y*rt.x*rt + delp.d*rt.x*rt.x + delp.c*rt.x*rt.y + delp.c*rt.y*rt.x) + rt4/35.0f*(delp.d.x*delp.c + delp.c.x*delp.d + delp.c.y*delp.c);

  result[ind].d = rt.y*rt.x*rt.y*rt - rt2/7.0f *(delp.d.x*rt.y*rt +delp.c.y*rt.y*rt + delp.d.y*rt.x*rt + delp.d*rt.x*rt.y + delp.c*rt.y*rt.y + delp.d*rt.y*rt.x) + rt4/35.0f*(delp.d.x*delp.d + delp.c.y*delp.d + delp.d.y*delp.c);

  result[ind].e = rt.y*rt.x*rt.z*rt - rt2/7.0f *(delp.d.x*rt.z*rt +delp.c.z*rt.y*rt + delp.e.y*rt.x*rt + delp.d*rt.x*rt.z + delp.c*rt.z*rt.y + delp.e*rt.y*rt.x) + rt4/35.0f*(delp.d.x*delp.e + delp.c.z*delp.d + delp.e.y*delp.c);

  result[ind].f = rt.y*rt.x*rt.w*rt - rt2/7.0f *(delp.d.x*rt.w*rt +delp.c.w*rt.y*rt + delp.f.y*rt.x*rt + delp.d*rt.x*rt.w + delp.c*rt.w*rt.y + delp.f*rt.y*rt.x) + rt4/35.0f*(delp.d.x*delp.f + delp.c.w*delp.d + delp.f.y*delp.c);
}


 if(1==i && 1==j){

  result[ind].c = rt.y*rt.y*rt.x*rt - rt2/7.0f *(delp.d.y*rt.x*rt +delp.d.x*rt.y*rt + delp.c.y*rt.y*rt + delp.d*rt.y*rt.x + delp.d*rt.x*rt.y + delp.c*rt.y*rt.y) + rt4/35.0f*(delp.d.y*delp.c + delp.d.x*delp.d + delp.c.y*delp.d);

  result[ind].d = rt.y*rt.y*rt.y*rt - rt2/7.0f *(delp.d.y*rt.y*rt +delp.d.y*rt.y*rt + delp.d.y*rt.y*rt + delp.d*rt.y*rt.y + delp.d*rt.y*rt.y + delp.d*rt.y*rt.y) + rt4/35.0f*(delp.d.y*delp.d + delp.d.y*delp.d + delp.d.y*delp.d);

  result[ind].e = rt.y*rt.y*rt.z*rt - rt2/7.0f *(delp.d.y*rt.z*rt +delp.d.z*rt.y*rt + delp.e.y*rt.y*rt + delp.d*rt.y*rt.z + delp.d*rt.z*rt.y + delp.e*rt.y*rt.y) + rt4/35.0f*(delp.d.y*delp.e + delp.d.z*delp.d + delp.e.y*delp.d);

  result[ind].f = rt.y*rt.y*rt.w*rt - rt2/7.0f *(delp.d.y*rt.w*rt +delp.d.w*rt.y*rt + delp.f.y*rt.y*rt + delp.d*rt.y*rt.w + delp.d*rt.w*rt.y + delp.f*rt.y*rt.y) + rt4/35.0f*(delp.d.y*delp.f + delp.d.w*delp.d + delp.f.y*delp.d);
 }

	
  if(1==i && 2==j){

  result[ind].c = rt.y*rt.z*rt.x*rt - rt2/7.0f *(delp.d.z*rt.x*rt +delp.e.x*rt.y*rt + delp.c.y*rt.z*rt + delp.d*rt.z*rt.x + delp.e*rt.x*rt.y + delp.c*rt.y*rt.z) + rt4/35.0f*(delp.d.z*delp.c + delp.e.x*delp.d + delp.c.y*delp.e);

   result[ind].d = rt.y*rt.z*rt.y*rt - rt2/7.0f *(delp.d.z*rt.y*rt +delp.e.y*rt.y*rt + delp.d.y*rt.z*rt + delp.d*rt.z*rt.y + delp.e*rt.y*rt.y + delp.d*rt.y*rt.z) + rt4/35.0f*(delp.d.z*delp.d + delp.e.y*delp.d + delp.d.y*delp.e);

   result[ind].e = rt.y*rt.z*rt.z*rt - rt2/7.0f *(delp.d.z*rt.z*rt +delp.e.z*rt.y*rt + delp.e.y*rt.z*rt + delp.d*rt.z*rt.z + delp.e*rt.z*rt.y + delp.e*rt.y*rt.z) + rt4/35.0f*(delp.d.z*delp.e + delp.e.z*delp.d + delp.e.y*delp.e);

   result[ind].f = rt.y*rt.z*rt.w*rt - rt2/7.0f *(delp.d.z*rt.w*rt +delp.e.w*rt.y*rt + delp.f.y*rt.z*rt + delp.d*rt.z*rt.w + delp.e*rt.w*rt.y + delp.f*rt.y*rt.z) + rt4/35.0f*(delp.d.z*delp.f + delp.e.w*delp.d + delp.f.y*delp.e);

}


 if(1==i && 3==j){

   result[ind].c = rt.y*rt.w*rt.x*rt - rt2/7.0f *(delp.d.w*rt.x*rt +delp.f.x*rt.y*rt + delp.c.y*rt.w*rt + delp.d*rt.w*rt.x + delp.f*rt.x*rt.y + delp.c*rt.y*rt.w) + rt4/35.0f*(delp.d.w*delp.c + delp.f.x*delp.d + delp.c.y*delp.f);

   result[ind].d = rt.y*rt.w*rt.y*rt - rt2/7.0f *(delp.d.w*rt.y*rt +delp.f.y*rt.y*rt + delp.d.y*rt.w*rt + delp.d*rt.w*rt.y + delp.f*rt.y*rt.y + delp.d*rt.y*rt.w) + rt4/35.0f*(delp.d.w*delp.d + delp.f.y*delp.d + delp.d.y*delp.f);

   result[ind].e = rt.y*rt.w*rt.z*rt - rt2/7.0f *(delp.d.w*rt.z*rt +delp.f.z*rt.y*rt + delp.e.y*rt.w*rt + delp.d*rt.w*rt.z + delp.f*rt.z*rt.y + delp.e*rt.y*rt.w) + rt4/35.0f*(delp.d.w*delp.e + delp.f.z*delp.d + delp.e.y*delp.f);

   result[ind].f = rt.y*rt.w*rt.w*rt - rt2/7.0f *(delp.d.w*rt.w*rt +delp.f.w*rt.y*rt + delp.f.y*rt.w*rt + delp.d*rt.w*rt.w + delp.f*rt.w*rt.y + delp.f*rt.y*rt.w) + rt4/35.0f*(delp.d.w*delp.f + delp.f.w*delp.d + delp.f.y*delp.f);
}




  if(2==i && 0==j){
    result[ind].c = rt.z*rt.x*rt.x*rt - rt2/7.0f *(delp.e.x*rt.x*rt +delp.c.x*rt.z*rt + delp.c.z*rt.x*rt + delp.e*rt.x*rt.x + delp.c*rt.x*rt.z + delp.c*rt.z*rt.x) + rt4/35.0f*(delp.e.x*delp.c + delp.c.x*delp.e + delp.c.z*delp.c);

    result[ind].d = rt.z*rt.x*rt.y*rt - rt2/7.0f *(delp.e.x*rt.y*rt +delp.c.y*rt.z*rt + delp.d.z*rt.x*rt + delp.e*rt.x*rt.y + delp.c*rt.y*rt.z + delp.d*rt.z*rt.x) + rt4/35.0f*(delp.e.x*delp.d + delp.c.y*delp.e + delp.d.z*delp.c);

    result[ind].e = rt.z*rt.x*rt.z*rt - rt2/7.0f *(delp.e.x*rt.z*rt +delp.c.z*rt.z*rt + delp.e.z*rt.x*rt + delp.e*rt.x*rt.z + delp.c*rt.z*rt.z + delp.e*rt.z*rt.x) + rt4/35.0f*(delp.e.x*delp.e + delp.c.z*delp.e + delp.e.z*delp.c);

    result[ind].f = rt.z*rt.x*rt.w*rt - rt2/7.0f *(delp.e.x*rt.w*rt +delp.c.w*rt.z*rt + delp.f.z*rt.x*rt + delp.e*rt.x*rt.w + delp.c*rt.w*rt.z + delp.f*rt.z*rt.x) + rt4/35.0f*(delp.e.x*delp.f + delp.c.w*delp.e + delp.f.z*delp.c);
}
	
    if(2==i && 1==j){

    result[ind].c = rt.z*rt.y*rt.x*rt - rt2/7.0f *(delp.e.y*rt.x*rt +delp.d.x*rt.z*rt + delp.c.z*rt.y*rt + delp.e*rt.y*rt.x + delp.d*rt.x*rt.z + delp.c*rt.z*rt.y) + rt4/35.0f*(delp.e.y*delp.c + delp.d.x*delp.e + delp.c.z*delp.d);

    result[ind].d = rt.z*rt.y*rt.y*rt - rt2/7.0f *(delp.e.y*rt.y*rt +delp.d.y*rt.z*rt + delp.d.z*rt.y*rt + delp.e*rt.y*rt.y + delp.d*rt.y*rt.z + delp.d*rt.z*rt.y) + rt4/35.0f*(delp.e.y*delp.d + delp.d.y*delp.e + delp.d.z*delp.d);

    result[ind].e = rt.z*rt.y*rt.z*rt - rt2/7.0f *(delp.e.y*rt.z*rt +delp.d.z*rt.z*rt + delp.e.z*rt.y*rt + delp.e*rt.y*rt.z + delp.d*rt.z*rt.z + delp.e*rt.z*rt.y) + rt4/35.0f*(delp.e.y*delp.e + delp.d.z*delp.e + delp.e.z*delp.d);

    result[ind].f = rt.z*rt.y*rt.w*rt - rt2/7.0f *(delp.e.y*rt.w*rt +delp.d.w*rt.z*rt + delp.f.z*rt.y*rt + delp.e*rt.y*rt.w + delp.d*rt.w*rt.z + delp.f*rt.z*rt.y) + rt4/35.0f*(delp.e.y*delp.f + delp.d.w*delp.e + delp.f.z*delp.d);
}
 
   if(2==i && 2==j){

   result[ind].c = rt.z*rt.z*rt.x*rt - rt2/7.0f *(delp.e.z*rt.x*rt +delp.e.x*rt.z*rt + delp.c.z*rt.z*rt + delp.e*rt.z*rt.x + delp.e*rt.x*rt.z + delp.c*rt.z*rt.z) + rt4/35.0f*(delp.e.z*delp.c + delp.e.x*delp.e + delp.c.z*delp.e);

   result[ind].d = rt.z*rt.z*rt.y*rt - rt2/7.0f *(delp.e.z*rt.y*rt +delp.e.y*rt.z*rt + delp.d.z*rt.z*rt + delp.e*rt.z*rt.y + delp.e*rt.y*rt.z + delp.d*rt.z*rt.z) + rt4/35.0f*(delp.e.z*delp.d + delp.e.y*delp.e + delp.d.z*delp.e);

   result[ind].e = rt.z*rt.z*rt.z*rt - rt2/7.0f *(delp.e.z*rt.z*rt +delp.e.z*rt.z*rt + delp.e.z*rt.z*rt + delp.e*rt.z*rt.z + delp.e*rt.z*rt.z + delp.e*rt.z*rt.z) + rt4/35.0f*(delp.e.z*delp.e + delp.e.z*delp.e + delp.e.z*delp.e);

   result[ind].f = rt.z*rt.z*rt.w*rt - rt2/7.0f *(delp.e.z*rt.w*rt +delp.e.w*rt.z*rt + delp.f.z*rt.z*rt + delp.e*rt.z*rt.w + delp.e*rt.w*rt.z + delp.f*rt.z*rt.z) + rt4/35.0f*(delp.e.z*delp.f + delp.e.w*delp.e + delp.f.z*delp.e);
}
   if(2==i && 3==j){

   result[ind].c = rt.z*rt.w*rt.x*rt - rt2/7.0f *(delp.e.w*rt.x*rt +delp.f.x*rt.z*rt + delp.c.z*rt.w*rt + delp.e*rt.w*rt.x + delp.f*rt.x*rt.z + delp.c*rt.z*rt.w) + rt4/35.0f*(delp.e.w*delp.c + delp.f.x*delp.e + delp.c.z*delp.f);

   result[ind].d = rt.z*rt.w*rt.y*rt - rt2/7.0f *(delp.e.w*rt.y*rt +delp.f.y*rt.z*rt + delp.d.z*rt.w*rt + delp.e*rt.w*rt.y + delp.f*rt.y*rt.z + delp.d*rt.z*rt.w) + rt4/35.0f*(delp.e.w*delp.d + delp.f.y*delp.e + delp.d.z*delp.f);

   result[ind].e = rt.z*rt.w*rt.z*rt - rt2/7.0f *(delp.e.w*rt.z*rt +delp.f.z*rt.z*rt + delp.e.z*rt.w*rt + delp.e*rt.w*rt.z + delp.f*rt.z*rt.z + delp.e*rt.z*rt.w) + rt4/35.0f*(delp.e.w*delp.e + delp.f.z*delp.e + delp.e.z*delp.f);

   result[ind].f = rt.z*rt.w*rt.w*rt - rt2/7.0f *(delp.e.w*rt.w*rt +delp.f.w*rt.z*rt + delp.f.z*rt.w*rt + delp.e*rt.w*rt.w + delp.f*rt.w*rt.z + delp.f*rt.z*rt.w) + rt4/35.0f*(delp.e.w*delp.f + delp.f.w*delp.e + delp.f.z*delp.f);
}


  if(3==i && 0==j){
  result[ind].c = rt.w*rt.x*rt.x*rt - rt2/7.0f *(delp.f.x*rt.x*rt +delp.c.x*rt.w*rt + delp.c.w*rt.x*rt + delp.f*rt.x*rt.x + delp.c*rt.x*rt.w + delp.c*rt.w*rt.x) + rt4/35.0f*(delp.f.x*delp.c + delp.c.x*delp.f + delp.c.w*delp.c);

  result[ind].d = rt.w*rt.x*rt.y*rt - rt2/7.0f *(delp.f.x*rt.y*rt +delp.c.y*rt.w*rt + delp.d.w*rt.x*rt + delp.f*rt.x*rt.y + delp.c*rt.y*rt.w + delp.d*rt.w*rt.x) + rt4/35.0f*(delp.f.x*delp.d + delp.c.y*delp.f + delp.d.w*delp.c);

  result[ind].e = rt.w*rt.x*rt.z*rt - rt2/7.0f *(delp.f.x*rt.z*rt +delp.c.z*rt.w*rt + delp.e.w*rt.x*rt + delp.f*rt.x*rt.z + delp.c*rt.z*rt.w + delp.e*rt.w*rt.x) + rt4/35.0f*(delp.f.x*delp.e + delp.c.z*delp.f + delp.e.w*delp.c);

  result[ind].f = rt.w*rt.x*rt.w*rt - rt2/7.0f *(delp.f.x*rt.w*rt +delp.c.w*rt.w*rt + delp.f.w*rt.x*rt + delp.f*rt.x*rt.w + delp.c*rt.w*rt.w + delp.f*rt.w*rt.x) + rt4/35.0f*(delp.f.x*delp.f + delp.c.w*delp.f + delp.f.w*delp.c);
}
	
  if(3==i && 1==j){	

  result[ind].c = rt.w*rt.y*rt.x*rt - rt2/7.0f *(delp.f.y*rt.x*rt +delp.d.x*rt.w*rt + delp.c.w*rt.y*rt + delp.f*rt.y*rt.x + delp.d*rt.x*rt.w + delp.c*rt.w*rt.y) + rt4/35.0f*(delp.f.y*delp.c + delp.d.x*delp.f + delp.c.w*delp.d);

  result[ind].d = rt.w*rt.y*rt.y*rt - rt2/7.0f *(delp.f.y*rt.y*rt +delp.d.y*rt.w*rt + delp.d.w*rt.y*rt + delp.f*rt.y*rt.y + delp.d*rt.y*rt.w + delp.d*rt.w*rt.y) + rt4/35.0f*(delp.f.y*delp.d + delp.d.y*delp.f + delp.d.w*delp.d);

  result[ind].e = rt.w*rt.y*rt.z*rt - rt2/7.0f *(delp.f.y*rt.z*rt +delp.d.z*rt.w*rt + delp.e.w*rt.y*rt + delp.f*rt.y*rt.z + delp.d*rt.z*rt.w + delp.e*rt.w*rt.y) + rt4/35.0f*(delp.f.y*delp.e + delp.d.z*delp.f + delp.e.w*delp.d);

  result[ind].f = rt.w*rt.y*rt.w*rt - rt2/7.0f *(delp.f.y*rt.w*rt +delp.d.w*rt.w*rt + delp.f.w*rt.y*rt + delp.f*rt.y*rt.w + delp.d*rt.w*rt.w + delp.f*rt.w*rt.y) + rt4/35.0f*(delp.f.y*delp.f + delp.d.w*delp.f + delp.f.w*delp.d);
}

   if(3==i && 2==j){

   result[ind].c = rt.w*rt.z*rt.x*rt - rt2/7.0f *(delp.f.z*rt.x*rt +delp.e.x*rt.w*rt + delp.c.w*rt.z*rt + delp.f*rt.z*rt.x + delp.e*rt.x*rt.w + delp.c*rt.w*rt.z) + rt4/35.0f*(delp.f.z*delp.c + delp.e.x*delp.f + delp.c.w*delp.e);

   result[ind].d = rt.w*rt.z*rt.y*rt - rt2/7.0f *(delp.f.z*rt.y*rt +delp.e.y*rt.w*rt + delp.d.w*rt.z*rt + delp.f*rt.z*rt.y + delp.e*rt.y*rt.w + delp.d*rt.w*rt.z) + rt4/35.0f*(delp.f.z*delp.d + delp.e.y*delp.f + delp.d.w*delp.e);

   result[ind].e = rt.w*rt.z*rt.z*rt - rt2/7.0f *(delp.f.z*rt.z*rt +delp.e.z*rt.w*rt + delp.e.w*rt.z*rt + delp.f*rt.z*rt.z + delp.e*rt.z*rt.w + delp.e*rt.w*rt.z) + rt4/35.0f*(delp.f.z*delp.e + delp.e.z*delp.f + delp.e.w*delp.e);

   result[ind].f = rt.w*rt.z*rt.w*rt - rt2/7.0f *(delp.f.z*rt.w*rt +delp.e.w*rt.w*rt + delp.f.w*rt.z*rt + delp.f*rt.z*rt.w + delp.e*rt.w*rt.w + delp.f*rt.w*rt.z) + rt4/35.0f*(delp.f.z*delp.f + delp.e.w*delp.f + delp.f.w*delp.e);
}
	
  if(3==i && 3==j){

  result[ind].c = rt.w*rt.w*rt.x*rt - rt2/7.0f *(delp.f.w*rt.x*rt +delp.f.x*rt.w*rt + delp.c.w*rt.w*rt + delp.f*rt.w*rt.x + delp.f*rt.x*rt.w + delp.c*rt.w*rt.w) + rt4/35.0f*(delp.f.w*delp.c + delp.f.x*delp.f + delp.c.w*delp.f);

  result[ind].d = rt.w*rt.w*rt.y*rt - rt2/7.0f *(delp.f.w*rt.y*rt +delp.f.y*rt.w*rt + delp.d.w*rt.w*rt + delp.f*rt.w*rt.y + delp.f*rt.y*rt.w + delp.d*rt.w*rt.w) + rt4/35.0f*(delp.f.w*delp.d + delp.f.y*delp.f + delp.d.w*delp.f);

  result[ind].e = rt.w*rt.w*rt.z*rt - rt2/7.0f *(delp.f.w*rt.z*rt +delp.f.z*rt.w*rt + delp.e.w*rt.w*rt + delp.f*rt.w*rt.z + delp.f*rt.z*rt.w + delp.e*rt.w*rt.w) + rt4/35.0f*(delp.f.w*delp.e + delp.f.z*delp.f + delp.e.w*delp.f);

  result[ind].f = rt.w*rt.w*rt.w*rt - rt2/7.0f *(delp.f.w*rt.w*rt +delp.f.w*rt.w*rt + delp.f.w*rt.w*rt + delp.f*rt.w*rt.w + delp.f*rt.w*rt.w + delp.f*rt.w*rt.w) + rt4/35.0f*(delp.f.w*delp.f + delp.f.w*delp.f + delp.f.w*delp.f);

}

}



__kernel void kernel4orbitaltensorconst(__global float4 * rtin, uint i, uint j, float44 delp,  __global out float44 * result){
																		
	uint ind = get_global_id(0);

	float4 rt = rtin[ind];


  float rt2 = -rt.x*rt.x - rt.y*rt.y - rt.z*rt.z + rt.w*rt.w;
  float rt4 = rt2*rt2;

  if(0==i && 0==j){
  result[ind].c = rt.x*rt.x*rt.x*rt - rt2/7.0f *(delp.c.x*rt.x*rt +delp.c.x*rt.x*rt + delp.c.x*rt.x*rt + delp.c*rt.x*rt.x + delp.c*rt.x*rt.x + delp.c*rt.x*rt.x) + rt4/35.0f*(delp.c.x*delp.c + delp.c.x*delp.c + delp.c.x*delp.c);


  result[ind].d = rt.x*rt.x*rt.y*rt - rt2/7.0f *(delp.c.x*rt.y*rt +delp.c.y*rt.x*rt + delp.d.x*rt.x*rt + delp.c*rt.x*rt.y + delp.c*rt.y*rt.x + delp.d*rt.x*rt.x) + rt4/35.0f*(delp.c.x*delp.d + delp.c.y*delp.c + delp.d.x*delp.c);


  result[ind].e = rt.x*rt.x*rt.z*rt - rt2/7.0f *(delp.c.x*rt.z*rt +delp.c.z*rt.x*rt + delp.e.x*rt.x*rt + delp.c*rt.x*rt.z + delp.c*rt.z*rt.x + delp.e*rt.x*rt.x) + rt4/35.0f*(delp.c.x*delp.e + delp.c.z*delp.c + delp.e.x*delp.c);


  result[ind].f = rt.x*rt.x*rt.w*rt - rt2/7.0f *(delp.c.x*rt.w*rt +delp.c.w*rt.x*rt + delp.f.x*rt.x*rt + delp.c*rt.x*rt.w + delp.c*rt.w*rt.x + delp.f*rt.x*rt.x) + rt4/35.0f*(delp.c.x*delp.f + delp.c.w*delp.c + delp.f.x*delp.c);
}

  if(0==i && 1==j){

  result[ind].c = rt.x*rt.y*rt.x*rt - rt2/7.0f *(delp.c.y*rt.x*rt +delp.d.x*rt.x*rt + delp.c.x*rt.y*rt + delp.c*rt.y*rt.x + delp.d*rt.x*rt.x + delp.c*rt.x*rt.y) + rt4/35.0f*(delp.c.y*delp.c + delp.d.x*delp.c + delp.c.x*delp.d);

  result[ind].d = rt.x*rt.y*rt.y*rt - rt2/7.0f *(delp.c.y*rt.y*rt +delp.d.y*rt.x*rt + delp.d.x*rt.y*rt + delp.c*rt.y*rt.y + delp.d*rt.y*rt.x + delp.d*rt.x*rt.y) + rt4/35.0f*(delp.c.y*delp.d + delp.d.y*delp.c + delp.d.x*delp.d);

   result[ind].e = rt.x*rt.y*rt.z*rt - rt2/7.0f *(delp.c.y*rt.z*rt +delp.d.z*rt.x*rt + delp.e.x*rt.y*rt + delp.c*rt.y*rt.z + delp.d*rt.z*rt.x + delp.e*rt.x*rt.y) + rt4/35.0f*(delp.c.y*delp.e + delp.d.z*delp.c + delp.e.x*delp.d);

   result[ind].f = rt.x*rt.y*rt.w*rt - rt2/7.0f *(delp.c.y*rt.w*rt +delp.d.w*rt.x*rt + delp.f.x*rt.y*rt + delp.c*rt.y*rt.w + delp.d*rt.w*rt.x + delp.f*rt.x*rt.y) + rt4/35.0f*(delp.c.y*delp.f + delp.d.w*delp.c + delp.f.x*delp.d);
}

   if(0==i && 2==j){

   result[ind].c = rt.x*rt.z*rt.x*rt - rt2/7.0f *(delp.c.z*rt.x*rt +delp.e.x*rt.x*rt + delp.c.x*rt.z*rt + delp.c*rt.z*rt.x + delp.e*rt.x*rt.x + delp.c*rt.x*rt.z) + rt4/35.0f*(delp.c.z*delp.c + delp.e.x*delp.c + delp.c.x*delp.e);

   result[ind].d = rt.x*rt.z*rt.y*rt - rt2/7.0f *(delp.c.z*rt.y*rt +delp.e.y*rt.x*rt + delp.d.x*rt.z*rt + delp.c*rt.z*rt.y + delp.e*rt.y*rt.x + delp.d*rt.x*rt.z) + rt4/35.0f*(delp.c.z*delp.d + delp.e.y*delp.c + delp.d.x*delp.e);

   result[ind].e = rt.x*rt.z*rt.z*rt - rt2/7.0f *(delp.c.z*rt.z*rt +delp.e.z*rt.x*rt + delp.e.x*rt.z*rt + delp.c*rt.z*rt.z + delp.e*rt.z*rt.x + delp.e*rt.x*rt.z) + rt4/35.0f*(delp.c.z*delp.e + delp.e.z*delp.c + delp.e.x*delp.e);

   result[ind].f = rt.x*rt.z*rt.w*rt - rt2/7.0f *(delp.c.z*rt.w*rt +delp.e.w*rt.x*rt + delp.f.x*rt.z*rt + delp.c*rt.z*rt.w + delp.e*rt.w*rt.x + delp.f*rt.x*rt.z) + rt4/35.0f*(delp.c.z*delp.f + delp.e.w*delp.c + delp.f.x*delp.e);

}

   if(0==i && 3==j){

   result[ind].c = rt.x*rt.w*rt.x*rt - rt2/7.0f *(delp.c.w*rt.x*rt +delp.f.x*rt.x*rt + delp.c.x*rt.w*rt + delp.c*rt.w*rt.x + delp.f*rt.x*rt.x + delp.c*rt.x*rt.w) + rt4/35.0f*(delp.c.w*delp.c + delp.f.x*delp.c + delp.c.x*delp.f);

   result[ind].d = rt.x*rt.w*rt.y*rt - rt2/7.0f *(delp.c.w*rt.y*rt +delp.f.y*rt.x*rt + delp.d.x*rt.w*rt + delp.c*rt.w*rt.y + delp.f*rt.y*rt.x + delp.d*rt.x*rt.w) + rt4/35.0f*(delp.c.w*delp.d + delp.f.y*delp.c + delp.d.x*delp.f);

   result[ind].e = rt.x*rt.w*rt.z*rt - rt2/7.0f *(delp.c.w*rt.z*rt +delp.f.z*rt.x*rt + delp.e.x*rt.w*rt + delp.c*rt.w*rt.z + delp.f*rt.z*rt.x + delp.e*rt.x*rt.w) + rt4/35.0f*(delp.c.w*delp.e + delp.f.z*delp.c + delp.e.x*delp.f);

   result[ind].f = rt.x*rt.w*rt.w*rt - rt2/7.0f *(delp.c.w*rt.w*rt +delp.f.w*rt.x*rt + delp.f.x*rt.w*rt + delp.c*rt.w*rt.w + delp.f*rt.w*rt.x + delp.f*rt.x*rt.w) + rt4/35.0f*(delp.c.w*delp.f + delp.f.w*delp.c + delp.f.x*delp.f);

}
		

   if(1==i && 0==j){

   result[ind].c = rt.y*rt.x*rt.x*rt - rt2/7.0f *(delp.d.x*rt.x*rt +delp.c.x*rt.y*rt + delp.c.y*rt.x*rt + delp.d*rt.x*rt.x + delp.c*rt.x*rt.y + delp.c*rt.y*rt.x) + rt4/35.0f*(delp.d.x*delp.c + delp.c.x*delp.d + delp.c.y*delp.c);

   result[ind].d = rt.y*rt.x*rt.y*rt - rt2/7.0f *(delp.d.x*rt.y*rt +delp.c.y*rt.y*rt + delp.d.y*rt.x*rt + delp.d*rt.x*rt.y + delp.c*rt.y*rt.y + delp.d*rt.y*rt.x) + rt4/35.0f*(delp.d.x*delp.d + delp.c.y*delp.d + delp.d.y*delp.c);

   result[ind].e = rt.y*rt.x*rt.z*rt - rt2/7.0f *(delp.d.x*rt.z*rt +delp.c.z*rt.y*rt + delp.e.y*rt.x*rt + delp.d*rt.x*rt.z + delp.c*rt.z*rt.y + delp.e*rt.y*rt.x) + rt4/35.0f*(delp.d.x*delp.e + delp.c.z*delp.d + delp.e.y*delp.c);

   result[ind].f = rt.y*rt.x*rt.w*rt - rt2/7.0f *(delp.d.x*rt.w*rt +delp.c.w*rt.y*rt + delp.f.y*rt.x*rt + delp.d*rt.x*rt.w + delp.c*rt.w*rt.y + delp.f*rt.y*rt.x) + rt4/35.0f*(delp.d.x*delp.f + delp.c.w*delp.d + delp.f.y*delp.c);
}


   if(1==i && 1==j){

   result[ind].c = rt.y*rt.y*rt.x*rt - rt2/7.0f *(delp.d.y*rt.x*rt +delp.d.x*rt.y*rt + delp.c.y*rt.y*rt + delp.d*rt.y*rt.x + delp.d*rt.x*rt.y + delp.c*rt.y*rt.y) + rt4/35.0f*(delp.d.y*delp.c + delp.d.x*delp.d + delp.c.y*delp.d);

   result[ind].d = rt.y*rt.y*rt.y*rt - rt2/7.0f *(delp.d.y*rt.y*rt +delp.d.y*rt.y*rt + delp.d.y*rt.y*rt + delp.d*rt.y*rt.y + delp.d*rt.y*rt.y + delp.d*rt.y*rt.y) + rt4/35.0f*(delp.d.y*delp.d + delp.d.y*delp.d + delp.d.y*delp.d);

   result[ind].e = rt.y*rt.y*rt.z*rt - rt2/7.0f *(delp.d.y*rt.z*rt +delp.d.z*rt.y*rt + delp.e.y*rt.y*rt + delp.d*rt.y*rt.z + delp.d*rt.z*rt.y + delp.e*rt.y*rt.y) + rt4/35.0f*(delp.d.y*delp.e + delp.d.z*delp.d + delp.e.y*delp.d);

   result[ind].f = rt.y*rt.y*rt.w*rt - rt2/7.0f *(delp.d.y*rt.w*rt +delp.d.w*rt.y*rt + delp.f.y*rt.y*rt + delp.d*rt.y*rt.w + delp.d*rt.w*rt.y + delp.f*rt.y*rt.y) + rt4/35.0f*(delp.d.y*delp.f + delp.d.w*delp.d + delp.f.y*delp.d);
}

  if(1==i && 2==j){

  result[ind].c = rt.y*rt.z*rt.x*rt - rt2/7.0f *(delp.d.z*rt.x*rt +delp.e.x*rt.y*rt + delp.c.y*rt.z*rt + delp.d*rt.z*rt.x + delp.e*rt.x*rt.y + delp.c*rt.y*rt.z) + rt4/35.0f*(delp.d.z*delp.c + delp.e.x*delp.d + delp.c.y*delp.e);

  result[ind].d = rt.y*rt.z*rt.y*rt - rt2/7.0f *(delp.d.z*rt.y*rt +delp.e.y*rt.y*rt + delp.d.y*rt.z*rt + delp.d*rt.z*rt.y + delp.e*rt.y*rt.y + delp.d*rt.y*rt.z) + rt4/35.0f*(delp.d.z*delp.d + delp.e.y*delp.d + delp.d.y*delp.e);

  result[ind].e = rt.y*rt.z*rt.z*rt - rt2/7.0f *(delp.d.z*rt.z*rt +delp.e.z*rt.y*rt + delp.e.y*rt.z*rt + delp.d*rt.z*rt.z + delp.e*rt.z*rt.y + delp.e*rt.y*rt.z) + rt4/35.0f*(delp.d.z*delp.e + delp.e.z*delp.d + delp.e.y*delp.e);

  result[ind].f = rt.y*rt.z*rt.w*rt - rt2/7.0f *(delp.d.z*rt.w*rt +delp.e.w*rt.y*rt + delp.f.y*rt.z*rt + delp.d*rt.z*rt.w + delp.e*rt.w*rt.y + delp.f*rt.y*rt.z) + rt4/35.0f*(delp.d.z*delp.f + delp.e.w*delp.d + delp.f.y*delp.e);
}

  if(1==i && 3==j){

  result[ind].c = rt.y*rt.w*rt.x*rt - rt2/7.0f *(delp.d.w*rt.x*rt +delp.f.x*rt.y*rt + delp.c.y*rt.w*rt + delp.d*rt.w*rt.x + delp.f*rt.x*rt.y + delp.c*rt.y*rt.w) + rt4/35.0f*(delp.d.w*delp.c + delp.f.x*delp.d + delp.c.y*delp.f);

  result[ind].d = rt.y*rt.w*rt.y*rt - rt2/7.0f *(delp.d.w*rt.y*rt +delp.f.y*rt.y*rt + delp.d.y*rt.w*rt + delp.d*rt.w*rt.y + delp.f*rt.y*rt.y + delp.d*rt.y*rt.w) + rt4/35.0f*(delp.d.w*delp.d + delp.f.y*delp.d + delp.d.y*delp.f);

  result[ind].e = rt.y*rt.w*rt.z*rt - rt2/7.0f *(delp.d.w*rt.z*rt +delp.f.z*rt.y*rt + delp.e.y*rt.w*rt + delp.d*rt.w*rt.z + delp.f*rt.z*rt.y + delp.e*rt.y*rt.w) + rt4/35.0f*(delp.d.w*delp.e + delp.f.z*delp.d + delp.e.y*delp.f);

  result[ind].f = rt.y*rt.w*rt.w*rt - rt2/7.0f *(delp.d.w*rt.w*rt +delp.f.w*rt.y*rt + delp.f.y*rt.w*rt + delp.d*rt.w*rt.w + delp.f*rt.w*rt.y + delp.f*rt.y*rt.w) + rt4/35.0f*(delp.d.w*delp.f + delp.f.w*delp.d + delp.f.y*delp.f);
  }
  

						     
  if(2==i && 0==j){
  result[ind].c = rt.z*rt.x*rt.x*rt - rt2/7.0f *(delp.e.x*rt.x*rt +delp.c.x*rt.z*rt + delp.c.z*rt.x*rt + delp.e*rt.x*rt.x + delp.c*rt.x*rt.z + delp.c*rt.z*rt.x) + rt4/35.0f*(delp.e.x*delp.c + delp.c.x*delp.e + delp.c.z*delp.c);

  result[ind].d = rt.z*rt.x*rt.y*rt - rt2/7.0f *(delp.e.x*rt.y*rt +delp.c.y*rt.z*rt + delp.d.z*rt.x*rt + delp.e*rt.x*rt.y + delp.c*rt.y*rt.z + delp.d*rt.z*rt.x) + rt4/35.0f*(delp.e.x*delp.d + delp.c.y*delp.e + delp.d.z*delp.c);

  result[ind].e = rt.z*rt.x*rt.z*rt - rt2/7.0f *(delp.e.x*rt.z*rt +delp.c.z*rt.z*rt + delp.e.z*rt.x*rt + delp.e*rt.x*rt.z + delp.c*rt.z*rt.z + delp.e*rt.z*rt.x) + rt4/35.0f*(delp.e.x*delp.e + delp.c.z*delp.e + delp.e.z*delp.c);

  result[ind].f = rt.z*rt.x*rt.w*rt - rt2/7.0f *(delp.e.x*rt.w*rt +delp.c.w*rt.z*rt + delp.f.z*rt.x*rt + delp.e*rt.x*rt.w + delp.c*rt.w*rt.z + delp.f*rt.z*rt.x) + rt4/35.0f*(delp.e.x*delp.f + delp.c.w*delp.e + delp.f.z*delp.c);
  }


  if(2==i && 1==j){

  result[ind].c = rt.z*rt.y*rt.x*rt - rt2/7.0f *(delp.e.y*rt.x*rt +delp.d.x*rt.z*rt + delp.c.z*rt.y*rt + delp.e*rt.y*rt.x + delp.d*rt.x*rt.z + delp.c*rt.z*rt.y) + rt4/35.0f*(delp.e.y*delp.c + delp.d.x*delp.e + delp.c.z*delp.d);

  result[ind].d = rt.z*rt.y*rt.y*rt - rt2/7.0f *(delp.e.y*rt.y*rt +delp.d.y*rt.z*rt + delp.d.z*rt.y*rt + delp.e*rt.y*rt.y + delp.d*rt.y*rt.z + delp.d*rt.z*rt.y) + rt4/35.0f*(delp.e.y*delp.d + delp.d.y*delp.e + delp.d.z*delp.d);

  result[ind].e = rt.z*rt.y*rt.z*rt - rt2/7.0f *(delp.e.y*rt.z*rt +delp.d.z*rt.z*rt + delp.e.z*rt.y*rt + delp.e*rt.y*rt.z + delp.d*rt.z*rt.z + delp.e*rt.z*rt.y) + rt4/35.0f*(delp.e.y*delp.e + delp.d.z*delp.e + delp.e.z*delp.d);

  result[ind].f = rt.z*rt.y*rt.w*rt - rt2/7.0f *(delp.e.y*rt.w*rt +delp.d.w*rt.z*rt + delp.f.z*rt.y*rt + delp.e*rt.y*rt.w + delp.d*rt.w*rt.z + delp.f*rt.z*rt.y) + rt4/35.0f*(delp.e.y*delp.f + delp.d.w*delp.e + delp.f.z*delp.d);

}

  if(2==i && 2==j){

  result[ind].c = rt.z*rt.z*rt.x*rt - rt2/7.0f *(delp.e.z*rt.x*rt +delp.e.x*rt.z*rt + delp.c.z*rt.z*rt + delp.e*rt.z*rt.x + delp.e*rt.x*rt.z + delp.c*rt.z*rt.z) + rt4/35.0f*(delp.e.z*delp.c + delp.e.x*delp.e + delp.c.z*delp.e);
		

  result[ind].d = rt.z*rt.z*rt.y*rt - rt2/7.0f *(delp.e.z*rt.y*rt +delp.e.y*rt.z*rt + delp.d.z*rt.z*rt + delp.e*rt.z*rt.y + delp.e*rt.y*rt.z + delp.d*rt.z*rt.z) + rt4/35.0f*(delp.e.z*delp.d + delp.e.y*delp.e + delp.d.z*delp.e);


  result[ind].e = rt.z*rt.z*rt.z*rt - rt2/7.0f *(delp.e.z*rt.z*rt +delp.e.z*rt.z*rt + delp.e.z*rt.z*rt + delp.e*rt.z*rt.z + delp.e*rt.z*rt.z + delp.e*rt.z*rt.z) + rt4/35.0f*(delp.e.z*delp.e + delp.e.z*delp.e + delp.e.z*delp.e);


  result[ind].f = rt.z*rt.z*rt.w*rt - rt2/7.0f *(delp.e.z*rt.w*rt +delp.e.w*rt.z*rt + delp.f.z*rt.z*rt + delp.e*rt.z*rt.w + delp.e*rt.w*rt.z + delp.f*rt.z*rt.z) + rt4/35.0f*(delp.e.z*delp.f + delp.e.w*delp.e + delp.f.z*delp.e);

}

  if(2==i && 3==j){

  result[ind].c = rt.z*rt.w*rt.x*rt - rt2/7.0f *(delp.e.w*rt.x*rt +delp.f.x*rt.z*rt + delp.c.z*rt.w*rt + delp.e*rt.w*rt.x + delp.f*rt.x*rt.z + delp.c*rt.z*rt.w) + rt4/35.0f*(delp.e.w*delp.c + delp.f.x*delp.e + delp.c.z*delp.f);

  result[ind].d = rt.z*rt.w*rt.y*rt - rt2/7.0f *(delp.e.w*rt.y*rt +delp.f.y*rt.z*rt + delp.d.z*rt.w*rt + delp.e*rt.w*rt.y + delp.f*rt.y*rt.z + delp.d*rt.z*rt.w) + rt4/35.0f*(delp.e.w*delp.d + delp.f.y*delp.e + delp.d.z*delp.f);

  result[ind].e = rt.z*rt.w*rt.z*rt - rt2/7.0f *(delp.e.w*rt.z*rt +delp.f.z*rt.z*rt + delp.e.z*rt.w*rt + delp.e*rt.w*rt.z + delp.f*rt.z*rt.z + delp.e*rt.z*rt.w) + rt4/35.0f*(delp.e.w*delp.e + delp.f.z*delp.e + delp.e.z*delp.f);

  result[ind].f = rt.z*rt.w*rt.w*rt - rt2/7.0f *(delp.e.w*rt.w*rt +delp.f.w*rt.z*rt + delp.f.z*rt.w*rt + delp.e*rt.w*rt.w + delp.f*rt.w*rt.z + delp.f*rt.z*rt.w) + rt4/35.0f*(delp.e.w*delp.f + delp.f.w*delp.e + delp.f.z*delp.f);
}


  if(3==i && 0==j){
  result[ind].c = rt.w*rt.x*rt.x*rt - rt2/7.0f *(delp.f.x*rt.x*rt +delp.c.x*rt.w*rt + delp.c.w*rt.x*rt + delp.f*rt.x*rt.x + delp.c*rt.x*rt.w + delp.c*rt.w*rt.x) + rt4/35.0f*(delp.f.x*delp.c + delp.c.x*delp.f + delp.c.w*delp.c);

  result[ind].d = rt.w*rt.x*rt.y*rt - rt2/7.0f *(delp.f.x*rt.y*rt +delp.c.y*rt.w*rt + delp.d.w*rt.x*rt + delp.f*rt.x*rt.y + delp.c*rt.y*rt.w + delp.d*rt.w*rt.x) + rt4/35.0f*(delp.f.x*delp.d + delp.c.y*delp.f + delp.d.w*delp.c);

  result[ind].e = rt.w*rt.x*rt.z*rt - rt2/7.0f *(delp.f.x*rt.z*rt +delp.c.z*rt.w*rt + delp.e.w*rt.x*rt + delp.f*rt.x*rt.z + delp.c*rt.z*rt.w + delp.e*rt.w*rt.x) + rt4/35.0f*(delp.f.x*delp.e + delp.c.z*delp.f + delp.e.w*delp.c);

  result[ind].f = rt.w*rt.x*rt.w*rt - rt2/7.0f *(delp.f.x*rt.w*rt +delp.c.w*rt.w*rt + delp.f.w*rt.x*rt + delp.f*rt.x*rt.w + delp.c*rt.w*rt.w + delp.f*rt.w*rt.x) + rt4/35.0f*(delp.f.x*delp.f + delp.c.w*delp.f + delp.f.w*delp.c);
}

  if(3==i && 1==j){

  result[ind].c = rt.w*rt.y*rt.x*rt - rt2/7.0f *(delp.f.y*rt.x*rt +delp.d.x*rt.w*rt + delp.c.w*rt.y*rt + delp.f*rt.y*rt.x + delp.d*rt.x*rt.w + delp.c*rt.w*rt.y) + rt4/35.0f*(delp.f.y*delp.c + delp.d.x*delp.f + delp.c.w*delp.d);

  result[ind].d = rt.w*rt.y*rt.y*rt - rt2/7.0f *(delp.f.y*rt.y*rt +delp.d.y*rt.w*rt + delp.d.w*rt.y*rt + delp.f*rt.y*rt.y + delp.d*rt.y*rt.w + delp.d*rt.w*rt.y) + rt4/35.0f*(delp.f.y*delp.d + delp.d.y*delp.f + delp.d.w*delp.d);

  result[ind].e = rt.w*rt.y*rt.z*rt - rt2/7.0f *(delp.f.y*rt.z*rt +delp.d.z*rt.w*rt + delp.e.w*rt.y*rt + delp.f*rt.y*rt.z + delp.d*rt.z*rt.w + delp.e*rt.w*rt.y) + rt4/35.0f*(delp.f.y*delp.e + delp.d.z*delp.f + delp.e.w*delp.d);

  result[ind].f = rt.w*rt.y*rt.w*rt - rt2/7.0f *(delp.f.y*rt.w*rt +delp.d.w*rt.w*rt + delp.f.w*rt.y*rt + delp.f*rt.y*rt.w + delp.d*rt.w*rt.w + delp.f*rt.w*rt.y) + rt4/35.0f*(delp.f.y*delp.f + delp.d.w*delp.f + delp.f.w*delp.d);
  }

  if(3==i && 2==j){

  result[ind].c = rt.w*rt.z*rt.x*rt - rt2/7.0f *(delp.f.z*rt.x*rt +delp.e.x*rt.w*rt + delp.c.w*rt.z*rt + delp.f*rt.z*rt.x + delp.e*rt.x*rt.w + delp.c*rt.w*rt.z) + rt4/35.0f*(delp.f.z*delp.c + delp.e.x*delp.f + delp.c.w*delp.e);

  result[ind].d = rt.w*rt.z*rt.y*rt - rt2/7.0f *(delp.f.z*rt.y*rt +delp.e.y*rt.w*rt + delp.d.w*rt.z*rt + delp.f*rt.z*rt.y + delp.e*rt.y*rt.w + delp.d*rt.w*rt.z) + rt4/35.0f*(delp.f.z*delp.d + delp.e.y*delp.f + delp.d.w*delp.e);

  result[ind].e = rt.w*rt.z*rt.z*rt - rt2/7.0f *(delp.f.z*rt.z*rt +delp.e.z*rt.w*rt + delp.e.w*rt.z*rt + delp.f*rt.z*rt.z + delp.e*rt.z*rt.w + delp.e*rt.w*rt.z) + rt4/35.0f*(delp.f.z*delp.e + delp.e.z*delp.f + delp.e.w*delp.e);

  result[ind].f = rt.w*rt.z*rt.w*rt - rt2/7.0f *(delp.f.z*rt.w*rt +delp.e.w*rt.w*rt + delp.f.w*rt.z*rt + delp.f*rt.z*rt.w + delp.e*rt.w*rt.w + delp.f*rt.w*rt.z) + rt4/35.0f*(delp.f.z*delp.f + delp.e.w*delp.f + delp.f.w*delp.e);
  }

  if(3==i && 3==j){

  result[ind].c = rt.w*rt.w*rt.x*rt - rt2/7.0f *(delp.f.w*rt.x*rt +delp.f.x*rt.w*rt + delp.c.w*rt.w*rt + delp.f*rt.w*rt.x + delp.f*rt.x*rt.w + delp.c*rt.w*rt.w) + rt4/35.0f*(delp.f.w*delp.c + delp.f.x*delp.f + delp.c.w*delp.f);

  result[ind].d = rt.w*rt.w*rt.y*rt - rt2/7.0f *(delp.f.w*rt.y*rt +delp.f.y*rt.w*rt + delp.d.w*rt.w*rt + delp.f*rt.w*rt.y + delp.f*rt.y*rt.w + delp.d*rt.w*rt.w) + rt4/35.0f*(delp.f.w*delp.d + delp.f.y*delp.f + delp.d.w*delp.f);

  result[ind].e = rt.w*rt.w*rt.z*rt - rt2/7.0f *(delp.f.w*rt.z*rt +delp.f.z*rt.w*rt + delp.e.w*rt.w*rt + delp.f*rt.w*rt.z + delp.f*rt.z*rt.w + delp.e*rt.w*rt.w) + rt4/35.0f*(delp.f.w*delp.e + delp.f.z*delp.f + delp.e.w*delp.f);

  result[ind].f = rt.w*rt.w*rt.w*rt - rt2/7.0f *(delp.f.w*rt.w*rt +delp.f.w*rt.w*rt + delp.f.w*rt.w*rt + delp.f*rt.w*rt.w + delp.f*rt.w*rt.w + delp.f*rt.w*rt.w) + rt4/35.0f*(delp.f.w*delp.f + delp.f.w*delp.f + delp.f.w*delp.f);
}

}



__kernel void kernel3orbitaltensor(__global float4 * rtin, __global float4 * pain, __global out float444 * result){

	uint ind = get_global_id(0);

	float4 rt = rtin[ind];
	float4 pa = pain[ind];

	float pa2;
	float rt2;
	float4 gpac;
	float4 gpad;
	float4 gpae;
	float4 gpaf;
	
	pa2 = -pa.x*pa.x-pa.y*pa.y-pa.z*pa.z + pa.w*pa.w;
	rt2 = -rt.x*rt.x-rt.y*rt.y-rt.z*rt.z + rt.w*rt.w;

	
	gpac   =     -pa.x*pa/pa2;
	gpac.x = gpac.x -1.0f;
	
	gpad   =     -pa.y*pa/pa2;
	gpad.y = gpad.y -1.0f;
	
	gpae   =     -pa.z*pa/pa2;
	gpae.z = gpae.z -1.0f;
	
	gpaf   =     -pa.w*pa/pa2;
	gpaf.w = gpaf.w +1.0f;
	
	result[ind].cc.x = rt.x*rt.x*rt.x - 0.2f*rt2*(gpac.x*rt.x + gpac.x*rt.x + gpac.x*rt.x);
	result[ind].cc.y = rt.x*rt.x*rt.y - 0.2f*rt2*(gpac.x*rt.y + gpac.y*rt.x + gpad.x*rt.x);
	result[ind].cc.z = rt.x*rt.x*rt.z - 0.2f*rt2*(gpac.x*rt.z + gpac.z*rt.x + gpae.x*rt.x);
	result[ind].cc.w = rt.x*rt.x*rt.w - 0.2f*rt2*(gpac.x*rt.w + gpac.w*rt.x + gpaf.x*rt.x);
	
	result[ind].cd.x = rt.x*rt.y*rt.x - 0.2f*rt2*(gpac.y*rt.x + gpad.x*rt.x + gpac.x*rt.y);
	result[ind].cd.y = rt.x*rt.y*rt.y - 0.2f*rt2*(gpac.y*rt.y + gpad.y*rt.x + gpad.x*rt.y);
	result[ind].cd.z = rt.x*rt.y*rt.z - 0.2f*rt2*(gpac.y*rt.z + gpad.z*rt.x + gpae.x*rt.y);
	result[ind].cd.w = rt.x*rt.y*rt.w - 0.2f*rt2*(gpac.y*rt.w + gpad.w*rt.x + gpaf.x*rt.y);
	
	result[ind].ce.x = rt.x*rt.z*rt.x - 0.2f*rt2*(gpac.z*rt.x + gpae.x*rt.x + gpac.x*rt.z);
	result[ind].ce.y = rt.x*rt.z*rt.y - 0.2f*rt2*(gpac.z*rt.y + gpae.y*rt.x + gpad.x*rt.z);
	result[ind].ce.z = rt.x*rt.z*rt.z - 0.2f*rt2*(gpac.z*rt.z + gpae.z*rt.x + gpae.x*rt.z);
	result[ind].ce.w = rt.x*rt.z*rt.w - 0.2f*rt2*(gpac.z*rt.w + gpae.w*rt.x + gpaf.x*rt.z);
	
	result[ind].cf.x = rt.x*rt.w*rt.x - 0.2f*rt2*(gpac.w*rt.x + gpaf.x*rt.x + gpac.x*rt.w);
	result[ind].cf.y = rt.x*rt.w*rt.y - 0.2f*rt2*(gpac.w*rt.y + gpaf.y*rt.x + gpad.x*rt.w);
	result[ind].cf.z = rt.x*rt.w*rt.z - 0.2f*rt2*(gpac.w*rt.z + gpaf.z*rt.x + gpae.x*rt.w);
	result[ind].cf.w = rt.x*rt.w*rt.w - 0.2f*rt2*(gpac.w*rt.w + gpaf.w*rt.x + gpaf.x*rt.w);
	
	/**/
	result[ind].dc.x = rt.y*rt.x*rt.x - 0.2f*rt2*(gpad.x*rt.x + gpac.x*rt.y + gpac.y*rt.x);
	result[ind].dc.y = rt.y*rt.x*rt.y - 0.2f*rt2*(gpad.x*rt.y + gpac.y*rt.y + gpad.y*rt.x);
	result[ind].dc.z = rt.y*rt.x*rt.z - 0.2f*rt2*(gpad.x*rt.z + gpac.z*rt.y + gpae.y*rt.x);
	result[ind].dc.w = rt.y*rt.x*rt.w - 0.2f*rt2*(gpad.x*rt.w + gpac.w*rt.y + gpaf.y*rt.x);
	
	result[ind].dd.x = rt.y*rt.y*rt.x - 0.2f*rt2*(gpad.y*rt.x + gpad.x*rt.y + gpac.y*rt.y);
	result[ind].dd.y = rt.y*rt.y*rt.y - 0.2f*rt2*(gpad.y*rt.y + gpad.y*rt.y + gpad.y*rt.y);
	result[ind].dd.z = rt.y*rt.y*rt.z - 0.2f*rt2*(gpad.y*rt.z + gpad.z*rt.y + gpae.y*rt.y);
	result[ind].dd.w = rt.y*rt.y*rt.w - 0.2f*rt2*(gpad.y*rt.w + gpad.w*rt.y + gpaf.y*rt.y);
	
	result[ind].de.x = rt.y*rt.z*rt.x - 0.2f*rt2*(gpad.z*rt.x + gpae.x*rt.y + gpac.y*rt.z);
	result[ind].de.y = rt.y*rt.z*rt.y - 0.2f*rt2*(gpad.z*rt.y + gpae.y*rt.y + gpad.y*rt.z);
	result[ind].de.z = rt.y*rt.z*rt.z - 0.2f*rt2*(gpad.z*rt.z + gpae.z*rt.y + gpae.y*rt.z);
	result[ind].de.w = rt.y*rt.z*rt.w - 0.2f*rt2*(gpad.z*rt.w + gpae.w*rt.y + gpaf.y*rt.z);
	
	result[ind].df.x = rt.y*rt.w*rt.x - 0.2f*rt2*(gpad.w*rt.x + gpaf.x*rt.y + gpac.y*rt.w);
	result[ind].df.y = rt.y*rt.w*rt.y - 0.2f*rt2*(gpad.w*rt.y + gpaf.y*rt.y + gpad.y*rt.w);
	result[ind].df.z = rt.y*rt.w*rt.z - 0.2f*rt2*(gpad.w*rt.z + gpaf.z*rt.y + gpae.y*rt.w);
	result[ind].df.w = rt.y*rt.w*rt.w - 0.2f*rt2*(gpad.w*rt.w + gpaf.w*rt.y + gpaf.y*rt.w);
	
	/**/
	result[ind].ec.x = rt.z*rt.x*rt.x - 0.2f*rt2*(gpae.x*rt.x + gpac.x*rt.z + gpac.z*rt.x);
	result[ind].ec.y = rt.z*rt.x*rt.y - 0.2f*rt2*(gpae.x*rt.y + gpac.y*rt.z + gpad.z*rt.x);
	result[ind].ec.z = rt.z*rt.x*rt.z - 0.2f*rt2*(gpae.x*rt.z + gpac.z*rt.z + gpae.z*rt.x);
	result[ind].ec.w = rt.z*rt.x*rt.w - 0.2f*rt2*(gpae.x*rt.w + gpac.w*rt.z + gpaf.z*rt.x);
	
	result[ind].ed.x = rt.z*rt.y*rt.x - 0.2f*rt2*(gpae.y*rt.x + gpad.x*rt.z + gpac.z*rt.y);
	result[ind].ed.y = rt.z*rt.y*rt.y - 0.2f*rt2*(gpae.y*rt.y + gpad.y*rt.z + gpad.z*rt.y);
	result[ind].ed.z = rt.z*rt.y*rt.z - 0.2f*rt2*(gpae.y*rt.z + gpad.z*rt.z + gpae.z*rt.y);
	result[ind].ed.w = rt.z*rt.y*rt.w - 0.2f*rt2*(gpae.y*rt.w + gpad.w*rt.z + gpaf.z*rt.y);
	
	result[ind].ee.x = rt.z*rt.z*rt.x - 0.2f*rt2*(gpae.z*rt.x + gpae.x*rt.z + gpac.z*rt.z);
	result[ind].ee.y = rt.z*rt.z*rt.y - 0.2f*rt2*(gpae.z*rt.y + gpae.y*rt.z + gpad.z*rt.z);
	result[ind].ee.z = rt.z*rt.z*rt.z - 0.2f*rt2*(gpae.z*rt.z + gpae.z*rt.z + gpae.z*rt.z);
	result[ind].ee.w = rt.z*rt.z*rt.w - 0.2f*rt2*(gpae.z*rt.w + gpae.w*rt.z + gpaf.z*rt.z);
	
	result[ind].ef.x = rt.z*rt.w*rt.x - 0.2f*rt2*(gpae.w*rt.x + gpaf.x*rt.z + gpac.z*rt.w);
	result[ind].ef.y = rt.z*rt.w*rt.y - 0.2f*rt2*(gpae.w*rt.y + gpaf.y*rt.z + gpad.z*rt.w);
	result[ind].ef.z = rt.z*rt.w*rt.z - 0.2f*rt2*(gpae.w*rt.z + gpaf.z*rt.z + gpae.z*rt.w);
	result[ind].ef.w = rt.z*rt.w*rt.w - 0.2f*rt2*(gpae.w*rt.w + gpaf.w*rt.z + gpaf.z*rt.w);
	
	/**/
	result[ind].fc.x = rt.w*rt.x*rt.x - 0.2f*rt2*(gpaf.x*rt.x + gpac.x*rt.w + gpac.w*rt.x);
	result[ind].fc.y = rt.w*rt.x*rt.y - 0.2f*rt2*(gpaf.x*rt.y + gpac.y*rt.w + gpad.w*rt.x);
	result[ind].fc.z = rt.w*rt.x*rt.z - 0.2f*rt2*(gpaf.x*rt.z + gpac.z*rt.w + gpae.w*rt.x);
	result[ind].fc.w = rt.w*rt.x*rt.w - 0.2f*rt2*(gpaf.x*rt.w + gpac.w*rt.w + gpaf.w*rt.x);
	
	result[ind].fd.x = rt.w*rt.y*rt.x - 0.2f*rt2*(gpaf.y*rt.x + gpad.x*rt.w + gpac.w*rt.y);
	result[ind].fd.y = rt.w*rt.y*rt.y - 0.2f*rt2*(gpaf.y*rt.y + gpad.y*rt.w + gpad.w*rt.y);
	result[ind].fd.z = rt.w*rt.y*rt.z - 0.2f*rt2*(gpaf.y*rt.z + gpad.z*rt.w + gpae.w*rt.y);
	result[ind].fd.w = rt.w*rt.y*rt.w - 0.2f*rt2*(gpaf.y*rt.w + gpad.w*rt.w + gpaf.w*rt.y);

	result[ind].fe.x = rt.w*rt.z*rt.x - 0.2f*rt2*(gpaf.z*rt.x + gpae.x*rt.w + gpac.w*rt.z);
	result[ind].fe.y = rt.w*rt.z*rt.y - 0.2f*rt2*(gpaf.z*rt.y + gpae.y*rt.w + gpad.w*rt.z);
	result[ind].fe.z = rt.w*rt.z*rt.z - 0.2f*rt2*(gpaf.z*rt.z + gpae.z*rt.w + gpae.w*rt.z);
	result[ind].fe.w = rt.w*rt.z*rt.w - 0.2f*rt2*(gpaf.z*rt.w + gpae.w*rt.w + gpaf.w*rt.z);
	
	result[ind].ff.x = rt.w*rt.w*rt.x - 0.2f*rt2*(gpaf.w*rt.x + gpaf.x*rt.w + gpac.w*rt.w);
	result[ind].ff.y = rt.w*rt.w*rt.y - 0.2f*rt2*(gpaf.w*rt.y + gpaf.y*rt.w + gpad.w*rt.w);
	result[ind].ff.z = rt.w*rt.w*rt.z - 0.2f*rt2*(gpaf.w*rt.z + gpaf.z*rt.w + gpae.w*rt.w);
	result[ind].ff.w = rt.w*rt.w*rt.w - 0.2f*rt2*(gpaf.w*rt.w + gpaf.w*rt.w + gpaf.w*rt.w);
}


__kernel void kernel3orbitaltensorconst(__global float4 * rtin, float4 pa, __global out float444 * result ){

	uint ind = get_global_id(0);

	float4 rt = rtin[ind];


	float pa2;
	float rt2;
	float4 gpac;
	float4 gpad;
	float4 gpae;
	float4 gpaf;
	
	pa2 = -pa.x*pa.x-pa.y*pa.y-pa.z*pa.z + pa.w*pa.w;
	rt2 = -rt.x*rt.x-rt.y*rt.y-rt.z*rt.z + rt.w*rt.w;

	
	gpac   =     -pa.x*pa/pa2;
	gpac.x = gpac.x -1.0f;
	
	gpad   =     -pa.y*pa/pa2;
	gpad.y = gpad.y -1.0f;
	
	gpae   =     -pa.z*pa/pa2;
	gpae.z = gpae.z -1.0f;
	
	gpaf   =     -pa.w*pa/pa2;
	gpaf.w = gpaf.w +1.0f;
	
	result[ind].cc.x = rt.x*rt.x*rt.x - 0.2f*rt2*(gpac.x*rt.x + gpac.x*rt.x + gpac.x*rt.x);
	result[ind].cc.y = rt.x*rt.x*rt.y - 0.2f*rt2*(gpac.x*rt.y + gpac.y*rt.x + gpad.x*rt.x);
	result[ind].cc.z = rt.x*rt.x*rt.z - 0.2f*rt2*(gpac.x*rt.z + gpac.z*rt.x + gpae.x*rt.x);
	result[ind].cc.w = rt.x*rt.x*rt.w - 0.2f*rt2*(gpac.x*rt.w + gpac.w*rt.x + gpaf.x*rt.x);
	
	result[ind].cd.x = rt.x*rt.y*rt.x - 0.2f*rt2*(gpac.y*rt.x + gpad.x*rt.x + gpac.x*rt.y);
	result[ind].cd.y = rt.x*rt.y*rt.y - 0.2f*rt2*(gpac.y*rt.y + gpad.y*rt.x + gpad.x*rt.y);
	result[ind].cd.z = rt.x*rt.y*rt.z - 0.2f*rt2*(gpac.y*rt.z + gpad.z*rt.x + gpae.x*rt.y);
	result[ind].cd.w = rt.x*rt.y*rt.w - 0.2f*rt2*(gpac.y*rt.w + gpad.w*rt.x + gpaf.x*rt.y);
	
	result[ind].ce.x = rt.x*rt.z*rt.x - 0.2f*rt2*(gpac.z*rt.x + gpae.x*rt.x + gpac.x*rt.z);
	result[ind].ce.y = rt.x*rt.z*rt.y - 0.2f*rt2*(gpac.z*rt.y + gpae.y*rt.x + gpad.x*rt.z);
	result[ind].ce.z = rt.x*rt.z*rt.z - 0.2f*rt2*(gpac.z*rt.z + gpae.z*rt.x + gpae.x*rt.z);
	result[ind].ce.w = rt.x*rt.z*rt.w - 0.2f*rt2*(gpac.z*rt.w + gpae.w*rt.x + gpaf.x*rt.z);
	
	result[ind].cf.x = rt.x*rt.w*rt.x - 0.2f*rt2*(gpac.w*rt.x + gpaf.x*rt.x + gpac.x*rt.w);
	result[ind].cf.y = rt.x*rt.w*rt.y - 0.2f*rt2*(gpac.w*rt.y + gpaf.y*rt.x + gpad.x*rt.w);
	result[ind].cf.z = rt.x*rt.w*rt.z - 0.2f*rt2*(gpac.w*rt.z + gpaf.z*rt.x + gpae.x*rt.w);
	result[ind].cf.w = rt.x*rt.w*rt.w - 0.2f*rt2*(gpac.w*rt.w + gpaf.w*rt.x + gpaf.x*rt.w);
	
	/**/
	result[ind].dc.x = rt.y*rt.x*rt.x - 0.2f*rt2*(gpad.x*rt.x + gpac.x*rt.y + gpac.y*rt.x);
	result[ind].dc.y = rt.y*rt.x*rt.y - 0.2f*rt2*(gpad.x*rt.y + gpac.y*rt.y + gpad.y*rt.x);
	result[ind].dc.z = rt.y*rt.x*rt.z - 0.2f*rt2*(gpad.x*rt.z + gpac.z*rt.y + gpae.y*rt.x);
	result[ind].dc.w = rt.y*rt.x*rt.w - 0.2f*rt2*(gpad.x*rt.w + gpac.w*rt.y + gpaf.y*rt.x);
	
	result[ind].dd.x = rt.y*rt.y*rt.x - 0.2f*rt2*(gpad.y*rt.x + gpad.x*rt.y + gpac.y*rt.y);
	result[ind].dd.y = rt.y*rt.y*rt.y - 0.2f*rt2*(gpad.y*rt.y + gpad.y*rt.y + gpad.y*rt.y);
	result[ind].dd.z = rt.y*rt.y*rt.z - 0.2f*rt2*(gpad.y*rt.z + gpad.z*rt.y + gpae.y*rt.y);
	result[ind].dd.w = rt.y*rt.y*rt.w - 0.2f*rt2*(gpad.y*rt.w + gpad.w*rt.y + gpaf.y*rt.y);
	
	result[ind].de.x = rt.y*rt.z*rt.x - 0.2f*rt2*(gpad.z*rt.x + gpae.x*rt.y + gpac.y*rt.z);
	result[ind].de.y = rt.y*rt.z*rt.y - 0.2f*rt2*(gpad.z*rt.y + gpae.y*rt.y + gpad.y*rt.z);
	result[ind].de.z = rt.y*rt.z*rt.z - 0.2f*rt2*(gpad.z*rt.z + gpae.z*rt.y + gpae.y*rt.z);
	result[ind].de.w = rt.y*rt.z*rt.w - 0.2f*rt2*(gpad.z*rt.w + gpae.w*rt.y + gpaf.y*rt.z);
	
	result[ind].df.x = rt.y*rt.w*rt.x - 0.2f*rt2*(gpad.w*rt.x + gpaf.x*rt.y + gpac.y*rt.w);
	result[ind].df.y = rt.y*rt.w*rt.y - 0.2f*rt2*(gpad.w*rt.y + gpaf.y*rt.y + gpad.y*rt.w);
	result[ind].df.z = rt.y*rt.w*rt.z - 0.2f*rt2*(gpad.w*rt.z + gpaf.z*rt.y + gpae.y*rt.w);
	result[ind].df.w = rt.y*rt.w*rt.w - 0.2f*rt2*(gpad.w*rt.w + gpaf.w*rt.y + gpaf.y*rt.w);
	
	/**/
	result[ind].ec.x = rt.z*rt.x*rt.x - 0.2f*rt2*(gpae.x*rt.x + gpac.x*rt.z + gpac.z*rt.x);
	result[ind].ec.y = rt.z*rt.x*rt.y - 0.2f*rt2*(gpae.x*rt.y + gpac.y*rt.z + gpad.z*rt.x);
	result[ind].ec.z = rt.z*rt.x*rt.z - 0.2f*rt2*(gpae.x*rt.z + gpac.z*rt.z + gpae.z*rt.x);
	result[ind].ec.w = rt.z*rt.x*rt.w - 0.2f*rt2*(gpae.x*rt.w + gpac.w*rt.z + gpaf.z*rt.x);
	
	result[ind].ed.x = rt.z*rt.y*rt.x - 0.2f*rt2*(gpae.y*rt.x + gpad.x*rt.z + gpac.z*rt.y);
	result[ind].ed.y = rt.z*rt.y*rt.y - 0.2f*rt2*(gpae.y*rt.y + gpad.y*rt.z + gpad.z*rt.y);
	result[ind].ed.z = rt.z*rt.y*rt.z - 0.2f*rt2*(gpae.y*rt.z + gpad.z*rt.z + gpae.z*rt.y);
	result[ind].ed.w = rt.z*rt.y*rt.w - 0.2f*rt2*(gpae.y*rt.w + gpad.w*rt.z + gpaf.z*rt.y);
	
	result[ind].ee.x = rt.z*rt.z*rt.x - 0.2f*rt2*(gpae.z*rt.x + gpae.x*rt.z + gpac.z*rt.z);
	result[ind].ee.y = rt.z*rt.z*rt.y - 0.2f*rt2*(gpae.z*rt.y + gpae.y*rt.z + gpad.z*rt.z);
	result[ind].ee.z = rt.z*rt.z*rt.z - 0.2f*rt2*(gpae.z*rt.z + gpae.z*rt.z + gpae.z*rt.z);
	result[ind].ee.w = rt.z*rt.z*rt.w - 0.2f*rt2*(gpae.z*rt.w + gpae.w*rt.z + gpaf.z*rt.z);
	
	result[ind].ef.x = rt.z*rt.w*rt.x - 0.2f*rt2*(gpae.w*rt.x + gpaf.x*rt.z + gpac.z*rt.w);
	result[ind].ef.y = rt.z*rt.w*rt.y - 0.2f*rt2*(gpae.w*rt.y + gpaf.y*rt.z + gpad.z*rt.w);
	result[ind].ef.z = rt.z*rt.w*rt.z - 0.2f*rt2*(gpae.w*rt.z + gpaf.z*rt.z + gpae.z*rt.w);
	result[ind].ef.w = rt.z*rt.w*rt.w - 0.2f*rt2*(gpae.w*rt.w + gpaf.w*rt.z + gpaf.z*rt.w);
	
	/**/
	result[ind].fc.x = rt.w*rt.x*rt.x - 0.2f*rt2*(gpaf.x*rt.x + gpac.x*rt.w + gpac.w*rt.x);
	result[ind].fc.y = rt.w*rt.x*rt.y - 0.2f*rt2*(gpaf.x*rt.y + gpac.y*rt.w + gpad.w*rt.x);
	result[ind].fc.z = rt.w*rt.x*rt.z - 0.2f*rt2*(gpaf.x*rt.z + gpac.z*rt.w + gpae.w*rt.x);
	result[ind].fc.w = rt.w*rt.x*rt.w - 0.2f*rt2*(gpaf.x*rt.w + gpac.w*rt.w + gpaf.w*rt.x);
	
	result[ind].fd.x = rt.w*rt.y*rt.x - 0.2f*rt2*(gpaf.y*rt.x + gpad.x*rt.w + gpac.w*rt.y);
	result[ind].fd.y = rt.w*rt.y*rt.y - 0.2f*rt2*(gpaf.y*rt.y + gpad.y*rt.w + gpad.w*rt.y);
	result[ind].fd.z = rt.w*rt.y*rt.z - 0.2f*rt2*(gpaf.y*rt.z + gpad.z*rt.w + gpae.w*rt.y);
	result[ind].fd.w = rt.w*rt.y*rt.w - 0.2f*rt2*(gpaf.y*rt.w + gpad.w*rt.w + gpaf.w*rt.y);

	result[ind].fe.x = rt.w*rt.z*rt.x - 0.2f*rt2*(gpaf.z*rt.x + gpae.x*rt.w + gpac.w*rt.z);
	result[ind].fe.y = rt.w*rt.z*rt.y - 0.2f*rt2*(gpaf.z*rt.y + gpae.y*rt.w + gpad.w*rt.z);
	result[ind].fe.z = rt.w*rt.z*rt.z - 0.2f*rt2*(gpaf.z*rt.z + gpae.z*rt.w + gpae.w*rt.z);
	result[ind].fe.w = rt.w*rt.z*rt.w - 0.2f*rt2*(gpaf.z*rt.w + gpae.w*rt.w + gpaf.w*rt.z);
	
	result[ind].ff.x = rt.w*rt.w*rt.x - 0.2f*rt2*(gpaf.w*rt.x + gpaf.x*rt.w + gpac.w*rt.w);
	result[ind].ff.y = rt.w*rt.w*rt.y - 0.2f*rt2*(gpaf.w*rt.y + gpaf.y*rt.w + gpad.w*rt.w);
	result[ind].ff.z = rt.w*rt.w*rt.z - 0.2f*rt2*(gpaf.w*rt.z + gpaf.z*rt.w + gpae.w*rt.w);
	result[ind].ff.w = rt.w*rt.w*rt.w - 0.2f*rt2*(gpaf.w*rt.w + gpaf.w*rt.w + gpaf.w*rt.w);
}



__kernel void kernelfilllookup(__global float2 * input, uint offset, uint ijindex, uint lookupsize, __global out float4 * cx, __global out float4 * cy)
{
	 uint i = get_global_id(0);
	 uint outindex = offset+i*lookupsize + ijindex;

	 //cx[i].x = i;
	 //cx[i].y = offset;
	 //cx[i].z = lookupsize;
	 //cx[i].w = ijindex;

	 cx[outindex].x = input[i*4].x;
	 cx[outindex].y = input[i*4+1].x;
	 cx[outindex].z = input[i*4+2].x;
	 cx[outindex].w = input[i*4+3].x;

	 cy[outindex].x = input[i*4].y;
	 cy[outindex].y = input[i*4+1].y;
	 cy[outindex].z = input[i*4+2].y;
	 cy[outindex].w = input[i*4+3].y;

}

