#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

typedef struct heapq{
	int weight;
	int parent, left, right;
} heapq;

typedef struct minHeap{
	int size;
	heapq* array;
} minHeap;

minHeap* createHeap(int size){
	minHeap* heap = (minHeap*)malloc(sizeof(minHeap));
	heap->size = 2*size-1;
	heap->array = (heapq*)malloc(sizeof(heapq) * heap->size);
	return heap;
}

void selectMin(minHeap* heap, int n, int* s1, int* s2){
	int min1 = INT_MAX, min2 = INT_MAX;
	int pos1 = 0, pos2 = 0;
	
	for(int i = 0; i != n; i++)
		if( !heap->array[i].parent ){
			if( heap->array[i].weight <= min1 ){
				min2 = min1;
				pos2 = pos1;
				min1 = heap->array[i].weight;
				pos1 = i;
			}else if( heap->array[i].weight <= min2 ){
				min2 = heap->array[i].weight;
				pos2 = i;
			}
		}
	
	*s1 = pos1;
	*s2 = pos2;
}

minHeap* HuffmanTree(char* data, int* freq, int size){
	minHeap* heap = createHeap(size);
	int total = 2*size-1;
	
	for(int i = 0; i != total; i++){
		heap->array[i].parent = heap->array[i].left = heap->array[i].right = 0;
		if( i <= size ) heap->array[i].weight = freq[i];
		else heap->array[i].weight = 0;
	}
	
	for(int i = size; i != total; i++){
		int s1, s2;
		selectMin(heap, i, &s1, &s2);
		heap->array[i].weight = heap->array[s1].weight + heap->array[s2].weight;
		heap->array[i].left = s1;
		heap->array[i].right = s2;
		heap->array[s1].parent = heap->array[s2].parent = i;
	}
	
	return heap;
}

void HuffmanCode(char* data, int* freq, int size, char** encode){
	minHeap* heap = HuffmanTree(data, freq, size);
	
	for(int i = 0; i != size; i++){
		char code[size+1]; code[size] = '\0';
		int parent = heap->array[i].parent, child = i;
		int count = size-1;
		
		while( parent ){
			if( child == heap->array[parent].left ) code[count--] = '0';
			else code[count--] = '1';
			child = parent;
			parent = heap->array[parent].parent;
		}
		
		encode[i] = strdup(&code[count+1]);
	}
}

int main(){
	char data[] = {'a', 'b', 'c', 'd', 'e','f'};
	int freq[] = {5, 9, 12, 13, 16, 45};

	int size = sizeof(freq)/sizeof(freq[0]);
	char* encode[size];
	
	HuffmanCode(data, freq, size, encode);
	for(int i = 0; i != size; i++)
		printf("%s\n", encode[i]);
	
	return 0;
}