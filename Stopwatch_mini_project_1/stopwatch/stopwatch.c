#include<avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
unsigned char timer_1_software_flag =0,INT0_software_flag =0,INT1_software_flag =0,INT2_software_flag =0; //flags for interrupt
unsigned char sec1tick=0,sec2tick=0, min1tick=0,min2tick=0,hr1tick=0,hr2tick=0; //global variables to count the time
unsigned char s1=0,s2=0, m1=0,m2=0,hr1=0,hr2=0;//global variables to display the time
void seven_segement_enable(unsigned char x); //function prototype to enable the segment to appear
void Timer_1_init()
{

	TCNT1=0;              // Intialize counter to 0x0000
	TCCR1A = (1<<FOC1A) ; //must be set for non- PWM mode
	TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10);
	/*
			 enable CHANNEL A for output compare match
			 select the mode:
			 CTC without Input capture unit
			 WGM13 =0 WGM12 (CTC1)= 1   WGM11 (PWM11) = 0  WGM10  (PWM10)= 0
			 select prescaler 1024
			 CS12 CS11 CS10 = 1 0 1 in TCCR1B
	 */
	TIMSK=(1<<OCIE1A); //Timer/Counter1, Output Compare A Match Interrupt Enable
	OCR1A=1000;
	/*
	  F_CPU = 1000000 , prescaler  = 1024
		F_Timer = F_CPU/ prescaler   == 976.56sec
		T_Timer = 1.024ms
		Set OCR1A ( compare A match) to value of 1000 to approximately count 1 sec
	Time to CTC = 1000*1.024 ms = 1 sec  --> approximately 1 inttrupt in 1 sec
	 */
	SREG |=(1<<7);//ENABLE GLOBAL INTRRUPT ENABLE BIT

}
void INT0_int(void)
{
	PORTD |=(1<<PD2); //Internal Pull up at pin 2 of port D.
	DDRD &=~(1<<PD2);//configure pin 2 in port D as input pin.
	GICR|=(1<<INT0); //General interrupt enable bit of INT0
	MCUCR |= (1<<ISC01); //Falling edge generates interrupt request.
	SREG |=(1<<7);//ENABLE GLOBAL INTRRUPT ENABLE BIT

}
void INT1_int(void)
{
	DDRD &= ~(1<<PD3);//configure pin 3  in port D as input pin.
	MCUCR |= (1<<ISC10) |(1<<ISC11); //Rising edge generates interrupt request.
	GICR |= (1<<INT1); // External Interrupt Request
	SREG |=(1<<7);//ENABLE GLOBAL INTRRUPT ENABLE BIT
}
void INT2_int(void)
{
	PORTB |=(1<<PB2); //Internal Pull up at pin 2 of port B.
	DDRB &=~(1<<PB2); //configure pin 2 in port B as input pin.
	GICR|=(1<<INT2);//General interrupt enable bit of INT2
	MCUCSR &= ~(1<<ISC2) ; //falling edge generates interrupt request.
	SREG |=(1<<7);//ENABLE GLOBAL INTRRUPT ENABLE BIT


}
ISR(TIMER1_COMPA_vect)

