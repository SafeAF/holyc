// arena memory allocated without malloc and free

#include <stdio.h>

typedef struct Pool {
	char memory[1024 * 1024];
	size_t arena_offset;
} Pool;

void pool_init(Pool *p) {
    p->arena_offset = 0;
}

void *pool_alloc(Pool *p, size_t size){
	size_t aligned_size = (size + 7) & ~7;
	if(p->arena_offset + aligned_size > sizeof(p->memory)){
		return NULL;
	}
	// pointer to first byte of free memory
	void *ptr = &p->memory[p->arena_offset];
	p->arena_offset += aligned_size;
	return ptr;
}


int main(void){
	
}

