#!/bin/bash

if test -z "$1";then
  echo $0  dirname
  exit -1
fi

dirname=$1

if [ -e $dirname ];then
  echo $dirname exist!
  exit
fi

mkdir $dirname
cd $dirname
mkdir input
cd ..
cp input/fileconfig.txt  $dirname/input
cp input/files.txt       $dirname/input
cp input/para.inp        $dirname/input
cp input/res.inp         $dirname/input

cp multifitresults_GammaEtaPi0Pi0Analysis_*.txt  $dirname

~/mypwa/zGetParaList.py  5  $dirname
~/mypwa/clean.sh
