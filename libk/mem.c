#include "mem.h"

void
memswap(ui8 *a, ui8 *b, ui64 len)
{
    ui8 t;

    while (len--)
    {
        t = *a;
        *a++ = *b;
        *b++ = t;
    }
}

void *
memcpy(ui8 *dst, const ui8 *src, ui64 len)
{
    ui8 *a = dst;
    const ui8 *b = src;

    while (len--)
    {
        *a++ = *b++;
    }
    return dst;
}

void *
memmove(ui8 *dst, const ui8 *src, ui64 len)
{
    ui8 *a = dst;
    const ui8 *b = src;

    if (a < b)
    {
        while (len--)
        {
            *a++ = *b++;
        }
    }
    else
    {
        ui8 *la = a + (len - 1);
        const ui8 *lb = b + (len - 1);
        while (len--)
        {
            *la-- = *lb--;
        }
    }
    return dst;
}

si32
memcmp(const ui8 *a, const ui8 *b, ui64 len)
{
    const ui8 *ap = a;
    const ui8 *bp = b;

    while (len-- > 0)
    {
        if (*ap++ != *bp++)
            return ap[-1] < bp[-1] ? -1 : 1;
    }
    return 0;
}
