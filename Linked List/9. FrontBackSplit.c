#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void FrontBackSplit(Node*, Node**, Node**);
void push(Node**, int);
void print(Node*);

int main(){
	Node* head = NULL;
	push(&head, 6);
	push(&head, 3);
	push(&head, 8);
	push(&head, 7);
	push(&head, 1);
	push(&head, 4);
	
	Node *front, *back;
	FrontBackSplit(head, &front, &back);
	print(front);
	print(back);
	
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

void FrontBackSplit(Node* src, Node** frontref, Node** backref){
	Node* slow = src;
	Node* fast = src;
	
	while( fast->next ){
		fast = fast->next;
		if( fast->next ){
			slow = slow->next;
			fast = fast->next;
		}
	}
	
	*frontref = src;
	*backref = slow->next;
	slow->next = NULL;
}