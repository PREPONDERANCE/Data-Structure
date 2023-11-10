#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Node{
	int dest, weight;
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
	newNode->next = g->array[src];
	g->array[src] = newNode;
	
	newNode = createNode(src, weight);
	newNode->next = g->array[dest];
	g->array[dest] = newNode;
}

typedef struct heapq{
	int v, dist;
	// v -- vertex number
} heapq;

typedef struct minHeap{
	int size, capacity;
	int* pos;
	// pos records index of node in the heap according to the index of node in graph
	// Since we're mutating the array (i.e. the minHeap), the index will change accordingly
	heapq** array;
} minHeap;

heapq* createHeapq(int v, int dist){
	heapq* node = (heapq*)malloc(sizeof(heapq));
	node->v = v;
	node->dist = dist;
	return node;
}

minHeap* createMinHeap(int capacity){
	minHeap* heap = (minHeap*)malloc(sizeof(minHeap));
	heap->size = 0;
	heap->capacity = capacity;
	heap->pos = (int*)malloc(sizeof(int) * capacity);
	heap->array = (heapq**)malloc(sizeof(heapq*) * capacity);
	return heap;
}

void swap_heapq(heapq** node1, heapq** node2){
	heapq* temp = *node1;
	*node1 = *node2;
	*node2 = temp;
}

void min_heapify(minHeap* heap, int i){
	int smallest = i;
	int left = 2*i+1, right = 2*i+2;
	
	if( left < heap->size && heap->array[left]->dist < heap->array[smallest]->dist )
		smallest = left;
	if( right < heap->size && heap->array[right]->dist < heap->array[smallest]->dist )
		smallest = right;
	
	if( smallest != i ){
		heapq* smallestNode = heap->array[smallest];
		heapq* idxNode = heap->array[i];
		
		heap->pos[smallestNode->v] = i;
		heap->pos[idxNode->v] = smallest;

		swap_heapq(&heap->array[smallest], &heap->array[i]);
		min_heapify(heap, smallest);
	}
}

void heappush(minHeap* heap, heapq* node){
	heap->array[heap->size++] = node;
	for(int i = heap->size / 2; i >= 0; i--)
		min_heapify(heap, i);
}

bool len(minHeap* heap){
	return heap->size == 0;
}

heapq* heappop(minHeap* heap){
	if( len(heap) ) return NULL;
	
	heapq* temp = heap->array[0];
	
	heapq* firstNode = heap->array[0];
	heapq* lastNode = heap->array[heap->size-1];
	
	heap->pos[firstNode->v] = heap->size-1;
	heap->pos[lastNode->v] = 0;
	
	swap_heapq(&heap->array[0], &heap->array[heap->size-1]);
	heap->size--;
	
	min_heapify(heap, 0);
	return temp;
}

bool in(minHeap* heap, int v){
	return heap->pos[v] < heap->size;
}

void Dijkstra(graph* g, int v){
	minHeap* heap = createMinHeap(g->v);
	int dist[g->v], path[g->v]; path[v] = -1;
	
	for(int i = 0; i != g->v; i++){
		if( i == v ) dist[i] = 0;
		else dist[i] = INT_MAX;
	
		heap->pos[i] = i;
		heappush(heap, createHeapq(i, dist[i]));
	}
	
	while( !len(heap) ){
		heapq* root = heappop(heap);
		Node* head = g->array[root->v];
		
		while( head ){
			if( in(heap, v) && root->dist + head->weight < dist[head->dest] ){
				dist[head->dest] = root->dist + head->weight;
				heap->array[heap->pos[head->dest]]->dist = dist[head->dest];
				path[head->dest] = root->v;
				for(int i = heap->size/2; i >= 0; i--) min_heapify(heap, i);
			}
			head = head->next;
		}
	}
	
	for(int i = 0; i != g->v; i++) printf("%d ", dist[i]); putchar('\n');
	for(int i = 0; i != g->v; i++) printf("%d ", path[i]); putchar('\n');
}

int main(int argc, char *argv[]) {
	graph* g = createGraph(9);
	
	insert(g, 0, 1, 4); insert(g, 0, 7, 8);
	insert(g, 1, 2, 8); insert(g, 1, 7, 11);
	insert(g, 2, 3, 7); insert(g, 2, 8, 2); insert(g, 2, 5, 4);
	insert(g, 3, 4, 9); insert(g, 3, 5, 14);
	insert(g, 4, 5, 10);
	insert(g, 5, 6, 2);
	insert(g, 6, 7, 1); insert(g, 6, 8, 6);
	insert(g, 7, 8, 7);
	
	Dijkstra(g, 0);
}