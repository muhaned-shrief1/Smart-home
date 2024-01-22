/*
 * lcd.c
 *
 *  Created on: 14 Sept 2022
 *      Author: Mahmoud Abdelmoniem
 */

#include "lcd.h"

static void Trigger_Enable();
static void Set_Cursor_Pos(uint8 row,uint8 column);
void LCD_Init(void)
{
	SET_BIT(LCD_DIR , PA2);
	SET_BIT(LCD_DIR , PA5);
	SET_BIT(LCD_DIR , PA6);

	SET_BIT(LCD_DIR , PA1);
	SET_BIT(LCD_DIR , PA3);
	SET_BIT(LCD_DIR , PA4);
	_delay_ms(20);
	LCD_Send_Command(0x33);
	LCD_Send_Command(0x32);
	LCD_Send_Command(_LCD_4BIT_MODE_2_LINE);
	LCD_Send_Command(_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
	LCD_Send_Command(_LCD_ENTRY_MODE_INC_SHIFT_OFF);
	LCD_Send_Command(_LCD_DDRAM_START);
	LCD_Send_Command(_LCD_CLEAR);
}
void LCD_Send_Command(uint8 command)
{
	CLEAR_BIT(LCD_PORT , RS);
	CLEAR_BIT(PORTC , RW);
	(READ_BIT(command,7)) ? SET_BIT(LCD_PORT , D7) : CLEAR_BIT(LCD_PORT , D7);
	(READ_BIT(command,6)) ? SET_BIT(LCD_PORT , D6) : CLEAR_BIT(LCD_PORT , D6);
	(READ_BIT(command,5)) ? SET_BIT(LCD_PORT , D5) : CLEAR_BIT(LCD_PORT , D5);
	(READ_BIT(command,4)) ? SET_BIT(LCD_PORT , D4) : CLEAR_BIT(LCD_PORT , D4);
	//Trigger Enable
	Trigger_Enable();
	(READ_BIT(command,3)) ? SET_BIT(LCD_PORT , D7) : CLEAR_BIT(LCD_PORT , D7);
	(READ_BIT(command,2)) ? SET_BIT(LCD_PORT , D6) : CLEAR_BIT(LCD_PORT , D6);
	(READ_BIT(command,1)) ? SET_BIT(LCD_PORT , D5) : CLEAR_BIT(LCD_PORT , D5);
	(READ_BIT(command,0)) ? SET_BIT(LCD_PORT , D4) : CLEAR_BIT(LCD_PORT , D4);
	//Trigger Enable
	Trigger_Enable();
}
void LCD_Send_Char(uint8 _char)
{
	SET_BIT(LCD_PORT , RS);
	CLEAR_BIT(PORTC , RW);
	(READ_BIT(_char,7)) ? SET_BIT(LCD_PORT , D7) : CLEAR_BIT(LCD_PORT , D7);
	(READ_BIT(_char,6)) ? SET_BIT(LCD_PORT , D6) : CLEAR_BIT(LCD_PORT , D6);
	(READ_BIT(_char,5)) ? SET_BIT(LCD_PORT , D5) : CLEAR_BIT(LCD_PORT , D5);
	(READ_BIT(_char,4)) ? SET_BIT(LCD_PORT , D4) : CLEAR_BIT(LCD_PORT , D4);
	//Trigger Enable
	Trigger_Enable();
	(READ_BIT(_char,3)) ? SET_BIT(LCD_PORT , D7) : CLEAR_BIT(LCD_PORT , D7);
	(READ_BIT(_char,2)) ? SET_BIT(LCD_PORT , D6) : CLEAR_BIT(LCD_PORT , D6);
	(READ_BIT(_char,1)) ? SET_BIT(LCD_PORT , D5) : CLEAR_BIT(LCD_PORT , D5);
	(READ_BIT(_char,0)) ? SET_BIT(LCD_PORT , D4) : CLEAR_BIT(LCD_PORT , D4);
	//Trigger Enable
	Trigger_Enable();
}
void LCD_Send_Char_Pos(uint8 _char,uint8 row,uint8 column)
{
	Set_Cursor_Pos(row,column);
	LCD_Send_Char(_char);
}
void LCD_Send_String(uint8 *string)
{
	while(*string !='\0')
	{
		LCD_Send_Char(*string++);
	}
}
void LCD_Send_String_Pos(uint8 *string,uint8 row,uint8 column)
{
	Set_Cursor_Pos(row,column);
	LCD_Send_String(string);
}

void LCD_Send_Number(uint32 num)
{
	uint8 arr[10],i=0,j=0;
	if(num == 0)
	{
		LCD_Send_Char('0');
	}
	else
	{
		while(num)
		{
			arr[i]=num%10+'0';
			num/=10;
			i++;
		}
		for(j=i;j>0;j--)
		{
			LCD_Send_Char(arr[j-1]);
		}
	}
}
void LCD_Send_Number_Pos(uint32 num,uint8 row,uint8 column)
{
	Set_Cursor_Pos(row,column);
	LCD_Send_Number(num);
	LCD_Send_Char('   ');
}

void LCD_Send_Cust_char(const uint8 _char[],uint8 row,uint8 column,uint8 mem_pos){
	uint8 lcd_counter=0;
	LCD_Send_Command((_LCD_CGRAM_START + (mem_pos*8)));
	for(lcd_counter =0;lcd_counter <= 7;lcd_counter++){
		LCD_Send_Char(_char[lcd_counter]);
	}
	LCD_Send_Char_Pos(mem_pos,row,column);
}
static void Trigger_Enable()
{
	SET_BIT(LCD_PORT , EN);
	_delay_us(10);
	CLEAR_BIT(LCD_PORT ,EN);
	_delay_us(2000);
}
static void Set_Cursor_Pos(uint8 row,uint8 column)
{
	column--;
	switch(row)
	{
	case ROW1: LCD_Send_Command((0x80 + column)); break;
	case ROW2: LCD_Send_Command((0xc0 + column)); break;
	default:;
	}
}
