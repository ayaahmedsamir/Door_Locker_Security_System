/********************************************************************************************
 * file name: MC1.c
 *
 * description: application for door security system
 *
 * Author: Aya Ahmed Samir
 *
 *******************************************************************************************/

/**********************************************************************************************
                                           * INCLUDES *
 **************************************************************************************************/


#include"gpio.h"
#include"keypad.h"
#include"lcd.h"
#include"timer1.h"
#include"uart.h"
#include<util/delay.h>
#include<avr/io.h>

/**********************************************************************************************
                                           * Definitions *
 **************************************************************************************************/
/* definitions for communication between MC1 and MC2*/
#define MC1_IsReady_Matched   0xFF  /* To send the password to MC2 if two passwords are matched*/
#define MC1_check_password    0XFC  /* To send the password to MC2 to check if it is the real pass*/
#define MC2_Checked           0XFF
#define MC2_READY             0x01  /* To make MC1 ready to send byte to MC2 and MC2 receive it at the same time*/
#define DOOR_OPEN             0x02  /* To send MC2 to open the door if password is correct*/
#define MC1_change_password   0x03  /* To send MC2 to change the password*/
#define Fire_Buzzer           0x04  /* To send to MC2 that the passwords dont match and operate the buzzer*/

/* common definitions*/
#define UNMATCHED       0
#define MATCHED         1
#define TRUE                   1
#define FALSE                  0
#define CORRECT                1
#define IN_CORRECT             0
#define CLEAR                  1
#define ERROR                  0


/***********************************************************************************************
                                 * Global Varibales*
 ************************************************************************************************/
uint8 pass2[6]; /* array to store in it the re-enter password*/
uint8 pass1[6]; /* array to store in it the real password*/
uint8 Pass_Match;
uint8 pass_Enter[5]; /* array to store in it the new password*/
uint8 pass_change[5];
uint8 pass_change_new[5];
uint8 pass_change_new2[5];
uint8 check_pass1;
uint8 error_check;
uint8 g_tick; /* variable to check the no. of interrupt of timer*/

/**************************************************************************************
	                            * Function definitions *
***************************************************************************************/

/* description:
 * function to set the password at first and make the user enter it and then re-enter it to
 * check if they are matched or not
 */
void Set_Password(void)
{
	uint8 key1;
	uint8 key2;
	uint8 k;
	uint8 m;
	uint8 i;
	uint8 p;

	do {
		Pass_Match=MATCHED;
		LCD_clearScreen();
		LCD_displayString("plz Enter pass:");
		LCD_moveCursor(1,0);

		while(KEYPAD_getPressedKey()=='='){}
		for(k=0;k<5;k++) // To enter the password //
		{
		key1=KEYPAD_getPressedKey();
		pass1[k]=key1;
		LCD_intgerToString(key1);
		_delay_ms(500);
		}

		while(KEYPAD_getPressedKey()!='='){} // wait till the user enter the ENTER button//

		LCD_clearScreen();
		LCD_displayString("plz Re-Enter");
		LCD_moveCursor(1,1);
		LCD_displayString("pass:");

		while(KEYPAD_getPressedKey()=='='){}

		for(m=0;m<5;m++) // to Re-enter the password//
		{
			key2=KEYPAD_getPressedKey();
			pass2[m]=key2;
			LCD_intgerToString(key2);
			_delay_ms(500);
		}


		while(KEYPAD_getPressedKey()!='='){} // wait till the user enter the ENTER button//

		for(i=0;i<5;i++) // to check if the two passwords are matched or not//
		{
			if (pass1[i]!=pass2[i])
			{
				Pass_Match=UNMATCHED;
				break;
			}
		}

		if (Pass_Match==MATCHED)// if the two passwords are matched the send it to the EEPROM//
		{
			UART_sendByte(MC1_IsReady_Matched);
			for(p=0;p<5;p++)
			{
				UART_sendByte(pass1[p]);
				_delay_ms(50);
			}

		}

	} while (Pass_Match!=MATCHED); /* loop in the function till the two passwords are matched*/

}


/* description:
 * function to check if the entered password is correct or not
 * if the entered password is not correct for three consecutive times then a buzzer should operate
 * and display an ERROR message on the screen
 */
void read_password(void)
{
	uint8 i;
	uint8 password_state;
	uint8 error_count=0;
	uint8 key2;
	uint8 j;

	while(error_count<3)
	{
		LCD_clearScreen();
		LCD_displayString("plz Enter pass:");
		LCD_moveCursor(1,0);

		while(KEYPAD_getPressedKey()=='='){}
		for(i=0;i<5;i++) // To enter the password //
		{
			key2=KEYPAD_getPressedKey();
			pass_Enter[i]=key2;
			LCD_intgerToString(key2);
			_delay_ms(500);
		}

		while(UART_recieveByte()!=MC2_READY){}

		UART_sendByte(MC1_check_password);

		while(UART_recieveByte()!=MC2_READY){}

		for(j=0;j<5;j++)
		{
			UART_sendByte(pass_Enter[j]);
			_delay_ms(50);
		}

		_delay_ms(2000);

		password_state=UART_recieveByte(); /* receive the state of the password from MC2*/


	if (password_state==CORRECT)
	{
		error_check=CLEAR;
		return;
	}
	else if(password_state==IN_CORRECT)
	{
		error_check=ERROR;
		error_count++;
	}

	}


	while(UART_recieveByte()!=MC2_READY){} /* wait for MC2 to send a byte so that MC1 can send*/
	UART_sendByte(Fire_Buzzer);

	message_error();

}

