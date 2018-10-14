/* Analysis_cpu.h  -- header for interface functions to the kernels
 defined in /scratchfs/bes/xiongxa/Demo_PWA_GPUPWA/GPUPWA/GPUPWA/Analysis.cl, the corresponding binaries are in binfiles/Analysis_cpu.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#ifndef HHAnalysis_CPUHH
#define HHAnalysis_CPUHH


#include"Stream.h"
#include"DeviceInterface.h"


namespace Analysis_CPU{

	 int prepare_kernels(const DeviceInterface * dev);

	 extern cl::Kernel * k_pwamult4;
	 extern cl::Kernel * k_collectpropagators4;
	 extern cl::Kernel * k_freepwamult4;
	 extern cl::Kernel * k_freepwamult4tcs;
	 extern cl::Kernel * k_freepwamult4tcsweighted;
	 extern cl::Kernel * k_pwagradmult4all;
	 extern cl::Kernel * k_kernelhessian;
	 extern cl::Kernel * k_kernelhessian4all;
	 extern cl::Kernel * k_pwamultdcsonly4;
	 extern cl::Kernel * k_pwamultdcsonly4weighted;
	 extern cl::Kernel * k_pwamultdcsonlyonewave4;
	 extern cl::Kernel * k_pwamultdcsonlytwowaves4;
	 extern cl::Kernel * k_kernelmult_c_c_f;
	 extern cl::Kernel * k_kernelmult_c_cbar_f;
	 extern cl::Kernel * k_kernelmult_2c_cbar_f;
	 extern cl::Kernel * k_kernelmult_c2_f;
	 extern cl::Kernel * k_kernelsum16float2double;
	 extern cl::Kernel * k_kernelsum16float2double2d;
	 extern cl::Kernel * k_kernelweightedsumfloat2double;
	 extern cl::Kernel * k_kernelsumfloat2double;
	 extern cl::Kernel * k_kernelsumdouble2double;
	 extern cl::Kernel * k_kernel4orbitaltensor;
	 extern cl::Kernel * k_kernel4orbitaltensorconst;
	 extern cl::Kernel * k_kernel3orbitaltensor;
	 extern cl::Kernel * k_kernel3orbitaltensorconst;
	 extern cl::Kernel * k_kernelfilllookup;
	 int pwamult4(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weight, Stream<float4> * lookupx, Stream<float4> * lookupy, Stream<float2> * parameters, uint n, float bgpar, float tcs, Stream<float4> * dcs, Stream<float4> * logdcs);

	 int collectpropagators4(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * propagator, uint nwave, uint waveindex, Stream<float4> * prop);

	 int freepwamult4(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weight, Stream<float4> * lookup, Stream<float4> * propagator, Stream<float2> * parameters, uint n, float bgpar, float tcs, Stream<float4> * dcs, Stream<float4> * logdcs);

	 int freepwamult4tcs(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * lookup, Stream<float4> * propagator, Stream<float2> * parameters, uint n, Stream<float4> * dcs);

	 int freepwamult4tcsweighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * weights, Stream<float4> * lookup, Stream<float4> * propagator, Stream<float2> * parameters, uint n, Stream<float4> * dcs);

	 int pwagradmult4all(const cl::NDRange & range, const DeviceInterface * dev, Stream<int> * input, Stream<float4> * weightin, Stream<float4> * dcsin, Stream<float4> * lookupx, Stream<float4> * lookupy, Stream<float2> * parameters, uint nwaves, uint ngrads, Stream<float> * gradpar, float bgpar, float tcs, Stream<float> * dtcsin, Stream<float4> * grad, Stream<float4> * innergrad);

	 int kernelhessian(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * gradient1, Stream<float> * gradient2, Stream<float> * dcs, Stream<float> * weight, float bgpar, float tcs, Stream<float> * hessian);

	 int kernelhessian4all(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * gradients, Stream<float4> * dcs, Stream<float4> * weight, uint ngrad, float bgpar, float tcs, Stream<float4> * hessian);

	 int pwamultdcsonly4(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * lookupx, Stream<float4> * lookupy, Stream<float2> * parameters, uint n, float bgpar, Stream<float4> * dcs);

	 int pwamultdcsonly4weighted(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * lookupx, Stream<float4> * lookupy, Stream<float4> * weights, Stream<float2> * parameters, uint n, float bgpar, Stream<float4> * dcs);

	 int pwamultdcsonlyonewave4(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * lookupx, Stream<float2> * parameters, uint n, uint wavenumber, Stream<float4> * dcs);

	 int pwamultdcsonlytwowaves4(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * lookupx, Stream<float4> * lookupy, Stream<float2> * parameters, uint n, uint wave1, uint wave2, Stream<float4> * dcs);

	 int kernelmult_c_c_f(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * c1, Stream<float2> * c2, Stream<float> * f, Stream<float2> * result);

	 int kernelmult_c_cbar_f(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * c1, Stream<float2> * c2, Stream<float> * f, Stream<float2> * result);

	 int kernelmult_2c_cbar_f(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * c1, Stream<float2> * c2, Stream<float> * f, double2 pprodd, Stream<float> * result);

	 int kernelmult_c2_f(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * c1, Stream<float> * f, Stream<float> * result);

	 int kernelsum16float2double(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * input, Stream<double2> * result);

	 int kernelsum16float2double2d(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * input, uint n, Stream<double2> * result);

	 int kernelweightedsumfloat2double(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * nin, Stream<float> * weights, Stream<float2> * input, Stream<double2> * result);

	 int kernelsumfloat2double(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * nin, Stream<float2> * input, Stream<double2> * result);

	 int kernelsumdouble2double(const cl::NDRange & range, const DeviceInterface * dev, Stream<float> * nin, Stream<double2> * input, Stream<double2> * result);

	 int kernel4orbitaltensor(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * rtin, uint i, uint j, Stream<float44> * delpin, Stream<float44> * result);

	 int kernel4orbitaltensorconst(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * rtin, uint i, uint j, float44 delp, Stream<float44> * result);

	 int kernel3orbitaltensor(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * rtin, Stream<float4> * pain, Stream<float444> * result);

	 int kernel3orbitaltensorconst(const cl::NDRange & range, const DeviceInterface * dev, Stream<float4> * rtin, float4 pa, Stream<float444> * result);

	 int kernelfilllookup(const cl::NDRange & range, const DeviceInterface * dev, Stream<float2> * input, uint offset, uint ijindex, uint lookupsize, Stream<float4> * cx, Stream<float4> * cy);

}
#endif
