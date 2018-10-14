#!/bin/bash/
N01=0
N02=0
while(( $N01 <= $N02 ))
  do
  rm -rf $N01
  cp -rf template $N01
  cd $N01/GenRandpara
#copy the files 
  cp -rf /besfs/groups/psip/psipgroup/user/xiongxa/GamEtaPi0Pi0/Alg_gg_xl/GPUPWA/gpupwa2.1_1/Bin_Bin_data/$N01/minimum_* .
  cp -rf /besfs/groups/psip/psipgroup/user/xiongxa/GamEtaPi0Pi0/Alg_gg_xl/GPUPWA/gpupwa2.1_1/Bin_Bin_data/$N01/*Amplitude_MC_Integral* Amplitude_MC_Integral
  cp -rf /besfs/groups/psip/psipgroup/user/xiongxa/GamEtaPi0Pi0/Alg_gg_xl/GPUPWA/gpupwa2.1_1/Bin_Bin_data/$N01/files/psfile/wave.inp .
  echo "Files needs are done with $N01 !!!!!!processing!!!!!"
#processe the files to fit to the requiements

#para.out
  para_line=`grep -n 'ext.' minimum_basic.txt | cut -d : -f 1`
#  echo "para_line= $para_line"
  cat minimum_basic.txt | tail -n +$para_line > para_tem.out 
  cat para_tem.out | tail -n +3 > para.out 
  sed -i 's/||/ /g' para.out
  sed -e '/^$/d' para.out > para_tem.out
  cp -rf para_tem.out para.out
  sed -i 's/[ ][ ]*/ /g' para.out #combin the whitespace
  sed -i 's/fixed.*/& 0/g' para.out #add a error for fixed parameters 0
  rm -rf para_tem.out

#modify GenRandPara.cxx
  npara=`cat para.out | wc -l`
  sed -i 's/npar=/npar='$npara'/g' GenRandPara.cxx 

#Minuit_result.out
  cat minimum_basic.txt | tail -n +4 | head -n 2 > Minuit_result.out 
  sed -i 's/minimum function Value/fmin/g' Minuit_result.out
  sed -i 's/minimum edm/edm/g' Minuit_result.out
  echo "covq: 1" >> Minuit_result.out
  echo "Mstate: 1" >> Minuit_result.out

#CovarianceCoef_tem.out
  cov_line=`grep -n 'MnUserCovariance Parameter correlations' minimum_covariance.txt | cut -d : -f 1`
#  echo "$cov_line"
  cat minimum_covariance.txt | tail -n +$cov_line > CovarianceCoef_tem.out
  cat CovarianceCoef_tem.out | tail -n +3 > CovarianceCoef.out
  rm -r CovarianceCoef_tem.out

#GlobalCorre.out
  cat minimum_globalcc.txt | tail -n +4 > GlobalCorre.out

#Fitfraction.cxx
#  nWave=`cat wave.inp| wc -l`
#  sed -i 's/Nwave=/Nwave='$nWave'/g' Fitfraction.cxx #the wave number you add in wave.inp
#  Num=$((nWave*(nWave+1)/2))
#  sed -i 's/Num=/Num='$Num'/g' Fitfraction.cxx  #the number of fit results you need see

#Amplitude_MC_Integral
  nActi_wave=`grep _mag para.out | wc -l` #the wave number actived in the PWA program, it is related to the wave you add and the the indepent wave numbers of the wave.
  Num_nActi=$((nActi_wave*(nActi_wave+1)/2))
  cat Amplitude_MC_Integral | tail -n +5 | head -n $Num_nActi > Amplitude_MC_Integral_tem
  cp -rf Amplitude_MC_Integral_tem Amplitude_MC_Integral
  rm -rf Amplitude_MC_Integral_tem

#run file
  root GenRandPara.cxx
  root Inter_Integral.cxx
  root Fitfraction.cxx

  cd ../../
  let N01=$N01+1
done
