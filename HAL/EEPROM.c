/*
 * EEPROM.c
 *
 *  Created on: Oct 23, 2016
 *      Author: ahmed
 */

#include "EEPROM.h"

void EEPROM_write(uint16 Address,uint8 Data)
 {
	while(EECR&(1<<EEWE));

	EEAR=Address;
	EEDR=Data;

	SET_BIT(EECR,EEMWE);
	SET_BIT(EECR,EEWE);

 }

uint8 EEPROM_read(uint16 Address)
 {
	while(EECR&(1<<EEWE));

	EEAR=Address;

	SET_BIT(EECR,EERE);
	return EEDR;
 }
