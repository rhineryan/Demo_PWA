/// \file PrepareKernels.h
/*
 * PrepareKernels.h
 *
 *  Created on: Dec 7, 2010
 *      Author: nberger
 */

#ifndef PREPAREKERNELS_H_
#define PREPAREKERNELS_H_

class DeviceInterface;

/// Prepare kernels for the CPU
void PrepareKernels_CPU(const DeviceInterface * dev);

/// Prepare kernels for the GPU
void PrepareKernels_GPU(const DeviceInterface * dev);

#endif /* PREPAREKERNELS_H_ */
