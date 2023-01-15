#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

Node* CreateNode(int);
void push(Node**, int);
void insert(Node*, int);
void append(Node**, int);
void deleteN(Node**, int);
void print(Node*);
void reverse(Node**);

int main(){
	Node* head = NULL;
	push(&head, 5);
	push(&head, 3);
	insert(head, 6);
	insert(head, 9);
	append(&head, 8);
	append(&head, 4);
	print(head);
	
	deleteN(&head, 8);
	reverse(&head);
	print(head);
	
	return 0;
}

Node* CreateNode(int data){
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->next = NULL;
	return temp;
}

void push(Node** headref, int new_data){
	Node* newNode = CreateNode(new_data);
	
	if(*headref == NULL){
		*headref = newNode;
		newNode->next = newNode;
		return;
	}
	
	newNode->next = *headref;
	Node* temp = *headref;
	
	while( temp->next != *headref )
		temp = temp->next;
	temp->next = newNode;
	*headref = newNode;
}

void insert(Node* prev, int new_data){
	if( prev == NULL )
		return;
	Node* newNode = CreateNode(new_data);
	newNode->next = prev->next;
	prev->next = newNode;
}

void append(Node** headref, int new_data){
	Node* newNode = CreateNode(new_data);
	Node* temp = *headref;
	
	if( *headref == NULL ){
		*headref = newNode;
		newNode->next = newNode;
		return;
	}
	
	while( temp->next != *headref )
		temp = temp->next;
	temp->next = newNode;
	newNode->next = *headref;
}

void deleteN(Node** headref, int pos){
	Node *temp = *headref, *prev = *headref;
	int i;
	
	for(i = 0; i < pos; i++){
		if(i == 0 && pos == 1){
			Node* last = *headref;
			while( last->next != *headref )
				last = last->next;
			*headref = (*headref)->next;
			last->next = *headref;
			free(temp);
		}else{
			if( i == pos-1 && temp != *headref){
				prev->next = temp->next;
				free(temp);
			}else{
				prev = temp;
				if( prev->next == *headref )
					return;
				temp = temp->next;
			}
		}
	}
}

void print(Node* head){
	Node* temp = head;
	do{
		printf("%d ", temp->data);
		temp = temp->next;
	}while( temp != head );
	putchar('\n');
}

void reverse(Node** headref){
	Node* temp = *headref;
	Node* prev = *headref;
	Node* current = *headref;
	
	do{
		temp = temp->next;
	}while( temp->next != *headref );
	
	do{
		current = current->next;
		prev->next = temp;
		temp = prev;
		prev = current;
	}while( current != *headref );
	
	*headref = temp;
}

// Think about how to write recursive versions
// (Might need to take in 2 arguments)