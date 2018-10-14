/// \file GPUFitConstraint.h
/*
 * GPUFitConstraint.h
 *
 *  Created on: Apr 22, 2009
 *      Author: nberger
 */

#ifndef GPUFITCONSTRAINT_H_
#define GPUFITCONSTRAINT_H_

#include <string>

using std::string;

class GPUPartialWaveAnalysis;

/// Base Class for defining constraints to fits
/** Abstract interface for additional constraints (likelihood penalty terms) in partial wave analysis fits
 *
 *
 */
class GPUFitConstraint {
public:
	/// Build a constraint belonging to an GPUPartialWaveAnalysis
	GPUFitConstraint(const GPUPartialWaveAnalysis * ana);
	/// Destructor
	virtual ~GPUFitConstraint();
	/// Get the contribution to the likelihood from this constraint
	virtual double operator() () const =0;
	/// Get the contribution to a specific gradient from this constraint
	virtual double gradient(unsigned int parindex) const =0;
	/// Get the contribution to the i,j element of the Hessian matrix (Fumili approx)
	virtual double hessian(unsigned int i, unsigned int j) const =0;
	/// Report the contribution to the likelihood by this constraint
	virtual string report() const  =0;
	/// Describe this constraints
	virtual string describe() const = 0;

protected:
	/// Pointer to mother analysis
	const GPUPartialWaveAnalysis *  const mAna;
};

#endif /* GPUFITCONSTRAINT_H_ */
