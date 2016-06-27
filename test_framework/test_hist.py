#!/bin/python

import os
import sys
import shutil

pathToSamples = sys.argv[1]
numOfPieces = sys.argv[2]
rangeWidth = sys.argv[3]

if True == os.path.exists("../Hist/tester"):
	shutil.copy("../Hist/tester", "./tester_histogram")

if True == os.path.exists("../Hist/chart.py"):
	shutil.copy("../Hist/chart.py", "./chart.py")


if True == os.path.exists("temp_f"):
	os.system("rm temp_f")

for i in os.listdir(pathToSamples):
	osCmd = "./tester_histogram " + pathToSamples + "/" + i + " " + numOfPieces + " " + rangeWidth +" > temp_f"
	out = os.system(osCmd)
	#print osCmd
	
	#f = open("tester_hist_output.txt", "a")
	lista = [line for line in open('temp_f') if 'results' in line]
	for lin in lista:
		print lin

	#print "linia====" + linia
	#f.write(linia)
	#f.close()
