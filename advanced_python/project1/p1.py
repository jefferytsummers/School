'''
Author:      Ryan Florida
Assignment:  Project 1
Due Date:    6/8/2017
Description: Approximate pi using Monte Carlo methods.
'''
import math, random, sys

#Get desired number of darts from user.
numOfDarts = int(sys.argv[1])

#Here we will simulate throwing the desired number of darts at a circle. We
#will keep track of the number of darts that land in the circle, that is those
#darts with a distance less than or equal to one from the origin.
dartsInCircle = 0
for i in range(numOfDarts):
    #This uses the typical distance calculation sqrt(x^2 + y^2).
    if math.sqrt(random.random()**2 + random.random()**2) <= 1:
        dartsInCircle += 1

#This is our approximated value for pi.
estimate = 4*float(dartsInCircle)/numOfDarts

#Display results for the user.
print("\u03C0 estimate =", estimate)
