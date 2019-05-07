#!/usr/bin/perl
use strict;

chomp(my @nums=<>);
@nums=grep {$_ ne "" &&(!($_=~/nan/)) && (!($_=~/inf/))} @nums;

sub numeric_sort{
  $a <=> $b;
}

@nums=sort numeric_sort @nums;
my $l_size=$#nums;
if($l_size<0){
  print 0;
  exit -1;
}

my $likelihood=$nums[-1];
my $like_index=-1;

for(my $i=0;$i<=$l_size;$i++){
  my $ncount=0;
  for(my $j=0;$j<=$l_size;$j++){
    my $L_diff=abs($nums[$j] - $nums[$i]);
    $ncount++ if($L_diff<1);
  }

  if($ncount>=3 && $nums[$i]<$likelihood){
    $likelihood=$nums[$i];
    $like_index=$i;last;
  }
  last if($i>=100);
}

if($like_index==-1) {$likelihood=9999999;}

print $likelihood;
