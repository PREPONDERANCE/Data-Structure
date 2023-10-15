#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

typedef struct{
	int count;
	Node* top;
} Stack;

Node* CreateNode(int);
Node* TopReference(Stack*);
Stack* CreateStack();
void push(Stack*, int);
void pop(Stack*);
void clear(Stack*);
void print(Stack*);
void reverseprint(Stack*);
bool empty(Stack*);
int size(Stack*);

int main()
{
	Stack* s = CreateStack();
	push(s, 5);
	push(s, 6);
	push(s, 3);
	push(s, 4);
	push(s, 2);
	push(s, 9);
	print(s);
	
	pop(s);
	pop(s);
	print(s);
	
	printf("size of current stack is %d\n", size(s));
	clear(s);
	
	return 0;
}

Node* CreateNode(int new_data){
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = new_data;
	temp->next = NULL;
	return temp;
}

Stack* CreateStack(void){
	Stack* temp = (Stack*)malloc(sizeof(Stack));
	temp->count = 0;
	temp->top = NULL;
	return temp;
}

void push(Stack* s, int new_data){
	Node* newNode = CreateNode(new_data);
	newNode->next = s->top;
	s->top = newNode;
	s->count++;
}

void pop(Stack* s){
	if(s->top == NULL)
		return;
	
	Node* temp = s->top;
	s->top = s->top->next;
	s->count--;
	free(temp);
}

bool empty(Stack *s){
	return (s->count > 0) ? false : true;
}

int size(Stack *s){
	return s->count;
}

Node* TopReference(Stack *s){
	return s->top;
}

void clear(Stack* s){
	Node* temp = s->top;
	
	while( temp ){
		s->top = s->top->next;
		free(temp);
		temp = s->top;
	}
	s->count = 0;
}

void print(Stack* s){
	Node* temp = s->top;
	if( s->top ){
		printf("%d ", s->top->data);
		s->top = s->top->next;
		print(s);
	}else
		putchar('\n');
	s->top = temp;
}

void reverseprint(Stack *s){
	Node* temp = s->top;
	if( s->top->next ){
		s->top = s->top->next;
		print(s);
	}
	printf("%d ", s->top->data);
	s->top = temp;
}



//#include <stdio.h>
//#include <stdbool.h>
//
//#define MAXLEN 3
//int A[MAXLEN];
//int top = -1;
//
//void push(int);
//void pop(void);
//bool isempty(void);
//int topelement(void);
//int size(void);
//
//int main(){
//	push(3);
//	push(4);
//	push(5);
//	push(2);
//	pop();
//	pop();
//	pop();
//	
//	return 0;
//}
//
//void push(int x){
//	if( top == MAXLEN-1 ){
//		printf("Stack full, can't push\n");
//		return;
//	}
//	A[++top] = x;
//}
//
//void pop(void){
//	if( isempty() ){
//		printf("Stack empty, can't pop\n");
//		return;
//	}
//	top--;
//}
//
//bool isempty(void){
//	if( top == -1 )
//		return true;
//	return false;
//}
//
//int topelement(void){
//	return A[top];
//}
//
//int size(void){
//	return top+1;
//}
//// Array implementation