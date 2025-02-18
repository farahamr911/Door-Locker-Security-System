/*
 * timer.c
 *
 *  Created on: Oct 25, 2024
 *      Author: farah
 */


#include "timer.h"
#include "common_macros.h"
#include "avr/io.h" /* To use the UART Registers */
#include <avr/interrupt.h>


#define NULL_PTR ((void*)0)
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g0_callBackPtr)(void) = NULL_PTR;
static volatile void (*g1_callBackPtr)(void) = NULL_PTR;
static volatile void (*g2_callBackPtr)(void) = NULL_PTR;


ISR(TIMER0_OVF_vect)
{
	if(g0_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g0_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER0_COMP_vect)
{
	if(g0_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g0_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_OVF_vect)
{
	if(g1_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g1_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER2_OVF_vect)
{
	if(g2_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g2_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER2_COMP_vect)
{
	if(g2_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g2_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


void Timer_init(const Timer_ConfigType * Config_Ptr)
{
	switch (Config_Ptr->timer_ID)
	{
	case Timer0:
        TCNT0 = Config_Ptr->timer_InitialValue;

           if (Config_Ptr->timer_mode == Timer_mode_CTC)
           {
               TCCR0 = (1 << WGM01); // Set CTC mode
               OCR0 = Config_Ptr->timer_compare_MatchValue; // Set compare match value
               TIMSK |= (1 << OCIE0); // Enable CTC interrupt
           }
           else
           {
               TCCR0 = 0; // Normal mode
           }
           // Set prescaler
           TCCR0 |= Config_Ptr->timer_clock;
           break;

	case Timer1:
           TCNT1 = Config_Ptr->timer_InitialValue;
           if (Config_Ptr->timer_mode == Timer_mode_CTC)
           {
               TCCR1A = 0; // Normal operation
               TCCR1B = (1 << WGM12); // Set CTC mode
               OCR1A = Config_Ptr->timer_compare_MatchValue; // Set compare match value
               TIMSK |= (1 << OCIE1A); // Enable CTC interrupt
           }
           else
           {
               TCCR1A = 0; // Normal mode
           }
           TCCR1B |= Config_Ptr->timer_clock;
           break;

       case Timer2:
           TCNT2 = Config_Ptr->timer_InitialValue;
           if (Config_Ptr->timer_mode == Timer_mode_CTC) {
               TCCR2 = (1 << WGM21); // Set CTC mode
               OCR2 = Config_Ptr->timer_compare_MatchValue; // Set compare match value
               TIMSK |= (1 << OCIE2); // Enable CTC interrupt
           }
           else
           {
               TCCR2 = 0; // Normal mode
           }
           TCCR2 |= Config_Ptr->timer_clock;
           break;
	}
}


void Timer_deInit(Timer_ID_Type timer_type)
{
	switch(timer_type)
	{
	//enable clock by setting CS10:2=000
	case Timer0:
	       TCCR0 &=~((1<<CS10)|(1<<CS11)|(1<<CS12));
	       break;

	case Timer1:
	       TCCR1B &=~((1<<CS10)|(1<<CS11)|(1<<CS12));
	       break;

	   case Timer2:
	       TCCR2 &=~((1<<CS10)|(1<<CS11)|(1<<CS12));
	       break;
	}
}

void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID )
{
	switch(a_timer_ID)
	{
	case Timer0:
		g0_callBackPtr = a_ptr;
	       break;

	case Timer1:
		g1_callBackPtr = a_ptr;
	       break;

	   case Timer2:
			g2_callBackPtr = a_ptr;
	       break;
	}
}

