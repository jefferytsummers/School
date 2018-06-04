from   math              import sqrt
import matplotlib.pyplot as     plt
from   sys               import maxsize
from   numpy             import sum
from   random            import randint, sample

#Constant that represents very large distance.
INF = maxsize

#0: Main.
def main():
	#If default is set to 1 (true), then the default points - which were given
	#in the question - will be used with the indicated centroids. Otherwise, a
	#random data set will be generated and the user will select their own
	#desired number of clusters.
	default  = int(input('Use default values: (0 or 1) '))
	points, clusters = GeneratePoints(default)

	#Display the data set with centroids highlighted.
	Display(clusters, points)

	#At this step is when we begin calculating the clusters and new centroids.
	#The loop predicate makes sure the centroids are constantly changing. Once
	#the centroids cease to change value, we know that we are done.
	Cluster(clusters, points)
	change = True
	count  = 0 #Sometimes the centroid values switch between two values, so the
	#count variable will cease computation after 50 centroid recalculations.
	while (change):
		#Here we update the temporary centroids to test against the predicate.
		centroids = list(clusters.keys())
		#Here we update the centroids according to their new clusters.
		CalculateCentroids(clusters)
		if centroids == list(clusters.keys()) or count == 50:
			change = False
		#Here we form the new clusters.
		Cluster(clusters, points)
		count += 1

	#Display completed clusters.
	Display(clusters)

#******************************************************************************
#1: Generate random data to cluster or use default data set.
def GeneratePoints(default = 1):
	#Dictionary to store cluster centroids (keys) and their associated clusters
	#(values).
	clusters = {}
	if default:
		points = [(2,10), (2,5), (8,4), (5,8), (7,5), (6,4), (1,2), (4,9)]
		for i in range(0, 7, 3):
			clusters[points[i]] = []
	else:
		n      = int(input('How many points would you like? '))
		k      = int(input('How many clusters would you like? '))
		#Generate n random points.
		points = [(randint(0, n), randint(0, n)) for _ in range(n)]
		#Choose k distinct values between 0 and n as cluster centers.
		s      = sample(range(n), k)
		for p in s:
			clusters[points[p]] = []

	return (points, clusters)


#******************************************************************************
#2: Display graph of clusters. If points array is also passed, then plot the
#   centroids.
def Display(clusters, points = 0):
	if points:
		#First, as per request of the question, we plot the original centroids.
		num = 1
		for (x,y) in points:
			if (x, y) in clusters:
				plt.scatter(x,y)
				num += 1
			else:
				plt.scatter(x,y, color='black')
		plt.title('Initial Centroids')

	else:
		#Since we are using a Euclidean distance formula, we know the resultant
		#clusters will be circular/spherical. Hence, we calculate the radii of
		#each cluster at this point in order to aid visualization of the
		#clusters.
		radii = GetRadii(clusters)

		symbols = 'o,v^<>*+x.12348spPhHXdD|_'
		colors  = 'bgrcmyk'
		color   = 0
		for (c, r) in zip(list(clusters.keys()), radii):
			plt.gcf().gca().add_artist(plt.Circle(c, r, color =\
				colors[color%len(colors)], alpha = 0.5))
			color += 1

		#Here we are just plotting each point with a specific color which
		#represents its cluster affiliation.
		color  = 0
		symbol = 0
		for centroid in clusters:
			for (x, y) in clusters[centroid]:
				plt.scatter(x, y, c = colors[color%len(colors)], marker =\
				symbols[symbol%len(symbols)])
			color += 1
			if color%len(colors) == 0:
				symbol += 1

		plt.title('Final Clusters')
	plt.xlim(-5,15)
	plt.ylim(-5,15)
	plt.show()


#******************************************************************************
#3: Assigns points to the cluster that they are closest to.
def Cluster(clusters, points):
	#Empty each cluster.
	for centroid in clusters:
		clusters[centroid] = []

	#Reform each cluster based on distance from centroid.
	for point in points:
		m_dist       = INF
		cluster_data = ()
		for c in clusters:
			check_dist = Dist(point, c)
			if check_dist < m_dist:
				m_dist       = check_dist
				cluster_data = c
		clusters[cluster_data].append(point)


#******************************************************************************
#4: Calculate new centroid values by taking the average of all points within
#the clusters.
def CalculateCentroids(clusters):
	#List to hold new centroid values.
	centroids = []
	#Calculate new centroids based on average of points in each cluster.
	for centroid in clusters:
		newX = newY = 0
		size = len(list(clusters[centroid]))
		for (x,y) in clusters[centroid]:
			newX += x
			newY += y
		if size != 0:
			newX /= size
			newY /= size
		centroids.append((newX, newY))

	#Clear old centroids.
	clusters.clear()
	#Append new centroids.
	for newCentroid in centroids:
		clusters[newCentroid] = []


#******************************************************************************
#2.1: Calculate radii of the clusters. Calculation is based on the maximum
#distance between the centroid and a point in the cluster.
def GetRadii(data):
	#List to hold the radius of each cluster.
	max_radii = []

	#Find distance from centroid to furthest point in cluster.
	for key in data:
		M = -INF
		for point in data[key]:
			dist = Dist(key, point)
			if dist > M:
				M = dist
		max_radii.append(M)

	return max_radii

#******************************************************************************
#3.1: Euclidean distance formula / Clustering constraint.
def Dist(vec1, vec2):
	#List to hold the square of the differences between respective vector
	#components.
	sqOfDif = []
	for (c1, c2) in zip(vec1, vec2):
		sqOfDif.append((c1 - c2)**2)

	#Return square root of the sum of squares (magnitude of difference vector).
	return sqrt(sum(sqOfDif))

#Call main.
main()