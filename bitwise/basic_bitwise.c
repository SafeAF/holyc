// basic bitwise operations


#include <stdio.h>
#include <stdint.h>
#include "binprint.h"

int main(){
	uint8_t a = 0b11001010;
	uint8_t b = 0b11110000;
	uint8_t ans = a & b;
	printf("%b\n", ans);

    uint8_t c = 0b10101010;
    uint32_t d = 0xDEADBEEF;

    PRINT_BIN(c); printf("\n");
    PRINT_BIN(d); printf("\n");

	return 0;
}