#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

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

//void insert2(Node** rootRef, int data){
//	if( *rootRef == NULL ) { *rootRef = createNode(data); return; }
//	if( (*rootRef)->data < data ) insert2((&(*rootRef)->right), data);
//	else insert2((&(*rootRef)->left), data);
//	
//}

Node* maxNode(Node* root){
	if( root->right == NULL ) return root;
	return maxNode(root->right);
}

Node* minNode(Node* root){
	if( !root->left ) return root;
	return minNode(root->left);
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
// End of utilities

// Task 1 : build123
// This problem is easy with the global utilities so we won't provide any code

// Task 2 : size
int size(Node* root){
	if( !root ) return 0;
	return size(root->left) + size(root->right) + 1;
}

// Task 3 : maxDepth
// Utility for task 2
int max(int a, int b){
	return (a > b ? a : b);
}
// End of utility

int maxDepth(Node* root){
	if( !root ) return 0;
	return max(maxDepth(root->left)+1, maxDepth(root->right)+1);
}

// Task 4 : minValue
int minValue(Node* root){
	if( !root->left ) return root->data;
	return minValue(root->left);
}

// Accordingly, we may write maxValue
int maxValue(Node* root){
	if( !root->right ) return root->data;
	return maxValue(root->right);
}

// Task 5 : printTree
// Since this function is common for test and debugging, we'll write it as print()
void print(Node* root){
	if( !root ) return;
	print(root->left);
	printf("%d ", root->data);
	print(root->right);
}

// Task 6 : printPostorder
void printPostorder(Node* root){
	if( !root ) return;
	printPostorder(root->left);
	printPostorder(root->right);
	printf("%d ", root->data);
}

// Task 7 : hasPathSum
bool hasPathSum(Node* root, int sum){
	if( !root ) return sum == 0;
	int subSum = sum-root->data;
	return (hasPathSum(root->left, subSum) || hasPathSum(root->right, subSum));
}

// Task 8 : printPaths
// Utitlity functions for task 8
void printArray(int* arr, int N){
	for(int i = 0; i != N; i++) printf("%d ", arr[i]);
}

void printPathUtil(Node* root, int* path, int i){
	if( !root ) return;
	if( !root->left && !root->right ){
		printArray(path, i);
		printf("%d", root->data);
		putchar('\n');
		return;
	}
	
	path[i++] = root->data;
	printPathUtil(root->left, path, i);
	printPathUtil(root->right, path, i);
}
// Utility functions end

void printPaths(Node* root){
	int len = size(root);
	int path[len];
	
	printPathUtil(root, path, 0);
}

// Task 9 : mirror
// Utility for task 9
void swap(Node* root){
	if( !root ) return;
	Node* temp = root->right;
	root->right = root->left;
	root->left = temp;
}
// Utility ends

void mirror(Node* root){
	if( !root->left && !root->right ) return;

	mirror(root->left);
	mirror(root->right);
	swap(root);
}

// Task 10 : doubleTree
void doubleTree(Node* root){
	if( !root ) return;
	
	doubleTree(root->left);
	doubleTree(root->right);
	
	root = insert(root, root->data);
}

// Task 11 : sameTree
bool sameTree(Node* root1, Node* root2){
	if( !root1 && !root2  ) return true;
	if( root1 && root2 )
		return (root1->data == root2->data &&
			sameTree(root1->left, root2->left) &&
			sameTree(root1->right, root2->right));
	
	return false;
}

// Task 12 : countTrees

////#########################################
//int countTrees(int num){
//	if( num == 2 ) return 2;
//	if( num == 1 ) return 1;
//	
//	return countTrees(num-1) * (num-2) + num;
//}
////#########################################

// This answer is incorrect!

int countTrees(int num){
	if( num <= 1 ) return 1;
	int sum = 0;
	
	for(int root = 1; root <= num; root++){
		int left = countTrees(root-1);
		int right = countTrees(num-root);
		
		sum += left*right;
	}
	
	return sum;
}

// Task 13 : isBST -- version 1
bool isBST1(Node* root){
	if( !root || (!root->left && !root->right) ) return true;
	return isBST1(root->left) && isBST1(root->right)
		&& minValue(root) < root->data
		&& maxValue(root) >= root->data
		&& ( root->left ? maxValue(root->left) < root->data : true)
		&& ( root->right ? minValue(root->right) >= root->data : true);
}

// Task 14 : isBST -- version 2
bool isBSTUtil(Node* root, int min, int max){
	if( !root ) return true;
	return root->data <= max && root->data >= min
		&& isBSTUtil(root->left, min, root->data)
		&& isBSTUtil(root->right, root->data, max);
}

bool isBST2(Node* root){
	return isBSTUtil(root, INT_MIN, INT_MAX);
}

// Task 15 : treeToList
void printList(Node* head){
	if( head->right == head ) printf("%d", head->data);
	
	Node* temp = head->left;
	do{
		printf("%d ", head->data);
		head = head->right;
	}while( head != temp->right );
}

Node* tail(Node* head){
	if( !head ) return NULL;
	return head->left;
}

void join(Node* a, Node* b){
	a->right = b;
	b->left = a;
}

Node* append(Node* head1, Node* root, Node* head2){
	Node *rear1 = tail(head1), *rear2 = tail(head2);
	
	if( rear1 && rear2 ) {
		join(rear1, root);
		join(root, head2);
		join(rear2, head1);
	}else if( !rear1 || !rear2 ){
		if( !rear1 && rear2 ){
			join(root, head2);
			join(rear2, root);
			head1 = root;
		}else{
			join(rear1, root);
			join(root, head1);
		}
	}
	return head1;
}

Node* treeToList(Node* root){
	if( !root ) return NULL;
	if( !root->left && !root->right ){
		root->right = root;
		root->left = root;
		return root;
	}
	
	Node* alist = treeToList(root->left);
	Node* blist = treeToList(root->right);
	alist = append(alist, root, blist);
	
	return alist;
}

// Task 16 : Inorder Successor
Node* findNode(Node* root, int data){
	if( !root ) return NULL;
	
	if( root->data == data ) return root;
	else if( root->data < data ) return findNode(root->right, data);
	else return findNode(root->left, data);
}

Node* InorderSuccessor(Node* root, int key){
	Node* current = findNode(root, key);
	if( !current ) return NULL;
	if( current->right ) return minNode(current->right);
	
	Node *successor = NULL, *ancestor = root;
	while( ancestor != current ){
		if( ancestor->data > key ){
			successor = ancestor;
			ancestor = ancestor->left;
		}else ancestor = ancestor->right;
	}
	
	return successor;
}

// Task 17 : Inorder Predecessor
Node* InorderPredecessor(Node* root, int key){
	Node* current = findNode(root, key);
	if( !current ) return NULL;
	if( current->left ) return maxNode(current->left);
	
	Node *predecessor = NULL, *ancestor = root;
	while( ancestor != current ){
		if( ancestor->data < key ){
			predecessor = ancestor;
			ancestor = ancestor->right;
		}else ancestor = ancestor->left;
	}
	
	return predecessor;
}

// Task 18 : Copy Tree
Node* copy(Node* srcRoot, Node* dstRoot){
	if( !srcRoot ) return NULL;
	
	dstRoot = createNode(srcRoot->data);
	dstRoot->left = copy(srcRoot->left, dstRoot->left);
	dstRoot->right = copy(srcRoot->right, dstRoot->right);
	
	return dstRoot;
}

// Task 19 : Count Leaf Nodes
int deg0Count(Node* root){
	if( !root ) return 0;
	if( !root->left && !root->right ) return 1;
	return deg0Count(root->left) + deg0Count(root->right);
}

// Task 20 : Count Nodes With deg = 1
int deg1Count(Node* root){
	if( !root ) return 0;
	if( !root->left && root->right ) return deg1Count(root->right) + 1;
	else if( root->left && !root->right) return deg1Count(root->left) + 1;
	else return deg1Count(root->left) + deg1Count(root->right);
}

// Task 21 : Count Nodes With deg = 2
int deg2Count(Node* root){
	if( !root ) return 0;
	if( root->left && root->right ) return deg2Count(root->left) + deg2Count(root->right) + 1;
	return deg2Count(root->left) + deg2Count(root->right);
}

int main(int argc, char *argv[]) {
	Node* root = NULL;
	root = insert(root, 6);
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 5);
	root = insert(root, 14);
	root = insert(root, 11);
	root = insert(root, 17);
	root = insert(root, 18);
	
	printPaths(root);
	
//	printf("%d\n", deg0Count(root));
//	printf("%d\n", deg1Count(root));
//	printf("%d\n", deg2Count(root));

	return 0;
}