/// \file GPUChi2FrFitConstraint.h
/*
 * GPUChi2FrFitConstraint.h
 *
 *  Created on: Dec 1, 2010
 *      Author: liubj
 */

#ifndef GPUCHI2FRFITCONSTRAINT_H_
#define GPUCHI2FRFITCONSTRAINT_H_
#include <vector>
#include "GPUFitConstraint.h"

/// Class implementing a branching fraction fit constraint
/** Constrain the relative branching fractions of two waves
 */
class GPUChi2FrFitConstraint: public GPUFitConstraint {
public:
	/// Constructor
	GPUChi2FrFitConstraint(GPUPartialWaveAnalysis * ana, ///< Partial wave analysis used to look-up parameter values
						const string name,                       /// name of the resonance
						const std::vector<int> waveindex,		///< Index of the waves to be constrained
						const double centralvalue,		   		///< Central value of the ratio
						const double sigma,				  		 ///< Error on the central value
						const double weight = 0.5            	///< Weight with which to enter the chi2 into the likelihood
							);
	/// Destructor
	virtual ~GPUChi2FrFitConstraint();

	/// Get the contribution to the likelihood from this constraint
	virtual double operator() () const;
	/// Get the contribution to a specific gradient from this constraint
	virtual double gradient(unsigned int parindex) const;
	/// Get the contribution to the i,j element of the Hessian matrix (Fumili approx)
	virtual double hessian(unsigned int i, unsigned int j) const;
	/// Report the contribution to the likelihood by this constraint
	virtual string report() const;
	/// Describe this constraints
	virtual string describe() const;




protected:
  /// name of the resonance
  const string mname;
	/// Index of the wave concerned
	const std::vector<int>		 mwaveindex;
	/// Central value of the ratio
	const double	 mcentralvalue;
	/// Error on the central value
	const double 	 msigma;
	/// Inverse squared error on the central value
	const double 	 msig2inv;
	/// Weight with which the chi2 enters the likelihood (usually 0.5)
	const double	 mweight;
};

#endif /* GPUCHI2FRFITCONSTRAINT_H_ */
