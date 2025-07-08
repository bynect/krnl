#include "pic.h"
#include "vga.h"


void
keyboard_handler(uint8_t scan, uint8_t chr)
{
    static const char shift_table[] = {
        [','] = '<',
        ['.'] = '>',
        ['/'] = '?',
        ['\''] = '"',
        ['['] = '{',
        [']'] = '}',
        ['\\'] = '|',
        ['1'] = '!',
        ['2'] = '@',
        ['3'] = '#',
        ['4'] = '$',
        ['5'] = '%',
        ['6'] = '^',
        ['7'] = '&',
        ['8'] = '*',
        ['9'] = '(',
        ['0'] = ')',
        ['='] = '+',
        ['-'] = '_'
    };

    static bool lshift = false;
    static bool rshift = false;
    static uint8_t last;

    if (last != 0xe0) {
        if (chr) {
            if (lshift | rshift && shift_table[chr]) {
                printchr(shift_table[chr], WHITE, BLACK);
            } else if (cursor + 1 <= VGA_MAX)
                printchr(chr, WHITE, BLACK);
        } else {
            switch (scan) {
                case 0x8e:
                    if (cursor - 1 >= VGA_MIN) {
                        cursor_set(cursor - 1);
                        printchr(' ', WHITE, BLACK);
                        cursor_set(cursor - 1);
                    }
                    break;

                case 0x2a:
                    lshift = true;
                    break;

                case 0xaa:
                    lshift = false;
                    break;

                case 0x36:
                    rshift = true;
                    break;

                case 0xb6:
                    rshift = false;
                    break;

                case 0x9c:
                    if (cursor + VGA_WIDTH < VGA_MAX)
                        cursor_set(cursor + VGA_WIDTH - cursor % VGA_WIDTH);
                    break;
            }
        }
    } else {
        switch (scan) {
            case 0x50:
                if (cursor + VGA_WIDTH < VGA_MAX)
                    cursor_set(cursor + VGA_WIDTH);
                break;

            case 0x48:
                if (cursor - VGA_WIDTH >= VGA_MIN)
                    cursor_set(cursor - VGA_WIDTH);
                break;

            case 0x4b:
                if (cursor - 1 >= VGA_MIN)
                    cursor_set(cursor - 1);
                break;

            case 0x4d:
                if (cursor + 1 < VGA_MAX)
                    cursor_set(cursor + 1);
                break;

            default:
                break;
        }
    }

    last = scan;
}


void
isr1_handler(void)
{
    static const char table[] = {
        0, 0, '1', '2', '3', '4', '5', '6',
        '7', '8', '9', '0', '-', '=', 0, 0,
        'q', 'w', 'e', 'r', 't', 'y', 'u',
        'i', 'o', 'p', '[', ']', 0, 0, 'a',
        's', 'd', 'f', 'g', 'h', 'j', 'k',
        'l', ';', '\'', '`', 0, '\\', 'z',
        'x', 'c', 'v', 'b', 'n', 'm', ',',
        '.', '/', 0, '*', 0, ' '
    };

    uint8_t scan = inb(0x60);
    uint8_t chr = 0;

    if (scan < 0x3a)
        chr = table[scan];

    keyboard_handler(scan, chr);

    PIC_SEND_EOI(1);
}
