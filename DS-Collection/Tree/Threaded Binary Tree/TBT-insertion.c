#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
	int data;
	bool Ltag, Rtag;
	struct Node *left, *right;
} Node;

Node* createNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	newNode->Ltag = newNode->Rtag = true;
	return newNode;
}

Node* insert(Node* root, int data){
	Node *ptr = root, *pnt = NULL;
	
	while( ptr ){
		pnt = ptr;
		if( data < ptr->data ){
			if( !ptr->Ltag ) ptr = ptr->left;
			else break;
		}else{
			if( !ptr->Rtag ) ptr = ptr->right;
			else break;
		}
	}
	
	Node* temp = createNode(data);
	if( !pnt ) root = temp;
	else if( data < pnt->data ){
		temp->left = pnt->left;
		pnt->left = temp;
		pnt->Ltag = false;
		temp->right = pnt;
	}else{
		temp->right = pnt->right;
		pnt->right = temp;
		pnt->Rtag = false;
		temp->left = pnt;
	}
	
	return root;
}

Node* successor(Node* root){
	if( root->Rtag ) return root->right;
	root = root->right;
	while( !root->Ltag ) root = root->left;
	return root;
}

void print(Node* root){
	if( !root ) return;
	Node* ptr = root;
	while( !ptr->Ltag ) ptr = ptr->left;
	while( ptr ){
		printf("%d ", ptr->data);
		ptr = successor(ptr);
	}
}

int main(int argc, char *argv[]) {
	Node* root = NULL;
	
	root = insert(root, 20);
	root = insert(root, 10);
	root = insert(root, 16);
	root = insert(root, 14);
	root = insert(root, 30);
	
	print(root);
	
	return 0;
}