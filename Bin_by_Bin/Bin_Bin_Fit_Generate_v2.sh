#!/bin/bash
No1=0
No2=15
event=(
    2528 2192 2036 1992 1924 2188 2392 2356 1916 1752 1740 1608 1568 1396 1312 1076
    )
while(($No1<=$No2))
  do
  rm -rf $No1
  cp -rf bin_template $No1 
  cp -rf /besfs/groups/psip/psipgroup/user/xiongxa/GamEtaPi0Pi0/Alg_gg_xl/GPUPWA/IO_check/Sampling/Sample/0mp/BinbyBin_sample/data$No1.root $No1/data/data.root
  cp -rf /besfs/groups/psip/psipgroup/user/xiongxa/GamEtaPi0Pi0/Alg_gg_xl/GPUPWA/IO_check/Sampling/Sample/0mp/BinbyBin_sample/phsp$No1.root $No1/data/phsp.root
  cd $No1
  sed -i 's/bin_template/'$No1'/g' Myauto_unfac1.sh
  awk '{flag = 1}
  {sub(/PWDdir/,"'$PWD'")}
  {if(flag == 1) {print $0} else {next} }' \
    ./Myauto_unfac1.sh >Myauto_unfac1.sh1
   mv -f Myauto_unfac1.sh1 Myauto_unfac1.sh 
  cd data
  sed -i 's/bin_template/'$No1'/g' files.txt
  awk '{flag = 1}
  {sub(/PWDdir/,"'$PWD'")}
  {sub(/EVENT/,"'${event[$No1]}'")}
  {if(flag == 1) {print $0} else {next} }' \
    ./files.txt > files1.txt
  mv -f files1.txt files.txt
  cd ../../
  echo 'done with '$No1''
  let No1+=1
  done
