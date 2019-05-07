#!/usr/bin/env python
import os
import sys
from sys import argv
from math import fabs
import re
import random

if len(argv)!=4:
  print "usuage:",argv[0],"oriflie  targetfileprefix  num"
  sys.exit(-1)

f1=open(argv[1],'r')
f1List=f1.readlines()
f1.close()
num=int(argv[3])
low=-500
up=500

for index in range(num):

  f2=open('%s_%d'%(argv[2],index+1),'w')
  fix=1
  f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%("phasespace",0,-1,-500,500))

  for line in f1List:
    line=line.rstrip()
    if line.find('yes')!=-1:
      arr=line.split()

      if arr[3].find('f')!=-1:
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

      else:
	if fix==0:
	  rand_mag = random.random() * 100.0
	  rand_magerr=max(0.1*rand_mag,1)
	  rand_phase = (random.random()*2.0-1)*6.28

	  f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'_b>_'+'1'+'_mag',rand_mag, rand_magerr,low,up))
	  f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'_b>_'+'1'+'_phase',rand_phase, 1,-6.3,6.3))
	  f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'_c>_'+'1'+'_mag',rand_mag, rand_magerr,low,up))
	  f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'_c>_'+'1'+'_phase',rand_phase, 1,-6.3,6.3))

	if fix==1:
	  f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'_b>_'+'1'+'_mag',25,-1,low,up))
	  f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'_b>_'+'1'+'_phase',0,-1,-6.3,6.3))
	  f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'_c>_'+'1'+'_mag',25,-1,low,up))
	  f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'_c>_'+'1'+'_phase',0,-1,-6.3,6.3))
	  fix=0

	for num in range(2,5):
	  rand_mag = random.random() * 100.0
	  rand_magerr=max(0.1*rand_mag,1)
	  rand_phase = (random.random()*2.0-1)*6.28

	  f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'_b>_'+str(num)+'_mag',rand_mag, rand_magerr,low,up))
	  f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'_b>_'+str(num)+'_phase',rand_phase, 1,-6.3,6.3))
	  f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'_c>_'+str(num)+'_mag',rand_mag, rand_magerr,low,up))
	  f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'_c>_'+str(num)+'_phase',rand_phase, 1,-6.3,6.3))

  f2.close()




