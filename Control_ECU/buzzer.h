/*
 * buzzer.h
 *
 *  Created on: Oct 7, 2024
 *      Author: farah
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include"gpio.h"

#define buzzer_port    PORTC_ID
#define buzzer_pin     PIN7_ID

void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);

#endif /* BUZZER_H_ */
