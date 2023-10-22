/*****************************************************************************************
 * Module: DC motor
 * description: source file for DC motor drive
 * file name:motor.c
 * Author: Aya Ahmed Samir
 *****************************************************************************************/

#include"gpio.h"
#include"common_macros.h"
#include"motor.h"



/*************************************************************************
                      *function definitions *
 *************************************************************************/

void DcMotor_Init(void)
{
	/* to set up the two pins of the motor as ouTput pins*/
	GPIO_setUpPinDirection(PORT_MOTOR_INPUT,PIN1_MOTOR_INPUT_ID,PIN_OUTPUT);
	GPIO_setUpPinDirection(PORT_MOTOR_INPUT,PIN2_MOTOR_INPUT_ID,PIN_OUTPUT);

	/* to stop the motor at the start*/
	GPIO_writePin(PORT_MOTOR_INPUT,PIN1_MOTOR_INPUT_ID,LOGIC_LOW);
	GPIO_writePin(PORT_MOTOR_INPUT,PIN2_MOTOR_INPUT_ID,LOGIC_LOW);

}

void DcMotor_Rotate(DCMotor_State state,uint8 speed)
{
	PWM_Timer0_Start(speed);
	switch (state)
	{
	case STATE_CW:
		GPIO_writePin(PORT_MOTOR_INPUT,PIN1_MOTOR_INPUT_ID,LOGIC_HIGH);
		GPIO_writePin(PORT_MOTOR_INPUT,PIN2_MOTOR_INPUT_ID,LOGIC_LOW);
		break;
	case STATE_ACW:
		GPIO_writePin(PORT_MOTOR_INPUT,PIN1_MOTOR_INPUT_ID,LOGIC_LOW);
		GPIO_writePin(PORT_MOTOR_INPUT,PIN2_MOTOR_INPUT_ID,LOGIC_HIGH);
		break;
	case STATE_STOP:
		GPIO_writePin(PORT_MOTOR_INPUT,PIN1_MOTOR_INPUT_ID,LOGIC_LOW);
		GPIO_writePin(PORT_MOTOR_INPUT,PIN2_MOTOR_INPUT_ID,LOGIC_LOW);

	}

}

