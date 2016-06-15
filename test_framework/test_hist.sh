#!/bin/bash

if [ $1 == "" ]
then
	print "Please provide path to samples in the way: ./tester.sh /path/to/samples/*"
	return 0
fi

HIST_OUT = "tester_hist_output.txt"

if [ -e HIST_OUT ]
then
	rm HIST_OUT
fi

PATH_TO_SAMPLES = $1

cp ../Hist/test ./tester_histogram

if [ -e tester_histogram]
then

	for f in $PATH_TO_SAMPLES
	do
  		echo "Processing $f file..."
  		# take action on each file. $f store current file name
		./tester_histogram $f >> HIST_OUT 
	done
	./tester_histogram $PATH_TO_SAMPLES

fi
