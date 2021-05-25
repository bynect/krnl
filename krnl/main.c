#include "types.h"
#include "attrs.h"
#include "bootdesc.h"
#include "dri/vga.h"

void NORETURN
main(struct boot_desc *bd)
{
    vga_init();

    vga_print("It just booted up!\r\n", 20);
    vga_print("It indeed worked. Nice!\r\n", 25);

    while (true);
}
