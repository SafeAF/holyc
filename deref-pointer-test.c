// deref an int pointer

#include <stdio.h>

void foo(int *x){
	int y; 

	y = *(int *)x;

	printf("value is %d\n", y);
}

int main(){
	int y = 5;

	foo(&y);
}