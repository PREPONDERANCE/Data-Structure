// A simpler version of hash table with arbitrary key-value pair being string-int captalizing on linear probing

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/types.h>
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL
#define TABLE_MAX_LOAD 0.75
#define NIL_VAL INT_MAX

typedef struct Pair{
	char* key;
	int value;
} Pair;

typedef struct HashTable{
	size_t len;
	size_t capacity;
	Pair* pairs;
} HashTable;

int max(int a, int b){
	return a > b ? a : b;
}

bool NIL_VALUE(int val){
	return val == INT_MAX;
}

HashTable* createHashTable(){
	HashTable* table = (HashTable*)malloc(sizeof(HashTable));
	table->len = 0;
	table->capacity = 0;
	table->pairs = NULL;
	return table;
}

void freeArray(Pair* pair, int capacity){
	for(int i = 0; i != capacity; i++) free(&pair[i]);
}

void freeHashTable(HashTable* table){
	freeArray(table->pairs, table->capacity);
	free(table);
}

static uint64_t hash(char* key){
	uint64_t hash = FNV_OFFSET;
	for(int i = 0; i != strlen(key); i++){
		hash ^= (uint64_t)(unsigned char)key[i];
		hash *= FNV_PRIME;
	}
	return hash;
}

static Pair* findPair(Pair* entries, int capacity, char* key){
	uint64_t index = hash(key) % capacity;
	Pair* tombstone = NULL;
	
	while( 1 ){
		Pair* entry = &entries[index];
		if( !entry->key ){
			if( NIL_VALUE(entry->value) ) return tombstone ? tombstone : entry;
			else if( !tombstone ) tombstone = entry;
		}else if( !strcmp(key, entry->key) ) return entry;
		index = (index+1) % capacity;
	}
}

void grow(HashTable* table){
	int new_capacity = max(table->capacity, 1);
	Pair* new_pairs = (Pair*)calloc(new_capacity, sizeof(Pair));
	
	for(int i = 0; i != new_capacity; i++){
		new_pairs->key = NULL;
		new_pairs->value = NIL_VAL;
	}
	
	table->len = 0;
	for(int i = 0; i != table->capacity; i++){
		Pair* curr_pair = &table->pairs[i];
		if( curr_pair->key == NULL ) continue;
		
		Pair* dst = findPair(new_pairs, new_capacity, curr_pair->key);
		dst->key = strdup(curr_pair->key);
		dst->value = curr_pair->value;
		
		table->len++;
	}
	
	freeArray(table->pairs, table->capacity);
	table->pairs = new_pairs;
	table->capacity = new_capacity;
}

bool insert(HashTable* table, char* key, int value){
	Pair* slot = findPair(table->pairs, table->capacity, key);
	bool isNewPair = slot->key == NULL;
	if( isNewPair && NIL_VALUE(slot->value) ) table->len++;
	
	if( table->len+1 > table->capacity*TABLE_MAX_LOAD ) grow(table);
	
	slot->key = strdup(key);
	slot->value = value;
	return isNewPair;
}