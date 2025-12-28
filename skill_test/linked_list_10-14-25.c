// skill test linked list 10-14-25

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct *Node next;
} Node;

Node* create_node(int data){
	Node* new_node = malloc(sizeof(Node));

	if(!new_node){
		exit(1);
	}
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

void insert(Node** head, int data){
	Node *new_node = create_node(data);
	Node *temp = *head;



	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = new_node
}


int main(void){


}