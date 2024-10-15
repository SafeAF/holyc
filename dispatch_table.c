// dispatch table


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void foo(){
	printf("Foo!\n");
}

void bar(){
	printf("Bar!\n");
}
void baz(){

	printf("baz!\n");
}

void (*dispatch[3])(void) = {foo, bar, baz};

int main(){
	
	
for(int i = 0;i < 3; i++){
dispatch[i]();

sleep(1);
}
}