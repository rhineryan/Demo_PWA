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
#include "../GPUPWA/GPUMetricTensor.h"
#include "../GPUPWA/GPUOrbitalTensors.h"
#include "../GPUPWA/GPUPropagatorBreitWigner.h"
#include "../GPUPWA/GPUPropagatorMassDependentBreitWigner.h"
#include "../GPUPWA/GPUPartialWaveAnalysis.h"
#include "../GPUPWA/GPUPWAAmplitudeCalculator.h"
#include "../GPUPWA/GPUStreamInputRootFileVector.h"
#include "../GPUPWA/GPUStreamInputTextFileVector.h"
#include "../GPUPWA/GPUPlotset.h"
#include "../GPUPWA/GPUChi2FitConstraint.h"
#include "../GPUPWA/GPUDataDependentObjectType.h"
#include "../GPUPWA/GPUFactorizedRadiativePartialWave.h"

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




#define PLOT

// Main program, can be called without any arguments
int main(int argc, char* argv[])
{
	// We will want to do some timing measurements, thus start the clock
	clock_t start = clock();

	// Say Hello to our user
	cout << "Gamma KK partial wave analysis huaning ni!" << endl << endl;;



	/* Here we start: Create a GPU Partial Wave Analysis Object.As parameters we give a name, a filename and the number of file types we want to use (in this case
	2, namely data and the phase space Monte Carlo). If you need additional input, e.g. different MC for systematic studies,
	increase that number. The file should contain the following entries:
	ParameterFile = <Name of file with fit parameter starting values (usually called para.inp)>
	ResonanceFile = <Name of file with resonance masses and widths (usually called res.inp)>
	DataFile = <Name of the file with the inputs for data>
	MCFile1 = <Name of the file with the inputs for MC (first set)>
	if the third argument is larger than 2, add MCFile2, MCFile3 etc. entries.
	*/
	GPUPartialWaveAnalysis * myanalysis = new GPUPartialWaveAnalysis("Gamma KK Analysis","files.txt",2);


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
	they will be used in. This is needed for the caching mechanism to work. Then we give the name of the root file for the data
	(here taken from the analysis objects, which in turn reads it from the input file at construction),
	the name of the root tree and the names of the branches in the tree containing the momentum components and the energy.
	Alternatively, text files can be used*/
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


	/* We can use weights for the data events, e.g. to do a background subtraction. Here we just set the weights to 1 for all
	data used*/
	myanalysis->SetEventWeights(1);
//	myanalysis->SetEventWeights(0.2,1);

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
	//gamma.Print(100);
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


	/* Next we create the propagators, here assumed to have a Breit-Wigner form. Arguments are
	 * a name (which is used to read the mass and width from the ResonanceFile input file and the
	 * mass squared at which it is to be evaluated.
	 * The input file should  contain entries of the form
	 * <Name>_mass = <Starting value> <Starting error> <lower limit> <upper limit>
	 * and <Name>_width = <Starting value> <Starting error> <lower limit> <upper limit>
	 * A negative starting error will fix the parameter, limits of 999 are interpreted as no limits.
	*/
	GPUPropagatorBreitWigner & propagator1 = * new GPUPropagatorBreitWigner("f2", x2);
	GPUPropagatorBreitWigner & propagator2 = * new GPUPropagatorBreitWigner("f0", x2);
	GPUPropagatorBreitWigner & propagator3 = * new GPUPropagatorBreitWigner("f4" ,x2);


	/* And now we build up partial waves from the orbital and propagator parts, the third argument
names the wave. As we are considering a radiative decay to mesons, the orbital parts are
second rank tensors (and real, which means that the complex and the higher rank parts
factorize) and we thus have GPUFactorizedRadiativePartialWave objects. For other analyses,
we would use GPUScalarPartialWave or GPUVectorPartialWave. Note that the name is used to
read starting parameters from the ParameterFile input file, which should thus
contain entries of the form <Name>_mag = <Starting value> <Starting error> <lower limit> <upper limit>
and <Name>_phase = <Starting value> <Starting error> <lower limit> <upper limit>
A negative starting error will fix the parameter, limits of 999 are interpreted as no limits.*/

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

	/* Add the waves to the partial wave analysis; for every wave added, four parameters
	(magnitude, phase, mass, width) are added to the list of fit parameters */
	myanalysis->GetWaves()->AddPartialWave(wave1);
	myanalysis->GetWaves()->AddPartialWave(wave2);
	myanalysis->GetWaves()->AddPartialWave(wave3);
	myanalysis->GetWaves()->AddPartialWave(wave0);

	/* If we feel lucky we can also add the 4+ waves*/
	/*myanalysis->GetWaves()->AddPartialWave(wave4);
	myanalysis->GetWaves()->AddPartialWave(wave5);
	myanalysis->GetWaves()->AddPartialWave(wave6);*/

	// As this is needed in the contractions, we should tell one of the radiative partial waves (it is a static member)
	wave0.SetGPerpStream(&gPerpPerp_mn);

	// Here we should see that there are indeed four waves in the analysis
	cout << "Active waves: " << myanalysis->GetWaves()->GetNActiveWaves() << endl;



/// to set a constrain of the fraction of a resonance
/// initialise 'this' pwacalculator to get the cross sections during the fit  
  //  myanalysis->InitCalculator();
/// index of waves of a resonance , e.g wave 0,1,2 for f2 
  //  std::vector<int> waveidx;
  //  waveidx.push_back(0);
  //  waveidx.push_back(1);
  //  waveidx.push_back(2);
/// add the constraint (myanalysis, name of the constrain, index of waves, central value, sigma)   
  //  GPUChi2FrFitConstraint * fractionconstraint = new GPUChi2FrFitConstraint(myanalysis, "f2", waveidx, 0.5887, 0.0001);
  //  myanalysis->AddConstraint(fractionconstraint);

	k_plus.ReadFile(0);
	k_minus.ReadFile(0);
	k_plus.ReadFile(1);
	k_minus.ReadFile(1);

	// And we are ready to run - so lets check how long this took...
	clock_t startup = clock();
	/* Here we perform the preparations for the Monte Carlo calculation.
	This will read the MC file, compute and sum all amplitude and interference
	terms and write them to a file. This has to be called only once for a constant set
	of resonances, as long as their masses and widths are not changed */
	myanalysis->MCIntegral();

	/* Reset the cache for the MC (at index 1) in order to free some memory. If you have "out of memory"
	or "Cal ressource allocation" errors, remove the comment from the next line */
	myanalysis->Reset(1);

	//PrintStreamMemoryUse();

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
	myanalysis->DoFit(GPUPartialWaveAnalysis::OLDFUMILI);
	//myanalysis->DoMultiFit(GPUPartialWaveAnalysis::OLDFUMILI, 5, 5);
	//TGraph * mygraph = myanalysis->ScanParameter(GPUPartialWaveAnalysis::OLDFUMILI, 15, 2.145,2.155,20);
	//	myanalysis->DoFit(GPUPartialWaveAnalysis::FUMILI);
		//myanalysis->DoFit(GPUPartialWaveAnalysis::MINUIT);
	//	myanalysis->DoFit(GPUPartialWaveAnalysis::MINUITGRAD);
	//	myanalysis->DoFit(GPUPartialWaveAnalysis::MINUITMINOS);

	// -> To do: Write fit results to a file

	clock_t fitend = clock();
	cout << "Fit: " << (fitend-mcend) << " ticks = " <<  (float)(fitend-mcend)/(float)CLOCKS_PER_SEC << " s" << endl;

	//PrintStreamMemoryUse();
/* get the total cross section of each partial wave
user case 1: calculate the fraction of each resonance by (partial total cross section/ total cross section);
user case 2: calculate the number of events of each resonance by fraction * N_data;
user case 3: calculate the efficiency of each partial wave or resonance by (partial total cross section with selected PHSP/ partial total cross section generated PHSP);
user case 4: constrain the fraction a resonance by chi^2 fit constrain; Also, get the statistical error of a fraction by scan the constrain;
*/
  // e.g to calculate the fraction of 2+ (wave 0,1,2) as following, GetPartialTotalXSection[1][NActiveWaves] is the total crossection. myanalysis->InitCalculator() is needed.
  //  double** ptx=myanalysis->GetPartialTotalXSection();
  //  cout<<"fraction: "<<(ptx[0][0]+ptx[0][1]+ptx[0][2]+ptx[1][1]+ptx[1][2]+ptx[2][2])/ptx[1][4]<<endl;


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

	// Done
	return 0;


}

