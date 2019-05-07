//##################################xiongxa##########################################//
//To calculate the interference between any of two waves 
//Generate the partial wave according to a giving wave.inp file.
//Draw the mass plot for each resonance.
//If you want to draw some specify Jpc's contribution, you have to specify the wave 
//number series
//
//edit by xiongxa in 2017.1.17
//##################################xiongxa##########################################//
#include "TMath.h"
#include "fstream.h"
#include <vector>
#include <map>
using namespace std;

void Inter_generate_by_wave_forpi_v2(){

   //TCanvas *canvas0 = new TCanvas("canvas0", "canvas0",1588,261,1064,600);
   TCanvas *canvas0 = new TCanvas("canvas0", "canvas0",1588,261,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   //canvas0->Range(-0.3015198,-452.1392,2.920365,1796.762);
   canvas0->Range(-0.3015198,-452.1392,2.920365,1500.762);
   canvas0->SetFillColor(0);
   canvas0->SetBorderMode(0);
   canvas0->SetBorderSize(2);
   canvas0->SetTickx(1);
   canvas0->SetTicky(1);
   canvas0->SetLeftMargin(0.15);
   canvas0->SetRightMargin(0.3335849);
   canvas0->SetTopMargin(0.04895105);
   canvas0->SetBottomMargin(0.201049);
   canvas0->SetFrameFillStyle(0);
   canvas0->SetFrameLineWidth(2);
   canvas0->SetFrameBorderMode(0);
   canvas0->SetFrameFillStyle(0);
   canvas0->SetFrameLineWidth(2);
   canvas0->SetFrameBorderMode(0);
   canvas0->Divide(2,2);

   int debug = 0;
  //TString Dis_name_total[10] = {"mx","m23","m12","m13","ct_g","ct_etap","ct_ks1","ct_ks2","ct_ks1e","ct_ks2e"};
  //TString Dis_name_total[4] = {"ct_ks2x","ct_ks1x","ct_g","ct_etap"};
  //TString Dis_name_total[4] = {"ct_ks2x","ct_ks1x","ct_ks2x","ct_ks1x"};
  TString Dis_name_total[4] = {"ct_ks2","ct_ks1","ct_ks2","ct_ks1"};
  //TString Dis_name_total[4] = {"ct_ks2","ct_ks1"};
  void Cal_inter(TString Dis_name,TString root_file,int N_Ac,int N_size2,int Npar[],int style,int color,bool leg_s,TString name_leg,int Nleg);
   TString wave_name ="/besfs/groups/psip/psipgroup/user/xiongxa/GamEtaPi0Pi0/Alg_gg_xl/GPUPWA/gpupwa2.1_1/Bin_Bin_data_full_range/Bin_by_Bin/11/plot_dir/input/wave.inp";
  TString root_file = "/besfs/groups/psip/psipgroup/user/xiongxa/GamEtaPi0Pi0/Alg_gg_xl/GPUPWA/gpupwa2.1_1/Bin_Bin_data_full_range/Bin_by_Bin/11/plot_dir/plot.root";
  //**********Read waves adding in the basic solution********************//
   int N_input=0; //number of wave in wave.inp
   string s[100];  
   string s_sort[100];  
   ifstream fin(wave_name);  
   while( getline(fin,s[N_input]) )
     {    
        //cout << "Read from file: " << s[N_input] << endl;
        N_input++;
     }
   cout<<" Number of lines if "<<N_input<<endl;
//**********Read waves we wanted ***********************************************************
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
  //exit(0); 
   int Want_waveid[100][100];
   int len=N_want;
   int N_Ac=0;
   //ARR_LEN(Reso_want,len);
   for(int i=0;i<len;i++)
   {
     int N_want=0;
     int N_fa=0;
     int j1=0;
    for (int j=0;j<N_input;j++)
    {
      string X_mark = s[j].substr(10,1);
      string X_mark1 = s[j].substr(10,2);
      string X_jpc = s[j].substr(6,3);

      if(s[j].find(Reso_want[i])!=string::npos) 
      {
        cout<<"Reso_want[i]="<<Reso_want[i]<<endl;
        if(X_mark == "f") 
        {
          if(X_jpc=="0mp"||X_jpc=="1pp"||X_jpc=="2pp"||X_jpc=="2mp")
          {
            Want_waveid[i][j1]=N_fa;
            N_fa++;
            j1++;
          }
          if(X_jpc=="1pp"||X_jpc=="2pp"||X_jpc=="2mp")
          {
            if(X_jpc=="1pp" && X_mark1 == "f2")
            {
              Want_waveid[i][j1]=N_fa;
              N_fa++;
              j1++;
              Want_waveid[i][j1]=N_fa;
              N_fa++;
              j1++;
              Want_waveid[i][j1]=N_fa;
              N_fa++;
              j1++;
            }else{
              Want_waveid[i][j1]=N_fa;
              N_fa++;
              j1++;
            }
          }
          if(X_jpc=="2pp"||X_jpc=="2mp")
          {
            Want_waveid[i][j1]=N_fa;
            N_fa++;
            j1++;
          }
          //cout << "wave f: " << s_sort[j] << endl;
        }
        if(X_mark == "a") 
        {
          if(X_jpc=="0mp"||X_jpc=="1pp"||X_jpc=="2pp"||X_jpc=="2mp")
          {
            Want_waveid[i][j1]=N_fa;
            N_fa++;
            j1++;
          }
          if(X_jpc=="1pp"||X_jpc=="2pp"||X_jpc=="2mp")
          {
            if(X_jpc=="1pp" && X_mark1 == "a2")
            {
              Want_waveid[i][j1]=N_fa;
              N_fa++;
              j1++;
              Want_waveid[i][j1]=N_fa;
              N_fa++;
              j1++;
              Want_waveid[i][j1]=N_fa;
              N_fa++;
              j1++;
            }else
            {
              Want_waveid[i][j1]=N_fa;
              N_fa++;
              j1++;
            }
          }
          if(X_jpc=="2pp"||X_jpc=="2mp")
          {
            Want_waveid[i][j1]=N_fa;
            N_fa++;
            j1++;
          }
          //cout << "wave a: " << s_sort[j] << endl;
        }
      } 
      else
      {
        if(X_mark == "f") 
        {
          if(X_jpc=="0mp"||X_jpc=="1pp"||X_jpc=="2pp"||X_jpc=="2mp")
          {
            N_fa++;
          }
          if(X_jpc=="1pp"||X_jpc=="2pp"||X_jpc=="2mp")
          {
            if(X_jpc=="1pp" && X_mark1 == "f2")
            {
              N_fa++;
              N_fa++;
              N_fa++;
            }else
            {
              N_fa++;
            }
          }
          if(X_jpc=="2pp"||X_jpc=="2mp")
          {
            N_fa++;
          }
          //cout << "wave f: " << s_sort[j] << endl;
        }
        if(X_mark == "a") 
        {
          if(X_jpc=="0mp"||X_jpc=="1pp"||X_jpc=="2pp"||X_jpc=="2mp")
          {
            N_fa++;
          }
          if(X_jpc=="1pp"||X_jpc=="2pp"||X_jpc=="2mp")
          {
            if(X_jpc=="1pp" && X_mark1 == "a2")
            {
              N_fa++;
              N_fa++;
              N_fa++;
            }else
            {
              N_fa++;
            }
          }
          if(X_jpc=="2pp"||X_jpc=="2mp")
          {
            N_fa++;
          }
        }
      }
    }
    N_Ac=N_fa;
    Want_waveid[i][99]=j1;
    if(debug) cout<<"Want_waveid[i][99]"<<Want_waveid[i][99]<<endl;
   }
     
     for(int i=0;i<len;i++)
     {
       for(int j=0;j<Want_waveid[i][99];j++)
       {
         if(debug) cout<<"Want_waveid[i][j]="<<Want_waveid[i][j]<<endl;
       }
       if(debug) cout<<endl;
     }
     //exit(0);
  bool leg_s=true;   
  if(debug) cout<<"LL--here5"<<endl;
  for(int Nplot=0;Nplot<4;Nplot++)
  {
  int Nleg=1;
  if(Nplot!=0) leg_s=false;
  TString Dis_name = Dis_name_total[Nplot];
  canvas0->cd(Nplot+1);
  TFile  *datafile1 = new TFile(root_file);
  //TH1F* H_data = new TH1F("data","data",100,2,2.8); 
  TH1F* H_data; 
  TH1F* H_data1; 
  TH1F* H_data2; 
  TString data_name1 =  "ct_ks1_Data";
  TString data_name2 = "ct_ks2_Data";
  H_data1= (TH1F*)datafile1->Get(data_name1);
  H_data2= (TH1F*)datafile1->Get(data_name2);
  H_data=H_data1;
  H_data->Add(H_data2,1);
  TLegend *leg = new TLegend(0.6,0.8,0.8,0.85,NULL,"brNDC");
  leg->SetTextSize(0.04237288);
  leg->SetTextFont(42);
  leg->SetLineColor(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetShadowColor(0);
  leg->AddEntry(H_data,"Data","p");
  //leg->Draw();
     
   if(debug) cout<<"LL--here5"<<endl;
  //for 1835,2370,phsp
  if(Dis_name == "mx") {plotdata(H_data,"M(#eta#pi^{0}#pi^{0})","Events/(GeV/c^{2})");}
  if(Dis_name == "m23"){plotdata(H_data,"M(#pi^{0}#pi^{0})","Events/(GeV/c^{2})");}
  if(Dis_name == "m12"){plotdata(H_data,"M(#eta#pi^{0}_{1})","Events/(GeV/c^{2})");}
  if(Dis_name == "m13"){plotdata(H_data,"M(#eta#pi^{0}_{2})","Events/(GeV/c^{2})");}
  if(Dis_name == "ct_g"){plotdata(H_data,"cos#theta_{#gamma}","Events");}
  if(Dis_name == "ct_etap"){plotdata(H_data,"cos#theta_{#eta}","Events");}
  if(Dis_name == "ct_ks1"){plotdata(H_data,"cos#theta_{#pi^{0}}","Events");}
  if(Dis_name == "ct_ks2"){plotdata(H_data,"cos#theta_{#pi^{0}}","Events");}
  if(Dis_name == "ct_ks1x"){plotdata(H_data,"cos#theta_{#pi_{1}^{0}}","Events");}
  if(Dis_name == "ct_ks2x"){plotdata(H_data,"cos#theta_{#pi_{2}^{0}}","Events");}
  H_data->GetYaxis()->SetRangeUser(0,3*H_data->GetMaximum());
  Nleg=1;
  if(leg_s) leg->Draw();
  int Npar_tem[100];

  const int Want_nwave=len; //number of wave that we want
  for(int j=0;j<Want_nwave;j++)
  {
    if(debug) cout<<"Reso_want[j]="<<Reso_want[j]<<" Want_waveid[j][99]="<<Want_waveid[j][99]<<endl;
    for(int wi=0;wi<Want_waveid[j][99];wi++)
    {
      //if(debug) cout<<"Want_waveid["<<j<<"]["<<wi<<"]"<<Want_waveid[j][wi]<<endl;
      cout<<"Want_waveid["<<j<<"]["<<wi<<"]"<<Want_waveid[j][wi]<<endl;
      Npar_tem[wi]=Want_waveid[j][wi];
    }
    //if(j==2)
    //{
    //  for()
    cout<<Reso_want[j]<<endl;
    if(j+3<10) {Cal_inter(Dis_name,root_file,N_Ac,Want_waveid[j][99],Npar_tem,1,j+3,leg_s,Reso_want[j],Nleg); Nleg++;}
    if(j+3>9) {Cal_inter(Dis_name,root_file,N_Ac,Want_waveid[j][99],Npar_tem,2,(j+3)-8,leg_s,Reso_want[j],Nleg); Nleg++;}
  }

  int Npar_total[100];
  for(int Ntot=0;Ntot<N_Ac;Ntot++) Npar_total[Ntot] = Ntot;
  Cal_inter(Dis_name,root_file,N_Ac,N_Ac,Npar_total,1,2,leg_s,"Total fit",Nleg); Nleg++;
  }
  canvas0->Print("Total.eps");
}

void Cal_inter(TString Dis_name,TString root_file,int N_Ac,int N_size2,int Npar[],int style,int color,bool leg_s,TString name_leg,int Nleg)
{
  TFile  *datafile1 = new TFile(root_file);
  const int N_par_wave=N_Ac;
  //read the interference value between any of two partial wave--------------------
  TString name_tmp0;
  TString name_tmp1;
  TString name_tmp2;
  char name_tmp[500];
  char* hisname[N_par_wave][N_par_wave];
  char* hisname1[N_par_wave][N_par_wave];
  char* hisname2[N_par_wave][N_par_wave];
  float interf[N_par_wave][N_par_wave],interf_sum[N_par_wave][N_par_wave];
  TH1F* H_NN[N_par_wave][N_par_wave];
  TH1F* H_NN1[N_par_wave][N_par_wave];
  TH1F* H_NN2[N_par_wave][N_par_wave];

  for(int i=0;i<N_par_wave;i++)
  {
    for(int j=i;j<N_par_wave;j++)
    {
      if(i==j)
      {
        sprintf(name_tmp,"_MC_wave_%d",j);
      }
      else
      {
       sprintf(name_tmp,"_MC_interference_%d_%d",i,j);
      }
      name_tmp0 = name_tmp;
      name_tmp1 = "ct_ks1" + name_tmp0;
      name_tmp2 = "ct_ks2" + name_tmp0;
      //name_tmp1 = Dis_name + name_tmp1;
      hisname1[i][j]=name_tmp1;
      hisname2[i][j]=name_tmp2;
      H_NN1[i][j] = (TH1F*)datafile1->Get(hisname1[i][j]);
      H_NN[i][j] = (TH1F*)datafile1->Get(hisname2[i][j]);
      H_NN[i][j]->Add(H_NN1[i][j],1);
      //interf[i][j]=H_NN[i][j]->Integral();
      //std::cout<<"The interference between wave"<<i<<" and wave"<<j<<" is "<<interf[i][j]<<std::endl;
    }
  }

  TH1F* H_total; 
  H_total= H_NN[Npar[0]][Npar[0]];
  for(int i1=0;i1<N_size2;i1++)
  {
    for(int i2=i1;i2<N_size2;i2++)
    {
      if(i1==i2&&i1==0) continue;
      //cout<<"i1="<<i1<<" i2=="<<i2<<endl;
      H_total->Add(H_NN[Npar[i1]][Npar[i2]],1);
    }
  }
  //cout<<H_total->Integral(37.5,43.75)<<endl;
  cout<<H_total->Integral()<<endl;
  double y1=0.8-0.04*Nleg;
  double y2=0.85-0.04*Nleg;
  plotphsp(H_total,style,color);
  TLegend *leg = new TLegend(.6,y1,.8,y2,NULL,"brNDC");
  //TLegend *leg = new TLegend(.2,y1,.3,y2,NULL,"brNDC");
  leg->SetTextSize(0.04237288);
  leg->SetTextFont(42);
  leg->SetLineColor(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetShadowColor(0);
  leg->AddEntry(H_total,name_leg,"l");
  if(leg_s) leg->Draw();
  }
void plotdata(TH1F *h1,const char *name1,const char *name2)
{
  //h1->GetXaxis()->SetTickLength(0.04);
  //h1->GetXaxis()->SetLabelSize(0.04);
  //h1->GetXaxis()->SetTitleOffset(1.5);
  h1->GetXaxis()->SetTitle(name1);
  h1->GetXaxis()->CenterTitle();
  //h1->GetYaxis()->SetTickLength(0.04);
  //h1->GetYaxis()->SetLabelSize(0.04);
  h1->GetYaxis()->SetTitleOffset(1.);
  h1->GetYaxis()->SetTitle(name2);
  h1->GetYaxis()->CenterTitle();
  h1->SetMarkerStyle(20);
  //h1->SetMarkerSize(0.7);
  h1->SetMarkerColor(2.);
  //h1->GetYaxis()->SetRangeUser(0,1.2*h1->GetMaximum());
  h1->Draw("e");
}
void plotphsp(TH1F *h1,int style, int color)
{
  //h1->GetXaxis()->SetTickLength(0.04);
  //h1->GetXaxis()->SetLabelSize(0.04);
  //h1->GetXaxis()->SetTitleOffset(1.1);
  //h1->GetYaxis()->SetTickLength(0.04);
  //h1->GetYaxis()->SetLabelSize(0.04);
  //h1->GetYaxis()->SetTitleOffset(1.8);
  //h1->GetYaxis()->SetTitle("EVENTS");
  h1->SetLineWidth(2);
  h1->SetLineStyle(style);
  h1->SetLineColor(color);
  //h1->GetYaxis()->SetRangeUser(0,1.2*h1->GetMaximum());
  h1->Draw("same");
}
void canvas()
{
   TCanvas *canvas = new TCanvas("canvas","canvas",800,600); 
   canvas->SetFillColor(0);
   canvas->SetBorderSize(2);
   canvas->SetLeftMargin(0.15);
   canvas->SetRightMargin(0.05);
   canvas->SetTopMargin(0.05);
   canvas->SetFrameFillStyle(0);
   canvas->SetFrameBorderMode(0);
   gStyle->SetLegendBorderSize(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetPadBorderSize(0);
   gStyle->SetPadTopMargin(0.05);
   gStyle->SetPadBottomMargin(0.1);
   gStyle->SetPadLeftMargin(0.05); //0.21
   gStyle->SetPadRightMargin(0.05); //0.05
   gStyle->SetOptStat(0000);
   gStyle->SetOptTitle(0000);
   //gPad->SetLogy();
}
