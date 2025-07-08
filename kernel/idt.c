#include "idt.h"
#include "io.h"
#include "pic.h"


extern struct idt_entry _idt[256];


extern void idt_setup();


extern uint64_t isr0;
extern uint64_t isr1;


void isr0_handler()
{

}


void
idt_init(void)
{
    uint64_t isr0_addr = (uint64_t)&isr0;

    _idt[0].offset_low = (uint16_t)((isr0_addr & 0x000000000000ffff));
    _idt[0].selector = 0x08;
    _idt[0].ist = 0;
    _idt[0].types_attr = 0x8e;
    _idt[0].offset_mid = (uint16_t)((isr0_addr & 0x00000000ffff0000) >> 16);
    _idt[0].offset_high = (uint32_t)((isr0_addr & 0xffffffff00000000) >> 32);
    _idt[0].zero = 0;

    uint64_t isr1_addr = (uint64_t)&isr1;

    _idt[1].offset_low = (uint16_t)((isr1_addr & 0x000000000000ffff));
    _idt[1].selector = 0x08;
    _idt[1].ist = 0;
    _idt[1].types_attr = 0x8e;
    _idt[1].offset_mid = (uint16_t)((isr1_addr & 0x00000000ffff0000) >> 16);
    _idt[1].offset_high = (uint32_t)((isr1_addr & 0xffffffff00000000) >> 32);
    _idt[1].zero = 0;

    pic_irq_remap(1, 1);

    outb(0x21, 0xfd);
    outb(0xa1, 0xff);

    idt_setup();
}
