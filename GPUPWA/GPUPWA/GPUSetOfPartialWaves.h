/// \file GPUSetOfPartialWaves.h
#pragma once
#include "GPUDataDependentObjectList.h"
#include "GPUPartialWave.h"
//#include "GPUPartialWaveAnalysis.h"
#include <map>

class GPUPartialWaveAnalysis;

/// Class that stores a set of GPUPartialWaves
/**
Ususally, as an user you do not have to create GPUSetOfPartialWaves objects,
this is done for you by your GPUPartialWaveAnalysis
**/
class GPUSetOfPartialWaves :
	public GPUDataDependentObjectList
{
public:
        /// Constructor, registering this list at its mother partial wave analysis
	GPUSetOfPartialWaves(GPUPartialWaveAnalysis * _list);
	/// Destructor
	virtual ~GPUSetOfPartialWaves(void);

	// Handling constituent partial waves
	/// Add a partial wave, returns the number of parameters added to the analysis
	unsigned int AddPartialWave(GPUPartialWave & _wave);
	/// Remove the n-th partial wave
	void RemovePartialWave(int _n);
	/// Remove a partial wave namend _name
	void RemovePartialWave(char * _name);
	/// Get a pointer to the n-th partial wave
	GPUPartialWave * GetPartialWave(int _n) const;
	/// Get a pointer to the n-th partial wave
	GPUPartialWave * operator[](int _n) const {return GetPartialWave(_n);};
	/// Get a pointer to a a partial wave named _name
	GPUPartialWave * GetPartialWave(char * _name) const;
	/// Gety the number of partial wave _name
	int FindPartialWave(char * _name) const;
	/// Set partial wave n to active (used in the fits)
	void SetActive(int _n, bool _active = true);
	/// Set the partial wave n to inactive (not used in fits)
	void SetInactive(int _n);
	/// Set partial wave named name to active (used in the fits)
	void SetActive(char * name, bool _active = true);
	/// Set the partial wave named name to inactive (not used in fits)
	void SetInactive(char * name);
	/// Query status of partial wave n
	bool Active(int _n) const;
	/// Query status of the partial wave named name
	bool Active(char * name) const;

	/// Get number of partial waves in this analysis
	int GetNWaves() const;
	/// Get number of currently active partial waves
	int GetNActiveWaves() const;
	/// Get number of currently inactive partial waves
	int GetNInactiveWaves() const;
	/// Get a a vector of pointers to the partial waves in this analysis
	vector<GPUPartialWave *> GetWaves() const;
	/// Get a a vector of pointers to the active partial waves in this analysis
	vector<GPUPartialWave *> GetActiveWaves() const;
	/// Get a vector of wave names
	std::vector<char *> GetWaveNames() const;
	/// Get a vector of wave names for the active waves
	std::vector<char *> GetActiveWaveNames() const;

	/// Get a vector of the magnitude parameter indices
	std::vector<unsigned int> GetMagnitudeParameters() const;
	/// Get a vector of the phase parameter indices
	std::vector<unsigned int> GetPhaseParameters() const;
	/// Get a vector of the dynamic parameter indices
	std::vector<unsigned int *> GetDynamicParameters() const;
	/// Get a vector of the number of dynamic parameter indices
	std::vector<unsigned int> GetNDynamicParameters() const;
	/// Get a vector of the magnitude parameter indices for active waves
	std::vector<unsigned int> GetActiveMagnitudeParameters() const;
	/// Get a vector of the phase parameter indices for active waves
	std::vector<unsigned int> GetActivePhaseParameters() const;
	/// Get a vector of the dynamic parameter indices for active waves
	std::vector<unsigned int *> GetActiveDynamicParameters() const;
	/// Get a vector of the number of dynamic parameter indices for active waves
	std::vector<unsigned int> GetNActiveDynamicParameters() const;
	/// Get a vector of the dynamic parameter names for active waves
	std::vector<char **> GetActiveDynamicParameterNames() const;

	/// Set the usecounts for cache managment
	void SetUsecount(int index);
	/// Set the usecounts for cache managment; Orbital part only
	void SetUsecountOrbital(int index);

	/// Check whether there is an orbital part available for caching for all the waves contained
	bool HasOrbitalContraction();

	/// Get the associated partial wave analysis
	GPUPartialWaveAnalysis * GetAnalysis(){return mAnalysis;};

protected:
	/// Vector of partial waves
	vector<GPUPartialWave *> mPartialWaves;
	/// Partial wave analysis this set is part of
	GPUPartialWaveAnalysis * mAnalysis;
	/// Map of dynamic parameters
	std::map<std::string, int> mResonanceDynamicParameters;


};

