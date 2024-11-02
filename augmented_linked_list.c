// augmented linked list

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

typedef struct LinkedList {
	int size;
	struct Node *tail;
	struct Node *head;
} LinkedList;


LinkedList* create_list(){
	LinkedList *list = malloc(sizeof(LinkedList));
	list->head = NULL;
	list->size = 0;
	return list;
}

void insert_at_beginning(LinkedList *list, int data){
	Node *new_node = malloc(sizeof(Node));
	new_node->data = data;
	new_node->next = list->head;
	list->head = new_node;
	list->size++;
}

void print_list(LinkedList *list){
	Node *current = list->head;

	while(current != NULL){
		printf("%d -> ", current->data);
		current = current->next;
	}

	printf("NULL \n");
}




int main(){
	LinkedList *list = create_list();
	insert_at_beginning(list, 10);
	insert_at_beginning(list, 20);

printf("List size after insertion: %d\n", list->size);
print_list(list);
}























// Node* create_node(int data){
// 	Node *new_node = malloc(sizeof(Node));

// 	if(new_node == NULL){
// 		return NULL;
// 	}

// 	new_node->data = data;
// 	new_node->next = NULL;

// 	return new_node;
// }

// void insert_at_end(Node **head, int data){
// 	Node *new_node = create_node(data);

// 	if(*head == NULL){
// 		*head = new_node;
// 		return;
// 	}

// 	Node *temp = *head;
	
// 	 while(temp->next != NULL){
// 	  	temp = temp->next;
// 	  }
// 	  temp->next = new_node;
// }

// void print_list(Node **head){
// 	Node *temp = *head;

// 	while(temp != NULL){
// 		printf("%d ", temp->data);
// 		temp = temp->next;
// 	}
// 	printf("\n");


// }

// void insert_at_beginning(Node **head, int data){
// 	Node *new_node = create_node(data);

// 	Node *old_head = *head;
// 	*head = new_node;
// 	new_node->next = old_head;

// 	return;
// }

// void insert_at_nth(Node **head, int data, int index){
// 	Node *new_node = create_node(data);

// 	Node *temp = *head;

// 	if(index == 0){
// 		insert_at_beginning(head, data);
// 		return;
// 	}

// 	for(int i = 0; i < index - 1; i++){
// 		if(temp == NULL){
// 			free(new_node);
// 		}
// 		temp = temp->next;
// 	}

// 	Node *old_node = temp->next;
// 	temp->next = new_node;
// 	*temp = *new_node;
// 	new_node->next = old_node; 
// }


// Node* search(Node** head, int target){
// 	Node *temp = *head;

// 	while(temp != NULL && temp->data != target){
// 		temp = temp->next;
// 	}
// 	return temp;
// }

// // void delete(Node **head, int target){
// // 	Node *temp = *head
// // 	Node *prev = NULL;

// // 	if(temp != NULL && temp->data == target){
// // 		*head = temp->next;
// // 		free(temp);
// // 		return
// // 	}

// // 	while(temp->next != NULL && temp->data != target){
// // 		prev = temp;
// // 		temp = temp->next;
// // 	}
// // 	if(temp == NULL) return;

// // 	prev->next = temp->next;

// // 	free(temp);
// // }







// void delete2(Node **head, int target){
// 	Node *temp = *head;
// 	Node *prev = NULL;

// 	if(temp != NULL && temp->data == target){
// 		*head = temp->next;
// 		free(temp);
// 		return; 
// 	}

// 	while(temp != NULL && temp->data != target){
// 		prev = temp;
// 		temp = temp->next;
// 	}

// 	if(temp == NULL){
// 		return;
// 	}

// 	 prev->next = temp->next;
// 	 free(temp);
// }



// int delete3(Node **head, int target){
// 	Node *temp = *head;
// 	Node *prev = NULL;


// 	if(temp != NULL && temp->data == target){
// 		*head = temp->next;
// 		free(temp);
// 		return 1;
// 	}

// 	while(temp != NULL && temp->data != target){
// 		prev = temp;
// 		temp = temp->next;
// 	}

// 	if(temp == NULL){
// 		return 0;
// 	}

// 	prev->next = temp->next;
// 	free(temp);
// 	return 1;
// }


// void insert_at_beginning2(Node **head, int data){
// 	Node *new_node = create_node(data);
// 	Node *temp = *head;

// 	*head = new_node;
// 	new_node->next = temp;
// 	return;
// }






// int main(void){
// 	Node *head = NULL;
// 	insert_at_end(&head, 10);
// 	insert_at_end(&head, 20);
// 	insert_at_end(&head, 40);
// 	insert_at_end(&head, 50);
// 	//printf("%p %d\n", &head, head->data);	
// 	//print_list(&head);
// 	//insert_at_beginning(&head, 30);
// 	//print_list(&head);
// 	//insert_at_nth(&head, 15, 2);
// 	//insert_at_nth(&head, 15,4);
// 	print_list(&head);

// 	Node* result = search(&head, 20);
// 	if(result != NULL){
// 	printf("Result found: %d\n", result->data);
// 	}

// 	int did_delete_node = delete3(&head, 20);

// 	printf("Did a node get deleted?: %d\n", did_delete_node);

// 	result = search(&head, 20);
// 	if(result != NULL){
// 	printf("Result found: %d\n", result->data);
// 	} else {
// 		printf("Result %d not found\n");
// 	}

// 	insert_at_beginning2(&head, 100);

// 	print_list(&head);
// }

