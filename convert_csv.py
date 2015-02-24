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
			print val
			#data[len(data) - 1].append(val)

def main(argv):
	for ar in range(1, len(argv)):
		data.append([])
		with open(argv[ar], "rb") as f_obj:
			parse_csv(f_obj)

if __name__ == "__main__":
	main(sys.argv)
