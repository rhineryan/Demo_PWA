#include "RooFit.h"

#include <iomanip>
#include "TMinuit.h"
#include "TMarker.h"
#include "TLine.h"
#include "TBox.h"
#include "TGaxis.h"
#include "TMatrix.h"
#include "TVector.h"
#include "../RooMyFitResult.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooEllipse.h"
#include "RooRandom.h"

void  GenRandPara(){
 srand((unsigned)time(NULL)); 
 const int number=3000; //Number of paras to be generated randomly.
 const int npar=82;   //number of pars including mag phase mass and width etc in para.out ,this number is equel to the lines of para.out and will substute by the Error_pre.sh automaticly.
// Four files para.out, Minuit_result.out, GlobalCorre.out, CovarianceCoef.out are needed as input

 double mag_lowlimit=-100.000;
 double mag_uplimit=100.000;
 double phs_lowlimit=-6.2832;
 double phs_uplimit=6.2832;
 double stepsize =0.01;

 gROOT->ProcessLine(".L ../RooMyFitResult.cxx");
 RooMyFitResult* r = new RooMyFitResult("lastMinuitFit","Last MINUIT fit") ;


 RooArgList constPars("constPars") ;
 RooArgList floatPars("floatPars") ;
 RooArgList globalcorr("globalcorrelation");
 TList  corrMatrix;

 ifstream f1("para.out", ios::in);

 int para_index[npar];
 TString para_name[npar];
 TString para_const[npar];
 double  para_value[npar];
 double para_error[npar]; 
 double para_low[npar];
 double para_up[npar]; 
 Int_t nfreevar=0;
 string wave_fixed_0; 

 for(int i=0; i<npar; i++){
    RooRealVar * var ;
    Int_t l=0;
    Bool_t isConstant(l==0) ;
    //f1>>para_index[i]>>para_name[i]>>para_const[i]>>para_value[i]>>para_error[i]>>para_low[i]>>para_up[i];
    f1>>para_index[i]>>para_name[i]>>para_const[i]>>para_value[i]>>para_error[i];
    cout<<para_name[i]<<endl; 
    string tt = para_name[i];
    if(i==2) wave_fixed_0 = para_name[i]; //stroe the fixed wave 

    if(para_const[i]=="limited") 
    {
       if(tt.find("_pha")!= string::npos) 
       var = new RooRealVar(para_name[i],para_name[i],para_value[i],-6.383200,6.283200) ;
       if(tt.find("_mag")!= string::npos)
       var = new RooRealVar(para_name[i],para_name[i],para_value[i],-100.0000,100.0000) ;
       var->setError(para_error[i]) ;
       floatPars.addOwned(*var) ;
       nfreevar++;
    } 
    else 
    {
      var =  new RooRealVar(para_name[i],para_name[i],para_value[i]);
      constPars.addOwned(*var) ;
    }
 }
 f1.close();

 ifstream f2("Minuit_result.out");
 string variable;
 double fmin;
 double edm;
 Int_t covq;
 Int_t Mstate;

 for(int i=0;i<4;i++)
 {
  double tmp;
  f2>>variable>>tmp; 
  if(variable=="fmin:") fmin=tmp;
  if(variable=="edm:") edm=tmp;
  if(variable=="covq:") covq=tmp;
  if(variable=="Mstate:") Mstate=tmp;
 }

 cout<<"covq= "<<covq<<endl;
 cout<<"edm= "<<edm<<endl;
 cout<<"fmin = "<<fmin<<endl;
 cout<<"Mstate = "<<Mstate<<endl;
 cout<<"Number of free parameters:"<<nfreevar<<endl;  
  ifstream f3("GlobalCorre.out", ios::in);
  vector<double>global_corre;
  for(int i=0; i<nfreevar;i++)
  {
   double tmp;
   f3>>tmp;
   global_corre.push_back(tmp);
//   cout<<global_corre[i]<<endl;
  }
  f3.close();
 

  ifstream f4("CovarianceCoef.out", ios::in);
  vector<double> covariance_coef;
  covariance_coef.clear();
  for(int i=0; i<nfreevar*nfreevar;i++)
  {
   double tmp;
   f4>>tmp;
//   cout<<"i= "<<i<<"tmp= "<<tmp<<endl;
   covariance_coef.push_back(tmp);
 //  cout<<covariance_coef[i]<<endl;
  }
  f4.close();
  //cout<<"covariance size"<<covariance_coef.size()<<endl;
 
   TIterator* vIter = floatPars.createIterator() ;
   RooAbsArg* arg ;
   Int_t idx(0) ;
   while((arg=(RooAbsArg*)vIter->Next())) {
     // Create global correlation value holder
     TString gcName("GC[") ;
     gcName.Append(arg->GetName()) ;
     gcName.Append("]") ;
     TString gcTitle(arg->GetTitle()) ;
     gcTitle.Append(" Global Correlation") ;
  //   cout<<gcName.Data()<<endl;
     globalcorr.addOwned(*(new RooRealVar(gcName.Data(),gcTitle.Data(),0.))) ;

     TString name("C[") ;
     name.Append(arg->GetName()) ;
     name.Append(",*]") ;
     RooArgList* corrMatrixRow = new RooArgList(name.Data()) ;
     corrMatrix.Add(corrMatrixRow) ;
     TIterator* vIter2 = floatPars.createIterator() ;
     RooAbsArg* arg2 ;
     while((arg2=(RooAbsArg*)vIter2->Next())) {

       TString cName("C[") ;
       cName.Append(arg->GetName()) ;
       cName.Append(",") ;
       cName.Append(arg2->GetName()) ;
       cName.Append("]") ;
       TString cTitle("Correlation between ") ;
       cTitle.Append(arg->GetName()) ;
       cTitle.Append(" and ") ;
       cTitle.Append(arg2->GetName()) ;
       corrMatrixRow->addOwned(*(new RooRealVar(cName.Data(),cTitle.Data(),0.))) ;
     }
     delete vIter2 ;
     idx++ ;
   }
   delete vIter ;
   TIterator *gcIter = globalcorr.createIterator() ;

   Int_t nparm = nfreevar;

   Int_t ndi, ndj,ndex;

  RooRealVar* gcVal = 0;
  for (int i = 1; i <= nparm; ++i) {
  //   ndi = i*(i + 1) / 2;
     std::vector<double> value_line;
     for (int j = 1; j <= nparm; ++j) {
       //int m    = TMath::Max(i,j);
       //int n    = TMath::Min(i,j);
       //ndex = m*(m-1) / 2 + n;
       //ndj  = j*(j + 1) / 2;
       //value_line.push_back(covariance_coef[ndex-1] / TMath::Sqrt(TMath::Abs(covariance_coef[ndi-1]*covariance_coef[ndj-1])));
       value_line.push_back(covariance_coef[(i-1)*nparm+j-1]); 
     }

     // Find the next global correlation slot to fill, skipping fixed parameters
     gcVal = (RooRealVar*) gcIter->Next() ;
     gcVal->setVal(global_corre[i-1]) ;

     // Fill a row of the correlation matrix
     TIterator* cIter = ((RooArgList*)corrMatrix.At(i-1))->createIterator() ;
     for (int it = 1; it <= nparm ; ++it) {
       RooRealVar* cVal = (RooRealVar*) cIter->Next() ;
       cVal->setVal(value_line[it-1]) ;
     }
     delete cIter ;
   }

   delete gcIter ;


  cout<<"**************************************"<<endl;


 r->setConstParList(constPars) ;
 r->setInitParList(floatPars) ;
 r->setFinalParList(floatPars) ;
 r->setMinNLL(fmin) ;
 r->setEDM(edm) ; 
 r->setCovQual(covq) ;
 r->setStatus(Mstate) ;
 r->setGlobalCorr(globalcorr);
 r->setCorrMatrix(corrMatrix);

//*******Test of GlobalCorr***************//

 //********Test of CorreMatrix***********//

//***************Generate random parameters***********************

    
 for(int it=0;it<number;it++)
 {
    char filename_[255];
    sprintf(filename_,"../randpara/rand_%i.txt", it+1);
    ofstream inputfile_(filename_);

    RooArgList  randpar = r->randomizePars();
   // cout<<"size="<<randpar.getSize()<<endl;
   
//***************Attention**********and change your code here****************

    //next line is to write the fixed parameters for a specified in you basic solution
    if(wave_fixed_0.find("_a")!= string::npos) //a need two waves, c.c channel
    {
      inputfile_<<setw(12)<<10*cos(1)<<setw(12)<<10*sin(1)<<endl;
      inputfile_<<setw(12)<<10*cos(1)<<setw(12)<<10*sin(1)<<endl;
    }else
    {
      inputfile_<<setw(12)<<10*cos(1)<<setw(12)<<10*sin(1)<<endl;
    }
    //In the next for loop, the output is dependent on your solution. The program only output the limited parameter into the rand.out. you need add the the parameters which is fixed to their c.c. channel but not write by this program automaticly.
    for( int i=0;i<randpar.getSize();i++)
    {
   
    //  RooRealVar * vv =(RooAbsReal*)randpar.at(4);
       
        string namet=((RooAbsArg*)randpar.at(i))->GetName();
     
        if(namet.find("_a")!= string::npos)
        {
          if(namet.find("_mag")!= string::npos)
          {
            //cout<<"Find a0 resonances="<<namet<<endl;
            double mag=((RooRealVar*)randpar.at(i))->getVal();
            double phs=((RooRealVar*)randpar.at(i+1))->getVal();
            inputfile_<<setw(12)<<mag*cos(phs)<<setw(12)<<mag*sin(phs)<<endl;
            inputfile_<<setw(12)<<mag*cos(phs)<<setw(12)<<mag*sin(phs)<<endl;
          }
        } 
        else if(namet.find("_mag")!= string::npos)
        //if(namet.find("_mag")!= string::npos)
        {
             //cout<<"Find other resonances="<<namet<<endl;
             double mag=((RooRealVar*)randpar.at(i))->getVal();
             double phs=((RooRealVar*)randpar.at(i+1))->getVal();
             inputfile_<<setw(12)<<mag*cos(phs)<<setw(12)<<mag*sin(phs)<<endl;
        }
    }
 } 
exit(0);
}






 
