#ifndef GDT_H
#define GDT_H
#include "../tty/tty.h"

struct gdt_entry
{
	uint16_t limit_0_15;
	uint16_t base_0_15;
	uint8_t  base_0_23;
	uint8_t  access;
	uint8_t  flags;
	uint8_t  base_24_31;
} __attribute__((packed));

struct gdt_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

void init_gdt();

#endif
