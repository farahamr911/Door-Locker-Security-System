/*
 * motor.c
 *
 *  Created on: Oct 7, 2024
 *      Author: farah
 */


#include "motor.h"
#include "gpio.h"
#include"pwm.h"

void DcMotor_Init(void)
{
	GPIO_setupPinDirection(PORT_MOTOR_INIT1, PIN_MOTOR_INIT1, PIN_OUTPUT);
	GPIO_setupPinDirection(PORT_MOTOR_INIT2, PIN_MOTOR_INIT2, PIN_OUTPUT);
	GPIO_writePin(PORT_MOTOR_INIT1, PIN_MOTOR_INIT1, 0);
	GPIO_writePin(PORT_MOTOR_INIT2, PIN_MOTOR_INIT2, 0);
}

void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{
	switch(state)
	{
	case CW: GPIO_writePin(PORT_MOTOR_INIT1, PIN_MOTOR_INIT1, 1);
	         GPIO_writePin(PORT_MOTOR_INIT2, PIN_MOTOR_INIT2, 0);
	         break;

	case A_CW: GPIO_writePin(PORT_MOTOR_INIT1, PIN_MOTOR_INIT1, 0);
               GPIO_writePin(PORT_MOTOR_INIT2, PIN_MOTOR_INIT2, 1);
               break;

	case Stop: GPIO_writePin(PORT_MOTOR_INIT1, PIN_MOTOR_INIT1, 0);
               GPIO_writePin(PORT_MOTOR_INIT2, PIN_MOTOR_INIT2, 0);
               break;
	}
	Timer0_PWM_Start(speed);
}
