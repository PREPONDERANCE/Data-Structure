// Binary heap
// MaxHeap & MinHeap -- cmp

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
	int* data;
	int* avail;
	int* limit;
} Array;

typedef struct{
	Array* arr;
	int size;
} Priority_Queue;

bool cmp(int a, int b){
	return a > b;
}

int max(int a, int b){
	return a > b ? a : b;
}

void copy(int* start, int* end, int* dst){
	while( start != end ) *dst++ = *start++;
}

Array* createArray(){
	Array* arr = (Array*)malloc(sizeof(Array));
	arr->data = arr->avail = arr->limit = NULL;
	return arr;
}

void grow(Array* a){
	size_t currLen = a->avail-a->data;
	size_t newLen = max(currLen*2, 1);
	int* new_data = (int*)malloc(sizeof(int) * newLen);
	
	copy(a->data, a->avail, new_data);
	free(a->data);
	
	a->data = new_data;
	a->avail = a->data + currLen;
	a->limit = a->data + newLen;
}

bool empty(Array* a){
	return a->data == a->avail;
}

void push(Array* a, int data){
	if( a->avail == a->limit ) grow(a);
	*a->avail++ = data;
}

void swap(Array* a, int i, int j){
	int temp = *(a->data+i);
	*(a->data+i) = *(a->data+j);
	*(a->data+j) = temp;
}

void pop(Array* a){
	if( empty(a) ) return;
	a->avail--;
}

Priority_Queue* createQueue(){
	Priority_Queue* pq = (Priority_Queue*)malloc(sizeof(Priority_Queue));
	pq->arr = createArray();
	pq->size = 0;
	return pq;
}

void max_heapiry(Priority_Queue* pq, int N, int i){
	int largest = i;
	int left = 2*i+1, right = 2*i+2;
	
	if( left < N && cmp(*(pq->arr->data+left), *(pq->arr->data+largest)) ) largest = left;
	if( right < N && cmp(*(pq->arr->data+right), *(pq->arr->data+largest)) ) largest = right;
	
	if( largest != i ){
		swap(pq->arr, i, largest);
		max_heapiry(pq, N, largest);
	}
}

void insert(Priority_Queue* pq, int data){
	push(pq->arr, data);
	pq->size++;
	
//	for(int i = 0; i != pq->size+1; i++) printf("%d ", *(pq->arr->data+i));
//	putchar('\n');
	
	for(int i = pq->size/2; i >= 0; i--)
		max_heapiry(pq, pq->size, i);
}

int extract(Priority_Queue* pq){
	if( empty(pq->arr) ) return -1;
	
	int temp = *(pq->arr->data);
	swap(pq->arr, 0, pq->size-1);
	pq->size--;
	
	max_heapiry(pq, pq->size, 0);
	
	return temp;
}

int main(int argc, char *argv[]) {
	Priority_Queue* pq = createQueue();
	insert(pq, 4);
	insert(pq, 5);
	insert(pq, 0);
	insert(pq, 1);
	insert(pq, 2);
	insert(pq, 6);
	insert(pq, 8);
	
	printf("%d\n", extract(pq));
	printf("%d\n", extract(pq));
	
	
//	for(int i = 0; i != pq->size; i++) printf("%d ", *(pq->arr->data+i));
	
	return 0;
}