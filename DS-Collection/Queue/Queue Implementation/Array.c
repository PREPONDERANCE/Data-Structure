#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLEN 10

typedef struct{
	int front, rear;
	int *data;
}Queue;

Queue* createQueue(){
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->data = (int*)malloc(sizeof(int) * MAXLEN);
	q->front = q->rear = -1;
	return q;
}

bool empty(Queue* q){
	return (q->front == -1 && q->rear == -1);
}

bool full(Queue* q){
	return (q->rear+1)%MAXLEN == q->front;
}

void push(Queue* q, int data){
	if( empty(q) ){
		q->front = q->rear = 0;
		q->data[q->front] = data;
		return;
	}
	if( full(q) ) return;
	q->data[(++q->rear)%MAXLEN] = data;
	q->rear %= MAXLEN;
}

void pop(Queue* q){
	if( empty(q) ) return;
	if( q->front == q->rear ){
		q->front = q->rear = -1;
		return;
	}
	q->front = (q->front + 1) % MAXLEN;
}

void print(Queue* q){
	for(int i = q->front; i != (q->rear > q->front ? q->rear+1:q->rear+MAXLEN+1); i++)
		printf("%d ", q->data[i%MAXLEN]);
	putchar('\n');
}

int main(int argc, char *argv[]) {
	Queue* q = createQueue();
	
	push(q, 5);
	push(q, 0);
	push(q, 3);
	push(q, 8);
	push(q, 7);
	push(q, 1);
	push(q, 2);
	push(q, 6);
	push(q, 4);
	push(q, 9);
	
	pop(q);
	pop(q);
	pop(q);
	pop(q);
	
	push(q, 5);
//	push(q, 4);
//	push(q, 4);
//	push(q, 4);
//	push(q, 4);
	
//	pop(q);
	
	print(q);
	
	return 0;
}