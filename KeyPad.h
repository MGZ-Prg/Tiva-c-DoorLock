#ifndef KEYPAD
#define KEYPAD
#include "stdint.h"
#include <stdbool.h>
#include "GPIO.h"

#define rows 4
#define cols 4

#define keypad_L GPIO_PORTB_LOCK_R // lock register
#define keypad_C GPIO_PORTB_CR_R  // commit register
#define keypad_AM GPIO_PORTB_AMSEL_R // analog enable 
#define keypad_DE GPIO_PORTB_DEN_R //digital enable 
#define keypad_AF GPIO_PORTB_AFSEL_R //alternative function
#define keypad_PCTL GPIO_PORTB_PCTL_R // port control 0 for GPIO ,each 4 bits for represent 1 pin
#define keypad_PU GPIO_PORTB_PUR_R // pull up resistors
#define keypad_data GPIO_PORTB_DATA_R  // data register
#define keypad_dir GPIO_PORTB_DIR_R // driection register

unsigned char keypad_get_char();
void keypad_init();



#endif
