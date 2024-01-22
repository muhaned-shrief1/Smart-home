/*
 * ADC.c
 *
 *  Created on: Aug 4, 2016
 *      Author: ahmed
 */
#include <avr/io.h>
#include "../ServiceLayer/PLATFORM_TYPES.h"

void ADC_init(void)
{
	//	ADMUX=(1<<REFS0)|(1<<MUX0);
	//	ADCSRA=(1<<ADEN)|(1<<ADPS1)|(1<<ADPS2);


	// Set the reference voltage to AVcc
	ADMUX |= (1 << REFS0);

	// Set the ADC prescaler to 128 for a 16MHz clock (adjust based on your clock speed)
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	// Enable the ADC
	ADCSRA |= (1 << ADEN);

}

int ADC_read(uint8 Channel)
{
	//	ADMUX &=0xE0; // clear least 5 bits (channel)
	//	Channel &=0x07; //reassignation for the input argument
	//	ADMUX |=Channel;
	//
	//	ADCSRA |=(1<<ADSC);
	//	while(ADCSRA & (1<<ADSC));
	//	return ADC;


	// Select the ADC channel (0-7)
	ADMUX = (ADMUX & 0xF0) | (Channel & 0x0F);

	// Start the ADC conversion
	ADCSRA |= (1 << ADSC);

	// Wait for the conversion to complete
	while (ADCSRA & (1 << ADSC));

	// Return the ADC result
	return ADC;
}


