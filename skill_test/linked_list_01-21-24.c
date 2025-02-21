// linked list 01-21-24

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

Node* create_node(int data){
	Node *new_node = malloc(sizeof(Node));

	if(new_node == NULL){
		exit(1);
	}

	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}

void insert_at_end(Node **head, int data){
	Node *new_node = create_node(data);
	Node *temp = *head;

	// empty list
	if(*head == NULL){
		*head = new_node;
		return; // return is critical or it falls through to the loop
	}

	while(temp != NULL){
		temp = temp->next;
	}

	temp->next = new_node;
	return;



}




int main(){
	
}