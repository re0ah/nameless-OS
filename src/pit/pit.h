#ifndef PIT_H
#define PIT_H
#include "../stdlib/stdint.h"

/*more on http://www.scs.stanford.edu/10wi-cs140/pintos/specs/8254.pdf*/
/*control word register:
	0    bit : BCD
		0   = 16-bit binary counter
		1   = 16-bit BCD    counter
	1..3 bits: modes
		000 = mode 0: interrupt on terminal count
 		001 = mode 1: hardware retriggerable one-shot
 		010 = mode 2: rate generator
 		011 = mode 3: square wave
 		100 = mode 4: software triggered strobe
 		101 = mode 5: harware  triggered strobe (retriggerable)
 	4..5 bits: read_write
		00  = counter latch commands
		01  = read/write least significant byte only
		10  = read/write most  significant byte only
		11  = read/write least significant byte first, them most significant byte
 	6..7 bits: select counter
		00  = counter 0
 		01  = counter 1
 		10  = counter 2
 		11  = read-back command*/
static const uint8_t PIT_MODE3 = 0x06;/*square wave mode*/
static const uint8_t PIT_RW4   = 0x30;/*read/write least significant byte first, then most significant byte*/

static const uint8_t PIT_0_PORT    	   		 = 0x40;
static const uint8_t PIT_COMMAND_PORT  		 = 0x43;
static const uint8_t PIT_DEFAULT_FREQUANCY 	 = 1193182;
static const uint8_t PIT_CONTROL_WORD_FORMAT = PIT_MODE3 | PIT_RW4;/*
													16-bit binary counter
													square wave
													first least byte, then most byte
													counter 0		*/

void pit_handler(void* unused);
void pit_phase(uint32_t speed);
void init_pit();

#endif
