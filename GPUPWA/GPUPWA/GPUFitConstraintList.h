/// \file GPUFitConstraintList.h
/*
 * GPUFitConstraintList.h
 *
 *  Created on: Apr 22, 2009
 *      Author: nberger
 */

#ifndef GPUFITCONSTRAINTLIST_H_
#define GPUFITCONSTRAINTLIST_H_

#include <vector>
#include <cassert>
#include <iostream>

class GPUFitConstraint;


/// A List of fit constraints with options to manipulate them
/** This function object serves as a container for fit constraints
 *  (likelihood penalties). The () operator will return the summed
 *  penalty.
 *
 */

class GPUFitConstraintList {
public:
	/// Construct an empty list
	GPUFitConstraintList();
	/// Destructor
	virtual ~GPUFitConstraintList();
	/// Calculate the likelihood penalty from all the constraints in the list
	virtual double operator() () const;
	/// Calculate the gradient of the likelihood penalty with regard to a certain parameter index
	virtual double gradient(unsigned int index) const;
	/// Get the contribution to the i,j element of the Hessian matrix (Fumili approx)
	virtual double hessian(unsigned int i, unsigned int j) const;
	/// Have all the constraints in the list report their contribution to the likelihood
	virtual void report(std::ostream & outstream) const;
	/// Have all the constraints in the list descrieb themselves
	virtual void describe(std::ostream & outstream) const;
	/// Add a constraint
	virtual void AddConstraint(GPUFitConstraint * constraint){
		assert(constraint);
		mConstraints.push_back(constraint);
	}
	/// Remove a constraint
	virtual void RemoveConstraint(unsigned int index){
		if(index < mConstraints.size()){
			std::vector<GPUFitConstraint *>::iterator it = mConstraints.begin();
			for(unsigned int i =0; i < index; i++)
				it++;
			mConstraints.erase(it);
		}
	}
	/// Get a constraint
	virtual GPUFitConstraint* GetConstraint(unsigned int index) const{
		assert(index < mConstraints.size());
		return mConstraints[index];
	}


protected:
	/// The actual list of constraints
	std::vector<GPUFitConstraint *> mConstraints;
};

#endif /* GPUFITCONSTRAINTLIST_H_ */
