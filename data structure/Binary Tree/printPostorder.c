#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *left, *right;
} Node;

Node* CreateNode(int data)
{
	Node* new_Node = (Node*)malloc(sizeof(Node));
	new_Node->data = data;
	new_Node->left = new_Node->right = NULL;
	return new_Node;
}

void insert(Node** rootref, int key)
{
	if( *rootref == NULL ){
		Node* new_Node = CreateNode(key);
		*rootref = new_Node;
		return;
	}else{
		if( (*rootref)->data < key )
			insert(&(*rootref)->right, key);
		else
			insert(&(*rootref)->left, key);
	}
}

void printPostorder(Node* root)
{
	if( root->left == NULL && root->right == NULL )
		printf("%d ", root->data);
	else{
		printPostorder(root->left);
		printPostorder(root->right);
		printf("%d ", root->data);
	}
}

int main()
{
	Node* root = NULL;
	insert(&root, 4);
	insert(&root, 2);
	insert(&root, 5);
	insert(&root, 1);
	insert(&root, 3);
	
	printPostorder(root);
	return 0;
}