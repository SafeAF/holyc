#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 1000

typedef struct HashNode{
	char *key
	int value;
	struct HashNode *next;
} HashNode;

typedef struct {
	HashNode *buckets[TABLESIZE];
} HashTable;

void init_table(HashTable *table){
	for(int i = 0; i < TABLESIZE; i++){
		table->buckets[i] = NULL
	}

}

unsigned int hash_func(const char *key){
	unsigned long hash = 5381;
	int c;
	while ((c = *key++))
		hash = ((hash << 5) + hash) + c; 
	return hash % TABLE_SIZE;
}

int main(){

}