#ifndef meta_command_handler_h
#define meta_command_handler_h

#include "buffer.h"

#define META_COMMAND_START_CHAR '.'


typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;


int buffer_is_metacommand(Buffer *, const char *);
MetaCommandResult do_meta_command(Buffer *);

#endif