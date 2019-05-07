#!/usr/bin/perl
use strict;

chomp(my @nums=<>);
@nums=grep {$_ ne ""} @nums;

sub numeric_sort{
  $a <=> $b;
}

@nums=sort numeric_sort @nums;
my $l_size=$#nums;
if($l_size<0){
  print 0;
  exit -1;
}

my $likelihood=$nums[0];
my $like_index=0;

for(my $i=0;$i<=0;$i++){
  my $ncount=0;
  for(my $j=0;$j<=$l_size;$j++){
    my $L_diff=abs($nums[$j] - $nums[$i]);
    $ncount++ if($L_diff<0.5);
  }

  if($ncount>=2 && $nums[$i]<$likelihood){
    $likelihood=$nums[$i];
    $like_index=$i;
  }
  last if($i>=100);
}

print $likelihood;
