/*********************************************************************
 * file name: MC1.c
 *
 * description: application for door security system
 *
 * Author: Aya Ahmed Samir
 *
 ********************************************************************/


/**********************************************************************************************
                                           * INCLUDES *
 **************************************************************************************************/
#include"gpio.h"
#include"motor.h"
#include"uart.h"
#include"timer1.h"
#include"motor.h"
#include"gpio.h"
#include"external_eeprom.h"
#include"twi.h"
#include<util/delay.h>
#include<avr/io.h>

/**********************************************************************************************
                                           * Definitions *
 **************************************************************************************************/

/* definitions for communication between MC1 and MC2*/
#define MC1_IsReady_Matched   0xFF /* To send the password to MC2 if two passwords are matched*/
#define MC1_check_password    0xFC /* To send the password to MC2 to check if it is the real pass*/
#define MC2_Checked           0xFF
#define MC2_READY             0x01 /* To make MC1 ready to send byte to MC2 and MC2 receive it at the same time*/
#define DOOR_OPEN             0x02 /* To send MC2 to open the door if password is correct*/
#define MC1_change_password   0x03 /* To send MC2 to change the password*/
#define Fire_Buzzer           0x04 /* To send to MC2 that the passwords dont match and operate the buzzer*/

/* common definitions*/
#define MATCHED                1
#define UNMATCHED              0
#define TRUE                   1
#define FALSE                  0
#define CORRECT                1
#define IN_CORRECT             0

/***********************************************************************************************
                                 * Global Varibales*
 ************************************************************************************************/

uint8 pass1[5]; // real password//
uint8 pass1_check[5];
uint8 str1_get[5];
uint8 pass_state;
uint8 check_pass1[5];
uint8 change_pass[5];
uint8 error_check=0;
uint8 g_tick;

/**************************************************************************************
	                            * Function definitions *
***************************************************************************************/

void UART_receivePass(void)
{
	uint8 i;
	for(i=0;i<5;i++)
	{
		/*to receive the password from MC1*/
		pass1[i] = UART_recieveByte();
		_delay_ms(50);
	}

	return;
}


/* To store password in the EEPROM*/
void Store_Password(void)
{
	uint8 i;
	uint8 byte;
	uint8 dummy;
	for(i=0;i<5;i++)
	{
		byte=pass1[i];		/* to store the password in EEPROM*/
		dummy=EEPROM_writeByte(0x0311+i,byte);
		_delay_ms(10);
	}
	return;
}

/*to get password from EEPROM and compare it */
void Get_Password (void)
{
	uint8 j;
	uint8 byte;
	uint8 dummy;

	for(j=0;j<5;j++)
		{
		/* read the password from EEPROM*/
		dummy=EEPROM_readByte(0x0311+j,&byte);
		pass1_check[j]=byte;
		_delay_ms(10);
		}
	return;
}

void Check_Pass_received(void)
{
	uint8 i;
	uint8 j;
	uint8 m;
	UART_sendByte(MC2_READY);
	for(i=0;i<5;i++)
	{
		check_pass1[i] = UART_recieveByte();
		_delay_ms(50);
			}
	Get_Password();
	for(j=0;j<5;j++)
	{
		if(check_pass1[j]==pass1_check[j])
			error_check=MATCHED;
		else
		{
			error_check=UNMATCHED;
			break;
		}

	}

	for(m=0;m<5;m++)
		{
	check_pass1[m]=0;
	pass1_check[m]=0;
		}
}

void change_password(void)
{
	uint8 i;
	UART_sendByte(MC2_READY);
	for(i=0;i<5;i++)
	{
		pass1[i] = UART_recieveByte();
		_delay_ms(50);
	}
	Store_Password();

}

void Timer1_processing(void)
{
	g_tick++;
}

void Door_Unlocking(void)
{
	Timer1_ConfigType config_type={0,62500,PRESCALAR_8,operation_CTC};
	Timer1_init(&config_type);
	Timer1_setCallBack(Timer1_processing);

	g_tick=0;
	DcMotor_Rotate(STATE_CW,100);
	while(g_tick<70){}

	g_tick=0;
	DcMotor_Rotate(STATE_STOP,0);
	while(g_tick<15){}

	g_tick=0;
	DcMotor_Rotate(STATE_ACW,100);
	while(g_tick<70){}

	DcMotor_Rotate(STATE_STOP,0);

	Timer1_deInit();
}


void Buzzer_operation(void)
{
	Timer1_ConfigType config_type={0,62500,PRESCALAR_8,operation_CTC};
	Timer1_init(&config_type);
	Timer1_setCallBack(Timer1_processing);
	g_tick=0;

	Buzzer_On();
	while(g_tick<240){}

	Buzzer_Off();
	Timer1_deInit();

}

/**********************************************************************************************
                                      *  MAIN *
 ***********************************************************************************************/
int main(void)
{

	uint8 check;
	uint8 choice;

/*to define the structure of the UART configurable and enable the UART*/
	UART_ConfigType Config_Type= {BITS_8,disabled_parity,BIT_1,9600};
	UART_init(&Config_Type);


/*to define the structure of the UART configurable and enable the UART*/
	TWI_ConfigType Config_TypeI2C= {1,400000};
	TWI_init(&Config_TypeI2C);

	DcMotor_Init();
	buzzer_init();
	SREG=(1<<7);

	while (UART_recieveByte()!=MC1_IsReady_Matched){}
	UART_receivePass();

	Store_Password();


	while(1)
	{
		UART_sendByte(MC2_READY);
		choice = UART_recieveByte();
		switch (choice)
		{
		case MC1_check_password:
		Check_Pass_received();

		if (error_check==MATCHED)
		{
			UART_sendByte(CORRECT);
		}
		else if(error_check==UNMATCHED)
		{
			UART_sendByte(IN_CORRECT);
		}
		break;

		case DOOR_OPEN:
			Door_Unlocking();
			break;

		case MC1_change_password:
			change_password();
			break;

		case Fire_Buzzer:
			Buzzer_operation();
			break;
		}

	}


}
