#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

typedef struct Queue{
	Node *front, *rear;
} Queue;

Node* createNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

Queue* createQueue(){
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->front = q->rear = NULL;
	return q;
}

void push(Queue* q, int data){
	Node* newNode = createNode(data);
	
	if( !q->front && !q->rear ){
		q->front = q->rear = newNode;
		return;
	}
	
	q->rear->next = newNode;
	q->rear = q->rear->next;
}

bool empty(Queue* q){
	return !q->front && !q->rear;
}

size_t size(Queue* q){
	return q->rear - q->front;
}

void pop(Queue* q){
	if( empty(q) ) return;
	
	Node* temp = q->front;
	q->front = q->front->next;
	free(temp);
	
	if( !q->front ) q->front = q->rear = NULL;
}

Node* front(Queue* q){
	if( !q->front ) return NULL;
	return q->front;
}

Node* back(Queue* q){
	if( !q->rear ) return NULL;
	return q->rear;
}

void print(Queue* q){
	Node *front = q->front;
	
	while( front ){
		printf("%d ", front->data);
		front = front->next;
	}
	
	putchar('\n');
}

int main(int argc, char *argv[]) {
	Queue* q = createQueue();
	
	push(q, 4);
//	push(q, 6);
//	push(q, 5);
//	push(q, 1);
//	push(q, 7);
//	push(q, 9);
//	push(q, 8);
	
//	pop(q);
//	pop(q);
	
	print(q);
	
	return 0;
}