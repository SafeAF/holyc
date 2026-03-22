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

static void* worker(){
    long i = 0;
    for(;;){
        i++;
    }
    return NULL;
}



int main(void){
    long nthreads = cpu_cores_online();
    printf("Number of online CPU cores: %ld\n", nthreads);

    
    pthread_t* threads = malloc(sizeof(pthread_t) * nthreads);

    if(!threads){
        perror("malloc");
        return 1;
    }

    for(long i = 0; i < nthreads; i++){
        pthread_create(&threads[i], NULL, worker, NULL);
    }

    pause();
    return 0;


}

