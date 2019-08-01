#include "gdt.h"

static const uint16_t GDT_LIMIT     = 0xFFFF;/*limit 0..15*/
static const uint8_t  GDT_ACCESS_CS = 0x9A;  /*access byte
		1 - present bit, must be 1 for valid selector
        0 - privilege, contains ring level
        0 - privelege, contains ring level
        1 - descriptor type, task state segment
        1 - executable bit
            1 - segment can be executed
            0 - is a data selector
        0 - direction/conforming bit
        	for data segment: (direction bit)
                0 - segment grows up
                1 - segment grows down
            for code segment: (conforming bit)
                1 - code can be executed from an equal or lower privelege level. Privelege bits represent the highest privelege level that is allowed to execute the segment.
                0 - code can only be executed from the ring set in privl
        1 - readable bit/writable bit
        	for data segment: (writable bit)
                write access for this segment, always allowed for data
            for code segment: (readable bit)
                read access for this segment, always never for code
        0 - accessed bit, cpu set this 1 when the segment accessed*/
static const uint8_t  GDT_ACCESS_DS = 0x92; /*access byte, see up*/
static const uint8_t  GDT_FLAGS     = 0xCF; /*flags
        1 - granularity bit
            0 - limit is in 1B   blocks. Byte granularity
            1 - limit is in 4KiB blocks. Page granularity
        1 - size bit
        	0 - 16-bit protected mode
        	1 - 32-bit protected mode
        0 - reserved
        0 - reserved
        & limit 16-19 (1111)*/

struct gdt_entry gdt[3] =
{
	{0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00}, 				   /*null segment*/
	{GDT_LIMIT, 0x0000, 0x00, GDT_ACCESS_CS, GDT_FLAGS, 0x00}, /*code segment*/
	{GDT_LIMIT, 0x0000, 0x00, GDT_ACCESS_DS, GDT_FLAGS, 0x00}  /*data segment*/
};
struct gdt_ptr gdtp = 
{
	sizeof(gdt) - 1,
	(uint32_t) &gdt
};

void init_gdt()
{
	vga_print_string("Initialized The Global Descriptor Table\n", 40);
	asm volatile("lgdt (%0)\n\t" : : "a"(&gdtp)); /*load gdtp in gdtp, khm.*/
	asm volatile("movw $0x10, %ax\n\t");
	asm volatile("movw %ss,   %ax\n\t");
	asm volatile("movw %ds,   %ax\n\t");
	asm volatile("movw %es,   %ax\n\t");
	asm volatile("movw %fs,   %ax\n\t");
	asm volatile("movw %gs,   %ax\n\t");
	vga_print_string("Loaded The Global Descriptor Table\n", 35);
}
