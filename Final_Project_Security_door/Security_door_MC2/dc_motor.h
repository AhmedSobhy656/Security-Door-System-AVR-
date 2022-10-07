/******************************************************************************
 *
 * File Name: dc_motor.h
 *
 * Description: header file for dc motor
 *
 * Author: Ahmed Sobhy
 *
 * 26/1/2019
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "micro_config.h"

#define MOTOR_DIRECTION DDRA
#define MOTOR_OUTPUT PORTA
#define IN1 PA1
#define IN2 PA2
void DCMOTOR_Init();
void DCMOTOR_onClockWise();
void DCMOTOR_onAntiClockWise();
void DCMOTOR_stop();

#endif /* DCMOTOR_H_ */
