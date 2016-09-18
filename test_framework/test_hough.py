#!/bin/python

import os
import sys
import shutil

pathToSamples = sys.argv[1]
numOfPieces  = sys.argv[2]

if True == os.path.exists("../Hough/tester"):
	shutil.copy("../Hough/tester", "./tester_hough")


if True == os.path.exists("temp_f"):
	os.system("rm temp_f")

for i in os.listdir(pathToSamples):
	osCmd = "./tester_hough " + pathToSamples + "/" + i + " " + numOfPieces +" > temp_f"
	out = os.system(osCmd)
	#print osCmd
	
	#f = open("tester_hist_output.txt", "a")
	lista = [line for line in open('temp_f') if 'frequent' in line]
	for lin in lista:
		print i + " " + lin

	#print "linia====" + linia
	#f.write(linia)
	#f.close()
