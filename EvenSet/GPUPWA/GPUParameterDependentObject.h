/// \file GPUParameterDependentObject.h

/*
 * GPUParameterDependentObject.h
 *
 *  Created on: Apr 28, 2011
 *      Author: nberger
 */

#ifndef GPUPARAMETERDEPENDENTOBJECT_H_
#define GPUPARAMETERDEPENDENTOBJECT_H_

#include <vector>
#include <iostream>
#include "Minuit2/MnUserParameters.h"

using std::vector;
using std::cout;
using std::endl;

/// Class representing and object that depends on fit parameters
/*** Implements the parameter handling and provides functionality to check whether cached values
 *   are still valid.
 *
 */
class GPUParameterDependentObject {
public:
	/// Constructor with not yet assigned parameters
	GPUParameterDependentObject(ROOT::Minuit2::MnUserParameters * pars, ///< Set of parameters used in the fit
								vector<char **>  parnames,              ///< Names of the parameters in this object
								unsigned int npars,						///< Number of parameters in this object
								unsigned int nsets);                    ///< Number of sets (Data/MC)
	GPUParameterDependentObject(ROOT::Minuit2::MnUserParameters * pars, ///< Set of parameters used in the fit
								vector<unsigned int *> indices, 		///< Indices of the parameters in this object
								vector<char **>  parnames,				///< Number of parameters in this object
								unsigned int nsets);				    ///< Number of sets (Data/MC)
	/// Destructor
	virtual ~GPUParameterDependentObject();

	/// Get the (global) indices of the parameters in this object
	virtual const vector<unsigned int *> & GetParameters() const {return mparindices;};

	/// Set the (global) indices of the parameters in this object
	virtual void SetParameters(vector<unsigned int *> pars){
		mparindices = pars;
		mlastvalues = vector<vector<double *> > ();
		for(unsigned int s=0; s < mnsets; s++){
			mlastvalues.push_back(vector<double *>(mparindices.size(), new double));
			for (unsigned int i=0; i < mparindices.size(); i++)
				*(mlastvalues[s][i]) = -9.999e9;
		}
	};

	/// Set the (global) index of a parameter in this object
	virtual void SetParameter(unsigned int index, unsigned int parindex){
		assert(index < mparindices.size());
		*(mparindices[index]) = parindex;
		for(unsigned int s=0; s < mnsets; s++)
			*(mlastvalues[s][index]) = -9.999e9;
		//cout << "In SetParameter() for index " <<  index << " " << mlastvalues[index] << endl;
	}

	/// Get the (global) index of a parameter in this object
	virtual unsigned int GetParameter(unsigned int index) const {return *(mparindices[index]);};

	/// Get the current value of a parameter using its local index
	virtual double GetParameterValue(unsigned int index) const {return mParameters->Value(*(mparindices[index]));};

	/// Get the number of parameters in this object
	virtual unsigned int GetNPars() const {return mparindices.size();};

	/// Check whether the cache is valid
	virtual bool CacheValid(unsigned int index) const{
		bool valid = true;
		//cout << "In CacheValid()" << endl;
		for(unsigned int i =0; i < mparindices.size(); i++){
			valid = valid && *(mlastvalues[index][i]) == mParameters->Value(*(mparindices[i]));
			//if(!valid)
			//	cout << *(mparindices[i]) << " : " << *(mlastvalues[i]) << " : " << mParameters->Value(*(mparindices[i])) << endl;
		}
		return valid;
	};

	/// Set the cache to invalid
	virtual void InvalidateCache(){
		for(unsigned int s=0; s < mnsets; s++){
			for(unsigned int i =0; i < mparindices.size(); i++){
				*(mlastvalues[s][i]) = -9.999e9;
			}
		}
	}

	/// Set the cache to invalid
	virtual void InvalidateCache(unsigned int index){
		for(unsigned int i =0; i < mparindices.size(); i++){
			*(mlastvalues[index][i]) = -9.999e9;
		}
	}


	/// Set the cache to valid
	virtual void ValidateCache(){
		//cout << "In ValidateCache()" << endl;
		for(unsigned int s=0; s < mnsets; s++){
			for(unsigned int i =0; i < mparindices.size(); i++){
				*(mlastvalues[s][i]) = mParameters->Value(*(mparindices[i]));
				//cout << *(mlastvalues[i]) << " : " << mParameters->Value(*(mparindices[i])) << endl;
			}
		}
	}

	/// Set the cache to valid
	virtual void ValidateCache(unsigned int index){
		//cout << "In ValidateCache()" << endl;
		for(unsigned int i =0; i < mparindices.size(); i++){
			*(mlastvalues[index][i]) = mParameters->Value(*(mparindices[i]));
			//cout << *(mlastvalues[i]) << " : " << mParameters->Value(*(mparindices[i])) << endl;
		}
	}

	/// Set the value used for cache checking at a local index to value
	virtual void SetLastValue(unsigned int index, unsigned int parindex, double value){
		*(mlastvalues[index][parindex]) = value;
	}

	/// Set the values used for cache checking
	virtual void SetLastValues(unsigned int index, vector<double *> & vals){
		mlastvalues[index] = vals;
	}

	/// Get the values used for cache checking
	virtual vector<double *> & GetLastValues(unsigned int index) {
		return mlastvalues[index];
	}

	/// Get the name of a parameter at local index
	virtual char * GetParameterName(unsigned int index) const {return *(mparnames[index]);};

	/// Get the names of all parameters
	virtual vector<char**> & GetParameterNames() {return  mparnames;};

	/// Get the associated set of parameters
	virtual ROOT::Minuit2::MnUserParameters * GetParset() const {return mParameters;};

protected:
	/// The global parameter set
	ROOT::Minuit2::MnUserParameters * mParameters;
	/// Pointers to the global indices of the parameters in this object
	vector<unsigned int *> mparindices;
	/// Pointers to the names of the parameters in this object
	vector<char **>       mparnames;
	/// Pointers to values used for cache checking
	vector<vector<double *> >       mlastvalues;
	/// Number of sets (Data/MC)
	const unsigned int mnsets;
};

#endif /* GPUPARAMETERDEPENDENTOBJECT_H_ */
