#!/usr/bin/env python
import random
import sys
from sys import argv
if len(argv) != 2:
  print argv[0],"likelyhoodfile"
  sys.exit(-1)

L = []
n_like=0
fwave = open(argv[1],"r")
iter_f = iter(fwave)
for line in iter_f:
  line=line.strip('\n')
  L.append(line)
  n_like+=1
if n_like>=100:
  n_like_100 =100
else:
  n_like_100 = n_like


run1_tem=0
L_tem=0
ncout_tem=0
nname=1
run1=0

while run1<n_like_100:
  ncout=0
  run2=0
  while run2<n_like_100:
    L_diff = float(L[run1]) - float(L[run2])
    if abs(L_diff) < 0.5:
      ncout+=1
    run2+=1
#  if ncout > ncout_tem:
  if ncout > 2 and float(L[run1]) < L_tem:
    L_tem = float(L[run1])
    ncout_tem = ncout
    run1_tem = run1
    break
  run1+=1
if ncout_tem==0:
  print L[0]
else:
  print L[run1_tem]
