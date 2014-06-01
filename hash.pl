#!/usr/bin/perl -w
use strict;

our $prime = 6673;

#Hashing Function
sub hash{
	my $key = shift;
	my @letters = split(//, $key);
	foreach (@letters){
		$_ = ord($_) -64;
	}
	my $hashvalue = 1;
	my $count = 1;
# This goes through each letter in the ticker symbol one by one and it XORs the ascii value
# with a number ( ^ is the XOR symbol in perl)
# Then takes that resulting number and raises it to the power of 7 and multiplies it by
# the position of that lettter (1 being the first) multiplied by 26.
	foreach(@letters){
		if( ($count % 2) == 1){
			$hashvalue += ($_*3)*($count*3)*11+($prime*$_*($count*4))+$_+$count;
			$count++;
		} else {
			$hashvalue += ($_*$count)*7+($_*(7*$count))+$_+$count;
			$count++;
		}
		if($count < 3){
			$hashvalue = $hashvalue/11;
		}
		if($count == 6 || $count == 3){
			$hashvalue = $hashvalue ^ 15;
		}
		if($count*$_ > 90){
			$hashvalue += 6673;
		}
	}
	$hashvalue = $hashvalue << 11;
	$hashvalue = $hashvalue % $prime;
	return $hashvalue;	

}

#This is the prime number that is used for the length of the array
my %ticker;

#Open up the file, parse it and get the ticker symbol out along with the company name
open(FD, "<bigDataDay1.cleaned") or die "Couldn't open the file: $!\n";
my $count = 0;
my $firstline = <FD>;
while(<FD>){
	my @words = split( /,/ , $_);
	$ticker{$words[1]} = $words[0];
}

# go through each ticker symbol and calculate it's hash value one by one
our %hashh;
foreach my $key (sort keys %ticker){
	my $hashvalue = hash($key);
	$hashh{$hashvalue}++;
}

my %hashstats;

foreach my $key (sort keys %hashh){
	$hashstats{$hashh{$key}}++;
#	if($hashh{$key} > 3){
#		print "$key seen $hashh{$key} times\n";
#	}
}
foreach my $key (sort keys %hashstats){

print "$hashstats{$key} keys with";
$key = $key-1; 
print " $key collisions\n";

}

my $lengthof = keys(%ticker);
print "$lengthof : $prime \n";
exit;


