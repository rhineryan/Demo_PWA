      cd $path
      mkdir C_${checkruns}_$check_n  -p
      cd C_${checkruns}_$check_n

      ln -s  $gpuprogram    ./
      ln -s  $binfilesdir   ./
      mkdir  input
      cp $inputfiles  input/
      cp $resfile   input/

      for i in "${!wave_ini[@]}"; do
	if [ $i -eq $check_n ];then
	  continue
	fi
	echo ${wave_ini[$i]} >> input/wave.inp
      done

      ~/mypwa/ConvConfig_xxa2xl.pl  input/wave.inp  input/fileconfig.txt
      ~/mypwa/GenParIni.py  input/fileconfig.txt  input/para.inp
      ~/mypwa/GenJob.sh  ${checkjobprefix}_${checkruns}_${check_n}.sh

      echo cd `pwd`";" gpu2q ${checkjobprefix}_${checkruns}_${check_n}.sh"; cd -" >>$path/checkrunlist
      echo ${check_n}  >>$path/checkrunnumberlist
      cd ..
      let check_n+=1
    done
    ######### Generate all check job end

    ############## sub jobs
    cd $path
    checkfilenum=`cat checkrunlist|wc -l`
    checkrun=`expr $checkfilenum / 10`
    if expr $checkfilenum % 10 != 0 >/dev/null;then
      let checkrun+=1
    fi

    for n in `seq  1 $checkrun`
    do
      read -r line < fail.inp
      if [ "$line"x = "stop"x ];then
	echo "Terminated !!!!" >>$path/Bin_Bin_Fit.log
	exit -1
      fi

      begin=`echo "10 * ($n - 1) + 1"|bc`
      let end=10*n
      sed -n "$begin,${end} p"  checkrunlist|sh
      ~/mypwa/checkgpujob.sh   ${checkjobprefix}_${checkruns}_
      cd $path
      #########  continue check signif
      for m in `sed -n "$begin,${end} p" checkrunnumberlist`
      do
	like_1=`cat C_${checkruns}_$m/multifitresults_GammaEtaPi0Pi0Analysis_0.txt |awk '{print $6}'|sed 's#:##'|sort -nr|tail -n1`
	if [ "$like_1" = "" ];then
	  echo   "Warnning!!! likelyhood of drop ${wave_ini[$m]} is empty! somthing is wrong! contunue!!!" >>$path/Bin_Bin_Fit.log
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
