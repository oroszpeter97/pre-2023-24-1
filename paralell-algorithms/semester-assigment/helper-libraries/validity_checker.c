#include <stdbool.h>
#include <ctype.h>
#include "validity_checker.h"
#include "error_library.h"

bool is_int(const char *str, Error* error) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            throw_new_error(NO_ERROR, error);
            return false;
        }
    }

    throw_new_error(NO_ERROR, error);
    return true;
}

bool is_even(int n){
    if(n % 2 == 0){
        return true;
    }

    return false;
}

bool is_valid_range(int lower_limit, int upper_limit){
    if(lower_limit <= upper_limit){
        return true;
    }

    return false;
}

bool is_within_range(int number, int lower_range, int upper_range, Error* error) {
    if (upper_range < lower_range) {
        throw_new_error(INVALID_RANGE, error);
        return false;
    }

    if(lower_range <= number && number <= upper_range){
        throw_new_error(NO_ERROR, error);
        return true;
    }

    throw_new_error(NO_ERROR, error);
    return false;
}