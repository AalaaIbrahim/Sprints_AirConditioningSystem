/*
 * keypad.h
 *
 * Created: 4/17/2023 4:06:37 AM
 *  Author: Sharpel
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_


/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/
#define R1     2
#define R2     3
#define R3     4
#define C1     5
#define C2     6
#define C3     7


#define KEYPAD_PORT PORTC
#define KEYPAD_DIR  DDRC
#define KEYPAD_PIN  PINC

/*************************************************************************************************************
 * 											User-defined data types
 ************************************************************************************************************/
typedef enum EN_KEYPAD_BTNS
{
	KEY_INCREAMENT=0,
	KEY_DECREAMENT,
	KEY_SET,
	KEY_ADJUST,
	KEY_RESET,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_NOTHING
	
	}EN_KEYPAD_BTNS;

/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/


/*************************************************************************************************************
 *
 Name : KEYPAD_init() 
 Description : This Function Initializes keypad pins (Rows are outputs & Columns are inputs).
 ARGS : void
 return : void   
 ************************************************************************************************************/

void KEYPAD_init(void);


/*************************************************************************************************************
 *
 Name : KEYPAD_GetButton 
 Description : This Function loops over other three functions (Checks (R1,R2,R3)).
 ARGS : void
 return : the pressed key or Nothing pressed   
 ************************************************************************************************************/

EN_KEYPAD_BTNS KEYPAD_GetButton(void);
/*************************************************************************************************************
 *
 Name : KEYPAD_checkR1 ,  KEYPAD_checkR2, KEYPAD_checkR3
 Description : functions are checking the entire row if it pressed or not.
 ARGS : void
 return : the pressed key or Nothing pressed   
 ************************************************************************************************************/

EN_KEYPAD_BTNS KEYPAD_checkR1(void);
EN_KEYPAD_BTNS KEYPAD_checkR2(void);
EN_KEYPAD_BTNS KEYPAD_checkR3(void);
#endif /* KEYPAD_H_ */








