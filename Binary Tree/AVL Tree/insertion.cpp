#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <queue>
using namespace std;

typedef struct Node{
	int data;
	struct Node *right, *left;
}Node;

int abs(int);
int max(int, int);
int height(Node*);
bool ifbalanced(Node*);
Node* CreateNode(int);
Node* insert(Node*, int*, int);
Node* insertutil1(Node*, int);
Node* insertutil2(Node*, int*, int, int);
void swap(int*, int, int);
int partition(int*, int, int);
void quicksort(int*, int, int);
void printarray(int*, int);
void levelorder(Node*);
void inorder(Node*);
void postorder(Node*);

int main(int argc, char *argv[]) {
	Node* root = NULL;
	int arr[] = {14, 17, 11, 7, 53, 4, 13, 12, 8, 60, 19, 16, 20};
	int size = sizeof(arr)/sizeof(arr[0]);
	quicksort(arr, 0, size-1);
	
	root = insert(root, arr, size);
	levelorder(root);
	cout << endl;
	
	if( ifbalanced(root) )
		printf("BST is AVL\n");
	
	inorder(root); cout << endl;
	postorder(root);
	
	return 0;
}

int abs(int x){
	return (x > 0) ? x : -x;
}

int max(int a, int b){
	return (a > b) ? a : b;
}

int height(Node* root){
	if( root == NULL )  return -1;
	return max(height(root->left), height(root->right))+1;
}

bool ifbalanced(Node* root){
	if( root == NULL ) return true;
	if( abs(height(root->left) - height(root->right)) <= 1 && ifbalanced(root->right) && ifbalanced(root->left) )
		return true;
	return false;
}

Node* CreateNode(int data){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->right = newNode->left = NULL;
	return newNode;
}

Node* insertutil1(Node* root, int data){
	if( root == NULL ) return CreateNode(data);
	if( root->data < data )
		root->right = insertutil1(root->right, data);
	else root->left = insertutil1(root->left, data);
	return root;
}

Node* insertutil2(Node* root, int* arr, int l, int r){
	if( l <= r ){
		int m = (l+r)/2;
		root = insertutil1(root, arr[m]);
		insertutil2(root, arr, l, m-1);
		insertutil2(root, arr, m+1, r);
	}
	return root;
}

Node* insert(Node* root, int* arr, int n){
	return insertutil2(root, arr, 0, n-1);
}

void swap(int v[], int i, int j){
	int temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int partition(int v[], int l, int r){
	int pIndex = l;
	
	for(int i = l; i < r; i++)
		if( v[i] < v[r] ){
			swap(v, i, pIndex);
			pIndex++;
		}
	swap(v, pIndex, r);
	
	return pIndex;
}

void quicksort(int v[], int l, int r){
	if( l < r ){
		int pivot = partition(v, l, r);
		quicksort(v, l, pivot-1);
		quicksort(v, pivot+1, r);
	}
}

void printarray(int v[], int n){
	for(int i = 0; i < n; i++)
		printf("%d ", v[i]);
	putchar('\n');
}

void levelorder(Node* root){
	queue<Node*> q;
	q.push(root);
	
	while( !q.empty() ){
		printf("%d ", q.front()->data);
		if( q.front()->left )  q.push(q.front()->left);
		if( q.front()->right ) q.push(q.front()->right);
		q.pop();
	}
}

void inorder(Node* root){
	if( root ){
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

void postorder(Node* root){
	if( root ){
		postorder(root->left);
		postorder(root->right);
		cout << root->data << ' ';
	}
}