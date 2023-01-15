#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void print(Node*);
void push(Node**, int);
void RemoveDuplicate(Node*);

int main(){
	Node* head = NULL;
	push(&head, 8);
	push(&head, 8);
	push(&head, 7);
	push(&head, 6);
	push(&head, 4);
	push(&head, 4);
	push(&head, 2);
	push(&head, 2);
	push(&head, 2);
	push(&head, 1);
	push(&head, 1);
	print(head);
	
	RemoveDuplicate(head);
	print(head);
	
	return 0;
}

void push(Node** headref, int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = *headref;
	*headref = newNode;
}

void RemoveDuplicate(Node* head){
	if( head->next == NULL )
		return;
	Node* prev = head;
	Node* temp = head->next;
	
	while( temp ){
		if( temp->data != prev->data ){
			prev->next = temp;
			prev = temp;
			temp = temp->next;
		}else{
			Node* current = temp;
			temp = temp->next;
			free(current);
		}
	}
	prev->next = temp;
}

void print(Node* head){
	while( head ){
		printf("%d ", head->data);
		head = head->next;
	}
	putchar('\n');
}