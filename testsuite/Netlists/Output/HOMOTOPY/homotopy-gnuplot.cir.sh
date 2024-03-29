#!/usr/bin/env perl

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

# Since the shell script runs Xyce also, it is responsible for capturing any
# error output from Xyce.  The script run_xyce_regression captures the test
# output and handles the resulting files.  

$XYCE=$ARGV[0];
$XYCE_VERIFY=$ARGV[1];
#$XYCE_COMPARE=$ARGV[2];
$CIRFILE=$ARGV[3];
$GOLDPRN=$ARGV[4];

$GOLDPRN =~ s/\.prn$//; # remove the .prn at the end.

# remove old files if they exist
`rm -f $CIRFILE.HOMOTOPY.prn $CIRFILE.prn $CIRFILE.err`;
`rm -f $CIRFILE.homotopy.out $CIRFILE.homotopy.err`;

# run Xyce
$CMD="$XYCE $CIRFILE > $CIRFILE.out 2> $CIRFILE.err";
$retval = system("$CMD");
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

# Exit if the HOMOTOPY.prn file was not made
if (not -s "$CIRFILE.HOMOTOPY.prn" )
{
  print "$CIRFILE.HOMOTOPY.prn file is missing\n"; 
  print "Exit code = 14\n"; 
  exit 14;
}

# Now check the .HOMOTOPY.prn file
$absTol=1e-5;
$relTol=1e-3;
$zeroTol=1e-10;
$fc = $XYCE_VERIFY;
$fc=~ s/xyce_verify/file_compare/;
$CMD="$fc $CIRFILE.HOMOTOPY.prn $GOLDPRN.HOMOTOPY.prn $absTol $relTol $zeroTol > $CIRFILE.homotopy.out 2> $CIRFILE.homotopy.err";
$retval = system("$CMD");
if ($retval != 0)
{
  print "test Failed comparison of HOMOTOPY.prn file vs. gold HOMOTOPY.prn file!\n";
  print "Exit code = 2\n";
  exit 2;
}
else
{
  print "Passed comparison of HOMOTOPY.prn files\n";
  print "Exit code = 0\n";
  exit 0;
}



