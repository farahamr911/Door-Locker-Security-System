/*
 * main.c
 *
 *  Created on: Oct 28, 2024
 *      Author: farah
 */

#include"HMI_main.h"
#include"avr/io.h"

uint8 x=0;
uint8 y=0;
uint8 pass_array[5];
uint8 pass_check_array[5];
int g_tick=0;
uint8 mode;
uint8 Equality;

void call_back_func(void)
{
	 g_tick++;
}

void timer_delay(uint32 delay)
{
	Timer_init(&timer_config);
	Timer_setCallBack(call_back_func,Timer1 );
	while(g_tick!=delay);
	g_tick=0;
}

void check_pass(void)
{
	for(int i=0;i<5;i++)
	{
		if(pass_array[i]!=pass_check_array[i])
		{
			enter_pass();
		}
	}
	UART_sendByte(Control_READY);
	for(int i=0;i<5;i++)
	{
//		while(UART_recieveByte()!= Control_READY);
		UART_sendByte(pass_array[i]);
		_delay_ms(500);
	}

}


void enter_pass(void)
{
	LCD_moveCursor(0,0);
	LCD_displayString("plz enter pass: ");
	LCD_moveCursor(1,0);
	LCD_displayString("                      ");
	LCD_moveCursor(1,0);
	for(int i=0;i<5;i++)
	{
		_delay_ms(500);
		pass_array[i]=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
	}
	while((KEYPAD_getPressedKey())!=13)
	{
		_delay_ms(500);
	}
	LCD_moveCursor(0,0);
	LCD_displayString("plz re-enter the");
	LCD_moveCursor(1,0);
	LCD_displayString("same pass:");
	for(int i=0;i<5;i++)
	{
		_delay_ms(500);
		pass_check_array[i]=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
	}
	while((KEYPAD_getPressedKey())!=13)
	{
		_delay_ms(500);
	}
	check_pass();
}


void pass_send_controlECU(void)
{
	for(int i=0;i<5;i++)
	{
//		while(UART_recieveByte()!=Control_READY);
		UART_sendByte(pass_array[i]);
		_delay_ms(500);
	}
}

void pass_openDoor_changPass(void)
{
	LCD_moveCursor(0,0);
	LCD_displayString("Plz enter pass:   ");
	LCD_moveCursor(1,0);
	LCD_displayString("                    ");
	LCD_moveCursor(1,0);
	for(int i=0;i<5;i++)
	{
		_delay_ms(500);
		pass_array[i]=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
	}
	while((KEYPAD_getPressedKey())!=13)
	{
		_delay_ms(500);
	}
	pass_send_controlECU();
}


void main_mode(void)
{
	LCD_moveCursor(0,0);
	LCD_displayString("+ :Open Door       ");
	LCD_moveCursor(1,0);
	LCD_displayString("- :Change pass     ");
	_delay_ms(500);
    mode=KEYPAD_getPressedKey();
}

int main(void)
{
	SREG |=(1<<7);
	UART_init(&cofig_uart);
	LCD_init();
	Timer_init(&timer_config);
	Timer_setCallBack(call_back_func,Timer1 );


	enter_pass();
	LCD_moveCursor(0,0);
	LCD_displayString("+ :Open Door        ");
	LCD_moveCursor(1,0);
	LCD_displayString("- :Change pass    ");
	_delay_ms(500);
	mode=KEYPAD_getPressedKey();
	while(UART_recieveByte()!= Control_READY);

	while(1)
	{
		if(mode=='+')
		{
		if(x==0)
		{
			UART_sendByte(open_door);
			pass_openDoor_changPass();
		}
		x=0;
		Equality=UART_recieveByte();
		if((Equality==Equal)&&(mode=='+'))
		{
			UART_sendByte(HMI_READY);
			if(UART_recieveByte()==Door_is_Unlocking)
			{
				LCD_moveCursor(0,0);
				LCD_displayString("Door unlocking  ");
				LCD_moveCursor(1,0);
				LCD_displayString("Please Wait         ");
//				timer_delay(15);
				_delay_ms(15000);
//				while(g_tick < 15);
			}
			LCD_moveCursor(0,0);
			LCD_displayString("Wait for people");
			LCD_moveCursor(1,0);
			LCD_displayString("To Enter       ");

			while(UART_recieveByte()!=Door_is_locking);
			LCD_moveCursor(0,0);
			LCD_displayString("Door locking     ");
			LCD_moveCursor(1,0);
			LCD_displayString("Please Wait          ");
//			timer_delay(15);
		    _delay_ms(15000);
//		    while(g_tick < 15);
			main_mode();
		}

		else if(Equality==Not_Equal)
		{
			UART_sendByte(No_Error);
			pass_openDoor_changPass();
			Equality=UART_recieveByte();
			if(Equality==Not_Equal)
			{
				LCD_moveCursor(0,0);
				LCD_displayString("System LOCKED  ");
				LCD_moveCursor(1,0);
				LCD_displayString("wait for 1 min  ");

				UART_sendByte(Error);
				timer_delay(60);
//				_delay_ms(60000);
//				while(g_tick < 20){};
				x=1;
				main_mode();
				if(mode=='+')
				{
					UART_sendByte(open_door);
					pass_openDoor_changPass();
				}
			}
			}
		}
		else if(mode=='-')
			{
				if(y==0)
				{
					UART_sendByte(change_pass);
					pass_openDoor_changPass();
				}
                y=0;
				Equality=UART_recieveByte();
				if((Equality==Equal)&&(mode=='-'))
				{
					enter_pass();
					LCD_moveCursor(0,0);
					LCD_displayString("Pass Changed      ");
					LCD_moveCursor(1,0);
					LCD_displayString("                    ");
					main_mode();
				}
				else if(Equality==Not_Equal)
				{
					UART_sendByte(No_Error);
					pass_openDoor_changPass();
					Equality=UART_recieveByte();
					if(Equality==Not_Equal)
					{
						LCD_moveCursor(0,0);
						LCD_displayString("System LOCKED   ");
						LCD_moveCursor(1,0);
						LCD_displayString("wait for 1 min  ");

						UART_sendByte(Error);
						timer_delay(60);
//						_delay_ms(60000);
//						while(g_tick < 20){};
						y=1;
						main_mode();
						if(mode=='-')
						{
							UART_sendByte(change_pass);
							pass_openDoor_changPass();
						}
					 }
					}
			}

	}

	}

