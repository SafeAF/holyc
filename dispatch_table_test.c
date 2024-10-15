// dispatch table test

#include <stdio.h>
#include <stdlib.h>


void foo(void){
	printf("Foo\n");
}

void bar(void){
	printf("Bar\n");
}


int main(){
	
	void (*table[2])(void) = {foo, bar};

	table[2]();

}