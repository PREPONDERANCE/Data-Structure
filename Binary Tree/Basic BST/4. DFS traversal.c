// visit - reading/processing/printing some data in a node
// DFS is short for Depth-First-strategy, meaning visiting left subtree, right subtree, current root in a given sequence
// Preorder - DLR (D - data)
// Inorder - LDR
// Postorder - LRD

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *right, *left;
} Node;

Node* CreateNode(int);
Node* insert(Node*, int);
void PreOrder(Node*);
void InOrder(Node*);
void PostOrder(Node*);

int main(){
	Node* root = NULL;
	root = insert(root, 6);
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 5);
	root = insert(root, 1);
	root = insert(root, 3);
	root = insert(root, 12);
	root = insert(root, 8);
	root = insert(root, 15);
	root = insert(root, 10);
	root = insert(root, 9);
	
	PreOrder(root);  putchar('\n');
	InOrder(root);   putchar('\n');
	PostOrder(root); putchar('\n');
	
	return 0;
}

Node* CreateNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->right = newNode->left = NULL;
	return newNode;
}

Node* insert(Node* root, int data){
	if( root == NULL )
		return CreateNode(data);
	else if( root->data < data )
		root->right = insert(root->right, data);
	else root->left = insert(root->left, data);
	
	return root;
}

void PreOrder(Node* root){
	if( root ){
		printf("%d ", root->data);
		PreOrder(root->left);
		PreOrder(root->right);
	}
}

void InOrder(Node* root){
	if( root ){
		InOrder(root->left);
		printf("%d ", root->data);
		InOrder(root->right);
	}
}

void PostOrder(Node* root){
	if( root ){
		PostOrder(root->left);
		PostOrder(root->right);
		printf("%d ", root->data);
	}
}