/// GammaKK.cpp : Example partial wave analysis
/**
Example analysis for the channel J/psi -> gamma KK
Created by Liu Beijiang and Nik Berger
For Questions, please contact nberger@ihep.ac.cn
**/
//

// Include some headers from the GPUPWA package
// -> should we reduce this to a single header?
#include "../GPUPWA/GPUStreamTensor.h"
#include "../GPUPWA/GPUComputedTensor.h"
#include "../GPUPWA/GPUPartialWave.h"
#include "../GPUPWA/GPUMetricTensor.h"
#include "../GPUPWA/GPUOrbitalTensors.h"
#include "../GPUPWA/GPUPropagatorBreitWigner.h"
#include "../GPUPWA/GPUPropagatorMassDependentBreitWigner.h"
#include "../GPUPWA/GPUFactorizedRadiativePartialWave.h"
#include "../GPUPWA/GPUPartialWaveAnalysis.h"
#include "../GPUPWA/GPUPWAAmplitudeCalculator.h"
#include "../GPUPWA/GPUStreamInputVector.h"
#include "../GPUPWA/GPUStreamInputRootFileVector.h"
#include "../GPUPWA/GPUStreamInputTextFileVector.h"
#include "../GPUPWA/GPUPlotset.h"
#include "../GPUPWA/ConfigFile.h"
#include "../GPUPWA/ParaCfg.h"
#include "../GPUPWA/ResCfg.h"
#include "../GPUPWA/GPUChi2FitConstraint.h"
#include "../GPUPWA/GPUDynamicalFunctionPVector.h"
// We also need some stuff from root
#include "TFile.h"
#include "TRandom3.h"

// And some general C/C++ stuff
#include <ctime>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

#define FIT
#define PLOT

