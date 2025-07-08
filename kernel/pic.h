#ifndef _PIC_H
#define _PIC_H


#include "common.h"
#include "io.h"


#define PIC_MASTER          0x20
#define PIC_SLAVE           0xa0
#define PIC_MASTER_COMMAND  PIC_MASTER
#define PIC_MASTER_DATA     (PIC_MASTER + 1)
#define PIC_SLAVE_COMMAND   PIC_SLAVE
#define PIC_SLAVE_DATA      (PIC_SLAVE + 1)


#define ICW1_ICW4           0x01
#define ICW1_SINGLE         0x02
#define ICW1_INTERVAL4      0x04
#define ICW1_LEVEL          0x08
#define ICW1_INIT           0x10
#define ICW4_8086           0x01
#define ICW4_AUTO           0x02
#define ICW4_BUF_SLAVE      0x08
#define ICW4_BUF_MASTER     0x0c
#define ICW4_SFNM           0x10


#define PIC_OCW3_IRR        0x0a
#define PIC_OCW3_ISR        0x0b
#define PIC_OCW3_REG(var, ocw3)                 \
    do {                                        \
        outb(PIC_MASTER_COMMAND, ocw3);         \
        outb(PIC_SLAVE_COMMAND, ocw3);          \
        var = (inb(PIC_SLAVE_COMMAND) << 8)     \
            | inb(PIC_MASTER_COMMAND);          \
    } while (false)


#define PIC_EOI             0x20
#define PIC_SEND_EOI(irq)                       \
    do {                                        \
        if ((irq) >= 8)                         \
            outb(PIC_SLAVE_COMMAND, PIC_EOI);   \
        outb(PIC_MASTER_COMMAND, PIC_EOI);      \
    } while (false)


static inlined uint16_t
pic_isr_get()
{
    uint16_t reg;
    PIC_OCW3_REG(reg, PIC_OCW3_ISR);
    return reg;
}


static inlined uint16_t
pic_irr_get()
{
    uint16_t reg;
    PIC_OCW3_REG(reg, PIC_OCW3_IRR);
    return reg;
}


static inlined void
pic_irq_remap(uint8_t master_offset, uint8_t slave_offset)
{
	uint8_t master_mask = inb(PIC_MASTER_DATA);
	uint8_t slave_mask = inb(PIC_SLAVE_DATA);

	outb(PIC_MASTER_COMMAND, ICW1_INIT | ICW1_ICW4);
	outb(PIC_SLAVE_COMMAND, ICW1_INIT | ICW1_ICW4);

	outb(PIC_MASTER_DATA, master_offset);
	outb(PIC_SLAVE_DATA, slave_offset);

	outb(PIC_MASTER_DATA, 4);
	outb(PIC_SLAVE_DATA, 2);

	outb(PIC_MASTER_DATA, ICW4_8086);
	outb(PIC_SLAVE_DATA, ICW4_8086);

	outb(PIC_MASTER_DATA, master_mask);
	outb(PIC_SLAVE_DATA, slave_mask);
}


static inlined void
pic_mask_set(uint8_t irq)
{
    uint16_t port;

    if(irq < 8)
        port = PIC_MASTER_DATA;

    else {
        port = PIC_SLAVE_DATA;
        irq -= 8;
    }

    uint8_t val = inb(port) | (1 << irq);
    outb(port, val);
}


static inlined void
pic_mask_clear(uint8_t irq)
{
    uint16_t port;

    if (irq < 8)
        port = PIC_MASTER_DATA;

    else {
        port = PIC_SLAVE_DATA;
        irq -= 8;
    }

    uint8_t val = inb(port) & ~(1 << irq);
    outb(port, val);
}


#endif /*_PIC_H*/
