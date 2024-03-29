#!/bin/sh

# The input arguments to this script are:
# $1 = location of Xyce binary
# $2 = location of xyce_verify.pl script
# $3 = location of compare script 
# $4 = location of circuit file to test
# $5 = location of gold standard prn file
# $6 = tags list

# If Xyce does not produce a prn file, then we return exit code 10.
#
# For this test we only care that Xyce ran and did not exit with an error
#


# Since the shell script runs Xyce also, it is responsible for capturing any
# error output from Xyce.  The script run_xyce_regression captures the test
# output and handles the resulting files.  

XYCE=$1
XYCE_VERIFY=$2
#XYCE_COMPARE=$3
CIRFILE=$4
GOLDPRN=$5

CIR1=$CIRFILE

rm -f $CIR1.prn $CIR1.err $CIR1.out 

$XYCE $CIR1 > $CIR1.out 2> $CIR1.err

if [ "$?" -ne "0" ]; then
  echo "Exit code = 10"
  exit 10
else

  $XYCE_VERIFY $CIR1 $GOLDPRN $CIR1.prn
  if [ $? -eq 0 ]; then
      echo "Exit code = 0"
      exit 0
  else
      echo "Exit code = 2"
      exit 2
  fi
fi



