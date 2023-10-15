// Deletion in BST can be categorized into 3 classes
// case 1 : delete a leaf node
// case 2 : delete a node with one chile
// case 3 : delete a node with 2 children

// For case 1, we simply need to return NULL when the desired node is located
// For case 2, we need to return root->left or root->right and free root
// For case 3, the task we're confronting is that this node has to be deleted while maintaining the tree as BST
// Considering the property of BST, we can first replace the data with the minimum data in the right subtree and then locate this minimum data and delete that node.
// Reason : all the data in the right subtree are greater than those in the left, according to which, the replacement won't harm the original left BST
// Since we choose the smallest in the right subtree, the remant data of right subtree is greater than it, which will do no harm as well to right BST.


#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *right, *left;
} Node;

Node* CreateNode(int);
Node* insert(Node*, int);
Node* delete(Node*, int);
int minValue(Node*);
void print(Node*);

int main(){
	Node* root = NULL;
//	root = insert(root, 12);
//	root = insert(root, 5);
//	root = insert(root, 3);
//	root = insert(root, 7);
//	root = insert(root, 1);
//	root = insert(root, 9);
//	root = insert(root, 20);
//	root = insert(root, 16);
//	root = insert(root, 25);
//	root = insert(root, 13);
//	root = insert(root, 17);
//	root = insert(root, 22);
//	root = insert(root, 21);
//	root = insert(root, 23);
//	root = insert(root, 30);
//	root = insert(root, 26);
//	
//	print(root);
//	putchar('\n');
//	print(delete(root, 35));
	
	
	root = insert(root, 20);
	root = insert(root, 10);
	root = insert(root, 16);
	root = insert(root, 14);
	
	print(delete(root, 20));
	
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
	else root->left = insert(root->left, data);
	
	return root;
}

int minValue(Node* root){
	if( root->left == NULL ) return root->data;
	else  return minValue(root->left);
}

Node* delete(Node* root, int key){
	if( root == NULL )
		return root;
	
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
		}else {
			root->data = minValue(root->right);
			root->right = delete(root->right, root->data);
		}
	}else if( root->data < key )
		root->right = delete(root->right, key);
	else
		root->left = delete(root->left, key);
	
	return root;
}

void print(Node* root){
	if( root ){
		print(root->left);
		printf("%d ", root->data);
		print(root->right);
	}
}