// BFS is short for Breadth-First-Strategy, also known as level order.
// BFS traversal goes from one level to another, printing all the data at the same level brefore going on to the next

#include <iostream>
#include <queue>
using namespace std;

typedef struct Node{
	int data;
	Node *right, *left;
} Node;

Node* CreateNode(int);
Node* insert(Node*, int);
void levelorder(Node*);

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
	
	levelorder(root);
	
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

void levelorder(Node* root){
	if( root == NULL )
		return;
	queue<Node*> q;
	q.push(root);
	
	while( !q.empty() ){
		Node* current = q.front();
		if( current->left ) q.push(current->left);
		if( current->right ) q.push(current->right);
		cout << current->data << ' ';
		q.pop();
	}
}