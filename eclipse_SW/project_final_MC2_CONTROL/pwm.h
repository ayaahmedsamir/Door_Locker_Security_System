/*
 *Module:PWM
 *description: header file for pulse width modulation to control speed of motor
 *file name: pwm.h
 *Author:Aya Ahmed
 */

#ifndef PWM_H_
#define PWM_H_

#include"common_header.h"

/***************************************************************************************
                           * Function prototype*
 ****************************************************************************************/


/* description:
 * function prototype to generate a specific PWM to control speed of motor*/
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