{
	timer_1_software_flag =1; //timer1 Int.Flag when the timer
};
ISR(INT0_vect)
{
	INT0_software_flag =1;//EXTERNAL INT0 Int.Flag when the button is pressed
}
ISR(INT1_vect)
{
	INT1_software_flag =1;//EXTERNAL INT1 Int.Flag when the button is pressed

}
ISR(INT2_vect)
{
	INT2_software_flag =1;//EXTERNAL INT2 Int.Flag when the button is pressed

}
int main(void)
{
	Timer_1_init();
	INT0_int();
	INT1_int();
	INT2_int();
	DDRA |=0x3F; //configure first 6 pins of port A as output pins.
	DDRC |= 0X0F;//configure the first 4 pins of port C as output pins.
	PORTC &= 0XF0; // Initialize first 4 pins of port C to 0.
	PORTA &= 0XC0; // Initialize first 6 pins of port A to 0.

	while (1)
	{
		//display numbers counted.
		s1=sec1tick;
		seven_segement_enable(1);
		s2=sec2tick;
		seven_segement_enable(2);
		m1=min1tick;
		seven_segement_enable(3);
		m2=min2tick;
		seven_segement_enable(4);
		hr1=hr1tick;
		seven_segement_enable(5);
		hr2=hr2tick;
		seven_segement_enable(6);

		if(INT0_software_flag ==1)
		{//reset the stopwatch
			TCNT1=0;
			sec1tick=0;
			seven_segement_enable(1);
			sec2tick=0;
			seven_segement_enable(2);
			min1tick=0;
			seven_segement_enable(3);
			min2tick=0;
			seven_segement_enable(4);
			hr1tick=0;
			seven_segement_enable(5);
			hr2tick=0;
			seven_segement_enable(6);
			INT0_software_flag =0;
		}
		else if(INT1_software_flag ==1)
		{//pause stopwatch
			TCCR1B &= ~(1<<CS12) & ~ (1<<CS10);
			INT1_software_flag =0;

		}
		else if(INT2_software_flag ==1)
		{//resume stopwatch
			TCCR1B |= (1<<CS12) | (1<<CS10);
			INT2_software_flag =0;
		}
		else
		{
			if(timer_1_software_flag ==1)
			{
				if((hr2tick==2)&&(hr1tick==3)&&(min2tick==5)&&(sec2tick==5) && (sec1tick==9) && (min1tick==9))
				{
					//check if the time is 23:59:59 then reset it to 00:00:00
					sec1tick=0;
					seven_segement_enable(1);
					sec2tick=0;
					seven_segement_enable(2);
					min1tick=0;
					seven_segement_enable(3);
					min2tick=0;
					seven_segement_enable(4);
					hr1tick=0;
					seven_segement_enable(5);
					hr2tick=0;
					seven_segement_enable(5);
				}
				else
				{
					if((hr1tick==9)&&(min2tick==5)&&(sec2tick==5) && (sec1tick==9) && (min1tick==9))
					{
						//check if the time is 09:59:59 then reset it to 10:00:00
						sec1tick=0;
						seven_segement_enable(1);
						sec2tick=0;
						seven_segement_enable(2);
						min1tick=0;
						seven_segement_enable(3);
						min2tick=0;
						seven_segement_enable(4);
						hr1tick=0;
						seven_segement_enable(5);
						hr2tick++;
						seven_segement_enable(5);

					}
					else
					{
						if((min2tick==5)&&(min1tick==9)&&(sec2tick==5) && (sec1tick==9))
						{
							//check if the time is 00:59:59 then reset it to 01:00:00
							sec1tick=0;
							seven_segement_enable(1);
							sec2tick=0;
							seven_segement_enable(2);
							min1tick=0;
							seven_segement_enable(3);
							min2tick=0;
							seven_segement_enable(4);
							hr1tick++;
							seven_segement_enable(5);


						}
						else
						{
							if((sec2tick==5) && (sec1tick==9) && (min1tick==9))
							{
								//check if the time is 00:09:59 then reset it to 00:10:00
								sec1tick=0;
								seven_segement_enable(1);
								sec2tick=0;
								seven_segement_enable(2);
								min1tick=0;
								seven_segement_enable(3);
								min2tick++;
								seven_segement_enable(4);
							}
							else
							{
								//check if the time is 00:00:59 then reset it to 00:01:00
								if((sec2tick==5) && (sec1tick==9) )
								{
									sec1tick=0;
									seven_segement_enable(1);
									sec2tick=0;
									seven_segement_enable(2);
									min1tick++;
									seven_segement_enable(3);
								}
								else
								{
									if(sec1tick==9)
									{
										//check if the time is 00:00:09 then reset it to 00:00:10
										sec1tick=0;
										seven_segement_enable(1);
										sec2tick++;
										seven_segement_enable(2);
									}
									else
									{
										sec1tick++;
										seven_segement_enable(1);
									}
								}
							}
						}
					}
				}
				timer_1_software_flag =0;
			}
		}
	}
}
void seven_segement_enable(unsigned char x)
{
	switch(x)
	{
	case 1: // FIRST SEGMENT ON
		PORTA = (1<<PA0);// 0x01;
		PORTC = (PORTC & 0xF0) | (s1 & 0x0F);
		_delay_ms(5);
		break;
	case 2:// SECOND SEGMENT ON
		PORTA = (1<<PA1);// 0x02;
		PORTC = (PORTC & 0xF0) | (s2 & 0x0F);
		_delay_ms(5);
		break;
	case 3 :// THIRD SEGMENT ON
		PORTA = (1<<PA2);// 0x04;
		PORTC = (PORTC & 0xF0) | (m1 & 0x0F);
		_delay_ms(5);
		break;
	case 4:// FOURTH SEGMENT ON
		PORTA = (1<<PA3);// 0x08;
		PORTC = (PORTC & 0xF0) | (m2 & 0x0F);
		_delay_ms(5);
		break;
	case 5 :// FIFTH SEGMENT ON
		PORTA = (1<<PA4);// 0x10;
		PORTC = (PORTC & 0xF0) | (hr1 & 0x0F);
		_delay_ms(5);
		break;
	case 6:// SIXTH SEGMENT ON
		PORTA = (1<<PA5);// 0x20;
		PORTC = (PORTC & 0xF0) | (hr2 & 0x0F);
		_delay_ms(5);
		break;
	}
}

