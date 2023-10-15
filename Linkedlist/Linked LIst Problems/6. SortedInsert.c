#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

Node* CreateNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void push(Node** headref, int data){
	Node* newNode = CreateNode(data);
	newNode->next = *headref;
	*headref = newNode;
}

void print(Node* head){
	if( head == NULL )
		putchar('\n');
	else{
		printf("%d ", head->data);
		print(head->next);
	}
}

void SortedInsert(Node** headref, Node* newNode){
	if( *headref == NULL ){
		*headref = newNode;
		return;
	}
	if( newNode->data < (*headref)->data ){
		newNode->next = *headref;
		*headref = newNode;
		return;
	}
	
	Node *temp = *headref, *prev = *headref;
	
	for(; temp && newNode->data > temp->data; temp = temp->next)
		prev = temp;
	newNode->next = temp;
	prev->next = newNode;
}

int main(){
	Node* head = NULL;
	push(&head, 5);
	push(&head, 4);
	push(&head, 3);
	push(&head, 2);
	push(&head, 1);
	print(head);
	
	SortedInsert(&head, CreateNode(0));
	SortedInsert(&head, CreateNode(4));
	SortedInsert(&head, CreateNode(8));
	print(head);
	
	return 0;
}