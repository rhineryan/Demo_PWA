#!/usr/bin/env perl
use strict;

my $ncount=0;
my @arr;
while(<>){
	chomp;
	next if /^$/;
    my @line=split /\s+/,$_;
	next if $#line!=1;
	next if ($line[1] =~ /^\s*$|nan|inf/);
	my $tmp="";
	for my $n (0 .. $#line){
	  $tmp.="$n"." ".$line[$n]." ";
	}
	my %h=split /\s+/,$tmp;
	$arr[$ncount]=\%h;
	$ncount++;
}

sub num_sort{
	$a <=> $b;
}

sub num2_sort{
	$a->{1} <=> $b->{1};
}

my @arr_sort=sort num2_sort @arr;

my $l_size=$#arr_sort;
if($l_size<0){
  print 0," ",0;
  exit -1;
}

my $likelihood=$arr_sort[-1]->{1};
my $like_index=-1;


for(my $i=0;$i<=$l_size;$i++){
	my $ncount2=0;
	for(my $j=0;$j<=$l_size;$j++){
		my $L_diff=abs($arr_sort[$j]->{1} - $arr_sort[$i]->{1});
		$ncount2++ if($L_diff<15);
	}

	if($ncount2>=3 && $arr_sort[$i]->{1} < $likelihood){
		$likelihood=$arr_sort[$i]->{1};
		$like_index=$i;last;
	}
	last if($i>=100);
}

print $arr_sort[$like_index]->{0}," ",$likelihood;
