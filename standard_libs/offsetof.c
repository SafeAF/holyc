// stddef offsetof

#include <stddef.h>
#include <stdio.h>

struct Boo {
	char foo;
	int bar;
	short baz;
};

int main(void){
	struct Boo bonk;

	printf("%zu\n", offsetof(struct Boo, foo));
	printf("%zu\n", offsetof(struct Boo, bar));
	printf("%zu\n", offsetof(struct Boo, baz));
}