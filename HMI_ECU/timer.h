/*
 * timer.h
 *
 *  Created on: Oct 25, 2024
 *      Author: farah
 */

#ifndef TIMER_H_
#define TIMER_H_

#include"std_types.h"

typedef enum
{
	Timer0,Timer1,Timer2
}Timer_ID_Type;

typedef enum
{
	NO_clockSource,CLK_1,CLK_8,CLK_64,CLK_256,CLK_1024,EXT_CLK_Falling_Edge,EXT_CLK_Rising_Edge
}Timer_ClockType;

typedef enum
{
	Timer_mode_Normal,Timer_mode_CTC
}Timer_ModeType;


typedef struct
{
uint16 timer_InitialValue;
uint16 timer_compare_MatchValue; /*it will be used in compare mode only*/
Timer_ID_Type timer_ID;
Timer_ClockType timer_clock;
Timer_ModeType timer_mode;
}Timer_ConfigType;

void Timer_init(const Timer_ConfigType * Config_Ptr);

void Timer_deInit(Timer_ID_Type timer_type);

void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID );

#endif /* TIMER_H_ */
