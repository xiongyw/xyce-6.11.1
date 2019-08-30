#!/usr/bin/env perl

use XyceRegression::Tools;

$Tools = XyceRegression::Tools->new();
#$Tools->setDebug(1);
#$Tools->setVerbose(1);

# The input arguments to this script are:
# $ARGV[0] = location of Xyce binary
# $ARGV[1] = location of xyce_verify.pl script
# $ARGV[2] = location of compare script 
# $ARGV[3] = location of circuit file to test
# $ARGV[4] = location of gold standard prn file

# If Xyce does not produce a prn file, then we return exit code 10.
# If Xyce succeeds, but the test fails, then we return exit code 2.
# If the shell script fails for some reason, then we return exit code 1.
# Otherwise we return the exit code of compare or xyce_verify.pl

# Since the shell script runs Xyce and the comparison program, it is
# responsible for capturing any error output from Xyce and the STDOUT & STDERR
# from the comparison program.  The outside script, run_xyce_regression,
# expects the STDERR output from Xyce to go into $CIRFILE.err, the STDOUT
# output from comparison to go into $CIRFILE.prn.out and the STDERR output from
# comparison to go into $CIRFILE.prn.err.  

use Getopt::Long;

&GetOptions( "verbose!" => \$verbose );
$XYCE=$ARGV[0];
$XYCE_VERIFY=$ARGV[1];
#$XYCE_COMPARE=$ARGV[2];
#$CIRFILE=$ARGV[3];
$GOLDPRN=$ARGV[4];

$CIRFILE1="bug402XyceTempOptions.cir";
$CIRFILE2="bug402SpiceTempOptions.cir";

if (defined($verbose)) { $Tools->setVerbose(1); }

sub verbosePrint { $Tools->verbosePrint(@_); }

$retval = -1;
$retval=$Tools->wrapXyce($XYCE,$CIRFILE1);
if ($retval != 0) { print "Failed on $CIRFILE1 \nExit code = $retval\n"; exit $retval; }
if (not -s "$CIRFILE1.prn" ) { print "Failed on $CIRFILE1 \nExit code = 14\n"; exit 14; }

$retval=$Tools->wrapXyce($XYCE,$CIRFILE2);
if ($retval != 0) { print "Failed on $CIRFILE2 \nExit code = $retval\n"; exit $retval; }
if (not -s "$CIRFILE2.prn" ) { print "Failed on $CIRFILE2 \nExit code = 14\n"; exit 14; }

# compare the output from $CIRFILE1 and $CIRFILE2 using xyce_verify.pl
$CMD="$XYCE_VERIFY $CIRFILE1 $CIRFILE1.prn $CIRFILE2.prn";
$retval = system("$CMD");
$retval = $retval >> 8;

if ( $retval != 0 )
{
  verbosePrint "test Failed!\n";
  print "Exit code = $retval\n"; 
  exit $retval;
}
  
verbosePrint "test Passed!\n";
print "Exit code = $retval\n"; 
exit $retval;

