// Basic logic and definition :
// 1. Height : number of edges from node x to a leaf ( notice the word edge : broadly speaking, edge means the number of arrows of the longest path)
// 2. Logic : 

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *right, *left;
} Node;

Node* insert(Node*, int);
Node* CreateNode(int);
int FindHeight(Node*);
int max(int, int);

int main(){
	Node* root = NULL;
	root = insert(root, 5);
	root = insert(root, 2);
	root = insert(root, 7);
	root = insert(root, 6);
	root = insert(root, 1);
	
	printf("Height of tree is %d\n", FindHeight(root));
	
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

int FindHeight(Node* root){
	if( root == NULL )
		return -1;
	return max( FindHeight(root->left), FindHeight(root->right) ) + 1;
}

int max(int a, int b){
	return (a > b) ? a : b;
}