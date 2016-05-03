#!/usr/bin/python

import csv
import sys
import matplotlib.pyplot as plt
import numpy as np

from scipy.signal import find_peaks_cwt

def findpeaks(yy):
	peaks = list()
	cb = np.array(yy)
	peaks = find_peaks_cwt(cb, np.arrange(1,len(yy)))
	return peaks

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

plt.plot(xx, yy)
plt.ylabel('Number of black pixels in each column')
plt.xlabel('Columns')
plt.plot(xx, pks)
plt.show()