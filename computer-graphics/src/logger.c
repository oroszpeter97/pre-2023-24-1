#include "include/logger.h"
#include <time.h>
#include <stdio.h>

static void to_file(LogLevel log_level, const char* log_message);
static void to_console(LogLevel log_level, const char* log_message);
static char* get_log_level_name(LogLevel log_level);

static char log_file_location[128];

Logger new_logger(){
    Logger logger;

    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info=localtime(&t);

    sprintf(log_file_location, "logs/session_%d_%d_%d_%d_%d_%d.log", tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday, tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);

    logger.to_console = to_console;
    logger.to_file = to_file;

    return logger;
}

static void to_file(LogLevel log_level, const char* log_message){
    FILE *file = fopen(log_file_location, "a");

    if (file == NULL) {
        to_console(ERROR_LOG, "Unable to create the file!");
        return;
    }

    if (fprintf(file, get_log_level_name(log_level)) < 0) {
        to_console(ERROR_LOG, "Unable to write to file the log level!");
        fclose(file);
        return;
    }

    if (fprintf(file, ": ") < 0) {
        to_console(ERROR_LOG, "Unable to write to file the seperator!");
        fclose(file);
        return;
    }

    if (fprintf(file, log_message) < 0) {
        to_console(ERROR_LOG, "Unable to write to file the log message!");
        fclose(file);
        return;
    }

    if (fprintf(file, "\n") < 0) {
        to_console(ERROR_LOG, "Unable to write to file the new line!");
        fclose(file);
        return;
    }

    fclose(file);
}

static void to_console(LogLevel log_level, const char* log_message){
    printf("%s: %s\n", get_log_level_name(log_level), log_message);
}

static char* get_log_level_name(LogLevel log_level){
    switch (log_level)
    {
    case INFO_LOG:
        return "INFO";
        break;
    case WARNING_LOG:
        return "WARNING";
        break;
    case ERROR_LOG:
        return "ERROR";
        break;
    default:
        return "";
        break;
    }
}