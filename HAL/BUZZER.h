/*
 * BUZZER.h
 *
 *  Created on: Dec 16, 2016
 *      Author: ahmed
 */

#ifndef HAL_BUZZER_H_
#define HAL_BUZZER_H_

#include "../MCAL/DIO.h"
#include <avr/io.h>

#define  BUZZER_DIR DDRC
#define  BUZZER_PORT PORTC
#define  BUZZER_PIN PC5

#define  BUZZER_ON (SET_BIT(BUZZER_PORT,BUZZER_PIN))
#define  BUZZER_OFF (CLEAR_BIT(BUZZER_PORT,BUZZER_PIN))




void Buzzer_init(void);


#endif /* HAL_BUZZER_H_ */
