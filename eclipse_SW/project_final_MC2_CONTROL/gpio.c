/**************************
 * Module: GPIO
 * file name: gpio.c
 * description: source file for AVR GPIO driver
 * author: Aya Ahmed
 ***************************************/

#include"gpio.h"
#include<avr/io.h> /* to use the I/O ports registers*/
#include"common_macros.h"


/*************************************************************************
                      *function definitions *
 *************************************************************************/

/* description:
 * function to determine the direction of the pin wethere input or output
 * if the pin number or port number is not correct, the function will do nothing
 */
void GPIO_setUpPinDirection(uint8 port_num, uint8 pin_num, uint8 direction)
{
	/* to check if the number of port and number of pin is correct
	 * if not correct then the function will not handle the request
	 * if correct then switch on the port to setup the pin direction in each port
	 * */

	if ((port_num >= NUM_OF_PORTS ) | (pin_num>=NUM_OF_PINS) )
	{
		/* Do nothing */
	}
	else {

	/* to check for the port and pin number and setup the pin direction*/
	switch(port_num)
	{
	case PORTA_ID:
		if (direction == PIN_INPUT)
			CLEAR_BIT(DDRA,pin_num);
		else
			SET_BIT(DDRA,pin_num);
		break;
	case PORTB_ID:
			if (direction==PIN_INPUT)
				CLEAR_BIT(DDRB,pin_num);
			else
				SET_BIT(DDRB,pin_num);
			break;
	case PORTC_ID:
			if (direction==PIN_INPUT)
				CLEAR_BIT(DDRC,pin_num);
			else
				SET_BIT(DDRC,pin_num);
			break;
	case PORTD_ID:
			if (direction==PIN_INPUT)
				CLEAR_BIT(DDRD,pin_num);
			else
				SET_BIT(DDRD,pin_num);
			break;
	}
	}
}

/* description:
 * function to set pin or clear pin
 * if the pin number or port number is not correct, the function will do nothing
 */

void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	/* if the pin number or port number is not correct then the function will do nothing
	 */
	if ((port_num >= NUM_OF_PORTS ) | (pin_num>=NUM_OF_PINS) )
		{
			/* Do nothing */
		}
	else {


	/* switch on the port number to set the required pin in the required port */

	switch(port_num)
	{
	case PORTA_ID:
		if(value==LOGIC_HIGH)
			SET_BIT(PORTA,pin_num);
		else
			CLEAR_BIT(PORTA,pin_num);
		break;
	case PORTB_ID:
			if(value==LOGIC_HIGH)
				SET_BIT(PORTB,pin_num);
			else
				CLEAR_BIT(PORTB,pin_num);
			break;
	case PORTC_ID:
			if(value==LOGIC_HIGH)
				SET_BIT(PORTC,pin_num);
			else
				CLEAR_BIT(PORTC,pin_num);
			break;
	case PORTD_ID:
			if(value==LOGIC_HIGH)
				SET_BIT(PORTD,pin_num);
			else
				CLEAR_BIT(PORTD,pin_num);
			break;
	}
	}

}


/* description:
 * function to read the statues of the pin whether it is high or low
 * if the number of port of pin number is incorrect then the function return logic low
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	uint8 statues;

	/* if the number of port of pin number is incorrect so return logic low */
	if ((port_num >= NUM_OF_PORTS ) | (pin_num>=NUM_OF_PINS) )
	{
		statues=LOGIC_LOW;
	}
	else {


	/* read the required pin from the required port and return the statues
	 * of the pin whether 1 or 0 (SET OR CLEARED)
	 */
	switch(port_num)
	{
	case PORTA_ID:
		if (BIT_IS_SET(PINA,pin_num))
			statues=LOGIC_HIGH;
		else
			statues=LOGIC_LOW;
		break;
	case PORTB_ID:
			if (BIT_IS_SET(PINB,pin_num))
				statues=LOGIC_HIGH;
			else
				statues=LOGIC_LOW;
			break;
	case PORTC_ID:
			if (BIT_IS_SET(PINC,pin_num))
				statues=LOGIC_HIGH;
			else
				statues=LOGIC_LOW;
			break;
	case PORTD_ID:
			if (BIT_IS_SET(PIND,pin_num))
				statues=LOGIC_HIGH;
			else
				statues=LOGIC_LOW;
			break;

	}
	}
	return statues;

}

/* description:
 * function to determine the direction of the port wethere input or output
 * if the pin number or port number is not correct, the function will do nothing
 */
void GPIO_setUpPortDirection(uint8 port_num, uint8 direction)
{
	/*if the  port number is not correct, do nothing*/
	if ((port_num >= NUM_OF_PORTS ) )
	{
		/*do nothing*/
	}
	else {


/* switch on the port to get the required port then set the whole port as input or
 * output
 */
	switch(port_num)
	{
	case PORTA_ID:
		if(direction==PORT_INPUT)
			DDRA=0x00;
		else
			DDRA=0xFF;
		break;
	case PORTB_ID:
			if(direction==PORT_INPUT)
				DDRB=0x00;
			else
				DDRB=0xFF;
			break;
	case PORTC_ID:
				if(direction==PORT_INPUT)
					DDRC=0x00;
				else
					DDRC=0xFF;
				break;
	case PORTD_ID:
				if(direction==PORT_INPUT)
					DDRD=0x00;
				else
					DDRD=0xFF;
				break;
	}
	}
}

/* description:
 * function to write on port a required value
 * if the pin number or port number is not correct, the function will do nothing
 */
void GPIO_writePort(uint8 port_num, uint8 value)
{
	/*if the port number is not correct, the function will do nothing*/
	if ((port_num >= NUM_OF_PORTS ))
		{
			/*do nothing*/
		}

	else {
		/* find the required port then write on the port the required value*/
		switch(port_num){
		case PORTA_ID:
			PORTA=value;
			break;
		case PORTB_ID:
			PORTB=value;
			break;
		case PORTC_ID:
			PORTC=value;
			break;
		case PORTD_ID:
			PORTD=value;
			break;

		}

	}

}

/* description:
 * function to read the whole port and return it's value
 * if the port number or pin number is incorrect the function will return zero
 */
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 port_value;
	/*if the port number is not correct, the function will do nothing*/
		if ((port_num >= NUM_OF_PORTS ))
			{
			port_value=0;
			}
		else
		{
			switch(port_num)
			{
			case PORTA_ID:
				port_value=PINA;
				break;
			case PORTB_ID:
				port_value=PINB;
				break;
			case PORTC_ID:
				port_value=PINC;
				break;
			case PORTD_ID:
				port_value=PIND;
				break;

			}
		}
		return port_value;
}

