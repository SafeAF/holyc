#include <stdint.h>
#include <stddef.h>
#include <stdio.h>


typedef struct {
    void *ptr;         // The aligned pointer returned to the user
    size_t size;       // The requested size in bytes
    size_t alignment;  // Alignment boundary (e.g., 8, 16, 32)
    size_t offset;     // Offset from the start of the arena (for diagnostics)
} AlignedAlloc;


AlignedAlloc arena_alloc_aligned(char *arena, size_t *offset, size_t size, size_t alignment) {
    uintptr_t raw_addr = (uintptr_t)(arena + *offset);

    uintptr_t aligned_addr = (raw_addr + alignment - 1) & ~(alignment - 1);
    size_t padding = aligned_addr - raw_addr;

    size_t final_offset = *offset + padding;
    *offset = final_offset + size;

    AlignedAlloc alloc = {
        .ptr = (void *)aligned_addr,
        .size = size,
        .alignment = alignment,
        .offset = final_offset
    };

    return alloc;
}


int main() {
    char arena[1024 * 1024];
    size_t offset = 0;

    AlignedAlloc a = arena_alloc_aligned(arena, &offset, sizeof(double), 8);
    AlignedAlloc b = arena_alloc_aligned(arena, &offset, 64, 16);
    AlignedAlloc c = arena_alloc_aligned(arena, &offset, 128, 32);

    printf("A: ptr=%p  size=%zu  align=%zu  offset=%zu\n", a.ptr, a.size, a.alignment, a.offset);
    printf("B: ptr=%p  size=%zu  align=%zu  offset=%zu\n", b.ptr, b.size, b.alignment, b.offset);
    printf("C: ptr=%p  size=%zu  align=%zu  offset=%zu\n", c.ptr, c.size, c.alignment, c.offset);

    return 0;
}