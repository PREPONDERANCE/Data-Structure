#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *left, *right;
} Node;

Node* newNode(int data)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

void insert(Node** rootref, int data)
{
	if( !*rootref ){
		Node* new = newNode(data);
		*rootref = new;
		return;
	}else{
		if( (*rootref)->data < data )
			insert(&(*rootref)->right, data);
		else
			insert(&(*rootref)->left, data);
	}
}

//int main()
//{
//	Node* root = newNode(2);
//	Node* subtree1 = newNode(1);
//	Node* subtree2 = newNode(3);
//	
//	root->left = subtree1;
//	root->right = subtree2;
//	
//	return 0;
//}

//int main()
//{
//	Node* root = newNode(2);
//	root->left = newNode(1);
//	root->right = newNode(3);
//	
//	return 0;
//}

int main()
{
	Node* root = newNode(2);
	insert(&root, 1);
	insert(&root, 3);
	
	return 0;
}

// Three methods given