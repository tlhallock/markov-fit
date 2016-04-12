
import numpy as np
import scipy.linalg as la
import matplotlib.pyplot as plt

#globalStart
#globalEnd
#globalN
#globalDistribution
#functionCount

globalStart = 0
globalEnd   = 10
globalN     = 100
globalDistribution = None
functionCount = 0

globalCost = 10



def getGenerator(n, q):
	k=0
	mat = np.zeros((n, n))
	for i in range(0, n):
		for j in range(0, n):
			if i != j:
				mat[i,j] = q[k]
				k = k + 1
	mat = mat - np.diag(np.sum(mat, axis=1))
	return mat[0:-1, 0:-1]

def getCdf(start, end, N, q):
	q = np.absolute(q)
	n = int((1 + np.sqrt(1 + 4 * q.size))/2)
	
	output = np.zeros((N, 1))
	
	left = np.zeros((1, n-1))
	left[0, 0] = 1
	
	right = np.ones((n-1, 1))
	
	generator = getGenerator(n, q)
	
	for index, t in enumerate(np.linspace(start, end, N, endpoint=False)):
		output[index] = 1 - np.dot(np.dot(left, la.expm(t * generator)),  right)
		
	return output

def get_distro(start, end, N, npoints):
	s1 = np.absolute(np.random.normal(2, .25, npoints/2))
	s2 = 1.5 * np.absolute(np.random.normal(4, .5, npoints/2))
	comb = np.concatenate((s1, s2), axis=0)
	h = np.histogram(comb, bins=N, range=(start, end), normed = False)
	return h[0]

def evaluateCost(x):
	global globalDistribution
	global globalStart
	global globalEnd
	global globalN
	global functionCount
	global globalCost
	
	if globalDistribution is None:
		nsample = 10000
		prob = get_distro(globalStart, globalEnd, globalN, 10000)
		globalDistribution = np.cumsum(prob) / float(nsample)
	output = np.transpose(getCdf(globalStart, globalEnd, globalN, x))
	
	n = la.norm(np.subtract(globalDistribution, output) / globalN)
	
	if n < globalCost:
		functionCount = functionCount + 1
		t = np.transpose(np.linspace(globalStart, globalEnd, globalN, endpoint=False))
		print t.size
		print output.size
		print globalDistribution.size
		
		print t
		print output[0]
		print globalDistribution
		
		
		plt.plot(t, globalDistribution, t, output[0])
		plt.savefig('cdf_' + str(functionCount).zfill(4) + '.png')
		#plt.show()
		globalCost = n
	
	print n
	
	return n

def getInitialQ(dim):
	return np.random.random((dim * (dim-1), 1))





if __name__ == "__main__":
	print 'called'

#s = 3;
#start = 0
#end = 1
#N = 100
#q = getInitialQ(s)

#cdf = getCdf(start, end, N, q)	
#plt.plot(np.linspace(start, end, N, endpoint=False), cdf)
#plt.ylabel('the cdf')
#plt.show()



#globalDistribution = get_distro(globalStart, globalEnd, N, 10000);

#t = np.linspace(start, end, N, endpoint=False);

#plt.plot(t, np.cumsum(globalDistribution), t, t**2)
#plt.savefig('myfig.png')
#plt.show()
