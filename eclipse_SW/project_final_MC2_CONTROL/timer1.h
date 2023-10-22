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

#define normal_mode    1
#define compare_mode   0

#define Timer1_Mode   normal_mode

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
	uint16 compare_value; //it will be used in compare mode only//
	Timer1_Prescalar prescalar;
	Timer1_operation mode;

}Timer1_ConfigType;


/***********************************************************************************
                              * Function Prototype*
 */
void Timer1_init(const Timer1_ConfigType* config_ptr);

void Timer1_setCallBack(void(*a_ptr)(void));

void Timer1_deInit(void);

#endif /* TIMER1_H_ */
