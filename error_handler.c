#include <stdio.h>
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
        case GENERIC_ERROR:                     return "Unkown error, please report this issue to mantainers"; break;
        default:                                return "Unkown error, please report this issue to mantainers"; break;
    }
}

void raise(ErrorCode err_code, ...) {
    const char * format = get_error_format(err_code);
    
    va_list args;
    va_start(args, err_code);

    printf("[ERROR] (code: %d) -> ", err_code);
    vprintf(format, args);
    printf(".\n");

    va_end(args);
}