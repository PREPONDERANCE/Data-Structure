// Implementation 1

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

void print(Node*);
void push(Node**, int);
void reverse(Node**);

int main(){
	Node* head = NULL;
	push(&head, 6);
	push(&head, 5);
	push(&head, 9);
	print(head);
	
	reverse(&head);
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

void reverse(Node** headref){
	Node *temp = *headref, *prev = NULL;
	
	while( temp ){
		*headref = (*headref)->next;
		// move forward in advance for other nodes to remain the link
		temp->next = prev;
		// reverse the link
		prev = temp;
		// move prev node forward for further reversal
		temp = *headref;
		// temp moves on to the next node of the original list without the help of its .next field
	}
	*headref = prev;
}






// Implementation 2 : With the help of MoveNode function (Check No.11 for details on function MoveNode)
//void reverse(Node**);
//void MoveNode(Node**, Node**);

//void reverse(Node** headref){
//	Node* result = NULL;
//	Node* current = *headref;
//	while( current != NULL )
//		MoveNode(&result, &current);
//	
//	*headref = result;
//}
//
//void MoveNode(Node** dst, Node** src){
//	if( *src == NULL )
//		return;
//	
//	Node* temp = *src;
//	*src = temp->next;
//	temp->next = *dst;
//	*dst = temp;
//}





// Implementation 3 : Front-Middle-Back strategy
//void reverse(Node**);
//
//void reverse(Node** headref){
//	if( *headref ){
//		Node* front = (*headref)->next;
//		Node* mid = *headref;
//		Node* back = NULL;
//		
//		while(1){
//			mid->next = back;
//			if( front == NULL ) break;
//			back = mid;
//			mid = front;
//			front = front->next;
//		}
//		*headref = mid;
//	}
//}
// This version is similar to implenmentation 1 for both scenarios we use 3 different pointers for traversal, the only difference being how we jump out of the loop.