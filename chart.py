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

def cutEdgeElements(input):
	output = list()
	average = (sum(input)/len(input))
	print "average=",average

	for value in input:
		if average > (2 * value) or average < (0.2 * value):
			pass
		else:
			output.append(value)

	return output

def getYsForIndexes(indexes, yy):
	output = list()

	for value in indexes:
		output.append(yy[value])

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

filteredYs = cutEdgeElements(yy)

pks = findpeaks(filteredYs)

pksY = getYsForIndexes(pks, filteredYs)

#filteredPksYs = cutEdgeElements(pksY)
#filteredPksXs = 

plt.plot(xx, yy)
plt.ylabel('Number of black pixels in each column')
plt.xlabel('Columns')

plt.plot(pks, pksY, 'ro')
plt.show()

print "Number of peaks found=", len(pks)
