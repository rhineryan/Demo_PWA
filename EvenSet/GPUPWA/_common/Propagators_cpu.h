/* Propagators_cpu.h  -- header for interface functions to the kernels
 defined in /scratchfs/bes/xiongxa/Demo_PWA_GPUPWA/GPUPWA/GPUPWA/Propagators.cl, the corresponding binaries are in binfiles/Propagators_cpu.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#ifndef HHPropagators_CPUHH
#define HHPropagators_CPUHH


#include"Stream.h"
#include"DeviceInterface.h"


namespace Propagators_CPU{

	 int prepare_kernels(const DeviceInterface * dev);

	 extern cl::Kernel * k_kernelbreitwigner;
	 extern cl::Kernel * k_kernelgaussian;
	 extern cl::Kernel * k_kerneldbreitwignerdmass;
	 extern cl::Kernel * k_kerneldbreitwignerdwidth;
	 extern cl::Kernel * k_kerneldbw2dmass;
	 extern cl::Kernel * k_kerneldbw2dwidth;
	 extern cl::Kernel * k_kernelmassdependentbreitwigner0;
	 extern cl::Kernel * k_kernelmassdependentbreitwigner1;
	 extern cl::Kernel * k_kernelmassdependentbreitwigner2;
	 extern cl::Kernel * k_kernelmassdependentbreitwigner3;
	 extern cl::Kernel * k_kernelmassdependentbreitwigner4;
	 extern cl::Kernel * k_kernelmassdependentbreitwigner0dwidth;
	 extern cl::Kernel * k_kernelmassdependentbreitwigner1dwidth;
	 extern cl::Kernel * k_kernelmassdependentbreitwigner2dwidth;
	 extern cl::Kernel * k_kernelmassdependentbreitwigner3dwidth;
	 extern cl::Kernel * k_kernelmassdependentbreitwigner4dwidth;
	 extern cl::Kernel * k_kernelmassdependentbreitwigner0dmass;
	 extern cl::Kernel * k_kernelmassdependentbreitwigner1dmass;
	 extern cl::Kernel * k_kernelmassdependentbreitwigner2dmass;
	 extern cl::Kernel * k_kernelmassdependentbreitwigner3dmass;
	 extern cl::Kernel * k_kernelmassdependentbreitwigner4dmass;
	 extern cl::Kernel * k_kerneldmassdependentbreitwigner20dwidth;
	 extern cl::Kernel * k_kerneldmassdependentbreitwigner21dwidth;
	 extern cl::Kernel * k_kerneldmassdependentbreitwigner22dwidth;
	 extern cl::Kernel * k_kerneldmassdependentbreitwigner23dwidth;
	 extern cl::Kernel * k_kerneldmassdependentbreitwigner24dwidth;
	 extern cl::Kernel * k_kernelflatte2;
	 extern cl::Kernel * k_kernelflatte3;
	 extern cl::Kernel * k_kernelflatte4;
	 extern cl::Kernel * k_kernelsigma;
	 extern cl::Kernel * k_kernelfnscalarzou;
	 extern cl::Kernel * k_kernelfnscalarcm2;
	 extern cl::Kernel * k_kernelfnscalarcm;
	 extern cl::Kernel * k_kernelfnscalarchung;
	 extern cl::Kernel * k_kernel_a0980;
	 extern cl::Kernel * k_kernelsumBW;
	 extern cl::Kernel * k_kernelComBW;
	 int kernelbreitwigner(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, Stream<float2> * output);

	 int kernelgaussian(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, Stream<float2> * output);

	 int kerneldbreitwignerdmass(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, Stream<float2> * output);

	 int kerneldbreitwignerdwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, Stream<float2> * output);

	 int kerneldbw2dmass(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, Stream<float> * output);

	 int kerneldbw2dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, Stream<float> * output);

	 int kernelmassdependentbreitwigner0(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelmassdependentbreitwigner1(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelmassdependentbreitwigner2(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelmassdependentbreitwigner3(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelmassdependentbreitwigner4(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelmassdependentbreitwigner0dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelmassdependentbreitwigner1dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelmassdependentbreitwigner2dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelmassdependentbreitwigner3dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelmassdependentbreitwigner4dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelmassdependentbreitwigner0dmass(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelmassdependentbreitwigner1dmass(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelmassdependentbreitwigner2dmass(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelmassdependentbreitwigner3dmass(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelmassdependentbreitwigner4dmass(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float wr, float pmr, float m1_2, float m2_2, Stream<float2> * output);

	 int kerneldmassdependentbreitwigner20dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g, float pmr, float m1_2, float m2_2, Stream<float> * output);

	 int kerneldmassdependentbreitwigner21dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g, float pmr, float m1_2, float m2_2, Stream<float> * output);

	 int kerneldmassdependentbreitwigner22dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g, float pmr, float m1_2, float m2_2, Stream<float> * output);

	 int kerneldmassdependentbreitwigner23dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g, float pmr, float m1_2, float m2_2, Stream<float> * output);

	 int kerneldmassdependentbreitwigner24dwidth(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g, float pmr, float m1_2, float m2_2, Stream<float> * output);

	 int kernelflatte2(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g1, float m1a, float m1b, float g2, float m2a, float m2b, Stream<float2> * output);

	 int kernelflatte3(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g1, float m1a, float m1b, float g2, float m2a, float m2b, float g3, float m3a, float m3b, Stream<float2> * output);

	 int kernelflatte4(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g1, float m1a, float m1b, float g2, float m2a, float m2b, float g3, float m3a, float m3b, float g4, float m4a, float m4b, Stream<float2> * output);

	 int kernelsigma(const DeviceInterface * dev, Stream<float> * mx2in, Stream<float2> * output);

	 int kernelfnscalarzou(const DeviceInterface * dev, Stream<float> * mx2in, uint n, Stream<float4> * par, float c, float cs, float2 d, float2 ds, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelfnscalarcm2(const DeviceInterface * dev, Stream<float> * mx2in, uint n, Stream<float4> * par, float c, float cs, float2 d, float2 ds, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelfnscalarcm(const DeviceInterface * dev, Stream<float> * mx2in, uint n, Stream<float4> * par, float c, float cs, float2 d, float2 ds, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelfnscalarchung(const DeviceInterface * dev, Stream<float> * mx2in, uint n, Stream<float4> * par, float c, float cs, float2 d, float2 ds, float m1_2, float m2_2, Stream<float2> * output);

	 int kernel_a0980(const DeviceInterface * dev, Stream<float> * mx2in, float mr, float mr2, float g1, float m1a, float m1b, float g2, float m2a, float m2b, float g3, float m3a, float m3b, float g4, float m4a, float m4b, Stream<float2> * output);

	 int kernelsumBW(const DeviceInterface * dev, Stream<float> * mx123in, Stream<float> * mx2in, uint n, Stream<float4> * par, float m1_2, float m2_2, Stream<float2> * output);

	 int kernelComBW(const DeviceInterface * dev, Stream<float> * mx2in, Stream<float4> * par, Stream<float2> * output);

}
#endif
