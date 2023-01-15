// In previous codes, we've covered push, insertafter, append but sometimes we want to build a link in the sequence we list the numbers using constant time, which function append doesn't possess.
// In the following code examples, we'll introduce some techniques ranging in increasing order of difficulty

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

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

// Build a link containing {1, 2, 3, 4, 5}
// Code example one
Node* buildlink1(void){
	Node dummy;
	Node* tail = &dummy;
	
	dummy.next = NULL;
	for(int i = 1; i < 6; i++){
		push(&(tail->next), i);
		tail = tail->next;
	}
	
	return dummy.next;
}
// In this example, dummy node serves as a temporary head node 
// The .next field of dummy node stores the head address of the list and by passing &(tail->next), we're actually passing in the tail address of the current list, by which way, we can build the list just the way we hope.



// Code example two
Node* buildlink2(void){
	Node* head = NULL;
	Node** tail = &head;
	
	for(int i = 1; i < 6; i++){
		push(tail, i);
		tail = &(*tail)->next;
	}
//	Suppose initially the address of head is 200 making tail = 200;
//	After first round of pushing, suppose head = 24( the address of newNode ), tail now has the address of .next field of newNode while head remains the same.
	
	
//	for(int i = 1; i < 6; i++){
//		push(tail, i);
//		*tail = (*tail)->next;
//	}
//	This method is wrong!!! Because what actually changes during its execution is the head pointer meaning at the end of the funcion, head points to the tail of the list even though the list is successfully built.
	
	return head;
}
// Code example 2 is not very much recommended but it's a good skill to master.


int main(){
	Node* head = NULL;
	//head = buildlink1();
	head = buildlink2();
	print(head);
	
	return 0;
}