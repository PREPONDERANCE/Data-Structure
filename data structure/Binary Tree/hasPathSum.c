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

int lookup(Node* node, int key)
{
	if( node ){
		if(node->data == key)
			return 1;
		else if(node->data < key)
			return lookup(node->right, key);
		return lookup(node->left, key);
	}
	
	return -1;
}

Node* insertion(Node* root, int data)
{
	if( root == NULL )
		return CreateNode(data);
	else{
		if( root->data <= data )
			root->right = insertion(root->right, data);
		else
			root->left = insertion(root->left, data);
	}
	
	return root;
}

void insert(Node** rootref, int data)
{
	Node* new_Node = CreateNode(data);
	
	if( *rootref == NULL ){
		*rootref = new_Node;
		return;
	}else{
		if( (*rootref)->data <= data )
			insert(&(*rootref)->right, data);
		else
			insert(&(*rootref)->left, data);
	}
}

int size(Node* root)
{
	if( root == NULL )
		return 0;
	else
		return (size(root->left) + 1 + size(root->right));
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
	if( root->left == NULL && root->right == NULL )
		return root->data;
	else
		return minValue(root->left);
}

void printTree(Node* root)
{
	if( root == NULL )
		return ;
	else{
		printTree(root->left);
		printf("%d ", root->data);
		printTree(root->right);
	}
}

void printPostorder(Node* root)
{
	if( root == NULL )
		return ;
	else{
		printPostorder(root->left);
		printPostorder(root->right);
		printf("%d ", root->data);
	}
}

int hasPathSum(Node* root, int sum)
{
	if( root == NULL )
		return (sum == 0);
	else{
		int subsum = sum - root->data;
		return(hasPathSum(root->left, subsum) || hasPathSum(root->right, subsum));
	}
}

int main()
{
	Node* root = NULL;
	root = insertion(root, 5);
	insert(&root, 4);
	root = insertion(root, 8);
	insert(&root, 11);
	insert(&root, 13);
	insert(&root, 7);
	insert(&root, 2);
	insert(&root, 1);
	
	printf("In all paths sum exist %d", hasPathSum(root, 20));
		
	return 0;
}