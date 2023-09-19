#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include "helper-libraries/validator.h"
#include "helper-libraries/range.h"
#include "helper-libraries/timer.h"

int* array;
int array_length, value_lower_limit, value_upper_limit, number_of_threads;
Range* ranges;
double important_times[10];
pthread_mutex_t lock;

/**
 * @brief Map an integer value to a double value within a specified range.
 *
 * This function maps an integer value to a double value within a specified range using linear mapping.
 * It takes the input integer value and maps it to a double value within the given range defined by the
 * minimum and maximum integer values and the corresponding minimum and maximum double values.
 *
 * @param value The integer value to be mapped.
 * @param i_min The minimum value of the integer range.
 * @param i_max The maximum value of the integer range.
 * @param d_min The minimum value of the double range.
 * @param d_max The maximum value of the double range.
 * @return The mapped double value.
 */
long double map_int_to_double(int value, int i_min, int i_max, double d_min, double d_max){
    return (double)(value - i_min) * (double)(d_max - d_min) / (double)(i_max - i_min) + d_min;
}

/**
 * @brief Define the ranges for splitting the array.
 *
 * This function defines the ranges for splitting the array into subsets for parallel processing.
 * It calculates the length of each part based on the total array length and the number of threads.
 * The ranges are stored in the dynamically allocated array of Range structs.
 *
 * @return This function does not return a value.
 */
void define_ranges(){
    float quotient;
    int part_size, remainder;

    ranges = (Range*)malloc(number_of_threads * sizeof(Range));

    // Calculate the length of each part of the splitting.
    quotient = (float) array_length / number_of_threads; // divide the number into n parts
    part_size = floor(quotient); // round the result to the nearest integer

    remainder = array_length % part_size; // calculate the remaining amount after division

    // Create the array of subset arrays
    int current_lower_range = 1;
    for(int i = 0; i < number_of_threads; i++){
        ranges[i].lower_range = current_lower_range - 1;
        if(remainder != 0){
            ranges[i].upper_range = ranges[i].lower_range + part_size + 1;
            remainder--;
        }else{
            ranges[i].upper_range = ranges[i].lower_range + part_size;
        }
        current_lower_range = ranges[i].upper_range + 1;
    }
}

/**
 * @brief Initialize the array with random values within a given range.
 *
 * This function is executed as a POSIX thread and initializes the array with random values
 * within the specified range for a specific range index. The array memory is allocated using
 * dynamic memory allocation. The random values are generated based on the lower and upper limits.
 *
 * @param args A pointer to the range index.
 * @return This function does not return a value.
 */
void* pt_initialize_array(void* args){
    int range_index = *(int*)args;
    array = (int*)malloc(array_length * sizeof(int));
    
    srand(time(NULL));
    for(int i = ranges[range_index].lower_range; i < ranges[range_index].upper_range; i++){
        array[i] = rand() % (value_upper_limit - value_lower_limit + 1) + value_lower_limit ;
    }
}

/**
 * @brief Calculate the sum of values within a given range.
 *
 * This function is executed as a POSIX thread and calculates the sum of values within
 * the specified range. It updates the corresponding range struct with the calculated sum.
 *
 * @param args A pointer to the range index.
 * @return This function does not return a value.
 */
void* pt_sum(void* args){
    int range_index = *(int*)args;

    ranges[range_index].sum = 0;
    for(int i = ranges[range_index].lower_range; i < ranges[range_index].upper_range; i++){
        ranges[range_index].sum += array[i];
    }
}

/**
 * @brief Calculate the product of values within a given range.
 *
 * This function is executed as a POSIX thread and calculates the product of values within
 * the specified range. It updates the corresponding range struct with the calculated product.
 *
 * @param args A pointer to the range index.
 * @return This function does not return a value.
 */
void* pt_prod(void* args){
    int range_index = *(int*)args;
    long double temp_map;

    ranges[range_index].prod = 1;
    for(int i = ranges[range_index].lower_range; i < ranges[range_index].upper_range; i++){
        temp_map = map_int_to_double(array[i], value_lower_limit, value_upper_limit, 1.0, 1.1);
        if(ranges[range_index].prod > 1){
            ranges[range_index].prod *= 1/temp_map;
        }else{
            ranges[range_index].prod *= temp_map;
        }	
    }
}

/**
 * @brief Calculate the minimum and maximum values within a given range.
 *
 * This function is executed as a POSIX thread and calculates the minimum and maximum
 * values within the specified range. It updates the corresponding range struct with
 * the indices of the minimum and maximum values.
 *
 * @param args A pointer to the range index.
 * @return This function does not return a value.
 */
