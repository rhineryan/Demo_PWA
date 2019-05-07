#!/usr/bin/perl
use strict;
if($#ARGV!=1){
  print $0," sfile  tfile\n";
  exit(-1);
}

open FH,"<",$ARGV[0];
chomp(my @fList=<FH>);
close FH;

open FB,">",$ARGV[1];
for my $i (@fList){
  my @num=$i=~/(\d)_/;
  if($i=~/-/){next;}
  if($i=~/K/){
    $i=~s/\+$//;

    printf FB "%-15s%-5s%-10s%-5s%10s\n",$i,"a",$num[0],11,"yes";
  }else{
    printf FB "%-15s%-5s%-10s%-5s%10s\n",$i,"f",$num[0],11,"yes";
  }
}
close FB;

