#ifndef SCANCODE_H
#define SCANCODE_H
/*low case*/
uint8_t qwerty_low[128] = {
	0,  /*null*/
	27, /*esc*/
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'0',
	'-',
	'=',
	'\b', /*backspace*/
	'\t', /*tab*/
	'q',
	'w',
	'e',
	'r',
	't',
	'y',
	'u',
	'i',
	'o',
	'p',
	'[',
	']',
	'\n', /*enter*/
	0,    /*left control*/
	'a',
	's',
	'd',
	'f',
	'g',
	'h',
	'j',
	'k',
	'l',
	';',
	'\'',
	'`',
	0,    /*left shift*/
	'\\',
	'z',
	'x',
	'c',
	'v','b',
	'n',
	'm',
	',',
	'.',
	'/',
	0, /*right shift*/
	0, /*keypad **/
	0, /*left alt*/
	' ',
	0, /*caps lock*/
	0, /*f1*/
	0, /*f2*/
	0, /*f3*/
	0, /*f4*/
	0, /*f5*/
	0, /*f6*/
	0, /*f7*/
	0, /*f8*/
	0, /*f9*/
	0, /*f10*/
	0, /*num lock*/
	0, /*scroll lock*/
	0, /*keypad 7*/
	0, /*keypad 8*/
	0, /*keypad 9*/
	0, /*keypad -*/
	0, /*keypad 4*/
	0, /*keypad 5*/
	0, /*keypad 6*/
	0, /*keypad +*/
	0, /*keypad 1*/
	0, /*keypad 2*/
	0, /*keypad 3*/
	0, /*keypad 0*/
	0, /*keypad .*/
	0, /*empty*/
	0, /*empty*/
	0, /*empty*/
	0, /*f11*/
	0, /*f12*/
};
/*upper_case*/
uint8_t qwerty_up[128] = {
	0,  /*null*/
	27, /*esc*/
	'!',
	'@',
	'#',
	'$',
	'%',
	'^',
	'&',
	'*',
	'(',
	')',
	'_',
	'+',
	'\b', /*backspace*/
	'\t', /*tab*/
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'{',
	'}',
	'\n', /*enter*/
	0,    /*left control*/
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	':',
	'"',
	'~',
	0,   /*left shift*/
	'|',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',
	'<',
	'>',
	'?',
	0, /*right shift*/
	0, /*keypad **/
	0, /*left alt*/
	' ',
	0, /*caps lock*/
	0, /*f1*/
	0, /*f2*/
	0, /*f3*/
	0, /*f4*/
	0, /*f5*/
	0, /*f6*/
	0, /*f7*/
	0, /*f8*/
	0, /*f9*/
	0, /*f10*/
	0, /*num lock*/
	0, /*scroll lock*/
	0, /*keypad 7*/
	0, /*keypad 8*/
	0, /*keypad 9*/
	0, /*keypad -*/
	0, /*keypad 4*/
	0, /*keypad 5*/
	0, /*keypad 6*/
	0, /*keypad +*/
	0, /*keypad 1*/
	0, /*keypad 2*/
	0, /*keypad 3*/
	0, /*keypad 0*/
	0, /*keypad .*/
	0, /*empty*/
	0, /*empty*/
	0, /*empty*/
	0, /*f11*/
	0, /*f12*/
};
#endif
