//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct Node{
//	int data;
//	struct Node* next;
//} Node;
//
//void push(Node**, int);
//void reverse(Node**);
//void printlist(Node*);
//
//int main()
//{
//	Node* head = NULL;
//	push(&head, 5);
//	push(&head, 6);
//	push(&head, 4);
//	push(&head, 2);
//	printlist(head);
//	
//	reverse(&head);
//	printlist(head);
//
//	return 0;
//}
//
//void push(Node** headref, int new_data)
//{
//	Node* new_Node = (Node*)malloc(sizeof(Node));
//	new_Node->data = new_data;
//	new_Node->next = *headref;
//	*headref = new_Node;
//}
//
//void reverse(Node** head)
//{
//	Node *temp = *head, *prev = NULL;
//	while( temp ){
//		*head = (*head)->next;
//		temp->next = prev;
//		prev = temp;
//		temp = *head;
//	}
//	*head = prev;
//}
//
//void printlist(Node* head)
//{
//	while( head ){
//		printf("%d ", head->data);
//		head = head->next;
//	}
//	putchar('\n');
//}
// Iterative Version



// How do we write a recursive version of it?
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void push(Node**, int);
void printlist(Node*);
void reversal(Node**);
Node* reverselist(Node*);

int main()
{
	Node* head = NULL;
	push(&head, 5);
	push(&head, 6);
	push(&head, 4);
	push(&head, 2);
	printlist(head);
	
	reversal(&head);
	//head = reverselist(head);
	printlist(head);
	
	return 0;
}

void printlist(Node* head)
{
	while( head ){
		printf("%d ", head->data);
		head = head->next;
	}
	putchar('\n');
}

void push(Node** headref, int new_data)
{
	Node* new_Node = (Node*)malloc(sizeof(Node));
	new_Node->data = new_data;
	new_Node->next = *headref;
	*headref = new_Node;
}

void reversal(Node** headref)
{
//	Node* temp = *headref;
//	static Node* prev = NULL;
//
//	if( temp == NULL ){
//		*headref = prev;
//		return;
//	}
//	
//	*headref = (*headref)->next;
//	temp->next = prev;
//	prev = temp;
//	temp = *headref;
//	reverse(headref);
	
	Node* temp = *headref;
	if( temp->next == NULL )
		return;
	*headref = (*headref)->next;
	reversal(headref);
	temp->next->next = temp;
	temp->next = NULL;
}

Node* reverselist(Node* head)
{
	Node* temp;
	if( head->next == NULL )
		return head;
	temp = reverselist(head->next);
	head->next->next = head;
	head->next = NULL;
	return temp;
}
// In recursive functions, keep in mind of the current value of the variable that makes the recursive calls.
