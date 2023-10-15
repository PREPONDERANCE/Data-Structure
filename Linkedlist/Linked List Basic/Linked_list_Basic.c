#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;
Node* head = NULL;

typedef struct{
	int size;
	Node* top;
} Stack;
Stack s;

typedef struct{
	int size;
	Node* top;
} Queue;
Queue q;

void push(Node** head, int new_data);
void insertafter(Node* prev, int new_data);
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
		}else{
			if(i==pos-1 && temp){
				prev->next = temp->next;
				free(temp);
			}else{
				prev = temp;
				if(!prev)
					break;
				temp = temp->next;
			}
		}
	}
}

void s_pop()
{
	if(!s.size)
		return;
	
	s.top = head;
	while( s.top->next )
		s.top = s.top->next;
	printf("%d\n", s.top->data);
	
	deleteN(&head, s.size);
	s.size--;
}

void q_pop()
{
	if( !q.size )
		return;
	
	q.top = head;
	printf("%d\n", q.top->data);
	
	deleteN(&head, 1);
	q.size--;
}

int main()
{
	push(&head, 5);
	push(&head, 4);
	insertafter(head, 3);
	append(&head, 9);
	insertafter(head, 2);
	push(&head, 7);
	push(&head, 1);
	append(&head, 6);
	printlist(head);
	putchar('\n');
	
	s_pop();
	s_pop();
	q_pop();
	q_pop();
	
	return 0;
}

void push(Node** head, int new_data)
{
	s.size++;
	q.size++;
	Node* new_Node = (Node*)malloc(sizeof(Node));
	new_Node->data = new_data;
	new_Node->next = *head;
	*head = new_Node;
}

void insertafter(Node* prev, int new_data)
{
	s.size++;
	q.size++;
	if( !prev )
		return;
	Node* new_Node = (Node*)malloc(sizeof(Node));
	new_Node->data = new_data;
	new_Node->next = prev->next;
	prev->next = new_Node;
}

void append(Node** head, int new_data)
{
	s.size++;
	q.size++;
	Node* new_Node = (Node*)malloc(sizeof(Node));
	new_Node->data = new_data;
	new_Node->next = NULL;
	if( !*head ){
		*head = new_Node;
		return;
	}
	
	Node* last = *head;
	while( last->next )
		last = last->next;
	last->next = new_Node;
}

void printlist(Node* head)
{
	while( head ){
		printf("%d ",head->data);
		head = head->next;
	}
}