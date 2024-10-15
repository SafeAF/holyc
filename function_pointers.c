// Function pointers

#include <stdio.h>
#include <stdbool.h>

// the type of this function is
// int (*)(int, int);

int foo(int x, int y){
	return x + y;
}

// if even predicate function
bool pred(int x){
	return x % 2 == 0;
}

// functions in functions - filter 
// predicate function will return true if meets condition
void print_if(int buf[10], bool (*predicate)(int)){
	for(int i = 0; i < 10; i++){
		if(predicate(buf[i])){
			printf("%d\n", buf[i]);
		}
	}
}

//function pointer type
typedef int* (*FuncPtr)(int);


int main(){
	int bar[] = {1,2,3,4,5,6,7,8,9,10};

	// store a function in a var
	// as a function is just a pointer to code in mem
	int (*func)(int, int) = foo;

	printf("%d\n", func(3,4));

	print_if(bar, pred);



	return 0;
}