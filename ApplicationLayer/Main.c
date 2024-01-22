/*
 * Main.c
 *
 *  Created on: Oct 11, 2019
 *      Author: Sami Selim
 */
#include "../HAL/lcd.h"
#include "../HAL/BUZZER.h"
#include "../HAL/Keypad.h"
#include "../ServiceLayer/PLATFORM_TYPES.h"
#include "../MCAL/ADC.h"
#include "../MCAL/USART.h"
#include <string.h>
#include <util/delay.h>
char pass[]="1234";
char EnteredPass[5];
char Key=0,flag=0;
char ch = 200;
int tries=3 , i=0 ;
uint16 MQ5 , MQ2;


int main(void)
{

	/* Init System */
	LCD_Init();
	LCD_Send_Command(_LCD_CLEAR);
	LCD_Send_String_Pos((uint8 *)"  Smart Home :) " , 1, 1);
	_delay_ms(3000);



	LCD_Send_Command(_LCD_CLEAR);
	Buzzer_init();
	ADC_init();
	Keypad_init();


	/* Leds Init as output */
//	SET_BIT(DDRC , PIN0);
//	CLEAR_BIT(PORTC , PIN0);
//
//
//	SET_BIT(DDRC , PIN1);
//	CLEAR_BIT(PORTC , PIN1);
//
//
//	SET_BIT(DDRC , PIN2);
//	CLEAR_BIT(PORTC , PIN2);
//
//
//	SET_BIT(DDRC , PIN3);
//	CLEAR_BIT(PORTC , PIN3);

/* PINC 4 as Input for PIR Sensor */
	CLEAR_BIT(DDRC , PIN4);

	SET_BIT(DDRB , PIN0);
	CLEAR_BIT(PORTB , PIN0);

	SET_BIT(DDRB , PIN1);
	CLEAR_BIT(PORTB , PIN1);

	SET_BIT(DDRB , PIN2);
	CLEAR_BIT(PORTB , PIN2);

/******************************************************************************************************/
	while(1)
	{
		while(flag == 0){
			if(tries >0 ){
				do{
					LCD_Send_String_Pos((uint8 *)"Enter PIN:", 1,1);
					LCD_Send_String_Pos((uint8 *)"Tries: ", 2,2);
					LCD_Send_Number_Pos(tries , 2,8);
					Key = Keypad_get_pressed_key();
					if(Key !=0){
						EnteredPass[i] = Key;
						LCD_Send_Char_Pos(Key , 1,11+i);
						_delay_ms(500);
						LCD_Send_Char_Pos('*' , 1,11+i);
						i++;
					}
					if(i == 4){
						break;
					}
				}while(1);
				EnteredPass[4]='\0';

				/* Compare Entered Pass with right Pass */
				/* If strcmp return 0 --> Pass Right  */
				if(strcmp(EnteredPass , pass) == 0){
					flag = 1; /* you Don't enter while loop Again */
				}else{
					flag =0;  /* Repeat again to get Password */
				}
				if(flag >0){
					LCD_Send_String_Pos((uint8 *)"Correct Password" , 2,1);

					_delay_ms(2000);
					LCD_Send_Command(_LCD_CLEAR);

					break;
				}
				else{
					flag = 0;
					LCD_Send_String_Pos((uint8 *)"Wrong Password" , 2,1);
					_delay_ms(2000);
					LCD_Send_Command(_LCD_CLEAR);
					tries--;
					i=0;
				}
			}
			else{
				/*  i tries == 0 this will lock the system */
				BUZZER_ON;
				LCD_Send_Command(_LCD_CLEAR);
				while(1){
					LCD_Send_String_Pos((uint8 *)"System Locked",1,1);
				}
			}

		}
		MQ2 = ADC_read(7);
		MQ5 = ADC_read(0);

		LCD_Send_String_Pos((uint8 *)"MQ2:" , 1,1); /* ((uint8 *)) Casting for Pointer to uint8 which store my string */
		LCD_Send_String_Pos((uint8 *)"MQ5:" , 1,9);
		LCD_Send_String_Pos((uint8 *)"PIR:" , 2,1);

		LCD_Send_Number_Pos(MQ2 , 1 , 5);
		LCD_Send_Number_Pos(MQ5 , 1 , 13);

		if((MQ2 > 80) || (MQ5 > 200)){
			BUZZER_ON;
			if(MQ2 > 80){
				SET_BIT(PORTB , PIN1);
			}
			else if (MQ5 > 200){
				SET_BIT(PORTB , PIN0);
			}
		}else{
			BUZZER_OFF;
			CLEAR_BIT(PORTB , PIN0);
			CLEAR_BIT(PORTB , PIN1);
		}

		if(READ_BIT(PINC , PIN4) == 1){
			LCD_Send_String_Pos((uint8 *)"   Motion.    ",2,5);
			SET_BIT(PORTB , PIN2);
		}else{
			LCD_Send_String_Pos((uint8 *)"No Motion.",2,5);
			CLEAR_BIT(PORTB , PIN2);
		}
	}

	return 0;
}

