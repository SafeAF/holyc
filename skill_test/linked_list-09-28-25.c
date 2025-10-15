#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node next;
} Node;

Node* create_node(int data){
	Node new_node = malloc(sizeof(Node));
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

void insert(Node **head, int data){
	Node new_node = create_node(data);
	Node *head = head;


	if(*head = NULL){
		*head = new_node;
		return;
	}

	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = new_node;
}



int main(){
	
	return 1;
}