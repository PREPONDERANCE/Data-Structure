#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void push(Node**, int);
void append(Node**, Node**);
void print(Node*);

int main(){
	Node* head1 = NULL;
	Node* head2 = NULL;
	
	push(&head1, 4);
	push(&head1, 6);
	push(&head1, 3);
	
	push(&head2, 5);
	push(&head2, 1);
	push(&head2, 2);
	
	print(head1);
	print(head2);
	
	append(&head1, &head2);
	print(head1);
	print(head2);
	
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

void append(Node** aref, Node** bref){
	if( *aref == NULL ){
		*aref = *bref;
		*bref = NULL;
		return;
	}
	
	Node* last = *aref;
	while( last->next )
		last = last->next;
	last->next = *bref;
	*bref = NULL;
}