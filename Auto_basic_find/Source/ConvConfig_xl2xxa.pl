#!/usr/bin/perl
use strict;

if($#ARGV!=1){
  print  "$0  source_file  target_file\n";
  exit -1
}

open FH,"<",$ARGV[0];
open FHb,">",$ARGV[1];

while(<FH>){
  s#X#x#g;
  if(/^\s*(\w+)_(\w+)\s*(\w+)\s*(\w+).*yes/){
    my($xname, $jpc, $rnamepre,$rnamesuf)=($3,$4,$1,$2);
    $xname=~s/X/x/;
    print FHb  $xname,"_",$jpc,"_","$rnamepre$rnamesuf\n";
  }
}

close FH;
close FHb;
