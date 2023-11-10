import numpy as np

class graph:
	def __init__(self, v):
		self.v = v
		self.matrix = [[np.inf] * v for i in range(v)]
		
		for i in range(v):
			self.matrix[i][i] = 0
			
		self.shortest = []
	
	def insert(self, s, e, w):
		self.matrix[s][e] = w
		
	def __str__(self):
		for i in range(self.v):
			for j in range(self.v):
				if self.matrix[i][j] == np.inf:
					print("INF", end = ' ')
				else: print(self.matrix[i][j], end = ' ')
				if j == self.v-1: print()
		
		return ''

	def FolydWarshall(self):
		dist = list(map(lambda i: list(map(lambda j: j, i)), self.matrix))
		"""
		dist holds exactly the same value as self.matrix
		list in the outer bracket is used to cast the result into a list
		The first map after list takes in two parameters: self.matrix and the lambda function:
			return the entire line every time we iterate through self.matrix
				The second lambda function is used to record the value at each column in the corresponding line
		"""
		
		for i in range(self.v):
			for j in range(self.v):
				for k in range(self.v):
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
		
		self.shortest = dist
		
		return self.shortest
	
g = graph(4)
g.insert(0, 1, 5)
g.insert(0, 3, 10)
g.insert(1, 2, 3)
g.insert(2, 3, 1)

print(g)

shortest = g.FolydWarshall()
print(shortest)