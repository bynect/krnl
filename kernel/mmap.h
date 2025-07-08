#ifndef _MMAP_H
#define _MMAP_H


#include "common.h"


extern uint8_t volatile __mem_region_count;


extern uint8_t usable_count;


struct mmap_entry {
    uint64_t addr_base;
    uint64_t addr_len;
    uint32_t type;
    uint32_t attrs;
} packed;


struct mmap_entry **get_usable_regions(void);


struct mm_seg {
    size_t len;
    struct mm_seg *next, *prev;
    struct mm_seg *next_free, *prev_free;
    enum {
        FREE,
        ALLOCATED,
        RESERVED
    } stat;
} packed;


struct mm_aseg {
    uint64_t seg_addr : 63;
    bool aligned : 1;
} packed;


void init_head_seg(uint64_t addr, uint64_t len);


#endif /*_MMAP_H*/
