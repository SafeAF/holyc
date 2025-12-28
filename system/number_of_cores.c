#define _POSIX_C_SOURCE 200112L 
/* For sysconf and _SC_NPROCESSORS_ONLN */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static long cpu_cores_online(void){
    long n = sysconf(_SC_NPROCESSORS_ONLN);
    if(n <1) n=1;
        return n;
}

int main(void){
    long nthreads = cpu_cores_online();
    printf("Number of online CPU cores: %ld\n", nthreads);
    return 0;
}