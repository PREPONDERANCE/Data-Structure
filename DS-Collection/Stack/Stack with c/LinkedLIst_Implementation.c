#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

typedef struct{
	size_t count;
	Node *top;
} stack;

stack* createStack(){
	stack* s = (stack*)malloc(sizeof(stack));
	s->top = NULL;
	s->count = 0;
	return s;
}

Node* createNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void push(stack* s, int data){
	Node* newNode = createNode(data);
	newNode->next = s->top;
	s->top = newNode;
	s->count++;
}

bool empty(stack* s){
	return s->count == 0;
}

size_t size(stack* s){
	return s->count;
}

int top(stack* s){
	if( empty(s) ) return INT_MIN;
	return s->top->data;
}

void pop(stack* s){
	if( empty(s) ) return;
	Node* temp = s->top;
	s->top = s->top->next;
	s->count--;
	free(temp);
}

void swap(stack* s1, stack* s2){
	Node* temp = s1->top;
	s1->top = s2->top;
	s2->top = temp;
}

int main(int argc, char *argv[]) {
	
}