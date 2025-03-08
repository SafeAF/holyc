// string key hashmap with djb2 hash func

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define TABLE_SIZE 100
typedef struct HashNode{
	char *key;
	int value;
	struct HashNode *next;
} HashNode;

typedef struct{
	HashNode *buckets[TABLE_SIZE];
} HashTable;

unsigned int hash_func(const char *key){
	unsigned long hash = 5381;
	int c;
	while ((c = *key++))
		hash = ((hash << 5) + hash) + c; 
	return hash % TABLE_SIZE;
}

HashNode* create_node(const char *key, int value){
	HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
	if(!new_node){
		exit(1);
	}
	new_node->key = strdup(key);
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}



// Init hashtable
void init_table(HashTable *table){
	for(int i = 0; i < TABLE_SIZE; i++)
		table->buckets[i] = NULL;
}

void insert(HashTable *table, const char *key, int value){
	unsigned int index = hash_func(key);
	HashNode *new_node = create_node(key, value);

	new_node->next = table->buckets[index];
	table->buckets[index] = new_node;
}

int* search(HashTable *table, const char *key){
	unsigned int index = hash_func(key);
	HashNode *node = table->buckets[index];

	while(node){
		if(strcmp(node->key, key) == 0)
			return &node->value;
		node = node->next;
	}
	return NULL;
}


void delete(HashTable *table, const char *key) {
    unsigned int index = hash_func(key);
    HashNode *node = table->buckets[index];
    HashNode *prev = NULL;

    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev)
                prev->next = node->next;
            else
                table->buckets[index] = node->next;

            free(node->key);
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

// Free the entire hash table
void free_table(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode *node = table->buckets[i];
        while (node) {
            HashNode *temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
}

// Test the hash table
int main() {
    HashTable table;
    init_table(&table);

    insert(&table, "Alice", 25);
    insert(&table, "Bob", 30);
    insert(&table, "Charlie", 22);

    int *age = search(&table, "Bob");
    if (age)
        printf("Bob's age: %d\n", *age);
    else
        printf("Bob not found\n");

    delete(&table, "Bob");
    age = search(&table, "Bob");
    if (age)
        printf("Bob's age: %d\n", *age);
    else
        printf("Bob not found after deletion\n");

    free_table(&table);
    return 0;
}