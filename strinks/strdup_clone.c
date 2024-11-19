// strdup clone

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * strdupe(char *s){
	size_t len = strlen(s);
	char *copy = malloc(sizeof(len) + 1);

	if(copy){
		memcpy(copy, s, len);
	}
	return copy;
}

int main(){
	char * foo = "barbaz";
	char * baz = NULL;

	baz = strdupe(foo);
	printf("Copied var: %s\n", baz);
}