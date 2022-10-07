 /******************************************************************************
 *
 * File Name: Final_Project_MC1.c
 *
 * Description: contain Header for Passward
 *
 * Author: Ahmed Sobhy
 *
 * 26/1/2019
 *******************************************************************************/

#ifndef PASSWORD_H_
#define PASSWORD_H_
#include "std_types.h"
#include "keypad.h"
#include "lcd.h"

void getPassword(uint8 array_passward[]);   //Take Passward from user

void prepareToSend(uint8 array[], uint8 array2[]);

#endif /* PASSWORD_H_ */
