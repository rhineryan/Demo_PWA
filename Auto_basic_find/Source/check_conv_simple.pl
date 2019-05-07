#!/usr/bin/perl
use strict;

chomp(my @nums=<>);
@nums=grep {$_ ne ""} @nums;

sub numeric_sort{
  $a <=> $b;
}

@nums=sort numeric_sort @nums;
my $l_size=$#nums;

my $ncount=0;
for(my $j=1;$j<=$l_size;$j++){
  my $L_diff=abs($nums[$j] - $nums[0]);

  $ncount++ if($L_diff<15);

  last if($j>=100);
}

if($ncount<=0){
  print 0;
}else{
  print 1;
}
