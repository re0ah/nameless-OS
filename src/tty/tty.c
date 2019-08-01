#include "tty.h"
#include "../ports/ports.h"

struct vga_terminal
{
	vga_char buf[80 * 25 * 4]; /*why C compiler don't support const values in static arrays? I should use defines? No, i use comments. AHAHAHA! Sorry. 4 it is lists of text*/
/*buf store 4 lists of text and support scrolling*/
	uint8_t  offset; /*offset in lines of text*/
	uint8_t  color;
	uint16_t cursor_pos;
} term = 
{
	{0},
	0,
	0x07,/*foreground light grey, background black*/
	0 
};

inline void vga_set_color(const uint8_t foreground, const uint8_t background)
{
	term.color = foreground | (background << 4);
}

static inline vga_char vga_create_char(const char c, const uint8_t color)
{
	return (vga_char) (color << 8) | (vga_char) c;
}

void vga_init(const uint8_t color)
{
	term.color = color;
	term.offset = 0;
	term.cursor_pos = 0;
	for(int i = 0; i < 80 * 25 * 4; i++)
	{
		term.buf[i] = 0;
	}
	for(int i = 0; i < 80 * 25; i++)
	{
		VGA_PTR[i] = 0;
	}
	/*memset(term.buf, 0, 80 * 25 * 4);*/
}

static void vga_term_move_cursor()
{
	outb(CURSOR_DATA, LOW_BYTE_NOW);		  /*say that next byte is low*/
	outb(CURSOR_OFFSET, term.cursor_pos);	  /*get low byte*/
	outb(CURSOR_DATA, HIGH_BYTE_NOW);		  /*say that next byte is high*/
	outb(CURSOR_OFFSET, term.cursor_pos >> 8);/*get high byte*/
}

inline void vga_term_update()
{
	/*update VGA buffer*/
	//memcpy(VGA_PTR, term.buf + (VGA_HEIGHT * term.offset * sizeof(vga_char)), VGA_WIDTH * VGA_HEIGHT * sizeof(vga_char));
	/*move cursor*/
	uint16_t off = VGA_HEIGHT * term.offset;
	for(int i = 0; i < 80 * 25; i++)
	{
		VGA_PTR[i] = term.buf[off + i];
	}
	vga_term_move_cursor();
}

/*update all terminal in the moment of input from the keyboard - absurd, need separate function. Sorry, normal name for function i can't think*/
inline void vga_update_for_keyboard(char c)
{
	/*move cursor*/
	vga_term_move_cursor();
	/*update VGA buffer*/
	uint16_t pos = term.cursor_pos + (VGA_HEIGHT * term.offset * sizeof(vga_char));
	VGA_PTR[pos] = vga_create_char(c, 0x07);
}

inline void vga_set_cursor_position(const uint16_t position)
{
	term.cursor_pos = position;
}

inline int16_t vga_get_cursor_position()
{
	return term.cursor_pos;
}

void vga_clear_screen()
{
	uint32_t i = 0;
	while (i < (VGA_HEIGHT * VGA_WIDTH)) {
		term.buf[i] = vga_create_char(' ', VGA_COLOR_LIGHT_GREY | (VGA_COLOR_BLACK << 4));
		i++;
	}
	vga_set_cursor_position(0);
}

void vga_print_char(char c)
{
	uint8_t line = (term.cursor_pos / 80);
	if(line >= VGA_HEIGHT)
	{
		line--;
		term.offset++;
	}
	if(c == '\n')
	{
		term.cursor_pos = (line + 1) * 80;
	}
	else
	{
		uint16_t pos = term.cursor_pos + (term.offset * VGA_WIDTH);
		term.buf[pos] = vga_create_char(c, term.color);
		term.cursor_pos++;
	}
}

void vga_print_string(const char* str, const uint16_t size)
{
	for (int i = 0; i < size; i++)
	{
		vga_print_char(str[i]);
	}
}
