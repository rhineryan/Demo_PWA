/*
 * GPUChi2FitConstraint.cpp
 *
 *  Created on: Apr 23, 2009
 *      Author: nberger
 */

#include "GPUChi2FitConstraint.h"
#include "GPUPartialWaveAnalysis.h"
#include <stdio.h>

GPUChi2FitConstraint::GPUChi2FitConstraint(GPUPartialWaveAnalysis * ana,
											const int parindex,
											const double centralvalue,
											const double sigma,
											const double weight): GPUFitConstraint(ana),
																  mparindex(parindex),
																  mcentralvalue(centralvalue),
																  msigma(sigma),
																  msig2inv(1.0/(sigma*sigma)),
																  mweight(weight){}

GPUChi2FitConstraint::~GPUChi2FitConstraint() {

}

double GPUChi2FitConstraint::operator() () const {
	double val = mAna->GetParameter(mparindex);
	double diff = (val-mcentralvalue);

	return diff*diff*mweight*msig2inv;
}

double GPUChi2FitConstraint::gradient(unsigned int parindex) const{
	double val = mAna->GetParameter(mparindex);
	if(parindex != (unsigned int)mparindex)
		return 0;

	return 2.0*mweight*msig2inv*(val-mcentralvalue);

}

/// Get the contribution to the i,j element of the Hessian matrix (Fumili approx)
double GPUChi2FitConstraint::hessian(unsigned int i, unsigned int j) const{
	if(i != j || i != (unsigned int)mparindex)
		return 0;
	double grad =  gradient(i);
	return grad*grad;

}

string GPUChi2FitConstraint::report() const {
	double val = mAna->GetParameter(mparindex);
	double diff = (val-mcentralvalue);
	double lhval = diff*diff*mweight*msig2inv;
	char text[100];
	string rep("The constraint on parameter ");
	rep += mAna->GetParameterName(mparindex);
	rep += " added ";
	sprintf(text,"%f",lhval);
	rep += text;
	rep += " to the likelihood.";
	return rep;
}

string GPUChi2FitConstraint::describe() const{
	char text[100];
	string rep("There is a chi2 constraint on parameter ");
	rep += mAna->GetParameterName(mparindex);
	rep += " with a central vale of ";
	sprintf(text,"%f",mcentralvalue);
	rep += text;
	rep += " and a sigma of ";
	sprintf(text,"%f",msigma);
	rep += text;
	return rep;

}
