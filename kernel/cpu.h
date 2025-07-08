#ifndef _CPU_H
#define _CPU_H


#include "common.h"


static inlined void
cpuid(int code, uint32_t *a, uint32_t *d)
{
    asm volatile ("cpuid" : "=a"(*a), "=d"(*d) : "0"(code) : "ebx", "ecx");
}


static inlined uint64_t
rdtsc(void)
{
    uint64_t ret;
    asm volatile ("rdtsc" : "=A"(ret));
    return ret;
}


static inlined uint64_t
rdtsc(void)
{
    uint32_t low, high;
    asm volatile ("rdtsc" : "=a"(low), "=d"(high));
    return ((uint64_t)high << 32) | low;
}


static inlined uint64_t
read_cr0(void)
{
    uint64_t ret;
    asm volatile ("mov %%cr0, %0" : "=r"(ret));
    return ret;
}


static inlined uint64_t
read_cr2(void)
{
    uint64_t ret;
    asm volatile ("mov %%cr2, %0" : "=r"(ret));
    return ret;
}


static inlined uint64_t
read_cr3(void)
{
    uint64_t ret;
    asm volatile ("mov %%cr3, %0" : "=r"(ret));
    return ret;
}


static inlined uint64_t
read_cr4(void)
{
    uint64_t ret;
    asm volatile ("mov %%cr4, %0" : "=r"(ret));
    return ret;
}


static inlined void
invlpg(void *off)
{
    asm volatile ("invlpg (%0)" : : "b"(off) : "memory");
}


static inlined void
wrmsr(uint64_t msr, uint64_t value)
{
    uint32_t low = value & 0xffffffff;
    uint32_t high = value >> 32;
    asm volatile ("wrmsr" : : "c"(msr), "a"(low), "d"(high));
}


static inlined uint64_t
rdmsr(uint64_t msr)
{
    uint32_t low, high;
    asm volatile ("rdmsr" : "=a"(low), "=d"(high) : "c"(msr));
    return ((uint64_t)high << 32) | low;
}


#endif /*_CPU_H*/
