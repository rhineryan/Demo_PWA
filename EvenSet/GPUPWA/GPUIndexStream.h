/// \file GPUIndexStream.h

/*
 * GPUIndexStream.h
 *
 *  Created on: Sep 8, 2009
 *      Author: nberger
 */

#ifndef GPUINDEXSTREAM_H_
#define GPUINDEXSTREAM_H_

#include "GPUDataStream.h"

class DeviceInterface;

///Create an index stream
/** Used for sums etc.
 *
 */
class GPUIndexStream: public GPUDataStream<float> {
public:
	/// Constructor
	/** Generate an index stream with n elements, counting in increments
	 *  of stride
	 */
	GPUIndexStream(const DeviceInterface * dev, unsigned int n, unsigned int stride = 1);
	/// Constructor for parameter indexing
	/** Generate an index stream with pnums.size elements
	 *  		 */
	GPUIndexStream(const DeviceInterface * dev, std::vector<int> pnums);
	/// Destructor
	virtual ~GPUIndexStream();
};


class GPUGradientIndexStream: public GPUDataStream<int> {
public:
	/// Constructor
	/// Constructor for parameter indexing
	/** Generate an index stream with pnums.size elements
	 *  		 */
	GPUGradientIndexStream(const DeviceInterface * dev, std::vector<int> pnums);
	/// Destructor
	virtual ~GPUGradientIndexStream();
};

///Create a 2D index stream
/** Used for sums etc.
 *
 */
class GPU2DIndexStream: public GPUDataStream<float2> {
public:
	/// Constructor
	/** Generate an index stream with n*m elements, counting in increments
	 *  of stride in the n direction, increments of 1 in the m direction
	 */
	GPU2DIndexStream(const DeviceInterface * dev, unsigned int n, unsigned int m, unsigned int stride = 1);

	/// Destructor
	virtual ~GPU2DIndexStream();
};


///Create a 3D index stream
/** Used for sums etc.
 *
 */
class GPU3DIndexStream: public GPUDataStream<float3> {
public:
	/// Constructor
	/** Generate an index stream with n rows, enumaerating
	 * the upper triangle of an m*m matrix
	 */
	GPU3DIndexStream(const DeviceInterface * dev, unsigned int n, unsigned int m);
	/// Destructor
	virtual ~GPU3DIndexStream();
};



#endif /* GPUINDEXSTREAM_H_ */
