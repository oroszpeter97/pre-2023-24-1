#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "error_library.h"

void throw_new_error(Error_T error_type, Error* error){
    error->type = error_type;
    initialize_error_message(error);
}

void initialize_error_message(Error *error){
    switch (error->type){
    case NO_ERROR: strcpy(error->message, "\n"); break;
    case OUT_OF_RANGE: strcpy(error->message, "Error: Number is not within range!\n"); break;
    case INVALID_RANGE: strcpy(error->message, "Error: The given range is not valid!\n"); break;
    case CONVERSION_ERROR: strcpy(error->message, "Error: Unable to convert value!\n"); break;
    case INTEGER_OVERFLOW: strcpy(error->message, "Error: integer overflow occured!\n"); break;
    case INVALID_CL_ARGUMENTS: strcpy(error->message, "Error: The given program arguments are invalid! Use '-help' for more information!\n"); break;
    case TOO_MANY_THREADS: strcpy(error->message, "Error: More threads than the problem can be split into!"); break;
    case INVALID_ARRAY_LENGTH: strcpy(error->message, "Error: The given array length is not valid!"); break;
    case INVALID_INDEX: strcpy(error->message, "Error: Given index is not valid!"); break;
    case CLOCK_IS_ALREADY_RUNNING: strcpy(error->message, "Error: Cannot start clock beacuse it's already running!"); break;
    case CLOCK_IS_NOT_RUNNING: strcpy(error->message, "Error: Cannot stop clock because it's not running!"); break;
    case NO_VALID_TIMEFRAME: strcpy(error->message, "Error: There is no valid timeframe to calculate elapsed time!"); break;
    default: strcpy(error->message, "Error: Undefined error.\n"); break;
    }
}

void print_error(Error* error){
    printf("%s", error->message);
}