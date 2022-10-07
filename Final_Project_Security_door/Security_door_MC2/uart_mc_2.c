 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver & ISR(USART_RXC_vect)
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#include "uart.h"
#include "Usart_message.h"

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)


extern volatile uint8 MC_2_recieved;  /*The Message will be come from MC1 */
extern volatile uint8 recived_new[6];
extern volatile uint8 recived_open[6];
extern volatile uint8 recived_change[6];

void UART_init(void)
{
	UCSRA = (1 << U2X); /* U2X = 1 for double transmission speed */
	/************************** UCSRB Description **************************
	 * RXCIE = 1 Enable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
		UBRRH = BAUD_PRESCALE>>8;
		UBRRL = BAUD_PRESCALE;
}

void UART_sendByte(const uint8 data) {
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for 
	 * transmitting a new byte so wait until this flag is set to one */
	while (BIT_IS_CLEAR(UCSRA, UDRE)) {
	}
	/* Put the required data in the UDR register and it also clear the UDRE flag as 
	 * the UDR register is not empty now */
	UDR = data;
	/************************* Another Method *************************
	 UDR = data;
 while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transimission is complete TXC = 1
	 SET_BIT(UCSRA,TXC); // Clear the TXC flag
	 *******************************************************************/
}

uint8 UART_recieveByte(void) {
	/* RXC flag is set when the UART receive data so wait until this 
	 * flag is set to one */
	while (BIT_IS_CLEAR(UCSRA, RXC)) {
	}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag 
	 will be cleared after read this data */
	return UDR;
}

void UART_sendString(const uint8 *Str) {
	uint8 i = 0;
	while (Str[i] != '\0') {
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	 while(*Str != '\0')
	 {
	 UART_sendByte(*Str);
	 Str++;
	 }
	 *******************************************************************/
}

void UART_receiveString(uint8 *Str) {
	uint8 i = 0;
	Str[i] = UART_recieveByte();
	while (Str[i] != '#') {
		i++;
		Str[i] = UART_recieveByte();
	}
	Str[i] = '\0';
}

/*------------------ ISR For Usart Driver-------------------------------------  */

ISR(USART_RXC_vect)
{
	uint8 message = UART_recieveByte();  /*Recieve message  from MC1*/
	if (message == NEW_PASSWORD)
	{
		MC_2_recieved = 1;
		UART_receiveString(recived_new); /*The first PassWord come from user*/
	}
	else if (message == OPEN_DOOR)
	{
		MC_2_recieved = 2;
	UART_receiveString(recived_open);/*The PassWord come from user to open the door*/

	}
	else if(message == CHANGE_PASSWORD) //this step to enter current  pass to change pass
	{
		MC_2_recieved = 3;
		UART_receiveString(recived_change);// The PassWord come from user to change

	}
	else if(message ==  CONFIRM_CHANGED)
	{
		MC_2_recieved = 4;
		UART_receiveString(recived_change);

	}
	else if(message ==  ALARM)
		{
			MC_2_recieved = 5;
		}

}
