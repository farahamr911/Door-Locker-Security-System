/*
 * pir_sensor.h
 *
 *  Created on: Oct 27, 2024
 *      Author: farah
 */

#ifndef PIR_SENSOR_H_
#define PIR_SENSOR_H_

#include"std_types.h"
#include"gpio.h"

void PIR_init(void);
uint8 PIR_getState(void);


#endif /* PIR_SENSOR_H_ */
