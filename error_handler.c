#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "error_handler.h"


char * get_error_format(ErrorCode err_code) {
    switch (err_code) {
        case UNRECOGNIZED_COMMAND_ERROR:        return "Unrecognized command '%s'"; break;
        case UNRECOGNIZED_STATEMENT_ERROR:      return "Unrecognized statement '%s'"; break;
        case SYNTAX_ERROR:                      return "Syntax error. Could not parse '%s' correctly";
        case TABLE_FULL_ERROR:                  return "No space left on the table"; break;
        case STRING_TOO_LONG_ERROR:             return "String is too long"; break;
        case NEGATIVE_ID_ERROR:                 return "ID must be positive"; break;
        case INPUT_ERROR:                       return "An error occoured while reading input bytes"; break;
        case UNABLE_TO_OPEN_FILE_ERROR:         return "Unable to open file (path: '%s')"; break;
        case PAGE_NUMBER_OUT_OF_BOUNDS_ERROR:   return "Tried to fetch a page out of bounds (%d > %d)"; break;
        case READ_FILE_ERROR:                   return "An error occured while reading file (file descriptor: '%d')"; break;
        case DB_CLOSE_ERROR:                    return "An error occured while closing database file"; break;
        case FLASHED_NULL_PAGE_ERROR:           return "Tried to flush NULL page"; break;
        case SEEKING_ERROR:                     return "Error seeking (errno: %d)"; break;
        case WRITE_FILE_ERROR:                  return "An error occured while writing file (errno: %d)"; break;
        case NO_FILENAME_ERROR:                 return "Must supply a database filename"; break;
        case GENERIC_ERROR:                     return "Unkown error, please report this issue to mantainers"; break;
        default:                                return "Unkown error, please report this issue to mantainers"; break;
    }
}

void raise(ErrorCode err_code, int should_exit, ...) {
    const char * format = get_error_format(err_code);
    
    va_list args;
    va_start(args, should_exit);

    printf("[ERROR] (code: %d) -> ", err_code);
    vprintf(format, args);
    printf(".\n");

    va_end(args);

    if (should_exit) exit(EXIT_FAILURE);
}