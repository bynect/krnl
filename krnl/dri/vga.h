#ifndef KRNL_VGA_H
#define KRNL_VGA_H

#include <krnl/types.h>
#include <krnl/attrs.h>

void vga_init(void);

void vga_clear(void);

void vga_print(const ui8 *str, ui64 len);

void vga_move(ui16 cur);

#endif