/* description:
 * call back function for Timer1 when an interrupt occurs
 */
void Timer1_processing(void)
{
	g_tick++;
}

/* description:
 * function to display the error message on the screen
 */
void message_error(void)
{
	Timer1_ConfigType config_type={0,62500,PRESCALAR_8,operation_CTC};
	Timer1_init(&config_type);
	Timer1_setCallBack(Timer1_processing);
	g_tick=0;

	LCD_clearScreen();
	LCD_displayString("ERROR");
	while(g_tick<120){}

	LCD_clearScreen();
}

/* description:
 * Function to open the door if the password is matched to the real password entered at first
 * rotate the motor CW for 15 sec then stop the motor for 3 sec
 * then rotate the motor ACW for 15sec
 */
void Door_Choice(void)
{
	uint8 n;
	uint8 key;
	uint8 i;

	read_password();


	if(error_check==CLEAR)
	{
		LCD_clearScreen();

		while(UART_recieveByte()!=MC2_READY){}

		UART_sendByte(DOOR_OPEN);

		LCD_displayString("Door is unlocking");
		_delay_ms(15000);
		LCD_clearScreen();
		LCD_displayString("Motor off");
		_delay_ms(3000);
		LCD_clearScreen();
		LCD_displayString("Door is locking");
		_delay_ms(15000);

	}
	LCD_clearScreen();

	End_State();
}


/* description:
 * Function to change the password of the system if the entered password is correct
 * and matched to the real password entered at first
 */
void Change_Password_Choice(void)
{
	uint8 i;
	uint8 k;
	uint8 m;
	uint8 key4;
	uint8 key5;
	uint8 p;

	LCD_clearScreen();

	read_password();

	if(error_check==CLEAR)
	{
		do {
		Pass_Match=MATCHED;
		LCD_clearScreen();
		LCD_displayString("Enter new pass");
		LCD_moveCursor(1,0);


		while(KEYPAD_getPressedKey()=='='){}
		for(k=0;k<5;k++) // To enter the password //
		{
			key4=KEYPAD_getPressedKey();
			pass1[k]=key4;
			LCD_intgerToString(key4);
			_delay_ms(500);
		}

		while(KEYPAD_getPressedKey()!='='){} // wait till the user enter the ENTER button//

		LCD_clearScreen();
		LCD_displayString("plz Re-Enter");
		LCD_moveCursor(1,1);
		LCD_displayString("pass:");

		while(KEYPAD_getPressedKey()=='='){}

		for(m=0;m<5;m++) // to Re-enter the password//
		{
			key5=KEYPAD_getPressedKey();
			pass2[m]=key5;
			LCD_intgerToString(key5);
			_delay_ms(500);
		}


		while(KEYPAD_getPressedKey()!='='){} // wait till the user enter the ENTER button//

		for(i=0;i<5;i++) // to check if the two passwords are matched or not//
		{
			if (pass1[i]!=pass2[i])
			{
				Pass_Match=UNMATCHED;
				break;
			}
		}
		if (Pass_Match==MATCHED)// if the two passwords are matched the send it to the EEPROM//
		{
			while(UART_recieveByte()!=MC2_READY){}
			UART_sendByte(MC1_change_password);
			while(UART_recieveByte()!=MC2_READY){}
			for(p=0;p<5;p++)
			{
				UART_sendByte(pass1[p]);
				_delay_ms(50);
			}
		}

		} while(Pass_Match==UNMATCHED);
	}


}

void End_State(void)
{
	LCD_displayString("END!");
	while (1)
	{

	}
}

/**********************************************************************************************
                                      *  MAIN *
 ***********************************************************************************************/
int main(void)
{

	LCD_init(); /* to initialize LCD screen*/

	UART_ConfigType Config_Type={BITS_8,disabled_parity,BIT_1,9600};
	UART_init(&Config_Type); /* to initialize UART*/
	SREG=(1<<7);

	/* to call the function of the set password first*/
	Set_Password();



	while(1)
	{
		LCD_clearScreen();
		LCD_displayString("+ : open door");
		LCD_moveCursor(1,1);
		LCD_displayString("- : change password");

		while(KEYPAD_getPressedKey()!='+' && KEYPAD_getPressedKey()!='-'){}

		if(KEYPAD_getPressedKey()=='+')
		{
			Door_Choice();

	}
		else if (KEYPAD_getPressedKey()=='-')
		{
			Change_Password_Choice();
		}


	}

}

