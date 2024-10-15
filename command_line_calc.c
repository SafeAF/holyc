// command line calc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add(void){
	printf("Add\n");
}

void subtract(void){
	printf("Subtract\n");
}

typedef struct {
	char *command;
	void (*function)(void);
} Command;

int main(){
	Command dispatch[] = {
		{"add", add},
		{"subtract", subtract},
		{NULL, NULL} // sentinel value to mark end of table
	};

	char input[20];
	printf("Enter a command (and or subtract): ");
	scanf("%s", input);

	for(int i = 0; dispatch[i].command != NULL; i++){
		if(strcmp(input, dispatch[i].command) == 0){
			dispatch[i].function();
			return 0;
		}	
	}
}

