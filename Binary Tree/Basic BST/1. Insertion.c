#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *right, *left;
} Node;

Node* insert(Node*, int);
Node* CreateNode(int);
void insertion(Node**, int);
void PrintTree(Node*);

int main(){
	Node* root = NULL;
//	root = insert(root, 6);
//	root = insert(root, 3);
//	root = insert(root, 7);
//	root = insert(root, 1);
//	root = insert(root, 5);
//	root = insert(root, 8);
	
	insertion(&root, 6);
	insertion(&root, 3);
	insertion(&root, 7);
	insertion(&root, 1);
	insertion(&root, 5);
	insertion(&root, 8);
	
	PrintTree(root);
	
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

// There's another variant of insert function of type void

void insertion(Node** rootref, int data){
	if( *rootref == NULL ){
		*rootref = CreateNode(data);
		return;
	}else if( (*rootref)->data < data ){
		insertion(&(*rootref)->right, data);
	}
	else
		insertion(&(*rootref)->left, data);
}

void PrintTree(Node* root){
	if( root == NULL )
		return;
	else{
		PrintTree(root->left);
		printf("%d ", root->data);
		PrintTree(root->right);
	}
}