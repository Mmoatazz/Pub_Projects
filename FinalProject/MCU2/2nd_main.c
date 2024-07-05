
#include "EEPROM.h"
#include"USART.h"
#include"timer_0.h"
#include"motor.h"

#define ArraySize 5
#define M2_READY 0x10
#define OPEN_DOOR_KEY 0x40
#define DOOR_LOCKING  0x99
#define DOOR_UNLOCKING  0x98
#define DOOR_STOP   0x97
#define DOOR_OFF 0x96

uint8 password[ArraySize];
void delay_in_ms_x_100(uint8 x);

int main()
{
	SREG  |= (1<<7);           // Enable global interrupts in MC.
	Timer0_config_type Timer0_config = {NORMALMODE,F_CPU_1024,0,NORMAL};
	EEPROM_init();
	USART_config_type USART_CONFIG = {_8_bits,disabled,_1_bit,9600};
	UART_init(&USART_CONFIG);

	while(1)
	{
		for(int i=0;i<ArraySize;i++)
		{
			password[i]=UART_recieveByte();
			EEPROM_writeByte(((0x0000)|(i)),password[i]);
			_delay_ms(10);
		}
		while(UART_recieveByte() != M2_READY){} // wait until MC1 is ready
		UART_sendString("Confirmed$");


		while(Motor_OFF==0)
		{
			Timer0_clock_init(&Timer0_config);
			if(TIMER_0_OVF_int_software_flag==1)
			{
				//action for motor
				doorAction();
				TIMER_0_OVF_int_software_flag=0;
			}
			Timer0_deinit();
			Motor_OFF=1;
		}
		//			while(UART_recieveByte() != WHAT_NEXT){} // wait until MC1 is ready
		//			UART_sendString("+ Change Pass$");
		//ACTION FOR WRONG PASS
		//	for (i = 0; i < ArraySize; i++)
		//				{
		//
		//					if (password[i] != passwordconfirmation[i])
		//					{
		//						while(UART_recieveByte() != M2_READY){} // wait until MC1 is ready
		//								UART_sendString("ERROR$");
		//								count++;
		//								if(count==3)
		//								{
		//									//BUZZZER
		//								}
		//
		//					}
		//
		//
		//				}
	}
}
void delay_in_ms_x_100(uint8 x)
{
	uint8 i;
x=x*10;
	for (i=0; i<x; i++) _delay_ms(10);
}
