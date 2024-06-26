#include <stdio.h>
#include <stdbool.h>

#include "buffer.h"
#include "error_handler.h"
#include "meta_command_handler.h"
#include "statement_handler.h"


/* development table:
    [column]        [type]
    id              integer
    username        varchar(32)
    email           varchar(255)
*/


void prompt() { printf("db > "); };

int main(int argc, char *argv[]) {
    //if (argc < 2) raise(NO_FILENAME_ERROR, 1);
    //char *filename = argv[1];

    char *filename = "mydb.db";
    Table * table = db_open(filename);
    Buffer * input_buffer = create_buffer();
    
    while (true) {
        prompt();
        populate(input_buffer);
        if (0 == input_buffer->len) continue;  // when only enter key is pressed: skip iteration (go next iteration and run prompt())

        // metacommands handling:
        if (META_COMMAND_START_CHAR == input_buffer->content[0]) {
            switch (do_meta_command(input_buffer, table)) {
                case META_COMMAND_SUCCESS: break;
                case META_COMMAND_UNRECOGNIZED_COMMAND: 
                    raise(UNRECOGNIZED_COMMAND_ERROR, 0, input_buffer->content); 
                    continue;
            }
        }

        // statements handling:
        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case PREPARE_SUCCESS: break;
            case PREPARE_NEGATIVE_ID:
                raise(NEGATIVE_ID_ERROR, 0);
                continue;
            case PREPARE_STRING_TOO_LONG:
                raise(STRING_TOO_LONG_ERROR, 0);
                continue;
            case PREPARE_SYNTAX_ERROR:
                raise(SYNTAX_ERROR, 0, input_buffer->content);
                continue;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                raise(UNRECOGNIZED_STATEMENT_ERROR, 0, input_buffer->content);
                continue;
        }

        // statement execution handling:
        switch (execute_statement(&statement, table)) {
            case EXECUTE_SUCCESS: break;
            case EXECUTE_TABLE_FULL:
                raise(TABLE_FULL_ERROR, 0);
                continue;
        }
    }

    return 0;
}
