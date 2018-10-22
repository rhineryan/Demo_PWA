#!/bin/bash

wave_tot=(
Xphsp_0mp_a0phsp Xphsp_0mp_a0980 Xphsp_0mp_a2phsp Xphsp_0mp_a21320 Xphsp_0mp_a21700
Xphsp_0mp_f0phsp Xphsp_0mp_f0500 Xphsp_0mp_f0980 Xphsp_0mp_f0phsp Xphsp_0mp_f01370
Xphsp_0mp_f01500 Xphsp_0mp_f01710 Xphsp_0mp_f2phsp Xphsp_0mp_f21270 Xphsp_0mp_f21525

X2370_0mp_a0phsp X2370_0mp_a0980 X2370_0mp_a2phsp X2370_0mp_a21320 X2370_0mp_a21700
X2370_0mp_f0phsp X2370_0mp_f0500 X2370_0mp_f0980 X2370_0mp_f0phsp X2370_0mp_f01370
X2370_0mp_f01500 X2370_0mp_f01710 X2370_0mp_f2phsp X2370_0mp_f21270 X2370_0mp_f21525

X2120_0mp_a0980 X2120_0mp_a21320 X2120_0mp_a21700 X2120_0mp_a0phsp X2120_0mp_a2phsp 
X2120_0mp_f0phsp X2120_0mp_f0500 X2120_0mp_f0980 X2120_0mp_f0phsp X2120_0mp_f01370
X2120_0mp_f01500 X2120_0mp_f01710 X2120_0mp_f2phsp X2120_0mp_f21270 X2120_0mp_f21525

X1835_0mp_a0phsp X1835_0mp_a0980 X1835_0mp_a2phsp X1835_0mp_a21320 X1835_0mp_a21700
X1835_0mp_f0phsp X1835_0mp_f0500 X1835_0mp_f0980 X1835_0mp_f0phsp X1835_0mp_f01370
X1835_0mp_f01500 X1835_0mp_f01710 X1835_0mp_f2phsp X1835_0mp_f21270 X1835_0mp_f21525

Xphsp_1pp_a0phsp Xphsp_1pp_a0980 Xphsp_1pp_a2phsp Xphsp_1pp_a21320 Xphsp_1pp_a21700
Xphsp_1pp_f0phsp Xphsp_1pp_f0500 Xphsp_1pp_f0980 Xphsp_1pp_f0phsp Xphsp_1pp_f01370
Xphsp_1pp_f01500 Xphsp_1pp_f01710 Xphsp_1pp_f2phsp Xphsp_1pp_f21270 Xphsp_1pp_f21525

Xphsp_2mp_a0phsp Xphsp_2mp_a0980 Xphsp_2mp_a2phsp Xphsp_2mp_a21320 Xphsp_2mp_a21700
Xphsp_2mp_f0phsp Xphsp_2mp_f0500 Xphsp_2mp_f0980 Xphsp_2mp_f0phsp Xphsp_2mp_f01370
Xphsp_2mp_f01500 Xphsp_2mp_f01710 Xphsp_2mp_f2phsp Xphsp_2mp_f21270 Xphsp_2mp_f21525

Xphsp_2pp_a2phsp Xphsp_2pp_a21320 Xphsp_2pp_a21700 Xphsp_2pp_f2phsp Xphsp_2pp_f21270
Xphsp_2pp_f21525

)

dof_tot=(
2 2 2 2 2
2 2 2 2 2
2 2 2 2 2

2 2 2 2 2
2 2 2 2 2
2 2 2 2 2

2 2 2 2 2
2 2 2 2 2
2 2 2 2 2

2 2 2 2 2
2 2 2 2 2
2 2 2 2 2

4 4 8 8 8
4 4 4 4 4
4 4 8 8 8

6 6 6 6 6
6 6 6 6 6
6 6 6 6 6

6 6 6 6 6
6
)

