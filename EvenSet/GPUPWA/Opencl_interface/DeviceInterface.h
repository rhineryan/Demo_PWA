/*
 * DeviceInterface.h
 *
 *  Created on: Mar 3, 2010
 *      Author: nberger
 */

#ifndef DEVICEINTERFACE_H_
#define DEVICEINTERFACE_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <CL/cl.hpp>

#include "../Status.h"

/// Class encapsulating the OpenCL interface; can be used for GPUs as well as CPUs
class DeviceInterface {
public:
	/// Constructor; indicate the device type to choose between GPU and CPU
	/** The corresponding device types are CL_DEVICE_TYPE_GPU and CL_DEVICE_TYPE_CPU
	 *
	 */
	DeviceInterface(cl_device_type device_type_);
	/// Destructor
	virtual ~DeviceInterface();

	/// Initialise the device and read its properties
	virtual STATUS init();

	/// Get the device type
	virtual cl_device_type GetDeviceType() const {return mdevice_type;};
	/// Check if initialization worked
	virtual STATUS initialized() const {return minit_ok;};

	/// Set the standard device number
	virtual void SetStandardDevice(unsigned int i) const{mstandarddevice = i;};
	/// Get the standard device number
	virtual const unsigned int GetStandardDevice()const { return mstandarddevice;};

	/// Get the platform used
	virtual cl::Platform * GetPlatform() const {return mplatform;};
	/// Get the platform profile
	virtual const char * GetPlatformProfile() const {return mplatform->getInfo<CL_PLATFORM_PROFILE>().c_str();};
	/// Get the platform version
	virtual const char * GetPlatformVersion() const {return mplatform->getInfo<CL_PLATFORM_VERSION>().c_str();};
	/// Get the platform vendor
	virtual const char * GetPlatformVendor() const {return mplatform->getInfo<CL_PLATFORM_VENDOR>().c_str();};
	/// Get the platform version
	virtual const char * GetPlatformName() const {return mplatform->getInfo<CL_PLATFORM_NAME>().c_str();};
	/// Get the context used
	virtual cl::Context * GetContext() const {return mcontext;};
	/// Get a device
	virtual const cl::Device * GetDevice(unsigned int i) const {return &(mdevices[i]);};
	/// Get the standard device
	virtual const cl::Device * GetDevice() const {return &(mdevices[mstandarddevice]);};
	/// Get the device vector
	virtual const std::vector<cl::Device> * GetDevices() const {return &(mdevices);};
	/// Get the number of devices
	virtual unsigned int GetNDevices() const {return mdevices.size();};
	/// Get the device ID
	virtual const unsigned int GetDeviceID(unsigned int i =0) const{
		return GetDevice(i)->getInfo<CL_DEVICE_VENDOR_ID>();
	};
	/// Get the maximum number of compute units in a device
	virtual const unsigned int GetDeviceMaxComputeUnits(unsigned int i =0) const{
		return GetDevice(i)->getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
	};
	/// Get the maximum number of work item dimensions in a device
	virtual const unsigned int GetDeviceMaxWorkItemDimensions(unsigned int i =0) const{
		return GetDevice(i)->getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
	};
	/// Get the maximum number of work item dimension sizes in a device
#ifdef DEF_64_BIT
	virtual const std::vector<long unsigned int> GetDeviceMaxWorkItemDimensionSize(unsigned int i =0) const{
		return GetDevice(i)->getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>();
	};
#else
	virtual const std::vector<unsigned int> GetDeviceMaxWorkItemDimensionSize(unsigned int i =0) const{
		return GetDevice(i)->getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>();
	};
#endif
	/// Get the maximum work group size in a device
	virtual const unsigned int GetDeviceMaxWorkGroupSize(unsigned int i =0) const{
		return GetDevice(i)->getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>();
	};
	/// Get the maximum clock frequency in a device
	virtual const unsigned int GetDeviceClockFrequency(unsigned int i =0) const{
		return GetDevice(i)->getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>();
	};
	/// Get the maximum memory allocation size in a device
	virtual const unsigned int GetDeviceMaxMemoryAllocationSize(unsigned int i =0) const{
		return GetDevice(i)->getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>();
	};
	/// Get the allocation block size in a device - currently use the maximum size
	virtual const unsigned int GetBlockSize(unsigned int i =0) const{
		return GetDevice(i)->getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>();
	};
	/// Get the global memory size in a device
	virtual const unsigned int GetDeviceGlobalMemorySize(unsigned int i =0) const{
		return GetDevice(i)->getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>();
	};

	/// Get a queue
	virtual const cl::CommandQueue * GetQueue(unsigned int i =0) const {return &(mqueues[i]);};
	/// Get the number of devices
	virtual unsigned int GetNQueues() const {return mqueues.size();};



protected:
	/// Device type (GPU or CPU)
	const cl_device_type mdevice_type;
	/// Standard device
	mutable unsigned int mstandarddevice;
	/// Initialisation ok?
	STATUS minit_ok;
	/// Vector of available platforms
	cl::Platform * mplatform;
	/// Pointer to the contenxt on the platform
	cl::Context * mcontext;
	/// List of devices in the context
	std::vector<cl::Device> mdevices;
	/// Queues
	std::vector<cl::CommandQueue> mqueues;

private:
	/// Disable copy constructor
	DeviceInterface(const DeviceInterface&);
	/// Disable operator=
	DeviceInterface& operator=(const DeviceInterface&);

};

#endif /* DEVICEINTERFACE_H_ */
