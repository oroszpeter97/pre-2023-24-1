#include <string.h>

#ifndef LOGGER_H
#define LOGGER_H

typedef enum {
    INFO_LOG,
    WARNING_LOG,
    ERROR_LOG
}LogLevel;

/**
 * @brief new_logger() MUST be called to initialize the logger;
*/
typedef struct {
    char* log_file_name;
    void (*to_file)(LogLevel log_level, const char* log_message);
    void (*to_console)(LogLevel log_level, const char* log_message);
}Logger;

/**
 * @brief Initializes the logger. Call this function only once at the Loggers initialization.
 */
Logger new_logger();

#endif