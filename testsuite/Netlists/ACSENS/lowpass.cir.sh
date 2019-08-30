#!/usr/bin/env perl

# The input arguments to this script are:
# $ARGV[0] = location of Xyce binary
# $ARGV[1] = location of xyce_verify.pl script
# $ARGV[2] = location of compare script  (This is NEVER used and can be ignored)
# $ARGV[3] = location of circuit file to test
# $ARGV[4] = location of gold standard prn file

# This test case runs a simple biased transistor and computes the
# sensitivities with respect to a few model variables.
#
# A second netlist, in which the sensitivities are generated by finite
# differencing between perturbed copies of the circuit, is also run.  The
# analytic sensitivities from the first netlist are compared to the
# sensitivities from the second.

$XYCE=$ARGV[0];
$XYCE_VERIFY=$ARGV[1];
$CIRFILE=$ARGV[3];

$XYCE_ACVERIFY = $XYCE_VERIFY;
$XYCE_ACVERIFY =~ s/xyce_verify/ACComparator/;

$CIR1=$CIRFILE;
$GOLDSCRIPT="./lowpass.cir.FD.SENS.prn.gs.pl";

`rm -f $CIR1.FD.SENS.prn $CIR1.err $CIR1.FD.SENS.prn.gs $GOLDSCRIPT.err`;

$CMD="$XYCE $CIR1 > $CIR1.out 2> $CIR1.err";
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

#If this is a VALGRIND run, we don't do our normal verification, we
# merely run "valgrind_check.sh" as if it were xyce_verify.pl
if ($XYCE_VERIFY =~ m/valgrind_check/)
{
  print STDERR "DOING VALGRIND RUN INSTEAD OF REAL RUN!";
  if (system("$XYCE_VERIFY $CIRFILE unusedarg > $CIRFILE.prn.out 2>&1 $CIRFILE.prn.err"))
  {
    print "Exit code = 2 \n";
    exit 2;
  }
  else
  {
    print "Exit code = 0 \n";
    exit 0;
  }
}

$retcode=0;

if (-f "$CIRFILE.FD.SENS.prn")
{
  # generate the analytic gold standard
  $CMD="$GOLDSCRIPT > /dev/null 2> $GOLDSCRIPT.err";
  $retval=system($CMD);
  # not sure how to process retval here.... fix later

  #comparison tolerances for ACComparator.pl
  $abstol=1.0;
  $reltol=1e-3;  #0.1%
  $zerotol=1e-8;
  $freqreltol=1e-6;

  $CMD="$XYCE_ACVERIFY  $CIR1.FD.SENS.prn.gs $CIR1.FD.SENS.prn $abstol $reltol $zerotol $freqreltol";
  $retval=system($CMD);
  $retval = $retval >> 8;
  if ($retval != 0)
  {
    print STDERR "Comparator exited with exit code $retval on file $CIRFILE.FD.prn\n";
    $retcode = 2;
  }
}
else
{
  print STDERR "Missing output file: $CIRFILE.FD.SENS.prn\n";
  $retcode = 14;
}

print "Exit code = $retcode\n"; exit $retcode;



