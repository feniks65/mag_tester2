#!/usr/bin/python

import csv
import sys
import matplotlib.pyplot as plt
import numpy
import peakutils

from scipy.signal import find_peaks_cwt

def findpeaks(yy):
	peaks = list()

	#cb = numpy.array([-0.010223, ... ])
	#peaks = find_peaks_cwt(cb, np.arange(1, 550))

	cb = numpy.array(yy)
	print cb.shape
	#print numpy.arange(0, 3500).shape
	print cb
	peaks = peakutils.indexes(cb, thres=0.00005 * max(cb), min_dist=100)
	#peaks = find_peaks_cwt(cb, numpy.arange(1, 100))

	return peaks

def sortElementAndCutEdges(input):
	average = (sum(input)/len(input))

	for value in input:
		if average > (2 * value) or average < (0.2 * value):
			while True:
				try:
					input.remove(value)
				except:
					break
	return input

def getXsForForYs(input):
	output = list()
	counter = 1
	for value in input:
		output.append(counter)
		counter++
	return output

#main code

xx = list()
yy = list()

with open(sys.argv[1], 'rb') as f:
    reader = csv.reader(f)
    for row in reader:
        #print row
        splitted = (str(row[0])).split(';')
        xx.append(int(splitted[0]))
        yy.append(int(splitted[1]))

#plt.plot([xx], [yy])

pks = findpeaks(yy)

pksy = list()

for value in pks:
    pksy.append(yy[value])
       
print findpeaks(yy)

plt.plot(xx, yy)
plt.ylabel('Number of black pixels in each column')
plt.xlabel('Columns')
plt.plot(xx, yy)

plt.plot(pks, pksy, 'ro')
plt.show()

print "Number of peaks found=", len(pks)