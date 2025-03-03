// string hashmap 3/3/24

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TABLE_SIZE 1000

typedef struct HashNode {
	char *key
	int value;
	struct HashNode next;
} HashNode;

typedef struct {
	// pointer to a big block of allocated memory
	HashNode *buckets[TABLE_SIZE];
} HashTable;






int main(){
	
}