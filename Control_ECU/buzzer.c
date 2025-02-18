/*
 * buzzer.c
 *
 *  Created on: Oct 7, 2024
 *      Author: farah
 */

#include"buzzer.h"
#include"gpio.h"
//#include"lcd.h"

void Buzzer_init(void)
{
	GPIO_setupPinDirection(buzzer_port,buzzer_pin,PIN_OUTPUT);
	GPIO_writePin(buzzer_port,buzzer_pin,0);
}

void Buzzer_on(void)
{
	GPIO_writePin(buzzer_port,buzzer_pin,1);
}

void Buzzer_off(void)
{
	GPIO_writePin(buzzer_port,buzzer_pin,0);
}
