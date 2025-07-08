#include "vga.h"
#include "string.h"
#include "mmap.h"
#include "malloc.h"
#include "idt.h"


void
kernel_main(void)
{
    idt_init();

    init_head_seg(0x100000, 0x100000);

    clear(BLACK << 4 | WHITE);
    cursor_move(0, 0);

    char ver[16];
    char *str = ftoa(1.001f * 100, ver, 3);

    printstr("nectix\t\tversion\t\t", WHITE, BLACK);
    printk(str);

    uint8_t num[11] = {
        'm', 'e', 'm' , ' ', 'r', 'e', 'g', 'i', 'o', 'n', 0x0a
    };

    char buf[12];

    memset(buf, 0, sizeof(buf));
    memcpy(buf, num, sizeof(num));

    printk(buf);

    struct mmap_entry **mms = get_usable_regions();
    for (int i = 0; i < usable_count; ++i) {
        struct mmap_entry *mm = mms[i];
        char buf[128];

        cursor_set(cursor + VGA_WIDTH - (cursor % VGA_WIDTH));
        printstr("addr_base\t", WHITE, BLACK);
        printk(itoa(mm->addr_base, buf));
        //cursor_pos_set(cursor_pos + VGA_WIDTH - (cursor_pos % VGA_WIDTH));

        printstr("addr_len\t", WHITE, BLACK);
        printk(itoa(mm->addr_len, buf));
        //cursor_pos_set(cursor_pos + VGA_WIDTH - (cursor_pos % VGA_WIDTH));

        printstr("type\t", WHITE, BLACK);
        printk(itoa(mm->type, buf));
        //cursor_pos_set(cursor_pos + VGA_WIDTH - (cursor_pos % VGA_WIDTH));

        printstr("attrs\t", WHITE, BLACK);
        printk(htoa(mm->attrs, buf));
        //cursor_pos_set(cursor_pos + VGA_WIDTH - (cursor_pos % VGA_WIDTH));
    }

    while (1);
}
