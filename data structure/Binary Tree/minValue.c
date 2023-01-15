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


Node* insertion(Node* root, int key)
{
	if( root == NULL )
		return CreateNode(key);
	else{
		if( root->data < key )
			root->right =  insertion(root->right, key);
		else
			root->left =  insertion(root->left, key);
	}
	
	return root;
}

int lookup(Node* root, int key)
{
	if(root == NULL)
		return 0;
	else{
		if( root->data == key )
			return 1;
		else if( root->data < key )
			return lookup(root->right, key);
		else
			return lookup(root->left, key);
	}
}

int size(Node* root)
{
	if( root == NULL )
		return 0;
	else
		return(size(root->left) + 1 + size(root->right));
}

int maxDepth(Node* root)
{
	if( root == NULL )
		return 0;
	else{
		int ldepth = maxDepth(root->left);
		int rdepth = maxDepth(root->right);
		
		if( ldepth > rdepth )
			return ldepth+1;
		else
			return rdepth+1;
	}
}

int minValue(Node* root)
{
	if( root->left == NULL )
		return root->data;
	else
		return minValue(root->left);
}

int main()
{
	Node* root = NULL;
	insert(&root, 5);
	insert(&root, 3);
	insert(&root, 1);
	insert(&root, 9);
	
	printf("Minimum value is %d\n", minValue(root));
	printf("Max depth of tree is %d\n", maxDepth(root));
	printf("Size of tree is %d\n", size(root));
	
	return 0;
}