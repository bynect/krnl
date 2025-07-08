#ifndef _MALLOC_H
#define _MALLOC_H


#include "common.h"


void *malloc(size_t size);


void *calloc(size_t size);


void *aligned_malloc(size_t size, uint32_t align);


void *realloc(void *ptr, size_t size);


void free(void *ptr);


#endif /*_MALLOC_H*/
