#ifndef DYNAMIC_INT_ARRAY_H_
#define DYNAMIC_INT_ARRAY_H_

#include "error_library.h"

/**
 * @brief A struct that represents an array of integers whose size can be modified during runtime.
*/
typedef struct{
    int* array; /*< Pointer to the array of integers. */
    int length; /*< The current length of the array. */
    unsigned long sum; /*< The sum of all the integers in the array. */
    long double prod; /*< The product of all the integers in the array. Mapped to [1.0, 1.1]*/
    int min_index; /*< The index of the smallest integer in the array. */
    int max_index; /*< The index of the largest integer in the array. */
} Dynamic_Int_Array;

/**
 * @brief A struct that represents a subset of a Dynamic_Int_Array.
*/
typedef struct{
    Dynamic_Int_Array* array; /*< Pointer to the parent Dynamic_Int_Array. */
    int lower_range; /*< The lower bound of the subset within the parent array. */
    int upper_range; /*< The upper bound of the subset within the parent array. */
    unsigned long sum; /*< The sum of all the integers in the subset. */
    long double prod; /*< The product of all the integers in the subset. Mapped to [1.0, 1.1]*/
    int min_index; /*< The index of the smallest integer in the subset. */
    int max_index; /*< The index of the largest integer in the subset. */
} Dynamic_Int_Array_Subset;

/**
 * @brief Initializes a dynamic integer array with a given length.
 * 
 * This function allocates memory for the dynamic integer array with the given length and initializes its length attribute.
 * 
 * @param dynamic_array A pointer to a Dynamic_Int_Array struct representing the dynamic integer array 
 * @param length The length of the dynamic integer array
 * @param error A pointer to an Error struct to store error information if needed
 * 
 * @throws INVALID_ARRAY_LENGTH
 */
void init_dynamic_int_array(Dynamic_Int_Array *dynamic_array, int length, Error* error);

/**
 * @brief Adds an element to the end of a dynamic integer array
 * 
 * This function reallocates memory for the dynamic integer array, adds the new element at the end, and increases its length attribute by 1.
 * 
 * @param dynamic_array A pointer to a Dynamic_Int_Array struct representing the dynamic integer array
 * @param element The integer value to be added to the end of the dynamic integer array
 */
void add_element_to_dynamic_int_array(Dynamic_Int_Array *dynamic_array, int element);

/**
 * @brief Removes an element from a dynamic integer array at a given index
 * 
 * This function removes the element at the given index by moving the following elements one index down, reduces the length attribute by 1, and reallocates memory for the dynamic integer array.
 * 
 * @param dynamic_array A pointer to a Dynamic_Int_Array struct representing the dynamic integer array
 * @param index The index of the element to be removed from the dynamic integer array
 * @param error A pointer to an Error struct to store error information if needed
 * 
 * @throws INVALID_INDEX
 */
void remove_element_from_dynamic_int_array(Dynamic_Int_Array *dynamic_array, int index, Error* error);

/**
 * @brief Inserts an element into a dynamic integer array at a given index
 * 
 * This function inserts the given element into the dynamic integer array at the given index by moving the following elements one index up, adding the new element at the given index, and increasing the length attribute by 1. It also reallocates memory for the dynamic integer array.
 * @param dynamic_array A pointer to a Dynamic_Int_Array struct representing the dynamic integer array
 * @param index The index at which the new element will be inserted into the dynamic integer array
 * @param element The integer value to be added to the dynamic integer array
 * @param error A pointer to an Error struct to store error information if needed
 * 
 * @throws INVALID_INDEX
 */
void insert_element_into_dynamic_int_array(Dynamic_Int_Array *dynamic_array, int index, int element, Error* error);

#endif // DYNAMIC_INT_ARRAY_H_