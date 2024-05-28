#ifndef buffer_h
#define buffer_h

#include "error_handler.h"


typedef struct Buffer {
    char *content;
    size_t len;
} Buffer;

Buffer * create_buffer();
void populate(Buffer *);
void deallocate(Buffer *);

#endif