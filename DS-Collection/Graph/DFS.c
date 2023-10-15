#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_SIZE 50

typedef struct grapht{
	int v;
	bool visited[MAX_SIZE];
	bool vertices[MAX_SIZE][MAX_SIZE];
} graph, *G;

G CreateGraph(int v){
	G newgraph = (G)malloc(sizeof(graph));
	newgraph->v = v;
	for(int i = 0; i != v; i++){
		newgraph->visited[i] = false;
		for(int j = 0; j != v; j++)
			newgraph->vertices[i][j] = false;
	}
	return newgraph;
}

void insert(G g, int i, int j){
	g->vertices[i][j] = true;
}


void DFSUtil(graph* g, bool* visited, int v){
	visited[v] = true;
	printf("%d ", v);
	
	for(int i = 0; i != g->v; i++){
		if( g->vertices[v][i] && !visited[i] ){
			visited[i] = true;
			DFSUtil(g, visited, i);
		}
	}
}

void DFS(graph* g, int v){
	bool visited[g->v];
	memset(visited, false, g->v);
	DFSUtil(g, visited, v);
}

int main(int argc, char *argv[]) {
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
	
	DFS(g, 5);
	
	return 0;

}