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

void insert(Node* head, int data, int pos){
	
}

Node* reverse(Node* head){
	Node* temp;
	if( head->next == NULL ) return head;
	temp = reverse(head->next);
	head->next->next = head;
	head->next = NULL;
	return temp;
}

void print(Node* head){
	while( head ){
		printf("%d ", head->data);
		head = head->next;
	}
	putchar('\n');
}

void append(Node** headref, Node** tailref, int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	
	if( !*headref ){
		*headref = *tailref = newNode;
		return;
	}
	
	(*tailref)->next = newNode;
	*tailref = newNode;
}

int main(int argc, char *argv[]) {
	
}