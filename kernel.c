#include "tty/tty.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "multiboot.h"
#include "mm/mm.h"

extern uint32_t kernel_end;
extern uint32_t kernel_base;
extern uint32_t kernel_size;

int32_t kernel(multiboot_info_t *mbinfo)
{
	vga_clear_screen();

	init_gdt();
	init_idt();

	init_mm(mbinfo, &kernel_base, &kernel_end, &kernel_size);

	asm volatile("sti"); /*enable interrupts*/
	
	vga_term_update();
	return 0;
}
