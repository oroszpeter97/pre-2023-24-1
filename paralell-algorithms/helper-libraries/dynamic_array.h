#ifndef DYNAMIC_ARRAY_H_ 
#define DYNAMIC_ARRAY_H_

typedef struct {
    int *arr;
    int size;
} DynamicArray;

/**
 * Initializes the dynamic array.
 * 
 * @param dynamic_array : pointer to the dynamic array.
 * @param size : initial size of the dynamic array.
 * 
 * @retval 0 : No errors.
 * @retval 1 : Size is not valid. (Smaller than 0)
*/
int init_dynamic_array(DynamicArray *dynamic_array, int size);

/**
 * Adds a new element to the dynamic array.
 * 
 * @param dynamic_array : pointer to the dynamic array.
 * @param element : int element to be added.
*/
void add_element_to_dynamic_array(DynamicArray *dynamic_array, int element);

/**
 * Removes an element from the dynamic array.
 * 
 * @param dynamic_array : pointer to the dynamic array.
 * @param element : index of the element to be removed.
 * 
 * @retval 0 : No errors.
 * @retval 1 : Invalid index.
*/
int remove_element_from_dynamic_array(DynamicArray *dynamic_array, int index);

#endif //DYNAMIC_ARRAY_H_