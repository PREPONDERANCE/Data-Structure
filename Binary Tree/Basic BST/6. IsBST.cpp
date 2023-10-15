// To check if a binary tree is a BST, keep in mind of this concept that we should always look at a BST with the awareness of group or recursion
// To be more specific, the basic logic for this problem will be we recursively check if all the data in left subtree are less than the root while those in right subtree are greater than the root, from which we develop the first approach.



//#include <iostream>
//using namespace std;
//
//typedef struct Node{
//	int data;
//	Node *right, *left;
//} Node;
//
//Node* CreateNode(int);
//Node* insert(Node*, int);
//bool isSubtreeless(Node*, int);
//bool isSubtreeGreater(Node*, int);
//bool isBST(Node*);
//
//int main(int argc, char *argv[]) {
//	
//}
//
//Node* CreateNode(int data){
//	Node* newNode = new Node;
//	newNode->data = data;
//	newNode->left = newNode->right = NULL;
//	return newNode;
//}

//Node* insert(Node* root, int data){
//	if( root == NULL )
//		return CreateNode(data);
//	else if( root->data < data )
//		root->right = insert(root->right, data);
//	else root->left = insert(root->left, data);
//	
//	return root;
//}
//
//bool isSubtreeless(Node* root, int value){
//	if( root == NULL ) return true;
//	if( root->data < value && isSubtreeless(root->left, value) && isSubtreeless(root->right, value))
//		return true;
//	return false;
//}
//
//bool isSubtreeGreater(Node* root, int value){
//	if( root == NULL ) return true;
//	if( root->data > value && isSubtreeGreater(root->left, value) && isSubtreeGreater(root->right, value))
//		return true;
//	return false;
//}
//
//bool isBST(Node* root){
//	if( root == NULL ) return true;
//	if(isSubtreeGreater(root->right, root->data) && isSubtreeless(root->left, root->data) && isBST(root->left) && isBST(root->right) )
//		return true;
//	return false;
//}


// In this method, we check every node using recursion
// isSubtreeLess function works like this : it compare every node of the left subtree with the root, in which process, recursion is presented
// After check through the left and right subtree ( compare the data with the root ), we change the root respectively to root->left and root->right.




#include <iostream>
#include <limits.h>
using namespace std;

typedef struct Node{
	int data;
	Node *right, *left;
} Node;

Node* CreateNode(int);
Node* insert(Node*, int);
bool isBSTutil(Node*, int, int);
bool isBST(Node*);

int main(){
	Node* root = NULL;
	root = insert(root, 6);
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 5);
	root = insert(root, 1);
	root = insert(root, 3);
	root = insert(root, 12);
	root = insert(root, 8);
	root = insert(root, 15);
	root = insert(root, 10);
	root = insert(root, 9);
	
//	Node* temp = root->right->left->right;
//	temp->right = CreateNode(9);
	
	cout << (isBST(root) ? "is BST" : "is not BST") << endl;
	
	return 0;
}

Node* CreateNode(int data){
	Node* newNode = new Node;
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

bool isBSTutil(Node* root, int minValue, int maxValue){
	if( root == NULL ) return true;
	if( root->data > minValue && root->data < maxValue && isBSTutil(root->left, minValue, root->data) && isBSTutil(root->right, root->data, maxValue))
		return true;
	return false;
}

bool isBST(Node* root){
	return isBSTutil(root, INT_MIN, INT_MAX);
}

// This method takes advantage of the concept of range.
// For a root node, its data range is infinity to infinity, and the range of its left child will be infinity to root->data, and so forth, we can make certain the range of every node.



//#include <iostream>
//#include <stack>
//using namespace std;
//
//typedef struct Node{
//	int data;
//	Node *right, *left;
//} Node;
//
//Node* CreateNode(int);
//Node* insert(Node*, int);
//bool isBST(Node*);
//
//int main(int argc, char *argv[]) {
//	Node* root = NULL;
//	root = insert(root, 6);
//	root = insert(root, 4);
//	root = insert(root, 2);
//	root = insert(root, 5);
//	root = insert(root, 1);
//	root = insert(root, 3);
//	root = insert(root, 12);
//	root = insert(root, 8);
//	root = insert(root, 15);
//	root = insert(root, 10);
//	root = insert(root, 9);
//	
////	Node* temp = root->right->left->right;
////	temp->right = CreateNode(9);
//	
//	cout << (isBST(root) ? "is BST" : "is not BST") << endl;
//
//	return 0;
//}
//
//Node* CreateNode(int data){
//	Node* newNode = new Node;
//	newNode->data = data;
//	newNode->left = newNode->right = NULL;
//	return newNode;
//}
//
//Node* insert(Node* root, int data){
//	if( root == NULL )
//		return CreateNode(data);
//	else if( root->data < data )
//		root->right = insert(root->right, data);
//	else root->left = insert(root->left, data);
//	
//	return root;
//}
//
//bool isBST(Node* root){
//	static stack<int> s;
//	static bool isbst = true;
//	if( root ){
//		isBST(root->left);
//		if( !s.empty() )
//			if( root->data < s.top() )
//				isbst = false;
//		s.push(root->data);
//		isBST(root->right);
//	}
//	return isbst;
//}

// This method uses DFS-InOrder sequence
// To be exact, we push every element of the tree into a stack using inorder sequence and in the same time, before we push a new element inside, we compare the current top element in the stack with the new element, and if the new one is less than the one in the stack, we can come to the conclusion that this is not a BST