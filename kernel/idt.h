#ifndef _IDT_H
#define _IDT_H


#include "common.h"


struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t types_attr;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t zero;
} packed;


void idt_init(void);


#endif
