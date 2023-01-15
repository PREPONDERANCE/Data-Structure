#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void print(Node*);
void push(Node**, int);
void FrontBackSplit(Node*, Node**, Node**);
Node* SortedMerge(Node*, Node*);
void MergeSort(Node**);

int main(){
	Node* head = NULL;
	push(&head, 6);
	push(&head, 3);
	push(&head, 7);
	push(&head, 1);
	push(&head, 4);

	MergeSort(&head);
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

void FrontBackSplit(Node* src, Node** frontref, Node** backref){
	Node* slow = src;
	Node* fast = src;
	
	while( fast->next ){
		fast = fast->next;
		if( fast->next ){
			slow = slow->next;
			fast = fast->next;
		}
	}
	
	*frontref = src;
	*backref = slow->next;
	slow->next = NULL;
}

void MergeSort(Node** headref){
	Node* temp = *headref;
	Node* a;
	Node* b;
	
	if( temp == NULL || temp->next == NULL )
		return;
	
	FrontBackSplit(temp, &a, &b);
		
	MergeSort(&a);
	MergeSort(&b);
		
	*headref = SortedMerge(a, b);
	
}