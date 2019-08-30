#!/usr/bin/env perl

use XyceRegression::Tools;

$Tools = XyceRegression::Tools->new();
#$Tools->setDebug(1);

# The input arguments to this script are: 
# $ARGV[0] = location of Xyce binary
# $ARGV[1] = location of xyce_verify.pl script
# $ARGV[2] = location of compare script 
# $ARGV[3] = location of circuit file to test
# $ARGV[4] = location of gold standard prn file

# If Xyce does not produce a prn file, then we return exit code 10.
# If Xyce succeeds, but the test fails, then we return exit code 2.
# If the shell script fails for some reason, then we return exit code 1.

# Since the shell script runs Xyce and the comparison program, it is
# responsible for capturing any error output from Xyce and the STDOUT & STDERR
# from the comparison program.  The outside script, run_xyce_regression,
# expects the STDERR output from Xyce to go into $CIRFILE.err, the STDOUT
# output from comparison to go into $CIRFILE.prn.out and the STDERR output from
# comparison to go into $CIRFILE.prn.err.  

use Getopt::Long;
&GetOptions( "verbose!" => \$verbose );
if (defined($verbose)) { $Tools->setVerbose(1); }
$Tools->setVerbose(1);

$XYCE=$ARGV[0];
#$XYCE_VERIFY=$ARGV[1];
#$XYCE_COMPARE=$ARGV[2];
$CIRFILE=$ARGV[3];
#$GOLDPRN=$ARGV[4];

# remove files from previous runs
system("rm -f $CIRFILE.out");

# these search strings are supposed to occur as a warning message
# in the stdout
@searchstrings = (["Netlist warning in file ParsingHelpers_handleIncludeLine.cir at or near line 9",
    "Extraneous data on .INCLUDE ignored"],
   ["Netlist warning in file ParsingHelpers_handleIncludeLine.cir at or near line 10",
    ".INC is missing argument\\(s\\), ignoring"]
);

$retval = $Tools->runAndCheckGroupedWarning($CIRFILE,$XYCE,@searchstrings);

print "Exit code = $retval\n";
exit $retval;
