#ifndef _VGA_H
#define _VGA_H


#include "common.h"


#define VGA_WIDTH           80
#define VGA_HEIGHT          25
#define VGA_MIN             0
#define VGA_MAX             VGA_WIDTH * VGA_HEIGHT


typedef enum {
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    PINK,
    YELLOW,
    WHITE,
} vga_color_t;


extern uint16_t cursor;


void cursor_set(uint16_t pos);


void cursor_move(uint8_t x, uint8_t y);


void clear(uint64_t col);


void printstr(const char *str, uint8_t fore, uint8_t back);


void printchr(const char chr, uint8_t fore, uint8_t back);


void printk(const char *str);


#endif /*_VGA_H*/
