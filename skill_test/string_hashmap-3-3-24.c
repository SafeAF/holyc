// string hashmap 3/3/24

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TABLE_SIZE 1000

typedef struct HashNode {
	char *key;
	int value;
	struct HashNode *next;
} HashNode;

typedef struct {
	// pointer to a big block of allocated memory
	HashNode *buckets[TABLE_SIZE];
} HashTable;


unsigned int hash_func(const char *key){
	unsigned long hash = 5381;
	int c;
	while ((c = *key++))
		hash = ((hash << 5) + hash) + c; 
	return hash % TABLE_SIZE;
}

void init_table(HashTable *table){
	for(int i; i<TABLE_SIZE; i++)
		table->buckets[i] = NULL;
}


HashNode* create_node(const char *key, int value){
	HashNode *new_node = malloc(sizeof(HashNode));

	if(!new_node){
		exit(1);
	}
	new_node->key = strdup(key);
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}

void insert(HashTable *table, const char *key, int value){
	HashNode *new_node = create_node(key, value);
	int index = hash_func(key);

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

void delete(HashTable *table, const char *target){
	int index = hash_func(target);
	HashNode *node = table->buckets[index];
	HashNode *prev = NULL;

	while(node){
		if(strcmp(node->key, target) == 0){
			if(prev){
				prev->next = node->next;
			}	
			else{
				table->buckets[index] = node->next;
			}
		}
		prev = node;
		node = node->next;
		free(node->key);
		free(node);			
		
	}
	return NULL;
} 


int main(){
	HashTable table;
	init_table(&table);
	insert(&table, "foo", 3);
	insert(&table, "bar", 13);
	insert(&table, "baz", 22);

	int *res = search(&table, "bar");

	printf("%d\n", *res);

	delete(&table, "bar");
	res = search(&table, "bar");

	printf("%d\n", *res);

}