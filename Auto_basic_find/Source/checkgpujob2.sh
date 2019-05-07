#!/bin/bash

if [ "$#" -ne 2 ];then
  echo sorry! $0 jobname
  exit -1
fi

No1=1
No2=${2:-360}
jobname=$1

while (($No1<=$No2))
  do
   line=`qstat gpu2q@pbssrv02 | grep $USER | grep $jobname | wc -l`

  if [ "$line"x = "0"x ];then
    break
  fi

  sleep 1m
  let No1+=1
done
