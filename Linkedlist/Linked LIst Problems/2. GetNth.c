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

int GetNth(Node* head, int pos){
	int i;
	for(i = 0; i < pos; i++){
		if( head == NULL ){
			printf("Out of range\n");
			return -1;
		}
		head = head->next;
	}
	return head->data;
}

int main(){
	Node* head = NULL;
	push(&head, 4);
	push(&head, 1);
	push(&head, 2);
	push(&head, 6);
	push(&head, 5);
	
	printf("%d", GetNth(head, 2));
	
	return 0;
}