/*
 * main.h
 *
 *  Created on: Oct 28, 2024
 *      Author: farah
 */

#ifndef MAIN_H_
#define MAIN_H_

#include"gpio.h"
#include"uart.h"
#include"timer.h"
#include"lcd.h"
#include"keypad.h"
#include "util/delay.h"
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

UART_ConfigType cofig_uart={BitDataType_8,
Disable_Parity,
StopBite_1bite,
9600};

Timer_ConfigType timer_config={0,
7813, /*it will be used in compare mode only*/
Timer1,
CLK_1024,
Timer_mode_CTC};


void call_back_func(void);
void timer_delay(uint32 delay);
void check_pass(void);
void enter_pass(void);
void pass_send_controlECU(void);
void pass_openDoor_changPass(void);


#endif /* MAIN_H_ */
