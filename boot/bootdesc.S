#define UI8(name, value)	name: .byte value
#define SI8(name, value)	name: .byte value
#define UI16(name, value)	name: .word value
#define SI16(name, value)	name: .word value
#define UI32(name, value)	name: .long value
#define SI32(name, value)	name: .long value
#define UI64(name, value)	name: .quad value
#define SI64(name, value)	name: .quad value
#define FL32(name, value)	name: .float value
#define FL64(name, value)	name: .double value

#define BOOTDESC_START	bootdesc:
#define BOOTDESC_END
#define BOOTDESC_MAGIC	0xDEADBEEF
#define BOOTDESC_VIDEO_MODE	0x00

#include <krnl/bootdesc.inc>

#undef BOOTDESC_START
#undef BOOTDESC_END
#undef BOOTDESC_MAGIC
#undef BOOTDESC_VIDEO_MODE

#undef UI8
#undef SI8
#undef UI16
#undef UI32
#undef SI32
#undef UI64
#undef SI64
#undef FL32
#undef FL64
