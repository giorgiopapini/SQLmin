#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "table.h"
#include "error_handler.h"


Table * db_open(const char *filename) {
    Pager *new_pager = pager_open(filename);
    Table *new_table = (Table *)malloc(sizeof(Table));
    
    new_table->pager = new_pager;
    new_table->num_rows = new_pager->file_length / ROW_SIZE;

    return new_table;
}

void db_close(Table *p_table) {
    Pager *pager = p_table->pager;
    uint32_t num_full_pages = p_table->num_rows / ROWS_PER_PAGE;

    for (uint32_t i = 0; i <= num_full_pages; i ++) {
        if (NULL == pager->pages[i]) continue;
        
        pager_flush(pager, i, PAGE_SIZE);
        free(pager->pages[i]);
        pager->pages[i] = NULL;
    }

    int result = close(pager->file_descriptor);
    
    if (-1 == result) raise(DB_CLOSE_ERROR, 1);

    free_pager(pager);
    free(p_table);
}

void * find_row_addr(Table *p_table, uint32_t row_num) {  // return the memory address in which inserting the row
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void *page = get_page(p_table->pager, page_num);

    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;
    return page + byte_offset;
}