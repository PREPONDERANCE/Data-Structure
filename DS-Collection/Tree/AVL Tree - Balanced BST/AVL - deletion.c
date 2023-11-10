#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data, height;
	struct Node *left, *right;
} Node;

Node* createNode(int data){
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->height = 0;
	temp->left = temp->right = NULL;
	return temp;
}

int maxValue(Node* root){
	if( !root->right ) return root->data;
	return maxValue(root->right);
}

int max(int a, int b){
	return a > b ? a : b;
}

int height(Node* root){
	if( !root ) return -1;
	return root->height;
}

int balanced(Node* root){
	if( !root ) return 0;
	return height(root->left) - height(root->right);
}

Node* leftrotate(Node* root){
	Node* temp = root->right;
	Node* rem = temp->left;
	
	temp->left = root;
	root->right = rem;
	
	root->height = max(height(root->left), height(root->right)) + 1;
	temp->height = max(height(temp->left), height(temp->right)) + 1;
	
	return temp;
}

Node* rightrotate(Node* root){
	Node* temp = root->left;
	Node* rem = temp->right;
	
	temp->right = root;
	root->left = rem;
	
	root->height = max(height(root->left), height(root->right)) + 1;
	temp->height = max(height(temp->left), height(temp->right)) + 1;
	
	return temp;
}

Node* insert(Node* root, int data){
	if( !root ) return createNode(data);
	else if( data < root->data ) root->left = insert(root->left, data);
	else root->right = insert(root->right, data);
	
	root->height = max(height(root->left), height(root->right)) + 1;
	int balance = balanced(root);
	
	if( balance > 1 ){
		if( data > root->left->data ) root->left = leftrotate(root->left);
		return rightrotate(root);
	}else if( balance < -1 ){
		if( data < root->right->data ) root->right = rightrotate(root->right);
		return leftrotate(root);
	}
	
	return root;
}

Node* delete(Node* root, int key){
	if( !root ) return NULL;
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
		}else{
			root->data = maxValue(root->left);
			root->left = delete(root->left, root->data);
		}
	}else if( key < root->data ) root->left = delete(root->left, key);
	else root->right = delete(root->right, key);
	
	root->height = max(height(root->left), height(root->right)) + 1;
	int balance = balanced(root);
	
	if( balance > 1 ){
		if( balanced(root->left) <= 0 ) root->left = leftrotate(root->left);
		return rightrotate(root);
	}else if( balance < -1 ){
		if( balanced(root->right) >= 0 ) root->right = rightrotate(root->right);
		return leftrotate(root);
	}
	
	return root;
}

int size(Node* root){
	if( !root ) return 0;
	return size(root->left) + size(root->right) + 1;
}

void print_levelorder(Node* root){
	Node* queue[size(root)];
	
	int i = 0, j = -1;
	queue[++j] = root;
	while( j >= i ){
		Node* curr = queue[i++];
		printf("%d ", curr->data);
		if( curr->left ) queue[++j] = curr->left;
		if( curr->right ) queue[++j] = curr->right;
	}
}


int main(int argc, char *argv[]) {
	Node* root = NULL;
	root = insert(root, 14); root = insert(root, 17); root = insert(root, 11);
	root = insert(root, 7); root = insert(root, 53); root = insert(root, 4);
	root = insert(root, 13); root = insert(root, 12); root = insert(root, 8);
	root = insert(root, 60); root = insert(root, 19); root = insert(root, 16);
	root = insert(root, 20);
	
	print_levelorder(root);
	
	return 0;
}