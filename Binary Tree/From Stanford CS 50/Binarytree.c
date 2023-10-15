#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
	int data;
	struct Node *left, *right;
} Node;

//int lookup(Node* root, int key)
//{
//	if( root == NULL )
//		return 0;
//	else{
//		if( root->data == key )
//			return 1;
//		else{
//			if( root->data < key )
//				return lookup(root->right, key);
//			else
//				return lookup(root->left, key);
//		}
//	}
//}
// Recursive calls of binary search tree

int lookup(Node* root, int key)
{
	while( root != NULL ){
		if( root->data == key )
			return 1;
		else if( root->data < key )
			root = root->right;
		else
			root = root->left;
	}
	
	return -1;
}
// Iterative version
// Both similar to binary search

Node* delete(Node* root, int key){
	if( root->data == key ){
		free(root);
		return NULL;
	}else if( root->data < key )
		root->right = delete(root->right, key);
	else
		root->left = delete(root->left, key);
	return root;
}

Node* CreateNode(int new_data)
{
	Node* new_Node = malloc(sizeof(Node));
	new_Node->data = new_data;
	new_Node->left = new_Node->right = NULL;
	return new_Node;
}

void printTree(Node* root)
{
	if( root == NULL )
		return;
	else{
		printTree(root->left);
		printf("%d ", root->data);
		printTree(root->right);
	}
}

Node* insert(Node* root, int new_data)
{
	if( root == NULL )
		return CreateNode(new_data);
	else{
		if( root->data <= new_data)
			root->right = insert(root->right, new_data);
		else
			root->left = insert(root->left, new_data);
	}
	
	return root;
}

void insert1(Node** rootref, int new_data)
{
	if( !*rootref ){
		Node* new_Node = CreateNode(new_data);
		*rootref = new_Node;
		return;
	}else{
		if( (*rootref)->data < new_data )
			insert1(&(*rootref)->right, new_data);
		else
			insert1(&(*rootref)->left, new_data);
	}
}

int main()
{
	Node *root = NULL;
	insert1(&root, 4);
	insert1(&root, 3);
	insert1(&root, 7);
	insert1(&root, 1);
	insert1(&root, 6);
	insert1(&root, 5);
	insert1(&root, 2);
	
	printTree(root);
	putchar('\n');
	
	root = delete(root, 5);
	printTree(root);
	
	//printf("Target value found or not : %d\n", lookup(root, 4));
	
	return 0;
}
//Binary Search tree