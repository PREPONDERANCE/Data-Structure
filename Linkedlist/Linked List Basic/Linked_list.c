#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *next;
}Node;

// Explanation : By creating structure Node, we actually combine data field and pointer field together. Pointer field is a pointer of a data structure we just created -- struct Node, pointing to the next structure we may initialize later in main function.

void traverse(Node *a);
void push(Node **head_ref, int new_data);
void insertafter(Node *prev_node, int new_data);
void append(Node **head_ref, int new_data);

// In later programming, we're gonna see how to link every Node to form a list and that how we can traverse the list using another pointer -- walker.
int main()
{
	Node* head = NULL;
	Node* second = NULL;
	Node* third = NULL;
	
	head = (Node*)malloc(sizeof(Node));
	second = (Node*)malloc(sizeof(Node));
	third = (Node*)malloc(sizeof(Node));
	// Allocate 3 blocks for each node in the heap
	
	head->data = 1;
	head->next = second;
	// The second statement means the pointer field of a Node structure called head now owns the address of another Node structure called second.
	
	second->data = 2;
	second->next = third;
	
	third->data = 3;
	third->next = NULL;
	// The second statement means the list has reached its end; we set the value of pointer field of Node third to NULL to represent the end.
	
	traverse(head);
	
	free(head);
	free(second);
	free(third);
	
	return 0;
}

void traverse(Node *a)
// Function traverse receive a pointer of type Node, in which cases we tend to pass in the head node inside.
{
	while(a != NULL){
		printf("%d\n",a->data);
		// Code here can be customized to any operations you like.
		a = a->next;
	}
	// Suppose we pass in head node. While the pointer doesn't equal to NULL, take an example, head = head->next = second;
	//  a->data equals to (head = head->next = second)->data // wrong statement, just to show the meaning!!!
}


//Insertion in Linked list
void push(Node **head_ref, int new_data)
{
	Node* new_Node = (Node*)malloc(sizeof(Node));
	new_Node->data = new_data;
	new_Node->next = *head_ref;
	*head_ref = new_Node;
}

void insertafter(Node *prev_node, int new_data)
{
	if(prev_node == NULL)
		return;
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = new_data;
	new_node->next = prev_node->next;
	prev_node->next = new_node;
}

void append(Node **head_ref, int new_data)
{
	Node* new_Node = (Node*)malloc(sizeof(Node));
	new_Node->data = new_data;
	new_Node->next = NULL;
	if(*head_ref == NULL){
		*head_ref = new_Node;
		return;
	}
	
	Node* last = *head_ref;
	while(last->next != NULL)
		last = last->next;
	last->next = new_Node;
}