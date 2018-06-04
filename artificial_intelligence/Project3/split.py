#!/usr/bin/env python3.5
from random import randint
from sys import stdin, argv
#******************************************************************************
#To use (on command line): cat dataFile.txt | python3 split.py num
#Example: cat iris-data.txt | python3 split.py 10
#The above would yield a training data set of size 10 and a testing set of 140.
#******************************************************************************

#Enter number of lines you would like in your training data file.
num = int(argv[1])

lines = [line for line in stdin.readlines()]
#Randomly shuffle entries in lines list.
for x in range(len(lines)):
    r = randint(0, len(lines) - 1)
    lines[x], lines[r] = lines[r], lines[x]

#Open two files for writing.
out1 = open('train.txt', 'w')
out2 = open('test.txt', 'w')

#Read in first 'num' number of lines from lines list to the training file.
for i in range(num):
    out1.write(lines[i])
#Read in remaining number of lines to testing file.
for i in range(num, len(lines)):
    out2.write(lines[i])

#Close files we were writing to, because we are good boys.
out1.close()
out2.close()
