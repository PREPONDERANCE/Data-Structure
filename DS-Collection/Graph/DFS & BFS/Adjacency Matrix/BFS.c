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
	if( !visited[v] ){
		visited[v] = true;
		vertex[e++] = v;
	}
	
	for(int i = 0; i != g->v; i++)
		if( g->vertices[v][i] && !visited[i] ){
			visited[i] = true;
			vertex[e++] = i;
		}
	
	s++;
	BFSUtil(g, visited, vertex, vertex[s], s, e);
}

void BFS_recusion(graph* g, int v){
	bool visited[g->v];
	int vertex[g->v];
	BFSUtil(g, visited, vertex, v, 0, 0);
}


void BFS_iteration(graph* g, int v){
	bool visited[g->v];
	int vertex[g->v];
	int i = 0, j = -1;
	
	vertex[++j] = v;
	visited[v] = true;
	printf("%d ", v);
	
	while( j >= i  ){
		int curr_vertex = vertex[i++];
		for(int k = 0; k != g->v; k++)
			if( g->vertices[curr_vertex][k] && !visited[k] ){
				visited[k] = true;
				printf("%d ", k);
				vertex[++j] = k;
			}
	}
}

void DFSUtil(graph* g, bool* visited, int v){
	printf("%d ", v);
	visited[v] = true;
	
	for(int i = 0; i != g->v; i++)
		if( g->vertices[v][i] && !visited[i] )
			DFSUtil(g, visited, i);
}

void DFS_recursion(graph* g, int v){
	bool visited[g->v];
	DFSUtil(g, visited, v);
}

void DFS_iteration(graph* g, int v){
	bool visited[g->v]; int stack[g->v];
	for(int i = 0; i != g->v; i++) stack[i] = 0;
	
	stack[0] = v; int i = 1;
	
	while( i > 0 ){
		int node = stack[--i];
		if( !visited[node] ){
			printf("%d ", node);
			visited[node] = true;
			for(int j = 0; j != g->v; j++)
				if( g->vertices[node][j] && !visited[j] )
					stack[i++] = j;
			
		}
	}
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
	
	BFS_recusion(g, 2);
	putchar('\n');
	BFS_iteration(g, 2);
	putchar('\n');
//	DFS_recursion(g, 2);
	DFS_iteration(g, 2);
	
	return 0;

}