#ifndef KRNL_ATTRS_H
#define KRNL_ATTRS_H

#define ATTR(attr)  __attribute__((attr))

#define PACKED      ATTR(packed)
#define NORETURN    ATTR(noreturn)
#define FINLINE     ATTR(always_inline)

#endif
