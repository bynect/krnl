#ifndef LIBK_STRING_H
#define LIBK_STRING_H

#include <krnl/types.h>
#include "mem.h"

ui64 strlen(const ui8 *str);

void strrev(ui8 *str, ui64 len);

#endif
