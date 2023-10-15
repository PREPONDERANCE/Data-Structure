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

void print(Node* head){
	while( head ){
		printf("%d ", head->data);
		head = head->next;
	}
	putchar('\n');
}

int pop(Node** headref){
	if( *headref == NULL ){
		printf("list is empty\n");
		return -1;
	}
	
	Node* temp = *headref;
	int data = temp->data;
	*headref = (*headref)->next;
	free(temp);
	return data;
}

int main(){
	Node* head = NULL;
	push(&head, 4);
	push(&head, 1);
	push(&head, 2);
	push(&head, 6);
	push(&head, 5);
	
	printf("%d\n", pop(&head));
	printf("%d\n", pop(&head));
	
	return 0;
}