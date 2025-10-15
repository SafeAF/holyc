// Arena.h

#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typdef struct Arena {
	uint8_t *base;
	size_t capacity;
	size_t offset;
	bool owns_memory;
} Arena;

typedef size_t ArenaMarker;


int arena_init_owned(Arena *a, size_t capacity, size_t base_alignment);
void arena_destroy(Arena *a);