wave_ini=(
Xphsp_0mp_a0980 Xphsp_0mp_a21320 Xphsp_0mp_f21270 Xphsp_0mp_f01370 X1835_0mp_f0500
X1835_0mp_f0980 X1835_0mp_f21270 X1835_0mp_a0980 X1835_0mp_a21320 X1835_0mp_a21700
Xphsp_0mp_a0phsp Xphsp_0mp_f0980 Xphsp_0mp_f0500 Xphsp_0mp_f01500 Xphsp_0mp_f01710
Xphsp_0mp_f2phsp X2370_0mp_a2phsp X2370_0mp_f01710 X2370_0mp_f2phsp X2370_0mp_f21270
X1835_0mp_a0phsp X1835_0mp_f2phsp X2370_0mp_f0980 X1835_0mp_f01370 Xphsp_1pp_a2phsp
X2370_0mp_a0980 X1835_0mp_f01710 Xphsp_0mp_a2phsp Xphsp_1pp_a0980
)

dof_ini=(
2 2 2 2 2
2 2 2 2 2
2 2 2 2 2
2 2 2 2 2
2 2 2 2 8
2 2 2 4
)

like_0="-7507.6244"

mcjobprefix='E' ### just for convenience to change
fitjobprefix='G'
checkjobprefix='Z'

#part of adding one wave into the ini array 
gpuprogram="/besfs/groups/gpugroup/xulei/GPUPWA2.1new/gpupwa_mtj/GEPP_unfact/GEtaPi0Pi0"
gpuMCInteprogram="/besfs/groups/gpugroup/xulei/GPUPWA2.1new/gpupwa_mtj/GEPP_unfact_mcinte/GEtaPi0Pi0"
gpuFitprogram="/besfs/groups/gpugroup/xulei/GPUPWA2.1new/gpupwa_mtj/GEPP_unfact_onlyFit/GEtaPi0Pi0"
binfilesdir="/besfs/groups/gpugroup/xulei/GPUPWA2.1new/gpupwa_mtj/GPUPWA/_common/binfiles"

resfile="/besfs/groups/gpugroup/xulei/GPUPWA2.1new/gpupwa_mtj/GEPP_unfact_mcinte/input/res.inp"
inputfiles="/besfs/groups/gpugroup/xulei/GPUPWA2.1new/gpupwa_mtj/GEPP_unfact_mcinte/input/files.txt"
inputfiles2="/besfs/groups/gpugroup/xulei/GPUPWA2.1new/gpupwa_mtj/GEPP_unfact_mcinte/input/files2.txt"

path=$PWD
fitjobnums=10  #########
checkjobnums=10 ########
N5sigma=1

echo "lets begin!!"  `date` > Bin_Bin_Fit.log
echo "begin" `date` > sucess.out

runs=0   #### count the adds
checkruns=0 ###### count the checks

