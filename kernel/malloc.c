#include "malloc.h"
#include "mmap.h"
#include "string.h"


#define SEGSIZE         sizeof(struct mm_seg)


extern struct mm_seg *head_seg;


void *
malloc(size_t size)
{
    uint64_t rem = size % 8;
    size += rem != 0 ? (8 - rem) : 0;

    struct mm_seg  *curr_seg = head_seg;

    do {
        if (curr_seg->len >= size) {
            if (curr_seg->len > SEGSIZE + size) {
                struct mm_seg *new_seg = (void *)((uint64_t)curr_seg + SEGSIZE + size);

                new_seg->len = curr_seg->len - (SEGSIZE + size);
                new_seg->next = curr_seg->next;
                new_seg->prev = curr_seg;
                new_seg->next_free = curr_seg->next_free;
                new_seg->prev_free = curr_seg->prev_free;
                new_seg->stat = FREE;

                curr_seg->len = size;
                curr_seg->next = new_seg;
                curr_seg->next_free = new_seg;
            }
            curr_seg->stat = ALLOCATED;

            if (curr_seg == head_seg)
                head_seg = curr_seg->next_free;

            if (curr_seg->next != 0)
                curr_seg->next->prev_free = curr_seg->prev_free;

            if (curr_seg->prev != 0)
                curr_seg->prev->next_free = curr_seg->next_free;

            if (curr_seg->next_free != 0)
                curr_seg->next_free->prev_free = curr_seg->prev_free;

            if (curr_seg->prev_free != 0)
                curr_seg->prev_free->next_free = curr_seg->next_free;

            return curr_seg + 1;
        }

        if (curr_seg->next_free == 0) break;

        curr_seg = curr_seg->next_free;
    } while (true);

    return 0;
}


void *
calloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr) memset(ptr, 0, size);
    return ptr;
}


void *
aligned_malloc(size_t size, uint32_t align)
{
    uint32_t align_rem = align % 8;
    align += align_rem != 0 ? (8 - align_rem) : 0;

    uint32_t size_rem = size % 8;
    size += size_rem != 0 ? (8 - size_rem) : 0;

    uint64_t new_size = size + align;

    void *alloc = malloc(new_size);
    uint64_t addr = (uint64_t)alloc;

    uint64_t rem = addr % align;
    addr -= rem;

    if (rem != 0) {
        addr += align;

        struct mm_aseg *a_seg = (struct mm_aseg *)addr - 1;
        a_seg->seg_addr = (uint64_t)alloc - SEGSIZE;
        a_seg->aligned = true;
    }

    return (void *)addr;
}


void *
realloc(void *ptr, size_t size)
{
    if (!ptr)
        return 0;

    if (size == 0) {
        free(ptr);
        return 0;
    }

    struct mm_seg *old = (struct mm_seg *)ptr - 1;
    size_t len = old->len < size ? old->len : size;

    void *new_ptr = malloc(size);
    memcpy(new_ptr, ptr, len);
    free(ptr);
    return new_ptr;
}


static inlined void
collapse_seg(struct mm_seg *a, struct mm_seg *b)
{
    if (a == 0 || b == 0)
        return;

    if (a < b) {
        a->len += b->len + SEGSIZE;
        a->next = b->next;
        a->next_free = b->next_free;

        b->next->prev = a;
        b->next->prev_free = a;
        b->next_free->prev_free = a;
    } else {
        b->len += a->len + SEGSIZE;
        b->next = a->next;
        b->next_free = a->next_free;

        a->next->prev = b;
        a->next->prev_free = b;
        a->next_free->prev_free = b;
    }
}


void
free(void *ptr)
{
    struct mm_seg *curr_seg;
    struct mm_aseg *a_seg = (struct mm_aseg *)ptr - 1;

    if (a_seg->aligned)
        curr_seg = (struct mm_seg *)(uint64_t)a_seg->seg_addr;
    else
        curr_seg = (struct mm_seg *)ptr - 1;

    curr_seg->stat = FREE;

    if (curr_seg < head_seg)
        head_seg = curr_seg;

    if (curr_seg->next_free != 0)
        if (curr_seg->next_free->prev_free < curr_seg)
            curr_seg->next_free->prev_free = curr_seg;

    if (curr_seg->prev_free != 0)
        if (curr_seg->prev_free->next_free > curr_seg)
            curr_seg->prev_free->next_free = curr_seg;

    if (curr_seg->next != 0) {
        curr_seg->next->prev = curr_seg;
        if (curr_seg->next->stat == FREE)
            collapse_seg(curr_seg, curr_seg->next);
    }

    if (curr_seg->prev != 0) {
        curr_seg->prev->next = curr_seg;
        if (curr_seg->prev->stat == FREE)
            collapse_seg(curr_seg, curr_seg->prev);
    }
}
