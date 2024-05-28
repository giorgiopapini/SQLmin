#ifndef pager_h
#define pager_h

#include "common.h"

typedef struct Pager {
    int file_descriptor;
    uint32_t file_length;
    void *pages[TABLE_MAX_PAGES];
} Pager;

Pager * pager_open(const char *filename);
void * get_page(Pager *, uint32_t page_num);
void pager_flush(Pager *, uint32_t page_num, uint32_t size);
void free_pager(Pager *);

#endif