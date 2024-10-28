#include <stdio.h>

int add(int x, int y){
	return x + y;
}

int main(void){
	
	int (*func)(int, int) = &add;
	printf("%d\n", func(3,4));

	return 1;
}