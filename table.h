#ifndef table_h
#define table_h

#include "common.h"
#include "row.h"

#define TABLE_MAX_PAGES 100

/*
    - Store rows in blocks of memory called pages
    - Each page stores as many rows as it can fit
    - Rows are serialized into a compact representation with each page
    - Pages are only allocated as needed
    - Keep a fixed-size array of pointers to pages

*/

static const uint32_t PAGE_SIZE = 4096;  // 4 kilobytes same size of a page used in the virtual memory system of most architectures (OS will move pages in and out memory as whole units)
static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

typedef struct Table {
    uint32_t num_rows;
    void *pages[TABLE_MAX_PAGES];
} Table;

Table * new_table();
void free_table(Table *);
void * find_row_addr(Table *, uint32_t);

#endif