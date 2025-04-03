#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
    size_t pagesize = sysconf(_SC_PAGESIZE);
    void *mem = mmap(NULL, pagesize, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (mem == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Use the memory
    snprintf(mem, pagesize, "Hello from mmap!\n");
    printf("%s", (char *)mem);

    // Clean up
    munmap(mem, pagesize);
    return 0;
}