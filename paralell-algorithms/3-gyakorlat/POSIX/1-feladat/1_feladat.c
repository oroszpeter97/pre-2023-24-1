#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define NUMBER_OF_THREADS 2


/**
 * @brief Waits for 4 seconds and then prints a message indicating that the wait is complete.
 * 
 * @param _ A pointer to the thread's argument (not used in this function)
 * @return void* Nothing is returned from this function
 */
void* wait_for_four_seconds(void* _){
    pthread_t this_thread = pthread_self();

    printf("[%ld] - Waiting...\n", this_thread);
    sleep(4);
    printf("[%ld] - Waited 4 seconds.\n", this_thread);
}

/**
 * @brief Creates a new thread that waits for 4 seconds, while the main thread waits for 8 seconds.
 * 
 * @param _ A pointer to the thread's argument (not used in this function)
 * @return void* Nothing is returned from this function
 */
void* wait_for_eight_seconds(void* _){
    pthread_t sub_thread;

    pthread_create(&sub_thread, NULL, wait_for_four_seconds, NULL);
    printf("[%ld] - Waiting...\n", pthread_self());
    sleep(8);
    printf("[%ld] - Waited 8 seconds.\n", pthread_self());
}

/**
 * Write a program that starts a thread that "calculates" for 8 seconds, while the thread started by it "calculates" for 4 seconds. 
 * 
 * How to compile:
 * 
 * gcc 1_feladat.c -o 1_feladat.exe -pthread
*/
int main(){
    pthread_t mainthread;

    pthread_create(&mainthread, NULL, wait_for_eight_seconds, NULL);
    pthread_join(mainthread, NULL);

    return 0;
}