/*
 * GPUChi2FrFitConstraint.cpp
 *
 *  Created on: Dec 1, 2010
 *      Author: liubj
 */

#include "GPUChi2FrFitConstraint.h"
#include "GPUPartialWaveAnalysis.h"
#include <stdio.h>

GPUChi2FrFitConstraint::GPUChi2FrFitConstraint(GPUPartialWaveAnalysis * ana,
                      const string name,
											const std::vector<int> waveindex,
											const double centralvalue,
											const double sigma,
											const double weight): GPUFitConstraint(ana),
                                  mname(name),
																  mwaveindex(waveindex),
																  mcentralvalue(centralvalue),
																  msigma(sigma),
																  msig2inv(1.0/(sigma*sigma)),
																  mweight(weight){}

GPUChi2FrFitConstraint::~GPUChi2FrFitConstraint() {

}

double GPUChi2FrFitConstraint::operator() () const {
//double val = mAna->GetParameter(mparindex);
  //mAna->InitCalculator();
  int nactwave=mAna->GetNActivePartialWaves();
  double** ptx=mAna->GetPartialTotalXSection();

  double val=0;
  for(int i=0;i<(int)mwaveindex.size();i++){
    for(int j=i;j<(int)mwaveindex.size();j++){
            val+=ptx[mwaveindex[i]][mwaveindex[j]]/ptx[1][nactwave];
    }
  }
  double diff = (val-mcentralvalue);
  
  return diff*diff*mweight*msig2inv;
}

double GPUChi2FrFitConstraint::gradient(unsigned int parindex) const{
// 	double val = mAna->GetParameter(mparindex);
// 	if(parindex != (unsigned int)mparindex)
// 		return 0;

// 	return 2.0*mweight*msig2inv*(val-mcentralvalue);
  int nactwave=mAna->GetNActivePartialWaves();
  double** ptx=mAna->GetPartialTotalXSection();
  double** ptxd=mAna->GetPartialTotalXSectionDerivative(parindex);
  
  double val=0; 
  for(int i=0;i<(int)mwaveindex.size();i++)
          for(int j=i;j<(int)mwaveindex.size();j++)
                      val+=ptx[mwaveindex[i]][mwaveindex[j]]/ptx[1][nactwave];

  double grad=0;
  for(int i=0;i<(int)mwaveindex.size();i++)
              for(int j=i;j<(int)mwaveindex.size();j++)
                grad+=(ptxd[mwaveindex[i]][mwaveindex[j]]*ptx[1][nactwave]-ptx[mwaveindex[i]][mwaveindex[j]]*ptxd[0][nactwave]);
  return 2.0*mweight*msig2inv*(val-mcentralvalue)*grad/(ptx[0][nactwave]*ptx[0][nactwave]);
}

/// Get the contribution to the i,j element of the Hessian matrix (Fumili approx)
double GPUChi2FrFitConstraint::hessian(unsigned int i, unsigned int j) const{
// 	if(i != j || i != (unsigned int)mparindex)
// 		return 0;
// 	double grad =  gradient(i);
 	return gradient(i)*gradient(j);
  return 0;
}

string GPUChi2FrFitConstraint::report() const {
  //	double val = mAna->GetParameter(mparindex);
  //mAna->InitCalculator();
  double** ptx=mAna->GetPartialTotalXSection();
  double val =ptx[3][3]/ptx[1][4];	
  double diff = (val-mcentralvalue);
	double lhval = diff*diff*mweight*msig2inv;
	char text[100];
	string rep("The constraint on ratio ");
	rep += mname;
	rep += " added ";
	sprintf(text,"%f",lhval);
	rep += text;
	rep += " to the likelihood.";
	return rep;
}

string GPUChi2FrFitConstraint::describe() const{
	char text[100];
	string rep("There is a chi2 constraint on ratio ");
	rep += mname;
	rep += " with a central vale of ";
	sprintf(text,"%f",mcentralvalue);
	rep += text;
	rep += " and a sigma of ";
	sprintf(text,"%f",msigma);
	rep += text;
	return rep;

}
