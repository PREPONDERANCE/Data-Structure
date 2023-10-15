//#include <iostream>
//#include <stack>
//using namespace std;
//
//typedef struct Node{
//	int data;
//	struct Node *right, *left;
//	bool state;
//} Node;
//
//Node* CreateNode(int);
//Node* insert(Node*, int);
//Node* minValue(Node*);
//void print(Node*);
//Node* Inordersuccessor(Node*, int);
//
//int main(){
//	Node* root = NULL;
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
//	print(root);
//	cout << endl;
//
////	int number;
////	cin >> number;
//	if( Inordersuccessor(root, 14) ) cout << "Successor is " << Inordersuccessor(root, 14)->data << endl;
//	else  cout << "No such successor" << endl;
//	
//	return 0;
//}
//
//Node* CreateNode(int data){
//	Node* newNode = (Node*)malloc(sizeof(Node));
//	newNode->data = data;
//	newNode->left = newNode->right = NULL;
//	newNode->state = false;
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
//Node* minValue(Node* root){
//	if( root->left == NULL ) return root;
//	else  return minValue(root->left);
//}
//
//void print(Node* root){
//	if( root ){
//		print(root->left);
//		printf("%d ", root->data);
//		print(root->right);
//	}
//}
//
//Node* Inordersuccessor(Node* root, int key){
//	static stack<Node*> s;
//	
//	if( root == NULL )  return NULL;
//	
//	if( root->data == key ){
//		if( root->right )
//			return minValue(root->right);
//		else{
//			while( !s.empty() && s.top()->state )
//				s.pop();
//			if( s.empty() )  return NULL;
//			return s.top();
//		}
//	}else if( root->data < key ){
//		s.push(root);
//		root->state = true;
//		return Inordersuccessor(root->right, key);
//	}else{
//		s.push(root);
//		return Inordersuccessor(root->left, key);
//	}
//}
//
//// This code example is my understanding of the problem.
//// My basic logic is : like the inorder traversal we've written before, we can apply a tag to identify if a node has already been traversed, which inspires the boolean variable in the tree node.
//// In the course of binary search to locate the particular node, we push all the nodes that are compared with the particular node into the stack and if the current data is less than the desired one, we tag this node as traversed.
//// When we reach this particular node, there're 2 cases to consider.
//
//// case 1 : If this particular node is in the root-like position, it's natural simply to find the min value in its right subtree due to the property of BST.
//// case 2 : If this node bears no right subtree, then locate the node in the stack with its boolean value being false.



#include <iostream>
using namespace std;

typedef struct Node{
	int data;
	struct Node *right, *left;
	bool state;
} Node;

Node* minValue(Node*);
Node* CreateNode(int);
Node* insert(Node*, int);
Node* FindNode(Node*, int);
Node* InorderSuccessor(Node*, int);

int main(){
	Node* root = NULL;
	root = insert(root, 12);
	root = insert(root, 5);
	root = insert(root, 3);
	root = insert(root, 7);
	root = insert(root, 1);
	root = insert(root, 9);
	root = insert(root, 20);
	root = insert(root, 16);
	root = insert(root, 25);
	root = insert(root, 13);
	root = insert(root, 17);
	root = insert(root, 22);
	root = insert(root, 21);
	root = insert(root, 23);
	root = insert(root, 30);
	root = insert(root, 26);
	
	if( InorderSuccessor(root, 4) )  cout << InorderSuccessor(root, 4)->data << endl;
	else  cout << "no successor";
	
	return 0;
}

Node* minValue(Node* root){
	if( root == NULL ) return NULL;
	if( root->left == NULL ) return root;
	return minValue(root->left);
}

Node* CreateNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	newNode->state = false;
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

Node* FindNode(Node* root, int data){
	if( root == NULL ) return NULL;
	if( root->data == data )  return root;
	else if( root->data < data )
		return FindNode(root->right, data);
	return FindNode(root->left, data);
}

Node* InorderSuccessor(Node* root, int data){
	Node* current = FindNode(root, data);
	if( current == NULL ) return NULL;
	if( current->right ) return minValue(current->right);
	
	Node* successor = NULL;
	Node* ancestor = root;
	
	while( ancestor != current ){
		if( ancestor->data > data ){
			successor = ancestor;
			ancestor = ancestor->left;
		}else ancestor = ancestor->right;
	}
	
	return successor;
}

// Explanation for this block of codes

// Instead of locating the desired node inside the function, we compile an external function to achieve this.
// Remedy for case 1 is the same as my version of codes
// For case 2 : the core logic is very similar, the only difference being that my version of funcion utilize a boolean variable to tag the node while this example takes advantage of 2 extra nodes.
// Node ancestor is for traversal while the statement of successor = ancestor is only satisfied on the premise that the data ancestor hold is greater than that in node current.

// To conclude, current node must be in the left subtree of its successor

// Advice : for problems concerning BST, do consider its most distinct feature - data in the left are lee than root while those in the right are greater