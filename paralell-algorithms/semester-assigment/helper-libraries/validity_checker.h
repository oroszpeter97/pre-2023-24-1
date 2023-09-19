#ifndef VALIDITY_CHECKER_H_
#define VALIDITY_CHECKER_H_

#include <stdbool.h>
#include "error_library.h"

/**
 * @brief Check if a string can be converted to an integer.
 *
 * This function checks if the given string can be converted to an integer using
 * the `strtol` function. If the string can be converted to an integer and the
 * integer value is within the range of `int` values, this function returns
 * true. Otherwise, it returns false.
 *
 * @param str The string to check.
 * @return true if the string can be converted to an integer, false otherwise.
 */
bool is_int(const char *str, Error* error);

/**
 * @brief Checks if provided int is even number.
 * 
 * @return true if even and false if not even.
 */
bool is_even(int n);

/**
 * @brief Checks if a range defined by lower_limit and upper_limit is valid.
 *
 * This function determines whether the range defined by the lower_limit and upper_limit
 * parameters is valid. A range is considered valid if the lower_limit is less than or
 * equal to the upper_limit.
 *
 * @param lower_limit The lower limit of the range.
 * @param upper_limit The upper limit of the range.
 *
 * @return Returns true if the range is valid (lower_limit <= upper_limit), otherwise false.
 */
bool is_valid_range(int lower_limit, int upper_limit);

/**
 * @brief Checks if a given number is within a specified range.
 *
 * This function determines whether the provided number falls within the inclusive range
 * defined by the lower_range and upper_range parameters. If the upper_range is less than
 * the lower_range, an error is thrown indicating an invalid range.
 *
 * @param number The number to be checked.
 * @param lower_range The lower bound of the range.
 * @param upper_range The upper bound of the range.
 * @param error A pointer to an Error structure where error information can be stored.
 *
 * @return Returns true if the number is within the specified range, otherwise false.
 *
 * @throws INVALID_RANGE
 * 
 * @remarks If the upper_range is less than the lower_range, the function will always
 * throw an error, regardless of the value of the number parameter.
 */
bool is_within_range(int number, int lower_range, int upper_range, Error* error);

#endif // VALIDITY_CHECKER_H_
