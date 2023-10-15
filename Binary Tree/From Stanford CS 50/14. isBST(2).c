#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
	int data;
	struct Node *right, *left;
} Node;

Node* CreateNode(int);
Node* insert(Node*, int);
bool isBST(Node*);
bool isBSTutil(Node*, int, int);

int main(){
	Node* root = NULL;
	root = insert(root, 6);
	root = insert(root, 3);
	root = insert(root, 1);
	root = insert(root, 4);
	root = insert(root, 8);
	root = insert(root, 7);
//	Node* temp = root;
//	temp->right->right = CreateNode(7);
	
	if( isBST(root) ) printf("is BST\n");
	else printf("is not BST\n");
	
	return 0;
}

Node* CreateNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

Node* insert(Node* root, int data){
	if( root == NULL ) return CreateNode(data);
	if( root->data < data )
		root->right = insert(root->right, data);
	else root->left = insert(root->left, data);
	return root;
}

bool isBST(Node* root){
	return isBSTutil(root, INT_MIN, INT_MAX);
}

bool isBSTutil(Node* root, int min, int max){
	if( root == NULL )  return true;
	if( root->data > min && root->data < max && isBSTutil(root->left, min, root->data) && isBSTutil(root->right, root->data, max) )
		return true;
	return false;
}