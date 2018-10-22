/* Tensors.h  -- header for interface functions to the kernels
 defined in /scratchfs/bes/xiongxa/Demo_PWA_GPUPWA/GPUPWA/GPUPWA/Tensors.cl, the corresponding binaries are in binfiles/Tensors.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#ifndef HHTensors_GPUHH
#define HHTensors_GPUHH


#include"Stream.h"
#include"DeviceInterface.h"


namespace Tensors_GPU{

	 int prepare_kernels(const DeviceInterface * dev);

	 extern cl::Kernel * k_kerneltensorcopy_2;
	 extern cl::Kernel * k_kerneltensorassign_c;
	 extern cl::Kernel * k_kerneltensorassign_d;
	 extern cl::Kernel * k_kerneltensorassign_e;
	 extern cl::Kernel * k_kerneltensorassign_f;
	 extern cl::Kernel * k_kerneltensorassign_0;
	 extern cl::Kernel * k_kerneltensorassign_1;
	 extern cl::Kernel * k_kerneltensorassign_2;
	 extern cl::Kernel * k_kerneltensorassign_3;
	 extern cl::Kernel * k_kernelgetfloat_1;
	 extern cl::Kernel * k_kernelgetfloat_2;
	 extern cl::Kernel * k_kerneltensormake_2;
	 extern cl::Kernel * k_kerneltensormake_2_1;
	 extern cl::Kernel * k_kerneltensormake_3;
	 extern cl::Kernel * k_kernelgetvector_2;
	 extern cl::Kernel * k_kernelgetvector_3;
	 extern cl::Kernel * k_kernelgetfloat44_3;
	 extern cl::Kernel * k_kerneltensoradd_0_0;
	 extern cl::Kernel * k_kerneltensoradd_0_16;
	 extern cl::Kernel * k_kerneltensoradd_4_16;
	 extern cl::Kernel * k_kerneltensoradd_0_4;
	 extern cl::Kernel * k_kerneltensoradd_0_f;
	 extern cl::Kernel * k_kerneltensoradd_1_1;
	 extern cl::Kernel * k_kerneltensoradd_1_f;
	 extern cl::Kernel * k_kerneltensoradd_2_2;
	 extern cl::Kernel * k_kerneltensoradd_2_f44;
	 extern cl::Kernel * k_kerneltensoradd_3_3;
	 extern cl::Kernel * k_kerneltensoradd_3_f;
	 extern cl::Kernel * k_kerneltensorsub_0_0;
	 extern cl::Kernel * k_kerneltensorsub_0_f;
	 extern cl::Kernel * k_kerneltensorsub_f_0;
	 extern cl::Kernel * k_kerneltensorsub_1_1;
	 extern cl::Kernel * k_kerneltensorsub_1_f;
	 extern cl::Kernel * k_kerneltensorsub_f_1;
	 extern cl::Kernel * k_kerneltensorsub_2_2;
	 extern cl::Kernel * k_kerneltensorsub_2_f;
	 extern cl::Kernel * k_kerneltensorsub_f_2;
	 extern cl::Kernel * k_kerneltensorsub_3_3;
	 extern cl::Kernel * k_kerneltensorsub_3_f;
	 extern cl::Kernel * k_kerneltensorsub_f_3;
	 extern cl::Kernel * k_kerneltensormult_0_0;
	 extern cl::Kernel * k_kerneltensormult_0_f;
	 extern cl::Kernel * k_kerneltensormult_0_1;
	 extern cl::Kernel * k_kerneltensormult_0_f4;
	 extern cl::Kernel * k_kerneltensormult_f_1;
	 extern cl::Kernel * k_kerneltensormult_0_2;
	 extern cl::Kernel * k_kerneltensormult_0_f44;
	 extern cl::Kernel * k_kerneltensormult_0i_2;
	 extern cl::Kernel * k_kerneltensormult_0i_f44;
	 extern cl::Kernel * k_kerneltensormult_f_2;
	 extern cl::Kernel * k_kerneltensormult_fi_2;
	 extern cl::Kernel * k_kerneltensormult_0_3;
	 extern cl::Kernel * k_kerneltensormult_f_3;
	 extern cl::Kernel * k_kerneltensormult_0_f444;
	 extern cl::Kernel * k_kerneltensordiv_0_0;
	 extern cl::Kernel * k_kerneltensordiv_f_0;
	 extern cl::Kernel * k_kerneltensordiv_1_0;
	 extern cl::Kernel * k_kerneltensordiv_f4_0;
	 extern cl::Kernel * k_kerneltensordiv_2_0;
	 extern cl::Kernel * k_kerneltensordiv_2_f;
	 extern cl::Kernel * k_kerneltensordiv_f44_0;
	 extern cl::Kernel * k_kerneltensordiv_3_0;
	 extern cl::Kernel * k_kerneltensordiv_3_f;
	 extern cl::Kernel * k_kerneltensordiv_f444_0;
	 extern cl::Kernel * k_kerneltensorouter_1_1;
	 extern cl::Kernel * k_kerneltensorouter_1_f4;
	 extern cl::Kernel * k_kerneltensorouter_f4_1;
	 extern cl::Kernel * k_kerneltensorouter_2_1;
	 extern cl::Kernel * k_kerneltensorouter_2_f4;
	 extern cl::Kernel * k_kerneltensorouter_f44_1;
	 extern cl::Kernel * k_kerneltensorouter_1_2;
	 extern cl::Kernel * k_kerneltensorouter_f4_2;
	 extern cl::Kernel * k_kerneltensorouter_1_f44;
	 extern cl::Kernel * k_kerneltensorneg_0;
	 extern cl::Kernel * k_kerneltensorneg_1;
	 extern cl::Kernel * k_kerneltensorneg_2;
	 extern cl::Kernel * k_kerneltensorneg_3;
	 extern cl::Kernel * k_kerneltensorsqrt_0;
	 extern cl::Kernel * k_kerneltensorsin_0;
	 extern cl::Kernel * k_kerneltensorcos_0;
	 extern cl::Kernel * k_kerneltensortan_0;
	 extern cl::Kernel * k_kerneltensorexp_0;
	 extern cl::Kernel * k_kerneltensortrans_2;
	 extern cl::Kernel * k_kerneltensortrans_3_213;
	 extern cl::Kernel * k_kerneltensortrans_3_132;
	 extern cl::Kernel * k_kernelmoveindex_1;
	 extern cl::Kernel * k_kernelmovelastindex_2;
	 extern cl::Kernel * k_kernelmovefirstindex_2;
	 extern cl::Kernel * k_kernelmoveindices_2;
	 extern cl::Kernel * k_kernelmoveindices_3;
	 extern cl::Kernel * k_kernelmovelastindex_3;
	 extern cl::Kernel * k_kernelmovemiddleindex_3;
	 extern cl::Kernel * k_kernelmovefirstindex_3;
	 extern cl::Kernel * k_kernellorentzboost;
	 extern cl::Kernel * k_kernellorentzrotation;
	 extern cl::Kernel * k_kerneltensorphi_1;
	 extern cl::Kernel * k_kerneltensorcostheta_1;
	 extern cl::Kernel * k_kerneltensorcontract_1_1;
	 extern cl::Kernel * k_kerneltensorcontract_1_f;
	 extern cl::Kernel * k_kerneltensorcontract_2_1;
	 extern cl::Kernel * k_kerneltensorcontract_f44_1;
	 extern cl::Kernel * k_kerneltensorcontract_2_f4;
	 extern cl::Kernel * k_kerneltensorcontract_2_2;
	 extern cl::Kernel * k_kerneltensorcontract_2_f44;
	 extern cl::Kernel * k_kerneltensorcontract2_2_2;
	 extern cl::Kernel * k_kerneltensorcontract2_2_f44;
	 extern cl::Kernel * k_kerneltensorcontract2_f44_2;
	 extern cl::Kernel * k_kerneltensorcontract_3_3;
	 extern cl::Kernel * k_kerneltensorcontract_3_f444;
	 extern cl::Kernel * k_kerneltensorcontract_3_1;
	 extern cl::Kernel * k_kerneltensorcontract_f444_1;
	 extern cl::Kernel * k_kerneltensorcontract_3_f4;
	 extern cl::Kernel * k_kerneltensorcontract_3_2;
	 extern cl::Kernel * k_kerneltensorcontract_3_f44;
	 extern cl::Kernel * k_kerneltensorcontract_2_3_sign;
	 extern cl::Kernel * k_kerneltensorcontract_2_3;
	 extern cl::Kernel * k_kerneltensorcontract_2_f444;
	 extern cl::Kernel * k_kerneltensorcontract_f44_3;
	 extern cl::Kernel * k_kerneltensorcontract_f444_2;
	 extern cl::Kernel * k_kerneltensorcontract2_3_3;
	 int kerneltensorcopy_2(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output);

	 int kerneltensorassign_c(const DeviceInterface * dev, Stream<float44> * p1, Stream<float44> * p2, Stream<float44> * p3, Stream<float44> * p4, Stream<float44> * output);

	 int kerneltensorassign_d(const DeviceInterface * dev, Stream<float44> * p1, Stream<float44> * p2, Stream<float44> * p3, Stream<float44> * p4, Stream<float44> * output);

	 int kerneltensorassign_e(const DeviceInterface * dev, Stream<float44> * p1, Stream<float44> * p2, Stream<float44> * p3, Stream<float44> * p4, Stream<float44> * output);

	 int kerneltensorassign_f(const DeviceInterface * dev, Stream<float44> * p1, Stream<float44> * p2, Stream<float44> * p3, Stream<float44> * p4, Stream<float44> * output);

	 int kerneltensorassign_0(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output);

	 int kerneltensorassign_1(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output);

	 int kerneltensorassign_2(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output);

	 int kerneltensorassign_3(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output);

	 int kernelgetfloat_1(const DeviceInterface * dev, Stream<float4> * input, float i, Stream<float> * output);

	 int kernelgetfloat_2(const DeviceInterface * dev, Stream<float44> * input, uint i, uint j, Stream<float> * output);

	 int kerneltensormake_2(const DeviceInterface * dev, Stream<float> * in1, Stream<float> * in2, Stream<float> * in3, Stream<float> * in4, Stream<float> * in5, Stream<float> * in6, Stream<float> * in7, Stream<float> * in8, Stream<float> * in9, Stream<float> * in10, Stream<float> * in11, Stream<float> * in12, Stream<float> * in13, Stream<float> * in14, Stream<float> * in15, Stream<float> * in16, Stream<float44> * output);

	 int kerneltensormake_2_1(const DeviceInterface * dev, Stream<float4> * in1, Stream<float4> * in2, Stream<float4> * in3, Stream<float4> * in4, Stream<float44> * output);

	 int kerneltensormake_3(const DeviceInterface * dev, Stream<float4> * in1, Stream<float4> * in2, Stream<float4> * in3, Stream<float4> * in4, Stream<float4> * in5, Stream<float4> * in6, Stream<float4> * in7, Stream<float4> * in8, Stream<float4> * in9, Stream<float4> * in10, Stream<float4> * in11, Stream<float4> * in12, Stream<float4> * in13, Stream<float4> * in14, Stream<float4> * in15, Stream<float4> * in16, Stream<float444> * output);

	 int kernelgetvector_2(const DeviceInterface * dev, Stream<float44> * input, uint i, Stream<float4> * output);

	 int kernelgetvector_3(const DeviceInterface * dev, Stream<float444> * input, uint i, uint j, Stream<float4> * output);

	 int kernelgetfloat44_3(const DeviceInterface * dev, Stream<float444> * input, uint i, Stream<float44> * output);

	 int kerneltensoradd_0_0(const DeviceInterface * dev, Stream<float> * input1, Stream<float> * input2, Stream<float> * output);

	 int kerneltensoradd_0_16(const DeviceInterface * dev, Stream<float> * p1, Stream<float> * p2, Stream<float> * p3, Stream<float> * p4, Stream<float> * p5, Stream<float> * p6, Stream<float> * p7, Stream<float> * p8, Stream<float> * p9, Stream<float> * p10, Stream<float> * p11, Stream<float> * p12, Stream<float> * p13, Stream<float> * p14, Stream<float> * p15, Stream<float> * p16, Stream<float> * output);

	 int kerneltensoradd_4_16(const DeviceInterface * dev, Stream<float4> * p00, Stream<float4> * p01, Stream<float4> * p02, Stream<float4> * p03, Stream<float4> * p10, Stream<float4> * p11, Stream<float4> * p12, Stream<float4> * p13, Stream<float4> * p20, Stream<float4> * p21, Stream<float4> * p22, Stream<float4> * p23, Stream<float4> * p30, Stream<float4> * p31, Stream<float4> * p32, Stream<float4> * p33, Stream<float4> * output);

	 int kerneltensoradd_0_4(const DeviceInterface * dev, Stream<float> * p1, Stream<float> * p2, Stream<float> * p3, Stream<float> * p4, Stream<float> * output);

	 int kerneltensoradd_0_f(const DeviceInterface * dev, Stream<float> * input1, float input2, Stream<float> * output);

	 int kerneltensoradd_1_1(const DeviceInterface * dev, Stream<float4> * input1, Stream<float4> * input2, Stream<float4> * output);

	 int kerneltensoradd_1_f(const DeviceInterface * dev, Stream<float4> * input1, float4 input2, Stream<float4> * output);

	 int kerneltensoradd_2_2(const DeviceInterface * dev, Stream<float44> * input1, Stream<float44> * input2, Stream<float44> * output);

	 int kerneltensoradd_2_f44(const DeviceInterface * dev, Stream<float44> * input1, float44 input2, Stream<float44> * output);

	 int kerneltensoradd_3_3(const DeviceInterface * dev, Stream<float444> * input1, Stream<float444> * input2, Stream<float444> * output);

	 int kerneltensoradd_3_f(const DeviceInterface * dev, Stream<float444> * input1, float444 input2, Stream<float444> * output);

	 int kerneltensorsub_0_0(const DeviceInterface * dev, Stream<float> * input1, Stream<float> * input2, Stream<float> * output);

	 int kerneltensorsub_0_f(const DeviceInterface * dev, Stream<float> * input1, float input2, Stream<float> * output);

	 int kerneltensorsub_f_0(const DeviceInterface * dev, float input1, Stream<float> * input2, Stream<float> * output);

	 int kerneltensorsub_1_1(const DeviceInterface * dev, Stream<float4> * input1, Stream<float4> * input2, Stream<float4> * output);

	 int kerneltensorsub_1_f(const DeviceInterface * dev, Stream<float4> * input1, float4 input2, Stream<float4> * output);

	 int kerneltensorsub_f_1(const DeviceInterface * dev, float4 input1, Stream<float4> * input2, Stream<float4> * output);

	 int kerneltensorsub_2_2(const DeviceInterface * dev, Stream<float44> * input1, Stream<float44> * input2, Stream<float44> * output);

	 int kerneltensorsub_2_f(const DeviceInterface * dev, Stream<float44> * input1, float44 input2, Stream<float44> * output);

	 int kerneltensorsub_f_2(const DeviceInterface * dev, float44 input1, Stream<float44> * input2, Stream<float44> * output);

	 int kerneltensorsub_3_3(const DeviceInterface * dev, Stream<float444> * input1, Stream<float444> * input2, Stream<float444> * output);

	 int kerneltensorsub_3_f(const DeviceInterface * dev, Stream<float444> * input1, float444 input2, Stream<float444> * output);

	 int kerneltensorsub_f_3(const DeviceInterface * dev, float444 input1, Stream<float444> * input2, Stream<float444> * output);

	 int kerneltensormult_0_0(const DeviceInterface * dev, Stream<float> * input1, Stream<float> * input2, Stream<float> * output);

	 int kerneltensormult_0_f(const DeviceInterface * dev, Stream<float> * input1, float input2, Stream<float> * output);

	 int kerneltensormult_0_1(const DeviceInterface * dev, Stream<float> * input1, Stream<float4> * input2, Stream<float4> * output);

	 int kerneltensormult_0_f4(const DeviceInterface * dev, Stream<float> * input1, float4 input2, Stream<float4> * output);

	 int kerneltensormult_f_1(const DeviceInterface * dev, float input1, Stream<float4> * input2, Stream<float4> * output);

	 int kerneltensormult_0_2(const DeviceInterface * dev, Stream<float> * input1, Stream<float44> * input2, Stream<float44> * output);

	 int kerneltensormult_0_f44(const DeviceInterface * dev, Stream<float> * input1, float44 input2, Stream<float44> * output);

	 int kerneltensormult_0i_2(const DeviceInterface * dev, Stream<float44> * inx, int i, int j, Stream<float44> * input2, Stream<float44> * output);

	 int kerneltensormult_0i_f44(const DeviceInterface * dev, Stream<float44> * inx, int i, int j, float44 input2, Stream<float44> * output);

	 int kerneltensormult_f_2(const DeviceInterface * dev, float input1, Stream<float44> * input2, Stream<float44> * output);

	 int kerneltensormult_fi_2(const DeviceInterface * dev, float44 inx, int i, int j, Stream<float44> * input2, Stream<float44> * output);

	 int kerneltensormult_0_3(const DeviceInterface * dev, Stream<float> * input1, Stream<float444> * input2, Stream<float444> * output);

	 int kerneltensormult_f_3(const DeviceInterface * dev, float input1, Stream<float444> * input2, Stream<float444> * output);

	 int kerneltensormult_0_f444(const DeviceInterface * dev, Stream<float> * input1, float444 input2, Stream<float444> * output);

	 int kerneltensordiv_0_0(const DeviceInterface * dev, Stream<float> * input1, Stream<float> * input2, Stream<float> * output);

	 int kerneltensordiv_f_0(const DeviceInterface * dev, float input1, Stream<float> * input2, Stream<float> * output);

	 int kerneltensordiv_1_0(const DeviceInterface * dev, Stream<float4> * input1, Stream<float> * input2, Stream<float4> * output);

	 int kerneltensordiv_f4_0(const DeviceInterface * dev, float4 input1, Stream<float> * input2, Stream<float4> * output);

	 int kerneltensordiv_2_0(const DeviceInterface * dev, Stream<float44> * input1, Stream<float> * input2, Stream<float44> * output);

	 int kerneltensordiv_2_f(const DeviceInterface * dev, Stream<float44> * input1, float input2, Stream<float44> * output);

	 int kerneltensordiv_f44_0(const DeviceInterface * dev, float44 input1, Stream<float> * input2, Stream<float44> * output);

	 int kerneltensordiv_3_0(const DeviceInterface * dev, Stream<float444> * input1, Stream<float> * input2, Stream<float444> * output);

	 int kerneltensordiv_3_f(const DeviceInterface * dev, Stream<float444> * input1, float input2, Stream<float444> * output);

	 int kerneltensordiv_f444_0(const DeviceInterface * dev, float444 input1, Stream<float> * input2, Stream<float444> * output);

	 int kerneltensorouter_1_1(const DeviceInterface * dev, Stream<float4> * input1, Stream<float4> * input2, Stream<float44> * output);

	 int kerneltensorouter_1_f4(const DeviceInterface * dev, Stream<float4> * input1, float4 input2, Stream<float44> * output);

	 int kerneltensorouter_f4_1(const DeviceInterface * dev, float4 input1, Stream<float4> * input2, Stream<float44> * output);

	 int kerneltensorouter_2_1(const DeviceInterface * dev, Stream<float44> * input1, Stream<float4> * input2, Stream<float444> * output);

	 int kerneltensorouter_2_f4(const DeviceInterface * dev, Stream<float44> * input1, float4 input2, Stream<float444> * output);

	 int kerneltensorouter_f44_1(const DeviceInterface * dev, float44 input1, Stream<float4> * input2, Stream<float444> * output);

	 int kerneltensorouter_1_2(const DeviceInterface * dev, Stream<float4> * lhs, Stream<float44> * rhs, Stream<float444> * output);

	 int kerneltensorouter_f4_2(const DeviceInterface * dev, float4 lhs, Stream<float44> * rhs, Stream<float444> * output);

	 int kerneltensorouter_1_f44(const DeviceInterface * dev, Stream<float4> * lhs, float44 rhs, Stream<float444> * output);

	 int kerneltensorneg_0(const DeviceInterface * dev, Stream<float> * input, Stream<float> * output);

	 int kerneltensorneg_1(const DeviceInterface * dev, Stream<float4> * input, Stream<float4> * output);

	 int kerneltensorneg_2(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output);

	 int kerneltensorneg_3(const DeviceInterface * dev, Stream<float444> * input, Stream<float444> * output);

	 int kerneltensorsqrt_0(const DeviceInterface * dev, Stream<float> * input, Stream<float> * output);

	 int kerneltensorsin_0(const DeviceInterface * dev, Stream<float> * input, Stream<float> * output);

	 int kerneltensorcos_0(const DeviceInterface * dev, Stream<float> * input, Stream<float> * output);

	 int kerneltensortan_0(const DeviceInterface * dev, Stream<float> * input, Stream<float> * output);

	 int kerneltensorexp_0(const DeviceInterface * dev, Stream<float> * input, Stream<float> * output);

	 int kerneltensortrans_2(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output);

	 int kerneltensortrans_3_213(const DeviceInterface * dev, Stream<float444> * input, Stream<float444> * output);

	 int kerneltensortrans_3_132(const DeviceInterface * dev, Stream<float444> * input, Stream<float444> * output);

	 int kernelmoveindex_1(const DeviceInterface * dev, Stream<float4> * input, Stream<float4> * output);

	 int kernelmovelastindex_2(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output);

	 int kernelmovefirstindex_2(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output);

	 int kernelmoveindices_2(const DeviceInterface * dev, Stream<float44> * input, Stream<float44> * output);

	 int kernelmoveindices_3(const DeviceInterface * dev, Stream<float444> * input, Stream<float444> * output);

	 int kernelmovelastindex_3(const DeviceInterface * dev, Stream<float444> * input, Stream<float444> * output);

	 int kernelmovemiddleindex_3(const DeviceInterface * dev, Stream<float444> * input, Stream<float444> * output);

	 int kernelmovefirstindex_3(const DeviceInterface * dev, Stream<float444> * input, Stream<float444> * output);

	 int kernellorentzboost(const DeviceInterface * dev, Stream<float4> * vector1, Stream<float4> * vector2, Stream<float4> * output);

	 int kernellorentzrotation(const DeviceInterface * dev, Stream<float4> * vector1, Stream<float4> * vector2, Stream<float4> * output);

	 int kerneltensorphi_1(const DeviceInterface * dev, Stream<float4> * input, Stream<float> * output);

	 int kerneltensorcostheta_1(const DeviceInterface * dev, Stream<float4> * input, Stream<float> * output);

	 int kerneltensorcontract_1_1(const DeviceInterface * dev, Stream<float4> * input1, Stream<float4> * input2, Stream<float> * output);

	 int kerneltensorcontract_1_f(const DeviceInterface * dev, Stream<float4> * input1, float4 input2, Stream<float> * output);

	 int kerneltensorcontract_2_1(const DeviceInterface * dev, Stream<float44> * input1, Stream<float4> * input2, Stream<float4> * output);

	 int kerneltensorcontract_f44_1(const DeviceInterface * dev, float44 input1, Stream<float4> * input2, Stream<float4> * output);

	 int kerneltensorcontract_2_f4(const DeviceInterface * dev, Stream<float44> * input1, float4 input2, Stream<float4> * output);

	 int kerneltensorcontract_2_2(const DeviceInterface * dev, Stream<float44> * input1, Stream<float44> * input2, Stream<float> * output);

	 int kerneltensorcontract_2_f44(const DeviceInterface * dev, Stream<float44> * input1, float44 input2, Stream<float> * output);

	 int kerneltensorcontract2_2_2(const DeviceInterface * dev, Stream<float44> * p1, Stream<float44> * p2, Stream<float44> * output);

	 int kerneltensorcontract2_2_f44(const DeviceInterface * dev, Stream<float44> * p1, float44 p2, Stream<float44> * output);

	 int kerneltensorcontract2_f44_2(const DeviceInterface * dev, float44 p1, Stream<float44> * p2, Stream<float44> * output);

	 int kerneltensorcontract_3_3(const DeviceInterface * dev, Stream<float444> * input1, Stream<float444> * input2, Stream<float> * output);

	 int kerneltensorcontract_3_f444(const DeviceInterface * dev, Stream<float444> * input1, float444 input2, Stream<float> * output);

	 int kerneltensorcontract_3_1(const DeviceInterface * dev, Stream<float444> * input1, Stream<float4> * input2, Stream<float44> * output);

	 int kerneltensorcontract_f444_1(const DeviceInterface * dev, float444 input1, Stream<float4> * input2, Stream<float44> * output);

	 int kerneltensorcontract_3_f4(const DeviceInterface * dev, Stream<float444> * input1, float4 input2, Stream<float44> * output);

	 int kerneltensorcontract_3_2(const DeviceInterface * dev, Stream<float444> * input1, Stream<float44> * input2, Stream<float4> * output);

	 int kerneltensorcontract_3_f44(const DeviceInterface * dev, Stream<float444> * input1, float44 input2, Stream<float4> * output);

	 int kerneltensorcontract_2_3_sign(const DeviceInterface * dev, Stream<float44> * input1, Stream<float444> * input2, int sign, Stream<float4> * output);

	 int kerneltensorcontract_2_3(const DeviceInterface * dev, Stream<float44> * input1, Stream<float444> * input2, Stream<float4> * output);

	 int kerneltensorcontract_2_f444(const DeviceInterface * dev, Stream<float44> * input1, float444 input2, Stream<float4> * output);

	 int kerneltensorcontract_f44_3(const DeviceInterface * dev, float44 input1, Stream<float444> * input2, Stream<float4> * output);

	 int kerneltensorcontract_f444_2(const DeviceInterface * dev, float444 input1, Stream<float44> * input2, Stream<float4> * output);

	 int kerneltensorcontract2_3_3(const DeviceInterface * dev, Stream<float444> * input1, Stream<float444> * input2, Stream<float44> * output);

}
#endif
