/* Summing_cpu.h  -- header for interface functions to the kernels
 defined in Summing.cl, the corresponding binaries are in binfiles/Summing_cpu.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#ifndef HHSumming_CPUHH
#define HHSumming_CPUHH


#include"Stream.h"
#include"DeviceInterface.h"


namespace Summing_CPU{

	 int prepare_kernels(const DeviceInterface * dev);

	 extern cl::Kernel * k_int_sum_16;
	 extern cl::Kernel * k_int_sum_N;
	 extern cl::Kernel * k_int_sum2d_16;
	 extern cl::Kernel * k_int_sum2d_N;
	 extern cl::Kernel * k_int_sum2d_16_weighted;
	 extern cl::Kernel * k_int_sum2d_N_weighted;
	 extern cl::Kernel * k_float_sum_16;
	 extern cl::Kernel * k_float_sum_N;
	 extern cl::Kernel * k_float_sum2d_16;
	 extern cl::Kernel * k_float_sum2d_N;
	 extern cl::Kernel * k_float_sum2d_16_weighted;
	 extern cl::Kernel * k_float_sum2d_N_weighted;
	 extern cl::Kernel * k_double_sum_16;
	 extern cl::Kernel * k_double_sum_N;
	 extern cl::Kernel * k_double_sum2d_16;
	 extern cl::Kernel * k_double_sum2d_N;
	 extern cl::Kernel * k_double_sum2d_16_weighted;
	 extern cl::Kernel * k_double_sum2d_N_weighted;
	 extern cl::Kernel * k_double2_sum_16;
	 extern cl::Kernel * k_double2_sum_N;
	 extern cl::Kernel * k_double2_sumcomponents_16;
	 extern cl::Kernel * k_double2_sumcomponents_N;
	 extern cl::Kernel * k_double2_sumcomponents_weighted_16;
	 extern cl::Kernel * k_double2_sumcomponents_weighted_N;
	 extern cl::Kernel * k_double2_sum2d_16;
	 extern cl::Kernel * k_double2_sum2d_N;
	 extern cl::Kernel * k_double2_sum2d_16_weighted;
	 extern cl::Kernel * k_double2_sum2d_N_weighted;
	 extern cl::Kernel * k_float2_sum_16;
	 extern cl::Kernel * k_float2_sum_N;
	 extern cl::Kernel * k_float2_sumcomponents_16;
	 extern cl::Kernel * k_float2_sumcomponents_N;
	 extern cl::Kernel * k_float2_sumcomponents_weighted_16;
	 extern cl::Kernel * k_float2_sumcomponents_weighted_N;
	 extern cl::Kernel * k_float2_sum2d_16;
	 extern cl::Kernel * k_float2_sum2d_N;
	 extern cl::Kernel * k_float2_sum2d_16_weighted;
	 extern cl::Kernel * k_float2_sum2d_N_weighted;
	 extern cl::Kernel * k_float4_sum_16;
	 extern cl::Kernel * k_float4_sum_N;
	 extern cl::Kernel * k_float4_sumcomponents_16;
	 extern cl::Kernel * k_float4_sumcomponents_N;
	 extern cl::Kernel * k_float4_sumcomponents_weighted_16;
	 extern cl::Kernel * k_float4_sumcomponents_weighted_N;
	 extern cl::Kernel * k_float4_sum2d_16;
	 extern cl::Kernel * k_float4_sum2d_N;
	 extern cl::Kernel * k_float4_sum2d_16_weighted;
	 extern cl::Kernel * k_float4_sum2d_N_weighted;
	 extern cl::Kernel * k_float44_sum_16;
	 extern cl::Kernel * k_float44_sum_N;
	 extern cl::Kernel * k_float44_sum2d_16;
	 extern cl::Kernel * k_float44_sum2d_N;
	 extern cl::Kernel * k_float44_sum2d_16_weighted;
	 extern cl::Kernel * k_float44_sum2d_N_weighted;
	 extern cl::Kernel * k_float444_sum_16;
	 extern cl::Kernel * k_float444_sum_N;
	 extern cl::Kernel * k_float444_sum2d_16;
	 extern cl::Kernel * k_float444_sum2d_N;
	 extern cl::Kernel * k_float444_sum2d_16_weighted;
	 extern cl::Kernel * k_float444_sum2d_N_weighted;
	 int int_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<int> * in, Stream<double> * result);

	 int int_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<int> * in, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int int_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<int> * in, uint d1, Stream<double> * result);

	 int int_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<int> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int int_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<int> * in, uint d1, Stream<double> * result);

	 int int_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<int> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int float_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * in, Stream<double> * result);

	 int float_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * in, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int float_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * in, uint d1, Stream<double> * result);

	 int float_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int float_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float> * in, uint d1, Stream<double> * result);

	 int float_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int double_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<double> * in, Stream<double> * result);

	 int double_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<double> * in, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int double_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<double> * in, uint d1, Stream<double> * result);

	 int double_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<double> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int double_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<double> * in, uint d1, Stream<double> * result);

	 int double_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<double> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int double2_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, Stream<double> * result);

	 int double2_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int double2_sumcomponents_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, Stream<double> * result_0, Stream<double> * result_1);

	 int double2_sumcomponents_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, uint offset, uint resultoffset, uint n, Stream<double> * result_0, Stream<double> * result_1);

	 int double2_sumcomponents_weighted_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, Stream<float> * weights, Stream<double> * result_0, Stream<double> * result_1);

	 int double2_sumcomponents_weighted_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, Stream<float> * weights, uint offset, uint resultoffset, uint n, Stream<double> * result_0, Stream<double> * result_1);

	 int double2_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, uint d1, Stream<double> * result);

	 int double2_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<double2> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int double2_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<double2> * in, uint d1, Stream<double> * result);

	 int double2_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<double2> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int float2_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, Stream<double> * result);

	 int float2_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int float2_sumcomponents_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, Stream<double> * result_0, Stream<double> * result_1);

	 int float2_sumcomponents_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, uint offset, uint resultoffset, uint n, Stream<double> * result_0, Stream<double> * result_1);

	 int float2_sumcomponents_weighted_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, Stream<float> * weights, Stream<double> * result_0, Stream<double> * result_1);

	 int float2_sumcomponents_weighted_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, Stream<float> * weights, uint offset, uint resultoffset, uint n, Stream<double> * result_0, Stream<double> * result_1);

	 int float2_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, uint d1, Stream<double> * result);

	 int float2_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int float2_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float2> * in, uint d1, Stream<double> * result);

	 int float2_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float2> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int float4_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, Stream<double> * result);

	 int float4_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int float4_sumcomponents_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, Stream<double> * result_0, Stream<double> * result_1, Stream<double> * result_2, Stream<double> * result_3);

	 int float4_sumcomponents_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, uint offset, uint resultoffset, uint n, Stream<double> * result_0, Stream<double> * result_1, Stream<double> * result_2, Stream<double> * result_3);

	 int float4_sumcomponents_weighted_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, Stream<float> * weights, Stream<double> * result_0, Stream<double> * result_1, Stream<double> * result_2, Stream<double> * result_3);

	 int float4_sumcomponents_weighted_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, Stream<float> * weights, uint offset, uint resultoffset, uint n, Stream<double> * result_0, Stream<double> * result_1, Stream<double> * result_2, Stream<double> * result_3);

	 int float4_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, uint d1, Stream<double> * result);

	 int float4_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int float4_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float4> * in, uint d1, Stream<double> * result);

	 int float4_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float4> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int float44_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float44> * in, Stream<double> * result);

	 int float44_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float44> * in, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int float44_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float44> * in, uint d1, Stream<double> * result);

	 int float44_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float44> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int float44_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float44> * in, uint d1, Stream<double> * result);

	 int float44_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float44> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int float444_sum_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float444> * in, Stream<double> * result);

	 int float444_sum_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float444> * in, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int float444_sum2d_16(const cl::NDRange & range, const DeviceInterface * dev, Stream<float444> * in, uint d1, Stream<double> * result);

	 int float444_sum2d_N(const cl::NDRange & range, const DeviceInterface * dev, Stream<float444> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

	 int float444_sum2d_16_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float444> * in, uint d1, Stream<double> * result);

	 int float444_sum2d_N_weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float444> * in, uint d1, uint offset, uint resultoffset, uint n, Stream<double> * result);

}
#endif
