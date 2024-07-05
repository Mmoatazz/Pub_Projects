/*
 ============================================================================
 Name        : Mini_Project_2
 Author      : Moataz Mokhtar
 Description : Motor with ADC and LCD modules project
 Date        : 2/15/2021
 ============================================================================
 */
#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*****************STATIC CONFIGURATIONS *****************/
#define MOTOR_INPUT_PORT_DIRECTION DDRC
#define MOTOR_INPUT_1_BIT_PIN_2 PC5
#define MOTOR_INPUT_2_BIT_PIN_7 PC6
#define MOTOR_INPUT_PORT PORTC
#define OPEN_DOOR_KEY 0x40
#define DOOR_LOCKING  0x99
#define DOOR_UNLOCKING  0x98
#define DOOR_STOP   0x97
#define DOOR_OFF 0x96

extern uint8 volatile Motor_OFF;
/*****************FUNCTION DECLRATIONS *****************/
void motor_off(void);
void motor_anticlockwise(void);
void motor_clockwise(void);
void doorAction(void);
#endif


