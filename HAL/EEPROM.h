/*
 * EEPROM.h
 *
 *  Created on: Oct 23, 2016
 *      Author: ahmed
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>
#include <util/delay.h>
#include "../MCAL/DIO.h"
#include "../ServiceLayer/PLATFORM_TYPES.h"

void EEPROM_write(uint16 Address,uint8 Data);
uint8 EEPROM_read(uint16 Address);

#endif /* EEPROM_H_ */
