//func ptr test 2

#include <stdio.h>

int add(int x, int y){
	return x+y;
}


int main(){
	
	int result;

	int (*addfunc)(int, int) = add;

	result = addfunc(2, 3);

	printf("result is %d\n", result);
}