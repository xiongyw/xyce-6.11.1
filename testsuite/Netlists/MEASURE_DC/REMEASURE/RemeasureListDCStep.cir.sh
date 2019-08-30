#!/usr/bin/env perl

use MeasureCommon;

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

$XYCE=$ARGV[0];
$XYCE_VERIFY=$ARGV[1];
#$XYCE_COMPARE=$ARGV[2];
$CIRFILE=$ARGV[3];
$GOLDPRN=$ARGV[4];

$fc=$XYCE_VERIFY;
$fc =~ s/xyce_verify/file_compare/;

# remove files from previous runs
system("rm -f $CIRFILE.ms0 $CIRFILE.out $CIRFILE.err* $CIRFILE.remeasure*");

# run Xyce and check for the proper files
$CMD="$XYCE $CIRFILE > $CIRFILE.out 2> $CIRFILE.err";
$retval=system($CMD);
if ($retval != 0)
{
  if ($retval & 127)
  {
    print "Exit code = 13\n"; 
    printf STDERR "Xyce crashed with signal %d on file %s\n",($retval&127),$CIRFILE; 
    exit 13;
  }
  else
  {
    print "Exit code = 10\n"; 
    printf STDERR "Xyce exited with exit code %d on %s\n",$retval>>8,$CIRFILE; 
    exit 10;
  }
}

#check for output files
if (not -s "$CIRFILE.prn" ) {print "Exit code = 14\n"; exit 14; }
if (not -s "$CIRFILE.ms0" ) { print "Exit code = 17\n"; exit 17; }

# these are the tolerances used in comparing the measured and re-measured data.  
# zeroTol is needed because some measured values should be zero (and relTol 
# won't make sense in that case).
my $absTol = 1.0e-5;
my $relTol = 1e-3;
my $zeroTol = 1.0e-10;

# Re-measure test uses the same approach as the FOUR measure
$retval = MeasureCommon::checkRemeasure($XYCE,$XYCE_VERIFY,$CIRFILE,$absTol,$relTol,$zeroTol,'prn',1,'ms');

# exit if the remeasure test failed.
if ($retval != 0)
{
  print STDERR "test failed comparison of Gold and measured .ms0 files with exit code $retval\n";
  print "Exit code = 2";
  exit 2;
}

# check that .out file exists for re-measure, and open it if it does
if (not -s "$CIRFILE.remeasure.out" ) 
{ 
  print "Exit code = 17\n"; 
  exit 17; 
}
else
{
  open(NETLIST, "$CIRFILE.remeasure.out");
  open(ERRMSG,">$CIRFILE.remeasure.errmsg") or die $!;
}

# now check the remeasure stdout
# parse the remeasure.out file to find the text related to remeasure
my $foundStart=0;
my $foundEnd=0;
my @outLine;
my $lineCount=0;
while( $line=<NETLIST> )
{
  if ($line =~ /In OutputMgr::remeasure/) { $foundStart = 1; }
  if ($foundStart > 0 && $line =~ /Remeasure analysis complete/) { $foundEnd = 1; }  

  if ($foundStart > 0 && $foundEnd < 1)
  {
    print ERRMSG $line;
  } 
}

close(NETLIST);
close(ERRMSG);

# test that the values and strings in the .out file match the Gold File 
# to the required tolerances
$GSFILE="RemeasureListDCStepGSfile";
$CMD="$fc $CIRFILE.remeasure.errmsg $GSFILE $absTol $relTol $zeroTol > $CIRFILE.remeasure.errmsg.out 2> $CIRFILE.remeasure.errmsg.err";
$retval=system($CMD);
$retval = $retval >> 8;

if ( $retval != 0 )
{
  print STDERR "test failed comparison of stdout vs. GSfile for remeasure with exit code $retval\n";
  print "Exit code = 2\n";
  exit 2;
}
else
{
  print "Passed comparison of stdout info for remeasure\n";
}

print "Exit code = $retval\n";
exit $retval;


