#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "pager.h"
#include "error_handler.h"


Pager *pager_open(const char *filename) {
    int fd = open(
        filename,
        O_RDWR | O_CREAT,       // O_RDWR = Read/Write mode;            O_CREAT = Create file if it does not exist
        S_IWUSR | S_IRUSR       // S_IWUSR = User write permission;     S_IRUSR = User read permission
    );

    if (-1 == fd) raise(UNABLE_TO_OPEN_FILE_ERROR, 1, filename);

    Pager *pager = (Pager *)malloc(sizeof(Pager));
    pager->file_descriptor = fd;
    pager->file_length = lseek(fd, 0, SEEK_END);

    for (int i = 0; i < TABLE_MAX_PAGES; i ++) pager->pages[i] = NULL;
    
    return pager;
}

void * get_page(Pager *pager, uint32_t page_num) {
    if (page_num > TABLE_MAX_PAGES) raise(PAGE_NUMBER_OUT_OF_BOUNDS_ERROR, 1, page_num, TABLE_MAX_PAGES);

    if (NULL == pager->pages[page_num]) {
        // Cache miss, allocate new memory and load data from file
        void *page = (void *)malloc(PAGE_SIZE);
        uint32_t num_pages = pager->file_length / PAGE_SIZE;

        if (pager->file_length % PAGE_SIZE) num_pages ++;

        if (page_num <= num_pages) {
            lseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);
            size_t bytes_read = read(pager->file_descriptor, page, PAGE_SIZE);
            
            if (-1 == bytes_read) raise(READ_FILE_ERROR, 1, pager->file_descriptor);
        }

        pager->pages[page_num] = page;
    }
    return pager->pages[page_num];
}

void pager_flush(Pager *p_pager, uint32_t page_num, uint32_t size) {
    if (NULL == p_pager->pages[page_num]) raise(FLASHED_NULL_PAGE_ERROR, 1);

    off_t offset = lseek(p_pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);
    if (-1 == offset) raise(SEEKING_ERROR, 1, errno);
    
    size_t written_bytes = write(p_pager->file_descriptor, p_pager->pages[page_num], size);
    if (-1 == written_bytes) raise(WRITE_FILE_ERROR, 1, errno);
}

void free_pager(Pager *p_pager) {
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i ++) {
        void *page = p_pager->pages[i];
        
        if (NULL != page) {
            free(page);
            p_pager->pages[i] = NULL;
        }
    }
    free(p_pager);
}