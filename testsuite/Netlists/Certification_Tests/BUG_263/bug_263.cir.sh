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

# Since the shell script runs Xyce and the comparison program, it is
# responsible for capturing any error output from Xyce and the STDOUT & STDERR
# from the comparison program.  The outside script, run_xyce_regression,
# expects the STDERR output from Xyce to go into $CIRFILE.err, the STDOUT
# output from comparison to go into $CIRFILE.prn.out and the STDERR output from
# comparison to go into $CIRFILE.prn.err.  


$XYCE=$ARGV[0];
#$XYCE_VERIFY=$ARGV[1];
#$XYCE_COMPARE=$ARGV[2];
$CIRFILE=$ARGV[3];
#$GOLDPRN=$ARGV[4];

$CMD="$XYCE $CIRFILE > /dev/null 2> $CIRFILE.err";
if (system("$CMD") != 0) { print "Exit code = 10\n"; exit 10; }

open(OUT,"$CIRFILE.csd");
$line = <OUT>;
if (not ($line =~ m/^\#H/)) { $failure=1; }
$line = <OUT>;
if (not ($line =~ m/^SOURCE=\'Xyce\'\s+VERSION=/)) { $failure=1; }
$line = <OUT>;
if (not ($line =~ m/^TITLE=\'\* bug_263.cir\'/i)) { $failure=1; }
$line = <OUT>;
if (not ($line =~ m/^SUBTITLE=\'Xyce data\'/)) { $failure=1; }
$line = <OUT>;
if (not ($line =~ m/^TIME=.*\s+DATE=.*\s+TEMPERATURE=/)) { $failure=1; }
$line = <OUT>;
if (not ($line =~ m/^ANALYSIS=\'Transient Analysis\'\s+SERIALNO=\'12345\'/)) { $failure=1; }
$line = <OUT>;
if (not ($line =~ m/^ALLVALUES=\'NO\'\s+COMPLEXVALUES=\'NO\'\s+NODES=\'2\'/)) { $failure=1; }
$line = <OUT>;
if (not ($line =~ m/^SWEEPVAR=\'Time\'\s+SWEEPMODE=\'VAR_STEP\'/)) { $failure=1; }
$line = <OUT>;
if (not ($line =~ m/^XBEGIN=.*\s+XEND=/)) { $failure=1; }
$line = <OUT>;
if (not ($line =~ m/^FORMAT=/)) { $failure=1; }
$line = <OUT>;
if (not ($line =~ m/^DGTLDATA=\'NO\'/)) { $failure=1; }
$line = <OUT>;
if (not ($line =~ m/^\#N/)) { $failure=1; }
$line = <OUT>;
if (not ($line =~ m/^\'V\(1\)\'\s+\'V\(2\)\'/)) { $failure=1; }
while (($line1=<OUT>) and ($line2=<OUT>))
{
  if (not ($line1 =~ m/^\#C\s+\d\.\d+e[+-]\d{2,3}\s+2/)) { $failure=1; }
  if (not ($line2 =~ m/\d\.\d+e[+-]\d{2,3}:1\s+\d\.\d+e[+-]\d{2,3}:2/)) { $failure=1; }
}
if (not ($line1 =~ m/^\#;\r*$/)) { $failure=1; }
close(OUT);

if (defined $failure)
{
  print "Exit code = 2\n"; exit 2;
} 
else
{
  print "Exit code = 0\n"; exit 0;
}

print "Exit code = 1\n"; exit 1;
