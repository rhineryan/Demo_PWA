/*
 * GPUMinimizationHistory.cpp
 *
 *  Created on: Dec 2, 2008
 *      Author: nberger
 */

#include "GPUMinimizationHistory.h"
#include "GPUPartialWaveAnalysis.h"
#include <iomanip>

using std::setw;


GPUMinimizationHistory::GPUMinimizationHistory(GPUPartialWaveAnalysis* ana,
		   const ROOT::Minuit2::MnUserParameters _InputParameters,
		   const ROOT::Minuit2::MnUserParameters _ResultParameters,
		   const double minimumLikelihood,
		   const double EDM, const bool OK, const int iterations):
	mana(ana), m_InputParameters(_InputParameters), m_ResultParameters(_ResultParameters),
	m_minimumLikelihood(minimumLikelihood), mEDM(EDM), mOK(OK), mNiterations(iterations)
{
	mWaveNames = mana->GetActiveWaveNames();
	mMagnitudeParameters = mana->GetActiveMagnitudeParameters();
	mPhaseParameters = mana->GetActivePhaseParameters();
	mDynamicParameters = mana->GetActiveDynamicParameters();
	mNDynamicParameters = mana->GetNActiveDynamicParameters();
}

GPUMinimizationHistory::~GPUMinimizationHistory() {

}

void GPUMinimizationHistory::Print(ostream & out){
	PrintAnalysis(out);
	PrintFitInfo(out);
	PrintWaves(out);
//	PrintInput(out);
//	PrintResult(out);
//add by lixl 
//	PrintInputRes(out);
//	PrintOutputRes(out);
//	PrintInputPara(out);
	PrintOutputPara(out);
	out << "************************************************************" << endl;
}

void GPUMinimizationHistory::PrintFitInfo(ostream & out) const{
	out << "************************************************************" << endl;
	if(mOK)
		out << "       Fit coverged" << endl;
	else
		out << "       Fit failed" << endl;
	out << endl;
	out << "       Minimum Likelihood: " << m_minimumLikelihood << endl;
	out << endl;
	out << "       Estimated Distance to Minimum: "<< mEDM << endl;
	out << endl;
	if(mNiterations){
		out << "       Obtained in "<< mNiterations << " iterations." << endl;
		out << endl;
	}

}

void GPUMinimizationHistory::PrintAnalysis(ostream & out){
	out << "************************************************************" << endl;
	out << mana->GetName() << endl;
	out << "With " << setw(10) << mana->GetNumberData() << " Data Events," << endl;
	out << "     " << setw(10) << mana->GetNumberMCGen() << " Generated MC Events and" << endl;
	out << "     " << setw(10) << mana->GetNumberMCAcc() << " Accepted MC Events." << endl;
}

void GPUMinimizationHistory::PrintWaves(ostream & out) const{
	out << "************************************************************" << endl;
	out << mana->GetName() << endl;
	out << "Using the following partial waves: " << endl;
	out << setw(20) << "Wave Name"
		<< setw(10) << "Magn. in"
		<< setw(10) << "Magn. out"
		<< setw(10) << "Phase in"
		<< setw(10) << "Phase out"
		<< setw(10) << "Dynamic in"
		<< setw(10) << "Dynamic out"
		<< setw(10) << "Dynamic in"
		<< setw(10) << "Dynamic out" << endl;
	out << "______________________________________________________________"
	<< "_______________________________________________" << endl;
	unsigned int dynparindex =0;
	for(int i=0; i < (int)mWaveNames.size(); i++){
		out << setw(20) << mWaveNames[i]

		    << setw(10) <<  m_InputParameters.Value(mMagnitudeParameters[i]);
		if(m_InputParameters.Parameter(mMagnitudeParameters[i]).IsFixed())
			out << setw(10) << "(fixed)";
		else
			out << setw(10) <<  m_ResultParameters.Value(mMagnitudeParameters[i]);

		out << setw(10) <<  m_InputParameters.Value(mPhaseParameters[i]);
		if(m_InputParameters.Parameter(mPhaseParameters[i]).IsFixed())
			out << setw(10) << "(fixed)";
		else
			out << setw(10) <<  m_ResultParameters.Value(mPhaseParameters[i]);

		for(unsigned int n=0; n < mNDynamicParameters[i]; n++){
			out << setw(10) <<  m_InputParameters.Value(*(mDynamicParameters[dynparindex]));
			if(m_InputParameters.Parameter(*(mDynamicParameters[dynparindex])).IsFixed())
				out << setw(10) << "(fixed)";
			else
				out << setw(10) <<  m_ResultParameters.Value(*(mDynamicParameters[dynparindex]));
			dynparindex++;
		}
		out << endl;
	}
	out << "______________________________________________________________"
	<< "_______________________________________________" <<  endl;
}

