// strings
// all your binary are read by us

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MIN_STR_LEN 4

void print_strings(const char *filename){
	FILE *file = fopen(filename, "rb");
	if(!file){
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	char buffer[1024];
	int count = 0;

	while(1){
		size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
		if(bytesRead == 0) break; // end of file

		for(size_t i=0; i < bytesRead; i++){
			if(isprint(buffer[i])){ // print if printable
				putchar(buffer[i]);
				count++;
			} else {
				if(count >= MIN_STR_LEN) {
					putchar('\n'); // end of printable string seq
				}
				count = 0; //reset count
			}
		}
	}

	if(count >= MIN_STR_LEN){
		putchar('\n');
	}
	fclose(file);
}

int main(void){

}
