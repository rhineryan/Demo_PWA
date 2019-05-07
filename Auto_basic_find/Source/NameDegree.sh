#!/bin/bash

#cat wave2.cfg|perl -nle 'print $1,$2 if/(<.*\|[^_]*_[^_>]*).*(>)/'|uniq -c|perl -anle '$num++;printf "%-40s%9d%9d%9d%9d\n",$F[1],$num,$num,1,$num}BEGIN{$num=0;'

cat wave2.cfg | perl -nle 'print $1,"_",$2,$3 if/<(.*)\|([^_]*)_([^_>]*).*>/' | uniq -c | perl -anle 'if($F[1]=~/f/){$F[0]*=2}else{$F[0]*=1} print $F[1]'|xargs -n5
echo
cat wave2.cfg | perl -nle 'print $1,"_",$2,$3 if/<(.*)\|([^_]*)_([^_>]*).*>/' | uniq -c | perl -anle 'if($F[1]=~/f/){$F[0]*=2}else{$F[0]*=1} print $F[0]'|xargs -n5
