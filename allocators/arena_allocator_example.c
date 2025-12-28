#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdalign.h>

#define ARENA_CAPACITY (1024 * 64) /* 64 KB */

typedef struct {
    unsigned char *memory;
    size_t capacity;
    size_t offset;
} Arena;

static size_t align_up(size_t value, size_t alignment) {
    return (value + alignment - 1) & ~(alignment - 1);
}

static void arena_init(Arena *arena, void *backing_memory, size_t backing_size) {
    arena->memory = (unsigned char *)backing_memory;
    arena->capacity = backing_size;
    arena->offset = 0;
}

static void arena_reset(Arena *arena) {
    arena->offset = 0;
}

static void *arena_alloc_aligned(Arena *arena, size_t size, size_t alignment) {
    size_t aligned_offset = align_up(arena->offset, alignment);
    if (aligned_offset + size > arena->capacity) {
        return NULL;
    }

    void *ptr = arena->memory + aligned_offset;
    arena->offset = aligned_offset + size;
    return ptr;
}

static void *arena_alloc(Arena *arena, size_t size) {
    return arena_alloc_aligned(arena, size, alignof(max_align_t));
}

int main(void) {
    unsigned char backing_memory[ARENA_CAPACITY];
    Arena arena;

    arena_init(&arena, backing_memory, sizeof(backing_memory));

    int *numbers = (int *)arena_alloc(&arena, 8 * sizeof(*numbers));
    if (!numbers) {
        printf("Allocation failed for numbers\n");
        return 1;
    }

    for (int i = 0; i < 8; i++) {
        numbers[i] = i * 10;
    }

    char *message = (char *)arena_alloc_aligned(&arena, 32, 16);
    if (!message) {
        printf("Allocation failed for message\n");
        return 1;
    }

    strncpy(message, "hello arena", 32);
    printf("message: %s\n", message);

    printf("numbers:");
    for (int i = 0; i < 8; i++) {
        printf(" %d", numbers[i]);
    }
    printf("\n");

    printf("arena used: %zu / %zu bytes\n", arena.offset, arena.capacity);

    arena_reset(&arena);
    printf("after reset: %zu / %zu bytes\n", arena.offset, arena.capacity);

    return 0;
}
