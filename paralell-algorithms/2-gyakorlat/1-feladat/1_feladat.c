#include <stdlib.h>
#include <stdio.h>
#include "../../helper-libraries/userio.h"

#define ARRAY_SIZE 10

/**
 * Returns the sum of an int array. (sequential)
 * 
 * @param arr : The array of numbers.
 * @param arr_size : The length of the array.
 * 
 * @retval 0 : The size of the array is less than 1.
 * @retval int : The sum of the array if no errors.
*/
int sum_int_array_seq(int arr[], int arr_size){
    if(arr_size < 1)
        return 0;

    int sum = 0;
    
    for (size_t i = 0; i < arr_size; i++){
        sum += arr[i];
    }
    
    return sum;
}

/**
 * Returns the sum of an int array. (recursive)
 * 
 * @param arr : The array of numbers.
 * @param arr_size : The length of the array.
 * 
 * @retval 0 : The size of the array is less than 1.
 * @retval int : The sum of the array if no errors.
*/
int sum_int_array_rec(int arr[], int arr_size){
    if(arr_size < 1)
        return 0;
    
    return (sum_int_array_rec(arr, arr_size - 1) + arr[arr_size - 1]);
}

/**
 * Returns the minimum value in an array. (sequential)
 * 
 * @param arr : The array of numbers.
 * @param arr_size : The length of the array.
 * 
 * @retval 0 : The size of the array is less than 1.
 * @retval int : The minimum value of the array if no errors.
*/
int min_int_array_seq(int arr[], int arr_size){
    int min;
    
    if(arr_size < 1)
        return 0;

    min = arr[0];

    for (size_t i = 1; i < arr_size; i++){
        if(arr[i] < min)
            min = arr[i];
    }
    
    return min;
}

/**
 * Returns the minimum value in an array. (recursive)
 * 
 * @param arr : The array of numbers.
 * @param arr_size : The length of the array.
 * 
 * @retval 0 : The size of the array is less than 1.
 * @retval int : The minimum value of the array if no errors.
*/
int min_int_array_rec(int arr[], int arr_size){
    // TO-DO
    return -1;
}

/**
 * Returns the maximum value in an array. (sequential)
 * 
 * @param arr : The array of numbers.
 * @param arr_size : The length of the array.
 * 
 * @retval 0 : The size of the array is less than 1.
 * @retval int : The maximum value of the array if no errors.
*/
int max_int_array_seq(int arr[], int arr_size){
    int max;
    
    if(arr_size < 1)
        return 0;

    max = arr[0];

    for (size_t i = 1; i < arr_size; i++){
        if(arr[i] > max)
            max = arr[i];
    }
    
    return max;
}

/**
 * Returns the maximum value in an array. (recursive)
 * 
 * @param arr : The array of numbers.
 * @param arr_size : The length of the array.
 * 
 * @retval 0 : The size of the array is less than 1.
 * @retval int : The maximum value of the array if no errors.
*/
int max_int_array_rec(int arr[], int arr_size){
    // TO-DO
    return -1;
}

/**
 * Write a program where you can input integers into an array.
 * - Write a function for sum of these integers.
 * - Write a funciion for 'min' and 'max'.
 * - Write a function for 'min' and 'max' using recursion.
 * - Measure and collect the time it takes for the iterative and recursive functions. Make a graph of the collected data. (Can be found with the name '1-feladat.xlsx').
 * 
 * How to compile:
 * 
 * gcc .\1_feladat.c ..\..\helper-libraries\userio.c -o 1_feladat.exe
*/
int main(){
    int *num_array = (int*) malloc (sizeof(int) * ARRAY_SIZE);
    int user_number, error;

    // read user input
    for (size_t i = 0; i < ARRAY_SIZE; i++){
        error = 1;
        while (error){
            error = 0;

            printf("\nPlease enter a positive number:\n>");
            user_number = read_positive_int_user_input();

            switch (user_number){
            case -1:
                printf("Read Error.");
                error = 1;
                break;
            case -2:
                printf("Buffer overflow.");
                error = 1;
                break;
            case -3:
                printf("Not a valid integer type.");
                error = 1;
                break;
            case -4:
                printf("Negative number.");
                error = 1;
                break;
            default:
                num_array[i] = user_number;
                break;
            }
        }
    }

    printf("Sum (sequential): %d\n\n", sum_int_array_seq(num_array, ARRAY_SIZE));
    printf("Sum (recursive): %d\n\n", sum_int_array_rec(num_array, ARRAY_SIZE));
    printf("The minimum value (sequential): %d\n\n", min_int_array_seq(num_array, ARRAY_SIZE));
    printf("The minimum value (recursive): %d\n\n", min_int_array_seq(num_array, ARRAY_SIZE));
    printf("The maximum value (sequantial): %d\n\n", max_int_array_seq(num_array, ARRAY_SIZE));
    printf("The maximum value (recursive): %d\n\n", max_int_array_seq(num_array, ARRAY_SIZE));
    
    free(num_array);
    return 0;
}