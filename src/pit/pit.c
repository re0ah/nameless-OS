#include "pit.h"
#include "../tty/tty.h"
#include "../idt/idt.h"

static size_t pit_ticks = 0;

__attribute__((interrupt)) void pit_handler(void *unused)
{
	pit_ticks++;
	outb(PICM, PIC_EOI);/*write end of interrupt code to PICM*/
}

void init_pit()
{
	uint16_t hz      = 1000;
	uint16_t divisor = PIT_DEFAULT_FREQUANCY / hz;

	outb(PIT_COMMAND_PORT, PIT_CONTROL_WORD_FORMAT);/*set control word register*/
	outb(PIT_0_PORT, (uint8_t)divisor);  			/*set low  byte the divisor*/
	outb(PIT_0_PORT, divisor >> 8);      			/*set high byte the divisor*/
	vga_print_string("Initialized The Programmable Interrupt Controller\n", 50);
}
