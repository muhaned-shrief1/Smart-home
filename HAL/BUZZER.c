/*
 * BUZZER.c
 *
 *  Created on: Dec 16, 2016
 *      Author: ahmed
 */

#include "BUZZER.h"

void Buzzer_init(void)
 {
	SET_BIT(BUZZER_DIR,BUZZER_PIN);
	CLEAR_BIT(BUZZER_PORT , BUZZER_PIN);
 }
