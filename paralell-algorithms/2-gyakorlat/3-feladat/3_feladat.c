#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


/**
 * Generates an 'n' size float array with random numbers in strictly increasing sequence.
 * 
 * @param n : The size of the array
 * 
 * @retval NULL : If the memory allocation failed.
 * @retval float* : If the generation succeded.
*/
float* generate_strictly_increasing_random_float_array(int n) {
    float* arr = (float*)malloc(sizeof(float) * n);

    if(arr == NULL)
        return NULL;

    srand(time(NULL));
    float min = 0.0f;

    for (int i = 0; i < n; i++) {
        if(i > 0)
            min = arr[i-1];
        float random = ((float)rand() / (float)RAND_MAX) + i;
        arr[i] = random;
    }

    return arr;
}

/**
 * Checks if a float arrays elements are in a strictly increasing sequence.
 * 
 * @param arr : Array to be checked.
 * @param n : Length of the array.
 * 
 * @retval 0 : Array is not in strictly increasing sequence.
 * @retval 1 : Array is in strictly increasing sequence.
*/
bool is_strictly_increasing_float_array(float* arr, int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] <= arr[i-1]) {
            return false;
        }
    }
    return true;
}

/**
 * Searches for a value in an ordered float array using binary search with recursion.
 * 
 * @param arr : Array to be searched.
 * @param left : Intervals left side. (Must be smaller or equal than the right)
 * @param right : Intervals right side. (Must be greater or equal than the left)
 * @param x : Value to be searched.
 * 
 * @retval int : The values position in the array if the array contains it.
 * @retval -1 : The value is not contained in the array.
*/
int binary_search_in_float_array_recursive(float arr[], int left, int right, float x) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
 
        // If the element is present at the middle itself
        if (arr[mid] == x)
            return mid;
 
        // If element is smaller than mid, then it can only be present in left subarray
        if (arr[mid] > x)
            return binary_search_in_float_array_recursive(arr, left, mid - 1, x);
 
        // Else the element can only be present in right subarray
        return binary_search_in_float_array_recursive(arr, mid + 1, right, x);
    }
 
    // We reach here when element is not present in array
    return -1;
}

/**
 * Searches for a value in an ordered float array using binary search with iteration.
 * 
 * @param arr : Array to be searched.
 * @param left : Intervals left side. (Must be smaller or equal than the right)
 * @param right : Intervals right side. (Must be greater or equal than the left)
 * @param x : Value to be searched.
 * 
 * @retval int : The values position in the array if the array contains it.
 * @retval -1 : The value is not contained in the array.
*/
int binary_search_in_float_array_iterative(float arr[], int left, int right, float x){
    while(left < right){
        int mid = (left + right) / 2;
        if(arr[mid] == x)
            return mid;
        else if(arr[mid] < x)
            left = mid++;
        else
            right = mid--;
    }

    return -1;
}

/**
 * Generate a float array with random number which are in a strictly increasing sequence.
 * - Write a function to check it.
 * - Write a binary search function recursivly and iterativly.
 * - Measure the time it takes to find each element with both and display the longest element it took.
 * 
 * How to compile:
 * 
 * gcc 3_feladat.c -o 3_feladat.exe
*/
int main(){
    clock_t start_time, end_time;
    double time_elapsed, longest_time_to_find;
    float* arr;
    int longest_time_to_find_n, is_strictly_increasing;

    start_time = clock();
    arr = generate_strictly_increasing_random_float_array(10000);
    end_time = clock();
    time_elapsed = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time it took to generate a 10000 long float array: %lf\n\n", time_elapsed);

    start_time = clock();
    is_strictly_increasing = is_strictly_increasing_float_array(arr, 10000);
    end_time = clock();
    time_elapsed = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time it took to check if the elements are in a strictly increasing sequence: %lf\n\n", time_elapsed);

    printf("-----------------------------------------------\n");
    printf("Checking how long to find every element with iterative binary search...\n");
    longest_time_to_find = 0.0;
    longest_time_to_find_n = 0;
    for (size_t i = 0; i < 9999; i++){
        start_time = clock();
        int temp_element = binary_search_in_float_array_iterative(arr, 0, 9999, arr[i]);
        end_time = clock();
        time_elapsed = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        if(time_elapsed > longest_time_to_find){
            longest_time_to_find = time_elapsed;
            longest_time_to_find_n = i;
        }
        // printf("Time it took to find the %ld. element iteratively: %lf\n", i, time_elapsed);
    }
    printf("The longest element to find was: arr[%d] = %lf\n", longest_time_to_find_n, longest_time_to_find);
    printf("-----------------------------------------------\n");

    printf("-----------------------------------------------\n");
    printf("Checking how long to find every element with recursive binary search...\n");
    longest_time_to_find = 0.0;
    longest_time_to_find_n = 0;
    for (size_t i = 0; i < 9999; i++){
        start_time = clock();
        int temp_element = binary_search_in_float_array_recursive(arr, 0, 9999, arr[i]);
        end_time = clock();
        time_elapsed = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
        if(time_elapsed > longest_time_to_find){
            longest_time_to_find = time_elapsed;
            longest_time_to_find_n = i;
        }
        // printf("Time it took to find the %ld. element recursively: %lf\n", i, time_elapsed);
    }
    printf("The longest element to find was: arr[%d] = %lf\n", longest_time_to_find_n, longest_time_to_find);
    printf("-----------------------------------------------\n");
    

    return 0;
}