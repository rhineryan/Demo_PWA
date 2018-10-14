__kernel void
testmul2(__global float *vec, __global float *scal, __global out float * result){
	
	uint pos = get_global_id(0);
	
	result[pos] = 7;//vec[pos]*scal[pos];

}

// and a very nice kernel
__kernel void
testmul(__global out float * result){
	
	uint pos = get_global_id(0);
	result[pos] = pos;
}
