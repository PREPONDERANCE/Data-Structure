#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 50

typedef struct Node{
	int data;
	struct Node* next;
} Node;

typedef struct graph{
	int v;
	Node *vertices[MAX_SIZE];
} graph;

graph* CreateGraph(int v){
	graph* g = (graph*)malloc(sizeof(graph));
	g->v = v;
	return g;
}

Node* CreateNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void insert(graph* g, int vertice, int data){
	if( g->vertices[vertice] == NULL ){
		g->vertices[vertice] = CreateNode(data);
		return;
	}
	
	Node* newNode = CreateNode(data);
	newNode->next = g->vertices[vertice];
	g->vertices[vertice] = newNode;
}

int main(){
	int v = 8;
	graph* g = CreateGraph(v);
	
	insert(g, 0, 3); insert(g, 0, 2); insert(g, 0, 1);
	insert(g, 1, 0); insert(g, 1, 4); insert(g, 1, 5);
	insert(g, 2, 0); insert(g, 2, 6);
	insert(g, 3, 0); insert(g, 3, 7);
	insert(g, 4, 1); insert(g, 4, 7);
	insert(g, 5, 1); insert(g, 5, 7);
	insert(g, 6, 2); insert(g, 6, 7);
	insert(g, 7, 3); insert(g, 7, 4); insert(g, 7, 5); insert(g, 7, 6);
	
	return 0;
}

// Graph representation of adjacency list using linked list