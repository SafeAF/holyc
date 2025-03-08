// dynamic hashmap
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
    HashNode **buckets;  // Dynamic array of pointers
} HashTable;

// djb2 string hash function
unsigned int hash_func(const char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash % TABLE_SIZE;
}

HashTable* create_table() {
    HashTable *table = malloc(sizeof(HashTable));
    if (!table) {
        perror("Failed to allocate table");
        exit(EXIT_FAILURE);
    }

    table->buckets = calloc(TABLE_SIZE, sizeof(HashNode *));
    if (!table->buckets) {
        perror("Failed to allocate buckets");
        free(table);
        exit(EXIT_FAILURE);
    }

    return table;
}

HashNode* create_node(const char *key, int value) {
    HashNode *node = malloc(sizeof(HashNode));
    if (!node) {
        perror("Failed to allocate node");
        exit(EXIT_FAILURE);
    }
    node->key = strdup(key);
    if (!node->key) {
        perror("Failed to duplicate key");
        free(node);
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->next = NULL;
    return node;
}

void insert(HashTable *table, const char *key, int value) {
    unsigned int index = hash_func(key);
    HashNode *new_node = create_node(key, value);

    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

HashNode* search(HashTable *table, const char *key) {
    unsigned int index = hash_func(key);
    HashNode *node = table->buckets[index];

    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

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
    free(table->buckets);
    free(table);
}

int main() {
    HashTable *table = create_table();

    insert(table, "foo", 42);
    insert(table, "bar", 84);
    insert(table, "baz", 168);

    HashNode *result = search(table, "bar");
    if (result) {
        printf("Found key 'bar' with value: %d\n", result->value);
    } else {
        printf("Key 'bar' not found\n");
    }

    result = search(table, "qux");
    if (result) {
        printf("Found key 'qux' with value: %d\n", result->value);
    } else {
        printf("Key 'qux' not found\n");
    }

    free_table(table);
    return 0;
}
