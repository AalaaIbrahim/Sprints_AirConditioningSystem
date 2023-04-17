/*
 * keypad.c
 *
 * Created: 4/17/2023 4:07:05 AM
 *  Author: ME
 */ 
/*************************************************************************************************************
 * 													Includes
 ************************************************************************************************************/
#include "../../Common/STD_Types.h"
#include "../../Common/BIT_Math.h"

#include "../../MCAL/dio/dio_interface.h"

#include "keypad.h"
/*************************************************************************************************************
 * 												Global Variables
 ************************************************************************************************************/
uint8_t keys_arr [] = {'+','-','=','~','0','6','7','8','9'};
/*************************************************************************************************************
 * 											Function Implementation
 ************************************************************************************************************/

void KEYPAD_init()
{
	KEYPAD_DIR &=~(1<<C1) | (1<<C2) | (1<<C3); // COLUMNS ARE INPUTS
	KEYPAD_DIR |= (1<<R1) | (1<<R2) | (1<<R3); // ROWS ARE OUTPUTS	
}
EN_KEYPAD_BTNS checkR1()
{
	
	KEYPAD_PORT |= (1<<C1) | (1<<C2) |(1<<C3) | (1<<R2) | (1<<R3);
	KEYPAD_PORT &=~ (1<<R1);
	if(GET_BIT(PINC,C1) == 0)
	{
		
		while (GET_BIT(PINC,C1) == 0);
		return KEY_INCREAMENT;
	}
	if(GET_BIT(PINC,C2) == 0)
	{
		while (GET_BIT(PINC,C2) == 0);
		return KEY_DECREAMENT;
	}
	if(GET_BIT(PINC,C3) == 0)
	{
		
		while (GET_BIT(PINC,C3) == 0);
		return KEY_SET;
	}
	return KEY_NOTHING;
	
}
EN_KEYPAD_BTNS checkR2()
{
	KEYPAD_PORT |= (1<<C1) | (1<<C2) |(1<<C3) | (1<<R1) | (1<<R3);
	KEYPAD_PORT &=~ (1<<R2);
	if(GET_BIT(PINC,C1) == 0)
	{
		
		while (GET_BIT(PINC,C1) == 0);
		return KEY_ADJUST;
	}
	if(GET_BIT(PINC,C2) == 0)
	{
		while (GET_BIT(PINC,C2) == 0);
		return KEY_RESET;
	}
	if(GET_BIT(PINC,C3) == 0)
	{
		
		while (GET_BIT(PINC,C3) == 0);
		return KEY_6;
	}
	return KEY_NOTHING;
	
}
EN_KEYPAD_BTNS checkR3()
{
	KEYPAD_PORT |= (1<<C1) | (1<<C2) |(1<<C3) | (1<<R1) | (1<<R2);
	KEYPAD_PORT &=~ (1<<R3);
	if(GET_BIT(PINC,C1) == 0)
	{
		
		while (GET_BIT(PINC,C1) == 0);
		return KEY_7;
	}
	if(GET_BIT(PINC,C2) == 0)
	{
		while (GET_BIT(PINC,C2) == 0);
		return KEY_8;
	}
	if(GET_BIT(PINC,C3) == 0)
	{
		
		while (GET_BIT(PINC,C3) == 0);
		return KEY_9;
	}
	return KEY_NOTHING;
	
}

EN_KEYPAD_BTNS GetButton()
{
	EN_KEYPAD_BTNS PRESSED = KEY_NOTHING;
	while(PRESSED == KEY_NOTHING)
	{
		PRESSED = checkR1();
		if(PRESSED != KEY_NOTHING) return PRESSED;
		PRESSED = checkR2();
		if(PRESSED != KEY_NOTHING) return PRESSED;
		PRESSED = checkR3();
		if(PRESSED != KEY_NOTHING) return PRESSED;
		return KEY_NOTHING;
	}
	
	return KEY_NOTHING;
}