#include <stdio.h>
#include <stdlib.h>
#include "/Users/mac/Desktop/Program/Algorithm/Sorting Algorithm/C/Util.h"

typedef struct union_find{
	int size;
	int* array;
} union_find;

union_find* createUnion(int v){
	union_find* newUnion = (union_find*)malloc(sizeof(union_find));
	newUnion->size = v;
	newUnion->array = (int*)malloc(sizeof(int) * v);
	return newUnion;
}

void make_set(union_find* parent, int v){
	parent->array[v] = v;
}

int find_set(union_find* parent, int v){
	while( parent->array[v] != v )
		v = parent->array[v];
	return v;
}

void union_sets(union_find* parent, int s1, int s2){
	int ptn1 = find_set(parent, s1), ptn2 = find_set(parent, s2);
	if( ptn1 != ptn2 ) parent->array[ptn1] = ptn2;
}

int main(int argc, char *argv[]) {
	int v = 12;
	union_find* un_find = createUnion(v);
	
	make_set(un_find, 0); make_set(un_find, 1); make_set(un_find, 2); make_set(un_find, 3);
	make_set(un_find, 4); make_set(un_find, 5); make_set(un_find, 6); make_set(un_find, 7);
	make_set(un_find, 8); make_set(un_find, 9); make_set(un_find, 10); make_set(un_find, 11);
	
	printArr(un_find->array, v);
	
	union_sets(un_find, 4, 9); union_sets(un_find, 1, 0);
	union_sets(un_find, 5, 6); union_sets(un_find, 5, 10);
	union_sets(un_find, 4, 3); union_sets(un_find, 3, 2);
	union_sets(un_find, 7, 1); union_sets(un_find, 4, 5);
	union_sets(un_find, 5, 10); union_sets(un_find, 11, 8);
	union_sets(un_find, 11, 1); union_sets(un_find, 411, 10);
	
	printArr(un_find->array, v);
}