#!/bin/bash

if [ ! -e input ];then
  echo  "There is no binfiles and input"
  exit -1
fi

ls -1  $PWD/* -d|perl -nle  'print if !-x '|grep -v "\.cpp" |grep -v Makefile |grep -v tags |xargs rm -f
