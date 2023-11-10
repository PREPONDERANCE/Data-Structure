# A collection for all graph algorithms so far -- adjacency list
# With reliance on built-in containers

import numpy as np
import heapq
import queue

class graph:
	def __init__(self, v):
		self.v = v
		self.adj = {}
		
		for i in range(v):
			self.adj[i] = []
			
	def insert(self, src, dest, weight):
		self.adj[src].append([dest, weight])
		self.adj[dest].append([src, weight])
		
	def DFS(self, v):
		visited = [False] * self.v
		
		def DFSUtil(v):
			for dest, weight in self.adj[v]:
				if not visited[dest]:
					visited[dest] = True
					print(f"{v , dest , weight}")
					DFSUtil(dest)
		DFSUtil(v)
			
	def BFS(self, v):
		visited = [False] * self.v
		
		q = queue.Queue()
		q.put(self.adj[v][0])
		visited[self.adj[v][0][0]] = True
		print(f"{v, self.adj[v][0][0], self.adj[v][1][1]}")
		
		while q.qsize():
			node, weight = q.get()
			for n, w in self.adj[node]:
				if not visited[n]:
					q.put([n, w])
					visited[n] = True
					print(f"{node, n, w}")
					
					
	def Dijkstra(self, src):
		shortest = { i : 1000 for i in range(self.v) }
		shortest[src] = 0
		
		minHeap = [[0, src]]
		
		while minHeap:
			w1, n1 = heapq.heappop(minHeap)
			
			for n2, w2 in self.adj[n1]:
				if w2+w1 < shortest[n2]:
					shortest[n2] = w2+w1
					heapq.heappush(minHeap, [w2+w1, n2])
					
			return shortest
			
g = graph(4)

g.insert(0, 1, 1)
g.insert(0, 2, 3)
g.insert(0, 3, 2)
g.insert(1, 3, 1)
g.insert(2, 3, 4)

#g.DFS(0)
print(g.Dijkstra(0))
#g.BFS(0)


#import numpy as np
#
#class Heap:
#	def __init__(self):
#		self.size = 0
#		self.pos = []
#		self.array = []
#	
#	def swap(self, node1: int, node2: int):
#		self.array[node1], self.array[node2] = self.array[node2], self.array[node1]
#	
#	def min_heapify(self, i):
#		smallest = i
#		left, right = 2*i+1, 2*i+2
#		
#		if left < self.size and self.array[left][1] < self.array[smallest][1]:
#			smallest = left
#		if right < self.size and self.array[right][1] < self.array[smallest][1]:
#			smallest = right
#			
#		if smallest != i:
#			self.pos[self.array[smallest][0]] = i
#			self.pos[self.array[i][0]] = smallest
#			
#			self.swap(smallest, i)
#			self.min_heapify(smallest)
#		
#	def heappush(self, node):
#		self.array.append(node)
#		self.size += 1
#		for i in range(self.size // 2, -1, -1):
#			self.min_heapify(i)
#	
#	def heappop(self):
#		first = self.array[0]
#		last = self.array[self.size-1]
#		
#		self.pos[first[0]] = self.size-1
#		self.pos[last[0]] = 0
#		
#		self.size -= 1
#		self.swap(0, self.size)
#		self.min_heapify(0)
#		
#		return first
#	
#	def empty(self):
#		return self.size == 0
#	
#class graph:
#	
#	def __init__(self, v):
#		self.v = v
#		self.adj = {}
#		
#		for i in range(v):
#			self.adj[i] = []
#			
#	def insert(self, src, dest, weight):
#		self.adj[src].append([dest, weight])
#		self.adj[dest].append([src, weight])
#		
#	def Dijkstra(self, v):
#		heap = Heap()
#		dist = [np.inf] * self.v
#		
#		for i in range(self.v):
#			if i == v: dist[v] = 0
#			heap.pos.append(i)
#			heap.heappush([i, dist[i]])
#		
#		while not heap.empty():
#			n1, w1 = heap.heappop()
#			
#			for n2, w2 in self.adj[n1]:
#				if w1 + w2 < dist[n2]:
#					dist[n2] = w1+w2
#					heap.array[heap.pos[n2]][1] = dist[n2]
#		
#		return dist
#
#g = graph(9)
#
#g.insert(0, 1, 4)
#g.insert(0, 7, 8)
#g.insert(1, 2, 8)
#g.insert(1, 7, 11)
#g.insert(2, 3, 7)
#g.insert(2, 8, 2)
#g.insert(2, 5, 4)
#g.insert(3, 4, 9)
#g.insert(3, 5, 14)
#g.insert(4, 5, 10)
#g.insert(5, 6, 2)
#g.insert(6, 7, 1)
#g.insert(6, 8, 6)
#g.insert(7, 8, 7)
#
#print(g.Dijkstra(0))