#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/**
 * @brief Performs a mock task as a thread. It was designed to throw a runtime error if the given arg is equal to 2. 
*/
void* thread_func(void* arg) {
    int id = *((int*) arg);
    printf("Thread %d starting\n", id);
    if (id == 2) {
        sleep(2);
        int* ptr = NULL;
        *ptr = 10;  // This will cause a runtime error
    } else {
        sleep(5);
    }
    printf("Thread %d exiting\n", id);
    pthread_exit(NULL);
}

/**
 * Write a program that will have a runtime error in one of the threads. What will happen?
 * 
 * Answer: Program runs into segmentation fault.
 * 
 * How to compile:
 * 
 * gcc 4_feladat.c -o 4_feladat.exe -pthread
*/
int main() {
    pthread_t threads[5];
    int ids[5] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, thread_func, &ids[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("All threads finished\n");
    return 0;
}
