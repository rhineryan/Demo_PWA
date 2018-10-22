/*
 * PrepareKernels.cpp
 *
 *  Created on: Dec 7, 2010
 *      Author: nberger
 */

#include "PrepareKernels.h"
#include "Analysis.h"
#include "Propagators.h"
#include "Tensors.h"
#include "Contractions.h"
#include "Orbitals.h"
#include "Summing.h"
#include "Complex.h"

#ifndef DEF_NO_CPU
#include "Analysis_cpu.h"
#include "Propagators_cpu.h"
#include "Tensors_cpu.h"
#include "Contractions_cpu.h"
#include "Orbitals_cpu.h"
#include "Summing_cpu.h"
#include "Complex_cpu.h"


// Prepare kernels for the CPU
void PrepareKernels_CPU(const DeviceInterface * dev){
	Analysis_CPU::prepare_kernels(dev);
	Propagators_CPU::prepare_kernels(dev);
	Tensors_CPU::prepare_kernels(dev);
	Contractions_CPU::prepare_kernels(dev);
	Orbitals_CPU::prepare_kernels(dev);
	Summing_CPU::prepare_kernels(dev);
	Complex_CPU::prepare_kernels(dev);
}
#else
void PrepareKernels_CPU(const DeviceInterface * dev){
}
#endif

// Prepare kernels for the GPU
void PrepareKernels_GPU(const DeviceInterface * dev){
	//std::cout << "init begin" << std::endl;
	Analysis_GPU::prepare_kernels(dev);
	//std::cout << " 1 done " << std::endl;
	Propagators_GPU::prepare_kernels(dev);
	Tensors_GPU::prepare_kernels(dev);
	Contractions_GPU::prepare_kernels(dev);
	Orbitals_GPU::prepare_kernels(dev);
	Summing_GPU::prepare_kernels(dev);
	Complex_GPU::prepare_kernels(dev);
}
