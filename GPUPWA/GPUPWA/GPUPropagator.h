/// \file GPUPropagator.h
#ifndef GPUPROPAGATOR_H__
#define GPUPROPAGATOR_H__

#include <vector>
#include <cassert>
#include "GPUParameterDependentObject.h"

class GPUPartialWaveAnalysis;

/// Abstarct Base Class for Propagators
/** In GPUPWA, every kind of complex number used in an amplitude is considered a Propagator.
 * This includes "true" propagators such as the GPUPropagatorBreitWigner as well as any object
 * derived from them in a calculation.
**/

class GPUPropagator: public GPUParameterDependentObject
{
public:
	/// Constructor
	GPUPropagator(GPUPartialWaveAnalysis * ana, char * name, std::vector<char **> _parnames, unsigned int npars);
	/// Constructor taking mass and width
	//GPUPropagator(char * name, float _mass, float _width);
	/// Constructor taking mass and with vectors and vectors for the parameters
	GPUPropagator(GPUPartialWaveAnalysis * ana, std::vector<char *> _names,
				std::vector<unsigned int *> _Parameters, std::vector<char **> _parnames);

	/// Destructor
	virtual ~GPUPropagator(void);

	/// Get the resonance mass
	//virtual float const GetMass(){return mMass[0];};
	/// Get the resonance width
	//virtual float const GetWidth(){return mWidth[0];};
	/// Get the nth-resonance mass
	//virtual float const GetMass(unsigned int n){return mMass[n];};
	/// Get the nth-resonance width
	//virtual float const GetWidth(unsigned int n){return mWidth[n];};

	/// Get the resonance mass parameter
	//virtual int const GetParameters(){return mMassParameter[0];};
	/// Get the resonance width parameter
	//virtual int const GetWidthParameter(){return mWidthParameter[0];};
	/// Get the nth-resonance mass parameter
	//virtual int const GetMassParameter(unsigned int n){return mMassParameter[n];};
	/// Get the nth-resonance width parameter
	//irtual int const GetWidthParameter(unsigned int n){return mWidthParameter[n];};


	/// Get the name
	virtual char * const GetName(){return mName[0];};
	/// Get the n-th name
	virtual char * const GetName(unsigned int n){assert(n < mName.size()); return mName[n];};
	/// Get a vector of the names
	virtual std::vector<char *> & GetNames(){return mName;};

	/// Set the resonance mass - invalidates cached values
	//virtual void SetMass(float _m){
	//	invalidateCache();
	//	mMass[0] = _m;
	//};
	///Set the resonance width - invalidates cached values
	//virtual void SetWidth(float _w){
	//	invalidateCache();
	//	mWidth[0] = _w;
	//};
    /// Set the resonance mass and width - invalidates cached values
	//virtual void SetMassAndWidth(float _m, float _w){
	//	invalidateCache();
	//	mMass[0] = _m;
	//	mWidth[0] = _w;
	//};

	/// Get the resonance masses
	//virtual std::vector<float> const GetMasses(){return mMass;};
	/// Get the resonance widths
	//virtual std::vector<float> const GetWidths(){return mWidth;};
	/// Set the resonance masses - invalidates cached values
	//virtual void SetMasses(std::vector<float> _m){
	//	invalidateCache();
	//	mMass = _m;
	//};
	///Set the resonance widths - invalidates cached values
	//virtual void SetWidths(std::vector<float> _w){
	//	invalidateCache();
	//	mWidth = _w;
	//};
	/// Set the resonance mass and width - invalidates cached values
	//virtual void SetMassesAndWidths(std::vector<float> _m, std::vector<float> _w){
	//	invalidateCache();
	//	mMass = _m;
	//	mWidth = _w;
	//};


	/// Set the resonance mass parameter
	//virtual void SetMassParameter(int _m){mMassParameter[0] = _m;};
	///Set the resonance width parameter
	//virtual void SetWidthParameter(int _w){	mWidthParameter[0] = _w;};
	// Set the resonance mass parameter
	//virtual void SetMassParameter(int index, int _m){mMassParameter[0] = _m;};
	///Set the resonance width parameter
	//virtual void SetWidthParameter(int index, int _w){	mWidthParameter[0] = _w;};
	/// Set the resonance mass and width - invalidates cached values
	//virtual void SetMassAndWidth(int _m, int _w){
	//	mMassParameter[0] = _m;
	//	mWidthParameter[0] = _w;
	//};

	/// Get the resonance mass parameters
	//virtual std::vector<int> const GetMassParameters(){return mMassParameter;};
	/// Get the resonance width parameters
	//virtual std::vector<int> const GetWidthParameters(){return mWidthParameter;};
	/// Set the resonance mass parameters
	//virtual void SetMassParameters(std::vector<int> _m){mMassParameter = _m;};
	///Set the resonance width parameters
	//virtual void SetWidthParameters(std::vector<int> _w){mWidthParameter = _w;};
	/// Set the resonance mass and width parameters
	//virtual void SetMassAndWidthParameters(std::vector<int> _m, std::vector<int> _w){
	//	mMassParameter = _m;
	//	mWidthParameter = _w;
	//};



	/// Indicates whether this propagator provides analytical derivaties
	virtual bool HasDerivatives(){ return false;};

	/// True if this is a scalar propagator
	virtual bool isScalar()=0;
	/// True if this is a vector propagator
	virtual bool isVector()=0;
	/// True if this is a rank 2 tensor propagator
	virtual bool isTensor2()=0;
	/// True if this is a rank 3 tensor propagator
	virtual bool isTensor3()=0;
	/// True if this is a rank 4 tensor propagator
	virtual bool isTensor4()=0;

	/// Get a pointer to the partial wave analysis, where this propagator is registered
	GPUPartialWaveAnalysis * GetAnalysis() const {return mana;};

protected:
	/// invalidate the cache on a mass/width change
	//virtual void invalidateCache() = 0;
	/// Ensure mass and with have not changed
	//virtual bool cacheValid(){
	//	int temp = 1;
	//	for(unsigned int i = 0; i < mMass.size(); i++){
	//		temp *= (mMass[i]==mLastMass[i]);
	//		temp *= (mWidth[i]==mLastWidth[i]);
	//	}
	//	return (bool)temp;
	//}

	/// Resonance masses
	//std::vector<float> mMass;
	/// Resonance widths
	//std::vector<float> mWidth;
	/// Resonance masses used for cached calculation
	//std::vector<float> mLastMass;
	/// Resonance widths used for cached Calculation
	//std::vector<float> mLastWidth;
	/// Pointer to the partial wave analysis - needed to read parameters
	GPUPartialWaveAnalysis * mana;
	/// Name(s)
	std::vector<char *> mName;
	/// Mass parameters
	//std::vector<int> mMassParameter;
	/// Width parameters
	//std::vector<int> mWidthParameter;

};

#endif
