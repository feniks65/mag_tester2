#!/bin/python

import os
import sys
import shutil

pathToSamples = sys.argv[1]

if True == os.path.exists("../Hough/tester_hough"):
	shutil.copy("../Hist/tester", "./tester_histogram")

if True == os.path.exists("../Hough/tester"):
	shutil.copy("../Hough/tester", "tester_hough")

for i in os.listdir(pathToSamples):
	osCmd = "./tester_histogram " + pathToSamples + "/" + i + " " + numOfPieces + " > temp_f"
	out = os.system(osCmd)
	#print osCmd
	
	#f = open("tester_hist_output.txt", "a")
	lista = [line for line in open('temp_f') if 'results' in line]
	for lin in lista:
		print lin

	#print "linia====" + linia
	#f.write(linia)
	#f.close()
