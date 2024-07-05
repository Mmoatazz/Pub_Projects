#include "Keypad.h"
#include "LCD.h"
#include"USART.h"

#define ArraySize 5
#define M2_READY 0x10
#define CHANGE_PASSWORD 43
#define OPEN_DOOR 45
#define OPEN_DOOR_KEY 0x40
#define DOOR_LOCKING  0x99
#define DOOR_UNLOCKING  0x98
#define DOOR_STOP   0x97
#define DOOR_OFF 0x96

uint8 password[ArraySize];
uint8 passwordconfirmation[ArraySize];
uint8 key;
uint8 key2;

void delay_in_ms_x_100(uint8 x);

uint8 passwordCompare(void);

int main()
{
	uint8 i;
	uint8 string[17];
	uint8 x=0,y=0,z=0,m=0,l=0,h=0;
	LCD_init();
	USART_config_type USART_CONFIG = {_8_bits,disabled,_1_bit,9600};
	UART_init(&USART_CONFIG);
	while(1)
	{
		if(x==0)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"New Password");
			LCD_goToRowColumn(1,0);
			for(i=0;i<ArraySize;i++)
			{
				key = KeyPad_getPressedKey(); /* get the pressed key number */
				if((key <= 9) && (key >= 0))
				{
					password[i]=key;
					LCD_displayCharacter('*');
				}
				delay_in_ms_x_100(5);
				//		_delay_ms(500);
			}
			delay_in_ms_x_100(5);
			//	_delay_ms(500);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Confirm Password");
			LCD_goToRowColumn(1,0);
			for(i=0;i<ArraySize;i++)
			{
				key2 = KeyPad_getPressedKey(); /* get the pressed key number */

				if((key2 <= 9) && (key2 >= 0))
				{passwordconfirmation[i]=key2;
				LCD_displayCharacter('*');
				UART_sendByte(passwordconfirmation[i]);
				}
				delay_in_ms_x_100(5);
				//		_delay_ms(500);
			}
			delay_in_ms_x_100(5);
			//	_delay_ms(500);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"C.H.E.C.K.I.N.G");
			delay_in_ms_x_100(20);
			//	_delay_ms(2000);

			while(passwordCompare()!=1)
			{
				if(passwordCompare()==1)
				{
					break;
				}
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Try again");
				LCD_displayStringRowColumn(1,0,"No match");
				delay_in_ms_x_100(20);
				//		_delay_ms(2000);
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Confirm password");
				LCD_goToRowColumn(1,0);
				for(i=0;i<ArraySize;i++)
				{
					key2 = KeyPad_getPressedKey(); /* get the pressed key number */

					if((key2 <= 9) && (key2 >= 0))
					{passwordconfirmation[i]=key2;
					LCD_displayCharacter('*');
					UART_sendByte(passwordconfirmation[i]);
					}
					delay_in_ms_x_100(5);
					//			_delay_ms(500);
				}
				delay_in_ms_x_100(5);
				//		_delay_ms(500);
			}
			LCD_clearScreen();
			UART_sendByte(M2_READY); // MC2 is ready
			UART_receivestring(string); // receive the string
			LCD_displayString(string); // display the string on LCD
			delay_in_ms_x_100(30);
			//	_delay_ms(3000);
			x=1;
		}

		else
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"+ Change Pass");
			LCD_displayStringRowColumn(1,0,"- Open Door");
			key2 = KeyPad_getPressedKey(); /* get the pressed key number */
			delay_in_ms_x_100(5);
			//		_delay_ms(500);
			if(key2==CHANGE_PASSWORD)
			{

				delay_in_ms_x_100(10);
				//			_delay_ms(1000);
				LCD_clearScreen();
				//			passwordToConfirmFlag= 0;
			}
			else if (key2==OPEN_DOOR)
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"You choose - ");
				delay_in_ms_x_100(5);
				//			_delay_ms(2000);
				UART_sendByte(DOOR_LOCKING); // MC2 is ready
				UART_receivestring(string); // receive the string
				LCD_clearScreen();
				LCD_displayString(string); // display the string on LCD
				delay_in_ms_x_100(150);
				//			_delay_ms(3000);
				//			_delay_ms(3000);
				//			_delay_ms(3000);
				//			_delay_ms(3000);
				//			_delay_ms(3000);
				UART_sendByte(DOOR_STOP); // MC2 is ready
				UART_receivestring(string); // receive the string
				LCD_clearScreen();
				LCD_displayString(string); // display the string on LCD
				delay_in_ms_x_100(30);
				UART_sendByte(DOOR_UNLOCKING); // MC2 is ready
				UART_receivestring(string); // receive the string
				LCD_clearScreen();
				LCD_displayString(string); // display the string on LCD
				delay_in_ms_x_100(150);
				//			_delay_ms(3000);
				//			_delay_ms(3000);
				//			_delay_ms(3000);
				//			_delay_ms(3000);
				//			_delay_ms(3000);

				UART_sendByte(DOOR_OFF); // MC2 is ready
				UART_receivestring(string); // receive the string
				LCD_clearScreen();
				LCD_displayString(string); // display the string on LCD
				delay_in_ms_x_100(20);
			}
		}
	}
}
uint8 passwordCompare(void)
{
	uint8 i=0;
	for (i = 0; i < ArraySize; i++)
	{
		if (password[i] != passwordconfirmation[i])
		{
			return 0;
		}
	}
	return 1;
}
void delay_in_ms_x_100(uint8 x)
{
	uint8 i;
	x=x*10;

	for (i=0; i<x; i++) _delay_ms(10);
}

