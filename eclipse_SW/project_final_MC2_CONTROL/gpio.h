/******************************************
 * Module: GPIO
 * File name: gpio.h
 * description: Header file for AVR gpio driver
 * Author: Aya Ahmed
 *********************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "common_header.h"
#include"common_macros.h"


#define NUM_OF_PORTS   4
#define NUM_OF_PINS    8


#define PORTA_ID      0
#define PORTB_ID      1
#define PORTC_ID      2
#define PORTD_ID      3


#define PIN0_NUM      0
#define PIN1_NUM      1
#define PIN2_NUM      2
#define PIN3_NUM      3
#define PIN4_NUM      4
#define PIN5_NUM      5
#define PIN6_NUM      6
#define PIN7_NUM      7

#define PIN_INPUT     0
#define PIN_OUTPUT    1
#define PORT_INPUT    0
#define PORT_OUTPUT   1

/*************************************************************************
                      *function prototypes *
 *************************************************************************/

/* function prototype for set up pin direction I/O*/
void GPIO_setUpPinDirection(uint8 port_num, uint8 pin_num, uint8 direction);

/*function prototype for write on pin 1 or 0*/
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*function prototype to read the statues of pin 1 or 0*/
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/* function prototype for set up port direction I/O*/
void GPIO_setUpPortDirection(uint8 port_num, uint8 direction);

/*function prototype for write a required value on port */
void GPIO_writePort(uint8 port_num, uint8 value);

/*function prototype to read the statues of port*/
uint8 GPIO_readPort(uint8 port_num);

#endif /* GPIO_H_ */
