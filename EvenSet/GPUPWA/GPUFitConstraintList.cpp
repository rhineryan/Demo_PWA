/*
 * GPUFitConstraintList.cpp
 *
 *  Created on: Apr 22, 2009
 *      Author: nberger
 */

#include "GPUFitConstraintList.h"
#include "GPUFitConstraint.h"

using std::endl;

GPUFitConstraintList::GPUFitConstraintList() {

}

GPUFitConstraintList::~GPUFitConstraintList() {
}

double GPUFitConstraintList::operator ()() const{
	double result = 0.0;
	std::vector<GPUFitConstraint *>::const_iterator it = mConstraints.begin();
	for(; it < mConstraints.end(); it++){
		result += (*it)->operator()();
	}
	return result;
}

double GPUFitConstraintList::gradient(unsigned int index) const{
	double result = 0.0;
	std::vector<GPUFitConstraint *>::const_iterator it = mConstraints.begin();
	for(; it < mConstraints.end(); it++){
		result += (*it)->gradient(index);
	}
	return result;
}

double GPUFitConstraintList::hessian(unsigned int i, unsigned int j) const{
	double result = 0.0;
	std::vector<GPUFitConstraint *>::const_iterator it = mConstraints.begin();
	for(; it < mConstraints.end(); it++){
		result += (*it)->hessian(i,j);
	}
	return result;
}



void GPUFitConstraintList::describe(std::ostream & out) const{
	if(mConstraints.size()== 0){
		out << "No additional constraints were applied" << endl;
		return;
	}
	if(mConstraints.size()== 1){
		out << "The following constraint was applied: "<< endl;
		out << mConstraints[0]->describe() << endl;
		return;
	}
	out << "The following constraints were applied: "<< endl;
	std::vector<GPUFitConstraint *>::const_iterator it = mConstraints.begin();
	for(; it < mConstraints.end(); it++){
		out << (*it)->describe() << endl;
	}
}

void GPUFitConstraintList::report(std::ostream & out) const{
	if(mConstraints.size()== 0){
		out << "No additional constraints were applied" << endl;
		return;
	}
	if(mConstraints.size()== 1){
		out << "The following constraint contributed to the likelihood: "<< endl;
		out << mConstraints[0]->report() << endl;
		return;
	}
	out << "The following constraints contributed to the likelihood: "<< endl;
	std::vector<GPUFitConstraint *>::const_iterator it = mConstraints.begin();
	for(; it < mConstraints.end(); it++){
		out << (*it)->report() << endl;
	}
}
