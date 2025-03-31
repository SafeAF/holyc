// binprint.h
#ifndef BINPRINT_H
#define BINPRINT_H

#include <stdint.h>
#include <stdio.h>

// Internal helper function to print `bits` bits of `val`
static inline void print_binary(uint64_t val, int bits) {
    for (int i = bits - 1; i >= 0; --i) {
        putchar((val >> i) & 1 ? '1' : '0');
    }
}

// Public macro to print binary of any unsigned integer type
#define PRINT_BIN(x) _Generic((x), \
    uint8_t:  print_binary(x, 8),  \
    uint16_t: print_binary(x, 16), \
    uint32_t: print_binary(x, 32), \
    uint64_t: print_binary(x, 64), \
    default:  print_binary((uint64_t)(x), sizeof(x) * 8) \
)

#endif // BINPRINT_H
