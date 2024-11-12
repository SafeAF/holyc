// memory leaker

#include <stdio.h>
#include <stdlib.h>


int main(){
	for(;;){
		int *foo = malloc(sizeof(int));
	}
}