// 2-22-24 HASHMAP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Node {
	int key;
	char *value;
	struct Node *next;
} Node;

Node *hash[TABLE_SIZE] = {NULL};

unsigned int hash_func(int key){
	return key % TABLE_SIZE;
}

void insert(int key, char *value){
	unsigned int index = hash_func(key);

	Node *new_node = malloc(sizeof(Node));
	new_node->key = index;
	new_node->value = strdup(value);
	new_node->next = NULL;

	if(hash[index] != NULL){
		hash[index] = new_node;
	}
	else{
		new_node->next = hash[index];
		hash[index] = new_node;
	}

}


int main(){
	insert(1, "foobar");
}
