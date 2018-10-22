/************************************************************************/
/************************ GammaEtapPiPi.cpp *****************************/ 
/************************************************************************/

/************************************************************************/
/****** Partial Wave Analysis for J/psi(psi') -> Gamma EtaP Pi Pi *******/
/**************** AUTHOR: Tianjue Min, 02/04/2015 ***********************/
/************* REFERENCE: GammaKKpi.cpp by Ye Chen, 22/11/2010 **********/
/************************************************************************/
#include "../GPUPWA/GPUStreamTensor.h"
#include "../GPUPWA/GPUComputedTensor.h"
#include "../GPUPWA/GPUComputedPropagator.h"
#include "../GPUPWA/GPUFactorizedRadiativePartialWave.h"
#include "../GPUPWA/GPUUnFactorizedRadiativePartialWave.h"
#include "../GPUPWA/GPUMetricTensor.h"
#include "../GPUPWA/GPUAntisymmetricTensor.h"
#include "../GPUPWA/GPUOrbitalTensors.h"
#include "../GPUPWA/GPUPropagatorBreitWigner.h"
#include "../GPUPWA/GPUPropagatorMassDependentBreitWigner.h"
#include "../GPUPWA/GPUPropagatorFlatte2.h"
#include "../GPUPWA/GPUPropagatorFlatte3.h"
#include "../GPUPWA/GPUPropagatorFlatte4.h"
#include "../GPUPWA/GPUPropagatorA980.h"
#include "../GPUPWA/GPUPropagatorSigma.h"
#include "../GPUPWA/GPUPropagatorGaussian.h"
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
#include "../GPUPWA/GPUDataDependentObjectType.h"
#include "TFile.h"
#include "TRandom3.h"
#include <ctime>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using std::cout;
using std::endl;
#define PLOT
typedef GPUUnFactorizedRadiativePartialWave UFPW;
typedef GPUFactorizedRadiativePartialWave FPW;

const float mpi0  = 0.134977f;
const float mpi   = 0.139570f;
const float mp    = 0.93827f;
const float mpbar = 0.93827f;
const float mK    = 0.493677f;
const float mKs   = 0.497614f;
const float meta  = 0.547853f;
const float metap = 0.95778f;
const float m0    = 0.0f;

////set the name of one wave
void setWaveName(char * waveName, char * nameX, char * nameY, const int & id) {
  sprintf(waveName, "<%s|%s>_%d", nameX, nameY, id);
}


template<typename T> string  toString(const T& t){
  stringstream oss;
  oss<<t;
  return oss.str();
}


bool ifSetGPerp(GPUPartialWaveAnalysis * ana) {
  if (ana->GetNPartialWaves() == 0)
    return true;
  else
    return false;
}

int ifhasX(vector<char *>  reso_name_X, string name){
  bool b_ad=false;
  int index=0;
  for(vector<char *>::iterator it_name=reso_name_X.begin(); it_name!= reso_name_X.end();it_name++){
    if(strcmp(*it_name, name.c_str()) == 0){
      b_ad=true;break;
    }
    index++;
  }
  if(b_ad){
    return index;
  }else{
    return -1;
  }
}


GPUScalarPropagator *  create_X_propagator( char *nameX, GPUStreamScalar & sX){
  if( strcmp(nameX,"X2370")==0){
    return  new GPUPropagatorBreitWigner("X2370", sX);
  } else if( strcmp(nameX,"Xphsp")==0){
    return  new GPUPropagatorBreitWigner("Xphsp", sX);
  }else if( strcmp(nameX, "X1835") == 0){
    //return  new GPUPropagatorBreitWigner("X1835", sX);
    return  new GPUPropagatorFlatte2("X1835", sX,m0,m0,mp,mpbar);
  }else{
    return new GPUPropagatorBreitWigner(nameX, sX);
  }
  return  0;
}

GPUScalarPropagator * create_f_propagator(char *nameY, GPUStreamScalar & sY,int rank, bool constWidth = true){
  if(strcmp(nameY,"f0_500")==0){
    return new GPUPropagatorSigma(nameY, sY);
  }else if(strcmp(nameY,"f0_980")==0){
    return new GPUPropagatorFlatte3(nameY, sY, mpi0, mpi0, mK, mK, mKs, mKs);
    //return  new GPUPropagatorFlatte2(nameY, sY, mpi, mpi, mK, mK);
  }else{
    if(constWidth){
      return new GPUPropagatorBreitWigner(nameY, sY);
    }else{
      return new GPUPropagatorMassDependentBreitWigner(nameY, sY, rank, mpi0, mpi0);
    }
  }
  return 0;
}


GPUScalarPropagator * create_a_propagator(char *nameY, GPUStreamScalar & sY, int rank, bool constWidth = true){
  if(strcmp(nameY,"a0_980") == 0){
    return new GPUPropagatorA980(nameY, sY, meta, mpi0, mK, mK, mKs, mKs, metap, mpi0);
    //return new GPUPropagatorA980(nameY, sY, meta, mpi, mK, mK,mKs, mKs,metap, mpi) ;
  }else {
    if(constWidth){
      return new GPUPropagatorBreitWigner(nameY, sY);
    }else{
      return new GPUPropagatorMassDependentBreitWigner(nameY, sY, rank, meta, mpi0);
    }
  }
  return 0;
}

//addfuction
//
void addPartialWave(GPUPartialWaveAnalysis * ana, GPUStreamTensor2 & gpp, GPUStreamTensor2 & t1, char *nameX, GPUScalarPropagator & resX, char * nameY, GPUScalarPropagator & resY,int pwavenum,std::vector<GPUTensor2Propagator *> &vpro_tensor2, std::vector<GPUUnFactorizedRadiativePartialWave *> &vec_unf_waves){
  bool setGPerp = ifSetGPerp(ana);

  char waveName1[100];
  setWaveName(waveName1, nameX, nameY, pwavenum);
  GPUTensor2Propagator & pro_amp= t1*(resX*resY);
  vpro_tensor2.push_back(& pro_amp);
  GPUUnFactorizedRadiativePartialWave & partialWave1 = * new GPUUnFactorizedRadiativePartialWave(pro_amp, waveName1);
  vec_unf_waves.push_back(& partialWave1);
  ana->GetWaves()->AddPartialWave(partialWave1);
  if(setGPerp){
    partialWave1.SetGPerpStream(&gpp);
  }
}

void addPartialWave(GPUPartialWaveAnalysis * ana, GPUStreamTensor2 & gpp, GPUStreamTensor2 & t1, GPUStreamTensor2 & t2, char *nameX, GPUScalarPropagator & resX, char * nameY, GPUScalarPropagator & resYb, GPUScalarPropagator & resYc,int pwavenum,std::vector<GPUTensor2Propagator *> &vpro_tensor2, std::vector<GPUUnFactorizedRadiativePartialWave *> &vec_unf_waves){
  bool setGPerp = ifSetGPerp(ana);

  char waveName1[100];
  setWaveName(waveName1, nameX, nameY, pwavenum);

  GPUTensor2Propagator & pro_amp= (t1*resYb + t2*resYc)*resX;
  vpro_tensor2.push_back(& pro_amp);
  GPUUnFactorizedRadiativePartialWave & partialWave1 = * new GPUUnFactorizedRadiativePartialWave(pro_amp, waveName1);
  vec_unf_waves.push_back(& partialWave1);
  ana->GetWaves()->AddPartialWave(partialWave1);
  if(setGPerp){
    partialWave1.SetGPerpStream(&gpp);
  }
}

