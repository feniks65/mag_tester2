#!/bin/bash

if [ $# -lt 2 ]
then
	print "Please provide path to samples in the way: ./tester.sh /path/to/samples/* <numOfPieces>"
	return 1
fi

HIST_OUT="tester_hist_output.txt"

if [ -e $HIST_OUT ]
then
	rm $HIST_OUT
fi

PATH_TO_SAMPLES=$1
NUM_OF_PIECES=$2

cp ../Hist/tester ./tester_histogram
cp ../Hist/chart.py ./chart.py

if [ -e tester_histogram ]
then

	for f in $PATH_TO_SAMPLES
	do
#  		echo "Processing $f file..."
  		# take action on each file. $f store current file name
		./tester_histogram $f $NUM_OF_PIECES | grep results >> $HIST_OUT 
#		echo "./tester_histogram $f $NUM_OF_PIECES | grep results >> $HIST_OUT"
	done

fi
