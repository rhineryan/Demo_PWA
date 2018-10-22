#include "GPUMinuitFCN.h"

GPUMinuitFCN::GPUMinuitFCN(GPUPWACalculator * _calc): mCalc(_calc)
{
}

GPUMinuitFCN::~GPUMinuitFCN(void)
{
}


vector<double> GPUMinuitFCN::Gradient(const vector<double> & x) const{
	vector<double> a;
	//vector<double> b(100,0);
	mCalc->LikelihoodGradient(x,a);
	//cout << "Grad requested!" << endl;
	return a;
}

double GPUMinuitFCN::operator() (const vector<double> & x) const{
	//vector<double> a;
	//vector<double> b(100,0);
	return mCalc->Likelihood(x);
}


