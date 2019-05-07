#!/usr/bin/perl
use strict;

if($#ARGV!=1){
  print "$0  sourcefile  targetfile\n";
  exit -1;
}

open FH,"<",$ARGV[0];
open FHb,">",$ARGV[1];

while(<FH>){
  s#x#X#g;
  if(/([^_]+)_([^_]+)_(\D+)(\d)(\w+)/){
    print FHb  $3,$4,"_",$5,"\t",$1,"\t",$2,"\t","$3","\t",$4,"\t11\tyes\n";
  }
}

close FH;
close FHb;
