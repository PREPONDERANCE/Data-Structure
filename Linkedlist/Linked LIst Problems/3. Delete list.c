#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void push(Node** headref, int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = *headref;
	*headref = newNode;
}

void deletelist(Node** headref){
	Node* temp = *headref;
	
	while( temp ){
		*headref = (*headref)->next;
		free(temp);
		temp = *headref;
	}
}

void print(Node* head){
	while( head ){
		printf("%d ", head->data);
		head = head->next;
	}
	putchar('\n');
}

int main(){
	Node* head = NULL;
	push(&head, 4);
	push(&head, 1);
	push(&head, 2);
	push(&head, 6);
	push(&head, 5);
	print(head);
	
	deletelist(&head);
	print(head);
	
	return 0;
}