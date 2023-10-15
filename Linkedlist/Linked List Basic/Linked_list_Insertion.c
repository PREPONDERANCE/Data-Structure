#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
}Node;

void push(Node** head_ref, int new_data);
void printlist(Node *head);
void insertafter(Node *prev_node, int new_data);
void append(Node** head_ref, int new_data);
int getcount_v1(Node* head)
{
	int cnt = 0;
	Node* last = head;
	while( last ){
		cnt++;
		last = last->next;
	}
	return cnt;
}

int getcount_v2(Node* head)
{
	int cnt = 0;
	if(head == NULL)
		return 0;
	else
		return 1+getcount_v2(head->next);
}
//int getcount_v3(Node* head, int count = 0)
//{
//	if(head == NULL)
//		return count;
//	return getcount_v3(head->next, count+1);
//} CPP

int main()
{
	Node* head = NULL;
	push(&head, 9);
	append(&head, 8);
	append(&head, 7);
	insertafter(head, 3);
	insertafter(head->next, 4);
	
	printlist(head);
	printf("\n%d", getcount_v1(head));
	printf("\n%d", getcount_v2(head));
//	printf("\n%d", getcount_v3(head));
	
	return 0;
}

void push(Node** head_ref, int new_data)
{
	Node* new_Node = (Node*)malloc(sizeof(Node));
	new_Node->data = new_data;
	new_Node->next = *head_ref;
	*head_ref = new_Node;
}

void insertafter(Node* prev_node, int new_data)
{
	if(prev_node == NULL)
		return;
	Node* new_Node = (Node*)malloc(sizeof(Node));
	new_Node->data = new_data;
	new_Node->next = prev_node->next;
	prev_node->next = new_Node;
}

void append(Node** head_ref, int new_data)
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

void printlist(Node* head)
{
	while(head != NULL){
		printf("%d ",head->data);
		head = head->next;
	}
}