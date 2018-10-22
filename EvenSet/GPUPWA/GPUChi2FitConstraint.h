/// \file GPUChi2FitConstraint.h
/*
 * GPUChi2FitConstraint.h
 *
 *  Created on: Apr 23, 2009
 *      Author: nberger
 */

#ifndef GPUCHI2FITCONSTRAINT_H_
#define GPUCHI2FITCONSTRAINT_H_

#include "GPUFitConstraint.h"

/// Class implementing a Chi 2 fit constraint
/** Add a chi2 constraint to a PWA fit, e.g. for the case where the mass of a resonance is
 *  approximately known with some error and this knowledge should enter the fit.
 */
class GPUChi2FitConstraint: public GPUFitConstraint {
public:
	/// Constructor
	GPUChi2FitConstraint(GPUPartialWaveAnalysis * ana, ///< Partial wave analysis used to look-up parameter values
						const int parindex,				   ///< Index of the parameter to be constrained
						const double centralvalue,		   ///< Central value of the parameter
						const double sigma,				   ///< Error on the central value
						const double weight = 0.5            ///< Weight with which to enter the chi2 into the likelihood
							);
	/// Destructor
	virtual ~GPUChi2FitConstraint();

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
	/// Index of the parameter concerned
	const int		 mparindex;
	/// Central value of the parameter
	const double	 mcentralvalue;
	/// Error on the central value
	const double 	 msigma;
	/// Inverse squared error on the central value
	const double 	 msig2inv;
	/// Weight with which the chi2 enters the likelihood (usually 0.5)
	const double	 mweight;
};

#endif /* GPUCHI2FITCONSTRAINT_H_ */
