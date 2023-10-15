#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Global utility functions and definition
typedef struct Node{
	int data;
	struct Node *left, *right;
} Node;

Node* createNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

Node* insert(Node* root, int data){
	if( root == NULL ) return createNode(data);
	
	if( root->data < data) root->right = insert(root->right, data);
	else if( root->data >= data ) root->left = insert(root->left, data);
	
	return root;
}

Node* maxNode(Node* root){
	if( root->right == NULL ) return root;
	return maxNode(root->right);
}

Node* delete(Node* root, int key){
	if( root == NULL ) return NULL;
	
	if( root->data == key ){
		if( !root->left && !root->right ){
			free(root); return NULL;
		}else if( !root->left || !root->right ){
			if( !root->left ){
				Node* temp = root->right;
				free(root);
				return temp;
			}else{
				Node* temp = root->left;
				free(root);
				return temp;
			}
		}else if( root->left && root->right ){
			Node* temp = maxNode(root->left);
			int data = temp->data;
			root->left = delete(root->left, data);
			root->data = data;
			
			return root;
		}
	}else if( root->data < key ) root->right = delete(root->right, key);
	else root->left = delete(root->left, key);
	
	return root;
}

// Utility ends


// Answer for task 15
void join(Node* a, Node* b){
	a->right = b;
	b->left = a;
}

Node* append(Node* alist, Node* blist){
	if( !alist ) return blist; if( !blist ) return alist;
	Node *alast = alist->left, *blast = blist->left;
	
	join(alast, blist);
	join(blast, alist);
	
	return alist;
}

Node* treeToList(Node* root){
	if( !root ) return NULL;
	Node* alist = treeToList(root->left);
	Node* blist = treeToList(root->right);
	
	root->left = root;
	root->right = root;
	
	alist = append(alist, root);
	alist = append(alist, blist);
	
	return alist;
}

void print(Node* head){
	Node* current = head;
	
	while( current ){
		printf("%d ", current->data);
		current = current->right;
		if( current == head ) break;
	}
	
	putchar('\n');
}

int main(){
	Node* root = NULL;
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 1);
	root = insert(root, 3);
	root = insert(root, 5);
	
	Node* head = treeToList(root);
	print(head);
	
	return 0;
}