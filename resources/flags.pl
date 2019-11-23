#!/usr/bin/perl -w

use strict;

my $textfile = open(FILE, "flags.txt")
	or die "flags.txt: $!\n";

print "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n<FLAGS>\n";

while (defined (my $line = <FILE>) )
{
	my ($short, $long, $code) = split (/\s\t+/, $line);
	$code =~ s/\n//;
	$code = lc ($code);
	print "\t<FLAG CODE=\"$code\" SHORT=\"$short\" LONG=\"$long\"/>\n";
}

print "</FLAGS>\n";

close(FILE);

