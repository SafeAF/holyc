// skill test hashmap 3-4-25

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000

typedef struct HashNode{
	char *key;
	int value;
	struct HashNode *next;
} HashNode;

typedef struct {
	HashNode *buckets[TABLE_SIZE];
} HashTable;

void init_table(HashTable *table){
	for(int i = 0; i < TABLE_SIZE; i++)
		table->buckets[i] = NULL;
}

unsigned int hash_func(const char *key){
	unsigned long hash = 5381;
	int c;
	while ((c = *key++))
		hash = ((hash << 5) + hash) + c; 
	return hash % TABLE_SIZE;
}

HashNode* create_node(const char *key, int value){
	int index = hash_func(key);
	HashNode *new_node = malloc(sizeof(HashNode));

	if(!new_node){
		exit(1);
	}

	new_node->key = strdup(key);
	new_node->value = value;
	new_node->next = NULL;
}

void insert(HashTable *table, const char *key, int value){
	int index = hash_func(key);
	printf("Key %s is in index %d\n", key, index);
	HashNode *new_node = create_node(key, value);

	if(!new_node){
		exit(1);
	}

	new_node->next = table->buckets[index];
	table->buckets[index] = new_node;
}

int* search(HashTable *table, const char *target){
	int index = hash_func(target);
	HashNode *node = table->buckets[index];

	while(node){
		if(strcmp(node->key, target) == 0){
			return &node->value;
		}
		node = node->next;
	}
	return NULL;
}

void print_list(HashTable *table){
	for(int i=0; i<TABLE_SIZE; i++){
		if(table->buckets[i]){
			printf("bucket %i ptr %p\n", i, table->buckets[i]);
			HashNode *node = table->buckets[i];
			while(node){
				printf("key %s, value %d, at index %d\n",
					node->key, node->value, i);
				node = node->next;
			}
		}
	}
}

void free_list(HashTable *table){
	for(int i=0; i<TABLE_SIZE; i++){
		if(table->buckets[i]){
			HashNode *node = table->buckets[i];
			while(node){
				HashNode *temp = node->next;
				
				free(node->key);
				free(node);
				node = temp;
			}
		}
	}
}





int main(){
	HashTable table;
	init_table(&table);
	insert(&table, "baz", 323);
	insert(&table, "bar", 2293);
	insert(&table, "boo", 290209);
	int *res = search(&table, "bar");

	printf("res %d\n", *res);
	print_list(&table);
	free_list(&table);
}