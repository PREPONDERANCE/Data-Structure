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

int Count(Node* head, int key){
//	Recursive version of this function
	static int count = 0;
	
	if( head ){
		if( head->data == key )
			count = Count(head->next, key) + 1;
		else
			count = Count(head->next, key);
	}
	
//	Iterative version
	
//	while( head ){
//		if( head->data == key )
//			count++;
//		head = head->next;
//	}
	
	return count;
}

int main(){
	Node* head = NULL;
	push(&head, 5);
	push(&head, 2);
	push(&head, 4);
	push(&head, 2);
	push(&head, 2);
	push(&head, 1);
	
	printf("%d", Count(head, 2));
	return 0;
}