/// \file GPUDataDependentObjectType.h
/*
 * GPUDataDependentObjectType.h
 *
 *  Created on: Aug 20, 2009
 *      Author: nberger
 */

#ifndef GPUDATADEPENDENTOBJECTTYPE_H_
#define GPUDATADEPENDENTOBJECTTYPE_H_

#include "GPUDataDependentObject.h"
#include "GPUDataDependentObjectList.h"
#include "GPUDataStream.h"

/// Template for class holding streams and part of the cachin mechanism
template <typename T>
class GPUDataDependentObjectType: public GPUDataDependentObject {
public:
	/// Constructor, taking a list in which to register the object
	GPUDataDependentObjectType(GPUDataDependentObjectList * _list, bool init=true):
		GPUDataDependentObject(_list), mstream(_list->GetNSets(),std::vector<GPUDataStream<T> *>()){
		if(init){
			for(int i =0; i < _list->GetNSets(); i++){
				for(int j =0; j < _list->GetNBlocks(i); j++){
					mstream[i].push_back(0);
					musecount[i].push_back(0);
				}
			}
		}
	};
	/// Destructor
	virtual ~GPUDataDependentObjectType(){};

	/// Reset the Stream at an index
	virtual void Reset(int index){
		Reset(index, -1);
	}

	/// Reset the Stream at an index and block
	virtual void Reset(int index, int block){
		if(block == -1){
			if(GetNSets() > index){
				for(int j=0; j < GetNBlocks(index); j++){
					if(mstream[index][j])
						delete mstream[index][j];
					mstream[index][j] =0;
				}
				ResetUsecount(index);
			}
		} else {
			if(GetNSets() > index){
				if(GetNBlocks(index) > block){
					if(mstream[index][block])
						delete mstream[index][block];
					mstream[index][block] =0;
					ResetUsecount(index,block);
				}
			}
		}
	};
protected:
	/// Protected constructor without arguments for derived classes with post-construction registration
	GPUDataDependentObjectType():
		GPUDataDependentObject(){
		assert(0);
	};
	/// Pointer to the stream containing the data
	std::vector<std::vector<GPUDataStream<T> *> > mstream;
};

/// Scalar data dependent object
typedef GPUDataDependentObjectType<float> GPUDataDependentScalar;
/// Complex data dependent object
typedef GPUDataDependentObjectType<float2> GPUDataDependentComplex;
/// Vector data dependent object
typedef GPUDataDependentObjectType<float4> GPUDataDependentVector;
/// Rank 2 data dependent object
typedef GPUDataDependentObjectType<float44> GPUDataDependentTensor2;
/// Rank 3 data dependent object
typedef GPUDataDependentObjectType<float444> GPUDataDependentTensor3;

#endif /* GPUDATADEPENDENTOBJECTTYPE_H_ */
