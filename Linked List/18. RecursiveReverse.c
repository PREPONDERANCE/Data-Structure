#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void print(Node*);
void push(Node**, int);
void RecursiveReverse1(Node**);
Node* RecursiveReverse2(Node*);


int main(){
	Node* head = NULL;
	push(&head, 6);
	push(&head, 5);
	push(&head, 9);
	print(head);
	
	RecursiveReverse1(&head);
	//head = RecursiveReverse2(head);
	print(head);
	
	return 0;
}

void push(Node** headref, int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = *headref;
	*headref = newNode;
}

void print(Node* head){
	while( head ){
		printf("%d ", head->data);
		head = head->next;
	}
	putchar('\n');
}

void RecursiveReverse1(Node** headref){
	Node* temp = *headref;
	if( temp->next == NULL )
		return;
	*headref = (*headref)->next;
	RecursiveReverse1(headref);
	temp->next->next = temp;
	temp->next = NULL;
}

Node* RecursiveReverse2(Node* head){
	Node* temp = head;
	if( head->next == NULL)
		return head;
	temp = RecursiveReverse2(head->next);
	head->next->next = head;
	head->next = NULL;
	
	return temp;
}