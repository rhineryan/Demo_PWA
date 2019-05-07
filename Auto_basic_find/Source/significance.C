#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>   
#include <TMath.h>
#include <RooStats/RooStatsUtils.h>

using namespace std;
int significance()
{
   Int_t       nparam        =   4; 
   Double_t    deltaL        = -770.75; 
   Double_t    factor        = 2.0; 
   //
   cout<<"deltaL = "<<deltaL<<", nParam= "<<nparam<<endl;
   Double_t    prob          = TMath::Prob(factor*fabs(deltaL),nparam);
   Double_t    significance  = RooStats::PValueToSignificance(prob*0.5);
   cout<<"prob= "<<prob<<", significance= "<<significance<<endl;
   exit(0);

}
