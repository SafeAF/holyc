// stack

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 500

typedef struct Stack {
	int topIndex;
	int data[MAX_SIZE];
} Stack;


void push(Stack *stacko, int value){
	if(stacko->topIndex >= MAX_SIZE - 1){
		perror("Stack overflow\n");
		exit(1);
	}
	stacko->data[++stacko->topIndex] = value;
}

int pop(Stack *stacko){
	if(stacko->topIndex < 1){
		perror("Stack Underflow\n");
		exit(1);
	}
	return stacko->data[stacko->topIndex--];
}


int main(){
		
	Stack *stacko = malloc(sizeof(Stack));
	stacko->topIndex = -1; //empty stack.
	push(stacko, 5);
	push(stacko, 10);
	int foo = pop(stacko);

	printf("Popped %d\n", foo);

}