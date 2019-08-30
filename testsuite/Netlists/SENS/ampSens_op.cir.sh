#!/usr/bin/env perl

# The input arguments to this script are:
# $ARGV[0] = location of Xyce binary
# $ARGV[1] = location of xyce_verify.pl script
# $ARGV[2] = location of compare script  (This is NEVER used and can be ignored)
# $ARGV[3] = location of circuit file to test
# $ARGV[4] = location of gold standard prn file

# This test case runs a simple biased transistor and computes the
# sensitivities with respect to a few model variables.  This test tests if the 
# .op command will work with .print sens.  It is compared to an equivalent 
# calculation that uses an equivalent .dc statement.
#
$XYCE=$ARGV[0];
$XYCE_VERIFY=$ARGV[1];
$CIRFILE=$ARGV[3]; 

$CIR1 = $CIRFILE;
$CIR2 = $CIRFILE;
$CIR2 =~ s/op.cir/10v.cir/;

`rm -f $CIR1*prn* $CIR1*.out $CIR2*prn* $CIR2*.out $CIR1.err $CIR2.err $CIR1.prn.err $CIR2.prn.err`;
$CMD="$XYCE $CIR1 > $CIR1.out 2> $CIR1.err";
if (system($CMD) != 0)
{
    print "Xyce EXITED WITH ERROR! on $CIR1\n";
    $xyceexit=1;
}
else
{
    if (-z "$CIR1.err" ) {`rm -f $CIR1.err`;}
}

if (defined ($xyceexit)) {print "Exit code = 10\n"; exit 10;}

if ( ! -f "$CIR1.SENS.prn")
{
    print STDERR "$CIR1.SENS.prn not created\n";
    print "Exit code = 14\n";
    exit 14;
}

#Run the reference circuit
$CMD="$XYCE $CIR2 > $CIR2.out 2> $CIR2.err";
if (system($CMD) != 0)
{
    print "Xyce EXITED WITH ERROR! on $CIR2\n";
    $xyceexit=1;
}
else
{
    if (-z "$CIR2.err" ) {`rm -f $CIR2.err`;}
}

if (defined ($xyceexit)) {print "Exit code = 10\n"; exit 10;}

if ( ! -f "$CIR2.prn")
{
    print STDERR "$CIR2.prn not created\n";
    print "Exit code = 14\n";
    exit 14;
}

#$CMD="$XYCE_VERIFY --printline=sens $CIR1 $CIR2.SENS.prn  $CIR1.SENS.prn > $CIR1.prn.out 2> $CIR1.prn.err";
$CMD="diff  $CIR2.SENS.prn  $CIR1.SENS.prn > $CIR1.prn.out 2> $CIR1.prn.err";

if (system($CMD) != 0)
{
    print STDERR "Comparison between analytic and FD sensitivities failed, see $CIR1.prn.err for detail.\n";
    print "Exit code = 2\n";
    exit 2;
}
else
{
    print "Exit code = 0\n";
    exit 0;
}
