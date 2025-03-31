// holy smokes lets attempt to make a dynamic array w/o
// cheating off chadgpt's homework using only an English
// language description from chatgpt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 1000

typedef struct {
	int *data;
	int size;
	int capacity;
} Array;

Array* array_init(){
	Array *new_array = malloc(sizeof(Array));
	new_array->data = malloc(sizeof(int) * INITIAL_SIZE);
	if (!new_array || !new_array->data) {
    	fprintf(stderr, "Memory allocation failed\n");
    	exit(1);
	}
	new_array->size = 0;
	new_array->capacity = INITIAL_SIZE;

	return new_array;
}

void append(Array *ary, int value){
	if(ary->size == ary->capacity){
		int *temp = malloc(sizeof(int) * ary->capacity * 2);
		if (!temp) {
    		fprintf(stderr, "Reallocation failed\n");
    		exit(1);
		}
		ary->capacity *= 2;
		memcpy(temp, ary->data, sizeof(int) * ary->size);
		free(ary->data);
		ary->data = temp;
	}

	ary->data[ary->size] = value;
	ary->size++;
}

int get(Array *array, int index){
	if(index < 0 || index >= array->size){
		fprintf(stderr, "Index %d out of bounds (size %d)\n", index, array->size);
		exit(1);
	}
	return array->data[index];
}

void set(Array *array, int index, int value){
	if(index < 0 || index >= array->size){
		fprintf(stderr, "Index %d out of bounds (size %d)\n", index, array->size);
		exit(1);
	}
	array->data[index] = value;
}

int main(){
	Array *array = array_init();
	append(array, 10);
	set(array, 1, 20);
	int ret = get(array, 1);
	printf("test %d\n", ret);

	free(array->data);
	free(array);
	return 0;
}