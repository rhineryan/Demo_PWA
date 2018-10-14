#include <iostream>
#include <iomanip>
#define ARR_LEN(array, length){ length =  sizeof(array) / sizeof(array[0]); }

void Inter_Integral(){
   int number=3000; 
//**********Read waves adding in the basic solution**********************************************
   TString wave_name ="wave.inp";
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
     int k=0;
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
            Want_waveid[i][j1]=N_fa;
            N_fa++;
            j1++;
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
            Want_waveid[i][j1]=N_fa;
            N_fa++;
            j1++;
          }
          if(X_jpc=="1pp"||X_jpc=="2pp"||X_jpc=="2mp")
          {
            Want_waveid[i][j1]=N_fa;
            N_fa++;
            j1++;
            Want_waveid[i][j1]=N_fa;
            N_fa++;
            j1++;
          }
          if(X_jpc=="2pp"||X_jpc=="2mp")
          {
            Want_waveid[i][j1]=N_fa;
            N_fa++;
            j1++;
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
            N_fa++;
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
            N_fa++;
          }
          if(X_jpc=="1pp"||X_jpc=="2pp"||X_jpc=="2mp")
          {
            N_fa++;
            N_fa++;
          }
          if(X_jpc=="2pp"||X_jpc=="2mp")
          {
            N_fa++;
            N_fa++;
          }
        }
      }
    }
    N_Ac=N_fa;
    Want_waveid[i][99]=j1;
   }
     /*
     for(int i=0;i<len;i++)
     {
       for(int j=0;j<Want_waveid[i][20];j++)
       {
         cout<<"Want_waveid[i][j]="<<Want_waveid[i][j]<<endl;
       }
       cout<<endl;
     }
     exit(0);
     */
   cout<<"N_input="<<N_input<<" N_Ac="<<N_Ac<<" Want_nwave="<<len<<endl;
   const int Want_nwave=len; //number of wave that we want
   const int Nactive_wave=N_Ac; //total partial wave
//*****************Read MCIntegral file***************************
   char name1[500];
   sprintf(name1,"./Amplitude_MC_Integral");
   ifstream f1(name1);
   //cout<<"McIntegral"<<endl;
   double McIntegral_real[Nactive_wave][Nactive_wave];
   double McIntegral_imag[Nactive_wave][Nactive_wave];
   int Nm=0;
   for(int i=0;i<Nactive_wave;i++)
    for(int j=i;j<Nactive_wave;j++)
    {
      f1>>McIntegral_real[i][j]>>McIntegral_imag[i][j]; 
      //cout<<McIntegral_real[i][j]<<"      "<<McIntegral_imag[i][j]<<endl; 
      Nm++;
    }
   //cout<<"Nm="<<Nm<<endl;

//*****************Read Npar sets of parameters*****************************
   for(int i=0;i<number;i++)
   {
     double sum=0;
     double par_real[Nactive_wave];
     double par_imag[Nactive_wave];
     double weights[Nactive_wave][Nactive_wave];  //Nactive_wave sets of mag and phs 
     double weights_inter[Want_nwave][Want_nwave];
     char name2[500];
     sprintf(name2,"../randpara/rand_%i.txt",i+1);
     ifstream f2(name2);
 
    // char Xsectionoutputfilename[255];
    // sprintf(Xsectionoutputfilename,"partial_weights_par_%i.out",i+1);
    // ofstream Xsectionoutputfile(Xsectionoutputfilename);
    // Xsectionoutputfile << setiosflags(ios::fixed)<<setprecision(10);

     char wfilename[255];
     sprintf(wfilename,"../out/fraction_%i.out",i+1);
     ofstream woutputfile(wfilename);
     woutputfile << setiosflags(ios::fixed)<<setprecision(10);


     for(int np=0;np<Nactive_wave;np++)
     {
       f2>>par_real[np]>>par_imag[np];
       //cout<<par_real[np]<<"   "<<par_imag[np]<<endl;
     }    

     for(int j=0;j<Nactive_wave;j++)
       for(int k=j;k<Nactive_wave;k++)
       {
         double wt; 
         if(k==j)
         {
           wt= McIntegral_real[j][k]*(par_real[j]*par_real[j]+par_imag[j]*par_imag[j]);
           //Xsectionoutputfile<<j<<"  "<<k<<"    "<<wt<<endl;  
           sum+=wt; 
         }
         else
         {
           double p_real = par_real[j]*par_real[k];
           double p_imag = par_imag[j]*par_imag[k];
           wt= 2.0*( p_real*McIntegral_real[j][k] + p_imag*McIntegral_real[j][k]
           + par_real[j]*par_imag[k]*McIntegral_imag[j][k] - par_imag[j]*par_real[k]*McIntegral_imag[j][k]); 
           //Xsectionoutputfile<<j<<"  "<<k<<"    "<<wt<<endl;
           sum+=wt; 
         }
         weights[j][k]= wt;
         //cout<<j<<"  "<<k<<"    "<<wt<<endl; 
       }


//********************************************************************************************

       for(int j=0;j<Want_nwave;j++)
       {
     
          for(int k=j;k<Want_nwave;k++)
          {
              weights_inter[j][k]=0;
              for(int wi=0;wi<Want_waveid[j][99];wi++)
     
                  for(int wj=0;wj<Want_waveid[k][99];wj++)
                  {
                   int left = Want_waveid[j][wi];
                   int right = Want_waveid[k][wj];
                   if(left>right) continue;
                   //cout<<j<<"  "<<k<<"weights_inter"<<weights[left][right]<<endl;
                   weights_inter[j][k] + = weights[left][right];
                 }
            }
     
        }
     
//********************************************************************************************
        //cout<<"TotalXSection= "<<sum<<endl;
       if(i%200==0) cout<<i<<"th"<<"processed..."<<endl;
     
        //cout<<"**********Print out cross section of each resonance Wanted*****************"<<endl;
        for(int j=0;j<len;j++)
        {
          for(int k=j;k<len;k++)
          {
           //woutputfile<<setiosflags(ios::fixed)<<setprecision(8)<<weights_inter[j][k]<<endl; //for total dcs
           woutputfile<<setiosflags(ios::fixed)<<setprecision(8)<<weights_inter[j][k]/sum<<endl; //for fraction
          }
        }
        /*
        cout<<"**********Print out cross section of each resonance Activated*****************"<<endl;
        for(int j=0;j<Nactive_wave;j++)
        {
          for(int k=j;k<Nactive_wave;k++)
          {
           woutputfile<<setiosflags(ios::fixed)<<setprecision(4)<<weights[j][k]/sum<<endl;
          }
        }
        */
   }
exit(0);
}
