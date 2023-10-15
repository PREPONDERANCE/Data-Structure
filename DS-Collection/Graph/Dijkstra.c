#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#define MAXSIZE 50

typedef struct graph{
	int v;
	bool AdM[MAXSIZE][MAXSIZE];
	int weights[MAXSIZE][MAXSIZE];
}graph;

graph* createGraph(int v){
	graph* g = (graph*)malloc(sizeof(graph));
	g->v = v;
	for(int i = 0; i != v; i++)
		for(int j = 0; j != v; j++){
			g->AdM[i][j] = false;
			g->weights[i][j] = INT_MAX;
		}
	return g;
}

void insert(graph* g, int i, int j, int weight){
	g->AdM[i][i] = true; g->AdM[j][j] = true;
	g->AdM[i][j] = true; g->AdM[j][i] = true;
	g->weights[i][j] = weight; g->weights[j][i] = weight;
}

int FindMin(graph* g, bool* visited, int v){
	int min = INT_MAX, j = g->v;
	for(int i = 0; i != g->v; i++){
		if( visited[i] ) continue;
		if( g->weights[i][i] < min ){
			j = i;
			min = g->weights[i][i];
		}
	}
	
	return j;
}

void DijkstraUtil(graph* g, bool* visited, int v){
	if( v == g->v ) return;
	visited[v] = true;
	
	for(int i = 0; i != g->v; i++)
		if( g->AdM[v][i] && !visited[i] )
			if( g->weights[v][i] + g->weights[v][v] < g->weights[i][i] )
				g->weights[i][i] = g->weights[v][i] + g->weights[v][v];
	DijkstraUtil(g, visited, FindMin(g, visited, v));
}

void Dijkstra(graph* g, int v){
	bool visited[g->v]; memset(visited, false, g->v);
	g->weights[v][v] = 0;
	DijkstraUtil(g, visited, v);
}

int main(int argc, char *argv[]) {
	graph* g = createGraph(5);
	insert(g, 0, 1, 5); insert(g, 0, 3, 3); insert(g, 0, 4, 11);
	insert(g, 1, 2, 8); insert(g, 1, 3, 10);
	insert(g, 2, 4, 2);
	insert(g, 3, 4, 1);
	
	Dijkstra(g, 2);
	
//	for(int i = 0; i != g->v; i++){
//		for(int j = 0; j != g->v; j++)
//			printf("%d ", g->AdM[i][j]);
//		putchar('\n');
//	}
	
	for(int i = 0; i != g->v; i++){
		for(int j = 0; j != g->v; j++)
			printf("%d ", g->weights[i][j]);
		putchar('\n');
	}
	
	return 0;
}