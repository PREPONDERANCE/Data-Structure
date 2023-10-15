#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct stack{
	int* data;
	int* avail;
	int* limit;
} stack;

void copy(int* dst, int* src, int len){
	for(int i = 0; i != len; i++)
		*dst++ = *src++;
}

stack* createStack(){
	stack* s = (stack*)malloc(sizeof(stack));
	s->data = s->avail = s->limit = NULL;
	return s;
}

int max(int a, int b){
	return a > b ? a : b;
}

void grow(stack* s){
	int curr_len = s->avail - s->data;
	int new_len = max(2*curr_len, 1);
	
	int* newArray = (int*)malloc(sizeof(new_len));
	copy(newArray, s->data, curr_len);
	s->avail = newArray + curr_len;
	s->limit = newArray + new_len;
	
	free(s->data);
	s->data = newArray;
}

void push(stack* s, int data){
	if( s->avail == s->limit ) grow(s);
	*(s->avail++) = data;
}

bool empty(stack* s){
	return (s->avail - s->data) == 0;
}

int pop(stack* s){
	if( empty(s) ) return INT_MIN;
	int temp = *(s->avail--);
	return temp;
}

size_t size(stack* s){
	return s->avail - s->data;
}

size_t capacity(stack* s){
	return s->limit - s->data;
}

void print(stack* s){
	int total = size(s);
	for(int i = 0; i != total; i++) printf("%d ", s->data[i]);
	putchar('\n');
}

int main(int argc, char *argv[]) {
	stack* s = createStack();
	
	push(s, 2);
	push(s, 4);
	push(s, 6);
	push(s, 7);
	push(s, 9);
	print(s);
	
	printf("Size of current stack is %zu while the capacity of current stack is %zu", size(s), capacity(s));
	
	return 0;
}