#!/usr/bin/python
import re
import sys
import fileinput
import numpy
import csv

data = []

def parse_csv(file_obj):
	reader = csv.reader(file_obj, delimiter=',')
	for row in reader:
		data.append([])
		for val in row:
			data[len(data) - 1].append(val)

def main(argv):
	with open(argv[1], "rb") as f_obj:
		parse_csv(f_obj)

	Bins = [0, .001, .0025, .005, .01, .05, .1]
	for row in data:
		binVals, bins = numpy.histogram([float(x) for x in row[1:]], Bins)

		print row[0]
		for b in bins:
			print b, "\t",

		cum_sum = 0
		print ""
		print "\t", 
		for i in binVals:
			cum_sum += i
			frac = float(cum_sum) / binVals.sum()
			print("%.3f" % frac), "\t", 
			
		print ""

if __name__ == "__main__":
	main(sys.argv)
