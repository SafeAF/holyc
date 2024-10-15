// func pointer test

#include <stdio.h>
#include <stdlib.h>

int add(int x, int y){
	return x+y;
}


int main(){


	int (*function)(int, int);
	printf("function pointer at %p value %p\n", function, *function);
	function = &add;
	printf("function pointer at %p value %p\n", function, *function);

	// int result;	
	// result = function(3,5);

	// printf("result is %d\n", result);
	return 1;
}