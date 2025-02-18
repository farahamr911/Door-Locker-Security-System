/*
 * pir_sensor.c
 *
 *  Created on: Oct 27, 2024
 *      Author: farah
 */
#include"pir_sensor.h"


void PIR_init(void)
{
	GPIO_setupPinDirection(PORTC_ID, PIN7_ID, PIN_INPUT);
	GPIO_writePin(PORTC_ID, PIN7_ID, 0);
}

uint8 PIR_getState(void)
{
//	return GPIO_readPin(PORTC_ID, PIN7_ID);
	uint8 state;
	state=GPIO_readPin(PORTC_ID, PIN2_ID);
    return state;
}

