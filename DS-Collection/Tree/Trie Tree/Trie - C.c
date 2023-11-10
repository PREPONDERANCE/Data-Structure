#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET 26

typedef struct TrieNode{
	bool endOfWord;
	struct TrieNode* children[ALPHABET];
} TrieNode;

int ord(char c){
	return c-'a';
}

TrieNode* createNode(){
	TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
	newNode->endOfWord = false;
	for(int i = 0; i != ALPHABET; i++) newNode->children[i] = NULL;
	return newNode;
}

void insert(TrieNode* root, char* word){
	for(int i = 0; i != strlen(word); i++){
		if( !root->children[ord(word[i])] )
			root->children[ord(word[i])] = createNode();
		root = root->children[ord(word[i])];
	}
	
	root->endOfWord = true;
}

bool search(TrieNode* root, char* word){
	for(int i = 0; i != strlen(word); i++){
		if( !root->children[ord(word[i])] ) return false;
		root = root->children[ord(word[i])];
	}
	return root->endOfWord;
}

bool startsWith(TrieNode* root, char* prefix){
	for(int i = 0; i != strlen(prefix); i++){
		if( !root->children[ord(prefix[i])] ) return false;
		root = root->children[ord(prefix[i])];
	}
	return true;
}

int main(int argc, char *argv[]) {
	TrieNode* root = createNode();
	
	insert(root, "apple");
	insert(root, "ai");
	
	if( search(root, "apple") ) printf("Target word found\n");
	else printf("Target word does not exist\n");
	
	if( startsWith(root, "app") ) printf("Target prefix exists\n");
	else printf("Target prefix does not exist\n");
	
	return 0;
}