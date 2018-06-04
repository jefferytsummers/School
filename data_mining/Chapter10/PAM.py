from numpy import sqrt, sum
from random import randint, sample
import matplotlib.pyplot as plt
from sys import maxsize

INF = maxsize
N   = 500

def main():
	k    = int(input("Enter number of clusters: (must be less than " + str(N)\
		+ ') '))

	data = [(randint(0, N), randint(0, N)) for _ in range(N)]

	Display(data)

	PAM(data, k)

#******************************************************************************
#1: Display data/clusters.
def Display(data, clustered = 0):
	if clustered:
		#The colors string, currently, gives us 7 colors to choose from and the
		#markers string, currently, gives us 25 different symbols to choose
		#from. This enables us to uniquely identify 175 different clusters. If
		#we happen to need more than this amount, then we can add more options
		#to the strings below.
		colors  = 'bgrcmyk'
		symbols = 'o,v^<>*+x.12348spPhHXdD|_'
		color   = 0
		symbol  = 0
		#radii   = GetRadii(data)
		#for (c, r) in zip(list(data.keys()), radii):
		#	plt.gcf().gca().add_artist(plt.Circle(c, r, color =\
		#		colors[color%len(colors)], alpha = 0.5))
		#	color += 1
		#color   = 0
		#symbol  = 0
		for key in data:
			for (x, y) in data[key]:
				plt.scatter(x, y, c = colors[color%len(colors)],\
					marker = symbols[symbol%len(symbols)])
			color += 1
			if color%len(colors) == 0:
				symbol += 1

	else:
		for (x, y) in data:
			plt.scatter(x,y)
	
	plt.show()

#******************************************************************************
#2: PAM algorithm
def PAM(data, k):
	#Inditialize medoids and clusters.
	medoids = [data[object] for object in sample(range(N), k)]
	clusters = {}
	for o in medoids:
		clusters[o] = []
	Cluster(data, medoids, clusters)

    #Compute cost associated with swapping a non-medoid object with the medoid
    #of its cluster. If the cost if sufficiently low (< 0), then swap the
    #current medoid with the non-medoid.
	cost = {}
	for o in clusters:
		o_random = clusters[o][randint(0, len(clusters[o])-1)]
		cost[o_random] = ComputeCost(o, o_random, clusters[o])
		
	for (o, o_random) in zip(clusters.keys(), cost.keys()):
		if cost[o_random] < 0:
			clusters[o_random] = clusters.pop(o)

	#While medoids are being swapped, repeat the process above.
	change = True
	while(change):
		medoids  = [center for center in clusters.keys()]
		clusters = {}
		for o in medoids:
			clusters[o] = []
		Cluster(data, medoids, clusters)

		cost = {}
		for o in clusters:
			o_random = clusters[o][randint(0, len(clusters[o])-1)]
			cost[o_random] = ComputeCost(o, o_random, clusters[o])

		for (o, o_random) in zip(clusters.keys(), cost.keys()):
			if cost[o_random] < 0:
				clusters[o_random] = clusters.pop(o)

		if medoids == list(clusters.keys()):
			change = False

	Display(clusters, 1)
		
#******************************************************************************
#1.1: Return radii if you would like to see the clusters expressed as circles.
def GetRadii(data):
	max_radii = []

	for key in data:
		M = -INF
		for point in data[key]:
			dist = Distance(key, point)
			if dist > M:
				M = dist
		max_radii.append(M)

	return max_radii

#******************************************************************************
#2.1: Cluster input data.
def Cluster(data, medoids, clusters):
	for point in data:
		m_dist       = INF
		cluster_data = ()
		for o in medoids:
			check_dist = Distance(point, o)
			if check_dist < m_dist:
				m_dist       = check_dist
				cluster_data = o
		clusters[cluster_data].append(point)

#******************************************************************************
#2.2: Compute the cost of replacing medoid object with non-medoid object.
def ComputeCost(o, o_random, cluster):
	error_o        = 0
	error_o_random = 0
	for object in cluster:
		error_o        += Distance(o, object)
		error_o_random += Distance(o_random, object)

	return error_o_random - error_o

#******************************************************************************
#2.1.1: Euclidean distance. Depending on type of data, this is the function to
#       edit in order to define similarity between two data objects.
def Distance(vec1, vec2):
	new_vec = []
	for i in range(len(vec1)):
		new_vec.append((vec1[i] - vec2[i])**2)

	return sqrt(sum(new_vec))


#Call Main.
main()