// linked lists in C for Ruby via FFI

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

Node* create_node(int data){
	Node * new_node = (Node*)malloc(sizeof(Node));

	if(new_node == NULL){
		perror("Malloc failed");
		exit(1);
	}

	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

void append(Node **head, int data){
	Node * new_node = create_node(data);
	if(*head == NULL){
		*head = new_node; 
	} else {

	Node * temp = *head;
	while(temp->next != NULL){
		temp = temp->next;
	}
	// we have reached the end of the list
	temp->next = new_node;
	}
}

int get_data(Node *node){
	return node->data;
}

void print_list(Node *head){
	Node *temp = head;

	while(temp != NULL){
		printf("%d -> ", temp->data);
		temp = temp->next;
	}
	printf("NULL\n");
}

void free_list(Node *head){
	Node *current = head;
	Node *next;

	while(current != NULL){
		next = current->next;
		free(current);
		current = next;
	}
}