/*
 *file name :buzzer.c
 *
 *description: source file for buzzer
 *
 *author:Aya Ahmed Samir
 */

#include"gpio.h"
#include"buzzer.h"
#include"common_header.h"

/*********************************************************************************
                               * Function definitions*
 ******************************************************************************/
void buzzer_init(void)
{
	GPIO_setUpPinDirection(BUZZER_PORT,BUZZER_PIN ,PIN_OUTPUT);
}

void Buzzer_On(void)
{
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH);
}

void Buzzer_Off(void)
{
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}
