#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

typedef struct Node{
	int dest;
	int weight;
	struct Node* next;
} Node;

typedef struct graph{
	int v;
	Node** array;
} graph;

graph* createGraph(int v){
	graph* temp = (graph*)malloc(sizeof(graph));
	temp->v = v;
	temp->array = (Node**)malloc(sizeof(Node*) * v);
	return temp;
}

Node* createNode(int dest, int weight){
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->dest = dest;
	temp->weight = weight;
	temp->next = NULL;
	return temp;
}

void insert(graph* g, int src, int dest, int weight){
	Node* newNode = createNode(dest, weight);
	
	if( !g->array[src] ){
		g->array[src] = newNode;
		return;
	}
	
	Node* head = g->array[src];
	newNode->next = head;
	g->array[src] = newNode;
}

void DFSUtil(graph* g, bool* visited, int v){
	Node* head = g->array[v];
	while( head ){
		if( !visited[head->dest] ){
			visited[head->dest] = true;
			printf("{%d : %d}\n", head->dest, head->weight);
			DFSUtil(g, visited, head->dest);
		}
		head = head->next;
	}
}

void DFS(graph* g, int v){
	bool visited[g->v]; memset(visited, false, g->v);
	DFSUtil(g, visited, v);
}

void BFSUtil(graph* g, bool* visited, Node** queue, int v){
	int i = 0, j = -1;
	queue[++j] = g->array[v];
	visited[g->array[v]->dest] = true;
	printf("{%d : %d}\n", g->array[v]->dest, g->array[v]->weight);
	
	while( j >= i ){
		Node* head = g->array[queue[i++]->dest];
		// We're accessing the first node in the array indexed at queue[i++]->dest
		while( head ){
			if( !visited[head->dest] ){
				visited[head->dest] = true;
				printf("{%d : %d}\n", head->dest, head->weight);
				queue[++j] = head;
			}
			head = head->next;
		}
		
	}
}

void BFS(graph* g, int v){
	Node* queue[g->v];
	for(int i = 0; i != g->v; i++) queue[i] = NULL;
	bool visited[g->v]; memset(visited, false, g->v);
	BFSUtil(g, visited, queue, v);
}

void findMin(graph*g, int* dist, bool* visited, int* weight, int* index){
	int min = INT_MAX, idx;
	
	for(int i = 0; i != g->v; i++)
		if( !visited[i] )
			if( dist[i] < min ){
				min = dist[i];
				idx = i;
			}
	
	*weight = min;
	*index =  idx;
}

void DijkstraUtil(graph* g, bool* visited, int v, int* dist){
	int path[g->v];
	for(int i = 0; i != g->v; i++) path[i] = 0;
	
	dist[v] = 0;
	path[v] = -1;
	
	for(int i = 0; i != g->v; i++){
		int node, weight;
		findMin(g, dist, visited, &weight, &node);
		visited[node] = true;
		Node* head = g->array[node];
		
		while( head ){
			if( weight + head->weight < dist[head->dest] ){
				dist[head->dest] = weight + head->weight;
				path[head->dest] = node;
			}
			head = head->next;
		}
	}
	
	for(int i = 0; i != g->v; i++) printf("%d ", dist[i]); putchar('\n');
	for(int i = 0; i != g->v; i++) printf("%d ", path[i]);
}

void Dijkstra(graph* g, int v){
	bool visited[g->v]; memset(visited, false, g->v);
	int weight[g->v];
	for(int i = 0; i != g->v; i++) weight[i] = INT_MAX;
	DijkstraUtil(g, visited, v, weight);
}

int main(int argc, char *argv[]) {
	graph* g = createGraph(9);
	
//	insert(g, 0, 1, 1); insert(g, 0, 3, 2); insert(g, 0, 2, 1);
//	insert(g, 1, 0, 1); insert(g, 1, 3, 3);
//	insert(g, 2, 0, 1); insert(g, 2, 3, 4);
//	insert(g, 3, 0, 2); insert(g, 3, 1, 3); insert(g, 3, 2, 4);
//	
//	DFS(g, 2);
//	BFS(g, 2);
//	
//	Dijkstra(g, 0);
	
	// Final Test Case
	insert(g, 0, 7, 8); insert(g, 0, 1, 4);
	insert(g, 1, 7, 11); insert(g, 1, 2, 8); insert(g, 1, 0, 4);
	insert(g, 2, 1, 8); insert(g, 2, 8, 2); insert(g, 2, 3, 7); insert(g, 2, 5, 4);
	insert(g, 3, 2, 7); insert(g, 3, 5, 14); insert(g, 3, 4, 9);
	insert(g, 4, 3, 9); insert(g, 4, 5, 10);
	insert(g, 5, 4, 10); insert(g, 5, 3, 14); insert(g, 5, 2, 4); insert(g, 5, 6, 2);
	insert(g, 6, 5, 2); insert(g, 6, 8, 6); insert(g, 6, 7, 1);
	insert(g, 7, 8, 7); insert(g, 7, 1, 11); insert(g, 7, 0, 8); insert(g, 7, 6, 1);
	
//	DFS(g, 0);
//	BFS(g, 0);
	
	Dijkstra(g, 0);
}