
import numpy as np
import scipy.linalg as la
import matplotlib.pyplot as plt



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
	s1 = np.absolute(np.random.normal(2, 1, npoints/2))
	s2 = 1.5 * np.absolute(np.random.normal(4, 1, npoints/2))
	comb = np.concatenate((s1, s2), axis=0)
	h = np.histogram(comb, bins=N, range=(start, end), normed = False)
	return h[0]


s = 3;
start = 0
end = 1
N = 100
q = np.random.random((s * (s-1), 1))

#cdf = getCdf(start, end, N, q)	
#plt.plot(np.linspace(start, end, N, endpoint=False), cdf)
#plt.ylabel('the cdf')
#plt.show()

plt.plot(np.cumsum(get_distro(start, end, N, 10000)))
plt.show()
