#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void push(Node** head, int new_data);
void insertafter(Node* head, int new_data);
void append(Node** head, int new_data);
void printlist(Node* head);

void deleteN(Node** head, int pos)
{
	Node* temp = *head;
	Node* prev = *head;
	int i;
	
	for(i = 0; i < pos; i++){
		if(pos == 1){
			*head = (*head)->next;
			free(temp);
		}else {
			if( i==pos-1 && temp ){
				prev->next = temp->next;
				free(temp);
			}
			else {
				prev = temp;
				if(prev == NULL)
					break;
				temp = temp->next;
			}
		}
	}
}

int main()
{
	Node* head = NULL;
	// Customise your code here
	// Functions available : push, insertafter, append, deletN, printlist
	
	push(&head, 8);
	push(&head, 7);
	append(&head, 3);
	insertafter(head->next, 5);
	append(&head, 4);
	printlist(head);
	putchar('\n');
	deleteN(&head, 1);
	
	printlist(head);
	return 0;
}

void push(Node** head, int new_data)
{
	Node* new_Node = (Node*)malloc(sizeof(Node));
	new_Node->data =  new_data;
	new_Node->next = *head;
	*head = new_Node;
}

void insertafter(Node* prev, int new_data)
{
	if(!prev)
		return;
	Node* new = (Node*)malloc(sizeof(Node));
	new->data = new_data;
	new->next = prev->next;
	prev->next = new;
}

void append(Node** head, int new_data)
{
	Node* new = (Node*)malloc(sizeof(Node));
	new->data = new_data;
	new->next = NULL;
	if(!*head){
		*head = new;
		return;
	}
	
	Node* last = *head;
	while(last->next)
		last = last->next;
	last->next = new;
}

void printlist(Node* head)
{
	Node* last = head;
	while(last){
		printf("%d ",last->data);
		last = last->next;
	}
}