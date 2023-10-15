#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
	int data;
	bool status;
	struct Node *right, *left, *parent;
} Node;

void inorder(Node*);
void leftrotate(Node*);
void rightrotate(Node*);
Node* CreateNode(int);
Node* fixup(Node*, Node*);
Node* insert(Node*, Node*);

int main(){
	Node* root = NULL;
	int n = 11;
	int a[] = {10, 18, 7, 15, 16, 25, 40, 60, 2, 1, 70};
	
	for(int i = 0; i < n; i++){
		Node* temp = CreateNode(a[i]);
		root = insert(root, temp);
		root = fixup(root, temp);
	}
	
	inorder(root);
	
	return 0;
}

Node* CreateNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->left = newNode->right = newNode->parent = NULL;
	newNode->status = false;
	return newNode;
}

Node* insert(Node* root, Node* temp){
	if( root == NULL )  return temp;
	if( root->data < temp->data ){
		root->right = insert(root->right, temp);
		root->right->parent = root;
	}else{
		root->left = insert(root->left, temp);
		root->left->parent = root;
	}
	return root;
}

Node* fixup(Node* root, Node* temp){
	if( root == temp ){
		root->status = true;
		return root;
	}
	
	Node* parent_pt = temp->parent;
	Node* grandparent = temp->parent->parent;
	
	if( !temp->status && !parent_pt->status ){
		if( parent_pt == grandparent->right ){
			if( !grandparent->left || grandparent->left->status ){
				if( temp == parent_pt->left ){
					rightrotate(parent_pt);
					parent_pt = temp;
				}
				leftrotate(grandparent);
				parent_pt->status = !parent_pt->status;
				parent_pt->left->status = !parent_pt->left->status;
				if( grandparent == root ) root = parent_pt;
			}else{
				Node* uncle_pt = grandparent->left;
				uncle_pt->status = !uncle_pt->status;
				parent_pt->status = !parent_pt->status;
				if( grandparent != root ){
					grandparent->status = !grandparent->status;
					root = fixup(root, grandparent);
				}
			}
		}else{
			if( !grandparent->right || grandparent->right->status ){
				if( temp == parent_pt->right ){
					leftrotate(parent_pt);
					parent_pt = temp;
				}
				rightrotate(grandparent);
				parent_pt->status = !parent_pt->status;
				parent_pt->right->status = !parent_pt->right->status;
				if( grandparent == root ) root = parent_pt;
			}else{
				Node* uncle_pt = grandparent->right;
				uncle_pt->status = !uncle_pt->status;
				parent_pt->status = !parent_pt->status;
				if( grandparent != root ){
					grandparent->status = !grandparent->status;
					root = fixup(root, grandparent);
				}
			}
		}
	}

	return root;
}

void leftrotate(Node* root){
	Node* temp = root->right;
	Node* rem = temp->left;
	
	temp->left = root;
	root->right = rem;
	
	if( root->parent ){
		temp->parent = root->parent;
		if( root->data > temp->parent->data )
			temp->parent->right = temp;
		else temp->parent->left = temp;
	}
	if( !root->parent ) temp->parent = NULL;
	
	root->parent = temp;
	if( rem ) rem->parent = root;
}

void rightrotate(Node* root){
	Node* temp = root->left;
	Node* rem = temp->right;
	
	temp->right = root;
	root->left = rem;
	
	if( root->parent ){
		temp->parent = root->parent;
		if( root->data < temp->parent->data )
			temp->parent->left = temp;
		else temp->parent->right = temp;
	}
	if( !root->parent )  temp->parent = NULL;
	
	root->parent = temp;
	if( rem ) rem->parent = root;
}

void inorder(Node* root){
	if( root ){
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}