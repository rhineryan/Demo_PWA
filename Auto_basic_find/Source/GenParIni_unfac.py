#!/usr/bin/env python
import os
import sys
from sys import argv
from math import fabs
import re

if len(argv)!=3:
  print "usuage:",argv[0],"oriflie  targetfile"
  sys.exit(-1)

f1=open(argv[1],'r')
f2=open(argv[2],'w')

fix=1
f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%("bg_mag",0,-1,-500,500))
f2.write('\n');

for line in f1:
  line=line.rstrip()
  if line.find('yes')!=-1:
    arr=line.split()

    if fix==0:
      f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'>_'+'1'+'_mag',0, 1,-500,500))
      f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'>_'+'1'+'_phase',0, 1,-6.3,6.3))

    if fix==1:
      f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'>_'+'1'+'_mag',25,-1,-500,500))
      f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'>_'+'1'+'_phase',0,-1,-6.3,6.3))
      fix=0

    for num in range(2,5):
      f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'>_'+str(num)+'_mag',0,1,-500,500))
      f2.write("%-30s=%30.3f%30.3f%20.1f%20.1f\n"%('<'+arr[1]+'_'+arr[2]+'|'+arr[0]+'>_'+str(num)+'_phase',0,1,-6.3,6.3))

    f2.write('\n')

f1.close()
f2.close()



