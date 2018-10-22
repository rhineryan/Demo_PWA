/* Orbitals_cpu.h  -- header for interface functions to the kernels
 defined in /scratchfs/bes/xiongxa/Demo_PWA_GPUPWA/GPUPWA/GPUPWA/Orbitals.cl, the corresponding binaries are in binfiles/Orbitals_cpu.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#ifndef HHOrbitals_CPUHH
#define HHOrbitals_CPUHH


#include"Stream.h"
#include"DeviceInterface.h"


namespace Orbitals_CPU{

	 int prepare_kernels(const DeviceInterface * dev);

	 extern cl::Kernel * k_kernel4orbitaltensor;
	 extern cl::Kernel * k_kernel4orbitaltensorconst;
	 extern cl::Kernel * k_kernel3orbitaltensor;
	 extern cl::Kernel * k_kernel3orbitaltensorconst;
	 extern cl::Kernel * k_kernelspinproject3_2_2;
	 int kernel4orbitaltensor(const DeviceInterface * dev, Stream<float4> * rt, int i, int j, Stream<float44> * delp, Stream<float44> * result);

	 int kernel4orbitaltensorconst(const DeviceInterface * dev, Stream<float4> * rt, int i, int j, float44 delp, Stream<float44> * result);

	 int kernel3orbitaltensor(const DeviceInterface * dev, Stream<float4> * rt, Stream<float4> * pa, Stream<float444> * result);

	 int kernel3orbitaltensorconst(const DeviceInterface * dev, Stream<float4> * rt, float4 pa, Stream<float444> * result);

	 int kernelspinproject3_2_2(const DeviceInterface * dev, Stream<float44> * gtin, Stream<float44> * Tin, uint i, uint j, Stream<float44> * result);

}
#endif
