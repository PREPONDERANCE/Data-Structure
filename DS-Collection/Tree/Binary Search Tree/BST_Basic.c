#include <stdio.h>
#include <stdlib.h>

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

Node* search(Node* root, int key){
	if( root == NULL ) return NULL;
	
	if( root->data == key ) return createNode(root->data);
	else if( root->data < key ) return (search(root->right, key) ? createNode(search(root->right, key)->data) : NULL);
	else return (search(root->left, key) ? createNode(search(root->left, key)->data) : NULL);
	
	return NULL;
}

int max(int a, int b){
	return (a > b) ? a : b;
}

int height(Node* root){
	if( !root ) return 0;
	return max(height(root->left)+1, height(root->right)+1);
}

int count(Node* root){
	if( !root ) return 0;
	return count(root->left) + count(root->right) + 1;
}

void print(Node* root){
	if( root == NULL ) return;
	print(root->left);
	printf("%d ", root->data);
	print(root->right);
}

// Level order traversal
void TraversalUtil(Node* root, Node** arr){
	int i = 0, j = 0;
	arr[i++] = root;
	
	while( i != j ){
		Node* current = arr[j++];
		if( current->left )	arr[i++] = current->left;
		if( current->right ) arr[i++] = current->right;
		printf("%d ", current->data);
	}
}

void LevelOrderTraversal(Node* root){
	Node* arr[count(root)];
	TraversalUtil(root, arr);
}

int main(int argc, char *argv[]) {
	Node* root = NULL;
	root = insert(root, 2);
	root = insert(root, 1);
	root = insert(root, 5);
	root = insert(root, 4);
	root = insert(root, 3);
	
	LevelOrderTraversal(root);
		
	return 0;
}