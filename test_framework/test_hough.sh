#!/bin/bash

if [ $# -lt 1 ]
then
	print "Please provide path to samples in the way: ./tester.sh /path/to/samples/*"
	return 0
fi

HIST_OUT = "tester_hough_output.txt"

if [ -e HIST_OUT ]
then
	rm HIST_OUT
fi

PATH_TO_SAMPLES = $1

cp ../Hough/tester ./tester_hough

if [ -e tester_histogram]
then

	for f in $PATH_TO_SAMPLES
	do
  		echo "Processing $f file..."
  		# take action on each file. $f store current file name
		./tester_hough $f | grep results >> HIST_OUT 
	done
	./tester_histogram $PATH_TO_SAMPLES

fi