////void print(vector<pair<int, int> > & pos) {
////  for (vector<pair<int, int> >::iterator it = pos.begin(); it != pos.end(); ++it) {
////    cout << "| " << (*it).first << " " << (*it).second << " |";
////  }
////  cout << endl;
////}
////
////int pos_nij(int n, int i, int j) {
////  if (i == j)
////    return i + 1;
////  else 
////    return (2*n-i-2)*(i-1)/2 + j + n;
////}

int main(int argc, char* argv[]){
  clock_t start = clock();
  cout << "lalala, lalala, wo shi fen bo de xiao hang jia ~ ~" << endl << endl;;

  GPUPartialWaveAnalysis * myanalysis = new GPUPartialWaveAnalysis("Gamma Etap Ks Ks Analysis", "./input/files.txt", 2);
  myanalysis->SetMCIndex(1);

  GPUStreamInputRootFileVector & p1 = * new GPUStreamInputRootFileVector(myanalysis, myanalysis->GetDataFile(), "GamEtapKsKs", "Px_etap", "Py_etap", "Pz_etap", "E_etap");
  GPUStreamInputRootFileVector & p2 = * new GPUStreamInputRootFileVector(myanalysis, myanalysis->GetDataFile(), "GamEtapKsKs", "Px_ks1", "Py_ks1", "Pz_ks1", "E_ks1");
  GPUStreamInputRootFileVector & p3 = * new GPUStreamInputRootFileVector(myanalysis, myanalysis->GetDataFile(), "GamEtapKsKs", "Px_ks2", "Py_ks2", "Pz_ks2", "E_ks2");
  p1.SetFilename(myanalysis->GetMCFile(), 1);
  p2.SetFilename(myanalysis->GetMCFile(), 1);
  p3.SetFilename(myanalysis->GetMCFile(), 1);

  // configuration file
  ConfigFile cfg("./input/files.txt");
  // what to do
  string OPERATION = cfg.read<string>("OPERATION");
  string FITTER = cfg.read<string>("FITTER");
  // number/weight of sideband events
  int NSG = cfg.read<int>("NSG");
  int NSB1 = cfg.read<int>("NSB1");

  float WSG = cfg.read<float>("WSG");
  float WSB1 = cfg.read<float>("WSB1");

  // spread and nfit
  float SPREAD = cfg.read<float>("SPREAD");
  float NFIT = cfg.read<int>("NFIT");
  // base line

  vector<int> ivec;
  vector<float> fvec;

  ivec.push_back(NSG);
  fvec.push_back(WSG);
  if (NSB1 != 0) {
    ivec.push_back(NSB1);
    fvec.push_back(WSB1);
  }

  //myanalysis->SetEventWeights(1);
  myanalysis->SetEventWeights(ivec, fvec, 0);

  myanalysis->SetNumberMCGen(myanalysis->GetNumberMCAcc());

  GPUMetricTensor & g = * new GPUMetricTensor();
  GPUAntisymmetricTensor & epsilon = * new GPUAntisymmetricTensor();

  float4 f_jpsi = mfloat4(0.0f, 0.0f, 0.0f, 3.097f);

  GPUConstVector & psip = * new GPUConstVector(f_jpsi) ;

  GPUStreamVector & petap = p1;
  GPUStreamVector & pks1 = p2;
  GPUStreamVector & pks2 = p3;
  GPUStreamVector & pksks = p2+p3;
  GPUStreamVector & petapks1 = p1+p2;
  GPUStreamVector & petapks2 = p1+p3;
  GPUStreamVector & x = p1+p2+p3 ;

  GPUStreamVector & p12 = p1+p2 ;
  GPUStreamVector & p23 = p2+p3 ;
  GPUStreamVector & p13 = p1+p3 ;

  GPUStreamVector & gam = psip-x ;
  GPUStreamScalar & sx = x|x ;
  GPUStreamScalar & s12 = p12|p12 ;
  GPUStreamScalar & s23 = p23|p23 ;
  GPUStreamScalar & s13 = p13|p13 ;
  GPUStreamScalar & xgam = x|gam;

  GPUStreamScalar & mx = sqrt(sx) ;
  GPUStreamScalar & m12 = sqrt(s12) ;
  GPUStreamScalar & m23 = sqrt(s23) ;
  GPUStreamScalar & m13 = sqrt(s13) ;

  // g_PerpPerp Tensor
  GPUStreamTensor2 & gpp = g-(gam%x+x%gam)/xgam+sx/(xgam|xgam)*(gam%gam);

  GPUStreamTensor2 & S_mn = (epsilon|gam)|psip;
  GPUStreamTensor2 & gx_tilde = g-x%x/sx;

  /*********************************************************************/
  GPUOrbitalTensors & psipOrb = * new GPUOrbitalTensors(myanalysis, psip, gam, x);
  //GPUOrbitalTensors & psipOrb = * new GPUOrbitalTensors(myanalysis, psip, gam, x, 0.128372); //mintj for psi(3686)
  GPUStreamScalar & B1 = psipOrb.Barrier1();
  GPUStreamScalar & B2 = psipOrb.Barrier2();
  GPUStreamScalar & B3 = psipOrb.Barrier3();
  /*********************************************************************/
  GPUOrbitalTensors & xa = * new GPUOrbitalTensors(myanalysis, x, p1 , p23);
  GPUOrbitalTensors & xb = * new GPUOrbitalTensors(myanalysis, x, p2 , p13);
  GPUOrbitalTensors & xc = * new GPUOrbitalTensors(myanalysis, x, p3 , p12);
  GPUStreamVector & xa_p = xa.Spin1OrbitalTensor();
  GPUStreamVector & xb_p = xb.Spin1OrbitalTensor();
  GPUStreamVector & xc_p = xc.Spin1OrbitalTensor();
  GPUStreamTensor2 & xa_d = xa.Spin2OrbitalTensor();
  GPUStreamTensor2 & xb_d = xb.Spin2OrbitalTensor();
  GPUStreamTensor2 & xc_d = xc.Spin2OrbitalTensor();
  GPUStreamTensor3 & xa_f = xa.Spin3OrbitalTensor();
  GPUStreamTensor3 & xb_f = xb.Spin3OrbitalTensor();
  GPUStreamTensor3 & xc_f = xc.Spin3OrbitalTensor();
  /**********************************************************************/
  GPUOrbitalTensors & yab = * new GPUOrbitalTensors(myanalysis, p12, p1, p2);
  GPUOrbitalTensors & ybc = * new GPUOrbitalTensors(myanalysis, p23, p2, p3);
  GPUOrbitalTensors & yac = * new GPUOrbitalTensors(myanalysis, p13, p1, p3);
  GPUStreamVector & yab_p = yab.Spin1OrbitalTensor();
  GPUStreamVector & ybc_p = ybc.Spin1OrbitalTensor();
  GPUStreamVector & yac_p = yac.Spin1OrbitalTensor();
  GPUStreamTensor2 & yab_d = yab.Spin2OrbitalTensor();
  GPUStreamTensor2 & ybc_d = ybc.Spin2OrbitalTensor();
  GPUStreamTensor2 & yac_d = yac.Spin2OrbitalTensor();
  //GPUStreamTensor3 & yab_f = yab.Spin3OrbitalTensor();
  //GPUStreamTensor3 & ybc_f = ybc.Spin3OrbitalTensor();
  //GPUStreamTensor3 & yac_f = yac.Spin3OrbitalTensor();
  GPUStreamTensor4 & yab_g = yab.Spin4OrbitalTensor();
  GPUStreamTensor4 & ybc_g = ybc.Spin4OrbitalTensor();
  GPUStreamTensor4 & yac_g = yac.Spin4OrbitalTensor();
  ///************************* Project Tensor *****************************/
  GPUStreamTensor4 & xproj = (trans_1324(gx_tilde%gx_tilde)+trans_1342(gx_tilde%gx_tilde))/2.0f-(gx_tilde%gx_tilde)/3.0f;
  /////************************* 0-+ ****************************************/
  GPUStreamTensor2 & T_0m0p_a_1 = S_mn*B1;//<0-+|f0>1
  GPUStreamTensor2 & T_0m0p_b_1 = S_mn*B1;//<0-+|a0>1
  GPUStreamTensor2 & T_0m0p_c_1 = S_mn*B1;//<0-+|a0>1

  GPUStreamTensor2 & T_0m2p_a_1 = S_mn*B1*(xa_d|ybc_d);//<0-+|f2>1
  GPUStreamTensor2 & T_0m2p_b_1 = S_mn*B1*(xb_d|yac_d);//<0-+|a2>1
  GPUStreamTensor2 & T_0m2p_c_1 = S_mn*B1*(xc_d|yab_d);//<0-+|a2>1

  GPUStreamTensor2 & T_0m1m_b_1 = S_mn*B1*(xb_p|yac_p);//<0-+|pi1>1
  GPUStreamTensor2 & T_0m1m_c_1 = S_mn*B1*(xc_p|yab_p);//<0-+|pi1>1
  ///************************* 1++ ****************************************/
  GPUStreamScalar & scale = * new GPUStreamScalar(myanalysis,1.0f);
  //GPUStreamScalar & scale = * new GPUStreamScalar(myanalysis,10.0f);

  GPUStreamTensor2 & T_1p0p_a_1 = (epsilon|xa_p)|psip;//<1++|f0>1
  GPUStreamTensor2 & T_1p0p_b_1 = (epsilon|xb_p)|psip;//<1++|a0>1
  GPUStreamTensor2 & T_1p0p_c_1 = (epsilon|xc_p)|psip;//<1++|a0>1

  GPUStreamTensor2 & T_1p0p_a_2 = gam%(S_mn|xa_p)*B2*scale;//<1++|f0>2
  GPUStreamTensor2 & T_1p0p_b_2 = gam%(S_mn|xb_p)*B2*scale;//<1++|f0>2
  GPUStreamTensor2 & T_1p0p_c_2 = gam%(S_mn|xc_p)*B2*scale;//<1++|f0>2

  GPUStreamTensor2 & T_1p2p_a_1 = (((xa_p|ybc_d)|gx_tilde)|epsilon)|psip;//<1++|f2>1
  GPUStreamTensor2 & T_1p2p_b_1 = (((xb_p|yac_d)|gx_tilde)|epsilon)|psip;//<1++|a2>1
  GPUStreamTensor2 & T_1p2p_c_1 = (((xc_p|yab_d)|gx_tilde)|epsilon)|psip;//<1++|a2>1

  GPUStreamTensor2 & T_1p2p_a_2 = gam%(S_mn|((xa_p|ybc_d)|gx_tilde))*B2;//<1++|f2>2
  GPUStreamTensor2 & T_1p2p_b_2 = gam%(S_mn|((xb_p|yac_d)|gx_tilde))*B2;//<1++|a2>2
  GPUStreamTensor2 & T_1p2p_c_2 = gam%(S_mn|((xc_p|yab_d)|gx_tilde))*B2;//<1++|a2>2

  GPUStreamTensor2 & T_1p2p_a_3 = (((xa_f|ybc_d)|gx_tilde)|epsilon)|psip;//<1++|f2>3
  GPUStreamTensor2 & T_1p2p_b_3 = (((xb_f|yac_d)|gx_tilde)|epsilon)|psip;//<1++|a2>3
  GPUStreamTensor2 & T_1p2p_c_3 = (((xc_f|yab_d)|gx_tilde)|epsilon)|psip;//<1++|a2>3

  GPUStreamTensor2 & T_1p2p_a_4 = gam%(S_mn|((xa_f|ybc_d)|gx_tilde))*B2;//<1++|f2>4
  GPUStreamTensor2 & T_1p2p_b_4 = gam%(S_mn|((xb_f|yac_d)|gx_tilde))*B2;//<1++|a2>4
  GPUStreamTensor2 & T_1p2p_c_4 = gam%(S_mn|((xc_f|yab_d)|gx_tilde))*B2;//<1++|a2>4

  GPUStreamTensor2 & T_1p1m_b_1 = (epsilon|yac_p)|psip;//<1++|pi1>1
  GPUStreamTensor2 & T_1p1m_c_1 = (epsilon|yab_p)|psip;//<1++|pi1>1

  GPUStreamTensor2 & T_1p1m_b_2 = gam%(S_mn|yac_p)*B2*scale;//<1++|pi1>2
  GPUStreamTensor2 & T_1p1m_c_2 = gam%(S_mn|yab_p)*B2*scale;//<1++|pi1>2

  GPUStreamTensor2 & T_1p1m_b_3 = (epsilon|(xb_d|yac_p))|psip;//<1++|pi1>3
  GPUStreamTensor2 & T_1p1m_c_3 = (epsilon|(xc_d|yab_p))|psip;//<1++|pi1>3

  GPUStreamTensor2 & T_1p1m_b_4 = gam%(S_mn|(xb_d|yac_p))*B2*scale;//<1++|pi1>4
  GPUStreamTensor2 & T_1p1m_c_4 = gam%(S_mn|(xc_d|yab_p))*B2*scale;//<1++|pi1>4

  GPUStreamTensor2 & T_1p4p_a_1 = (((ybc_g|xa_f)|gx_tilde)|epsilon)|psip;//<1++|f4>1
  GPUStreamTensor2 & T_1p4p_b_1 = (((yac_g|xb_f)|gx_tilde)|epsilon)|psip;//<1++|a4>1
  GPUStreamTensor2 & T_1p4p_c_1 = (((yab_g|xc_f)|gx_tilde)|epsilon)|psip;//<1++|a4>1

  GPUStreamTensor2 & T_1p4p_a_2 = gam%(S_mn|((ybc_g|xa_f)|gx_tilde))*B2;//<1++|f4>2
  GPUStreamTensor2 & T_1p4p_b_2 = gam%(S_mn|((yac_g|xb_f)|gx_tilde))*B2;//<1++|a4>2
  GPUStreamTensor2 & T_1p4p_c_2 = gam%(S_mn|((yab_g|xc_f)|gx_tilde))*B2;//<1++|a4>2
  ///************************* 1-+ ****************************************/
  GPUStreamTensor2 & T_1m2p_a_1 = g*(S_mn|(xa_d||ybc_d))*B1;//<1-+|f2>1
  GPUStreamTensor2 & T_1m2p_b_1 = g*(S_mn|(xb_d||yac_d))*B1;//<1-+|f2>1
  GPUStreamTensor2 & T_1m2p_c_1 = g*(S_mn|(xc_d||yab_d))*B1;//<1-+|f2>1

  // Here's a problem which I havn't figured out: the two methods below give different results
  GPUStreamTensor2 & T_1m2p_a_2 = gam%((trans_1342(epsilon)|x)|(xa_d||ybc_d))*B1;//<1-+|f2>2
  GPUStreamTensor2 & T_1m2p_b_2 = gam%((trans_1342(epsilon)|x)|(xb_d||yac_d))*B1;//<1-+|a2>2
  GPUStreamTensor2 & T_1m2p_c_2 = gam%((trans_1342(epsilon)|x)|(xc_d||yab_d))*B1;//<1-+|a2>2
  //GPUStreamTensor2 & T_1m2p_a_2 = gam%(epsilon|(x%(xa_d||ybc_d)))*B1;//<1-+|f2>2
  //GPUStreamTensor2 & T_1m2p_b_2 = gam%(epsilon|(x%(xb_d||yac_d)))*B1;//<1-+|a2>2
  //GPUStreamTensor2 & T_1m2p_c_2 = gam%(epsilon|(x%(xc_d||yab_d)))*B1;//<1-+|a2>2

  GPUStreamTensor2 & T_1m1m_b_1 = g*(S_mn|(xb_p%yac_p))*B1;//<1-+|pi1>1
  GPUStreamTensor2 & T_1m1m_c_1 = g*(S_mn|(xc_p%yab_p))*B1;//<1-+|pi1>1

  // The same problem
  GPUStreamTensor2 & T_1m1m_b_2 = gam%((trans_1342(epsilon)|x)|(xb_p%yac_p))*B1;//<1-+|a2>2
  GPUStreamTensor2 & T_1m1m_c_2 = gam%((trans_1342(epsilon)|x)|(xc_p%yab_p))*B1;//<1-+|a2>2
  //GPUStreamTensor2 & T_1m1m_b_2 = gam%(epsilon|(x%(xb_p%yac_p)))*B1;//<1-+|pi1>2
  //GPUStreamTensor2 & T_1m1m_c_2 = gam%(epsilon|(x%(xc_p%yab_p)))*B1;//<1-+|pi1>2
  /************************* 2++ ****************************************/
  GPUStreamTensor2 & T_2p2p_a_1 = xproj|((trans_1423(epsilon||ybc_d)|xa_p)|x);//<2++|f2>1
  GPUStreamTensor2 & T_2p2p_b_1 = xproj|((trans_1423(epsilon||yac_d)|xb_p)|x);//<2++|a2>1
  GPUStreamTensor2 & T_2p2p_c_1 = xproj|((trans_1423(epsilon||yab_d)|xc_p)|x);//<2++|a2>1

  GPUStreamTensor2 & T_2p2p_a_2 = g*((((xproj||ybc_d)|((trans_1423(epsilon)|xa_p)|x))|psip)|psip)*B2;//<2++|f2>2
  GPUStreamTensor2 & T_2p2p_b_2 = g*((((xproj||yac_d)|((trans_1423(epsilon)|xb_p)|x))|psip)|psip)*B2;//<2++|a2>2
  GPUStreamTensor2 & T_2p2p_c_2 = g*((((xproj||yab_d)|((trans_1423(epsilon)|xc_p)|x))|psip)|psip)*B2;//<2++|a2>2

  GPUStreamTensor2 & T_2p2p_a_3 = gam%(((xproj||ybc_d)|((trans_1423(epsilon)|xa_p)|x))|psip)*B2;//<2++|f2>2
  GPUStreamTensor2 & T_2p2p_b_3 = gam%(((xproj||yac_d)|((trans_1423(epsilon)|xb_p)|x))|psip)*B2;//<2++|a2>2
  GPUStreamTensor2 & T_2p2p_c_3 = gam%(((xproj||yab_d)|((trans_1423(epsilon)|xc_p)|x))|psip)*B2;//<2++|a2>2
  ///************************* 2-+ ****************************************/
  GPUStreamTensor2 & T_2m0p_a_1 = ((epsilon|(xa_d|gam))|psip)*B1;//<2-+|f0>1
  GPUStreamTensor2 & T_2m0p_b_1 = ((epsilon|(xb_d|gam))|psip)*B1;//<2-+|a0>1
  GPUStreamTensor2 & T_2m0p_c_1 = ((epsilon|(xc_d|gam))|psip)*B1;//<2-+|a0>1

  //GPUStreamTensor2 & T_2m0p_a_2 = S_mn*(xa_d|(psip%psip))*B3;//<2-+|f0>2
  //GPUStreamTensor2 & T_2m0p_b_2 = S_mn*(xb_d|(psip%psip))*B3;//<2-+|a0>2
  //GPUStreamTensor2 & T_2m0p_c_2 = S_mn*(xc_d|(psip%psip))*B3;//<2-+|a0>2
  GPUStreamTensor2 & T_2m0p_a_2 = S_mn*((psip%psip)|xa_d)*B3;//<2-+|f0>2
  GPUStreamTensor2 & T_2m0p_b_2 = S_mn*((psip%psip)|xb_d)*B3;//<2-+|a0>2
  GPUStreamTensor2 & T_2m0p_c_2 = S_mn*((psip%psip)|xc_d)*B3;//<2-+|a0>2

  GPUStreamTensor2 & T_2m0p_a_3 = gam%(S_mn|(xa_d|psip))*B3;//<2-+|f0>3
  GPUStreamTensor2 & T_2m0p_b_3 = gam%(S_mn|(xb_d|psip))*B3;//<2-+|a0>3
  GPUStreamTensor2 & T_2m0p_c_3 = gam%(S_mn|(xc_d|psip))*B3;//<2-+|a0>3

  GPUStreamTensor2 & T_2m2p_a_1 = ((epsilon|((xproj|ybc_d)|gam))|psip)*B1;//<2-+|f2>1
  GPUStreamTensor2 & T_2m2p_b_1 = ((epsilon|((xproj|yac_d)|gam))|psip)*B1;//<2-+|a2>1
  GPUStreamTensor2 & T_2m2p_c_1 = ((epsilon|((xproj|yab_d)|gam))|psip)*B1;//<2-+|a2>1

  GPUStreamTensor2 & T_2m2p_a_2 = S_mn*((xproj|ybc_d)|(psip%psip))*B3;//<2-+|f2>2
  GPUStreamTensor2 & T_2m2p_b_2 = S_mn*((xproj|yac_d)|(psip%psip))*B3;//<2-+|f2>2
  GPUStreamTensor2 & T_2m2p_c_2 = S_mn*((xproj|yab_d)|(psip%psip))*B3;//<2-+|f2>2

  GPUStreamTensor2 & T_2m2p_a_3 = gam%(S_mn|((xproj|ybc_d)|psip))*B3;//<2-+|f2>3
  GPUStreamTensor2 & T_2m2p_b_3 = gam%(S_mn|((xproj|yac_d)|psip))*B3;//<2-+|a2>3
  GPUStreamTensor2 & T_2m2p_c_3 = gam%(S_mn|((xproj|yab_d)|psip))*B3;//<2-+|a2>3
  /**********************************************************************/
  /**********************************************************************/
  ////////////////////////////////////////////////
  map<string, int> wavenum_dict;/////numbers of partial waves
  wavenum_dict["0mp_f0"]=1;
  wavenum_dict["0mp_a0"]=1;
  wavenum_dict["0mp_f2"]=1;
  wavenum_dict["0mp_a2"]=1;
  wavenum_dict["0mp_pi1"]=1;

  wavenum_dict["1pp_f0"]=2;
  wavenum_dict["1pp_a0"]=2;
  wavenum_dict["1pp_f2"]=4;
  wavenum_dict["1pp_a2"]=4;
  wavenum_dict["1pp_pi1"]=4;
  wavenum_dict["1pp_f4"]=2;
  wavenum_dict["1pp_a4"]=2;

  wavenum_dict["1mp_pi1"]=2;
  wavenum_dict["1mp_f2"]=2;
  wavenum_dict["1mp_a2"]=2;

  wavenum_dict["2mp_f0"]=3;
  wavenum_dict["2mp_a0"]=3;
  wavenum_dict["2mp_f2"]=3;
  wavenum_dict["2mp_a2"]=3;

  wavenum_dict["2pp_f2"]=3;
  wavenum_dict["2pp_a2"]=3;

  map<string,vector<GPUStreamTensor2 *> > orbital_dict;  /////////orbitals of partial waves
  orbital_dict["0mp_f0"].push_back(& T_0m0p_a_1);
  orbital_dict["0mp_a0"].push_back(& T_0m0p_b_1);  orbital_dict["0mp_a0"].push_back(& T_0m0p_c_1);
  orbital_dict["0mp_f2"].push_back(& T_0m2p_a_1);
  orbital_dict["0mp_a2"].push_back(& T_0m2p_b_1);  orbital_dict["0mp_a2"].push_back(& T_0m2p_c_1);
  orbital_dict["0mp_pi1"].push_back(& T_0m1m_b_1); orbital_dict["0mp_pi1"].push_back(& T_0m1m_c_1);

  orbital_dict["1mp_f2"].push_back(& T_1m2p_a_1);  orbital_dict["1mp_f2"].push_back(& T_1m2p_a_2);
  orbital_dict["1mp_a2"].push_back(& T_1m2p_b_1); orbital_dict["1mp_a2"].push_back(& T_1m2p_c_1); orbital_dict["1mp_a2"].push_back(& T_1m2p_b_2); orbital_dict["1mp_a2"].push_back(& T_1m2p_c_2);
  orbital_dict["1mp_pi1"].push_back(& T_1m1m_b_1); orbital_dict["1mp_pi1"].push_back(& T_1m1m_c_1); orbital_dict["1mp_pi1"].push_back(& T_1m1m_b_2); orbital_dict["1mp_pi1"].push_back(& T_1m1m_c_2);

  orbital_dict["1pp_f0"].push_back(& T_1p0p_a_1); orbital_dict["1pp_f0"].push_back(& T_1p0p_a_2);
  orbital_dict["1pp_a0"].push_back(& T_1p0p_b_1); orbital_dict["1pp_a0"].push_back(& T_1p0p_c_1); orbital_dict["1pp_a0"].push_back(& T_1p0p_b_2); orbital_dict["1pp_a0"].push_back(& T_1p0p_c_2);

  orbital_dict["1pp_f2"].push_back(& T_1p2p_a_1);
  orbital_dict["1pp_f2"].push_back(& T_1p2p_a_2);
  orbital_dict["1pp_f2"].push_back(& T_1p2p_a_3);
  orbital_dict["1pp_f2"].push_back(& T_1p2p_a_4);

  orbital_dict["1pp_pi1"].push_back(& T_1p1m_b_1);
  orbital_dict["1pp_pi1"].push_back(& T_1p1m_c_1);
  orbital_dict["1pp_pi1"].push_back(& T_1p1m_b_2);
  orbital_dict["1pp_pi1"].push_back(& T_1p1m_c_2);
  orbital_dict["1pp_pi1"].push_back(& T_1p1m_b_3);
  orbital_dict["1pp_pi1"].push_back(& T_1p1m_c_3);
  orbital_dict["1pp_pi1"].push_back(& T_1p1m_b_4);
  orbital_dict["1pp_pi1"].push_back(& T_1p1m_c_4);

  orbital_dict["1pp_a2"].push_back(& T_1p2p_b_1);
  orbital_dict["1pp_a2"].push_back(& T_1p2p_c_1);
  orbital_dict["1pp_a2"].push_back(& T_1p2p_b_2);
  orbital_dict["1pp_a2"].push_back(& T_1p2p_c_2);
  orbital_dict["1pp_a2"].push_back(& T_1p2p_b_3);
  orbital_dict["1pp_a2"].push_back(& T_1p2p_c_3);
  orbital_dict["1pp_a2"].push_back(& T_1p2p_b_4);
  orbital_dict["1pp_a2"].push_back(& T_1p2p_c_4);

  orbital_dict["1pp_f4"].push_back(& T_1p4p_a_1); orbital_dict["1pp_f4"].push_back(& T_1p4p_a_2);

  orbital_dict["1pp_a4"].push_back(& T_1p4p_b_1);
  orbital_dict["1pp_a4"].push_back(& T_1p4p_c_1);
  orbital_dict["1pp_a4"].push_back(& T_1p4p_b_2);
  orbital_dict["1pp_a4"].push_back(& T_1p4p_c_2);

  orbital_dict["2mp_f0"].push_back(& T_2m0p_a_1);
  orbital_dict["2mp_f0"].push_back(& T_2m0p_a_2);
  orbital_dict["2mp_f0"].push_back(& T_2m0p_a_3);

  orbital_dict["2mp_a0"].push_back(& T_2m0p_b_1);
  orbital_dict["2mp_a0"].push_back(& T_2m0p_c_1);
  orbital_dict["2mp_a0"].push_back(& T_2m0p_b_2);
  orbital_dict["2mp_a0"].push_back(& T_2m0p_c_2);
  orbital_dict["2mp_a0"].push_back(& T_2m0p_b_3);
  orbital_dict["2mp_a0"].push_back(& T_2m0p_c_3);

  orbital_dict["2mp_f2"].push_back(& T_2m2p_a_1);
  orbital_dict["2mp_f2"].push_back(& T_2m2p_a_2);
  orbital_dict["2mp_f2"].push_back(& T_2m2p_a_3);

  orbital_dict["2mp_a2"].push_back(& T_2m2p_b_1);
  orbital_dict["2mp_a2"].push_back(& T_2m2p_c_1);
  orbital_dict["2mp_a2"].push_back(& T_2m2p_b_2);
  orbital_dict["2mp_a2"].push_back(& T_2m2p_c_2);
  orbital_dict["2mp_a2"].push_back(& T_2m2p_b_3);
  orbital_dict["2mp_a2"].push_back(& T_2m2p_c_3);

  orbital_dict["2pp_f2"].push_back(& T_2p2p_a_1);
  orbital_dict["2pp_f2"].push_back(& T_2p2p_a_2);
  orbital_dict["2pp_f2"].push_back(& T_2p2p_a_3);

  orbital_dict["2pp_a2"].push_back(& T_2p2p_b_1);
  orbital_dict["2pp_a2"].push_back(& T_2p2p_c_1);
  orbital_dict["2pp_a2"].push_back(& T_2p2p_b_2);
  orbital_dict["2pp_a2"].push_back(& T_2p2p_c_2);
  orbital_dict["2pp_a2"].push_back(& T_2p2p_b_3);
  orbital_dict["2pp_a2"].push_back(& T_2p2p_c_3);

  /////////////////////////////////////////////////////////////////

  vector<char *> reso_name_X;//store the name of X's
  reso_name_X.clear();
  vector<GPUScalarPropagator *> propagator_vec_X;//for X(2370),X(1835),Xphsp,...
  propagator_vec_X.clear();
  //GPUScalarPropagator * resX=0;
  //GPUScalarPropagator * resY=0;

  vector<char *> reso_name_F;//store the names of fs
  reso_name_F.clear();
  vector<GPUScalarPropagator *> propagator_vecF;//for f0,f2,...
  propagator_vecF.clear();

  vector<char *> reso_name_A; //store the names of a's
  reso_name_A.clear();
  vector<GPUScalarPropagator *> propagator_vecA_b;//for a0,a2,...
  vector<GPUScalarPropagator *> propagator_vecA_c;//for a0,a2,...
  propagator_vecA_b.clear();
  propagator_vecA_c.clear();



  map<string, int>  add_X_num; //information about X ( sequence number in propagator_vec_X)
  map<string, string> add_X_jpc;
  map<string, vector<int> > add_Y_nums; //information about Y (sequence number in propagator_vecF/propagator_vecA_b/propagator_vecA_c)
  map<string, string> add_orbital_info; // wave string <=>  orbital string (key of  orbital_dict)

  const string filename_config="input/fileconfig.txt";
  ifstream  in;
  in.open(filename_config.c_str());

  string sline;
  string name,type_add,Xname;
  string st_jpc;
  int rank=0,status_add=0;
  string remain_left;

  int name_size=0;
  while(getline(in,sline)){
    if(sline.find("yes")!=string::npos){

      stringstream mysstream;
      mysstream.clear();
      mysstream<<sline;

      mysstream>>name>>Xname>>st_jpc >>type_add>>rank>>status_add >>remain_left;// one can change the style of input here |||| type_add -> (f/a); status_add(constant width or mass dependent)

      int index_X = ifhasX(reso_name_X, Xname);
      if(  index_X == -1 ){
	index_X=reso_name_X.size();
	name_size=Xname.size();
	char *pname=new char[name_size+1];
	strcpy(pname,Xname.c_str());

	reso_name_X.push_back(pname);
	propagator_vec_X.push_back(create_X_propagator(pname, sx));
      }

      if(type_add=='f'){
	int index_f = ifhasX(reso_name_F,name);

	if(index_f == -1){
	  index_f=reso_name_F.size();
	  name_size=name.size();
	  char *pname=new char[name_size+1];
	  strcpy(pname, name.c_str());
	  reso_name_F.push_back(pname);

	  propagator_vecF.push_back(create_f_propagator(pname, s23,rank,status_add%2));
	}

	string l_wname="f"+toString(rank)+"_"+Xname+"_"+st_jpc; //the key of add_X_num
	string l_orbital=st_jpc+"_f"+toString(rank); // the key of orbital_dict
	add_X_num[l_wname]=index_X;
	add_X_jpc[l_wname]=st_jpc;
	add_orbital_info[l_wname]=l_orbital;
	add_Y_nums[l_wname].push_back(index_f);

      }else{

	int index_a = ifhasX(reso_name_A, name);

	if( index_a == -1){
	  index_a=reso_name_A.size();
	  name_size=name.size();
	  char *pname= new char[name_size+1];
	  strcpy(pname, name.c_str());
	  reso_name_A.push_back(pname);

	  propagator_vecA_b.push_back(create_a_propagator(pname,s13,rank,status_add%2));
	  propagator_vecA_c.push_back(create_a_propagator(pname,s12,rank,status_add%2));
	}

	string l_wname="a"+toString(rank)+"_"+Xname+"_"+st_jpc;
	string l_orbital=st_jpc+"_a"+toString(rank);

	if(name.find("pi")!=string::npos){
	  l_wname="pi"+toString(rank)+"_"+Xname+"_"+st_jpc;
	  l_orbital=st_jpc+"_pi"+toString(rank);
	}

	add_X_num[l_wname]=index_X;
	add_X_jpc[l_wname]=st_jpc;
	add_orbital_info[l_wname]=l_orbital;
	add_Y_nums[l_wname].push_back(index_a);

      }
    }
  }
  in.close();

  char xname[200];char yname[200];

  vector<char *> ComplingPara_name; // store the name of compling parameters
  ComplingPara_name.clear();
  vector<GPUScalarPropagator *> ComplingPara_propa; //store the  propagators
  ComplingPara_propa.clear();

  vector<GPUTensor2Propagator *> vpro_tensor2;vpro_tensor2.clear();
  vector<GPUUnFactorizedRadiativePartialWave *> vec_unf_waves;vec_unf_waves.clear();

  map<string, int>::const_iterator map_it=add_X_num.begin();

  for(;map_it!=add_X_num.end();map_it++){
    string tmp_wname=map_it->first;  //// the key of add_X_num, mark the type of channel
    string xname_o=reso_name_X[add_X_num[tmp_wname]]; //// the name of X
    sprintf(xname,"%s_%s",xname_o.c_str(),(add_X_jpc[tmp_wname]).c_str());
    string y_head=add_orbital_info[tmp_wname].substr(4); // something like f0,f2,a0,f2,...

    if(y_head.find("f")!=string::npos){

      for(int m=0;m<add_Y_nums[tmp_wname].size();m++){    //
	string yname_o= reso_name_F[add_Y_nums[tmp_wname][m]]; // name of f0,f2, ...
	sprintf(yname,"%s",yname_o.c_str());

	for(int k=0;k<wavenum_dict[add_orbital_info[tmp_wname]];k++){  // partialWave of one type of chennel

	  addPartialWave(myanalysis, gpp, *orbital_dict[add_orbital_info[tmp_wname]][k],xname,*propagator_vec_X[add_X_num[tmp_wname]],yname, * propagator_vecF[add_Y_nums[tmp_wname][m]], k+1, vpro_tensor2,vec_unf_waves );

	}

      }



    }else{

      for(int m=0;m<add_Y_nums[tmp_wname].size();m++){
	string yname_o= reso_name_A[add_Y_nums[tmp_wname][m]];
	sprintf(yname,"%s",yname_o.c_str());

	for(int k=0;k<wavenum_dict[ add_orbital_info[tmp_wname] ];k++){

	  addPartialWave(myanalysis, gpp,*orbital_dict[add_orbital_info[tmp_wname]][k*2], *orbital_dict[add_orbital_info[tmp_wname]][k*2+1],xname,*propagator_vec_X[add_X_num[tmp_wname]],yname,*propagator_vecA_b[add_Y_nums[tmp_wname][m]], *propagator_vecA_c[add_Y_nums[tmp_wname][m]], k+1, vpro_tensor2, vec_unf_waves );

	}


      }

    }

  }


  // Here we should see that there are indeed four waves in the analysis
  cout << "Active waves: " << myanalysis->GetWaves()->GetNActiveWaves() << endl;
  p1.ReadFile(0);
  p2.ReadFile(0);
  p3.ReadFile(0);
  p1.ReadFile(1);
  p2.ReadFile(1);
  p3.ReadFile(1);

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

  //myanalysis->GetAmplitudes("wordge.dat");
  //const char * OPERATION = "PROJECTION";
  //	OPERATION="FIT";
  if (OPERATION == "FIT") {
    /* Now we can do the fit. Currently you can use either of the following fitters:
       -FUMILI (the Minuit2 implementation,
       -OLDFUMILI (the BES II implementation, in general requires fewest iterations),
       -MINUIT (with numerical gradients),
       -MINUITGRAD (with analytical gradients,
       -MINUITMINOS (MNUIT (numerical gradients) followed by a modified MINOS error estimation)
       */
    //myanalysis->DoFit(GPUPartialWaveAnalysis::OLDFUMILI);
    //myanalysis->DoFit(GPUPartialWaveAnalysis::MINUIT);
    if (FITTER == "OLDFUMILI")
      //myanalysis->DoMultiFit(GPUPartialWaveAnalysis::OLDFUMILI, SPREAD, NFIT);
      myanalysis->DoFit(GPUPartialWaveAnalysis::OLDFUMILI);
    else if (FITTER == "MINUIT")
      myanalysis->DoMultiFit(GPUPartialWaveAnalysis::MINUIT, SPREAD, NFIT);
    else if (FITTER == "MINUITDoFit")
      myanalysis->DoFit(GPUPartialWaveAnalysis::MINUIT);
    else if (FITTER == "MINUITGRAD")
      myanalysis->DoMultiFit(GPUPartialWaveAnalysis::MINUITGRAD, SPREAD, NFIT);
    else if (FITTER == "MINUITMINOS")
      myanalysis->DoMultiFit(GPUPartialWaveAnalysis::MINUITMINOS, SPREAD, NFIT);
    else {
      cout << "FITTER \"" << FITTER << "\" IS NOT SUPPORTED! EXIT..." << endl;
      exit (-1);
    }
    clock_t fitend = clock();
    cout << "fitend: " << (fitend - mcend) << " ticks = " << (float)( fitend - mcend)/(float)CLOCKS_PER_SEC << " s" << endl;

  }else if ( OPERATION == "DY_FIT") {
    /* Now we can do the fit. Currently you can use either of the following fitters:
       -FUMILI (the Minuit2 implementation,
       -OLDFUMILI (the BES II implementation, in general requires fewest iterations),
       -MINUIT (with numerical gradients),
       -MINUITGRAD (with analytical gradients,
       -MINUITMINOS (MNUIT (numerical gradients) followed by a modified MINOS error estimation)
       */
    if (FITTER == "OLDFUMILI"){
      myanalysis->DoDynamicFit(GPUPartialWaveAnalysis::OLDFUMILI,0.5,5, SPREAD, NFIT);
    }else if (FITTER == "MINUIT"){
      myanalysis->DoDynamicFit(GPUPartialWaveAnalysis::MINUIT, 0.5,5,SPREAD, NFIT);
    }else if (FITTER == "MINUITGRAD"){
      myanalysis->DoDynamicFit(GPUPartialWaveAnalysis::MINUITGRAD, 0.5,5,SPREAD, NFIT);
    }else if (FITTER == "MINUITMINOS"){
      myanalysis->DoDynamicFit(GPUPartialWaveAnalysis::MINUITMINOS, 0.5,5,SPREAD, NFIT);
    }else {
      cout << "FITTER \"" << FITTER << "\" IS NOT SUPPORTED! EXIT..." << endl;
      exit (-1);
    }
    clock_t fitend = clock();
    cout << "fitend: " << (fitend - mcend) << " ticks = " << (float)( fitend - mcend)/(float)CLOCKS_PER_SEC << " s" << endl;

  }else if (OPERATION == "PROJECTION") {
    /* Reset the cache for the Data (at index 0) in order to free some memory. If you have "out of memory"
       or "Cal ressource allocation" errors, remove the comment from the next line */
//    myanalysis->Reset(0);
//    /*And now we would like to plot some projections for the fit results. For this we need event-wise differential
//      x-sections for the Monte Carlo, which we are going to generate with the following line. The boolean argument denotes
//      whether the interference terms should also be plotted*/
  myanalysis->DoFit(GPUPartialWaveAnalysis::OLDFUMILI);
      
#ifdef PLOT
	myanalysis->Reset(0);
	GPUPlotset * plotset = new GPUPlotset();

	float ** dcs = myanalysis->GetMCDcs(true);
	myanalysis->Reset(1);

 	GPUStreamScalar &ct_g=costheta(gam);
//-----plot----------------------------------
	GPUStreamVector & pks1r= lorentzrotation(pks1,pksks);
 	GPUStreamVector & pksksr= lorentzrotation(pksks,pksks);
	GPUStreamVector & pks1b= lorentzboost(pks1r,pksksr);
 	GPUStreamScalar & ct_ks1=costheta(pks1b);
	GPUStreamScalar & ph_ks1=phi(pks1b);

	GPUStreamVector & pks2r= lorentzrotation(pks2,pksks);
	GPUStreamVector & pks2b= lorentzboost(pks2r,pksksr);
 	GPUStreamScalar & ct_ks2=costheta(pks2b);
	GPUStreamScalar & ph_ks2=phi(pks2b);

	GPUStreamVector & pks1er= lorentzrotation(pks1,petapks1);
 	GPUStreamVector & petapks1r= lorentzrotation(petapks1,petapks1);
	GPUStreamVector & pks1eb= lorentzboost(pks1er,petapks1r);
 	GPUStreamScalar & ct_ks1e=costheta(pks1eb);
	GPUStreamScalar & ph_ks1e=phi(pks1eb);

	GPUStreamVector & pks2er= lorentzrotation(pks2,petapks2);
 	GPUStreamVector & petapks2r= lorentzrotation(petapks2,petapks2);
	GPUStreamVector & pks2eb= lorentzboost(pks2er,petapks2r);
 	GPUStreamScalar & ct_ks2e=costheta(pks2eb);
	GPUStreamScalar & ph_ks2e=phi(pks2eb);

	GPUStreamVector & petapr= lorentzrotation(petap,x);
 	GPUStreamVector & xr= lorentzrotation(x,x);
	GPUStreamVector & petapb= lorentzboost(petapr,xr);
 	GPUStreamScalar & ct_etap=costheta(petapb);
	GPUStreamScalar & ph_etap=phi(petapb);
	// So first we create a set of plots, which takes care of the formatting and file handling
	int nwaves =  myanalysis->GetWaves()->GetNActiveWaves();
  
  float * dataweights = myanalysis->GetEventWeights();
  plotset->AddPlots(mx.Plot("mx","Invariant mass of #eta#pi^{0}#pi^{0}; M_{#eta#pi^{0}#pi^{0}}",100,2,2.8,dcs,nwaves,true,dataweights));
  plotset->AddPlots(m23.Plot("m23","Invariant mass of #pi^{0}#pi^{0}; M_{#pi^{0}#pi^{0}}",50,0.2,2.2,dcs,nwaves,true,dataweights));
  plotset->AddPlots(m13.Plot("m13","Invariant mass of #eta#pi^{0}_{2}; M_{#eta#pi^{0}}",60,0.6,2.6,dcs,nwaves,true,dataweights));
  plotset->AddPlots(m12.Plot("m12","Invariant mass of #eta#pi^{0}_{1}; M_{#eta#pi^{0}}",60,0.6,2.6,dcs,nwaves,true,dataweights));
  plotset->AddPlots(ct_g.Plot("ct_g","cos#theta of #gamma in J/#psi; cos#theta_{#gamma}",40,-1,1,dcs,nwaves,true,dataweights));
  plotset->AddPlots(ct_ks1.Plot("ct_ks1","cos#theta of #pi^{0} in #pi^{0}#pi^{0}; cos#theta_{#pi^{0}_{1}}",40,-1,1,dcs,nwaves,true,dataweights));
  plotset->AddPlots(ct_ks2.Plot("ct_ks2","cos#theta of #pi^{0} in #pi^{0}#pi^{0}; cos#theta_{#pi^{0}_{2}}",40,-1,1,dcs,nwaves,true,dataweights));
  plotset->AddPlots(ct_ks1e.Plot("ct_ks1e","cos#theta of #pi^{0} in #eta#pi^{0}; cos#theta_{#pi^{0}_{1}}",40,-1,1,dcs,nwaves,true,dataweights));
  plotset->AddPlots(ct_ks2e.Plot("ct_ks2e","cos#theta of #pi^{0} in #eta#pi^{0}; cos#theta_{#pi^{0}_{2}}",40,-1,1,dcs,nwaves,true,dataweights));
  plotset->AddPlots(ct_etap.Plot("ct_etap","cos#theta of #eta in #eta#pi^{0}#pi^{0}; cos#theta_{#eta}",40,-1,1,dcs,nwaves,true,dataweights));
	plotset->Format();

  //char * parout1;
  //char * parout2;
  //parout1=argv[1];
  //parout2=argv[1];
	plotset->WritePsfile("plot.ps",1,1);
	plotset->WriteRootfile("plot.root");
//    clock_t plotend = clock();
//    //cout << "Plots: " << (plotend-fitend) << " ticks = " << (float)(plotend -fitend)/(float)CLOCKS_PER_SEC << " sx" << endl;
//    clock_t end = clock();
//    cout << "Overall: " << (end-start) << " ticks = " <<  (float)(end-start)/(float)CLOCKS_PER_SEC << " sx" << endl;
#endif
  } else if (OPERATION == "MCINTEGRAL") {
//    myanalysis->Reset(0);
//    float ** dcs = myanalysis->GetMCDcs(true);
//    myanalysis->Reset(1);
//    int nwaves =  myanalysis->GetWaves()->GetNActiveWaves();
//    clock_t plotend = clock();
//    //cout << "Plots: " << (plotend-fitend) << " ticks = " << (float)(plotend -fitend)/(float)CLOCKS_PER_SEC << " sx" << endl;
//    clock_t end = clock();
//    cout << "Overall: " << (end-start) << " ticks = " <<  (float)(end-start)/(float)CLOCKS_PER_SEC << " sx" << endl;
  }
  else {
    cout << "OPERATION \"" << OPERATION << "\" NOT DEFINED! EXIT..." << endl;
    exit (-1);
  }








  /////////////////////////////////////////////////////EEEEEEEEEEEEEEnd
  vector<char *>name_waves=myanalysis->GetWaves()->GetWaveNames();
  for(vector<char *>::iterator it_name=name_waves.begin();it_name!=name_waves.end();it_name++){
    cout<<"AddWaves: "<<*it_name<<endl;
  }
  /////  cout<<"================================================ "<<endl;
  /////  int size1=reso_name_X.size();
  /////  for(int k=0;k<size1;k++){
  /////    cout<<k<<'\t'<<reso_name_X[k]<<'\t'<<propagator_vec_X[k]->GetName()<<endl;
  /////  }
  /////  cout<<endl;
  /////  int size2=reso_name_F.size();
  /////  for(int k=0;k<size2;k++){
  /////    cout<<k<<'\t'<<reso_name_F[k]<<'\t'<<propagator_vecF[k]->GetName()<<endl;
  /////  }
  /////  cout<<endl;
  /////  int size3=reso_name_A.size();
  /////  for(int k=0;k<size3;k++){
  /////    cout<<k<<'\t'<<reso_name_A[k]<<'\t'<<propagator_vecA_b[k]->GetName()<<'\t'<<propagator_vecA_c[k]->GetName()<<endl;
  /////  }
  /////  cout<<"================================================ 2"<<endl;


  //reslease memory!
  for(vector<char *>::iterator it = reso_name_X.begin(); it!=reso_name_X.end();it++){
    if(*it != 0){
      delete [] *it;
      *it=0;
    }
  }
  reso_name_X.clear();

  for(vector<char *>::iterator it = reso_name_F.begin(); it!=reso_name_F.end();it++){
    if(*it != 0){
      delete [] *it;
      *it=0;
    }
  }
  reso_name_F.clear();

  for(vector<char *>::iterator it = reso_name_A.begin(); it!=reso_name_A.end();it++){
    if(*it != 0){
      delete [] *it;
      *it=0;
    }
  }
  reso_name_A.clear();


  for(vector<char *>::iterator it = ComplingPara_name.begin(); it!=ComplingPara_name.end();it++){
    if(*it != 0){
      delete [] *it;
      *it=0;
    }
  }
  ComplingPara_name.clear();


  for(vector<GPUScalarPropagator *> :: iterator it = propagator_vec_X.begin(); it != propagator_vec_X.end();it++){
    if(*it !=0 ){
      delete *it;
      *it=0;
    }
  }
  propagator_vec_X.clear();

  for(vector<GPUScalarPropagator *> :: iterator it = propagator_vecF.begin(); it != propagator_vecF.end();it++){
    if(*it !=0 ){
      delete *it;
      *it=0;
    }
  }
  propagator_vecF.clear();

  for(vector<GPUScalarPropagator *> :: iterator it = propagator_vecA_b.begin(); it != propagator_vecA_b.end();it++){
    if(*it !=0 ){
      delete *it;
      *it=0;
    }
  }
  propagator_vecA_b.clear();

  for(vector<GPUScalarPropagator *> :: iterator it = propagator_vecA_c.begin(); it != propagator_vecA_c.end();it++){
    if(*it !=0 ){
      delete *it;
      *it=0;
    }
  }
  propagator_vecA_c.clear();

  for(vector<GPUScalarPropagator *> :: iterator it = ComplingPara_propa.begin(); it != ComplingPara_propa.end();it++){
    if(*it !=0 ){
      delete *it;
      *it=0;
    }
  }
  ComplingPara_propa.clear();

  for(vector<GPUTensor2Propagator *> :: iterator it = vpro_tensor2.begin(); it != vpro_tensor2.end();it++){
    if(*it !=0 ){
      delete *it;
      *it=0;
    }
  }
  vpro_tensor2.clear();

  for(vector<GPUUnFactorizedRadiativePartialWave *> :: iterator it = vec_unf_waves.begin(); it != vec_unf_waves.end();it++){
    if(*it !=0 ){
      delete *it;
      *it=0;
    }
  }
  vec_unf_waves.clear();

  return 0;
}
