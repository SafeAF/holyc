// skill test 1/1/25

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

Node* create_node(int data){
	Node *new_node = malloc(sizeof(Node));

	if(new_node == NULL){
		exit(0);
	}

	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}

void insert_at_end(Node** head, int data){
	Node *new_node = create_node(data);
	Node *temp  = *head;

	// error checking

	if(*head == NULL){
		*head = new_node;
		return;
	}

	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = new_node;

}




int main(){
	Node *list = NULL;
	insert_at_end(&list, 10);

}