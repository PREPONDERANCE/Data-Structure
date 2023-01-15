#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void push(Node** headref, int new_data)
{
	Node* new_Node = (Node*)malloc(sizeof(Node));
	new_Node->data = new_data;
	new_Node->next = *headref;
	*headref = new_Node;
}

void printlist(Node* head)
{
	if( head ){
		printf("%d ", head->data);
		printlist(head->next);
	}
}

void reverseprint(Node* head)
{
	if( head ){
		reverseprint(head->next);
		printf("%d ", head->data);
	}
}

int main()
{
	Node* head = NULL;
	push(&head, 5);
	push(&head, 6);
	push(&head, 4);
	push(&head, 2);
	printlist(head);
	putchar('\n');
	
	reverseprint(head);
	
	return 0;
}