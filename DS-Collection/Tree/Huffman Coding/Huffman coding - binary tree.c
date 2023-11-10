#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition of heap node and heap data structure
typedef struct heapq{
	char data;
	int freq;
	struct heapq *left, *right;
} heapq;

typedef struct{
	int size;
	int capacity;
	heapq** array;
} minHeap;
// End of definition

// Utility for creating heap node and min-heap
heapq* createNode(char data, int freq){
	heapq* temp = (heapq*)malloc(sizeof(heapq));
	temp->data = data;
	temp->freq = freq;
	temp->left = temp->right = NULL;
	return temp;
}

minHeap* createHeap(int capacity){
	minHeap* heap = (minHeap*)malloc(sizeof(minHeap));
	heap->size = 0;
	heap->capacity = capacity;
	heap->array = (heapq**)malloc(sizeof(heapq)*capacity);
	return heap;
}
// End of utility

// Maintaining min-heap data structure
void swap_heapq(heapq** node1, heapq** node2){
	heapq* temp = *node1;
	*node1 = *node2;
	*node2 = temp;
}

// Remember: if we want to swap the value at two different places, we're going to need the address of these two variables.

void min_heapify(minHeap* heap, int idx){
	int smallest = idx;
	int left = 2*idx+1, right = 2*idx+2;
	
	if( left < heap->size && heap->array[left]->freq < heap->array[smallest]->freq )
		smallest = left;
	if( right < heap->size && heap->array[right]->freq < heap->array[smallest]->freq )
		smallest = right;
	
	if( smallest != idx ){
		swap_heapq(&heap->array[smallest], &heap->array[idx]);
		min_heapify(heap, smallest);
	}
}

// min-heap operations
void insert(minHeap* heap, heapq* node){
	heap->array[heap->size++] = node;
	for(int i = heap->size/2; i >= 0; i--)
		min_heapify(heap, i);
}

heapq* extract(minHeap* heap){
	heapq* temp = heap->array[0];
	heap->size--;
	
	swap_heapq(&heap->array[0], &heap->array[heap->size]);
	min_heapify(heap, 0);
	return temp;
}

// Creating huffman tree
minHeap* createTree(char* data, int* freq, int size){
	minHeap* heap = createHeap(size);
	for(int i = 0; i != size; i++)
		insert(heap, createNode(data[i], freq[i]));

	return heap;
}

heapq* buildHuffman(char* data, int* freq, int size){
	minHeap* heap = createTree(data, freq, size);
	heapq *left, *right, *top;
	
	while( heap->size > 1 ){
		left = extract(heap);
		right = extract(heap);
		
		top = createNode('#', left->freq+right->freq);
		top->left = left;
		top->right = right;
		
		insert(heap, top);
	}
	
	return extract(heap);
}

// Encode in huffman
void printArray(int* arr, int N){
	for(int i = 0; i != N; i++) printf("%d", arr[i]);
	putchar('\n');
}

void encodeUtil(heapq* root, int* path, int len){
	if( !root->left && !root->right ){
		printf("%c :", root->data);
		printArray(path, len);
		return;
	}
	path[len++] = 0;
	encodeUtil(root->left, path, len);
	len--;
	path[len++] = 1;
	encodeUtil(root->right, path, len);
}

// Recall the printPath function where we want recursion to restore the value of len
// But in this case, it's different because we're not recording the data at each root
// Instead, we're recording value at each edge based on the left and right subtree

void encodeHuffman(char* data, int* freq, int size){
	heapq* root = buildHuffman(data, freq, size);
	int path[size];
	encodeUtil(root, path, 0);
}

int main(int argc, char *argv[]) {
	char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
	int freq[] = {5, 9, 12, 13, 16, 45};
	
	int size = sizeof(freq)/sizeof(freq[0]);
	encodeHuffman(data, freq, size);
	
	return 0;
}