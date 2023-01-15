#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void print(Node*);
void push(Node**, int);
Node* merge(Node*, Node*);
Node* middle(Node*);
Node* sort(Node*);
Node* SortedIntersect(Node*, Node*);

int main(){
	Node* head1 = NULL;
	Node* head2 = NULL;
	
	push(&head1, 4);
	push(&head1, 6);
	push(&head1, 2);
	push(&head1, 5);
	push(&head1, 8);
	push(&head1, 7);
	
	push(&head2, 5);
	push(&head2, 1);
	push(&head2, 7);
	push(&head2, 2);
	
	head1 = sort(head1);
	head2 = sort(head2);
	
	Node* head = SortedIntersect(head1, head2);
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

Node* merge(Node* head1, Node* head2){
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
	
	while( head2 ){
		temp->next = head2;
		head2 = head2->next;
		temp = temp->next;
	}
	
	return merged->next;
}

Node* middle(Node* head){
	Node* slow = head;
	Node* fast = head->next;
	
	while( fast && fast->next ){
		slow = slow->next;
		fast = fast->next->next;
	}
	
	return slow;
}

Node* sort(Node* head){
	if( head->next == NULL )
		return head;
	
	Node* mid = middle(head);
	Node* head2 = mid->next;
	mid->next = NULL;
	
	return merge(sort(head), sort(head2));
}

Node* SortedIntersect(Node* head1, Node* head2){
	Node* result = NULL;
	
	while( head1 && head2 ){
		if( head1->data < head2->data )
			head1 = head1->next;
		else if( head1->data > head2->data )
			head2 = head2->next;
		else{
			push(&result, head1->data);
			head1 = head1->next;
			head2 = head2->next;
			//result = result->next;
		}
	}
	
	return result;
}