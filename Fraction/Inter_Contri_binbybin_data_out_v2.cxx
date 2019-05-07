//##################################xiongxa##########################################//
//To calculate the interference between any of two waves 
//Draw the mass plot of the different waves contribution 
//
//edit by xiongxa in 2017.1.17
//##################################xiongxa##########################################//
#include "TMath.h"
#include "fstream.h"
#include <vector>
typedef std::vector<int> Vint;
typedef std::vector<double> Vdouble;

void Inter_Contri_binbybin_data_out(){
   TCanvas *canvas0 = new TCanvas("canvas0", "canvas0",1588,261,1064,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   canvas0->Range(-0.3015198,-452.1392,2.920365,1796.762);
   canvas0->SetFillColor(0);
   canvas0->SetBorderMode(0);
   canvas0->SetBorderSize(2);
   canvas0->SetTickx(1);
   canvas0->SetTicky(1);
   canvas0->SetLeftMargin(0.15);
   canvas0->SetRightMargin(0.2335849);
   canvas0->SetTopMargin(0.04895105);
   canvas0->SetBottomMargin(0.201049);
   canvas0->SetFrameFillStyle(0);
   canvas0->SetFrameLineWidth(2);
   canvas0->SetFrameBorderMode(0);
   canvas0->SetFrameFillStyle(0);
   canvas0->SetFrameLineWidth(2);
   canvas0->SetFrameBorderMode(0);
//##################################xiongxa##########################################//
//To calculate the interference between any of two waves 
//Draw the mass plot of the different waves contribution 
//
//edit by xiongxa in 2017.1.17
//##################################xiongxa##########################################//
  int ttt=1;
  if(ttt==1){

  //TFile f("bin_by_bin_mx.root","recreate");
  int Nleg=1;
  TString Dis_name = "mx";

  int Nbin,low,up;
  if(Dis_name == "mx")  {Nbin=80;low=2;up=2.8;}
  if(Dis_name == "m23") {Nbin=50;low=0.2;up=2.2;}
  if(Dis_name == "m13") {Nbin=60;low=0.6;up=2.6;}
  if(Dis_name == "m12") {Nbin=60;low=0.6;up=2.6;}
  //TH1F* H_ini = new TH1F("ini","ini",Nbin,low,up); 
  TH1F* H_ini = new TH1F("ini","ini",80,2,2.8); 

  TFile* f =new TFile("bin_by_bin_mx.root","recreate");
  H_ini->Write();
  f->Close();
  delete f;

  const int nbins=16;
  int Cal_inter(TString Root_name,int N_par_wave0,TString Out_name,TString Dis_name,int N_size2,int Npar[],int style,int color,TString name_leg,int Nleg);
  for(int ibin=0;ibin<nbins;ibin++)
  //for(int i=12;i<13;i++)
  {
  cout<<"ibin="<<ibin<<endl;
  TString tem;
  char c[20];
  sprintf(c,"%d",ibin);
  tem = c;
  TString File_name = "mc" + tem;
  TString Root_file = "/besfs/groups/psip/psipgroup/user/xiongxa/GamEtaPi0Pi0/Alg_gg_xl/GPUPWA/gpupwa2.1_1/Bin_Bin_data_v2/" + tem + "/plot_dir/plot.root";
  TString wave_name = "/besfs/groups/psip/psipgroup/user/xiongxa/GamEtaPi0Pi0/Alg_gg_xl/GPUPWA/gpupwa2.1_1/Bin_Bin_data_v2/" + tem + "/plot_dir/input/wave.inp";

  //TString his_data = File_name + "data" + tem;
  //TFile* datafile1 =new TFile(Root_file);
  ////TH1F* H_data = new TH1F(his_data,his_data,Nbin,low,up); 
  //TH1F* H_data = new TH1F(his_data,his_data,100,2,2.8); 
  //TH1F* H_data0;
  //TString data_name = "mx_Data";
  //H_data0= (TH1F*)datafile1->Get(data_name);
  //H_data->Add(H_data0,1);

  //TFile* f =new TFile("bin_by_bin_mx.root","UPDATE");
  ////TFile f("bin_by_bin_mx.root","UPDATE");
  //H_data->Write();
  //datafile1->Close();
  //f->Close();
  //delete H_data;
  //delete f;

  int debug = 0;
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
        //cout<<"Reso_want[i]="<<s[j]<<endl;
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
  int Nleg=1;
  //if(Nplot!=0) leg_s=false;
  //TString Dis_name = Dis_name_total[Nplot];
     
   if(debug) cout<<"LL--here5"<<endl;
  Nleg=1;
  //if(leg_s) leg->Draw();
  int Npar_tem[100];

  const int Want_nwave=len; //number of wave that we want
  for(int j=0;j<Want_nwave;j++)
  {
    if(debug) cout<<"Reso_want[j]="<<Reso_want[j]<<" Want_waveid[j][99]="<<Want_waveid[j][99]<<endl;
    for(int wi=0;wi<Want_waveid[j][99];wi++)
    {
      if(debug) cout<<"Want_waveid["<<j<<"]["<<wi<<"]"<<Want_waveid[j][wi]<<endl;
      Npar_tem[wi]=Want_waveid[j][wi];
    }
    TString Reso_want_tem = Reso_want[j];
    TString Out_name = File_name + Reso_want_tem + tem;
    //write to root
    Cal_inter(Root_file,N_Ac,Out_name,Dis_name,Want_waveid[j][99],Npar_tem,2,2,"ibin",Nleg); Nleg++;
  }
  //int Npar_total[100];
  //for(int Ntot=0;Ntot<N_Ac;Ntot++) Npar_total[Ntot] = Ntot;
  //Cal_inter(Dis_name,root_file,N_Ac,N_Ac,Npar_total,1,2,leg_s,"Total fit",Nleg); Nleg++;
  }
  //cout<<__LINE__<<endl;
  
  //plot to grahp
  TFile* f1 =new TFile("bin_by_bin_mx.root");
  
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
   Vdouble fit_item[nbins];
   //for(int i=0;i<nbins;i++){fit_item[0].push_back(i);cout<<fit_item[0][i]<<endl;}
  double Total_tem=0;
  double  fit_mx[nbins]={0};
  TH1F* H_tem[500];
  for(int i=0;i<nbins;i++)
  {
    fit_mx[i] = 2.0+0.05*i+0.025;
    char c[20];
    TString tem1;
    sprintf(c,"%d",i);
    tem1 = c;
    TString File_name1 = "mc" + tem1;

    int ihist=0;
    for(int iwant=0;iwant<N_want;iwant++)
    {
      TString Reso_want_tem = Reso_want[iwant];
      TString hisdat = File_name1 + Reso_want_tem + tem1;
      H_tem[ihist] = (TH1F*)f1->Get(hisdat);
      fit_item[iwant].push_back(H_tem[ihist]->Integral());
      if(debug) cout<<"Reso_want_tem="<<Reso_want_tem<<" fit_item[iwant]="<<H_tem[ihist]->Integral()<<endl;
      ihist++;
    }
  }
  //TH1F* H_total=new TH1F("H_total","H_total",100,2,2.8);
  //plotgraph(H_total,16,0,0,"",0);
  //H_total->Draw();
  for(int idraw=0;idraw<N_want;idraw++)
  {
    double fit_item_tem[nbins]={0};
    for(int iibin=0;iibin<nbins;iibin++)
    {
      fit_item_tem[iibin]=fit_item[idraw][iibin];
    }
    if(idraw==0) {
      TGraph *gr0 = new TGraph (nbins, fit_mx, fit_item_tem);
      gr0->SetMarkerColor(2);gr0->Draw("ALP*");
      gr0->GetYaxis()->SetRangeUser(0,5000);
      gr0->GetYaxis()->SetTitle("Events/(0.05GeV/c^{2})");
      gr0->GetXaxis()->SetTitle("M(#eta#pi^{0}#pi^{0})");} 

    if(idraw==1) {TGraph *gr1 = new TGraph (nbins, fit_mx, fit_item_tem);gr1->SetMarkerColor(3);gr1->Draw("LP*");} 
    if(idraw==2) {TGraph *gr2 = new TGraph (nbins, fit_mx, fit_item_tem);gr2->SetMarkerColor(4);gr2->Draw("LP*");} 
    if(idraw==3) {TGraph *gr3 = new TGraph (nbins, fit_mx, fit_item_tem);gr3->SetMarkerColor(5);gr3->Draw("LP*");} 
    if(idraw==4) {TGraph *gr4 = new TGraph (nbins, fit_mx, fit_item_tem);gr4->SetMarkerColor(6);gr4->Draw("LP*");} 
    if(idraw==5) {TGraph *gr5 = new TGraph (nbins, fit_mx, fit_item_tem);gr5->SetMarkerColor(7);gr5->Draw("LP*");} 
    if(idraw==6) {TGraph *gr6 = new TGraph (nbins, fit_mx, fit_item_tem);gr6->SetMarkerColor(8);gr6->Draw("LP*");} 
    if(idraw==7) {TGraph *gr7 = new TGraph (nbins, fit_mx, fit_item_tem);gr7->SetMarkerColor(9);gr7->Draw("LP*");} 
    if(idraw==8) {TGraph *gr8 = new TGraph (nbins, fit_mx, fit_item_tem);gr8->SetMarkerColor(11);gr8->Draw("LP*");} 
    if(idraw==9) {TGraph *gr9 = new TGraph (nbins, fit_mx, fit_item_tem);gr9->SetMarkerColor(46);gr9->Draw("LP*");} 

  }
   //gr0->Draw("P*");
   //gr0->GetYaxis()->SetRangeUser(0,3500);
   //gr0->GetYaxis()->SetTitle("Events/(0.05GeV/c^{2})");
   //gr0->GetXaxis()->SetTitle("M(#eta#pi^{0}#pi^{0})");

   TLegend *leg = new TLegend(.783,.2,.938,.95,NULL,"brNDC");
   leg->SetTextSize(0.04237288);
   leg->SetTextFont(42);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetShadowColor(0);
   for(int idraw=0;idraw<N_want;idraw++)
   {
     TString Reso_want_tem = Reso_want[idraw];
     TString leg_name = Reso_want_tem +"";
     if(idraw==0) {leg->AddEntry(gr0,leg_name,"p");}
     if(idraw==1) {leg->AddEntry(gr1,leg_name,"p");}
     if(idraw==2) {leg->AddEntry(gr2,leg_name,"p");}
     if(idraw==3) {leg->AddEntry(gr3,leg_name,"p");}
     if(idraw==4) {leg->AddEntry(gr4,leg_name,"p");}
     if(idraw==5) {leg->AddEntry(gr5,leg_name,"p");}
     if(idraw==6) {leg->AddEntry(gr6,leg_name,"p");}
     if(idraw==7) {leg->AddEntry(gr7,leg_name,"p");}
     if(idraw==8) {leg->AddEntry(gr8,leg_name,"p");}
     if(idraw==9) {leg->AddEntry(gr9,leg_name,"p");}
   }
   leg->Draw();
}
  //if(Dis_name == "mx")  canvas0->Print("metapi0pi0_x.eps");
  //if(Dis_name == "m23") canvas0->Print("mpi0pi0_x.eps");
  //if(Dis_name == "m12") canvas0->Print("metapi01_x.eps");
  //if(Dis_name == "m13") canvas0->Print("metapi02_x.eps");

}

void Cal_inter_hist(TString Dis_name,int N_size2,int Npar[],int style,int color,TString name_leg,int Nleg)
{
  TFile  *datafile1 = new TFile("/besfs/groups/psip/psipgroup/user/xiongxa/GamEtaPi0Pi0/Alg_gg_xl/GPUPWA/gpupwa2.1_1/Sampling/0/files/1pp_all/par_1_1.root");
  const int N_par_wave=33;
  //read the interference value between any of two partial wave--------------------
  TString name_tmp1;
  char name_tmp[500];
  char* hisname[N_par_wave][N_par_wave];
  float interf[N_par_wave][N_par_wave],interf_sum[N_par_wave][N_par_wave];
  TH1F* H_NN[N_par_wave][N_par_wave];
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
      name_tmp1 = name_tmp;
      name_tmp1 = Dis_name + name_tmp1;
      hisname[i][j]=name_tmp1;
      H_NN[i][j] = (TH1F*)datafile1->Get(hisname[i][j]);
      interf[i][j]=H_NN[i][j]->Integral();
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
  const int Num=16;
  plotgraph(H_total,Num,style,color,name_leg,Nleg);
  cout<<H_total->Integral()<<endl;
  /*
  double y1=0.928-0.04*Nleg;
  double y2=0.968-0.04*Nleg;
  //plotphsp(H_total,style,color);
  TLegend *leg = new TLegend(.783,y1,.938,y2,NULL,"brNDC");
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
  //leg->Draw();
  */
  }


//Nind is to define the number of independent amplitude in one partile wave,eg:1-+->0++ has one independent amplitude, however 1-+->2++ has three independent amplitudes
//Npar is to define which independent amplitudes numbers showed in the root file.eg if Nind[i] =1,means Npar[] has one number corresponding to it,if Nind[i] = 3 means Npar[] has three numbers corresponding to it.
//int Cal_inter(int Nbin,int low,int up,TString Root_name,int N_par_wave0,TString Out_name,TString Dis_name,int N_size2,vector <int> Npar,int style,int color,TString name_leg,int Nleg)
int Cal_inter(TString Root_name,int N_par_wave0,TString Out_name,TString Dis_name,int N_size2,int Npar[],int style,int color,TString name_leg,int Nleg)
{
  if(N_size2 ==0)
  {
    TH1F* H_total=new TH1F(Out_name,Out_name,80,2,2.8);
    TFile* f =new TFile("bin_by_bin_mx.root","UPDATE");
    //TFile f("bin_by_bin_mx.root","UPDATE");
    H_total->Write();
    f->Close();
    delete H_total;
    delete f;
    return 1;
  }
  //cout<<__LINE__<<" Enter write waves"<<endl;
  TFile  *datafile1 = new TFile(Root_name);
  //read the interference value between any of two partial wave--------------------
  const int N_par_wave = N_par_wave0;
  TString name_tmp1;
  char name_tmp[500];
  char* hisname[N_par_wave][N_par_wave];
  float interf[N_par_wave][N_par_wave],interf_sum[N_par_wave][N_par_wave];
  TH1F* H_NN[N_par_wave][N_par_wave];
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
      name_tmp1 = name_tmp;
      name_tmp1 = Dis_name + name_tmp1;
      hisname[i][j]=name_tmp1;
      H_NN[i][j] = (TH1F*)datafile1->Get(hisname[i][j]);
      interf[i][j]=H_NN[i][j]->Integral();
      //std::cout<<"The interference between wave"<<i<<" and wave"<<j<<" is "<<interf[i][j]<<std::endl;
    }
  }

  double Total_int=0;
  TH1F* H_total=new TH1F(Out_name,Out_name,80,2,2.8); 
  //H_total= H_NN[Npar[0]][Npar[0]];
  for(int i1=0;i1<N_size2;i1++)
  {
    for(int i2=i1;i2<N_size2;i2++)
    {
      //if(i1==i2&&i1==0) continue;
      //cout<<"i1="<<i1<<" i2=="<<i2<<endl;
      H_total->Add(H_NN[Npar[i1]][Npar[i2]],1);
      Total_int+=interf[Npar[i1]][Npar[i2]];
    }
  }
  //cout<<"Total_int="<<Total_int<<endl;
  
  TFile* f =new TFile("bin_by_bin_mx.root","UPDATE");
  //TFile f("bin_by_bin_mx.root","UPDATE");
  H_total->Write();
  f->Close();
  delete H_total;
  delete f;
  delete datafile1;
  return 1;
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

