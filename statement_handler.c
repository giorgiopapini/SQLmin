#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "statement_handler.h"


char * get_statement_format(StatementType stm_type) {  // this function should manage variable amount of args and types of input
    switch (stm_type) {
        case STATEMENT_INSERT:              return "insert %s %d %d"; break;  // find a way to concatenate string (INSERT_KEYWORD + "%d %d...")
        case STATEMENT_SELECT:              return "select %s %d %d"; break;
    }
}

int buffer_is_statement(Buffer *p_buffer, char *statement, int len) {
    if (0 == strncmp(p_buffer->content, statement, len)) return 1;
    return 0;
}

PrepareResult prepare_insert(Buffer *p_buffer, Statement *p_statement) {
    p_statement->type = STATEMENT_INSERT;
    
    // Using a copy of the buffer content ensure that strtok() does not modify the original buffer content, which may be
    // valuable for future use inside the session (like error handling and formatting)
    size_t content_len = strlen(p_buffer->content) + 1;  // including null terminator
    char buff_content_copy[content_len];
    memcpy(buff_content_copy, p_buffer->content, content_len);

    char *keyword = strtok(buff_content_copy, " ");
    char *id_str = strtok(NULL, " ");
    char *username = strtok(NULL, " ");
    char *email = strtok(NULL, " ");

    if (id_str == NULL || username == NULL || email == NULL) return PREPARE_SYNTAX_ERROR;

    int id = atoi(id_str);
    if (id < 0) return PREPARE_NEGATIVE_ID;
    if (strlen(username) > COLUMN_USERNAME_SIZE) return PREPARE_STRING_TOO_LONG;
    if (strlen(email) > COLUMN_EMAIL_SIZE) return PREPARE_STRING_TOO_LONG;

    p_statement->row_to_insert.id = id;
    strcpy(p_statement->row_to_insert.username, username);
    strcpy(p_statement->row_to_insert.email, email);

    return PREPARE_SUCCESS;
}

PrepareResult prepare_statement(Buffer *p_buffer, Statement *p_statement) {
    if (buffer_is_statement(p_buffer, INSERT_KEYWORD, 6)) {   // find a way to NOT insert the length of the keyword
        return prepare_insert(p_buffer, p_statement);
    }

    if (buffer_is_statement(p_buffer, SELECT_KEYWORD, 6)) {
        p_statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

ExecuteResult execute_insert(Statement *p_statement, Table *p_table) {
    if (p_table->num_rows >= TABLE_MAX_ROWS) return EXECUTE_TABLE_FULL;
    Row *new_row = &(p_statement->row_to_insert);
    
    serialize_row(new_row, find_row_addr(p_table, p_table->num_rows));
    p_table->num_rows ++;

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement *p_statement, Table *p_table) {
    Row row;

    for (uint32_t i = 0; i < p_table->num_rows; i ++) {
        deserialize_row(find_row_addr(p_table, i), &row);
        printf("\nid: [%d], username: [%s], email: [%s]\n", row.id, row.username, row.email);
    }

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement *p_statement, Table *p_table) {
    switch (p_statement->type) {
        case STATEMENT_INSERT:          execute_insert(p_statement, p_table); break;
        case STATEMENT_SELECT:          execute_select(p_statement, p_table); break;
    }
}