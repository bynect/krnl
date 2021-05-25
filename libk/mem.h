#ifndef LIBK_MEM_H
#define LIBK_MEM_H

#include <krnl/types.h>

void memswap(ui8 *a, ui8 *b, ui64 len);

void *memcpy(ui8 *dst, const ui8 *src, ui64 len);

void *memmove(ui8 *dst, const ui8 *src, ui64 len);

si32 memcmp(const ui8 *a, const ui8 *b, ui64 len);

#endif
