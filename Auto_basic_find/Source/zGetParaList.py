#!/usr/bin/env python

import os
import sys
import subprocess
from sys import argv
from math import fabs

targetdir='input'

if len(argv) <  2:
  print 'At least one paramaters!'
  sys.exit(-1)
elif len(argv) > 2:
  targetdir=argv[2]

num=int(argv[1])


def PrintMessage(level, message, indent = 0) :
	lvl = {0:'', 1:' ERROR :', 2:' WARNING :', 3:' INFO :'}[level]
	print indent*4*' ' + lvl, message



spath=os.getcwd()
keep=True

result = ''
para = ''
files = []
for file in os.listdir(spath) :
	file = spath + '/' + file
	if file.find('multifitresults') >= 0 and os.path.isfile(file) :
		files.append(file)
count = len(files)
if count == 0 :
	print 'FITRESULT NOT FOUND!'
	sys.exit(-1)
if count > 1 :
	print  'MULTIPLE FITRESULTS EXIST! USING THE LATEST ONE!'
	files.sort()

result = files[-1]
info = os.popen('''grep Min %s | grep -v nan | grep -v inf | sort -k6nr | tail -n%i|sort -k6n |awk '{print $2}'|sed 's/://' '''%(result,num )).readlines()

tindex=0

for index in info:
  tindex+=1
  print '===================== ',int(index)
  source = spath + '/para_output_GammaEtaPi0Pi0Analysis_%04d.txt'%(int(index), )
  target = spath + '/'+targetdir+'/paraout_%i.txt'%(tindex,)
  
  os.system('cp %s %s'%(source, target))
  input_lines = open(target, 'r')
  new_lines = []
  count = 0
  rewrite = True
  nwaves = 0
  for line in input_lines :
  	new_line = line.strip() + '\n'
  	if line.find('_c') >= 0 :
  		rewrite = False
  		break
  	if line.find('_b') >= 0 :
  		if count % 4 == 2 or count % 4 == 3 :
  			new_line = line.replace('_b', '_c')
  		count += 1
  	config = new_line.split()
  	if len(config) == 6 :
  		nwaves += 1
  		if config[0] == 'phasespace' :
  			new_line = 'phasespace                    =    0.000   -1.000  -500.0   500.0\n'
  		else :
  			low = -500
  			up = 500
  			config[2] = float(config[2])
  			config[3] = float(config[3])
  			if config[2] > 400 or config[2] < -400 :
  				PrintMessage(2, '%s = %f IS CLOSE TO BOUNDARY!'%(config[0], config[2]))
  			if config[0].find('phase') >= 0 :
  				config[2] = config[2] - (int(config[2]/6.2831853))*6.2831853
  				if not keep:
  					config[3] = 0.1
  				low = -6.3
  				up = 6.3
  				if config[3] > 0.78:
  					PrintMessage(2, '%s = %f +/- %f: ERROR MIGHT BE TOO LARGE!'%(config[0], config[2], config[3]))
  			else :
  				if not keep:
  					config[3] = max(0.1 * fabs(config[2]), 0.01)
  				if config[3] > 0.5*config[2]:
  					PrintMessage(2, '%s = %f +/- %f: ERROR MIGHT BE TOO LARGE!'%(config[0], config[2], config[3]))
  			if nwaves < 4 :
  				#new_line = '%-30s=%30.3f%30.3f%30.1f%30.1f\n'%(config[0], config[2], -1, -500, 500)
  				new_line = '%-30s=%30.3f%30.3f%30.1f%30.1f\n'%(config[0], config[2], -1, low, up)
  			else :
  				#new_line = '%-30s=%30.3f%30.3f%30.1f%30.1f\n'%(config[0], config[2], config[3], -500, 500)
  				#new_line = '%-30s=%30.3f%30.3f%30.1f%30.1f\n'%(config[0], config[2], config[3], low, up)
  				new_line = '%-30s=%30s%30s%30s%30s\n'%(config[0], config[2], config[3], low, up)
  	new_lines.append(new_line)
  input_lines.close()
  
  if rewrite :
  	output_lines = open(target, 'w')
  	for new_line in new_lines :
  		output_lines.writelines(new_line)
  	output_lines.close()
  

