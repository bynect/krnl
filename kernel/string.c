#include "string.h"


void
memset(void *dst, int8_t val, size_t len)
{
    char *ptr = dst;
    char *end = ptr + len;

    for (;;) {
        if (ptr >= end) break;
        *ptr++ = (uint8_t)val;

        if (ptr >= end) break;
        *ptr++ = (uint8_t)val;

        if (ptr >= end) break;
        *ptr++ = (uint8_t)val;

        if (ptr >= end) break;
        *ptr++ = (uint8_t)val;
    }
}


void
memcpy(void *dst, void *src, size_t len)
{
    char *d = dst;
    char *s = src;
    while (len--) *d++ = *s++;
}


void
memmove(void *dst, void *src, size_t len)
{
    uint8_t *d = dst;
    const uint8_t *s = src;

    if (d < s)
        while (len--) *d++ = *s++;
    else {
        const uint8_t *lasts = s + (len - 1);
        uint8_t *lastd = d + (len - 1);
        while (len--) *lastd-- = *lasts--;
    }
}


size_t
strlen(const char *str)
{
    register const char *tail;
    for (tail = str; *tail; ++tail);

    return (tail - str);
}


char *
itoa(int64_t val, char *str)
{
    static char ascii[] = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz";
    char *tail = str, *head = str;
    register int64_t test;

    do {
        test = val;
        val /= 10;
        *tail++ = ascii[(test - val * 10) + 35];
    } while (val);

    if (test < 0) *tail++ = '-';
    *tail-- = '\0';

    char tmp;
    while (head < tail) {
        tmp     = *tail;
        *tail--  = *head;
        *head++ = tmp;
    }

    return str;
}


char *
htoa(uint64_t val, char *str)
{
    static char hex[] = "0123456789abcdef";
    char *tail = str;

    uint8_t *input = (uint8_t *)&val;
    for (int i = 0; i < 8; ++i) {
        tail[(i * 2)] = hex[input[7 - i] >> 4];
        tail[(i * 2) + 1] = hex[input[7 - i] & 0x0f];
    }

    tail[16] = '\0';
    return str;
}


char *
ftoa(double val, char *str, uint8_t acc)
{
    acc = acc < 20 ? acc : 19;

    char *ptr = itoa((int64_t)val, str);
    char *tail = str;

    val = val < 0 ? -val : val;
    while (*ptr) *tail++ = *ptr++;

    *tail++ = '.';
    double dec = val - (uint32_t)val;

    for (uint8_t i = 0; i < acc; ++i) {
        dec *= 10;
        *tail++ = '0' + (uint32_t)dec;
        dec -= (uint32_t)dec;
    }

    *tail = '\0';
    return str;
}
