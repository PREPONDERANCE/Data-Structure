#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Utility functions and definitions
typedef struct Node{
	int data;
	struct Node* next;
} Node;

Node* createNode(){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	return newNode;
}

void push(Node** headref, int data){
	Node* newNode = createNode();
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

int len(Node* head){
	int count = 0;
	while( head ) { count++; head = head->next; }
	return count;
}
// Utility functions and definitions end

// Your code

// Task 1 : Count
int Count(Node* head, int searchFor){
	int count = 0;
	while( head ){
		if( head->data == searchFor ) count++;
		head = head->next;
	}
	return count;
}

// Task 2 : GetNth
int GetNth(Node* head, int pos){
	for(int i = 0; i != pos; i++)
		if( head ) head = head->next;
	
	if( head ) return head->data;
	assert(0);
}

// Task 3 : DeleteList
void DeleteList(Node** headref){
	Node* temp = *headref;
	while( temp ){
		temp = temp->next;
		free(*headref);
		*headref = temp;
	}
}

// Task 4 : Pop
int Pop(Node** headref){
	if( !*headref ) return 0;
	
	int temp = (*headref)->data;
	*headref = (*headref)->next;
	return temp;
}

// Task 5 : insertNth
// This function covers the basic insert functionality which we won't be repeating again

// Task 6 : SortedInsert
// Utility functions for SortedInsert
Node* split(Node** head, Node** tail){
	Node *fast = *head, *slow = *head;
	
	while( fast != (tail ? *tail : NULL) ){
		fast = fast->next;
		if( fast != (tail ? *tail : NULL) ){
			fast = fast->next;
			slow = slow->next;
		}
	}
	
	return slow;
}

void SortedInsertUtil(Node** headref, Node** tailref, Node* newnode){
	if( *headref == NULL ) { *headref = newnode; newnode->next = NULL; return; }
	
	if( (*headref)->next == (tailref ? *tailref : NULL) ){
		if( newnode->data >= (*headref)->data ){
			newnode->next = (*headref)->next;
			(*headref)->next = newnode;
		}else{
			newnode->next = *headref;
			*headref = newnode;
		}
		return;
	}
	
	Node* middle = split(headref, tailref);
	if( newnode->data >= middle->data ) SortedInsertUtil(&middle, tailref, newnode);
	else if( newnode->data < middle->data ) SortedInsertUtil(headref, &middle, newnode);
}
// Utility functions end

void SortedInsert(Node** headref, Node* newNode){
	SortedInsertUtil(headref, NULL, newNode);
}

// Task 7 : InsertSort
void InsertSort(Node** headref){
	Node* result = NULL, *current = *headref, *next;
	
	while( current ){
		next = current->next;
		SortedInsert(&result, current);
		current = next;
	}
	
	*headref = result;
}

// Task 8 : Append
Node* tailNode(Node** headref){
	if( (*headref)->next == NULL ) return *headref;
	Node* middle = split(headref, NULL);
	return tailNode(&middle);
}

void Append(Node** aRef, Node** bRef){
	if( *aRef == NULL ) { *aRef = *bRef; return; }
	Node* tail = tailNode(aRef);
	tail->next = *bRef;
	*bRef = NULL;
}

// Task 9 : FronBackSplit
void FrontBackSplit(Node* src, Node** frontRef, Node** backRef){
	if( src == NULL || src->next == NULL ){
		*frontRef = src;
		*backRef = NULL;
		return;
	}
	
	Node *fast = src->next, *slow = src;
	while( fast ){
		fast = fast->next;
		if( fast ){
			fast = fast->next;
			slow = slow->next;
		}
	}
	
	*frontRef = src;
	*backRef = slow->next;
	slow->next = NULL;
}

// Task 10 : RemoveDuplicate
void RemoveDuplicate(Node* head){
	while( head ){
		if( head->next && head->next->data < head->data ) head = head->next;
		else{
			int data = head->data;
			Node *current = head->next, *temp = head->next;
			while( temp && temp->data == data ){
				current = temp->next;
				free(temp);
				temp = current;
			}
			head->next = temp;
			head = temp;
		}
	}
}

// Task 11 : MoveNode
void MoveNode(Node** dstRef, Node** srcRef){
	if( *srcRef == NULL ) return;
	
	Node* temp = *srcRef;
	*srcRef = (*srcRef)->next;
	temp->next = *dstRef;
	*dstRef = temp;
}

// Task 12 : AlternatingSplit
void AlternatingSplit(Node* src, Node** frontRef, Node** backRef){
	int i = 1;
	while( src ){
		if( i%2 ) MoveNode(frontRef, &src);
		else MoveNode(backRef, &src);
		i++;
	}
}

// Task 13 : ShuffleMerge
Node* ShuffleMerge(Node* head1, Node* head2){
	Node* temp = (Node*)malloc(sizeof(Node));
	Node* merged = temp;
	
	int i = 1;
	while( head1 && head2 ){
		if( i%2 ){
			temp->next = head1;
			head1 = head1->next;
		}else{
			temp->next = head2;
			head2 = head2->next;
		}
		temp = temp->next;
		i++;
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

// Task 14 : SortedMerge
// Task 15 : MergeSort
// Both tasks are very familiar to us

// Task 16 : SortedIntersect
Node* SortedIntersect(Node* head1, Node* head2){
	Node* temp = (Node*)malloc(sizeof(Node));
	Node* merged = temp;
	
	while( head1 && head2 ){
		while( head1->data != head2->data )
			if( head1->data < head2->data )
				head1 = head1->next;
			else head2 = head2->next;
		while( head1 && head2 && head1->data == head2->data ){
			Node* newNode = createNode();
			newNode->data = head1->data;
			temp->next = newNode;
			temp = temp->next;
			head1 = head1->next;
			head2 = head2->next;
		}
	}
	
	return merged->next;
}

// Test functions


// Test functions end

int main(int argc, char *argv[]) {
	Node* head = NULL;
	push(&head, 3);
	push(&head, 2);
	push(&head, 1);
//	push(&head, 3);
//	push(&head, 5);
//	push(&head, 5);
//	push(&head, 6);
//	push(&head, 7);
//	push(&head, 7);
//	push(&head, 7);
//	push(&head, 8);
//	push(&head, 9);
//	push(&head, 9);
	
	Node* head2 = NULL;
	push(&head2, 7);
	push(&head2, 3);
	push(&head2, 2);
//	push(&head2, 2);
//	push(&head2, 1);
	
//	Node *a = NULL, *b = NULL;
//	AlternatingSplit(head2, &a, &b);
//	print(a);
//	print(b);
	
//	Node* merged = ShuffleMerge(head, head2);
//	print(merged);
//	
	Node* e = SortedIntersect(head, head2);
	print(e);
	
	//RemoveDuplicate(head);
	
//	MoveNode(&head, &head2);
//	
//	print(head);
	
//	Node* newNode = createNode();
//	newNode->data = 10;
//	SortedInsert(&head, newNode);
	
//	InsertSort(&head);
	
//	Node* result = tailNode(&head);
//	print(result);
	
//	Append(&head, &head2);
//	print(head);
//	print(head2);
	
//	print(head);
//	int a = Pop(&head);
//	int b = Pop(&head);
//	int c = Pop(&head);
//	int length = len(head);
//	
//	printf("%d %d %d %d", a, b, c, length);
	
	return 0;
}