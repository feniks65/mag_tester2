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
	peaks = peakutils.indexes(cb, thres=0.00005 * max(cb), min_dist=sys.argv[2])
	#peaks = find_peaks_cwt(cb, numpy.arange(1, 100))

	print "PEAKS=",peaks

	return peaks

def cutEdgeElements(average, peaksIndexes, yy):
	counter = 0

	print "PEAKSlen=",len(peaksIndexes)


	for value in peaksIndexes:
		print "counter=",counter," value=",value," average=",average," yy[value]=",yy[value]

		if yy[value] > (1.9 * average) or yy[value] < (0.2 * average):
			peaksIndexes = numpy.delete(peaksIndexes, counter)
			print "DELETED"
		else:
			counter = counter + 1
	return peaksIndexes

"""
def getYsForIndexes(indexes, yy):
	output = list()

	for value in indexes:
		output.append(yy[value])

	return output
"""


def averageOfPeaks(peaksIndexes, yy):
	average = 0
	if 0 != len(peaksIndexes):
		for index in peaksIndexes:
			average += yy[index]

		average = average / len(peaksIndexes)
	return average

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

#filteredYs = cutEdgeElements(yy)

pks = findpeaks(yy)

peak_average = averageOfPeaks(pks, yy)
#
pks = cutEdgeElements(peak_average, pks, yy)

#pksY = getYsForIndexes(pks, filteredYs)

#filteredPksYs = cutEdgeElements(pksY)
#filteredPksXs = 

"""
plt.plot(xx, yy)
plt.ylabel('Number of black pixels in each column')
plt.xlabel('Columns')
"""


print "PKS=",pks
print "Liczba pksow=",len(pks)

"""
#drawing dots
for index in pks:
	plt.plot(index, yy[index], 'ro')


plt.show()
"""


print "Number of peaks found=", len(pks)

f = open("foundPeaks.txt", "a")

stringToFile = str(len(pks))+"\n"

f.write(stringToFile)      # str() converts to string
f.close()
