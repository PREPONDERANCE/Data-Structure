#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void print(Node* head){
	while( head ){
		printf("%d ", head->data);
		head = head->next;
	}
	putchar('\n');
}

void InsertNth(Node** headref, int pos, int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	Node *temp = *headref, *prev = *headref;
	newNode->data = data;
	int i;
	
	for(i = 0; i <= pos; i++){
		if( i == 0 && pos == 0 ){
			newNode->next = *headref;
			*headref = newNode;
			return;
		}else{
			if( i == pos ){
				newNode->next = temp;
				prev->next = newNode;
				return;
			}else{
				prev = temp;
				if( prev == NULL )
					return;
				temp = temp->next;
			}
		}
	}
}

int main(){
	Node* head = NULL;
	InsertNth(&head, 0, 13);
	InsertNth(&head, 1, 42);
	InsertNth(&head, 1, 5);
	
	print(head);
	
	return 0;
}




//#include <assert.h>
//
//void push(Node**, int);
//void InsertNth(Node**, int, int);
//
//void push(Node** headref, int data){
//	Node* newNode = (Node*)malloc(sizeof(Node));
//	newNode->data = data;
//	newNode->next = *headref;
//	*headref = newNode;
//}
//
//void InsertNth(Node** headref, int pos, int data){
//	if( pos == 0 )
//		push(headref, data);
	//// Look out for specail cases
//	else{
//		Node* current = *headref;
//		int i;
//		
//		for(i = 0; i < pos-1; i++){
//			assert(current != NULL);
			// check if pos is out of range
//			current = current->next;
//		}
//		push(&(current->next), data);
		//// add a new node to the front of the next node
//	}
//}