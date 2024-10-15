	// linked list

	#include <stdio.h>
	#include <stdlib.h>

	typedef struct Node {
		int data;
		struct Node* next;
	} Node;

	Node* create_node(int data){
		Node *new_node = (Node*)malloc(sizeof(Node));

		if(new_node == NULL){
			perror("malloc failure\n");
			exit(1);
		}

		new_node->data = data;
		new_node->next = NULL;

		return new_node;
	}

	void insert_at_end(Node ** head, int data){
		Node* new_node = create_node(data);
		if(*head == NULL){
			*head = new_node;
			return;
		}

		Node * temp = *head;

		while(temp->next != NULL){
			temp = temp->next;
		}

		temp->next = new_node;
	}

	void print_list(Node *list){
		Node *temp = list;
		while(temp !=NULL){
		printf("%d\n", temp->data);
		temp = temp->next;
		}
	}

	Node* search(Node **list, int target){
		Node *temp = *list;

		while(temp != NULL && temp->data != target){
			temp = temp->next;
		}
		return temp;
	}

	void delete(Node **list, int target){
		Node *temp = *list;
		Node *prev = NULL;

		if(temp == NULL){
			return;
		}

		if(temp->data == target){
			*list = temp->next;
			free(temp);
			return;
		}

		while(temp != NULL && temp->data != target){
			prev = temp;
			temp = temp->next;
		}

		if(temp == NULL){
			return;
		}
		prev->next = temp->next;
		free(temp);
	}

	int main(){

		Node* list = NULL;
		insert_at_end(&list, 10);
		insert_at_end(&list, 20);

		print_list(list);
		Node * ret = search(&list, 10);
		printf("%d\n", ret->data);
		delete(&list, 10);
		print_list(list);
		
	}