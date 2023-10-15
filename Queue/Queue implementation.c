// Use cases for queue
// In computer construction, we have the concepts of program, job, process
// When a job enters cpu, it becomes a process. And with multiple processes racked up together, CPU handles them using queue data structure ( to be specific, the CPU allocates certain time slot for each process, which if not executed completely will be reset in queue for further computing ).

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

typedef struct{
	Node *front, *rear;
	int count;
} Queue;

Queue* CreateQueue();
Node* CreateNode(int);
Node* top(Queue*);
void push(Queue*, int);
void pop(Queue*);
void print(Queue*);
void clear(Queue*);
bool empty(Queue*);
int size(Queue*);

int main(){
	Queue *q = CreateQueue();
	push(q, 8);
	push(q, 5);
	push(q, 6);
	push(q, 4);
	push(q, 9);
	print(q);
	
	pop(q);
	pop(q);
	print(q);
	clear(q);
	
	printf("size of current queue is %d\n", size(q));
	
	return 0;
}

Queue* CreateQueue(void){
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->count = 0;
	q->front = q->rear = NULL;
	return q;
}

Node* CreateNode(int data){
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->next = NULL;
	return temp;
}

void push(Queue* q, int data){
	Node* newNode = CreateNode(data);
	
	if( q->rear == NULL ){
		q->front = q->rear = newNode;
		q->count++;
		return;
	}
	
	q->rear->next = newNode;
	q->rear = newNode;
	q->count++;
}

void pop(Queue* q){
	if( q->count == 0 )
		return;
	if( q->front == q->rear ){
		q->front = q->rear = NULL;
		return; 
	}
	
	Node* temp = q->front;
	q->front = q->front->next;
	free(temp);
	q->count--;
}

bool empty(Queue* q){
	return (q->count > 0) ? false : true;
}

int size(Queue* q){
	return q->count;
}

Node* top(Queue* q){
	return q->front;
}

void print(Queue *q){
	Node* temp = q->front;
	
	if( q->front ){
		printf("%d ", q->front->data);
		q->front = q->front->next;
		print(q);
	}else
		putchar('\n');
	
	q->front = temp;
}

void clear(Queue *q){
	if( q->front ){
		Node* temp = q->front;
		q->front = q->front->next;
		free(temp);
		q->count--;
		clear(q);
	}
}




//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//
//#define MAXLEN 100
//
//typedef struct {
//	int front;
//	int rear;
//	int count;
//} queue;
//queue Q = {-1, -1, 0};
//
//bool isFull(void){
//	return (Q.rear == MAXLEN-1) ? true : false;
//}
//
//bool isEmpty(void){
//	return (Q.rear == -1 && Q.front == -1) ? true : false;
//}
//
//void enqueue(int *arr, int k)
//{
//	if( isEmpty() ){
//		Q.rear = Q.front = 0;
//		arr[Q.rear++] = k;
//		Q.count++;
//		return;
//	}else if( isFull() ){
//		printf("Queue full, can't push\n");
//		return;
//	}
//	*(arr + Q.rear) = k;
//	Q.rear++;
//	Q.count++;
//}
//
//void dequeue(int *arr)
//{
//	if(Q.front == Q.rear){
//		Q.rear = Q.front = -1;
//		return;
//	}
//	
//	if( isEmpty() )
//		return;
//	
//	Q.front++;
//	Q.count--;
//}
//
//int main()
//{
//	int *qarr = (int*)malloc(sizeof(int) * MAXLEN);
//	enqueue(qarr, 8);
//	enqueue(qarr, 9);
//	enqueue(qarr, 3);
//	enqueue(qarr, 53);
//	dequeue(qarr);
//	printf("Head of the queue %d\n", qarr[Q.front]);
//	printf("Rear of the queue %d\n", qarr[Q.rear-1]);
//	
//	return 0;
//}

// Array implementation
// This approach bears a serious problem where if we keep dequeuing, the blank spaces before front are totally wasted making it less efficient for queue manipulation
// For this case, introduce to circular array.
// Circular array essentially is normal array, the only difference being the way we deal with traversal.
// Let's see how we can achieve this in code example for queue implementation.

//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//
//#define MAXLEN 100
//
//typedef struct{
//	int front, rear, count;
//} queue;
//queue q = {-1, -1, 0};
//
//bool isEmpty(void){
//	return ( q.front == -1 &&  q.rear == -1 ) ? true : false;
//}
//
//bool isFull(void){
//	return ((q.rear + 1) % MAXLEN == q.front) ? true : false;
//}
//
//void enqueue(int *arr, int key){
//	if( isEmpty() ){
//		q.front = q.rear = 0;
//		arr[q.rear++] = key;
//		q.count++;
//		return;
//	}
//	
//	if( isFull() )
//		return;
//	
//	arr[q.rear] = key;
//	q.rear = (q.rear + 1) % MAXLEN;
//	q.count++;
//}
//
//void dequeue(int *arr){
//	if( isEmpty() )
//		return;
//	else if( q.front == q.rear ){
//		q.front = q.rear = -1;
//		q.count = 0;
//	}else{
//		q.front = (q.front + 1) % MAXLEN;
//		q.count--;
//	}
//}
//
//int main(){
//	int *qarr = (int*)malloc(sizeof(int) * MAXLEN);
//	enqueue(qarr, 8);
//	enqueue(qarr, 9);
//	enqueue(qarr, 3);
//	enqueue(qarr, 53);
//	dequeue(qarr);
//	printf("Head of the queue %d\n", qarr[q.front]);
//	printf("Rear of the queue %d\n", qarr[q.rear-1]);
//	
//	return 0;
//}
