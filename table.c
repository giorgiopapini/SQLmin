#include <stdlib.h>

#include "table.h"

Table * new_table() {
    Table *new_table = (Table *)malloc(sizeof(Table));
    new_table->num_rows = 0;
    for (int i = 0; i < TABLE_MAX_PAGES; i ++) new_table->pages[i] = NULL;
    return new_table;
}

void free_table(Table * p_table) {
    for (int i = 0; p_table->pages[i]; i ++) free(p_table->pages[i]);
    free(p_table);
}

void * find_row_addr(Table *p_table, uint32_t row_num) {  // return the memory address in which inserting the row
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void *page = p_table->pages[page_num];

    // if a new page is needed (for the next row insertion), allocate memory for a new page
    if (NULL == page) page = p_table->pages[page_num] = malloc(PAGE_SIZE);

    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;
    return page + byte_offset;
}