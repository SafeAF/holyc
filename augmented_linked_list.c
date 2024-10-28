// augmented linked list

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;


Node* create_node(int data){
	Node *new_node = malloc(sizeof(Node));

	if(new_node == NULL){
		return NULL;
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
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");


}

void insert_at_beginning(Node **head, int data){
	Node *new_node = create_node(data);

	Node *old_head = *head;
	*head = new_node;
	new_node->next = old_head;

	return;
}

void insert_at_nth(Node **head, int data, int index){
	Node *new_node = create_node(data);

	Node *temp = *head;

	if(index == 0){
		insert_at_beginning(head, data);
		return;
	}

	for(int i = 0; i < index - 1; i++){
		if(temp == NULL){
			free(new_node);
		}
		temp = temp->next;
	}

	Node *old_node = temp->next;
	temp->next = new_node;
	*temp = *new_node;
	new_node->next = old_node; 
}


Node* search(Node** head, int target){
	Node *temp = *head;

	while(temp != NULL && temp->data != target){
		temp = temp->next;
	}
	

}



int main(void){
	Node *head = NULL;
	insert_at_end(&head, 10);
	insert_at_end(&head, 20);
	insert_at_end(&head, 40);
	insert_at_end(&head, 50);
	//printf("%p %d\n", &head, head->data);	
	//print_list(&head);
	insert_at_beginning(&head, 30);
	//print_list(&head);
	insert_at_nth(&head, 15, 2);
	//insert_at_nth(&head, 15,4);
	print_list(&head);
}