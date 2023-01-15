#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void print(Node*);
void push(Node**, int);
Node* ShuffleMerge(Node*, Node*);

int main(){
	Node* head1 = NULL;
	Node* head2 = NULL;
	
	push(&head1, 4);
	push(&head1, 6);
	push(&head1, 3);
	
	push(&head2, 5);
	push(&head2, 1);
	push(&head2, 2);
	
	Node* head = ShuffleMerge(head1, head2);
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

Node* ShuffleMerge(Node* a, Node* b){
	Node* temp = (Node*)malloc(sizeof(Node));
	Node* merged = temp;
	
	while( a && b ){
		temp->next = a;
		a = a->next;
		temp = temp->next;
		temp->next = b;
		b = b->next;
		temp = temp->next;
	}
	while( a ){
		temp->next = a;
		a = a->next;
	}
	while( b ){
		temp->next = b;
		b = b->next;
	}
	
	return merged->next;
}