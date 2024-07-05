/*
 ============================================================================
 Name        : Mini_Project_2
 Author      : Moataz Mokhtar
 Description : Motor with ADC and LCD modules project
 Date        : 2/15/2021
 ============================================================================
 */


#include "motor.h"
#include "timer_0.h"
#include "USART.h"

/*****************FUNCTIONS DEFINTIONS *****************/
uint8 volatile Motor_OFF=0;
uint8 static g_tick_motor=0;
uint8 static tick=0;

/*Motor configurations function*/
void motor_clockwise(void)
{
	SET_BIT(MOTOR_INPUT_PORT_DIRECTION,MOTOR_INPUT_1_BIT_PIN_2);
	SET_BIT(MOTOR_INPUT_PORT_DIRECTION,MOTOR_INPUT_2_BIT_PIN_7);

	/*input pins for the motor which are output pins for the mcu*/

	CLEAR_BIT(MOTOR_INPUT_PORT,MOTOR_INPUT_1_BIT_PIN_2);
	SET_BIT(MOTOR_INPUT_PORT,MOTOR_INPUT_2_BIT_PIN_7);
	SET_BIT(MOTOR_INPUT_PORT,PC7);
	/* Motor ROTATE CLOCKWISE  at the beginning */

}
void motor_anticlockwise(void)
{
	SET_BIT(MOTOR_INPUT_PORT_DIRECTION,MOTOR_INPUT_1_BIT_PIN_2);
	SET_BIT(MOTOR_INPUT_PORT_DIRECTION,MOTOR_INPUT_2_BIT_PIN_7);
	/*input pins for the motor which are output pins for the mcu*/

	SET_BIT(MOTOR_INPUT_PORT,MOTOR_INPUT_1_BIT_PIN_2);
	CLEAR_BIT(MOTOR_INPUT_PORT,MOTOR_INPUT_2_BIT_PIN_7);
	SET_BIT(MOTOR_INPUT_PORT,PC7);
	/* Motor ROTATE CLOCKWISE  at the beginning */

}
void motor_off(void)
{
	SET_BIT(MOTOR_INPUT_PORT_DIRECTION,MOTOR_INPUT_1_BIT_PIN_2);
	SET_BIT(MOTOR_INPUT_PORT_DIRECTION,MOTOR_INPUT_2_BIT_PIN_7);
	/*input pins for the motor which are output pins for the mcu*/

	CLEAR_BIT(MOTOR_INPUT_PORT,MOTOR_INPUT_1_BIT_PIN_2);
	CLEAR_BIT(MOTOR_INPUT_PORT,MOTOR_INPUT_2_BIT_PIN_7);
	CLEAR_BIT(MOTOR_INPUT_PORT,PC7);
	/* Motor ROTATE CLOCKWISE  at the beginning */

}
void doorAction(void)
{
	tick++;
	if(tick==NUMBER_OF_OVERFLOWS_PER_SECOND_F_CPU_CLOCK_1024)
	{
		g_tick_motor++;
		if(g_tick_motor==1)
		{
			while(UART_recieveByte() != DOOR_LOCKING){} // wait until MC1 is ready
			UART_sendString("Door is Locking$");
			motor_clockwise();
		}
		if(g_tick_motor==15)
		{
			while(UART_recieveByte() != DOOR_STOP){} // wait until MC1 is ready
			UART_sendString("Door Stopped$");
			motor_off();
		}
		if(g_tick_motor==18)
		{
			while(UART_recieveByte() != DOOR_UNLOCKING){} // wait until MC1 is ready
			UART_sendString("Door Unlocking$");
			motor_anticlockwise();
		}
		if(g_tick_motor==33)
		{
			while(UART_recieveByte() != DOOR_OFF){} // wait until MC1 is ready
			UART_sendString("Action Done$");
			motor_off();
			g_tick_motor=0;
			tick=0;
			Motor_OFF=1;
			Timer0_deinit();
		}
		tick=0;
	}

}

