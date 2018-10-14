#include "GPUPropagator.h"
#include <cassert>

#include "GPUPartialWaveAnalysis.h"

GPUPropagator::GPUPropagator(GPUPartialWaveAnalysis * ana, char * name, std::vector<char **> _parnames, unsigned int npars):
	GPUParameterDependentObject(ana->GetParameters(), _parnames, npars, ana->GetNSets()),
	mana(ana),
	mName(1,name)
{}



GPUPropagator::GPUPropagator(GPUPartialWaveAnalysis * ana, std::vector<char *> _names,
								std::vector<unsigned int *> _Parameters, vector<char **>  parnames):
								GPUParameterDependentObject(ana->GetParameters(), _Parameters, parnames, ana->GetNSets()),
								mana(ana),
								mName(_names)
{

}


GPUPropagator::~GPUPropagator(void)
{
}


