#include <iomanip.h>
#include <TH1F.h>

//Double_t dgaus(Double_t *x, Double_t *par){
//
//Double_t value=0;
//
//if(par[1]!=0&&par[4]!=0) value =  exp(-0.5*(x[0]-par[0])*(x[0]-par[0])/(par[1]*par[1])) + par[2]*exp(-0.5*(x[0]-par[3])*(x[0]-par[3])/(par[4]*par[4]));
////value =  a*exp(-0.5*(x-b)*(x-b)/(c*c))+exp(-0.5*(x-d)*(x-d)/(e*e));
//return value;
//}

void Fitfraction(){
  gStyle->SetOptTitle(1);
  gStyle->SetTitleSize(0.08,"xy");
  gStyle->SetTitleXOffset(0.9);
  gStyle->SetTitleYOffset(0.8);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadTopMargin(0.12);
  gStyle->SetPadBottomMargin(0.16);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^Read the wanted wave and determin the number of N_want^^^^^^^^
   string Reso_want[100];
   int N_want=0;
   char want_wave[100];
   sprintf(want_wave,"Want_wave.inp");
   ifstream fwant(want_wave);  
   while( getline(fwant,Reso_want[N_want]) )
   {
     //cout << "Read from file: " <<Reso_want[N_want] << endl;
     N_want++;
   }
   int Num_tem=N_want*(N_want+1)/2;
   cout<<"N_want="<<N_want<<" Num_tem="<<Num_tem<<endl;
   const int Nwave=N_want; //The wave you add into you basic solution in wave.inp, not the number of actived wave.  
   const int number=3000;
   const int Num=Num_tem;  //Num = Nwave*(Nwave+1)/2; 
   double inter[Num][number]; 
   const double dd = 0.489*0.489*1225*1e+6;
   int igood =0;
 
    
   ofstream fitresult("./err.out");
   fitresult << setiosflags(ios::fixed)<<setprecision(10);
   
   for(int i=1;i<number;i++)
   {
   char file[1400];
   double t1=0, t2;
   sprintf(file,"../out/fraction_%i.out", i+1);
   ifstream f(file,ios::in);
   f>>t1;
   if(t1==0) continue;
   else {
        inter[0][igood]=t1;
//        cout<<"i="<<i<<"  "<<inter[0][igood]<<endl;
        for(int j=1;j<Num;j++)
        {
        f>>inter[j][igood];
    //    cout<<inter[j][i]<<endl;
        }    
   
   }
   igood++;
   f.close();
   }
   cout<<"igood="<<igood<<endl;

double low[Num],up[Num];
for(int i=0;i<Num;i++){
low[i]=getmin(inter[i],igood);
up[i]=getmax(inter[i],igood);
}
//cout<<"low[0]"<<low[0]<<endl;

TH1F *h0[Num];
TH1F *h[Num];
TF1 *fit[Num];
for (int i=0;i<Num;i++){
  h0[i] = new TH1F(Form("h0%d",i),Form("hist name of h0%d",i),300,low[i],up[i]);
}
for(int i=0; i<igood; i++){
  for(int j=0;j<Num;j++)
   h0[j]->Fill(inter[j][i]);
}
cout<<"Mean="<<h0[9]->GetMean()<<endl;
for (int i=0;i<Num;i++){
  h[i] = new TH1F(Form("h%d",i),Form("hist name of h%d",i),100,low[i],2*h0[i]->GetMean());
}
for(int i=0; i<igood; i++){
  for(int j=0;j<Num;j++)
   h[j]->Fill(inter[j][i]);
}
for (int i=0;i<Num;i++){
fit[i] = new TF1(Form("fit%d",i),"gaus",h[i]->GetBinCenter(1),h[i]->GetBinCenter(100));
}
for(int i=0;i<Num;i++)
{
h[i]->GetXaxis()->CenterTitle();
h[i]->GetXaxis()->SetTitle("fraction");
h[i]->GetYaxis()->SetTitle("Entries");
}

 Double_t  x0 = 0.65;
 Double_t  y0 = 0.7;
 TLatex *t = new TLatex();
 t->SetNDC();
 t->SetTextFont(62);
 t->SetTextColor(1);
 t->SetTextSize(0.09);
 t->SetTextAlign(12); 
 
int ifit=0; 
TCanvas *c=new TCanvas("c","c",1200,900);
if(Nwave%2==0)
{
  int ngridx=Nwave+1;
  int ngridy=Nwave/2;
}else
{
  int ngridx=Nwave;
  int ngridy=(Nwave+1)/2;

}
 c->Divide(ngridx,ngridy);
 for(int i=0;i<Num;i++)
 {
  //if((low[i]==1&&up[i]==0)||((fabs(low[i])<0.01)&&(fabs(up[i])<0.01)))  continue;
  c->cd(ifit+1);
  h[i]->Fit(fit[i],"E");
  h[i]->Draw("e");
  h[i]->SetMarkerSize(0.5);
  fit[i]->Draw("same");
  fit[i]->SetLineColor(2);
  fit[i]->SetLineStyle(2);
  ifit++;
  }
//***********************************output the all interference part into Inter.dat**********************************//
 ofstream fout_inter("Inter.dat");
 int Ntem1 =Nwave;
 int Ntem2 =Nwave;
 for(int i=0;i<Num;i++)
 {
   fout_inter<<setprecision(3)<<"fit"<<i+1<<" "<<fit[i]->GetParameter(1)*100<<" "<<fit[i]->GetParameter(2)*100<<endl;
   fitresult<<fit[i]->GetParameter(2)<<endl;
 }

//***********************************output the Reso itself into into Reso.dat****************************************//
 ofstream fout_Reso("Reso.dat");
 fout_Reso<<setprecision(3)<<"Reso1"<<" "<<fit[0]->GetParameter(1)*100<<" "<<fit[0]->GetParameter(2)*100<<endl;
 for(int i=0;i<Num;i++)
 {
 if(i == Ntem1 ) {
   fout_Reso<<setprecision(3)<<"Reso"<<i+1<<" "<<fit[i]->GetParameter(1)*100<<" "<<fit[i]->GetParameter(2)*100<<endl;
   Ntem2--;
   Ntem1=Ntem1+Ntem2;
 }
 }
//***********************************output the Num of each Reso into Num.dat*****************************************//
/*
  Ntem1 =Nwave;
  Ntem2 =Nwave;
   cout<<setprecision(3)<<"Nfit1"<<" "<<fit[0]->GetParameter(1)*100*300<<" +/- "<<fit[0]->GetParameter(2)*100*300<<endl;
 for(int i=0;i<Num;i++)
 {
 if(i == Ntem1 ) {
   cout<<setprecision(3)<<"Nfit"<<i+1<<" "<<fit[i]->GetParameter(1)*100*300<<" +/- "<<fit[i]->GetParameter(2)*100*300<<endl;
   Ntem2--;
   Ntem1=Ntem1+Ntem2;
 }
 }
 */
c->Print("fit_fraction.eps");
exit(0);
}

double getmin(double *ma,int num){
double low=1;
for(int i=0;i<num;i++)
if(ma[i]<low&&ma[i]!=0) 
{low=ma[i];
//cout<<"ma[i]"<<ma[i]<<endl;
}
return low;
}

double getmax(double *ma,int num){
double low=-1;
for(int i=0;i<num;i++)
if(ma[i]>low) low=ma[i];
return low;
}



