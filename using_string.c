// strings

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int compare_strings(const void *a, const void *b){
	return strcmp(*(const char **)a, *(const char **)b);
}

int bar(const char *format, ...);


int main(){
	const char *arr[] = {"orange", "lemon", "apple", "grape"};

	int size = sizeof(arr) / sizeof(arr[0]); // number of elems in array

	qsort(arr, size, sizeof(char*), compare_strings);

}