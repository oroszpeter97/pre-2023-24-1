#include <stdbool.h>

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
bool is_int(const char *str);

/**
 * @brief Displays how the program work into the console.
*/
void display_help(char *program_name);

/**
 * Validates the command line arguments passed to the program and performs necessary error handling.
 * 
 * @param argc The number of command line arguments.
 * @param argv The array of command line argument strings.
 * @param error A pointer to an Error struct that will be used to report any errors that occur.
 * 
 * @throws INVALID_CL_ARGUMENTS : if the number of command line arguments is not 2 or 5, or if the argument values are invalid.
 * @throws CONVERSION_ERROR : if any of the argument values cannot be converted to integers.
 * 
 * @return void
*/
void check_argument_validity(int argc, char *argv[]);