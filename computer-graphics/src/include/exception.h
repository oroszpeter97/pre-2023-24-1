#ifndef EXCEPTION_H
#define EXCEPTION_H

/**
 * @brief Enums for exception types.
 * 
 * Represents the various types of exception.
 * Use these to throw exceptions.
*/
typedef enum {
    GENERAL_EXCEPTION = 1,          // General Exception: Catch-all for unexpected errors.
    FILE_NOT_FOUND_EXCEPTION,       // File Not Found Exception: The specified file could not be located.
    IO_EXCEPTION,                   // I/O Exception: General input or output error occurred.
    ARGUMENT_EXCEPTION,             // Argument Exception: An invalid argument was provided.
    NULL_POINTER_EXCEPTION,         // Null Pointer Exception: A null argument was passed when it was not allowed.
    MEMORY_EXCEPTION,               // Memory Exception: Memory allocation or freeing error.
    OUT_OF_RANGE_EXCEPTION,         // Out of Range Exception: An index or value was outside the valid range.
    TIMEOUT_EXCEPTION,              // Timeout Exception: A process exceeded the allocated time to finish.
    PERMISSION_EXCEPTION,           // Permission Denied Exception: Insufficient permissions to access a file.
    WRITE_PERMISSION_EXCEPTION,     // Write Permission Denied Exception: No permission to write to a file.
    INVALID_FILE_PATH_EXCEPTION,    // Invalid File Path Exception: The provided path is not a valid file path.
    CONFIGURATION_EXCEPTION         // Configuration Exception: Configuration file is corrupted or contradictory.
}Exception;

#endif