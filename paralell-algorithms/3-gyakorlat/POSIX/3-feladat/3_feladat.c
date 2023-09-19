#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../../helper-libraries/dynamic_array.h"    

#define NUMBER_OF_THREADS 10

DynamicArray dynamic_shared_array;
pthread_mutex_t lock;

/**
 * @brief Check if given int parameter is a prime.
 * 
 * @param n : The number to check.
 * 
 * @retval 0 : Not a prime.
 * @retval 1 : Is a prime.
*/
int is_prime(int n) {
    if (n < 2) {
        return 0;
    }
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

/**
 * POSIX thread startable function that takes an n number as an argument. The range is calculated the following way:
 * 
 * lower limit = n * 100
 * 
 * upper limit = (n * 100) + 99
*/
void* add_primes_in_range_to_global_dynamic_array(void* args){
    int number_of_primes = 0;

    int lower_limit = *((int*)args) * 100;
    int upper_limit = (*((int*)args) * 100) + 99;
    
    for(int i = lower_limit; i < upper_limit; i++){
        if(is_prime(i)){
            number_of_primes++;

            // Add to global int array
            pthread_mutex_lock(&lock);
            add_element_to_dynamic_array(&dynamic_shared_array, i);
            pthread_mutex_unlock(&lock);
        }
    }
}

/**
 * Write a program that uses 10 threads to calculate how many primes are in the ranges:
 * [0,99], [100,199], [200,299], [300,399], [400,499], [500,599], [600,699], [700,799], [800,899], [900,999]
 * 
 * How to compile:
 * 
 * gcc 3_feladat.c ../../../helper-libraries/dynamic_array.c -o 3_feladat.exe -pthread
*/
int main(){
    pthread_t threads[NUMBER_OF_THREADS];
    int exception = 0;
    int i_args[NUMBER_OF_THREADS];
    
    // Initialize the dynamic array
    exception = init_dynamic_array(&dynamic_shared_array, 0);
    if(exception){
        printf("Failed to initialize array, because of invalid size value. Terminating program.");
        return 1;
    }

    // Start threads
    for(int i = 0; i < NUMBER_OF_THREADS; i++){
        i_args[i] = i;
        pthread_create(&threads[i], NULL, add_primes_in_range_to_global_dynamic_array, &i_args[i]);
    }

    // Wait for threads to converge
    for (int i = 0; i < NUMBER_OF_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    // Print out the shared array
    for(int i = 0; i < dynamic_shared_array.size; i++){
        printf("dynamic_shared_array[%d] = %d\n", i, dynamic_shared_array.arr[i]);
    }
    
    return 0;
}