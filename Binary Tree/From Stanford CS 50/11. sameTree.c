#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
	int data;
	struct Node *right, *left;
} Node;

Node* CreateNode(int);
Node* insert(Node*, int);
void print(Node*);
bool sameTree(Node*, Node*);

int main(){
	Node *a = NULL, *b = NULL;
	
	a = insert(a, 5);
	a = insert(a, 3);
	a = insert(a, 1);
	a = insert(a, 4);
	a = insert(a, 8);
	a = insert(a, 6);
	print(a); putchar('\n');
	
	b = insert(b, 5);
	b = insert(b, 3);
	b = insert(b, 1);
	b = insert(b, 4);
	b = insert(b, 8);
	//b = insert(b, 6);
	print(b); putchar('\n');
	
	sameTree(a, b) ? printf("same tree\n") : printf("not the same\n");
	
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

bool sameTree(Node* a, Node* b){
	if( !a && !b ) return true;
	if( !a && b || a && !b ) return false;
	if( a->data == b->data && sameTree(a->left, b->left) && sameTree(a->right, b->right) )
		return true;
	return false;
}