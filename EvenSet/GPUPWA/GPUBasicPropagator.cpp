/*
 * GPUBasicPropagator.cpp
 *
 *  Created on: Aug 26, 2009
 *      Author: nberger
 */

#include "GPUBasicPropagator.h"
#include "GPUStreamTensor.h"
#include "GPUPartialWaveAnalysis.h"

GPUBasicPropagator::GPUBasicPropagator(char * name,
										GPUStreamScalar & _mx2,
										std::vector<char **> parnames,
										unsigned int npar):
										GPUScalarPropagator(static_cast<GPUPartialWaveAnalysis*>(_mx2.GetList()),
												name,
												parnames,
												npar),
										mx2(_mx2) {
}

GPUBasicPropagator::~GPUBasicPropagator() {

}
