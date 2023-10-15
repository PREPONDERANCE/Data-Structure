#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *right, *left;
} Node;

Node* maxValue(Node*);
Node* CreateNode(int);
Node* insert(Node*, int);
Node* FindNode(Node*, int);
Node* InorderPredecessor(Node*, int);

int main(int argc, char *argv[]) {
	Node* root = NULL;
	root = insert(root, 12);
	root = insert(root, 5);
	root = insert(root, 3);
	root = insert(root, 7);
	root = insert(root, 1);
	root = insert(root, 9);
	root = insert(root, 20);
	root = insert(root, 16);
	root = insert(root, 25);
	root = insert(root, 13);
	root = insert(root, 17);
	root = insert(root, 22);
	root = insert(root, 21);
	root = insert(root, 23);
	root = insert(root, 30);
	root = insert(root, 26);
	
	if( InorderPredecessor(root, 13) )
		printf("%d", InorderPredecessor(root, 13)->data);
	else printf("No predecessor");
	
	return 0;
}

Node* maxValue(Node* root){
	if( root == NULL ) return NULL;
	if( root->right == NULL )
		return root;
	return maxValue(root->right);
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

Node* FindNode(Node* root, int data){
	if( root == NULL )  return NULL;
	if( root->data == data)  return root;
	if( root->data < data )
		return FindNode(root->right, data);
	return FindNode(root->left, data);
}

Node* InorderPredecessor(Node* root, int data){
	Node* current = FindNode(root, data);
	if( current == NULL )  return NULL;
	if( current->left ) return maxValue(current->left);
	
	Node* ancestor = root;
	Node* predecessor = NULL;
	while( ancestor != current ){
		if( ancestor->data < data ){
			predecessor = ancestor;
			ancestor = ancestor->right;
		}else ancestor = ancestor->left;
	}
	
	return predecessor;
}