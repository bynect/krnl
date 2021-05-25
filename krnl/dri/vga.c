#include "vga.h"
#include <krnl/asm.h>
#include <libk/mem.h>

#define VGA_COLS    80
#define VGA_ROWS    25
#define VGA_MAX     (VGA_COLS * VGA_ROWS)

static volatile ui8 *vga_mem;
static ui16 vga_port;
static ui16 vga_cur;

void
vga_init(void)
{
    vga_mem = (void *)0xB8000;
    vga_port = 0x03D4;
    vga_move(0);
    vga_clear();
}

void
vga_clear(void)
{
    for (ui16 i = 0; i < VGA_MAX; i++)
    {
        vga_mem[i * 2] = ' ';
        vga_mem[i * 2 + 1] = 0x07;
    }
}

void
vga_print(const ui8 *str, ui64 len)
{
    for (ui64 i = 0; i < len; i++)
    {
        ui8 c = str[i];

        switch (c)
        {
            case '\t':
                vga_cur += 4;
                break;

            case '\n':
                vga_cur = (vga_cur / VGA_COLS + 1) * VGA_COLS;
                break;

            case '\r':
                vga_cur -= vga_cur % VGA_COLS;
                break;

            default:
                if (vga_cur >= VGA_MAX)
                {
                    vga_cur = 0;
                }
                vga_mem[2 * vga_cur++] = c;
                break;
        }
    }

    vga_move_cur(vga_cur);
}

void
vga_move(ui16 cur)
{
    vga_move_cur(cur);
    vga_cur = cur;
}

void
vga_move_cur(ui16 cur)
{
    asm_outui8(vga_port, 0x0F);
    asm_outui8(vga_port + 1, (ui8)(cur & 0xff));
    asm_outui8(vga_port, 0x0E);
    asm_outui8(vga_port + 1, (ui8)((cur >> 8) & 0xff));
}
