#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "../stdlib/stdint.h"

static const uint8_t KEYBOARD_DATA_PORT = 0x60;

void keyboard_handler(void* unused);

#endif