// Main program, can be called without any arguments
int main(int argc, char* argv[])
{
	// We will want to do some timing measurements, thus start the clock
	clock_t start = clock();

	// Say Hello to our user
	cout << "Gamma KK partial wave analysis huaning ni!" << endl << endl;;

	// First, we read masses and widths of resonances from a configuation file
/*	ConfigFile resconfig( "res.inp" );
	// Values can be read from the file by name
	ResCfg res_f2;
	resconfig.readInto(res_f2 , "f2" );
	cout << "f2 mass width " << res_f2 << endl;
	ResCfg res_f0;
	resconfig.readInto(res_f0 , "f0" );
	cout << "f0 mass width " << res_f0 << endl;
	ResCfg res_f4;
	resconfig.readInto(res_f4 , "f4" );
	cout << "f4 mass width " << res_f4 << endl;*/

	/* And now we read the inital values, error estimates and limits of the fit
	parameters from another configuration file */
/*	ConfigFile paraconfig( "para.inp" );
	ParaCfg mag_f0,phase_f0;
	ParaCfg mag_f20,phase_f20, mag_f21,phase_f21,mag_f22,phase_f22;
	ParaCfg mag_f40,phase_f40, mag_f41,phase_f41,mag_f42,phase_f42;
	ParaCfg mag_bg;
    /// ......
	paraconfig.readInto(mag_f0, "f0_mag");
	paraconfig.readInto(phase_f0, "f0_phase");
	cout << "f0 mag " << mag_f0 << endl;
	cout << "f0 phase " << phase_f0 << endl;
	/// ......
	paraconfig.readInto(mag_f20, "f20_mag");
	paraconfig.readInto(phase_f20, "f20_phase");
	cout << "f20 mag " << mag_f20 << endl;
	cout << "f20 phase " << phase_f20 << endl;
	/// ......
	paraconfig.readInto(mag_f21, "f21_mag");
	paraconfig.readInto(phase_f21, "f21_phase");
	cout << "f21 mag " << mag_f21 << endl;
	cout << "f21 phase " << phase_f21 << endl;
	/// ......
	paraconfig.readInto(mag_f22, "f22_mag");
	paraconfig.readInto(phase_f22, "f22_phase");
	cout << "f22 mag " << mag_f22 << endl;
	cout << "f22 phase " << phase_f22 << endl;
		/// ......
	paraconfig.readInto(mag_f40, "f40_mag");
	paraconfig.readInto(phase_f40, "f40_phase");
	cout << "f40 mag " << mag_f40 << endl;
	cout << "f40 phase " << phase_f40 << endl;
	/// ......
	paraconfig.readInto(mag_f41, "f41_mag");
	paraconfig.readInto(phase_f41, "f41_phase");
	cout << "f41 mag " << mag_f41 << endl;
	cout << "f41 phase " << phase_f41 << endl;
	/// ......
	paraconfig.readInto(mag_f42, "f42_mag");
	paraconfig.readInto(phase_f42, "f42_phase");
	cout << "f42 mag " << mag_f42 << endl;
	cout << "f42 phase " << phase_f42 << endl;
    /// ......
	paraconfig.readInto(mag_bg, "bg_mag");
	cout << "bg mag " << mag_bg << endl;*/

	// -> To be done: Reading of input filenames from configuration files


	/* Here we start: Creat a GPU Partial Wave Analysis Object, in this case we are looking at a radiative decay to mesons,
	so it is a Radiative Meson Partial Wave Analysis. The type of the analysis determines the Rank of the orbital Tensors
	and the contraction of amplitudes. As parameters we give a name and the number of file types we want to use (in this case
	2, namely data and the phase space Monte Carlo. If you need additional input, e.g. different MC for systematic studies,
	increase that number */
	GPUPartialWaveAnalysis * myanalysis = new GPUPartialWaveAnalysis("Free Gamma KK Analysis","files_km.txt",2);


	// For now we will store and use MC at index 1
	myanalysis->SetMCIndex(1);





	// Next we will start building up the partial wave amplitudes from the particle momenta

	/* Convention used: Vectors (lower index) start in small letters, Covectors (upper index) with capitals
	For Tensors, the indices are given (T_mn), again capitals for upper indices, small letters for lower indices
	The metric Tensor stays the same, so is always called g */

	/* Note that all the following statements will not read files or perform calculations. They merey set up a framework such
	that as soon as some calculated quantity is needed, it can be computed using the power of the GPU */

	// Input: Four vectors of the two Kaons

	/* Here we create two GPUStreamInputRootFileVectors. The constructor takes the following arguments: The GPUPartialWaveAnalysis
	they will be used in. This is needed for the caching mechanism to work. Then we give the name of the root file for the data,
	the name of the root tree and the names of the branches in the tree conatining the momentum compnents and the energy.
	Alternatively, text files can be used*/
	//	GPUStreamInputRootFileVector & k_plus = * new GPUStreamInputRootFileVector(myanalysis,"data/zeroplustwoplus_data_50k_01.root", "t","px1","py1","pz1","E1");
	//	GPUStreamInputRootFileVector & k_minus = * new GPUStreamInputRootFileVector(myanalysis,"data/zeroplustwoplus_data_50k_01.root", "t","px2","py2","pz2","E2");
		GPUStreamInputRootFileVector & k_plus = * new GPUStreamInputRootFileVector(myanalysis,myanalysis->GetDataFile(), "t","px1","py1","pz1","E1");
		GPUStreamInputRootFileVector & k_minus = * new GPUStreamInputRootFileVector(myanalysis,myanalysis->GetDataFile(), "t","px2","py2","pz2","E2");
	//GPUStreamInputRootFileVector & k_plus = * new GPUStreamInputRootFileVector(myanalysis,"data/real2-20k.root", "t","px1","py1","pz1","E1");
	//GPUStreamInputRootFileVector & k_minus = * new GPUStreamInputRootFileVector(myanalysis,"data/real2-20k.root", "t","px2","py2","pz2","E2");

	/* Add the filenames for the MC information (it is assumed it is saved at the same location in the trees as for the data.
	If you have additional files e.g. for systmeatics, just add them with a higher index */
	k_plus.SetFilename(myanalysis->GetMCFile(),myanalysis->GetMCIndex());
	k_minus.SetFilename(myanalysis->GetMCFile(),myanalysis->GetMCIndex());
	//k_plus.SetFilename("data/mc.root",1);
	//k_minus.SetFilename("data/mc.root",1);

	// -> To do: Set Filenames from config files

	/* We can use weights for the data events, e.g. to do a background subtraction. Here we just set the weights to 1 for all
	data used*/
	myanalysis->SetEventWeights(1);

	// Set the number of generated MC events; this is just a normalisation constant
	// - here we assume that all MC events have been accepted
	myanalysis->SetNumberMCGen(myanalysis->GetNumberMCAcc());


	// Let's do some calculations

	// First some constant ingredients: The metric Tensor g_mu_nu (we use a -1,-1,-1,1 metric)
	GPUMetricTensor & g = * new GPUMetricTensor();
	//GPUMetricTensor g();
	// And the four-vector of the J/psi...
	float4 f_jpsi = mfloat4(0.0f,0.0f,0.0f,3.0969f);
	// ... in covariant ...
	GPUConstVector & jpsi = * new GPUConstVector(f_jpsi);
	// ... and contravariant form - in this case, the two vectors should be identical ...
	GPUConstVector & Jpsi = moveindex(jpsi);

	// Four-Vector of the intermediate resonance x
	GPUStreamVector & x = k_plus + k_minus;

	// the rest of the momentum and energy is in the photon
	GPUStreamVector & gamma = jpsi - x;
	// and again the contravariant form
	GPUStreamVector & Gamma = moveindex(gamma);

	// We use the '|' charcter to denote contratctions - in the case of 4-vectors such as here, this is the scalar product
	GPUStreamScalar & x2 = x|x;
	// ... and the square root of it is the mass of the intermediate state
	GPUStreamScalar & mX = sqrt(x2);
	// and here we contract the gamma and x four-vectors
	GPUStreamScalar & xgamma = x|gamma;

	// Prepare the g_perp_perp Tensor used in the contratctions
	GPUStreamTensor2 & gPerpPerp_mn = g - (gamma%x +x%gamma)/(xgamma) + x2/(xgamma|xgamma)*(gamma%gamma);


	/* Next we create two GPUOrbitalTensors objects. As it is rather tedious to calculate orbital tensors
	from the momenta, we do this for you. Again, you need to give the analysis object in order for the
	caching to work and in addition the four-momenta of the mother- and the two daughter particles.
	Here we expect the lower index (covariant) vectors*/
	// Orbital tensors for x -> K+K-
	//GPUOrbitalTensors & xorbitals = * new GPUOrbitalTensors(myanalysis, x, k_plus, k_minus);
	GPUOrbitalTensors xorbitals(myanalysis, x, k_plus, k_minus);
	// Orbital tensors for J/psi -> gamma x
	GPUOrbitalTensors & jpsiorbitals =*  new GPUOrbitalTensors(myanalysis, jpsi, gamma, x);

	// Orbital tensors; for f0 we just have the metric tensor
	/* Here we have to cheat a little in order to create a stream object (with a value for every event)
	from the constant metric tensor - so we just create a stream that is one for all events...*/
	GPUStreamScalar & one = *new GPUStreamScalar(myanalysis,1.0f);
	GPUStreamTensor2 & Orbital_f0_MN = g * one;
	//Orbital_f0_MN.Print();

	// Orbital tensors: three independent ones for f2s
	// Here we get the orbital tensor from the xorbitals object
	GPUStreamTensor2 &  t2_mn = xorbitals.Spin2OrbitalTensor();
	// And do some index lowering and raising gymnastics
	GPUStreamTensor2 &  t2_MN = moveindices(t2_mn);
	GPUStreamTensor2 &  t2_mN = movelastindex(t2_mn);
	GPUStreamTensor2 &  t2_Nm = trans(t2_mN);

	// The orbital tensor object also conveniently provides barrier factors
	GPUStreamScalar & B2_psi_gamma_f2 = jpsiorbitals.Barrier2();

	// so we end up with the complete orbital part of the amplitudes
	GPUStreamTensor2 & Orbital_f2_0_MN = t2_mn;
	GPUStreamTensor2 & Orbital_f2_1_MN = -g * (((Jpsi%Jpsi)|t2_mn )* B2_psi_gamma_f2);
	GPUStreamTensor2 & Orbital_f2_2_MN = (Gamma % (t2_Nm|jpsi))*  B2_psi_gamma_f2;
		/* The '%' charcter denotes the outer product of two tensors - you can find the complete
	catalogue of permitted operations on the GPUPWA Wiki*/
	//Orbital_f2_2_MN.Print();


	// And the same for the f4s...
	GPUStreamTensor4 &  t4_mnuv = xorbitals.Spin4OrbitalTensor();
	GPUStreamTensor4 &  t4_mnUV = moveindices(t4_mnuv);
	GPUStreamTensor4 &  t4_UVmn = trans_3412(t4_mnUV);
	GPUStreamTensor4 &  t4_mnuV = movelastindex(t4_mnuv);
	GPUStreamTensor4 &  t4_Vmnu = trans_2341(t4_mnuV);

	GPUStreamScalar &  B4_psi_gamma_f4 = jpsiorbitals.Barrier4();
	GPUStreamTensor2 & Orbital_f4_0_MN = (t4_UVmn|(jpsi%jpsi)) * B2_psi_gamma_f2;
	GPUStreamTensor2 & Orbital_f4_1_MN = -g * (t4_mnuv|((jpsi%jpsi)%(jpsi%jpsi))) * B4_psi_gamma_f4;
	GPUStreamTensor2 & Orbital_f4_2_MN = Gamma %(t4_Vmnu|(jpsi%jpsi%jpsi)) * B4_psi_gamma_f4;


	/* Next we create the propagators, here assumed to have a Breit-Wigner form. Arguments are the
	mass squared at which it is to be evalueted and the resonance mass and width (here taken in a
	single object from the configuration file).
	*/
	//GPUPropagatorMassDependentBreitWigner & propagator1 = * new GPUPropagatorMassDependentBreitWigner(x2,2,res_f2,0.492,0.492);
	GPUPropagatorBreitWigner & propagator1 = * new GPUPropagatorBreitWigner("f2",x2);
	GPUPropagatorBreitWigner & propagator2 = * new GPUPropagatorBreitWigner("f0",x2);
	GPUPropagatorBreitWigner & propagator3 = * new GPUPropagatorBreitWigner("f4",x2);

	// And now we build up partial waves from the orbital an propagator parts, the third argument names the wave
	// A scalar
	GPUFactorizedRadiativePartialWave & wave0 = * new GPUFactorizedRadiativePartialWave(Orbital_f0_MN,propagator2,"f0");
	// And a 2+ resonance, with three waves.
	GPUFactorizedRadiativePartialWave & wave1 = * new GPUFactorizedRadiativePartialWave(Orbital_f2_0_MN,propagator1,"f20");
	GPUFactorizedRadiativePartialWave & wave2 = * new GPUFactorizedRadiativePartialWave(Orbital_f2_1_MN,propagator1,"f21");
	GPUFactorizedRadiativePartialWave & wave3 = * new GPUFactorizedRadiativePartialWave(Orbital_f2_2_MN,propagator1,"f22");
	// And again the same for the 4+
	GPUFactorizedRadiativePartialWave & wave4 = * new GPUFactorizedRadiativePartialWave(Orbital_f4_0_MN,propagator3,"f40");
	GPUFactorizedRadiativePartialWave & wave5 = * new GPUFactorizedRadiativePartialWave(Orbital_f4_1_MN,propagator3,"f41");
	GPUFactorizedRadiativePartialWave & wave6 = * new GPUFactorizedRadiativePartialWave(Orbital_f4_2_MN,propagator3,"f42");


	std::vector<char **> parnames;
	char* rp1="res_f0_1_mass";
	char* rp2="res_f0_1_width";
	char* rp3="res_f0_1_mag";
	char* rp4="res_f0_1_phase";
	char* rp5="res_f0_2_mass";
	char* rp6="res_f0_2_width";
	char* rp7="res_f0_2_mag";
	char* rp8="res_f0_2_phase";
	char* rp9="c";
	char* rp10="cs";
	char* rp11="dx";
	char* rp12="dy";
	char* rp13="dsx";
	char* rp14="dsy";
	parnames.push_back(&rp1);
	parnames.push_back(&rp2);
	parnames.push_back(&rp3);
	parnames.push_back(&rp4);
	parnames.push_back(&rp5);
	parnames.push_back(&rp6);
	parnames.push_back(&rp7);
	parnames.push_back(&rp8);
	parnames.push_back(&rp9);
	parnames.push_back(&rp10);
	parnames.push_back(&rp11);
	parnames.push_back(&rp12);
	parnames.push_back(&rp13);
	parnames.push_back(&rp14);
	float m1=0.493677;
	float m2=0.493677;       
	GPUDynamicalFunctionPVector & pvector = * new GPUDynamicalFunctionPVector("kmatrix",x2,parnames,2,m1,m2);


	GPUFactorizedRadiativePartialWave & wave0p = * new GPUFactorizedRadiativePartialWave(Orbital_f0_MN,pvector,"f0pvector");






	/* Add the waves to the partial wave analysis; for every wave added, four parameters
	(magnitude, phase, mass, width) are added to the list of fit parameters */
// 	myanalysis->GetWaves()->AddPartialWave(wave1);
//	myanalysis->GetWaves()->AddPartialWave(wave2);
//	myanalysis->GetWaves()->AddPartialWave(wave3);
	myanalysis->GetWaves()->AddPartialWave(wave0p);

	/* If we feel lucky we can also add the 4+ waves*/
	/*myanalysis->GetWaves()->AddPartialWave(wave4);
	myanalysis->GetWaves()->AddPartialWave(wave5);
	myanalysis->GetWaves()->AddPartialWave(wave6);*/

	// As this is needed in the contractions, we should tell one of the radiative partial waves (it is a static member)
	wave0p.SetGPerpStream(&gPerpPerp_mn);

	// Here we should see that there are indeed four waves in the analysis
	cout << "Active waves: " << myanalysis->GetWaves()->GetNActiveWaves() << endl;
/*
  myanalysis->GetPartialWave(1)->SetPhaseParameter(myanalysis->GetParameterIndex("f20_phase"));
    myanalysis->FixParameter(myanalysis->GetParameterIndex("f21_phase"));
      myanalysis->GetPartialWave(2)->SetPhaseParameter(myanalysis->GetParameterIndex("f20_phase"));
        myanalysis->FixParameter(myanalysis->GetParameterIndex("f22_phase"));
*/
	/* Now we set the initial values, error estimates and limits of the parameters
	from the configuration file. If the value of the error estimate is negative,
	the parameter will be fixed. Limits with a value of 999 will be ignored, i.e.
	the parameter will  be considered free in that direction
	The 0th parameter is always the magnitude of the phase-space background*/
//	myanalysis->SetParameter(0,mag_bg);
//	myanalysis->SetParameter(0,0);
//	myanalysis->FixParameter(0,0);
	/* Magnitude and phase parameters for the 4 resonances. Note that at least
	one magnitude and one phase in the fit have to be fixed, otherwise there is
	no unique solution and fits will generally not converge */
//	myanalysis->SetParameter(1,mag_f20);
//	myanalysis->SetParameter(2,phase_f20);

//	myanalysis->SetParameter(5,mag_f21);
	//myanalysis->SetParameter(6,phase_f21);
/*	myanalysis->GetPartialWave(1)->SetPhaseParameter(2);
	myanalysis->FixParameter(6,0);

	myanalysis->SetParameter(9,mag_f22);
	//myanalysis->SetParameter(10,phase_f22);
	myanalysis->GetPartialWave(2)->SetPhaseParameter(2);
	myanalysis->FixParameter(10,0);

	myanalysis->SetParameter(13,mag_f0);
	myanalysis->SetParameter(14,phase_f0);*/

/*	myanalysis->SetParameter(17,mag_f40);
	myanalysis->SetParameter(18,phase_f40);

	myanalysis->SetParameter(21,mag_f41);
	myanalysis->GetPartialWave(5)->SetPhaseParameter(18);
	myanalysis->FixParameter(22,0);
	//myanalysis->SetParameter(22,phase_f41);

	myanalysis->SetParameter(25,mag_f42);
	myanalysis->GetPartialWave(6)->SetPhaseParameter(18);
	myanalysis->FixParameter(26,0);
	//myanalysis->SetParameter(26,phase_f42);*/

	/*myanalysis->SetParameter(1,mag_f40);
	myanalysis->SetParameter(2,phase_f40);

	myanalysis->SetParameter(5,mag_f41);
	myanalysis->SetParameter(6,phase_f41);

	myanalysis->SetParameter(9,mag_f42);
	myanalysis->SetParameter(10,phase_f42);*/
	// And now we fix the resonance parameters
	// -> To do: 1. Fits with free resonance parameters
	//			 2. do the fixing automatically
/*	myanalysis->FixParameter(3,res_f2.m);
	myanalysis->FixParameter(4,res_f2.w);

	myanalysis->FixParameter(7,res_f2.m);
	myanalysis->FixParameter(8,res_f2.w);

	myanalysis->FixParameter(11,res_f2.m);
	myanalysis->FixParameter(12,res_f2.w);

	myanalysis->SetParameter(15,res_f0.m);
	//myanalysis->FixParameter(15,2.0);
	myanalysis->SetParameterError(15,0.01);*/

	// Constrain the parameter
	//        myanalysis->ReleaseParameter(11);
  //	GPUChi2FitConstraint * p11constraint = new GPUChi2FitConstraint(myanalysis, 11, 2.15, 0.001);
  //	myanalysis->AddConstraint(p11constraint);

//	myanalysis->SetParameter(16,res_f0.w);
//	myanalysis->SetParameterError(16,0.01);

	/*myanalysis->FixParameter(19,res_f4.m);
	myanalysis->FixParameter(20,res_f4.w);

	myanalysis->FixParameter(23,res_f4.m);
	myanalysis->FixParameter(24,res_f4.w);

	myanalysis->FixParameter(27,res_f4.m);
	myanalysis->FixParameter(28,res_f4.w);*/

	/*myanalysis->FixParameter(3,res_f4.m);
	myanalysis->FixParameter(4,res_f4.w);

	myanalysis->FixParameter(7,res_f4.m);
	myanalysis->FixParameter(8,res_f4.w);

	myanalysis->FixParameter(11,res_f4.m);
	myanalysis->FixParameter(12,res_f4.w);*/

	// And we are ready to run - so lets check how long this took...
	clock_t startup = clock();
	/* Here we perform the preparations for the Monte Carlo calculation.
	This will read the MC file, compute and sum all amplitude and interference
	terms and write them to a file. This has to be called only once for a constant set
	of resonances, as long as their masses and widths are not changed */
	//myanalysis->MCIntegral();

	/* Reset the cache for the MC (at index 1) in order to free some memory. If you have "out of memory"
	or "Cal ressource allocation" errors, remove the comment from the next line */
	//myanalysis->Reset(1);

	//k_plus.ReadFile(0);
	//k_minus.ReadFile(0);

	std::vector<unsigned int> nad=myanalysis->GetNActiveDynamicParameters();
	myanalysis->PrintParameters();

#ifdef FIT

	// Print how long all this took...
	clock_t mcend = clock();
	cout << "Startup: " << (startup-start) << " ticks = " <<  (float)(startup-start)/(float)CLOCKS_PER_SEC << " s" << endl;
	cout << "MC: " << (mcend-startup) << " ticks = " <<  (float)(mcend-startup)/(float)CLOCKS_PER_SEC << " s" << endl;



	/* Now we can do the fit. Currently you can use either of the following fitters:
	- FUMILI (the Minuit2 implementation,
	- OLDFUMILI (the BES II implementation, in general requires fewest iterations),
	- MINUIT (with numerical gradients),
	- MINUITGRAD (with analytical gradients,
	- MINUITMINOS (MNUIT (numerical gradients) followed by a modified MINOS error estimation)
	*/
	//myanalysis->DoFit(GPUPartialWaveAnalysis::OLDFUMILI);
	//myanalysis->DoMultiFit(GPUPartialWaveAnalysis::OLDFUMILI, 5, 5);
	//TGraph * mygraph = myanalysis->ScanParameter(GPUPartialWaveAnalysis::OLDFUMILI, 15, 2.145,2.155,20);
	//	myanalysis->DoFit(GPUPartialWaveAnalysis::FUMILI);
		myanalysis->DoFit(GPUPartialWaveAnalysis::MINUIT);
	//	myanalysis->DoFit(GPUPartialWaveAnalysis::MINUITGRAD);
	//	myanalysis->DoFit(GPUPartialWaveAnalysis::MINUITMINOS);

	// -> To do: Write fit results to a file

	clock_t fitend = clock();
	cout << "Fit: " << (fitend-mcend) << " ticks = " <<  (float)(fitend-mcend)/(float)CLOCKS_PER_SEC << " s" << endl;
#endif
#ifdef PLOT
	/* Reset the cache for the Data (at index 0) in order to free some memory. If you have "out of memory"
	or "Cal ressource allocation" errors, remove the comment from the next line */
	myanalysis->Reset(0);


	/*And now we would like to plot some projections for the fit results. For this we need event-wise differential
	x-sections for the Monte Carlo, which we are going to generate with the following line. The boolean argument denotes
	whether the interference terms should also be plotted*/

	float ** dcs = myanalysis->GetMCDcs(true);
	myanalysis->Reset(1);

	// Create the quantities to be plotted
 	GPUStreamScalar &ct_g=costheta(gamma);

	/* .. yes, we can also rotate and boost vectors - this is of course meaningless for covariant amplitudes, but nice for
	plotting */
	GPUStreamVector & kr= lorentzrotation(k_plus,x);
 	GPUStreamVector & xr= lorentzrotation(x,x);
	GPUStreamVector & kb= lorentzboost(kr,xr);
 	GPUStreamScalar & ct_k=costheta(kb);
	GPUStreamScalar & ph_k=phi(kb);

	// So first we create a set of plots, which takes care of the formatting and file handling
	GPUPlotset * plotset = new GPUPlotset();
	//plotset->AddGraph(mygraph);
	int nwaves =  myanalysis->GetWaves()->GetNActiveWaves();
	/* And then we add plots.
	The GPUStreamScalar::Plot() function generates a vector of root histograms (TH1F). Arguments are:
	- Plot name (used for acces in root files)
	- Plot title (used for displying). In the title, titles for the x and y axis can be given after semicolons
	- Number of bins
	- Axis low
	- Axis high
	- Array with the MC differential cross sections
	- Number of waves
	- Whether or not to plot the off diagonal (interference) elements. If true, the dcs array also has to contain
		the interference terms
	*/
	plotset->AddPlots(mX.Plot("mass","mass;mX [GeV]",50,1.7,2.3,dcs, nwaves,true));
	plotset->AddPlots(ct_g.Plot("cos_theta_g","cos theta of gamma in J/psi;cos theta(gamma) ",50,-1,1,dcs, nwaves, true));
    plotset->AddPlots(ct_k.Plot("cos_theta_K","cos theta of K in X;cos theta(K) ",20,-1,1,dcs, nwaves,true));
	plotset->AddPlots(ph_k.Plot("phi_K","phi of K in X;phi(K) ",20,-3.1416,3.1416,dcs, nwaves,true));
	// Nicely format the plots (root defaults are REALLY UGLY!)
	plotset->Format();
	// Write a postscript file with the plots. The erguments are currently ignored.
	// -> Fix the argument issue
	plotset->WritePsfile("testout1.ps",1,1);
	// Write a rootfile with the plots
	plotset->WriteRootfile("testout1.root");

	clock_t plotend = clock();
	cout << "Plots: " << (plotend-fitend) << " ticks = " << (float)(plotend -fitend)/(float)CLOCKS_PER_SEC << " s" << endl;
#endif
	// Last words from timing
	clock_t end = clock();
	cout << "Overall: " << (end-start) << " ticks = " <<  (float)(end-start)/(float)CLOCKS_PER_SEC << " s" << endl;

#ifdef WINDOWS
	// Ask for input to prevent console from closing to early...
	cout << "Enter 0 to continue " <<endl;
	char wurst[511];
	std::cin >> wurst;
#endif
	// Done
	return 0;


}

