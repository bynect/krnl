#include "vga.h"
#include "io.h"


#define VGA_MEMORY          (volatile uint8_t *)0xb8000


uint16_t cursor = 0;


void
cursor_set(uint16_t pos)
{
    outb(0x03d4, 0x0f);
    outb(0x03d5, (uint8_t)(pos & 0xff));
    outb(0x03d4, 0x0e);
    outb(0x03d5, (uint8_t)((pos >> 8) & 0xff));

    cursor = pos;
}


void
cursor_move(uint8_t x, uint8_t y)
{
    cursor_set(y * VGA_WIDTH + x);
}


void
clear(uint64_t col)
{
    uint64_t value = 0;
    value += col << 8;
    value += col << 24;
    value += col << 40;
    value += col << 56;

    uint64_t *i = (uint64_t *)VGA_MEMORY;
    do {
        *i = value;
    } while (++i < (uint64_t *)(VGA_MEMORY + 4000));
}


void
printstr(const char *str, uint8_t fore, uint8_t back)
{
    uint16_t index = cursor;

    while (*str) {
        switch (*str) {
            case 9:
                index += 4;
                break;

            case 11:
                index += VGA_WIDTH;
                index -= index % VGA_WIDTH;
                index += 4;
                break;

            case 10:
                index += VGA_WIDTH;
                /*fall through*/
            case 13:
                index -= index % VGA_WIDTH;
                break;

            default:
                *(VGA_MEMORY + index * 2) = *str;
                *(VGA_MEMORY + index * 2 + 1) = back << 4 | fore;
                ++index;
                break;
        }
        ++str;
    }
    cursor_set(index);
}


void
printchr(const char chr, uint8_t fore, uint8_t back)
{
    uint16_t index = cursor;

    switch (chr) {
        case 9:
            index += 4;
            break;

        case 11:
            index += VGA_WIDTH;
            index -= index % VGA_WIDTH;
            index += 4;
            break;

        case 10:
            index += VGA_WIDTH;
            /*fall through*/
        case 13:
            index -= index % VGA_WIDTH;
            break;

        default:
            *(VGA_MEMORY + cursor * 2) = chr;
            *(VGA_MEMORY + cursor * 2 + 1) = back << 4 | fore;

            ++index;
    }

    cursor_set(index);
}


void
printk(const char *str)
{
    printstr(str, WHITE, BLACK);
    printchr('\n', WHITE, BLACK);
}
