#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define NUMBER_OF_THREADS 60

/**
 * @brief Mock task that sleeps for 1 second.
*/
void* wait_one_second(void* _){
    printf("[%ld] - Calculating...\n", pthread_self());
    sleep(1);
    printf("[%ld] - Finished Calculating.\n", pthread_self());
}

/**
 * Write a program that starts 60 threads, each "calculating" for 1 seconds. How long does the program run.
 * 
 * How to compile:
 * 
 * gcc 2_feladat.c -o 2_feladat.exe -pthread
*/
int main(){
    pthread_t threads[NUMBER_OF_THREADS];
    double time_elapsed;
    clock_t start_time, end_time;


    start_time = clock();
    // Start threads
    for(int i = 0; i < NUMBER_OF_THREADS; i++){
        pthread_create(&threads[i], NULL, wait_one_second, NULL);
    }

    // Wait for thread convergion
    for (int i = 0; i < NUMBER_OF_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    end_time = clock();
    time_elapsed = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    
    printf("The time it took for the program to finish running: %lf\n", time_elapsed);

    return 0;
}