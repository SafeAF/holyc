#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#define ARENA_SIZE (1024 * 1024) // 1 MB

typedef struct {
    char memory[ARENA_SIZE]; // Raw memory buffer
    size_t arena_offset;     // Offset into memory
} Pool;

// Align to 8 bytes (can change to 16 or sizeof(max_align_t) for stricter alignment)
size_t align_up(size_t n, size_t alignment) {
	// ADD alignment to n to push up to next multiple
	// AND result with alignment to chop off lower bits
	// to ensure multiple of alignment.
    return (n + alignment - 1) & ~(alignment - 1);
}

// Initialize the arena (reset offset to zero)
void pool_init(Pool *p) {
    p->arena_offset = 0;
}

// Reset arena to empty
void pool_reset(Pool *p) {
    p->arena_offset = 0;
    printf("[RESET] Arena reset to offset 0\n");
}

// Allocate memory from the arena
void *pool_alloc(Pool *p, size_t size) {
    size_t aligned_size = align_up(size, 8);

    if (p->arena_offset + aligned_size > ARENA_SIZE) {
        printf("[ERROR] Out of memory: requested %zu bytes (aligned to %zu), offset %zu\n",
               size, aligned_size, p->arena_offset);
        return NULL;
    }

    void *ptr = &p->memory[p->arena_offset];
    printf("[ALLOC] %zu bytes at offset %zu (aligned to %zu), returning address %p\n",
           size, p->arena_offset, aligned_size, ptr);

    p->arena_offset += aligned_size;
    return ptr;
}



void *arena_alloc_aligned(char *memory, size_t *offset, size_t size, size_t alignment) {
    uintptr_t raw_addr = (uintptr_t)(memory + *offset);

    // Align the address up
    uintptr_t aligned_addr = (raw_addr + alignment - 1) & ~(alignment - 1);

    // Compute how much extra space we just jumped
    size_t padding = aligned_addr - raw_addr;

    // Update the offset with both padding and size
    *offset += padding + size;

    return (void *)aligned_addr;
}

int main() {
    Pool my_pool;
    pool_init(&my_pool);

    void *a = pool_alloc(&my_pool, 24);
    void *b = pool_alloc(&my_pool, 40);
    void *c = pool_alloc(&my_pool, 1000);
    void *d = pool_alloc(&my_pool, 1024 * 1024); // too big, should fail

    printf("Addresses:\n");
    printf("  a: %p\n", a);
    printf("  b: %p\n", b);
    printf("  c: %p\n", c);
    printf("  d: %p (should be NULL)\n", d);

    pool_reset(&my_pool);

    void *e = pool_alloc(&my_pool, 128);
    printf("After reset, e: %p\n", e);

    return 0;
}

