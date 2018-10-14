/*
 * DeviceInterface.cpp
 *
 *  Created on: Mar 3, 2010
 *      Author: nberger
 */

#include "DeviceInterface.h"

using namespace std;

DeviceInterface::DeviceInterface(cl_device_type device_type_):
mdevice_type(device_type_),mstandarddevice(0){
	minit_ok = FAILURE;
	if(mdevice_type != CL_DEVICE_TYPE_GPU && mdevice_type != CL_DEVICE_TYPE_CPU){
		cerr << "Unsupported device type given" << endl;
		return;
	}
	minit_ok = init();

}

DeviceInterface::~DeviceInterface() {
	if(mcontext)
		delete mcontext;
}


STATUS DeviceInterface::init() {

	cl_int err;

	cout << "Initializing Device!" << endl;

	cout<<"Getting Platform Information" << endl;
	std::vector<cl::Platform> platforms;
	err = cl::Platform::get(&platforms);
	if(err != CL_SUCCESS){
		cerr << "Platform::get() failed (" << err << ")" << endl;
		return FAILURE;
	}
	// Here we loop over the available platforms; if there is more than one, we use the first one that
	// supports the selected device type
	vector<cl::Platform>::iterator i;
	if(platforms.size() > 0) {
		for(i = platforms.begin(); i != platforms.end(); ++i){
			cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM, (cl_context_properties)(*i)(), 0 };
			cout<<"Trying to create a context on the platform" << endl;
			mcontext = new cl::Context(mdevice_type, cps, NULL, NULL, &err);
			if(err == CL_SUCCESS){
				mplatform = &(*i);
				break;
			}
			delete mcontext;
		}
	}
	if(err != CL_SUCCESS || platforms.size() == 0){
		cerr << "Context::Context() failed (" << err << ")" << endl;
		return FAILURE;
	}

	cout<<"Getting device info" << endl;
	mdevices = mcontext->getInfo<CL_CONTEXT_DEVICES>();
	if (err != CL_SUCCESS) {
		cerr << "Context::getInfo() failed (" << err << ")" << endl;
		return FAILURE;
	}

	if (mdevices.size() == 0) {
		std::cerr << "No device available\n";
		return FAILURE;
	} else {
		cout << mdevices.size() << " devices found!" << endl;
	}

	cout<<"Creating queue(s)" << endl;
	vector<cl::Device>::iterator j;
	for(j = mdevices.begin(); j != mdevices.end(); j++){

		mqueues.push_back( cl::CommandQueue(*mcontext, *j, CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE, &err));
		if (err != CL_SUCCESS) {
			std::cerr << "CommandQueue::CommandQueue() failed (" << err << ")\n";
			return FAILURE;
		}
	}

	//cout << "Huh!" << endl;
	return OK;
}
