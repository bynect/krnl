#include "mmap.h"
#include "string.h"


struct mmap_entry *usable_regions[16];

uint8_t usable_count = 0;


struct mmap_entry **
get_usable_regions(void)
{
    static bool done = false;

    if (!done) {
        for (uint8_t i = 0; i < __mem_region_count; ++i) {
            struct mmap_entry *mmap = (void *)0x5000;
            mmap += i;

            if (mmap->type == 1)
                usable_regions[usable_count++] = mmap;
        }
    }

    done = true;
    return usable_regions;
}


struct mm_seg *head_seg;


void
init_head_seg(uint64_t addr, uint64_t len)
{
    head_seg = (void *)addr;
    head_seg->len = len - sizeof(struct mm_seg);
    head_seg->next = NULL;
    head_seg->prev = NULL;
    head_seg->next_free = NULL;
    head_seg->prev_free = NULL;
    head_seg->stat = FREE;
}