void Cal_inter_all(TString Dis_name,TString root_file,int N_Ac,int N_size2,int Npar[],int style,int color,bool leg_s,TString name_leg,int Nleg)
{
  TFile  *datafile1 = new TFile(root_file);
  const int N_par_wave=N_Ac;
  //read the interference value between any of two partial wave--------------------
  TString name_tmp1;
  char name_tmp[500];
  char* hisname[N_par_wave][N_par_wave];
  float interf[N_par_wave][N_par_wave],interf_sum[N_par_wave][N_par_wave];
  TH1F* H_NN[N_par_wave][N_par_wave];
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
      name_tmp1 = name_tmp;
      name_tmp1 = Dis_name + name_tmp1;
      hisname[i][j]=name_tmp1;
      H_NN[i][j] = (TH1F*)datafile1->Get(hisname[i][j]);
      interf[i][j]=H_NN[i][j]->Integral();
      //std::cout<<"The interference between wave"<<i<<" and wave"<<j<<" is "<<interf[i][j]<<std::endl;
    }
  }

  //TH1F* H_total; 
  //H_total= H_NN[Npar[0]][Npar[0]];
  TH1F* H_total=new TH1F("H_total","H_total",80,2,2.8);
  for(int i1=0;i1<N_size2;i1++)
  {
    for(int i2=i1;i2<N_size2;i2++)
    {
      //if(i1==i2&&i1==0) continue;
      //cout<<"i1="<<i1<<" i2=="<<i2<<endl;
      H_total->Add(H_NN[Npar[i1]][Npar[i2]],1);
    }
  }

  cout<<H_total->Integral()<<endl;
  const int Num=16;
  plotgraph(H_total,Num,style,color,name_leg,Nleg);
  delete datafile1;
  }
