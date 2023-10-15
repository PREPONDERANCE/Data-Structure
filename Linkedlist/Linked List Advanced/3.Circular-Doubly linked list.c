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
void print(Node*);
void reverseprint(Node*);

int main(){
	Node* head = NULL;
	append(&head, 9);
	insert(head, 3);
	push(&head, 5);
	push(&head, 4);
	print(head);
	
	deleteN(&head, 2);
	print(head);
	reverseprint(head);
	
	return 0;
}

Node* CreateNode(int data){
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->prev = temp->next = NULL;
	return temp;
}

void push(Node** headref, int new_data){
	Node* newNode = CreateNode(new_data);
	
	if( *headref == NULL ){
		*headref = newNode;
		newNode->next = newNode;
		return;
	}
	
	newNode->next = *headref;
	(*headref)->prev = newNode;
	
	Node* temp = *headref;
	while( temp->next != *headref )
		temp = temp->next;
	temp->next = newNode;
	newNode->prev = temp;
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
	Node* temp = *headref;
	
	if( *headref == NULL ){
		*headref = newNode;
		newNode->next = newNode->prev = newNode;
		return;
	}
	
	while( temp->next != *headref )
		temp = temp->next;
	newNode->next = temp->next;
	temp->next = newNode;
	newNode->prev = temp;
	(*headref)->prev = newNode;
}

void deleteN(Node** headref, int pos){
	Node* temp = *headref;
	int i;
	
	for(i = 0; i < pos; i++){
		if( i == 0 && pos == 1 ){
			Node* last = *headref;
			while( last->next != *headref )
				last = last->next;
			*headref = (*headref)->next;
			last->next = *headref;
			(*headref)->prev = last;
			free(temp);
		}else{
			if( i == pos-1 && temp != *headref ){
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				free(temp);
			}else{
				temp = temp->next;
				if( temp == *headref )
					return;
			}
		}
	}
}

void print(Node* head){
	Node* temp = head;
	do{
		printf("%d ", temp->data);
		temp = temp->next;
	}while( temp != head);
	putchar('\n');
}

void reverseprint(Node* head){
	Node* last = head;
	while( last->next != head )
		last = last->next;
	Node* temp = last;
	do{
		printf("%d ",last->data);
		last = last->prev;
	}while( last != temp );
	putchar('\n');
}