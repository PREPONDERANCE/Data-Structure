#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
	int data;
	struct Node *right, *left;
} Node;

Node* CreateNode(int);
Node* insert(Node*, int);
bool isless(Node*, int);
bool isgreater(Node*, int);
bool isBST(Node*);

int main(){
	Node* root = NULL;
	root = insert(root, 6);
	root = insert(root, 3);
	root = insert(root, 1);
	root = insert(root, 4);
	root = insert(root, 8);
	//root = insert(root, 7);
	Node* temp = root;
	temp->right->right = CreateNode(7);
	
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

bool isless(Node* root, int value){
	if( root == NULL )  return true;
	if( root->data < value && isless(root->left, value) && isless(root->right, value) )
		return true;
	return false;
}

bool isgreater(Node* root, int value){
	if( root == NULL )  return true;
	if( root->data > value && isgreater(root->left, value) && isgreater(root->right, value) )
		return true;
	return false;
}

bool isBST(Node* root){
	if( root == NULL ) return true;
	if( isless(root->left, root->data) && isgreater(root->right, root->data) && isBST(root->left) && isBST(root->right) )
		return true;
	return false;
}