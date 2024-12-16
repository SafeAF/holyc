// linked list skill test

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
	Node *temp = *head; // save the head pointer

	if(*head == NULL){ // if head ptr null, list is empty
		*head = new_node;
		return;
	}

	//iterate the list while there is a next node
	while(temp->next != NULL){ 
		temp = temp->next;
	}
	// found the end of the list
	// set the next node to new_node
	temp->next = new_node;
}

bool search(Node *head, int data){
	Node *temp = head; //set temp to header ptr

	//iterate while there is a node and it isn't eq data
	while(temp != NULL && temp->data != data){
		temp = temp->next;
	}
	//came to end of list or hit a match
	// check if null return false
	// else check if match return true
	return temp != NULL; // if temp is NULL returns 0 or false, otherwise true
}

bool delete(Node **head, int data){
	Node *temp = *head; //save head ptr
	Node *prev = NULL; // save prev node ptr

	// iterate while node and node not eq data
	while(temp != NULL && temp->data != data){
		prev = temp;	// store prev node
		temp = temp->next; // go to next node
	}

	// if temp hits null that means data not found in list
	if(temp == NULL){
		return false; // critical to return here and not continue exec
	}

	// target at head of the list
	if(prev == NULL){ 
		*head = temp->next; // set head to next node
	} else {
		prev->next = temp->next; // leapfrog current node(temp)
	}

	free(temp); // unlink temp
	return true;
}




int main(){
	Node *list = NULL;

	insert_at_end(&list, 10);
	insert_at_end(&list, 20);
	int target = 20;
	bool found = search(list, target);
	if(found){
		printf("Found %d\n", target);
	}
	else {
		printf("%d not found\n", target);
	}

	bool removed = delete(&list, 20);
		if(found){
		printf("Found %d it wasnt deleted\n", target);
	}
	else {
		printf("%d not found, successfully deleted\n", target);
	}
}