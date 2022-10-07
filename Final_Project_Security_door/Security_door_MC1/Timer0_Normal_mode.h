/******************************************************************************
 *
 * File Name: TIMER0_NORMAL_MODE
 *
 * Description: Header file for Timer0 Normal Mode
 *
 * Author: Ahmed Sobhy
 *
 * 29/1/2019
 *******************************************************************************/


#ifndef TIMER0_NORMAL_H_
#define TIMER0_NORMAL_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

void timer0_init_normal_mode(void);

#endif /* TIMER0_NORMAL_H_ */
