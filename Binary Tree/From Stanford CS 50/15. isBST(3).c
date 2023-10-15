#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
	int data;
	struct Node *right, *left;
} Node;

Node* CreateNode(int);
Node* insert(Node*, int);
bool isBST(Node*);
int minValue(Node*);
int maxValue(Node*);

int main(){
	Node* root = NULL;
	root = insert(root, 6);
	root = insert(root, 3);
	root = insert(root, 1);
	root = insert(root, 4);
	root = insert(root, 8);
	//root = insert(root, 7);
	Node* temp = root;
	temp->left->right = CreateNode(7);
	
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

int minValue(Node* root){
	if( root->left == NULL )
		return root->data;
	return minValue(root->left);
}

int maxValue(Node* root){
	if( root->right == NULL )
		return root->data;
	return maxValue(root->right);
}
//
//bool isBST(Node* root){
//	if( root == NULL ) return true;
//	if( root->left && maxValue(root->left) > root->data || root->right && minValue(root->right) < root->data )
//		return false;
//	if( !isBST(root->left) || !isBST(root->right) )
//		return false;
//	return true;
//}

bool isBST(struct Node* node) {
	if (node==NULL) return(true);
	// false if the min of the left is > than us
	if (node->left!=NULL && minValue(node->left) > node->data)
		return(false);
	// false if the max of the right is <= than us
	if (node->right!=NULL && maxValue(node->right) <= node->data)
		return(false);
	// false if, recursively, the left or right is not a BST
	if (!isBST(node->left) || !isBST(node->right))
		return(false);
	// passing all that, it's a BST
	return(true);
}
