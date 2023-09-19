/**
 * @file error_library.h
 * @brief Library for handling error codes.
 *
 * This library provides a set of error codes and functions for handling them.
 */

#ifndef ERROR_LIBRARY_H_
#define ERROR_LIBRARY_H_


/**
 * @enum Error_T
 *
 * @brief An enumeration for different error types.
 */
typedef enum {
    NO_ERROR = 0,   /**< No error occurred */
    OUT_OF_RANGE,  /**< Array index out of bounds */
    INVALID_RANGE, /**< The given range is not valid*/
    CONVERSION_ERROR, /**< Unable to convert value*/
    INTEGER_OVERFLOW, /**< Integer overflow occured*/
    INVALID_CL_ARGUMENTS, /**< The given program arguments are invalid! Use '-help' for more information!*/
    TOO_MANY_THREADS, /**< More threads than the problem can be split into!*/
    INVALID_ARRAY_LENGTH, /**< The given array length is not valid!*/
    INVALID_INDEX, /**< Given index is not valid!*/
    CLOCK_IS_ALREADY_RUNNING, /**< Cannot start clock beacuse it's already running!*/
    CLOCK_IS_NOT_RUNNING, /**< Cannot stop clock because it's not running!*/
    NO_VALID_TIMEFRAME /**< There is no valid timeframe to calculate elapsed time!*/
} Error_T;

/**
 * @struct Error
 *
 * @brief A structure to hold information about an error.
 */
typedef struct{
    Error_T type;
    char message[256];
} Error;

/**
 * @brief Throws a new error and sets the message for the error.
 *
 * @param error_type The type of the error to throw.
 * @param error A pointer to the Error struct to update.
 */
void throw_new_error(Error_T error_code, Error* error_pointer);

/**
 * @brief Initializes the error message based on the error type.
 *
 * @param error A pointer to the Error struct to update.
 */
void initialize_error_message(Error *error);

/**
 * @brief Prints the error message to stdout.
 *
 * @param error A pointer to the Error struct to print.
 */
void print_error(Error* error);

#endif /* ERROR_LIBRARY_H_ */