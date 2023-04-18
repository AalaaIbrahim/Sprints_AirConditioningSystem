/*************************************************************************************************************
* 													Includes
************************************************************************************************************/
#include <util/delay.h>
#include "../Common/STD_Types.h"
#include "../Common/BIT_Math.h"
#include "../Common/vect_table.h"

#include "../ECUAL/buzzer/buzzer.h"
#include "../ECUAL/htimer0/htimer0.h"
#include "../ECUAL/keypad/keypad.h"
#include "../ECUAL/lcd/lcd_interface.h"
#include "../ECUAL/temp_sensor/temp_sensor.h"

#include "app.h"
/*************************************************************************************************************
* 												Global Variables
************************************************************************************************************/
extern st_Buzzer_t st_g_Buzzer;
extern st_TempSensor_t st_g_TempSensor;
extern Uchar8_t arr_g_bell[8];

Uchar8_t u8_g_tempValue = DEFAULT_TEMP;
Uchar8_t u8_g_setFlag = 0;
Uchar8_t u8_g_CursorPosition = 0;

float32_t f32_l_CurrentTemp = 0;

Uchar8_t lcdDelay = 0;

void lcdFlag(void);
/*************************************************************************************************************
* 											Function Implementation
************************************************************************************************************/
void APP_Init(void)
{
	
	/* Initialize used modules */
	HLCD_vidInit();
	KEYPAD_init();
	TSENSOR_Init(&st_g_TempSensor);
	BUZ_Init(&st_g_Buzzer);
	
	HLCD_vidCreatCustomChar(arr_g_bell, 1);
	
	/* Display welcome message for one second */
	HLCD_gotoXY(0, 4);
	HLCD_WriteString("Welcome!");
	TIM0_SyncDelay(1, Seconds);
	HLCD_ClrDisplay();
	
	/* Display Default Temperature */
	HLCD_WriteString(" Default temp:");
	HLCD_gotoXY(1, 7);
	HLCD_WriteInt(DEFAULT_TEMP);
	TIM0_SyncDelay(1, Seconds);
	HLCD_ClrDisplay();
	
	/* Get the required temperature */
	HLCD_WriteString("Pick temperature");
	TIM0_SyncDelay(500, mSeconds);

//	SET_BIT(SREG_REG,7);
	APP_adjustInit();
	
}

static void APP_adjustInit(void)
{
	HLCD_ClrDisplay();
	HLCD_WriteInt(MIN_TEMP);
	HLCD_gotoXY(0, 14);
	HLCD_WriteInt(MAX_TEMP);
	HLCD_gotoXY(0, 7);
	HLCD_WriteInt(u8_g_tempValue);
	HLCD_gotoXY(1, 0);
	HLCD_WriteString("||||||||||||||||");
	u8_g_CursorPosition = u8_g_tempValue - MIN_TEMP;
	HLCD_gotoXY(1, u8_g_CursorPosition);
	
}


void APP_Start(void)
{
	Uchar8_t u8_l_PressedKey;

	u8_l_PressedKey = GetButton();

	switch(u8_l_PressedKey)
	{
		case KEY_INCREAMENT:
		{
			if(!u8_g_setFlag)
			{
				if(u8_g_CursorPosition == 15) break;
				
				HLCD_gotoXY(0, 7);
				HLCD_WriteInt(++ u8_g_tempValue);
				HLCD_gotoXY(1, ++ u8_g_CursorPosition);
			}
			else
			{
				HLCD_ClrDisplay();
				HLCD_WriteString("This Operation");
				HLCD_gotoXY(1, 0);
				HLCD_WriteString("is not allowed!");
				TIM0_SyncDelay(500, mSeconds);

				HLCD_ClrDisplay();
			}
			break;
		}
		case KEY_DECREAMENT:
		{
			if(!u8_g_setFlag)
			{
				if(u8_g_CursorPosition == 0) break;
				
				HLCD_gotoXY(0, 7);
				HLCD_WriteInt(-- u8_g_tempValue);
				HLCD_gotoXY(1, -- u8_g_CursorPosition);
			}
			else
			{
				HLCD_ClrDisplay();
				HLCD_WriteString("This Operation");
				HLCD_gotoXY(1, 0);
				HLCD_WriteString("is not allowed!");
				TIM0_SyncDelay(500, mSeconds);

				HLCD_ClrDisplay();
			}
			break;
		}
		case KEY_SET:
		{
			if(!u8_g_setFlag)
			{
				u8_g_setFlag = 1;
				HLCD_vidWritecmd(HLCD_DISPLAY_ON_CURSOR_OFF);
				HLCD_ClrDisplay();
			}
			else
			{
				HLCD_ClrDisplay();
				HLCD_WriteString("This Operation");
				HLCD_gotoXY(1, 0);
				HLCD_WriteString("is not allowed!");
				TIM0_SyncDelay(500, mSeconds);

				HLCD_ClrDisplay();
			}
			break;
		}
		case KEY_ADJUST:
		{
			u8_g_setFlag = 0;
			BUZ_SetState(&st_g_Buzzer, BUZ_OFF);
			HLCD_vidWritecmd(HLCD_DISPLAY_ON_CURSOR_ON_NO_BLINK);
			APP_adjustInit();
			break;
		}
		case KEY_RESET:
		{
			u8_g_tempValue = DEFAULT_TEMP;
			break;
		}
	}
	

		lcdDelay = 1;
		TSENSOR_ReadValue(&st_g_TempSensor, &f32_l_CurrentTemp);
		//TIM0_AsyncDelay(500, mSeconds,lcdFlag);	

	
	if(f32_l_CurrentTemp > u8_g_tempValue && u8_g_setFlag)
	{
		HLCD_gotoXY(0,0);
		HLCD_vidWriteChar(1);
		HLCD_WriteString("Current temp ");
		HLCD_WriteInt(f32_l_CurrentTemp);
		BUZ_SetState(&st_g_Buzzer, BUZ_ON);
		
		HLCD_gotoXY(0,14);
		HLCD_WriteInt(f32_l_CurrentTemp);
	}
	else if(u8_g_setFlag)
	{
		BUZ_SetState(&st_g_Buzzer, BUZ_OFF);
		HLCD_gotoXY(0,0);
		HLCD_WriteString("Current temp: ");
		HLCD_WriteInt(f32_l_CurrentTemp);
	}
	
	
	
}


void lcdFlag(void)
{
	lcdDelay = 0;
}