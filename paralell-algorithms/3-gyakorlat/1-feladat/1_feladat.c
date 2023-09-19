#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdint.h>

typedef struct{
    int* array;
    int lower_range;
    int upper_range;
    int sum;
} ArrayWithRange;

/**
 * @brief Allocates an array of n integers and fills it with random numbers in the range of (0,32768)
 * 
 * @param n The length of the array to be allocated
 * @return int* A pointer to the allocated and filled array
 */
int* create_n_length_array_with_random_numbers(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 32768;
    }
    return arr;
}

/**
 * @brief Calculates the sum of an array within a specified range using a separate thread.
 * 
 * @param arg Pointer to an ArrayWithRange struct.
 * @return Void pointer to the result (not used in this implementation).
*/
void* thread_sum_array_with_range(void* arg) {
    ArrayWithRange* array_with_range = (ArrayWithRange*) arg;

    int sum = 0;
    for (int i = array_with_range->lower_range; i < array_with_range->upper_range; i++) {
        sum += array_with_range->array[i];
    }
    array_with_range->sum = sum;
}

/**
 * @brief Splits an array into parts and calculates the sum using multiple threads.
 * 
 * @param array Pointer to an integer array.
 * @param array_size The size of the integer array.
 * @param number_of_threads The number of threads to use for the calculation.
*/
void sum_of_array_with_n_threads(int* array, int array_size, int number_of_threads){
    // Calculate the length of each part of the splitting.
    float quotient = (float) array_size / number_of_threads; // divide the number into n parts
    int part_size = floor(quotient); // round the result to the nearest integer

    int remainder = array_size % part_size; // calculate the remaining amount after division 
    int num_parts_with_extra = remainder; // the number of parts with an extra element

    int num_parts_without_extra = number_of_threads - num_parts_with_extra; // the number of parts without an extra element

    // Create an array of ArrayWithRange with the divided array.
    int array_with_range_size = num_parts_with_extra + num_parts_without_extra;
    ArrayWithRange* arrays_with_range = (ArrayWithRange*) malloc(array_with_range_size * sizeof(ArrayWithRange));
    int current_lower_range = 1;
    for(int i = 0; i < array_with_range_size; i++){
        arrays_with_range[i].array = array;
        arrays_with_range[i].lower_range = current_lower_range - 1; 
        if(remainder != 0){
            arrays_with_range[i].upper_range = arrays_with_range[i].lower_range + part_size + 1;
            remainder--;
        }else{
            arrays_with_range[i].upper_range = arrays_with_range[i].lower_range + part_size;
        }
        current_lower_range = arrays_with_range[i].upper_range + 1;
    }

    // Start threads
    double time_elapsed;
    clock_t start_time, end_time;
    start_time = clock();
    
    pthread_t threads[number_of_threads];
    for(int i = 0; i < array_with_range_size; i++){
        pthread_create(&threads[i], NULL, thread_sum_array_with_range, &arrays_with_range[i]);
    }

    // Wait for threads
    for(int i = 0; i < number_of_threads; i++){
        pthread_join(threads[i], NULL);
    }

    end_time = clock();
    time_elapsed = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    // Print thread results
    int total_thread_result = 0;
    printf("Array Size: %d\nNumber of Threads: %d\nTime to Sum: %lf\n\n", array_size, number_of_threads, time_elapsed);
    for(int i = 0; i < number_of_threads; i++){
        printf("thread_results[%ld]: %d\n", threads[i], arrays_with_range[i].sum);
        total_thread_result += arrays_with_range[i].sum;
    }
    printf("total_thread_result: %d\n\n", total_thread_result);
}

/**
 * Write a program, that sums the elements of an array using threads!
 * - The program should work for an array of any size.
 * - The program should split the array in equal lengths.
 * - Try using recursion for the splitting.
 * - Compare it to using only one thread.
 * - Use different number of threads and inputs.
 * - Make a graph for it. (Can be found as 1_feladat.xlsx)
 * 
 * How to compile:
 * 
 * gcc 1_feladat.c -o 1_feladat.exe -pthread -lm
*/
int main(){
    int array_size = 0;
    int* array;

    // Size incrementation
    for(int array_size = 1000; array_size < 10000; array_size = array_size + 1000){
        // Array initialization. Using the same array for every thread test.
        array = create_n_length_array_with_random_numbers(array_size);

        // Thread incrementation
        for(int number_of_threads = 1; number_of_threads < 11; number_of_threads++){
            sum_of_array_with_n_threads(array, array_size, number_of_threads);
        }
    }

    return 0;
}