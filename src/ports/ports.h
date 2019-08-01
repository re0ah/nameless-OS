#ifndef PORT_H
#define PORT_H
#include "../stdlib/stdint.h"
extern uint8_t inb(uint16_t port);

extern void outb(uint16_t port, uint8_t data);

extern void io_wait();
#endif
