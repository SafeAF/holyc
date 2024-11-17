#include <stdio.h>

int main(int argc, char *argv[]){
	argv++;

	while(*argv && *argv[0] == '-'){
		printf("%s\n", *argv);
		argv++;
	}
	return 0;
}