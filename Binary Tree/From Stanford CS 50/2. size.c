#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *left, *right;
} Node;

Node* CreateNode(int new_data)
{
	Node* new_Node = malloc(sizeof(Node));
	new_Node->data = new_data;
	new_Node->left = new_Node->right = NULL;
	return new_Node;
}

void insert(Node** rootref, int new_data)
{
	if( !*rootref ){
		Node* new_Node = CreateNode(new_data);
		*rootref = new_Node;
		return;
	}else{
		if( (*rootref)->data < new_data )
			insert(&(*rootref)->right, new_data);
		else
			insert(&(*rootref)->left, new_data);
	}
}

int size(Node* root)
{
	if( root == NULL )
		return 0;
	else
		return(size(root->left) + 1 + size(root->right));
}

int main()
{
	Node* root = NULL;
	insert(&root, 4);
	insert(&root, 6);
	insert(&root, 1);
	
	printf("%d", size(root));
	return 0;
}