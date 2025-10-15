// linked list skill test aug 5th

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node next;
} Node;

Node* create_node(int data){
	Node* new_node = malloc(sizeof Node);
	// check if node was allocated
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

void insert(Node** head, int data){

	Node *temp = *head;
	// check if temp allocated

	// check if list is size 0 
	if(head == NULL){
		*head = new_node;
	}

	while(temp->next != NULL){
		temp = temp->next; //walk the list
	}
	temp->next = new_node;
}

int main(void){
	
}