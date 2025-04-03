// basic bitwise operations


#include <stdio.h>
#include <stdint.h>
#include "binprint.h"

int main(){
	uint8_t a = 0b11001010;
	uint8_t b = 0b11110000;
	uint8_t ans = a & b;

	printf("AND\n");
	PRINT_BIN(a);printf("\n");
	PRINT_BIN(b);printf("\n");
	PRINT_BIN(ans);printf("\n");

	printf("BIT SHIFT << 1 (mult by 2)\n");
	uint8_t x = 0b00000101;
	PRINT_BIN(x); printf("\n");
	uint8_t res = x << 1;

	PRINT_BIN(res); printf("\n");



    // uint8_t c = 0b10101010;
    // uint32_t d = 0xDEADBEEF;

    // PRINT_BIN(c); printf("\n");
    // PRINT_BIN(d); printf("\n");


	return 0;
}