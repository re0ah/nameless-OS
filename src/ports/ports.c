#include "ports.h"

inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ("inb %%dx, %%al" : "=a" (ret) : "d" (port));
    return ret;
}

inline void outb(uint16_t port, uint8_t data)
{
    asm volatile ("outb %%al, %%dx" : : "a" (data), "d" (port));
}

inline void io_wait()
{
    asm volatile ("outb %%al, $0x80" : : "a"(0));
}
