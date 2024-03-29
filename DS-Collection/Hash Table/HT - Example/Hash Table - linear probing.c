// implement hashtable using linear probing

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define INITINAL_CAPACITY 16
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

typedef struct{
	const char* key;
	void* value;
} ht_entry;

typedef struct{
	ht_entry* entries;
	
	size_t capacity;
	size_t length;
} ht;

typedef struct{
	const char* key;
	void* value;
	
	ht* _table;
	size_t _index;
} hti;

ht* ht_create(void){
	ht* table = malloc(sizeof(ht));
	if( !table ) return NULL;
	
	table->length = 0;
	table->capacity = INITINAL_CAPACITY;
	
	table->entries = calloc(table->capacity, sizeof(ht_entry));
	if( !table->entries ){
		free(table);
		return NULL;
	}
	
	return table;
}

void ht_destroy(ht* table){
	for(size_t i = 0; i < table->capacity; i++)
		free((void*)table->entries[i].key);
	
	free(table->entries);
	free(table);
}

static uint64_t hash_key(const char* key){
	uint64_t hash = FNV_OFFSET;
	for(const char* p = key; *p; p++){
		hash ^= (uint64_t)(unsigned char)(*p);
		hash *= FNV_PRIME;
	}
	return hash;
}

void* ht_get(ht* table, const char* key){
	uint64_t hash = hash_key(key);
	size_t index = (size_t)(hash & (uint64_t)(table->capacity-1));
	
	while( table->entries[index].key != NULL ){
		if( strcmp(key, table->entries[index].key) == 0 ) return table->entries[index].value;
		index++;
		if( index >= table->capacity ) index = 0;
	}
	
	return NULL;
}

static const char* ht_set_entry(ht_entry* entries, size_t capacity, const char* key, void* value, size_t* plength){
	uint64_t hash = hash_key(key);
	size_t index = (size_t)(hash & (uint64_t)(capacity-1));
	
	while( entries[index].key != NULL ){
		if( strcmp(key, entries[index].key) == 0 ){
			entries[index].value = value;
			return entries[index].key;
		}
		index++;
		if( index >= capacity ) index = 0;
	}
	
	if( plength != NULL ){
		key = strdup(key);
		if( key == NULL ) return NULL;
		(*plength)++;
	}
	
	entries[index].key = (char*)key;
	entries[index].value = value;
	
	return key;
}

static bool ht_expand(ht* table){
	size_t new_capacity = table->capacity*2;
	if( new_capacity < table->capacity ) return false;
	
	ht_entry* new_entries = calloc(new_capacity, sizeof(ht_entry));
	if( new_entries == NULL ) return false;
	
	for(size_t i = 0; i < table->capacity; i++){
		ht_entry entry = table->entries[i];
		if( entry.key != NULL )
			ht_set_entry(new_entries, new_capacity, entry.key, entry.value, NULL);
	}
	
	free(table->entries);
	table->entries = new_entries;
	table->capacity = new_capacity;
	
	return true;
}

const char* ht_set(ht* table, const char* key, void* value){
	assert(value != NULL);
	
	if( !value ) return NULL;
	if( table->length >= table->capacity/2 )
		if( !ht_expand(table) ) return NULL;
	
	return ht_set_entry(table->entries, table->capacity, key, value, &table->length);
}

size_t ht_length(ht* table){
	return table->length;
}

hti ht_iterator(ht* table){
	hti it;
	it._table = table;
	it._index = 0;
	return it;
}

bool ht_next(hti* it){
	ht* table = it->_table;
	
	while( it->_index < table->capacity ){
		size_t i = it->_index;
		it->_index++;
		if( table->entries[i].key != NULL ){
			ht_entry entry = table->entries[i];
			it->key = entry.key;
			it->value = entry.value;
			return true;
		}
	}
	
	return false;
}

int main(int argc, char *argv[]) {
	ht* table = ht_create();
	
	char* testString[20] = {"test1", "test2", "test3", "test4", "test5"};
	void* testValue[] = {(void*)3, (void*)5, (void*)4, (void*)1, (void*)9};
	
	for(int i = 0; i != sizeof(testValue)/sizeof(testValue[0]); i++)
		ht_set(table, testString[i], testValue[i]);
	
	printf("Test on ht_get function\n");
	printf("Value at key 0: %d\n", (int)(intptr_t)ht_get(table, testString[0]));
	printf("Value at key 1: %d\n", (int)(intptr_t)ht_get(table, testString[1]));
	printf("Value at key 2: %d\n", (int)(intptr_t)ht_get(table, testString[2]));
	printf("Value at key 3: %d\n", (int)(intptr_t)ht_get(table, testString[3]));
	printf("Value at key 4: %d\n", (int)(intptr_t)ht_get(table, testString[4]));
	printf("\n");
	
	printf("Test on hti iterator functionality\n");
	hti it = ht_iterator(table);
	while( ht_next(&it) )
		printf("Key \"%s\" : value %d\n", it.key, (int)(intptr_t)it.value);
	printf("\n");
	
	printf("Test on ht_length function\n");
	printf("Length of hash table is: %zu\n", ht_length(table));
	
	return 0;
}