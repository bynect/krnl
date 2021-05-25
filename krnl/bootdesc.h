#ifndef KRNL_BOOTDESC_H
#define KRNL_BOOTDESC_H

#include "types.h"

#define UI8(name, _)    ui8 name;
#define SI8(name, _)    ui8 name;
#define UI16(name, _)   ui16 name;
#define SI16(name, _)   si16 name;
#define UI32(name, _)   ui32 name;
#define SI32(name, _)   si32 name;
#define UI64(name, _)   ui64 name;
#define SI64(name, _)   si64 name;
#define FL32(name, _)   fl32 name;
#define FL64(name, _)   fl64 name;

#define BOOTDESC_START  struct boot_desc {
#define BOOTDESC_END    } PACKED;

#include "bootdesc.inc"

#undef BOOTDESC_START
#undef BOOTDESC_END

#undef UI8
#undef SI8
#undef UI16
#undef UI32
#undef SI32
#undef UI64
#undef SI64
#undef FL32
#undef FL64

#endif
