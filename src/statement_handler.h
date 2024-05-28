#ifndef statement_handler_h
#define statement_handler_h

#include "buffer.h"
#include "row.h"
#include "table.h"

#define INSERT_KEYWORD "insert"
#define SELECT_KEYWORD "select"
#define UPDATE_KEYWORD "update"
#define DELETE_KEYWORD "delete"


typedef enum { 
    PREPARE_SUCCESS, 
    PREPARE_UNRECOGNIZED_STATEMENT,
    PREPARE_SYNTAX_ERROR,
    PREPARE_STRING_TOO_LONG,
    PREPARE_NEGATIVE_ID
} PrepareResult;

typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
} ExecuteResult;

typedef enum { 
    STATEMENT_INSERT, 
    STATEMENT_SELECT 
} StatementType;

typedef struct Statement {
    StatementType type;
    Row row_to_insert;
} Statement;


char * get_statement_format(StatementType);
int buffer_is_statement(Buffer *, char *, int);
PrepareResult prepare_insert(Buffer *, Statement *);
PrepareResult prepare_statement(Buffer *, Statement *);

ExecuteResult execute_insert(Statement *, Table *);
ExecuteResult execute_select(Statement *, Table *);
ExecuteResult execute_statement(Statement *, Table *);

#endif