//min max linked list

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

typedef struct LinkedList {
	struct Node *head;
	int min_val;
	int max_val;
} LinkedList;


LinkedList* create_list(){
	LinkedList *list = malloc(sizeof(LinkedList));
	list->min_val = INT_MAX;
	list->max_val = INT_MIN;
	list->head = NULL;

	return list;
}

void insert(LinkedList *list, int data){
	Node* newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = list->head;
	list->head = newNode;

	if(data > list->max_val) list->max_val = data;
	if(data < list->min_val) list->min_val = data;
}

void delete_node(LinkedList *list, int value){
	Node *temp = list->head; // use temp to traverse list
	Node *prev = NULL;

	while(temp != NULL && temp->data != value){
		prev = temp; // store prev for when we find node
		temp = temp->next;
	}

	if(temp == NULL) return; //didn't find it

	if(prev == NULL){
		list->head = temp->next; // first item was target
	}
	else { // set the prev node ptr to the one temp next points to
		prev->next = temp->next; 
	}

	if(temp->data == list->min_val || temp->data == list->max_val){
		list->min_val = INT_MAX;
		list->max_val = INT_MIN;
		Node *current = list->head;

		while(current != NULL){
			if(current->data < list->min_val) list->min_val = current->data;
			if(current->data > list->max_val) list->max_val = current->data;
			current = current->next;
		}
	}
	free(temp);

}

void print_list(LinkedList *list){
	Node *temp = list->head;

	while(temp != NULL){
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
	printf("List min: %d List max: %d\n", list->min_val, list->max_val);
}

void reverse(LinkedList *list){
	Node *prev = NULL;
	Node *current = list->head;
	Node *next = NULL;

	while(current != NULL){
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	list->head = prev;
}































void reverse2(LinkedList *linkedlist){
	Node *current = linkedlist->head
	Node *prev = NULL
	Node *next = NULL;

	while(current != NULL){
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	list->head = prev;
}
















	

int main(){
	LinkedList *list = create_list();
	insert(list, 10);
	insert(list, 20);
	insert(list, 30);
	insert(list, 6);
	print_list(list);
	delete_node(list, 30);
	print_list(list);
	reverse(list);
	print_list(list);
}