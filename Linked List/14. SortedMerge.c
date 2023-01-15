#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void print(Node*);
void push(Node**, int);
Node* SortedMerge(Node*, Node*);

int main(){
	Node* head1 = NULL;
	Node* head2 = NULL;
	
	push(&head1, 8);
	push(&head1, 6);
	push(&head1, 3);
	
	push(&head2, 5);
	push(&head2, 1);
	push(&head2, 0);
	
	Node* head = SortedMerge(head1, head2);
	print(head);
	
	return 0;
}

void push(Node** headref, int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = *headref;
	*headref = newNode;
}

void print(Node* head){
	while( head ){
		printf("%d ", head->data);
		head = head->next;
	}
	putchar('\n');
}

Node* SortedMerge(Node* head1, Node* head2){
	Node* temp = (Node*)malloc(sizeof(Node));
	Node* merged = temp;
	
	while( head1 && head2 ){
		if( head1->data < head2->data ){
			temp->next = head1;
			head1 = head1->next;
		}else{
			temp->next = head2;
			head2 = head2->next;
		}
		temp = temp->next;
	}
	
	while( head1 ){
		temp->next = head1;
		head1 = head1->next;
		temp = temp->next;
	}
	
	while ( head2 ) {
		temp->next = head2;
		head2 = head2->next;
		temp = temp->next;
	}
	
	return merged->next;
}