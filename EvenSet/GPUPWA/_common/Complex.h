/* Complex.h  -- header for interface functions to the kernels
 defined in /scratchfs/bes/xiongxa/Demo_PWA_GPUPWA/GPUPWA/GPUPWA/Complex.cl, the corresponding binaries are in binfiles/Complex.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#ifndef HHComplex_GPUHH
#define HHComplex_GPUHH


#include"Stream.h"
#include"DeviceInterface.h"


namespace Complex_GPU{

	 int prepare_kernels(const DeviceInterface * dev);

	 extern cl::Kernel * k_kernelmultiplycomplex;
	 extern cl::Kernel * k_kerneladdcomplex;
	 extern cl::Kernel * k_kernelmultiplycomplexf;
	 extern cl::Kernel * k_kernelcomplexsplit;
	 extern cl::Kernel * k_kerneltensormult_c4_c;
	 extern cl::Kernel * k_kerneltensormult_4_c;
	 extern cl::Kernel * k_kerneltensormult_c_c44;
	 int kernelmultiplycomplex(const DeviceInterface * dev, Stream<float2> * in1, Stream<float2> * in2, Stream<float2> * result);

	 int kerneladdcomplex(const DeviceInterface * dev, Stream<float2> * in1, Stream<float2> * in2, Stream<float2> * result);

	 int kernelmultiplycomplexf(const DeviceInterface * dev, Stream<float2> * in1, Stream<float> * in2, Stream<float2> * result);

	 int kernelcomplexsplit(const DeviceInterface * dev, Stream<float2> * myin, Stream<float> * real, Stream<float> * imag);

	 int kerneltensormult_c4_c(const DeviceInterface * dev, Stream<float4> * lreal, Stream<float4> * limag, Stream<float> * rreal, Stream<float> * rimag, Stream<float4> * resultreal, Stream<float4> * resultimag);

	 int kerneltensormult_4_c(const DeviceInterface * dev, Stream<float4> * lreal, Stream<float> * rreal, Stream<float> * rimag, Stream<float4> * resultreal, Stream<float4> * resultimag);

	 int kerneltensormult_c_c44(const DeviceInterface * dev, Stream<float> * lreal, Stream<float> * limag, Stream<float44> * rreal, Stream<float44> * rimag, Stream<float44> * resultreal, Stream<float44> * resultimag);

}
#endif
