// lambda functions in C

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	// size and data?
	int (*func) (int, void *);
	void *context;
} lambda_t;

#define lambda(return_type, context_type, context_ptr, body)
	({
		return_type __fn__ (int x, void *context) body lambda_t l
			= {.func = __fn__,
				.context = (void*) context_ptr};
		l;
	})