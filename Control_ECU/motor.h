/*
 * motor.h
 *
 *  Created on: Oct 7, 2024
 *      Author: farah
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"
#include "gpio.h"
typedef enum
{
	CW,A_CW,Stop
}DcMotor_State;

#define PORT_MOTOR_INIT1 PORTD_ID
#define PORT_MOTOR_INIT2 PORTD_ID

#define PIN_MOTOR_INIT1 PIN6_ID
#define PIN_MOTOR_INIT2 PIN7_ID


void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state, uint8 speed);


#endif /* MOTOR_H_ */
