#!/usr/bin/env python
import os
import sys
from sys import argv
from math import fabs
import re
import random

#if len(argv)!=4:
#  print "usuage:",argv[0],"oriflie  targetfileprefix  num"
#  sys.exit(-1)
if len(argv)!=3:
  print "usuage:",argv[0],"oriflie  targetfileprefix"
  sys.exit(-1)

f1=open(argv[1],'r')
f1List=f1.readlines()
f1.close()

low=-500
up=500

f2=open(argv[2],'w')
fix=1
f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n\n"%("bg_mag",0,-1,-500,500))

for line in f1List:
  line=line.rstrip()
  if line.find('yes')!=-1:
    arr=line.split()

    if arr[1].find('f')!=-1:
      #if fix==0:
      #  #rand_mag = random.random() * 100.0
      #  #rand_magerr=max(0.1*rand_mag,1)
      #  #rand_phase = (random.random()*2.0-1)*6.28

      name_prefix=arr[0]
      f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%(name_prefix+'_mag',10, 1,low,up))
      f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%(name_prefix+'_phase',0, 0.7,-6.3,6.3))

      #if fix==1:
      #f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%(name_prefix+'_mag',10,-1,low,up))
      #f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%(name_prefix+'_phase',0,-1,-6.3,6.3))
      #fix=0

    else:
      #if fix==0:
      if arr[0].find('K2_1430')==-1:
        #rand_mag = random.random() * 100.0
        #rand_magerr=max(0.1*rand_mag,1)
        #rand_phase = (random.random()*2.0-1)*6.28

	name_prefix=arr[0]+'+'
        f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%(name_prefix+'_mag',10, 1,low,up))
        f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%(name_prefix+'_phase',0, 0.7,-6.3,6.3))
	name_prefix=arr[0]+'-'
        f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%(name_prefix+'_mag',10, 1,low,up))
        f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%(name_prefix+'_phase',0, 0.7,-6.3,6.3))

      else:
	name_prefix=arr[0]+'+'
        f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%(name_prefix+'_mag',10,-1,low,up))
        f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%(name_prefix+'_phase',0,-1,-6.3,6.3))
	name_prefix=arr[0]+'-'
        f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%(name_prefix+'_mag',10,-1,low,up))
        f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%(name_prefix+'_phase',0,-1,-6.3,6.3))
        #fix=0

f2.close()