void plotgraph(TH1F* H1,const int Num,int MarkerStyle,int MarkerColor,TString name_leg,int Nleg)
{
  int nbins = H1->GetNbinsX();
  //double width = H1->GetBinWidth(0);
  double width = H1->GetBinContent(97);
  int n=0;
  double fit_mx[Num];
  double fit_dat[Num];
  //int setp = 
  //cout<<"width="<<width<<endl;
  double sum_tem=0;
  for(int i=0;i<Num;i++)
  {
    double Nsum = H1->Integral(1+6*i,6+6*i);
    fit_mx[i] = 2.0+0.05*i+0.025;
    fit_dat[i] = Nsum/10.0;
    sum_tem+=fit_dat[i];
    n++;
  }
   cout<<"sum="<<sum_tem<<endl;
   TGraph *gr0 = new TGraph (n, fit_mx, fit_dat); 
   gr0->SetMarkerStyle(MarkerStyle);
   gr0->SetMarkerColor(MarkerColor);
   if(Nleg == 1) gr0->Draw("APL");
   if(Nleg != 1) gr0->Draw("PL");
   
  gr0->GetYaxis()->SetRangeUser(0,3000);
  gr0->GetYaxis()->SetTitle("Events/(0.05GeV/c^{2})");
  gr0->GetXaxis()->SetTitle("M(#eta#pi^{0}#pi^{0})");
   
  double y1=0.928-0.04*Nleg;
  double y2=0.968-0.04*Nleg;
  TLegend *leg = new TLegend(.783,y1,.948,y2,NULL,"brNDC");
  leg->SetTextSize(0.04237288);
  leg->SetTextFont(42);
  leg->SetLineColor(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetShadowColor(0);
  TString name_leg_tem = name_leg + " input";
  leg->AddEntry(gr0,name_leg_tem,"p");
  leg->Draw();
}
