#include "GPUPartialWave.h"
#include <cstring>


GPUPartialWave::GPUPartialWave(ROOT::Minuit2::MnUserParameters * pars, unsigned int ndynpars, char * _name, unsigned int nsets):
								  GPUParameterDependentObject(pars,
								  std::vector<char **>(ndynpars+2,(char **)0),ndynpars+2, nsets)
{
	mName = new char[strlen(_name)+1];
	strcpy(mName, _name);
	mActive = true;

	unsigned int sl = strlen(_name);
	char ** p1 = new char*;
	char ** p2 = new char*;

	*p1 = new char[sl+8];
	*p2 = new char[sl+8];
	sprintf(*p1,"%s_%s",_name,"mag");
	sprintf(*p2,"%s_%s",_name,"phase");
	mparnames[0] = p1;
	mparnames[1] = p2;
}


GPUPartialWave::~GPUPartialWave(void)
{
	delete[] mName;
}
