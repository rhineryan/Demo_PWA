#!/bin/bash

if [ -z $1 ];then
  echo Sorry! $0   tdir  odir
fi
spath=`pwd`
odir=${2:-$spath}

tdir=$1
mkdir $tdir

if [ $? != 0 ];then
  echo $tdir exist! Something wrong?
  exit -1
fi

cd $odir
odir=`pwd`
cd -

ln -s /besfs/groups/gpugroup/xulei/GPUPWA2.1new/gpupwa_mtj/GPUPWA/_common/binfiles   $tdir/binfiles
ln -s $odir/GEtaPi0Pi0   $tdir/
#cp   $odir/input   $tdir/  -r
cp   ./input   $tdir/  -r
