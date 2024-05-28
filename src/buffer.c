#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"


Buffer * create_buffer() {
    Buffer * new_buffer = (Buffer *)malloc(sizeof(Buffer));
    new_buffer->content = NULL;
    new_buffer->len = 0;
    return new_buffer;
}

void populate(Buffer * p_buffer) {
    size_t bytes = getline(&p_buffer->content, &p_buffer->len, stdin);
    
    if (bytes <= 0) raise(INPUT_ERROR, 1);
    
    p_buffer->content[bytes - 1] = 0;
    p_buffer->len = bytes - 1;
}

void deallocate(Buffer * p_buffer) {
    free(p_buffer->content);
    free(p_buffer);
}