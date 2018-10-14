/* Contractions.h  -- header for interface functions to the kernels
 defined in /scratchfs/bes/xiongxa/GamEtapKsKs/GPUPWA/gpupwa2.1_jpc2370check/GPUPWA/Contractions.cl, the corresponding binaries are in binfiles/Contractions.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#ifndef HHContractions_GPUHH
#define HHContractions_GPUHH


#include"Stream.h"
#include"DeviceInterface.h"


namespace Contractions_GPU{

	 int prepare_kernels(const DeviceInterface * dev);

	 extern cl::Kernel * k_kernelone;
	 extern cl::Kernel * k_kernelone_c;
	 extern cl::Kernel * k_kernelcontractscalar;
	 extern cl::Kernel * k_kernelcontractscalar_f_u;
	 extern cl::Kernel * k_kernelcontractscalar_u_f;
	 extern cl::Kernel * k_kernelcontractscalar_u_u;
	 extern cl::Kernel * k_kernelcontractscalarorbital;
	 extern cl::Kernel * k_kernelcontractmesons;
	 extern cl::Kernel * k_kernelcontractmesons_v_v;
	 extern cl::Kernel * k_kernelcontractmesons_s_v;
	 extern cl::Kernel * k_kernelcontractmesons_v_s;
	 extern cl::Kernel * k_kernelcontractmesonsorbital;
	 extern cl::Kernel * k_kernelcontractradmesons;
	 extern cl::Kernel * k_kernelcontractradmesonsorbital;
	 extern cl::Kernel * k_kernelcontractradmesons_f_u;
	 extern cl::Kernel * k_kernelcontractradmesons_u_f;
	 extern cl::Kernel * k_kernelcontract3radmesons;
	 int kernelone(const DeviceInterface * dev, Stream<float> * a);

	 int kernelone_c(const DeviceInterface * dev, Stream<float2> * a);

	 int kernelcontractscalar(const DeviceInterface * dev, Stream<float> * tensor1, Stream<float> * tensor2, Stream<float2> * propagator1, Stream<float2> * propagator2, Stream<float2> * result);

	 int kernelcontractscalar_f_u(const DeviceInterface * dev, Stream<float> * tensor1, Stream<float2> * propagator1, Stream<float2> * propagator2, Stream<float2> * result);

	 int kernelcontractscalar_u_f(const DeviceInterface * dev, Stream<float2> * propagator1, Stream<float> * tensor2, Stream<float2> * propagator2, Stream<float2> * result);

	 int kernelcontractscalar_u_u(const DeviceInterface * dev, Stream<float2> * propagator1, Stream<float2> * propagator2, Stream<float2> * result);

	 int kernelcontractscalarorbital(const DeviceInterface * dev, Stream<float> * tensor1, Stream<float> * tensor2, Stream<float> * result);

	 int kernelcontractmesons(const DeviceInterface * dev, Stream<float4> * tensor1, Stream<float4> * tensor2, Stream<float2> * propagator1, Stream<float2> * propagator2, Stream<float2> * result);

	 int kernelcontractmesons_v_v(const DeviceInterface * dev, Stream<float4> * propagator1real, Stream<float4> * propagator1imag, Stream<float4> * propagator2real, Stream<float4> * propagator2imag, Stream<float2> * result);

	 int kernelcontractmesons_s_v(const DeviceInterface * dev, Stream<float4> * tensor1, Stream<float2> * propagator1, Stream<float4> * propagator2real, Stream<float4> * propagator2imag, Stream<float2> * result);

	 int kernelcontractmesons_v_s(const DeviceInterface * dev, Stream<float4> * tensor2, Stream<float4> * propagator1real, Stream<float4> * propagator1imag, Stream<float2> * propagator2, Stream<float2> * result);

	 int kernelcontractmesonsorbital(const DeviceInterface * dev, Stream<float4> * tensor1, Stream<float4> * tensor2, Stream<float> * result);

	 int kernelcontractradmesons(const DeviceInterface * dev, Stream<float44> * tensor1, Stream<float44> * tensor2, Stream<float44> * gperp, Stream<float2> * propagator1, Stream<float2> * propagator2, Stream<float2> * result);

	 int kernelcontractradmesonsorbital(const DeviceInterface * dev, Stream<float44> * tensor1, Stream<float44> * tensor2, Stream<float44> * gperp, Stream<float> * result);

	 int kernelcontractradmesons_f_u(const DeviceInterface * dev, Stream<float44> * tensor1, Stream<float2> * propagator1, Stream<float44> * gperp, Stream<float44> * p2real, Stream<float44> * p2imag, Stream<float2> * result);

	 int kernelcontractradmesons_u_f(const DeviceInterface * dev, Stream<float44> * p1real, Stream<float44> * p1imag, Stream<float44> * gperp, Stream<float44> * tensor2, Stream<float2> * propagator2, Stream<float2> * result);

	 int kernelcontract3radmesons(const DeviceInterface * dev, Stream<float44> * gperp, Stream<float44> * p1real, Stream<float44> * p1imag, Stream<float44> * p2real, Stream<float44> * p2imag, Stream<float2> * result);

}
#endif
