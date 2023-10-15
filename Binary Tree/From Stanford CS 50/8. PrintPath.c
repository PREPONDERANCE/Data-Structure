#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *right, *left;
} Node;

Node* CreateNode(int);
Node* insert(Node*, int);
void PrintArray(int*, int);
void PrintPath(Node*);
void PrintTreeRecur(Node*, int*, int);

int main(){
	Node* root = NULL;
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 1);
	root = insert(root, 3);
	root = insert(root, 5);
	
	PrintPath(root);
	
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

void PrintArray(int *arr, int n){
	for(int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}

void PrintPath(Node* root){
	int path[1000];
	PrintTreeRecur(root, path, 0);
}

void PrintTreeRecur(Node* root, int *path, int len){
	if( root == NULL ) return;
	path[len++] = root->data;
	
	if( root->left == NULL && root->right == NULL ){
		PrintArray(path, len);
		return;
	}
	
	PrintTreeRecur(root->left, path, len);
	PrintTreeRecur(root->right, path, len);
}