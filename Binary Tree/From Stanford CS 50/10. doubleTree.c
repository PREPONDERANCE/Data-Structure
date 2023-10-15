#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *right, *left;
} Node;

Node* CreateNode(int);
Node* insert(Node*, int);
void print(Node*);
void doubleTree(Node*);

int main(){
	Node* root = NULL;
	root = insert(root, 2);
	root = insert(root, 1);
	root = insert(root, 3);
	print(root); putchar('\n');
	
	doubleTree(root);
	print(root);
	
	return 0;
}

Node* CreateNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->right = newNode->left = NULL;
	return newNode;
}

Node* insert(Node* root, int data){
	if( root == NULL ) return CreateNode(data);
	if( root->data < data )
		root->right = insert(root->right, data);
	else root->left = insert(root->left, data);
	return root;
}

void print(Node* root){
	if( root == NULL )
		return;
	print(root->left);
	printf("%d ", root->data);
	print(root->right);
}

void doubleTree(Node* root){
	if( root == NULL )
		return;
	
	doubleTree(root->left);
	doubleTree(root->right);
	
	root = insert(root, root->data);
}