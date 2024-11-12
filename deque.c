//deque

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct Dequeu{
	Node *front;
	Node *back;
} Deque;

Deque* create_deque(){
	Deque *deque = malloc(sizeof(Deque));
	deque->front = deque->back = NULL;
	return deque;
}

void push_front(Deque *deque, int value){
	Node* node = malloc(sizeof(Node));
	node->data = value;
	node->next = deque->front;
	node->prev = NULL;

	if(deque->front){
		deque->front->prev = node;
	}

	deque->front = node;
	if(!deque->back){
		deque->back = node;
	}
}


int main(void){

}