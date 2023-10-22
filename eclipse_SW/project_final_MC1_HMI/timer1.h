/*
 * Module: timer1
 *
 * File name: timer1.h
 *
 * description: Header file for timer1 driver
 *
 * Author: Aya Ahmed Samir
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include"common_macros.h"
#include"common_header.h"


typedef enum
{
	PRESCALAR_ZERO,PRESCALAR_1,PRESCALAR_8,PRESCALAR_64,PRESCALAR_256,PRESCALAR_1024

}Timer1_Prescalar;

typedef enum
{
	operation_normal,operation_CTC=4
}Timer1_operation;

typedef struct
{
	uint16 initial_value;
	uint16 compare_value;// used if compare mode//
	Timer1_Prescalar prescalar;
	Timer1_operation mode;

}Timer1_ConfigType;

/************************************************************************************************
                                  * Function Prototypes*
 ***********************************************************************************************/
/* description:
 * configurable function to initialize the timer with its settings
 * whether its mode or prescalar or the initial value or the compare vale if compare mode
 */
void Timer1_init(const Timer1_ConfigType* config_ptr);

/* description:
 * Function to call the call back function when an interrupt occurs
 */
void Timer1_setCallBack(void(*a_ptr)(void));
/* description:
 * Function to stop the timer , if it is needed to initialize it with diffrenet settings
 */
void Timer1_deInit(void);

#endif /* TIMER1_H_ */
