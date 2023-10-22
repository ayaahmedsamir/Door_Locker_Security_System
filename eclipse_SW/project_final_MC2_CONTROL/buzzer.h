/*
 * file name : buzzer.h
 *
 * description: Header file for buzzer
 *
 * author: Aya Ahmed Samir
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include"gpio.h"

#define BUZZER_PORT             PORTD_ID
#define BUZZER_PIN              PIN3_NUM


/**************************************************************************************
                               *  Function protoyypes*
 ***********************************************************************************/
void buzzer_init(void);

void Buzzer_On(void);

void Buzzer_Off(void);

#endif /* BUZZER_H_ */
