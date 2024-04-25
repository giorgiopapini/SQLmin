#ifndef error_handler_h
#define error_handler_h


typedef enum {
    UNRECOGNIZED_COMMAND_ERROR,
    UNRECOGNIZED_STATEMENT_ERROR,
    SYNTAX_ERROR,
    TABLE_FULL_ERROR,
    STRING_TOO_LONG_ERROR,
    NEGATIVE_ID_ERROR,
    INPUT_ERROR,
    GENERIC_ERROR,
} ErrorCode;


char * get_error_format(ErrorCode);
void raise(ErrorCode, ...);

#endif