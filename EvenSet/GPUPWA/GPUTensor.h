/// \file GPUTensor.h

#pragma once
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>

///Base class for GPU based Tensors
/** This is the base class for all GPU based Tensor calculations, it mainly serves as an
abstraction for calculation input, in order to allow for the operater notation in user 
programs. A priori, GPUTensors have just one property, namely their rank. The constructors
are protected to ensure only derived objects can be instantiated.
*/
class GPUTensor
{
public:
	/// Destructor
	virtual ~GPUTensor(void){};
	/// Number of elements in the tensor
	int Size() const {
		return (1 << (mrank << 1));
	};
	/// Get the Tensors rank
	int Rank() const {return mrank;};
protected:
	/// Default Costructor -> Rank 0
	GPUTensor(void):mrank(0) {}; // ,mlength(1,0)
	/// Costructor with Rank
	GPUTensor(int _rank):mrank(_rank) {};	//,mlength(1,0)
	/// Assert tensors have the same rank
	inline void RankAssert (const GPUTensor & _tbase) const
	{  assert(this->mrank == _tbase.mrank);};
	/// Rank of the tensor
	const int mrank;


};