void* pt_min_max(void* args){
    int range_index = *(int*)args;

    ranges[range_index].min_index = ranges[range_index].lower_range;
    ranges[range_index].max_index = ranges[range_index].lower_range;
    for(int i = ranges[range_index].lower_range + 1; i < ranges[range_index].upper_range; i++){
        //min
        if(array[i] < array[ranges[range_index].min_index]){
            ranges[range_index].min_index = i;
        }
        //max
        if(array[i] > array[ranges[range_index].max_index]){
            ranges[range_index].max_index = i;
        }
    }
}

int main(int argc, char *argv[]) {
    double program_start_time = clock();

    int array_sum, array_min_index, array_max_index;
    long double array_prod;

    check_argument_validity(argc, argv);
	array_length = atoi(argv[1]);
	value_lower_limit = atoi(argv[2]);
	value_upper_limit = atoi(argv[3]);
	number_of_threads = atoi(argv[4]);

    pthread_t threads[number_of_threads];
    int i_args[number_of_threads];
    
    printf("\nArray Length: %d\n", array_length);
    printf("Value Lower Limit: %d\n", value_lower_limit);
    printf("Value Upper Limit: %d\n", value_upper_limit);
    printf("Number of Threads: %d\n\n", number_of_threads);


    start_clock();
    define_ranges();
    stop_clock();
    important_times[0] = get_elapsed_time();
    printf("Time to define ranges: %lf second(s)\n\n", important_times[0]);


    start_clock();
    // Start threads
    for(int i = 0; i < number_of_threads; i++){
        i_args[i] = i;
        pthread_create(&threads[i], NULL, pt_initialize_array,&i_args[i]);
    }
    // Wait for threads
    for (int i = 0; i < number_of_threads; i++){
        pthread_join(threads[i], NULL);
    }
    stop_clock();
    important_times[1] = get_elapsed_time();
    printf("Time to initialize array with %d thread(s): %lf second(s)\n\n", number_of_threads, important_times[1]);


    // S U M
    start_clock();
    // Start threads
    for (int i = 0; i < number_of_threads; i++){
        i_args[i] = i;
        pthread_create(&threads[i], NULL, pt_sum,&i_args[i]);
    }
    // Wait for threads
    for (int i = 0; i < number_of_threads; i++){
        pthread_join(threads[i], NULL);
    }
    // Full array sum
    array_sum = 0;
    for (int i = 0; i< number_of_threads; i++){
        array_sum += ranges[i].sum;
    }
    printf("Array Sum: %d\n", array_sum);
    stop_clock();
    important_times[2] = get_elapsed_time();
    printf("Time to sum array with %d thread(s): %lf second(s)\n\n", number_of_threads, important_times[2]);

    // P R O D
    start_clock();
    // Start threads
    for (int i = 0; i < number_of_threads; i++){
        i_args[i] = i;
        pthread_create(&threads[i], NULL, pt_prod,&i_args[i]);
    }
    // Wait for threads
    for (int i = 0; i < number_of_threads; i++){
        pthread_join(threads[i], NULL);
    }
    // Full array prod
    array_prod = 1;
    for (int i = 0; i< number_of_threads; i++){
        array_prod *= ranges[i].prod;
    }
    printf("Array Prod: %Lf\n", array_prod);
    stop_clock();
    important_times[3] = get_elapsed_time();
    printf("Time to prod array with %d thread(s): %lf second(s)\n\n", number_of_threads, important_times[3]);

    // M I N,  M A X
    start_clock();
    // Start threads
    for (int i = 0; i < number_of_threads; i++){
        i_args[i] = i;
        pthread_create(&threads[i], NULL, pt_min_max,&i_args[i]);
    }
    // Wait for threads
    for (int i = 0; i < number_of_threads; i++){
        pthread_join(threads[i], NULL);
    }
    // Full array min and max
    array_min_index = ranges[0].min_index;
    array_max_index = ranges[0].max_index;
    for(int i = 1; i < number_of_threads; i++){
        //min
        if(array[ranges[i].min_index] < array[array_min_index]){
            array_min_index = ranges[i].min_index;
        }
        //max
        if(array[ranges[i].max_index] > array[array_max_index]){
            array_max_index = ranges[i].max_index;
        }
    }
    stop_clock();
    important_times[4] = get_elapsed_time();
    printf("Array min: array[%d] = %d\n", array_min_index, array[array_min_index]);
    printf("Array max: array[%d] = %d\n", array_max_index, array[array_max_index]);
    printf("Time to find min and max with %d thread(s): %lf second(s)\n\n", number_of_threads, important_times[4]);

    double program_end_time = clock();
    double program_elapsed_time = ((double) (program_end_time - program_start_time)) / CLOCKS_PER_SEC;

    printf("\nProgram time: %lf\n", program_elapsed_time);

    return 0; 
}