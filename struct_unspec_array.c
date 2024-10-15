// struct with unspec array

#include <stdio.h>
#include <stdlib.h>


typedef struct {
	int size;
	int data[];
} Array;


int main(){
	int size = 5;
	Array *ary = malloc(sizeof(Array) + sizeof(int) * size);
	ary->size = size;

	for(int i=0; i<size; i++){
		ary->data[i] = i * i;
	}

	for(int i=0; i<size; i++){
		printf("array[%d]: %d", ary->data[i], i);
	}

	free(ary);

}