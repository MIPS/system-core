#!/usr/bin/perl 
#===============================================================================
#
#         FILE:  generateGCCArgCode.pl
#
#        USAGE:  ./generateGCCArgCode.pl
#
#  DESCRIPTION:  Display the GCC code generated for each combination of
#                different type arguments for MIPS
#
#        NOTES:  Output will be generated as files of name /tmp/tmpp.*
#       AUTHOR:  Bhanu Chetlapalli
#        EMAIL:  bhanu@mips.com
#      COMPANY:  MIPS Technologies
#      CREATED:  10/08/2010 11:47:31 AM
#===============================================================================

use strict;
use warnings;

my $GCC = "mips-linux-gnu-gcc";

# generate Combination of arguments
my @argtypes = ("int", "float", "double");
my @argvals = ("0", "0.0f", "0.0");
my @argshrt = ("i", "f", "d");

for (my $i = 0; $i < 81; $i++) {
    my $argcombs = 
        $argtypes[int($i/27)% 3] . ", " .
        $argtypes[int($i/9) % 3] . ", " .
        $argtypes[int($i/3) % 3] . ", " .
        $argtypes[    $i    % 3];

    my $valcombs = 
        $argvals[int($i/27)% 3] . ", " .
        $argvals[int($i/9) % 3] . ", " .
        $argvals[int($i/3) % 3] . ", " .
        $argvals[    $i    % 3];
    my $fnbase = "/tmp/c_inp.".
        $argshrt[int($i/27)% 3] . "." .
        $argshrt[int($i/9) % 3] . "." .
        $argshrt[int($i/3) % 3] . "." .
        $argshrt[    $i    % 3] . ".";
    my $fn = $fnbase."c";
    my $fns = $fnbase."s";
    my $fnp = $fnbase."p";

# Generate a C file

    open(OUT, ">$fn") or die;

    print OUT "extern void test($argcombs);\n\n";
    print OUT "void f(void) { asm(\"#START_TEST\");\n";
    print OUT "test($valcombs);\n";
    print OUT "asm(\"#END_TEST\");}\n";

    close OUT;

# Run gcc assembler
    system("$GCC -S $fn -o $fns");
    
    my $fnptmp = "/tmp/tmpp";
    open(AS, $fns) or die;
    open(FP, ">$fnptmp") or die;
    my $start = 0;
#    print FP "test($argcombs)\n";
    while (<AS>) {
        $start++ if (/#APP/);
        if ($start == 2) {
            # Only print the registers we are intersted in (arg regs)
            print FP if (/\$f12/);
            print FP if (/\$f13/);
            print FP if (/\$f14/);
            print FP if (/\$f15/);
            print FP if (/\$4/);
            print FP if (/\$5/);
            print FP if (/\$6/);
            print FP if (/\$7/);
        }
        $start++ if (/#NO_APP/);
    }
    close FP;
    system("sort $fnptmp > $fnp");
# We can use these files to figure out how GCC actually populates stacks
}

