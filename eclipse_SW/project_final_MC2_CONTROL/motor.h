/*******************************************************************************************
 * Module: DC motor
 * description: header file for DC motor drive
 * file name:motor.h
 * Author: Aya Ahmed Samir
 ******************************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_



#define PIN1_MOTOR_INPUT_ID          PIN0_NUM
#define PIN2_MOTOR_INPUT_ID          PIN1_NUM
#define PORT_MOTOR_INPUT             PORTB_ID


typedef enum
{
	STATE_CW, STATE_ACW, STATE_STOP
}DCMotor_State;

/***************************************************************************************
 *                         function prototypes
 *************************************************************************************/


/*description:
 * function responsible for initialize the DC motor
 */
void DcMotor_Init(void);

/* description:
 * function responsible to rotate the motor wether clock or anti-clock
 * and to control the speed of the motor by calling the PWM function
 */
void DcMotor_Rotate(DCMotor_State state,uint8 speed);



#endif /* MOTOR_H_ */
