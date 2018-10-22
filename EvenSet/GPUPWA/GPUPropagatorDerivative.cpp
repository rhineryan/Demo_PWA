/*
 * GPUPropagatorDerivative.cpp
 *
 *  Created on: Aug 27, 2009
 *      Author: nberger
 */

#include "GPUPropagatorDerivative.h"

GPUPropagatorDerivative::GPUPropagatorDerivative() {


}

GPUPropagatorDerivative::~GPUPropagatorDerivative() {

}

void GPUPropagatorDerivative::ResetDerivatives(int index) {
	if (index < (int) mDmass.size()) {
		for (int i = 0; i < (int) mDmass[index].size(); i++) {
			if (mDmass[index][i])
				delete mDmass[index][i];
			mDmass[index][i] = 0;
		}
	}
	if (index < (int) mDwidth.size()) {
		for (int i = 0; i < (int) mDwidth[index].size(); i++) {
			if (mDwidth[index][i])
				delete mDwidth[index][i];
			mDwidth[index][i] = 0;
		}
	}
	if (index < (int) mAbsDmass.size()) {
		for (int i = 0; i < (int) mAbsDmass[index].size(); i++) {
			if (mAbsDmass[index][i])
				delete mAbsDmass[index][i];
			mAbsDmass[index][i] = 0;
		}
	}
	if (index < (int) mAbsDwidth.size()) {
		for (int i = 0; i < (int) mAbsDwidth[index].size(); i++) {
			if (mAbsDwidth[index][i])
				delete mAbsDwidth[index][i];
			mAbsDwidth[index][i] = 0;
		}
	}



}

void GPUPropagatorDerivative::ResetDerivatives(int index, int block) {
	if (index < (int) mDmass.size()) {
		if (mDmass[index][block])
			delete mDmass[index][block];
		mDmass[index][block] = 0;
	}
	if (index < (int) mDwidth.size()) {
		if (mDwidth[index][block])
			delete mDwidth[index][block];
		mDwidth[index][block] = 0;
	}
	if (index < (int) mAbsDmass.size()) {
		if (mAbsDmass[index][block])
			delete mAbsDmass[index][block];
		mAbsDmass[index][block] = 0;
	}
	if (index < (int) mAbsDwidth.size()) {
		if (mAbsDwidth[index][block])
			delete mAbsDwidth[index][block];
		mAbsDwidth[index][block] = 0;
	}
}
