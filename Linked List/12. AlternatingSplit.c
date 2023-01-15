#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void print(Node*);
void push(Node**, int);
void AlternatingSplit(Node*, Node**, Node**);

int main(){
	Node* head = NULL;
	push(&head, 6);
	push(&head, 3);
	push(&head, 7);
	push(&head, 1);
	push(&head, 4);
	
	Node* even = NULL;
	Node* odd = NULL;
	AlternatingSplit(head, &even, &odd);
	print(even);
	print(odd);
	
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

void AlternatingSplit(Node* src, Node** aref, Node** bref){
	Node *temp = src, *prev = src;
	int i = 1;
	
	while( temp ){
		temp = temp->next;
		if( i%2 ){
			prev->next = *aref;
			*aref = prev;
			prev = temp;
		}else{
			prev->next = *bref;
			*bref = prev;
			prev = temp;
		}
		i++;
	}
}