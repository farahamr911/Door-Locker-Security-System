/*
 * Control_main.h
 *
 *  Created on: Oct 29, 2024
 *      Author: farah
 */

#ifndef CONTROL_MAIN_H_
#define CONTROL_MAIN_H_

#include "util/delay.h"
#include"buzzer.h"
#include"eeprom.h"
#include"motor.h"
#include"pir_sensor.h"
#include"uart.h"
#include"timer.h"
#include"avr/io.h"


//typedef uint8 State;

#define Control_READY      (uint8)1
#define HMI_READY          (uint8)2
#define open_door          (uint8)3
#define Door_is_Unlocking  (uint8)4
#define Wait_For_Pepole    (uint8)5
#define Door_is_locking    (uint8)6
#define Equal              (uint8)7
#define Not_Equal          (uint8)8
#define change_pass        (uint8)9
#define Error              (uint8)10
#define No_Error           (uint8)11

void call_back_func(void);
void timer_delay(uint32 delay);
void save_pass(void);
void temp_pass(void);
void check_pass (void);
void save_pass_eeprom(void);
void pass_wrong_error();



#endif /* CONTROL_MAIN_H_ */
