/// \file GPUPartialWave.h

#pragma once

#include "GPUParameterDependentObject.h"
#include "GPUDataStream.h"
#include <cstdio>
#include <cassert>
#include <vector>

/// Class representing a single partial wave and its relationship with fit parameters
/**
Abstract base class for all kinds of partial waves
With the SetActive and SetInactive functions, a wave can be switched on and off for a
particular fit.
**/
class GPUPartialWave: public GPUParameterDependentObject
{
public:
  /// Constructor
  GPUPartialWave(ROOT::Minuit2::MnUserParameters * pars, unsigned int ndynpars, char * _name, unsigned int nsets);

  /// Destructor
  virtual ~GPUPartialWave(void);

  /// Get the name
  virtual char * GetName(){return mName;};
  /// Find out whether the wave is currently actiev (i.e. used in fits)
  virtual bool Active(){return mActive;};
  /// Switch the wave on (off, if _mActive == false)
  virtual void SetActive(bool _mActive = true){mActive = _mActive;};
  /// Switch the wave off
  virtual void SetInactive(){mActive = false;};

  /// Get the number of the parameter, that controls the magnitude of this wave
  virtual int GetMagnitudeParameter() const {return GetParameter(0);};
  /// Get the number of the parameter, that controls the Phase of this wave
  virtual int GetPhaseParameter()const{return GetParameter(1);};
  /// Get the list of the parameters, that control the dynamic part of this wave
  virtual std::vector<unsigned int *> GetDynamicParameters()const =0;
  /// Get the number the parameters, that control the dynamic part of this wave
  virtual unsigned int GetNDynamicParameters()const{return GetNPars()-2;};

  /// Get the a parameter, that controls the dynamic part of this wave
  virtual unsigned int GetDynamicParameter(unsigned int index)const{
	  return GetParameter(index+2);
  };
  /// Get the name of a dynamic parameter
  virtual char * GetDynamicParameterName(unsigned int index)const{
  	  return GetParameterName(index+2);
   };

  /// Get the name of a dynamic parameter
  virtual std::vector<char **> GetDynamicParameterNames(){
	  std::vector<char **> ret;
	  for(unsigned i=2; i < GetNPars(); i++)
    	  ret.push_back(GetParameterNames()[i]);
	  return ret;
   };

  /// Set the number of the parameter, that controls the magnitude of this wave
  virtual void SetMagnitudeParameter(int n){SetParameter(0,n);};
  /// Set the number of the parameter, that controls the phase of this wave
  virtual void SetPhaseParameter(int n){SetParameter(1,n);};
  /// Set the numbers of the parameters, that control the dynamic part of this wave
  virtual void SetDynamicParameters(std::vector<unsigned int *> n)=0;
  /// Set the number of a parameter, that controls the dynamic part of this wave
  virtual void SetDynamicParameter(unsigned int index, unsigned int parindex ){
	  assert(index-2 >= 0);
	  SetParameter(index-2,parindex);
  };

  /// Check whether the cached dynamic part is valid (magnitute and phase are allowed to have changed
  virtual bool DynamicCacheValid(unsigned int index) const{
	  bool valid = true;
	  //cout << "In CacheValid()" << endl;
	  for(unsigned int i =2; i < mparindices.size(); i++){
		  valid = valid && *(mlastvalues[index][i]) == mParameters->Value(*(mparindices[i]));
		  //if(!valid)
		//	  cout << *(mparindices[i]) << " : " << *(mlastvalues[i]) << " : " << mParameters->Value(*(mparindices[i])) << endl;
  		}
  		return valid;
  	};

  /// Core functionality: Contract with another wave to a complex number stream
  virtual GPUDataStream<float2> * Contract(GPUPartialWave * wave, unsigned int index, unsigned int block) =0;

  /// Core functionality: Contract parameter independent parts with another wave to a scalar number stream
  /** Will return 0 if there is no parameter-independent part, has to be checked by the calling function
   */
  virtual GPUDataStream<float> * ContractOrbital(GPUPartialWave * wave, unsigned int index, unsigned int block){return 0;};

  /// Check whether a wave combination has a parameter independent part
  virtual bool HasContractOrbital(GPUPartialWave * wave){return false;};

  /// Increase the Usecount for the caching mechanism
  virtual void IncreaseUsecount(unsigned int index) =0;

  /// Increase the Usecount for the caching mechanism
  virtual void IncreaseUsecountOrbital(unsigned int index){IncreaseUsecount(index);};

 protected:
  /// Name of the wave
  char * mName;
  /// Current active state of the wave
  bool mActive;
};
