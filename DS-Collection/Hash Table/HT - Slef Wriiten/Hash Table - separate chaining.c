#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct Pair{
	char* key;
	int val;
	struct Pair* next;
}Pair;

typedef struct hashTable{
	Pair** array;
	size_t capacity;
}hashTable;

Pair* createPair(char* key, int val){
	Pair* temp = (Pair*)malloc(sizeof(Pair));
	temp->key = strdup(key);
	temp->val = val;
	temp->next = NULL;
	return temp;
}

hashTable* createTable(){
	hashTable* temp = (hashTable*)malloc(sizeof(hashTable));
	temp->capacity = 50;
	temp->array = (Pair**)malloc(sizeof(Pair*) * temp->capacity);
	return temp;
}

int hash(char* key, int size){
	int hashVal = 0;
	for(int i = 0; i != strlen(key); i++) hashVal += key[i];
	return hashVal % size;
}

void update(hashTable* HT, char* key, int val){
	int index = hash(key, HT->capacity);
	Pair* newPair = createPair(key, val);
	
	if( HT->array[index] == NULL ){
		HT->array[index] = newPair;
		return;
	}
	
	Pair* head = HT->array[index];
	while( (!strcmp(head->key, key) && head->val == val) && head->next ){
		if( strcmp(head->key, key) && head->val == val ) return;
		head = head->next;
	}
	head->next = newPair;
}

int get(hashTable* HT, char* key){
	int index = hash(key, HT->capacity);
	
	if( HT->array[index] == NULL ) return -1;
	Pair* head = HT->array[index];
	while( head ){
		if( strcmp(head->key, key) == 0 ) return head->val;
		head = head->next;
	}
	
	return -1;
}

void del(hashTable* HT, char* key){
	int index = hash(key, HT->capacity);
	
	if( !HT->array[index] ) return;
	Pair *head = HT->array[index], *prev = NULL;
	while( head ){
		if( !strcmp(key, head->key) ){
			if( !prev ){
				HT->array[index] = head->next;
				free(head);
				return;
			}
			prev->next = head->next;
			free(head);
			break;
		}
		prev = head;
		head = head->next;
	}
}

int main(int argc, char *argv[]) {
	hashTable* HT = createTable();
	
	char key[][20] = {"abcd", "jsdf", "asdjofi", "djoisdf"};
	int size = sizeof(key)/sizeof(key[0]);
	
	int val[] = {20, 40, 30, 14};
	for(int i = 0; i != size; i++)
		update(HT, key[i], val[i]);
	for(int i = 0; i != size; i++)
		printf("%d ", get(HT, key[i]));
	
	return 0;
}