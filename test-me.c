// test of linked list from memory

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;

Node* create_node(int data){
	Node *new_node = (Node*)malloc(sizeof(Node));
	if(new_node == NULL){
		perror("malloc");
		exit(1);
	}
	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}

void insert_at_end(Node **head, int data){
 	Node *new_node = create_node(data);

 	if(*head == NULL){
 		*head = new_node; // head will point to the new_node
 		return;
 	}

 	 Node *temp = *head;

 	 while(temp->next != NULL){
 	 	temp = temp->next;
 	 }

 	temp->next = new_node;
 	return;

}

Node* search(Node** list, int target){
	Node* temp = *list;

	while(temp->next != NULL && temp->data != target){
		temp = temp->next;
	}
	return temp;
}

void print_list(Node** list){
	Node* temp = *list;

	while(temp != NULL){
		printf("data is %d\n", temp->data);
		temp = temp->next;
	}
}

void delete(Node** list, int target){
	Node* temp = *list;

	Node* prev = NULL;
	while(temp->next != NULL && temp->data != target){
		prev = temp;
		temp = temp->next;
	}

	if(temp == NULL){
		// we went through the whole list, not found.
		return;
	}
	
	if(prev == NULL){
		*list = temp->next;
	} else {
		prev->next = temp->next;
	}
	free(prev);
}

int main(void){
	Node *list = NULL;

	insert_at_end(&list, 10);
	insert_at_end(&list, 20);

	int target = 20;
	Node * ret = NULL;
	ret = search(&list,  target);

	if(ret != NULL){
		printf("found target %d\n", ret->data);
	}
	else{
		printf("target not found, %d\n", target);
	}

	print_list(&list);

	printf("%d\n", list->data);

	delete(&list, 10);

	printf("%d\n", list->data);

}