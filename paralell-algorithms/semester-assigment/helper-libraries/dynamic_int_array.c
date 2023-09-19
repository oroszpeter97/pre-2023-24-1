#include <stdio.h>
#include <stdlib.h>
#include "dynamic_int_array.h"
#include "error_library.h"

void init_dynamic_int_array(Dynamic_Int_Array *dynamic_array, int length, Error* error) {
    if(length < 0){
        throw_new_error(INVALID_ARRAY_LENGTH, error);
        return;
    }

    dynamic_array->array = (int*) malloc(length * sizeof(int));
    dynamic_array->length = length;

    throw_new_error(NO_ERROR, error);
    return;
}

void add_element_to_dynamic_int_array(Dynamic_Int_Array *dynamic_array, int element) {
    // Reallocate the size of the dynamic array, add the new element then increase the size attribute of the dynamic array.
    dynamic_array->array = (int*) realloc(dynamic_array->array, (dynamic_array->length + 1) * sizeof(int));
    dynamic_array->array[dynamic_array->length] = element;
    dynamic_array->length++;
}

void remove_element_from_dynamic_int_array(Dynamic_Int_Array *dynamic_array, int index, Error* error) {
    // valid index check
    if(index < 0 || index > dynamic_array->length -1){
        throw_new_error(INVALID_INDEX, error);
        return;
    }

    // From the index that needs to be removed, move the next elements down by one, reduce the dynamic arrays size attribute, then reallocate the dynamic arrays size.
    for (int i = index; i < dynamic_array->length - 1; i++) {
        dynamic_array->array[i] = dynamic_array->array[i + 1];
    }
    dynamic_array->length--;
    dynamic_array->array = (int*) realloc(dynamic_array->array, dynamic_array->length * sizeof(int));

    throw_new_error(NO_ERROR, error);
    return;
}

void insert_element_into_dynamic_int_array(Dynamic_Int_Array *dynamic_array, int index, int element, Error* error) {
    // valid index check
    if(index < 0 || index > dynamic_array->length){
        throw_new_error(INVALID_INDEX, error);
        return;
    }

    // Increase the size of the dynamic array, move the elements from the index up by one, add the new element at the index.
    dynamic_array->array = (int*) realloc(dynamic_array->array, (dynamic_array->length + 1) * sizeof(int));
    for (int i = dynamic_array->length - 1; i >= index; i--) {
        dynamic_array->array[i + 1] = dynamic_array->array[i];
    }
    dynamic_array->array[index] = element;
    dynamic_array->length++;

    throw_new_error(NO_ERROR, error);
    return;
}