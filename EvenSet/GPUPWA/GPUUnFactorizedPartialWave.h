/// \file GPUUnFactorizedPartialWave.h

#pragma once
#include "GPUComputedTensor.h"
#include "GPUPropagatorType.h"
#include "GPUStreamTensor.h"
#include "GPUPartialWave.h"
#include <cassert>
#include <vector>

/// Class represnting a single partial wave that does not factorize into a tensor and a parameter dependent complex number and its relationship with fit parameters
/** This partial wave consists just of Propagator part, which may be of higher rank and complex
**/
template <typename T>
class GPUUnFactorizedPartialWave: public GPUPartialWave
{
public:
  /// Constructor
  GPUUnFactorizedPartialWave(
		 GPUPropagatorType<T> & _propagator,      ///< Complex propagator
		 char * _name);                    ///< Name for the wave

  /// Destructor
  virtual ~GPUUnFactorizedPartialWave(void);
  /// Get the propagator part
  GPUPropagatorType<T> & GetPropagator(){return mPropagator;};
  /// Get the list of the parameters, that control the dynamic part of this wave
  std::vector<unsigned int *> GetDynamicParameters()const{return mPropagator.GetParameters();};
  /// Get the number the parameters, that control the dynamic part of this wave
  unsigned int GetNDynamicParameters()const{return mPropagator.GetNPars();};

  /// Get the a parameter, that controls the dynamic part of this wave
  unsigned int GetDynamicParameter(unsigned int index)const{return mPropagator.GetParameter(index);};
  /// Set the number of the parameter, that controls the magnitude of this wave
  void SetMagnitudeParameter(int n){SetParameter(0,n);};
  /// Set the number of the parameter, that controls the phase of this wave
  void SetPhaseParameter(int n){SetParameter(1,n);};
  /// Set the numbers of the parameters, that control the dynamic part of this wave
  void SetDynamicParameters(std::vector<unsigned int *> n){mPropagator.SetParameters(n);};
  /// Set the number of a parameter, that controls the dynamic part of this wave
  void SetDynamicParameter(unsigned int index, unsigned int parindex ){
	  mPropagator.SetParameter(index,parindex);
  };
  /// Contract this wave with another one
  virtual GPUDataStream<float2> * Contract(GPUPartialWave * wave, unsigned int index, unsigned int block);

  /// Core functionality: Contract parameter independent parts with another wave to a scalar number stream
    /** Will return 0, as there is no parameter-independent part, has to be checked by the calling function
     */
   virtual GPUDataStream<float> * ContractOrbital(GPUPartialWave * wave, unsigned int index, unsigned int block){return 0;};

   /// Check whether a wave combination has a parameter independent part
   virtual bool HasContractOrbital(GPUPartialWave * wave){return false;};

   /// Increase the Usecount for the caching mechanism
   virtual void IncreaseUsecount(unsigned int index){mPropagator.IncreaseUsecount(index);};



 protected:
  /// Propagator part of the wave
  GPUPropagatorType<T> & mPropagator;

};

/// A partial wave with a scalar orbital part
typedef GPUUnFactorizedPartialWave<float> GPUUnFactorizedScalarPartialWave;
/// A partial wave with a vector orbital part
typedef GPUUnFactorizedPartialWave<float4>  GPUUnFactorizedVectorPartialWave;

