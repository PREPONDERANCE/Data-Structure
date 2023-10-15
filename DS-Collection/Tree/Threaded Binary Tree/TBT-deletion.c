#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
	int data;
	struct Node *left, *right;
	bool Ltag, Rtag;
} Node;

Node* createNode(int data){
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->left = temp->right = NULL;
	temp->Ltag = temp->Rtag = true;
	temp->data = data;
	return temp;
}

Node* insert(Node* root, int data){
	Node *pnt = NULL, *ptr = root;
	
	while( ptr ){
		pnt = ptr;
		if( data < ptr->data ){
			if( !ptr->Ltag ) ptr = ptr->left;
			else break;
		}else{
			if( !ptr->Rtag ) ptr = ptr->right;
			else break;
		}
	}
	
	Node* temp = createNode(data);
	if( !pnt ) root = temp;
	else if( data < pnt->data ){
		temp->left = pnt->left;
		pnt->Ltag = false;
		pnt->left = temp;
		temp->right = pnt;
	}else{
		temp->right = pnt->right;
		pnt->Rtag = false;
		pnt->right = temp;
		temp->left = pnt;
	}
	
	return root;
}

Node* successor(Node* root){
	if( root->Rtag ) return root->right;
	root = root->right;
	while( !root->Ltag ) root = root->left;
	return root;
}

Node* predecessor(Node* root){
	if( root->Ltag ) return root->left;
	root = root->left;
	while( !root->Rtag ) root = root->right;
	return root;
}

Node* deg0(Node* root, Node* pnt, Node* ptr){
	if( !pnt ) root = NULL;
	if( ptr == pnt->left ){
		pnt->left = ptr->left;
		pnt->Ltag = true;
	}else{
		pnt->right = ptr->right;
		pnt->Rtag = true;
	}
	
	free(ptr);
	return root;
}

void print(Node* root){
	if( !root ) return;
	while( !root->Ltag ) root = root->left;
	while( root ){
		printf("%d ", root->data);
		root = successor(root);
	}
	putchar('\n');
}

Node* deg1(Node* root, Node* pnt, Node* ptr){
	Node* child = ( !ptr->Ltag ) ? ptr->left : ptr->right;
	if( !pnt ) root = child;
	else if( ptr == pnt->left ) pnt->left = child;
	else if( ptr == pnt->right ) pnt->right = child;
	
	Node *p = predecessor(ptr), *s = successor(ptr);
	if( !p->Ltag ) p->right = s;
	else if( !p->Rtag ) s->left = p;
	
	free(ptr);
	return root;
}

Node* deg2(Node* root, Node* ptr){
	Node *succ = ptr->right, *pntSucc = ptr;
	
	while( !succ->Ltag ){
		pntSucc = succ;
		succ = succ->left;
	}
	
	ptr->data = succ->data;
	if( succ->Ltag && succ->Rtag ) ptr = deg0(ptr, pntSucc, succ);
	else ptr = deg1(ptr, pntSucc, succ);
	
	return root;
}

Node* delete(Node* root, int key){
	if( !root ) return NULL;
	Node *pnt = NULL, *ptr = root;
	bool found = false;
	
	while( ptr ){
		if( ptr->data == key ){
			found = true;
			break;
		}
		pnt = ptr;
		if( key < ptr->data ){
			if( !ptr->Ltag ) ptr = ptr->left;
			else break;
		}else{
			if( !ptr->Rtag ) ptr = ptr->right;
			else break;
		}
	}
	
	if( !found ) return root;
	else if( ptr->Ltag && ptr->Rtag ) root = deg0(root, pnt, ptr);
	else if( ptr->Ltag || ptr->Rtag ) root = deg1(root, pnt, ptr);
	else root = deg2(root, ptr);
	
	return root;
}

int main(int argc, char *argv[]) {
	Node* root = NULL;
	
	root = insert(root, 20);
	root = insert(root, 10);
	root = insert(root, 16);
	root = insert(root, 14);
	root = insert(root, 30);
	
	print(root);
	
	return 0;
}