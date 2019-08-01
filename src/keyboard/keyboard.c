#include "keyboard.h"
#include "scancode.h"
#include "../idt/idt.h"
#include "../ports/ports.h"
#include "../tty/tty.h"

__attribute__((interrupt)) void keyboard_handler(void* unused)
{
	uint8_t scancode = inb(KEYBOARD_DATA_PORT);
	static uint8_t upper_case;

	if ((scancode & 0x80))
	{
		if (scancode == 0xAA || scancode == 0xB6)
		{
			upper_case = 0;
		}
	}
	else
	{
		if (scancode == 0x36 || scancode == 0x2A)
		{
			upper_case = 1;
			outb(PICM, PIC_EOI);/*write end of interrupt code to PICM*/
			return;
		}
	}

	// PRINT CHAR
	if (!(scancode & 0x80))
	{
		unsigned char c = (upper_case ? qwerty_up[scancode] : qwerty_low[scancode]);

		if (c == '\b')
		{
			const short pos = vga_get_cursor_position() - 1;

			if (pos + 1 <= 0)
			{
				return
				outb(PICM, PIC_EOI);/*write end of interrupt code to PICM*/
			}
			vga_print_char(c);
			vga_update_for_keyboard(c);
			outb(PICM, PIC_EOI);/*write end of interrupt code to PICM*/
			return;
		}

		vga_print_char(c);
		vga_update_for_keyboard(c);
	}
	outb(PICM, PIC_EOI);/*write end of interrupt code to PICM*/
}
