 /******************************************************************************
 *
 * Module: Micro - Configuration
 *
 * File Name: Micro_Config.h for MC2
 *
 * Description: File include all Microcontroller libraries
 *
 * Author: Ahmed Sobhy
 *
 *******************************************************************************/

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#ifndef F_CPU
#define F_CPU 1000000UL //1MHz Clock frequency
#endif  

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "std_types.h"
#include "common_macros.h"
#include "uart.h"
#include "usart_message.h"
#include "timer0_normal_mode.h"
#include "dc_motor.h"
#include "i2c.h"
#include "external_eeprom.h"



#endif /* MICRO_CONFIG_H_ */
