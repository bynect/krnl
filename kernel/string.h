#ifndef _STRING_H
#define _STRING_H


#include "common.h"


void memset(void *dst, int8_t val, size_t len);


void memcpy(void *dst, void *src, size_t len);


void memmove(void *dst, void *src, size_t len);


size_t strlen(const char *str);


char *itoa(int64_t val, char *str);


char *htoa(uint64_t val, char *str);


char *ftoa(double val, char *str, uint8_t acc);


#endif /*_STRING_H*/
