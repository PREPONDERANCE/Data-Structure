// My codes for insert a node in AVL tree
// Saves more memory at the cost of more time consumption
// In every insertion, we check if the tree is balanced by way of recursing down the tree each time the function is invoked, which takes up a lot more time

//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//
//typedef struct Node{
//	int data;
//	struct Node *right, *left;
//} Node;
//
//int abs(int);
//int max(int, int);
//int height(Node*);
//int difference(Node*);
//bool ifbalanced(Node*);
//void postorder(Node*);
//Node* CreateNode(int);
//Node* leftrotate(Node*);
//Node* rightrotate(Node*);
//Node* insert(Node*, int);
//
//int main(){
//	Node* root = NULL;
//	root = insert(root, 14); root = insert(root, 17); root = insert(root, 11);
//	root = insert(root, 7); root = insert(root, 53); root = insert(root, 4);
//	root = insert(root, 13); root = insert(root, 12); root = insert(root, 8);
//	root = insert(root, 60); root = insert(root, 19); root = insert(root, 16);
//	root = insert(root, 20);
//	
//	postorder(root);
//	
//	return 0;
//}
//
//int abs(int x){
//	return (x > 0) ? x : -x;
//}
//
//int max(int a, int b){
//	return (a > b) ? a : b;
//}
//
//int height(Node* root){
//	if( root == NULL )  return -1;
//	return max(height(root->left), height(root->right))+1;
//}
//
//int difference(Node* root){
//	if( root == NULL ) return 0;
//	return height(root->left) - height(root->right);
//}
//
//bool ifbalanced(Node* root){
//	if( root == NULL ) return true;
//	if( abs(difference(root)) <= 1 && ifbalanced(root->left) && ifbalanced(root->right) )
//		return true;
//	return false;
//}
//
//Node* CreateNode(int data){
//	Node* newNode = (Node*)malloc(sizeof(Node));
//	newNode->data = data;
//	newNode->left = newNode->right = NULL;
//	return newNode;
//}
//
//Node* rightrotate(Node* root){
//	Node* temp = root->left;
//	Node* rem = temp->right;
//	
//	temp->right = root;
//	root->left = rem;
//	
//	return temp;
//}
//
//Node* leftrotate(Node* root){
//	Node* temp = root->right;
//	Node* rem = temp->left;
//	
//	temp->left = root;
//	root->right = rem;
//	
//	return temp;
//}
//
//Node* insert(Node* root, int data){
//	if( root == NULL ) return CreateNode(data);
//	if( root->data < data )
//		root->right = insert(root->right, data);
//	else root->left = insert(root->left, data);
//	
//	if( !ifbalanced(root) ){
//		if( difference(root) > 1 ){
//			if( data < root->left->data )
//				return rightrotate(root);
//			else{
//				root->left = leftrotate(root->left);
//				return rightrotate(root);
//			}
//		}else if( difference(root) < -1 ){
//			if( data > root->right->data )
//				return leftrotate(root);
//			else{
//				root->right = rightrotate(root->right);
//				return leftrotate(root);
//			}
//		}
//	}
//	
//	return root;
//}
//
//void postorder(Node* root){
//	if( root ){
//		printf("%d ", root->data);
//		postorder(root->left);
//		postorder(root->right);
//	}
//}



// In this code example, we add variabel height into the structure of node to store the current height of each tree, which brings up the advantage of saving more time on the premise that we update the height each time a rotation is needed.



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
Node* CreateNode(int);
Node* insert(Node*, int);
Node* leftrotate(Node*);
Node* rightrotate(Node*);
void postorder(Node*);

int main(){
	Node* root = NULL;
	root = insert(root, 14); root = insert(root, 17); root = insert(root, 11);
	root = insert(root, 7); root = insert(root, 53); root = insert(root, 4);
	root = insert(root, 13); root = insert(root, 12); root = insert(root, 8);
	root = insert(root, 60); root = insert(root, 19); root = insert(root, 16);
	root = insert(root, 20);
	
	postorder(root);
	
	return 0;
}

int max(int a, int b){
	return (a > b) ? a : b;
}

int height(Node* root){
	if( root == NULL )  return -1;
	return root->height;
}

int balanced(Node* root){
	if( root == NULL ) return 0;
	return height(root->left) - height(root->right);
}

Node* CreateNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->height = 0;
	newNode->right = newNode->left = NULL;
	return newNode;
}

void postorder(Node* root){
	if( root ){
		printf("%d ", root->data);
		postorder(root->left);
		postorder(root->right);
	}
}

Node* rightrotate(Node* root){
	Node* temp = root->left;
	Node* rem = temp->right;
	
	temp->right = root;
	root->left = rem;
	
	root->height = max(height(root->left), height(root->right))+1;
	temp->height = max(height(temp->left), height(temp->right))+1;
	
	return temp;
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

Node* insert(Node* root, int data){
	if( root == NULL ) return CreateNode(data);
	if( root->data < data )
		root->right = insert(root->right, data);
	else root->left = insert(root->left, data);
	
	root->height = max(height(root->left), height(root->right))+1;
	int balance = balanced(root);
	
	if( balance > 1 ){
		if( data < root->left->data )
			return rightrotate(root);
		else{
			root->left = leftrotate(root->left);
			return rightrotate(root);
		}
	}
	if( balance < -1 ){
		if( data > root->right->data )
			return leftrotate(root);
		else{
			root->right = rightrotate(root->right);
			return leftrotate(root);
		}
	}
	
	return root;
}