void GPUMinimizationHistory::PrintParameters(ROOT::Minuit2::MnUserParameters pars, ostream & out) const{
	vector<double> pvec = pars.Params();
	for(int i=0; i < (int)pvec.size(); i++){
		out << setw(2) <<  i << ":   " << setw(15) << pars.Name(i) << ": " << setw(10) <<pvec[i] << " +- " << setw(10) << pars.Error(i) << endl;
	}
}

void GPUMinimizationHistory::PrintInput(ostream & out) const{
	out << "************************************************************" << endl;
	out << "Input Parameters used: " << endl;
	PrintParameters(m_InputParameters, out);
}

void GPUMinimizationHistory::PrintResult(ostream & out) const{
	out << "************************************************************" << endl;
	out << "Fitted Parameters obtained: " << endl;
	PrintParameters(m_ResultParameters, out);
}

// add by lixl
void GPUMinimizationHistory::PrintParaParameters(ROOT::Minuit2::MnUserParameters pars, ostream & out) const{
	vector<double> pvec = pars.Params();
	out << setw(15) << pars.Name(0) << " = " << setw(10) <<pvec[0] << "  " << setw(10) << pars.Error(0) << "  0       500   "<< endl;
	for(int i=0; i < (int)mWaveNames.size(); i++){
		out << setw(15) << pars.Name(mMagnitudeParameters[i]) << " = " << setw(10) <<pvec[mMagnitudeParameters[i]] << "  " << setw(10) << pars.Error(mMagnitudeParameters[i])<<"   "<<(pars.Parameter(mMagnitudeParameters[i])).LowerLimit()<<"   "<<(pars.Parameter(mMagnitudeParameters[i])).UpperLimit()<<endl;// << "  0       500   "<< endl;
		out << setw(15) << pars.Name(mPhaseParameters[i]) << " = " << setw(10) <<pvec[mPhaseParameters[i]] << "  " << setw(10) << pars.Error(mPhaseParameters[i]) <<"   "<<(pars.Parameter(mPhaseParameters[i])).LowerLimit()<<"   "<<(pars.Parameter(mPhaseParameters[i])).UpperLimit()<<endl;//<< " -3.1416 +3.1416  "<< endl;
	}


	/*for(int i=0; i < (int)pvec.size(); i++){
           if (i==0 ) {
		out << setw(15) << pars.Name(i) << " = " << setw(10) <<pvec[i] << "  " << setw(10) << pars.Error(i) << "  0       500   "<< endl;
           }else
           if (fmod(i,4)==1 ) { 
		out << setw(15) << pars.Name(i) << " = " << setw(10) <<pvec[i] << "  " << setw(10) << pars.Error(i) << "  0       500   "<< endl;
	   }
           if (fmod(i,4)==2 ) {
                out << setw(15) << pars.Name(i) << " = " << setw(10) <<pvec[i] << "  " << setw(10) << pars.Error(i) << " -3.1416 +3.1416  "<< endl;
           }
         }*/
}
 
void GPUMinimizationHistory::PrintResParameters(ROOT::Minuit2::MnUserParameters pars, ostream & out) const{
	vector<double> pvec = pars.Params();
	for(int i=1; i < (int)pvec.size(); i++){
           if (fmod(i,4)==3 ) { 
               out << setw(15) << pars.Name(i) << " = " << setw(10) <<pvec[i] << " " << setw(10) << pvec[i+1]  << "     1" << endl;
           }
        }
}


void GPUMinimizationHistory::PrintInputRes(ostream & out) const{
	out << "************************************************************" << endl;
	out << "******************** Input res.inp *************************" << endl;
	PrintResParameters(m_InputParameters, out);
}


void GPUMinimizationHistory::PrintOutputRes(ostream & out) const{
	out << "************************************************************" << endl;
	out << "******************** Output res.inp *************************" << endl;
	PrintResParameters(m_ResultParameters, out);
}


void GPUMinimizationHistory::PrintInputPara(ostream & out) const{
	out << "************************************************************" << endl;
	out << "******************** Input para.inp *************************" << endl;
	PrintParaParameters(m_InputParameters, out);
}


void GPUMinimizationHistory::PrintOutputPara(ostream & out) const{
	out << "************************************************************" << endl;
	out << "******************** Output para.inp *************************" << endl;
	PrintParaParameters(m_ResultParameters, out);
}


