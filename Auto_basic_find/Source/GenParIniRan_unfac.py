#!/usr/bin/env python
import os
import sys
from sys import argv
from math import fabs
import re
import random

if len(argv)!=3:
  print "usuage:",argv[0],"fileconfig.txt  para.inp"
  sys.exit(-1)

def Gen(file1,file2):
  f1=open(argv[1],'r')
  f1List=f1.readlines()
  f1.close()
  f2=open(file2,'w')

  low=-500
  up=500

  fix=1
  f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%("bg_mag",0,-1,-500,500))
  f2.write("\n")

  for line in f1List:
    line=line.rstrip()

    if line.find('yes')!=-1:
      arr=line.split()

      if fix==0:
	rand_mag = random.random() * 100.0
	rand_magerr=max(0.1*rand_mag,1)
	rand_phase = (random.random()*2.0-1)*6.28

	f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'>_'+'1'+'_mag',rand_mag, rand_magerr,low,up))
	f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'>_'+'1'+'_phase',rand_phase, 1,-6.3,6.3))

      if fix==1:
	f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'>_'+'1'+'_mag',25,-1,low,up))
	f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'>_'+'1'+'_phase',0,-1,-6.3,6.3))
	fix=0

      for num in range(2,5):
	rand_mag = random.random() * 100.0
	rand_magerr=max(0.1*rand_mag,1)
	rand_phase = (random.random()*2.0-1)*6.28
	f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'>_'+str(num)+'_mag',rand_mag,rand_magerr,low,up))
	f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'>_'+str(num)+'_phase',rand_phase,1,-6.3,6.3))
      f2.write("\n");

  f2.close()

Gen(argv[1],argv[2])
