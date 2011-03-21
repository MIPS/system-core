#!/usr/bin/perl 
#===============================================================================
#
#         FILE:  generateArgPermutations.pl
#
#        USAGE:  ./generateArgPermutations.pl
#
#  DESCRIPTION:  Generate a testcase to test if all argument types are being
#                processed correctly by libacc
#
#        NOTES:  Output will be generated in out.c
#       AUTHOR:  Bhanu Chetlapalli
#        EMAIL:  bhanu@mips.com
#      COMPANY:  MIPS Technologies
#      CREATED:  10/08/2010 11:47:31 AM
#===============================================================================

use strict;
use warnings;

# generate Combination of arguments
my @argtypes = ("int i", "float f", "double d");
my @argshrt = ("i", "f", "d");

open(OUT, ">out.c") or die;
my $str = "";

print OUT "void abrt() {\n *(int*)(0) = 1; \n}\n";

for (my $numargs = 5; $numargs <= 5; $numargs++) {
    for (my $i = 0; $i < 3**$numargs; $i++) {
        my $argcombs = "";

        for (my $j = 0; $j < $numargs; $j++) {
            $argcombs .= $argtypes[int($i/(3**$j))% 3] . "$j, ";
        }
        chop $argcombs;
        chop $argcombs;

        my $fnbase = "";

        for (my $j = 0; $j < $numargs; $j++) {
            $fnbase .= $argshrt[int($i/(3**$j))% 3] . "_";
        }
        chop $fnbase;

        print OUT "void test_$fnbase($argcombs) { \n";

        my $valcombs = "";
        for (my $j = 0; $j < $numargs; $j++) {
            if (int($i/(3**$j))% 3 == 0) {
                # Int
                my $x = int(rand(0x7FFFFFFF));
                $valcombs .= "$x, ";
                print OUT "\tif (i$j != $x) { printf(\"test_$fnbase failed\\n\"); abrt(); }\n";
            } elsif (int($i/(3**$j))% 3 == 1) {
                # Float
                my $x = rand(10000000);
                $valcombs .= $x."f, ";
                print OUT "\tif (f$j != $x"."f) { printf(\"test_$fnbase failed\\n\"); abrt(); }\n";
            } elsif (int($i/(3**$j))% 3 == 2) {
                # Float
                my $x = rand(10000000);
                $valcombs .= $x."0, ";
                print OUT "\tif (d$j != $x"."0) { printf(\"test_$fnbase failed\\n\"); abrt(); }\n";
            }
        }
        chop $valcombs;
        chop $valcombs;

        print OUT "\t\n";
        print OUT "} \n";
        $str .= "\ttest_$fnbase($valcombs);\n";
    }
}
print OUT "int main(int argc, char **argv) { \n";
print OUT "$str\n";
print OUT "}\n";

close OUT;

