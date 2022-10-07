/******************************************************************************
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for dc motor
 *
 * Author: Ahmed Sobhy
 *
 * 26/1/2019
 *******************************************************************************/

#include "dc_motor.h"
#include <avr/io.h>

void DCMOTOR_Init()
{
	MOTOR_DIRECTION |= (1 << IN1); /* configure IN1 pin as output pin*/
	MOTOR_DIRECTION |= (1 << IN2); /* configure IN1 pin as output pin*/

	/*Motor is stop at the beginning*/
	MOTOR_OUTPUT &= ~((1 << IN1) | (1 << IN2));
}

void DCMOTOR_onClockWise()
{
	/* Direction of the DC Motor*/
	MOTOR_OUTPUT |= (1 << IN1);
	MOTOR_OUTPUT &= ~(1 << IN2);

}

void DCMOTOR_onAntiClockWise()
{
	/* Direction of the DC Motor*/
	MOTOR_OUTPUT &= ~(1 << IN1);
	MOTOR_OUTPUT |= (1 << IN2);

}

void DCMOTOR_stop()
{
	MOTOR_OUTPUT &= ~((1 << IN1) | (1 << IN2));
}
