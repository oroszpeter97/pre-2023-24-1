#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

int init_dynamic_array(DynamicArray *dynamic_array, int size) {
    if(size < 0)
        return 1;

    dynamic_array->arr = (int*) malloc(size * sizeof(int));
    dynamic_array->size = size;

    return 0;
}

void add_element_to_dynamic_array(DynamicArray *dynamic_array, int element) {
    // Reallocate the size of the dynamic array, add the new element then increase the size attribute of the dynamic array.
    dynamic_array->arr = (int*) realloc(dynamic_array->arr, (dynamic_array->size + 1) * sizeof(int));
    dynamic_array->arr[dynamic_array->size] = element;
    dynamic_array->size++;
}

int remove_element_from_dynamic_array(DynamicArray *dynamic_array, int index) {
    // valid index check
    if(index < 0 || index > dynamic_array->size -1)
        return 1;

    // From the index that needs to be removed, move the next elements down by one, reduce the dynamic arrays size attribute, then reallocate the dynamic arrays size.
    for (int i = index; i < dynamic_array->size - 1; i++) {
        dynamic_array->arr[i] = dynamic_array->arr[i + 1];
    }
    dynamic_array->size--;
    dynamic_array->arr = (int*) realloc(dynamic_array->arr, dynamic_array->size * sizeof(int));

    return 0;
}
