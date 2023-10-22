/****************************************************************************************
 *Module:PWM
 *description: source file for pulse width modulation to control speed of motor
 *file name: pwm.c
 *Author:Aya Ahmed
 *****************************************************************************************/
#include<avr/io.h>
#include"gpio.h"

/*************************************************************************
                      *function definitions *
 *************************************************************************/


void PWM_Timer0_Start(uint8 duty_cycle)
{
	/* to make PWM mode and non-inverting mode
	 *  and prescalar of 8
	 */
	TCCR0=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS01);
	TCNT0=0;

	OCR0= (uint8)(((uint16)(duty_cycle*255))/(100));
	GPIO_setUpPinDirection(PORTB_ID,PIN3_NUM,PIN_OUTPUT);

}


