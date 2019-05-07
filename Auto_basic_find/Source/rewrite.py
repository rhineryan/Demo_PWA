#!/usr/bin/env python
import os
import sys
from sys import argv
from math import fabs
import re

if len(argv)!=2:
  print "usuage:",argv[0],"fliename" 
  sys.exit(-1)


f=open(argv[1],'r')
fList=f.readlines()
f.close()

f2=open(argv[1],'w')

for line in fList:
  arr=line.split()
  if(len(arr)==6):
    f2.write('%-30s=%30s%20s%-30s%20s%20s\n'%(arr[0], arr[2]," ",arr[3], arr[4], arr[5]))

