#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_SIZE 50

typedef struct grapht{
	int v;
	bool vertices[MAX_SIZE][MAX_SIZE];
} graph, *G;

G CreateGraph(int v){
	G newgraph = (G)malloc(sizeof(graph));
	newgraph->v = v;
	for(int i = 0; i != v; i++)
		for(int j = 0; j != v; j++)
			newgraph->vertices[i][j] = false;
	
	return newgraph;
}

void insert(G g, int i, int j){
	g->vertices[i][j] = true;
}

void BFSUtil(graph* g, bool* visited, int* vertex, int v, int s, int e){
	if( s == g->v ) return;
	
	printf("%d ", v);
	if( visited[v] == false ){
		vertex[e++] = v;
		visited[v] = true;
	}
	
	for(int i = 0; i != g->v; i++)
		if( g->vertices[v][i] && !visited[i] ){
			visited[i] = true;
			vertex[e++] = i;
		}
	s++;
	BFSUtil(g, visited, vertex, vertex[s], s, e);
}

void BFS(graph* g, int v){
	bool visited[g->v];
	int vertex[g->v];
	BFSUtil(g, visited, vertex, v, 0, 0);
}



int main(int argc, char *argv[]) {	
	graph* g = CreateGraph(4);
	
	insert(g, 0, 1);
//	insert(g, 1, 0);
	insert(g, 0, 2);
	insert(g, 1, 2);
	insert(g, 2, 0);
	insert(g, 2, 3);
	insert(g, 3, 3);
//	insert(g, 2, 1);
//	insert(g, 3, 2);
	
	BFS(g, 2);
	
	return 0;

}