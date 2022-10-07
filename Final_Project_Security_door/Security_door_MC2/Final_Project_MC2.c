/******************************************************************************
 *
 * File Name: Final_Project_MC2.c
 *
 * Description: Source file for Final_Project_MC2
 *
 * Author: Ahmed Sobhy
 *
 * 26/1/2019
 *******************************************************************************/
#include "micro_config.h"

 /*  holds a value depends on the message recived
using UART from the MC1 , Modified in the ISR in uart_mc_2.c file */
volatile uint8 MC_2_recieved = 0;

/*holds the number of seconds counted by the Timer0, Modified in the ISR*/
volatile uint8 second = 0;

/*  holds the PassWord recived using UART from the MC1 ,
 * Modified in the ISR in uart_mc_2.c file */
volatile uint8 recived_new[6];  // holds the Password which store in external password
volatile uint8 recived_open[6]; // holds the Password which open the door
volatile uint8 recived_change[6]; // holds the New Password which changed by old

int main(void)
{
	/*---------------------- All Variables ----------------------------*/
	uint8 i=0; // holds the number in array from 0 to 6
	uint8 write; // holds the number by number PassWord to store it in eeprom
	uint8 Read_Pass[6]; // Read the pass which store in eeprom
	uint8 read; // holds the number by number PassWord to read it from eeprom

/*holds the return value of "strcmp" function when comparing the password to open the door*/
	uint8 compare_pass=0;

/*------------------------- Function initialisation---------------------  */
		UART_init();
		EEPROM_init();
		DCMOTOR_Init();
		SREG  |= (1<<7); //enable global interrupts in MC by setting the I-Bit.

		DDRB=0xFF; // Make PORTB output

  while(1)
   {
		/*-----------------Step 1 : store PassWord in External EEPROM--------------------*/

    if(MC_2_recieved==1) // NEW_PASSWORD
	{
    	MC_2_recieved = 0;
/* this loop put the password which take from user in another place(write) to put it number
    by number in eeprom    */
		while (recived_new[i] != '\0')
		{
		  write = recived_new[i];
		  EEPROM_writeByte(0x0A + i, write); // function if file external_eeprom.c
		  _delay_ms(50);
		   i++;
		}
	}

/*---------------------------- Step 2 : Open The Door -------------------------------*/

	else if (MC_2_recieved == 2) //OPEN_DOOR
	{
		MC_2_recieved = 0;
/* This loop to read the 5 number password which store it before and put it in array
 (Read_Pass) to compare it from Enter PassWord from user  */

	  for (i = 0; i < 5; i++)
   	    {
   		 EEPROM_readByte( 0x0A + i, &read);
   	 	 Read_Pass[i] = read;
   	    }
      Read_Pass[5] = '\0';
/* compare between the PassWord Enter from User(Pass) and the PassWord store before
in eeprom  (Read_Pass) */
      compare_pass = strcmp(recived_open, Read_Pass);
     if (compare_pass == 0)
      {
    	 /*Send Message to MC1 which recieved by ISR Usart in file usart_mc_1
    	  * This Meassage is Open the door */
		   UART_sendByte(CORRECT_PASSWORD);
    	   DCMOTOR_onClockWise();  // Run Motor to open the door
			 //  _delay_ms(2000);

				timer0_init_normal_mode();// delay for motor
				while (second != 3);
				second = 0;

			DCMOTOR_onAntiClockWise(); // closed door
			//    _delay_ms(2000);

				timer0_init_normal_mode();// delay for motor
				while (second != 3)	;
				second = 0;

				DCMOTOR_stop();
            }

			else
			{
/* Send Message to MC1 which recieved by ISR Usart in file usart_mc_1
  * This Meassage is Wrong PassWord and give him try again before send the alarm */
			UART_sendByte(WRONG_PASSWORD);
			DCMOTOR_stop();
			}
	}

/*-------------------------- Check The Password Change or not-------------------------- */

	else if (MC_2_recieved == 3)
	 {
		MC_2_recieved = 0;
/* This loop to read the 5 number password which store it before and put it in array
    (Read_Pass) to compare it from Enter PassWord from user  */
			 for (i = 0; i < 5; i++)
			   	    {
			   		 EEPROM_readByte( 0x0A + i, &read);
			   	 	 Read_Pass[i] = read;
			   	    }
			      Read_Pass[5] = '\0';
/* compare between the PassWord Enter from User(Pass) and the PassWord store before
   in eeprom (Read_Pass) */
			      compare_pass = strcmp(recived_change, Read_Pass);
			      if (compare_pass == 0)
    	  			{

			    	  UART_sendByte(PASSWORD_CHANGED);
    	  			}
   	  			else
    	  			{
	  	  			UART_sendByte(DONT_CHANGE);
    	  			}
	}

 /* ---------------------- Change PassWord --------------------------------------*/

   /* Repeat : Step 1 : store PassWord in External EEPRO */
	else if (MC_2_recieved == 4)
		 {
		MC_2_recieved = 0;
			uint8 i=0;
			while (recived_change[i] != '\0')
			{
			  write = recived_change[i];
			  EEPROM_writeByte(0x0A + i, write);
			  _delay_ms(50);
			  i++;
			}
		 }

    /* ------------------------Alarm ...Buzzer------------------------------ */

	else if (MC_2_recieved == 5)
		 {
			MC_2_recieved = 0;
			/* PB7 : Led On (alarm)
			 * PB5 : Buzzer work */
			PORTB |=( (1 << PB7) | (1 << PB5) );
			timer0_init_normal_mode();
			while (second != 10);
				second = 0;
			CLEAR_BIT(PORTB,7);

		 }

  }//While
}  // main
