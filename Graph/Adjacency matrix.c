#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 50

typedef struct graph{
	int v;
	bool vertice[MAX_SIZE][MAX_SIZE];
}graph;

graph* CreateGraph(int v){
	graph* g = (graph*)malloc(sizeof(graph));
	g->v = v;
	for(int i = 0; i < v; i++)
		for(int j = 0; j < v; j++)
			g->vertice[i][j] = false;
	return g;
}

void insert(graph* g, int i, int j){
	g->vertice[i][j] = true;
}

int main(){
	int v = 8;
	graph *g = CreateGraph(v);
	
	insert(g, 0, 1); insert(g, 0, 2); insert(g, 0, 3);
	insert(g, 1, 0); insert(g, 1, 4); insert(g, 1, 5);
	insert(g, 2, 0); insert(g, 2, 6);
	insert(g, 3, 0); insert(g, 3, 7);
	insert(g, 4, 1); insert(g, 4, 7);
	insert(g, 5, 1); insert(g, 5, 7);
	insert(g, 6, 2); insert(g, 6, 7);
	insert(g, 7, 3); insert(g, 7, 4); insert(g, 7, 5); insert(g, 7, 6);
	
	return 0;
}

// Adjacent matrix is always used for dense graph.
// For a sparse graph, this method wastes too much memory