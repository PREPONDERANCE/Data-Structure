#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *right, *left;
} Node;

Node* insert(Node*, int);
Node* CreateNode(int);
int minValue(Node*);
int maxValue(Node*);

int main(){
	Node* root = NULL;
	root = insert(root, 5);
	root = insert(root, 2);
	root = insert(root, 7);
	root = insert(root, 6);
	root = insert(root, 1);
	
	printf("min value is %d max value is %d\n", minValue(root), maxValue(root));
	
	return 0;
}

Node* CreateNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

Node* insert(Node* root, int data){
	if( root == NULL )
		return CreateNode(data);
	else if( root->data < data )
		root->right = insert(root->right, data);
	else
		root->left = insert(root->left, data);
	
	return root;
}

int minValue(Node* root){
	if( root->left == NULL )
		return root->data;
	return minValue(root->left);
}
// The basic logic is we keep recursively moving down to the left subtree until there's no more branch
// ( As of basic property of BST, this logic is relatively easy and maxValue is approximately the same)

int maxValue(Node* root){
	if( root->right == NULL )
		return root->data;
	return maxValue(root->right);
}