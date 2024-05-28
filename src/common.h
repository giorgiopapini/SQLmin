#ifndef common_h
#define common_h

#include <stdbool.h>   // boolean types
#include <stddef.h>    // NULL, size_t (result of sizeof operator), ptrdiff_t (signed integral type of result of pointers subtraction), wchar_t
#include <stdint.h>    // Numbers with different sizes, eg: int8_t, int16_t, uint8_t, ecc... 

#define TABLE_MAX_PAGES 100
#define PAGE_SIZE 4096  // 4 kilobytes same size of a page used in the virtual memory system of most architectures (OS will move pages in and out memory as whole units)

#endif