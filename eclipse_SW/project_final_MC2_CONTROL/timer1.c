/**********************************************************************
 * Module: timer1
 *
 * File name: timer1.c
 *
 * description: source file for timer1 driver
 *
 * Author: Aya Ahmed Samir
 *
 ******************************************************************/

#include"timer1.h"
#include<avr/io.h>
#include<avr/interrupt.h>


/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
/***********************************************************************
                     * Function Definitions*
 **********************************************************************/

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr!=NULL_PTR)
	{
		(*g_callBackPtr)();

	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr!=NULL_PTR)
	{
		(*g_callBackPtr)();

	}
}




void Timer1_init(const Timer1_ConfigType* config_ptr)
{
	/* FOC1A are set high when a non-pwm mode*/
	TCCR1A =(1<<FOC1A);

	/* make the mode operation configurable wether normal or compare
	 * by configuration in WGM10,WGM11 in TCCR1A register
	 * and WGM12 in TCCR1B register
	 */
	TCCR1A=(TCCR1A & 0xFC)| ( (config_ptr->mode) & 0x03) ;
	TCCR1B=(TCCR1B & 0xE7)| ( ((config_ptr->mode) & 0x0C) << 1);

	/* make the prescalar configurable
	 * by configuration in bit CS10,CS11,CS12 in TCCR1B
	 */
	TCCR1B=(TCCR1B & 0xF8) |(config_ptr->prescalar);
	TCNT1= (config_ptr-> initial_value);

	/* to write in the compare register if it is compare mode*/
	if (config_ptr->mode==operation_CTC)
	{
		OCR1A= (config_ptr->compare_value);
		TIMSK|=(1<<OCIE1A);

	}
	else if(config_ptr->mode==operation_normal)
		TIMSK|=(1<<TOIE1);


}

void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr=a_ptr;
}

/*function to deInit the timer to use it again with another settings or
 * to stop the timer */
void Timer1_deInit(void)
{
	TCCR1A=0;
	TCCR1B=0;
	TCNT1=0;
	OCR1A=0;
	CLEAR_BIT(TIMSK,OCIE1A);
	CLEAR_BIT(TIMSK,TOIE1);

}
