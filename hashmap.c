// hashmap
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10 // # buckets

typedef struct Node {
	int key;
	char* value;
	struct Node* next; 
} Node;

Node  *hash_table[TABLE_SIZE] = {NULL};

unsigned int hash(int key){
	return key % TABLE_SIZE;
}

void insert(int key, char *value){
	unsigned int index = hash(key);

	Node *new_node = malloc(sizeof(Node));
	new_node->key = key;
	new_node->value = strdup(value);
	new_node->next = NULL;

	if(hash_table[index] == NULL){
		hash_table[index] = new_node;
	}
	else {
		new_node->next = hash_table[index];
		hash_table[index] = new_node;
	}
}

char* search(int key){
	unsigned int index = hash(key);
	Node* current = hash_table[index];

	while(current){
		if(current->key == key){
			return current->value;
		}
		current = current->next;
	}
	return NULL;
}

void delete(int key) {
    unsigned int index = hash(key);
    Node* current = hash_table[index];
    Node* prev = NULL;

    while (current) {
        if (current->key == key) {
            if (prev == NULL) {
                hash_table[index] = current->next;  // Remove head node
            } else {
                prev->next = current->next;  // Bypass the node
            }
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void print_table(){
	for(int i = 0; i < TABLE_SIZE; i++){
		printf("Bucket %d: ", i);
		Node* current = hash_table[i];
		while(current){
			printf("(%d, %s) -> ", current->key, current->value);
			current = current->next;
		}
		printf("NULL\n");
	}
}



int main(){
    insert(1, "Apple");
    insert(2, "Banana");
    insert(11, "Cherry");  // Will collide with key 1
    insert(21, "Date");    // Will collide with key 1 & 11

    printf("HashMap after insertions:\n");
    print_table();

    printf("\nSearching for key 2: %s\n", search(2));   // Banana
    printf("Searching for key 11: %s\n", search(11)); // Cherry

}