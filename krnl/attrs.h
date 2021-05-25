#ifndef KRNL_ATTRS_H
#define KRNL_ATTRS_H

#include "types.h"

#define ATTR(attr)  __attribute__((attr))

#define PACKED      ATTR(packed)
#define NORETURN    ATTR(noreturn)
#define FINLINE     ATTR(always_inline)
#define FCOLD       ATTR(cold)
#define FHOT        ATTR(hot)

#define LIKELY(cond)   __builtin_expect((cond), true)
#define UNLIKELY(cond) __builtin_expect((cond), false)

#endif
