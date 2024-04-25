#include <stdlib.h>
#include <string.h>

#include "meta_command_handler.h"


int buffer_is_metacommand(Buffer * p_buffer, const char *metacommand) {
    // (buffer->content + 1) means excluding the first char ('.') that identifies a metacommand
    if (0 == strcmp(p_buffer->content + 1, metacommand)) return 1;
    return 0;
}

MetaCommandResult do_meta_command(Buffer *p_buffer) {
    if (buffer_is_metacommand(p_buffer, "exit")) {
        deallocate(p_buffer);
        exit(EXIT_SUCCESS);
    }
    else return META_COMMAND_UNRECOGNIZED_COMMAND;
}