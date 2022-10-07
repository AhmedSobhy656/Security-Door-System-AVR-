 /******************************************************************************
 *
 * File Name: Usart Message .h
 *
 * Description: header file for Usart Message_MC1
 * to communicate (send/recieve messages between two micro )
 * Author: Ahmed Sobhy
 *
 * 29/1/2019
 *******************************************************************************/

#ifndef UART_MESSAGES_H_
#define UART_MESSAGES_H_

#define NEW_PASSWORD     0x01
#define OPEN_DOOR        0x02
#define CHANGE_PASSWORD  0x03
#define PASSWORD_CHANGED 0x04
#define DOOR_IS_OPENING  0x05
#define WRONG_PASSWORD   0x06
#define DOOR_IS_CLOSED   0x07
#define CONFIRM_CHANGED  0x08
#define CORRECT_PASSWORD 0x09
#define DONT_CHANGE      0X10
#define ALARM      0X11


#endif /* UART_MESSAGES_H_ */