add_n=0
while [ "$add_n" -lt "${#wave_tot[@]}" ]
do
  read -r line < fail.inp
  if [ "$line"x = "stop"x ];then
    echo "!!!!!!!!!!!!!!!!!!!stop by $USER!!!!!!!!!!!!!!!!!!!!" >>Bin_Bin_Fit.log
    break
  fi

  add_stat=1
  for j in "${!wave_ini[@]}"; do 
    if [ "${wave_ini[$j]}"x = "${wave_tot[$add_n]}"x ];then
      add_stat=0
    fi 
  done 

  if [ $add_stat -eq 0 ];then
    let add_n++
    continue
  fi

  echo "Before adding, the likeli value is $like_0 and the solution is ${wave_ini[@]}" >> Bin_Bin_Fit.log
  wave_ini[${#wave_ini[@]}]="${wave_tot[$add_n]}"
  dof_ini[${#dof_ini[@]}]="${dof_tot[$add_n]}" 

  let runs++
  mkdir -p  add_${wave_tot[$add_n]}_$runs
  cd  add_${wave_tot[$add_n]}_$runs 

  ln -s $gpuMCInteprogram  ./MCInte_GEtaPi0Pi0
  ln -s  $binfilesdir   ./
  mkdir  input
  cp $inputfiles  input/files.txt
  cp $resfile   input/

  for i in "${!wave_ini[@]}"; do
    echo ${wave_ini[$i]} >> input/wave.inp
  done

  ##################################### MC Integral
  ~xulei/mypwa/ConvConfig_xxa2xl.pl  input/wave.inp  input/fileconfig.txt
  ~xulei/mypwa/GenParIniRan_unfac.py input/fileconfig.txt  input/para.inp
  ~xulei/mypwa/GenJob2par.sh  ${mcjobprefix}_${runs}_.sh  MCInte_GEtaPi0Pi0
  gpu2q   ${mcjobprefix}_${runs}_.sh

  checkmctimes=0
  while true
  do
    jobflag=`grep 'End===End'  MCInte_GEtaPi0Pi0.log`
    if [ "$jobflag" != "" ];then
      break
    fi
    sleep 30
    let checkmctimes+=1
    if [ "$checkmctimes" -gt  240 ];then
      echo "Something is wrong! MCInte Terminaled " >>$path/Bin_Bin_Fit.log
      exit -1
    fi

    read -r line < $path/fail.inp
    if [ "$line"x = "stop"x ];then
      echo "!!!!!!!!!!!!!!!!!!!stop by $USER!!!!!!!!!!!!!!!!!!!!" `date` >>Bin_Bin_Fit.log
      exit -1
    fi
  done

  for k in `seq 1 $fitjobnums`
  do
    mkdir Fit_$k  -p
    cd Fit_$k
    ln -s $gpuFitprogram  ./Fit_GEtaPi0Pi0
    ln -s  $binfilesdir   ./
    mkdir  input
    cd input

    cp  -s  ../../input/files.txt   .
    cp -s  ../../input/res.inp   .
    cp -s  ../../input/fileconfig.txt  .
    ~xulei/mypwa/GenParIniRan_unfac.py  fileconfig.txt  para.inp
    cd ..
    cp -s  ../GammaEtaPi0Pi0Analysis_Amplitude_MC_Integral    .
    ~xulei/mypwa/GenJob2par.sh  ${fitjobprefix}_${runs}_$k.sh  Fit_GEtaPi0Pi0
    gpu2q ${fitjobprefix}_${runs}_$k.sh
    cd ..
  done

  ~xulei/mypwa/checkgpujob.sh   ${fitjobprefix}_${runs}_
  ################################ check significance
  like_add_test=`cat Fit_*/multifitresults_GammaEtaPi0Pi0Analysis_*.txt |awk '{print $6}'|sed 's#:##'|sed '/^$/d'|sort -nr|tail -n1`
  like_add=`cat Fit_*/multifitresults_GammaEtaPi0Pi0Analysis_*.txt |awk '{print $6}'|sed 's#:##'|sed '/^$/d'|sort -n|~xulei/mypwa/check_conv_simple2.pl`
  if [ "$like_add" != "$like_add_test" ];then
    echo "the likelihood is strange, the least $like_add_test is abandoned! use $like_add ">>$path/Bin_Bin_Fit.log
  fi
  if [ "$like_add" = "" ];then
    echo Something is wrong! >>$path/Bin_Bin_Fit.log
    let like_add=0
    break
  fi
  cd  $path
  value3=`echo $like_0 - $like_add|bc`
  sigf=`/workfs/bes/xulei/significance/significance $value3  ${dof_tot[$add_n]}|perl -nle 'print $1 if(/significance= *(\S+)/)'`
  pmflag=`echo $value3|perl -nle 'if($_>=0){print 1}else{print 0}'`
  flag=`echo $sigf|perl -nle 'if($_<5){print 0}else{print 1}'`
  if [ "$pmflag" = 0 ];then
    flag=0
  fi
  echo "trying to add wave ${wave_tot[$add_n]},the new like value of new likelihood is $like_add ,the signif is  $sigf" >> Bin_Bin_Fit.log

  rm  $path/add_${wave_tot[$add_n]}_$runs -fr

  if [ "$flag"x = "0"x ];then
    echo "So the wave ${wave_ini[${#wave_ini[@]}-1]} dont add, try next wave" >> Bin_Bin_Fit.log
    add_tem=${#wave_ini[@]}-1
    wave_ini=(${wave_ini[@]:0:$add_tem} ${wave_ini[@]:$add_tem+1})
    dof_ini=(${dof_ini[@]:0:$add_tem} ${dof_ini[@]:$add_tem+1})

    let add_n++
    continue
  fi

  like_0=$like_add
  echo  >>Bin_Bin_Fit.log
  echo "So the wave ${wave_ini[${#wave_ini[@]}-1]} have added, next part is to check the sig for everyone in ${#wave_ini[@]} waves" >> Bin_Bin_Fit.log


  #########################################part of checking the sig. for every one inside 

  like_1="0"
  check_end=${#wave_ini[@]}
  let check_end-=1

  while true  ###check until all 5sigma
  do  ###### DeadRun1111111 start
    cd $path
    check_run_flag=0  #### denote the change of status 
    let checkruns++
    >checkrunlist
    >checkrunnumberlist

    read -r line < $path/fail.inp
    if [ "$line"x = "stop"x ];then
      echo "!!!!!!!!!!!!!!!!!!!stop by $USER!!!!!!!!!!!!!!!!!!!!" `date` >>Bin_Bin_Fit.log
      break
    fi

    if [ ${#wave_ini[@]} -eq 1 ];then
      break
    fi

    ######### Generate all check job begin
    check_n=1
    while [ $check_n -lt ${check_end} ]
    do
      cd $path
      mkdir C_${checkruns}_$check_n  -p
      cd C_${checkruns}_$check_n

      ln -s  $gpuprogram    ./
      ln -s  $binfilesdir   ./
      mkdir  input
      cp $inputfiles2  input/files.txt
      cp $resfile   input/

      for i in "${!wave_ini[@]}"; do
	if [ $i -eq $check_n ];then
	  continue
	fi
	echo ${wave_ini[$i]} >> input/wave.inp
      done

      ~xulei/mypwa/ConvConfig_xxa2xl.pl  input/wave.inp  input/fileconfig.txt
      ~xulei/mypwa/GenParIniRan_unfac.py input/fileconfig.txt  input/para.inp
      ~xulei/mypwa/GenJob.sh  ${checkjobprefix}_${checkruns}_${check_n}.sh

      echo cd `pwd`";" gpu2q ${checkjobprefix}_${checkruns}_${check_n}.sh"; cd -" >>$path/checkrunlist
      echo ${check_n}  >>$path/checkrunnumberlist
      cd ..
      let check_n+=1
    done
    ######### Generate all check job end

    ############## sub jobs
    cd $path
    checkfilenum=`cat checkrunlist|wc -l`
    checkrun=`expr $checkfilenum / $checkjobnums`
    if expr $checkfilenum % $checkjobnums != 0 >/dev/null;then
      let checkrun+=1
    fi

    for n in `seq  1 $checkrun`
    do
      read -r line < fail.inp
      if [ "$line"x = "stop"x ];then
	echo "Terminated !!!!" >>$path/Bin_Bin_Fit.log
	exit -1
      fi

      begin=`echo "$checkjobnums * ($n - 1) + 1"|bc`
      let end=checkjobnums*n
      sed -n "$begin,${end} p"  checkrunlist|sh
      ~xulei/mypwa/checkgpujob.sh   ${checkjobprefix}_${checkruns}_
      cd $path
      #########  continue check signif
      for m in `sed -n "$begin,${end} p" checkrunnumberlist`
      do
	like_1_test=`cat C_${checkruns}_$m/multifitresults_GammaEtaPi0Pi0Analysis_0.txt |awk '{print $6}'|sed 's#:##'|sed '/^$/d'|sort -nr|tail -n1`
	like_1_1=`cat C_${checkruns}_$m/multifitresults_GammaEtaPi0Pi0Analysis_0.txt |awk '{print $6}'|sed 's#:##'|sed '/^$/d'|sort -n|~xulei/mypwa/check_conv_simple2.pl`
	if [ "$like_1" != "$like_1_test" ];then
	  echo "In check,the likelihood is strange, the least $like_1_test is abandoned! use $like_1 ">>$path/Bin_Bin_Fit.log
	fi

	if [ "$like_1" = "" ];then
	  echo   "Warnning!!! likelyhood of drop ${wave_ini[$m]} is empty! somthing is wrong! contunue!!!" >>$path/Bin_Bin_Fit.log
	  like_1=0
	fi
	value3=`echo $like_1 - $like_0|bc`
	sigf=`/workfs/bes/xulei/significance/significance $value3  ${dof_ini[$m]}|perl -nle 'print $1 if(/significance= *(\S+)/)'`
	pmflag=`echo $value3|perl -nle 'if($_>=0){print 1}else{print 0}'`
	flag=`echo $sigf|perl -nle 'if($_<5){print 0}else{print 1}'`
	if [ "$pmflag" = 0 ];then
	  flag=0
	fi
	if [ "$flag"x = "0"x ];then
	  echo "wave ${wave_ini[$m]} have checked with ${#wave_ini[@]} waves" >> Bin_Bin_Fit.log
	  echo "Before drop the wave ${wave_ini[$m]},the like value is $like_0" >> Bin_Bin_Fit.log
	  echo "After drop the wave ${wave_ini[$m]},the like value is $like_1" >> Bin_Bin_Fit.log
	  echo "So the wave ${wave_ini[$m]} will be dropped, the significance is $sigf" >> Bin_Bin_Fit.log

	  wave_ini=(${wave_ini[@]:0:$m} ${wave_ini[@]:$m+1})
	  dof_ini=(${dof_ini[@]:0:$m} ${dof_ini[@]:$m+1})
	  like_0=$like_1 #change the base solution value 
	  echo "After the wave is droped and the base value should change to $like_0" >> Bin_Bin_Fit.log
	  check_run_flag=1
	  let check_end=${#wave_ini[@]}
	  break
	fi

	jobflag=`grep 'End===End'  C_${checkruns}_$m/GEtaPi0Pi0.log`
	if [ "$jobflag" = "" ];then
	  echo  check ${wave_ini[$m]}  may not finish well >>$path/Bin_Bin_Fit.log
	fi
	echo "wave ${wave_ini[$m]} have checked with ${#wave_ini[@]} waves" >> Bin_Bin_Fit.log
	echo "Before drop the wave ${wave_ini[$m]},the like value is $like_0" >> Bin_Bin_Fit.log
	echo "After drop the wave ${wave_ini[$m]},the like value is $like_1, the significance is $sigf, wave remain " >> Bin_Bin_Fit.log

      done
      ###### check signif end

      ####### jump out one check run
      if [ "$check_run_flag" = 1 ];then
	break
      fi
    done

    cd $path
    rm  -fr  C_${checkruns}_* 

    ######### jump out of check loop
    if [ "$check_run_flag" = 0 ];then
      echo "Now left ${#wave_ini[@]} waves(> 5sigma)" >> Bin_Bin_Fit.log
      echo  >> Bin_Bin_Fit.log
      break
    fi
  done  ######DeadRun1111111 end

  echo "Now $N5sigma added are sig. > 5sigma " >> sucess.out
  echo "${#wave_ini[@]}states, likelihood value is $like_0" >> sucess.out
  for i in "${!wave_ini[@]}"; do
    echo ${wave_ini[$i]}   ${dof_ini[$i]}>> sucess.out
  done
  echo  >>sucess.out
  let N5sigma++

  let add_n=0 #restart the adding part from the first particle
done

echo "======= End" >>Bin_Bin_Fit.log
