#include "panic.h"
#include "asm.h"
#include "dri/vga.h"
#include "attrs.h"

FCOLD void
krnl_panic(const ui8 *str, ui64 len)
{
    vga_clear();
    vga_move(0);
    vga_print("[ PANIC ] ", 10);
    vga_print(str, len);

    asm(
        "cli\n"
        "hlt\n"
    );
}
