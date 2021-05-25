#ifndef KRNL_ASM_H
#define KRNL_ASM_H

#include "types.h"

#define ASM     __asm__ volatile

static inline ui8
asm_inui8(ui16 port)
{
    ui8 t;
    ASM(
        "inb %1, %0"
        : "=a" (t)
        : "dN" (port)
    );
    return t;
}

static inline void
asm_outui8(ui16 port, ui8 data)
{
    ASM(
        "outb %1, %0"
        :
        : "dN" (port), "a" (data)
    );
}

static inline ui16
asm_inui16(ui16 port)
{
    ui16 t;
    ASM(
        "inw %1, %0"
        : "=a" (t)
        : "dN" (port)
    );
    return t;
}

static inline void
asm_outui16(ui16 port, ui16 data)
{
    ASM(
        "outw %1, %0"
        :
        : "dN" (port), "a" (data)
    );
}

#endif
