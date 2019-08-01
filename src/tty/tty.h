#ifndef TTY_H
#define TTY_H
#include "../stdlib/stdint.h"

/*char in vga consist of 2 bytes:
 *1 byte(low) :code of char
 *2 byte(high):4 bits(low) is foreground color, 4 bits(high) is background color*/
typedef uint16_t vga_char;

/*Я чуть не сошел с ума, пока пытался включить монохромный режим. Он просто не работает. Забил и использую цветной режим. Не знаю, на кой черт мне цвета, но монохром просто не работает.*/
static vga_char* const VGA_PTR = (uint16_t*) 0xB8000;/*VGA mode 3 buffer (0xB8000..0xBFFFF)*/
static const uint8_t VGA_WIDTH       = 80;    /*standard VGA width*/
static const uint8_t VGA_HEIGHT      = 25;    /*standard VGA height*/
/*VGA ports to 32-bits registers storing cursor position in 16-bit values. MUST BE UNSIGNED 32 BITS. I'm serious. But register is 16-bit*/
static const uint32_t CURSOR_DATA    = 0x03D4;/*this port get high byte cursor position*/
static const uint32_t CURSOR_OFFSET  = 0x03D5;/*this port get low  byte cursor position*/
/*cursor commands*/
static const uint8_t  HIGH_BYTE_NOW  = 0x0E;  /*tell VGA that next byte in CURSOR_OFFSET will be high*/
static const uint8_t  LOW_BYTE_NOW   = 0x0F;  /*tell VGA that next byte in CURSOR_OFFSET will be low*/

enum vga_color/*VGA mode 3 color constants*/
{
	VGA_COLOR_BLACK         = 0x00,
	VGA_COLOR_BLUE          = 0x01,
	VGA_COLOR_GREEN         = 0x02,
	VGA_COLOR_CYAN          = 0x03,
	VGA_COLOR_RED           = 0x04,
	VGA_COLOR_MAGENTA       = 0x05,
	VGA_COLOR_BROWN         = 0x06,
	VGA_COLOR_LIGHT_GREY    = 0x07,
	VGA_COLOR_DARK_GREY     = 0x08,
	VGA_COLOR_LIGHT_BLUE    = 0x09,
	VGA_COLOR_LIGHT_GREEN   = 0x0a,
	VGA_COLOR_LIGHT_CYAN    = 0x0b,
	VGA_COLOR_LIGHT_RED     = 0x0c,
	VGA_COLOR_LIGHT_MAGENTA = 0x0d,
	VGA_COLOR_LIGHT_BROWN   = 0x0e,
	VGA_COLOR_WHITE         = 0x0f,
};

extern struct vga_terminal vga_term;

extern void vga_set_color(const uint8_t foreground, const uint8_t background);
extern void vga_term_update();
extern void vga_update_for_keyboard(char c);
void vga_init(const uint8_t color);

void vga_set_cursor_position(const uint16_t position);
int16_t vga_get_cursor_position();

void vga_clear_screen();

void vga_print_char(char c);
void vga_print_string(const char* str, const uint16_t size);
#endif
