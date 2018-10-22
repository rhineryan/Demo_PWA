/// \file GPUFactorizedPartialWave.h

#pragma once
#include "GPUComputedTensor.h"
#include "GPUPropagatorType.h"
#include "GPUStreamTensor.h"
#include "GPUPartialWave.h"
#include <cassert>
#include <vector>

/// Class represnting a single partial wave that factorizes into a tensor and a parameter dependent complex number and its relationship with fit parameters
/** In GPUPWA a partial wave consits of a orbital part, mOrbitalTensor which should
have the rank required for the PWA performed and whose elements are real. mPropagator
on the other hand is a scalar that is allowed to be complex.
**/
template <typename T>
class GPUFactorizedPartialWave: public GPUPartialWave
{
public:
  /// Constructor
  GPUFactorizedPartialWave(GPUStreamTensor<T> & _orbitalTensor, ///< (Real) orbital tensor, has to have the correct rank for the analysis
		 GPUScalarPropagator & _propagator,      ///< Complex propagator
		 char * _name);                    ///< Name for the wave

  /// Destructor
  virtual ~GPUFactorizedPartialWave(void);

  /// Get the Tensor part
  GPUStreamTensor<T> & GetTensor(){return mOrbitalTensor;};
  /// Get the propagator part
  GPUScalarPropagator & GetPropagator(){return mPropagator;};
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

  /// Contract the parameter independent part of this wave with another one
  virtual GPUDataStream<float> * ContractOrbital(GPUPartialWave * wave, unsigned int index, unsigned int block);

  /// Check whether a wave combination has a parameter independent part
  virtual bool HasContractOrbital(GPUPartialWave * wave);

  /// Increase the Usecount for the caching mechanism
  virtual void IncreaseUsecount(unsigned int index){
	  mOrbitalTensor.IncreaseUsecount(index);
	  mPropagator.IncreaseUsecount(index);
  };

  /// Increase the Usecount for the caching mechanism
  virtual void IncreaseUsecountOrbital(unsigned int index){mOrbitalTensor.IncreaseUsecount(index);};

 protected:
  /// Orbital part of the wave
  GPUStreamTensor<T> & mOrbitalTensor;
  /// Propagator part of the wave
  GPUScalarPropagator & mPropagator;
  /// Name of the wave
  char * mName;
  /// Current active state of the wave
  bool mActive;
};

/// A partial wave with a scalar orbital part
typedef GPUFactorizedPartialWave<float> GPUFactorizedScalarPartialWave;
/// A partial wave with a vector orbital part
typedef GPUFactorizedPartialWave<float4>  GPUFactorizedVectorPartialWave;
/// A partial wave with a tensor2 orbital part
typedef GPUFactorizedPartialWave<float44>  GPUFactorizedTensor2PartialWave;
