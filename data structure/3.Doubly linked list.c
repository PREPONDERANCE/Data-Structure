#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
	int data;
	struct Node *prev, *next;
} Node;

Node* CreateNode(int);
void push(Node**, int);
void insert(Node*, int);
void append(Node**, int);
void deleteN(Node**, int);
void printlist(Node*);
void reverseprint(Node*);

int main(){
	Node* head = NULL;
	push(&head, 5);
	push(&head, 4);
	push(&head, 9);
	insert(head, 3);
	insert(head, 7);
	insert(head, 2);
	append(&head, 8);
	append(&head, 1);
	append(&head, 6);
	printlist(head);
	
	deleteN(&head, 9);
	printlist(head);
	//reverseprint(head);
	
	return 0;
}

Node* CreateNode(int data){
	Node* new_Node = (Node*)malloc(sizeof(Node));
	new_Node->data = data;
	new_Node->next = new_Node->prev = NULL;
	return new_Node;
}

void push(Node** headref, int new_data){
	Node* newNode = CreateNode(new_data);
	
	if( *headref == NULL ){
		*headref = newNode;
		return;
	}
	
	newNode->next = *headref;
	(*headref)->prev = newNode;
	*headref = newNode;
}

void insert(Node* prev, int new_data){
	if( prev == NULL )
		return;
	
	Node* newNode = CreateNode(new_data);
	newNode->next = prev->next;
	prev->next->prev = newNode;
	prev->next = newNode;
	newNode->prev = prev;
}

void append(Node** headref, int new_data){
	Node* newNode = CreateNode(new_data);
	
	if( *headref == NULL ){
		*headref = newNode;
		return;
	}
	
	Node* last = *headref;
	while( last->next )
		last = last->next;
	last->next = newNode;
	newNode->prev = last;
}

void deleteN(Node** headref, int pos){
	Node* temp = *headref;
	int i;
	
	for(i = 0; i < pos; i++){
		if( i == 0 && pos == 1){
			*headref = (*headref)->next;
			(*headref)->prev = NULL;
			free(temp);
		}else{
			if( i == pos-1 && temp ){
				if( temp->next == NULL ){
					temp->prev->next = temp->next;
					return;
				}
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				free(temp);
			}else{
				if( temp == NULL )
					return;
				temp = temp->next;
			}
		}
	}
}

void printlist(Node* head){
	while( head ){
		printf("%d ", head->data);
		head = head->next;
	}
	putchar('\n');
}

void reverseprint(Node* head){
	Node* last = head;
	while(last->next)
		last = last->next;
	
	while( last ){
		printf("%d ", last->data);
		last = last->prev;
	}
	putchar('\n');
}