// linked list external functions for ds server

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node; 

Node* create_node(int data){
	Node *new_node = (Node*)malloc(sizeof(Node));

	if(new_node == NULL){
		perror("Memory alloc failed\n");
		exit(1);
	} 

	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}

void insert_at_end(Node **head, int data){
	Node *new_node = create_node(data);

	if(*head == NULL){
		*head = new_node;
		return;
	}

	Node *temp = *head;

	while(temp->next != NULL){
		temp = temp->next;
	}

	temp->next = new_node;
}

void print_list(Node **head){
	Node *temp = *head;

	while(temp != NULL){
		printf("Data: %d\n", temp->data);
		temp = temp->next;
	}
}

Node* search(Node **head, int target){
	Node *temp = *head;

	while(temp != NULL && temp->data != target){
		temp = temp->next;
	}
	return temp;
}

void delete(Node **head, int target) {
    Node *temp = *head, *prev = NULL;

    while (temp != NULL && temp->data != target) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        // Target not found
        return;
    }

    if (prev == NULL) {
        // Deleting the head node
        *head = temp->next;
    } else {
        // Bypass the node to delete it
        prev->next = temp->next;
    }

    free(temp);
}