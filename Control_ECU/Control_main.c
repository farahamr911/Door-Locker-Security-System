/*
 * Control_main.c
 *
 *  Created on: Oct 29, 2024
 *      Author: farah
 */
#include"Control_main.h"

#define  address   0x0311

int g_tick;
uint8 saved_pass_array[5];
uint8 temp_pass_array[5];
uint8 temp_eeprom_pass[5];
uint8 mode;
uint8 Equality;

Timer_ConfigType timer_config={0,
7813, /*it will be used in compare mode only*/
Timer1,
CLK_1024,
Timer_mode_CTC};

UART_ConfigType cofig_uart={BitDataType_8,
Disable_Parity,
StopBite_1bite,
9600};


void call_back_func(void){
	 g_tick++;
}

void timer_delay(uint32 delay)
{
	Timer_init(&timer_config);
	Timer_setCallBack(call_back_func,Timer1 );
	while(g_tick!=delay);
	g_tick=0;
}


void save_pass(void)
{

	for(int i=0;i<5;i++)
	{
//		UART_sendByte(Control_READY);
		saved_pass_array[i]=UART_recieveByte();
		_delay_ms(500);
	}
}


void temp_pass(void)
{

	for(int i=0;i<5;i++)
	{
//		UART_sendByte(Control_READY);
		temp_pass_array[i]=UART_recieveByte();
		_delay_ms(500);
	}
}


void check_pass (void)
{
	for(int i=0;i<5;i++)
	{
		EEPROM_readByte((address+i),&temp_eeprom_pass[i]);
		_delay_ms(10);
	}
	for(int i=0;i<5;i++)
	{
		if(temp_pass_array[i]!=temp_eeprom_pass[i])
		{
			Equality = Not_Equal;
//			while(UART_recieveByte()!=HMI_READY);
			UART_sendByte(Not_Equal);
			pass_wrong_error();
			return;
		}
	}
	Equality = Equal;
//	while(UART_recieveByte()!=HMI_READY);
	UART_sendByte(Equal);
}


void save_pass_eeprom(void)
{
	for(int i=0;i<5;i++)
	{
		EEPROM_writeByte((address+i), saved_pass_array[i]); /* Write saved_pass_array[i] in the external EEPROM */
		_delay_ms(10);
	}
}

void pass_wrong_error(void)
{
//	UART_sendByte(Control_READY);
	if (UART_recieveByte()==Error)
	{
		Buzzer_on();
		timer_delay(60);
//		_delay_ms(60000);
//		while(g_tick < 20);
		Buzzer_off();
	}
	else
	{
		temp_pass();
		check_pass();
	}
}

int main(void)
{
	SREG |=(1<<7);
	DcMotor_Init();
	PIR_init();
	UART_init(&cofig_uart);
	Timer_init(&timer_config);
	Timer_setCallBack(call_back_func,Timer1 );

//	UART_sendByte(Control_READY);
	while(UART_recieveByte()!= Control_READY);
	save_pass();
	save_pass_eeprom();
	UART_sendByte(Control_READY);
	while(1)
	{
//		UART_sendByte(Control_READY);
		mode=UART_recieveByte();
		if(mode==open_door)
		{
			temp_pass();
			check_pass();
			while(UART_recieveByte()!=HMI_READY);
			UART_sendByte(Door_is_Unlocking);
			DcMotor_Rotate(CW,100);
//			timer_delay(15);
			_delay_ms(15000);
//			while(g_tick < 15);

            DcMotor_Rotate(Stop,0);
            while(PIR_getState()){};

//            while(UART_recieveByte()!=HMI_READY);
    		  UART_sendByte(Door_is_locking);
    		  DcMotor_Rotate(A_CW,100);
    		  _delay_ms(15000);
//		      timer_delay(15);
//    		  while(g_tick < 15);
              DcMotor_Rotate(Stop,0);
			}

		else if(mode==change_pass)
		{
			temp_pass();
			check_pass();
			save_pass();
			save_pass_eeprom();
		}
	}
}
