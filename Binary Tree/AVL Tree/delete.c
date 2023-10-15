#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
	int data, height;
	struct Node *right, *left;
} Node;

int max(int, int);
int height(Node*);
int balanced(Node*);
int minValue(Node*);
void preorder(Node*);
Node* CreateNode(int);
Node* leftrotate(Node*);
Node* rightrotate(Node*);
Node* insert(Node*, int);
Node* delete(Node*, int);

int main(){
	Node* root = NULL;
	root = insert(root, 9);
	root = insert(root, 5);
	root = insert(root, 10);
	root = insert(root, 0);
	root = insert(root, 6);
	root = insert(root, 11);
	root = insert(root, -1);
	root = insert(root, 1);
	root = insert(root, 2);
	
	printf("Preorder traversal of the constructed AVL tree is \n");
	preorder(root);
	
	root = delete(root, 10);
	
	printf("\nPreorder traversal after deletion of 10 \n");
	preorder(root);
	
	return 0;
}

int max(int a, int b){
	return (a > b) ? a : b;
}

int height(Node* root){
	if( root == NULL ) return -1;
	return root->height;
}

int balanced(Node* root){
	if( root == NULL ) return 0;
	return height(root->left) - height(root->right);
}

int minValue(Node* root){
	if( root->left == NULL ) return root->data;
	return minValue(root->left);
}

Node* righrotate(Node* root){
	Node* temp = root->left;
	Node* rem = temp->right;
	
	temp->right = root;
	root->left = rem;
	
	root->height = max(height(root->left), height(root->right))+1;
	temp->height = max(height(temp->left), height(temp->right))+1;
	
	return temp;
}

Node* CreateNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->right = newNode->left = NULL;
	newNode->height = 0;
	return newNode;
}

Node* leftrotate(Node* root){
	Node* temp = root->right;
	Node* rem = temp->left;
	
	temp->left = root;
	root->right = rem;
	
	root->height = max(height(root->left), height(root->right))+1;
	temp->height = max(height(temp->left), height(temp->right))+1;
	
	return temp;
}

Node* delete(Node* root, int key){
	if( root == NULL ) return NULL;
	if( root->data == key ){
		if( !root->left && !root->right ){
			free(root);
			return NULL;
		}else if( !root->left || !root->right ){
			if( !root->left ){
				Node* temp = root->right;
				free(root);
				return temp;
			}else {
				Node* temp = root->left;
				free(root);
				return temp;
			}
		}else{
			root->data = minValue(root->right);
			root->right = delete(root->right, root->data);
		}
	}else if( root->data < key )
		root->right = delete(root->right, key);
	else root->left = delete(root->left, key);
	
	root->height = max(height(root->left), height(root->right))+1;
	int balance = balanced(root);
	
	if( balance > 1 ){
		if( balanced(root->left) <= 0 ){
			root->left = leftrotate(root->left);
			return righrotate(root);
		}else return righrotate(root);
	}
	if( balance < -1 ){
		if( balanced(root->right) >= 0 ){
			root->right = righrotate(root->right);
			return leftrotate(root);
		}else return leftrotate(root);
	}
	
	return root;
}

Node* insert(Node* root, int data){
	if( root == NULL ) return CreateNode(data);
	if( root->data < data )
		root->right = insert(root->right, data);
	else root->left = insert(root->left, data);
	
	root->height = max(height(root->left), height(root->right))+1;
	int balance = balanced(root);
	
	if( balance > 1 ){
		if( data < root->left->data )
			return righrotate(root);
		else{
			root->left = leftrotate(root->left);
			return righrotate(root);
		}
	}
	if( balance < -1 ){
		if( data > root->right->data )
			return leftrotate(root);
		else{
			root->right = righrotate(root->right);
			return leftrotate(root);
		}
	}
	
	return root;
}

void preorder(Node* root){
	if( root ){
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}