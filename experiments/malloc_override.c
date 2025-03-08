// messing with LD_PRELOAD and custom malloc
//$ gcc -shared -fPIC -o malloc_override.so malloc_override.c -ldl
//$ LD_PRELOAD=./malloc_override.so ls

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


static void *(*real_malloc)(size_t) = NULL;

void* malloc(size_t size) {
    if (!real_malloc) {
        real_malloc = dlsym(RTLD_NEXT, "malloc");
        if (!real_malloc) {
            fprintf(stderr, "Error in dlsym: %s\n", dlerror());
            exit(EXIT_FAILURE);
        }
    }

    void *ptr = real_malloc(size);
    printf("malloc(%zu) = %p\n", size, ptr);
    return ptr;
}