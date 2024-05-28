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
    UNABLE_TO_OPEN_FILE_ERROR,
    PAGE_NUMBER_OUT_OF_BOUNDS_ERROR,
    READ_FILE_ERROR,
    DB_CLOSE_ERROR,
    FLASHED_NULL_PAGE_ERROR,
    SEEKING_ERROR,
    WRITE_FILE_ERROR,
    NO_FILENAME_ERROR,
    GENERIC_ERROR,
} ErrorCode;


char * get_error_format(ErrorCode err_code);
void raise(ErrorCode err_code, int should_exit, ...);

#endif