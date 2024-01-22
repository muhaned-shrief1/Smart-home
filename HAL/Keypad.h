/*
 * Keypad.h
 *
 *  Created on: Oct 23, 2016
 *      Author: ahmed
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../MCAL/DIO.h"
#include "../ServiceLayer/PLATFORM_TYPES.h"
#include <avr/io.h>
#include <util/delay.h>

/*Wiring diagram*/

/* * * *c1  c2 c3
 * row1  1  2  3
 * row2  4  5  6
 * row3  7  8  9
 */

#define KEYPAD_PORT_OUT_R PORTB
#define KEYPAD_PORT_IN_R  PINB
#define KEYPAD_PORT_DIR_R DDRB

#define KEYPAD_PORT_OUT_C PORTD
#define KEYPAD_PORT_IN_C  PIND
#define KEYPAD_PORT_DIR_C DDRD

#define FIRST_ROW  (4)
#define SECOND_ROW (5)
#define THIRD_ROW  (6)

#define FIRST_COL  (2)
#define SECOND_COL (3)
#define THIRD_COL  (4)

void  Keypad_init(void);
uint8 Keypad_get_pressed_key(void);


#endif /* KEYPAD_H_ */
