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
	if( *headref == NULL || newNode->data < (*headref)->data ){
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

void InsertSort(Node** headref){
	Node* temp = *headref;
	Node* next = *headref;
	Node dummy;
	dummy.next = NULL;
	Node* head = &dummy;
	
	while( temp ){
		next = next->next;
		SortedInsert(&(head->next), temp);
		temp = next;
	}
	*headref = dummy.next;
}

int main(){
	Node* head = NULL;
	push(&head, 6);
	push(&head, 3);
	push(&head, 8);
	push(&head, 7);
	push(&head, 1);
	push(&head, 4);
	InsertSort(&head);
	
	print(head);
	
	return 0;
}