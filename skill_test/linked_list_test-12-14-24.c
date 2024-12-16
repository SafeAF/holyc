// linked list test 12-14-24

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

Node* create_node(int data){
	Node* new_node = malloc(sizeof(Node));
	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}

void insert_at_end(Node **head, int data){
	Node *new_node = create_node(data);
	Node *temp = *head;

	if(*head == NULL){
		*head = new_node;
		return;
	}

	while(temp->next != NULL){
		temp = temp->next;
	}

	 temp->next = new_node;
}

int search(Node *list, int target){
	Node *temp = list;

	while(temp->next != NULL && temp->data != target){
		temp = temp->next;
	}

	return temp != NULL;
}

int main(){
	Node *list = NULL;

	insert_at_end(&list, 10);
	insert_at_end(&list, 20);

	// int ret = search(list, 20);
	// printf("Return value of search %d\n", ret);
}