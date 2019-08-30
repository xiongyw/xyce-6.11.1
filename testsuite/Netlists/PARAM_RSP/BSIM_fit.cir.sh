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
$CIRFILE=$ARGV[3];
$GOLDPRN=$ARGV[4];

# these are the tolerances used in comparing the measures calculated by this 
# script to those calculated by Xyce.  Zerotol is needed because some measured
# values should be zero (and reltol won't make sense in that case).

my $absTol = 3.0e-3;
my $relTol = 0.02;
my $zeroTol = 1.0e-5;

if (defined($verbose)) { $Tools->setVerbose(1); }

sub verbosePrint { $Tools->verbosePrint(@_); }

$retval = -1;
my @paramsFiles = ( "BSIM_fit_params1.in",  "BSIM_fit_params2.in", "BSIM_fit_params3.in" );
my @responseFiles = ("BSIM_fit_resp1.out", "BSIM_fit_resp2.out", "BSIM_fit_resp3.out");

for $i (0..2)
{
  # have to call Xyce manually here to stick in extra args
  $CMD="$XYCE -prf $paramsFiles[$i] -rsf $responseFiles[$i] $CIRFILE > $CIRFILE.$i.out";
  print "$CMD\n";
  $retval=system($CMD)>>8;
  if ($retval != 0) { print "Exit code = $retval\n"; exit $retval; }
  if (not -s "$CIRFILE.prn" ) { print "Exit code = 14\n"; exit 14; }
}

# the response values from the three simulations will be in the output file
# and not yet in the $responseFile[123]. The results should 
# be different as the underlying model should have changed at each 
# simulation.
#
# accepted values are:
#  Param set               Residual in curve fit
#    1                         VSQ = 4.254545e-05
#    2                         VSQ = 2.515038e-05
#    3                         VSQ = 1.885232e-04
#

# I will parse these out of the Xyce output and compare them to the expected 
# values we have. 
my @VSQ_Values = (4.254545e-05, 2.515038e-05, 1.885232e-04);

for $i (0..2)
{
  open(RESULT_FILE,  "$CIRFILE.$i.out");
  my $absError = 0.0;
  my $relError = 0.0;
  my $value = 0.0;
  while( $line=<RESULT_FILE> )
  {
    if( $line =~ /^VSQ = / )
    {
      chop $line;
      # Remove leading spaces on line, otherwise the spaces become element 0 of "@lineOfDataFromXyce" instead of the first column of data.
      $line =~ s/^\s*//;
      #    print STDERR "Line of data = \'$line\'\n";
      ($name, $value, $sep) = (split(/\s+=\s+/, $line));
    }
  }
  close(RESULT_FILE);
  $absError = $VSQ_Values[$i] - $value;
  if( $value != 0.0 )
  {
    $relError = $absError / $value;
  }
  else
  {
    print "Error: Objective value for VSQ value not correctly read from output file.  \n";
    $retval = 2;
  }
  if( (abs( $absError ) > $absTol) || (abs( $relError ) > $relTol) ) 
  {
    print "\nSimulation $i is out of tolerance with absErr = $absError and relErr = $relError\n";
    print "Simulation VSQ value $i = $value, Gold VSQ value $i = $VSQ_Values[$i]\n";
    $retval = 2;
  }
}


if ( $retval != 0 )
{
  verbosePrint "test Failed!\n";
  print "\nExit code = $retval\n"; 
  exit $retval;
}
  
verbosePrint "test Passed!\n";
print "\nExit code = $retval\n"; 
exit $retval;

