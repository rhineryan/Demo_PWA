/*
 * GPUParameterDependentObject.cpp
 *
 *  Created on: Apr 28, 2011
 *      Author: nberger
 */

#include "GPUParameterDependentObject.h"

GPUParameterDependentObject::GPUParameterDependentObject(ROOT::Minuit2::MnUserParameters * pars,
														vector<char **>  parnames,
														unsigned int npars,
														unsigned int nsets):
mParameters(pars), mparnames(parnames), mnsets(nsets)
{
	for(unsigned int i=0; i < npars; i++){
		mparindices.push_back(new unsigned int);
		*(mparindices[i]) = 999;
	}

	for(unsigned int s=0; s < mnsets; s++){
		mlastvalues.push_back(std::vector<double *>());
	}

	for(unsigned int s=0; s < mnsets; s++){
		for(unsigned int i=0; i < npars; i++){
			mlastvalues[s].push_back(new double);
			*(mlastvalues[s][i]) = -9.999e9;
		}
	}
}

GPUParameterDependentObject::GPUParameterDependentObject(ROOT::Minuit2::MnUserParameters * pars,
														 vector<unsigned int *> parlist,
														 vector<char **>  parnames,
														 unsigned int nsets):
mParameters(pars), mparnames(parnames), mnsets(nsets)
{
	for(unsigned int i=0; i < parlist.size(); i++){
		mparindices.push_back(parlist[i]);
	}
	for(unsigned int s=0; s < mnsets; s++){
		mlastvalues.push_back(std::vector<double *>());
	}

	for(unsigned int s=0; s < mnsets; s++){
		for(unsigned int i=0; i < parlist.size(); i++){
			mlastvalues[s].push_back(new double);
			*(mlastvalues[s][i]) = -9.999e9;
		}
	}

}

GPUParameterDependentObject::~GPUParameterDependentObject() {
}
