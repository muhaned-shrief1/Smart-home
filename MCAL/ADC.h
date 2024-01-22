/*
 * ADC.h
 *
 *  Created on: Aug 4, 2016
 *      Author: ahmed
 */

#ifndef ADC_H_
#define ADC_H_

#include "../ServiceLayer/PLATFORM_TYPES.h"
#include <avr/io.h>


void ADC_init(void);
int ADC_read(uint8 Channel);


#endif /* ADC_H_ */
