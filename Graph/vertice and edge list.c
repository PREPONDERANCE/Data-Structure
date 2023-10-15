// Graph implementation version 1

#include <stdio.h>

#define MAX_SIZE 100

typedef struct edge{
	int startvertice;
	int endvertice;
	int weight;
} edge;

int main(){
	int i;
	edge graph[MAX_SIZE];
	char vertice[MAX_SIZE];
	
	for(i = 0; i < 8; i++)
		vertice[i] = i + 'A';
	
	graph[0].startvertice = vertice[0];
	graph[0].endvertice = vertice[1];
	graph[0].weight = 5;
	
	graph[1].startvertice = vertice[0];
	graph[1].endvertice = vertice[2];
	graph[1].weight = 7;
	
	graph[2].startvertice = vertice[0];
	graph[2].endvertice = vertice[3];
	graph[2].weight = 3;
	
	graph[3].startvertice = vertice[1];
	graph[3].endvertice = vertice[5];
	graph[3].weight = 10;
	
	graph[4].startvertice = vertice[1];
	graph[4].endvertice = vertice[4];
	graph[4].weight = 2;
	
	graph[5].startvertice = vertice[2];
	graph[5].endvertice = vertice[6];
	graph[5].weight = 1;
	
	graph[6].startvertice = vertice[3];
	graph[6].endvertice = vertice[7];
	graph[6].weight = 11;
	
	graph[7].startvertice = vertice[4];
	graph[7].endvertice = vertice[7];
	graph[7].weight = 9;
	
	graph[8].startvertice = vertice[5];
	graph[8].endvertice = vertice[7];
	graph[8].weight = 4;
	
	graph[9].startvertice = vertice[6];
	graph[9].endvertice = vertice[7];
	graph[9].weight = 6;
	
	return 0;
}
// This version of implementation is actually shallow as we simplify the name from the potential string variable to character variable, in which scenario, it's rather easy.


// Q1 : check if 2 given nodes are connected - O(|E|)
// Q2 : check how many nodes are connected to the given node - O(|E|)
// According to the property of graph, |E| = n(n-1)/2 for undirected graph, so the time complexity for these operations will be O(n^2), which is time-consuming
// We actually want a structure with time complexity of O(|V|) - O(n)