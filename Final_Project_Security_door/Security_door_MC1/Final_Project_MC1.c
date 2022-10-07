 /******************************************************************************
 *
 * File Name: Final_Project_MC1.c
 *
 * Description: Source file for Final_Project_MC1
 *
 * Author: Ahmed Sobhy
 *
 * 27/1/2019
 *******************************************************************************/
#include "micro_config.h"

 /* holds a value depends on the message recived using UART from the MC2
    , Modified in the ISR in uart.c file */
volatile uint8 MC_1_recieved = 0;

/*holds the number of seconds counted by the Timer0, Modified in the ISR*/
volatile uint8 second = 0;

int main(void)
{
	/*---------------------- All Variables ----------------------------*/
	uint8 Pass_flag=0;/* This is flag if it 0 go (Step 1) else if 1 go (step 2) */
	uint8 value_pass; /*to read the value from External EEPROM 1 which menaning the
	                    PassWord is saved in EEPROM 2  */
	uint8 first_Pass[6]; /*holds The first time enter password to store in system*/
	uint8 confirm_Pass[6]; /*holds the  password which confirm it in system*/
	uint8 Pass[7]; /* holds the passWord to open the door before adding (#) */
	uint8 Pass_send[7]; /*holds pass to open the door which send to other micro
	                          after adding (#) */
	uint8 compare_Pass=0;/*holds the return value of "strcmp" function when comparing
	                       2 password in the first time */
	uint8 user_match;/*holds the user match between open the door(=)OR Change Password (+)*/
	uint8 message_flag = 0; /*like the flag if (1) go to The messages revieved from MC2*/
	uint8 wrong_Counter = 0; /* Count The password Entered wrong */

	/*------------------------- Function initialisation---------------------  */
	LCD_init();
	UART_init();
	SREG  |= (1<<7); //enable global interrupts in MC by setting the I-Bit.
    EEPROM_init();

/* --Read from internal eeprom from avr but don't work ..so I connect external eeprom */

/* Read from the Internal_eeprom_avr The address (0x0A) which contain the flag for
     password */
    /* eepromReadByte(0x0A,&value_pass); /* Read from Internal eeprom for avr ... Not Work*/

    EEPROM_readByte(0x0A,&value_pass); /* Read from external EEPROM  */

    if (value_pass != 0x03)
		{
			Pass_flag = 0; // Go step 1
		}
		else if (value_pass == 0x03)
		{
			Pass_flag = 1; // Go step 2
		}

  while (1)
	{
	 /* ----------------------------Step 1 ------------------------------------*/

	  if(Pass_flag == 0)
	  {
		 LCD_clearScreen();
		 LCD_displayStringRowColumn(0,0,"Enter Password");
/* The first time enter password to store in system	by Fucntion (getPassWord)
   which placed in file PassWord.c */
        getPassword(first_Pass);

        LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "ReEnter The pass");
		getPassword(confirm_Pass);//  enter password to confirm it in system

/* compare between the two password when user Enter it at first time*/
		compare_Pass = strcmp(first_Pass, confirm_Pass);
/* holds the return value of "strcmp" function when comparing 2 password in the first time*/
		  if (compare_Pass == 0)
		   {
/* Write in the Internal_eeprom_avr The address (0x0A) which contain the flag for password*/
/*  eepromWriteByte(0x0A, 0x03); /*Write in internal eeprom for avr */
			    EEPROM_writeByte(0x0A, 0x03); /* Write in external eeprom  */
				  _delay_ms(10);
  			    Pass_flag = 1;

			  LCD_clearScreen();
			  LCD_displayStringRowColumn(2,4," True ");
				_delay_ms(1000);
/*befor sending the PassWord to MC2 we need to attach the (#) in end message
   to MC2 understand the message is ended ..The (prepareToSend function) make that*/
		    prepareToSend(first_Pass, Pass_send);
/* before sending the message , The MC2 should you know it recieved message from MC1
 *  So, we sending this message (NEW_PASSWORD) to ready */
		    UART_sendByte(NEW_PASSWORD); /* defined in file usart_message.h */
			UART_sendString(Pass_send);  /* send Password after adding (#) */

       		}
			else
			{
					LCD_clearScreen();
					LCD_displayStringRowColumn(2,4," False ");
					_delay_ms(2000); /* 2 second display error  */
			}

	   }

/*---------------------------- Step 2 ----------------------------------------*/

	  else if (Pass_flag == 1) /*The Next step to open the door OR change Password */
	    {
		if (message_flag == 0) /*like the flag if (1)go to The messages revieved from MC2*/
			{
		             LCD_clearScreen();
		            LCD_displayStringRowColumn(0, 0, "= : Open Door   ");
			    	LCD_displayStringRowColumn(1, 0, "+ : Change pass");
			    	user_match = KeyPad_getPressedKey();

			    if (user_match == '=')  /* to open the door*/
			      {
			    	message_flag = 1;

			    	 LCD_clearScreen();
			    	 LCD_displayStringRowColumn(1,0,"Enter Password ");
			    	 getPassword(Pass);

			    	 prepareToSend( Pass , Pass_send);
			    	 UART_sendByte(OPEN_DOOR);
					 UART_sendString(Pass_send);  //second send
     		      }
			    else if (user_match == '+')  /* Change Password */
			   	 {
			    	message_flag = 1;
					 LCD_clearScreen();
					 LCD_displayStringRowColumn(1,0,"Current password");
					 getPassword(Pass);

					 prepareToSend( Pass , Pass_send);
					 UART_sendByte(CHANGE_PASSWORD);
					UART_sendString(Pass_send);  //Third send
			   	 }
		  	}

/* --------------------------------Messages from MC2----------------------------------- */

	 else if (message_flag == 1)
	  	{
		 if (MC_1_recieved == 1) /*message from MC2 (Door is Opening)..
		                           defined in file uart.c  in ISR For Usart Driver--  */
			{
			  MC_1_recieved = 0;

     		  LCD_clearScreen();
	  		  LCD_displayStringRowColumn(1, 0, "Door Is Opening");
	  		//	_delay_ms(3000);

	  					timer0_init_normal_mode(); /* display for 3 seconds */
	  					while (second < 3);
	  					second = 0;

	  		 LCD_clearScreen();
	  		 LCD_displayStringRowColumn(1, 0, "Door Is Closing");
	  			//_delay_ms(3000);

	  					timer0_init_normal_mode();
	  					while (second < 3);
	  					second = 0;
	  					message_flag = 0;
			}
//---------------------------------------------------------------------------
		else if (MC_1_recieved == 2) /* message from MC2 (Wrong Password) ..
		                               defined in file uart.c in ISR For Usart Driver*/
		{
		  MC_1_recieved = 0;
		  wrong_Counter++;
		  if (wrong_Counter == 3)
			{
	  		  UART_sendByte(ALARM); //send message to MC2 to On the alarm

			  LCD_clearScreen();
			  LCD_displayStringRowColumn(1, 0, "     ERROR      ");
			//	_delay_ms(2000);
			  timer0_init_normal_mode();
			  while (second != 10);
				second = 0;
			  wrong_Counter = 0;

			  message_flag = 0;

				continue;
			}

		  LCD_clearScreen();
		  LCD_displayStringRowColumn(1, 1, "Wrong password");
			_delay_ms(2000);
			message_flag = 0;
		}
	//------------------------------------------------------------------------
	  else if (MC_1_recieved == 3) /* message from MC2 (Change Password) ..
		                               defined in file uart.c in ISR For Usart Driver*/
	  	{
		/* -------------Repeat Step 1--------------*/
		  MC_1_recieved = 0;
	  	 LCD_clearScreen();
	  	LCD_displayStringRowColumn(0,0,"Enter Password");
	  	getPassword(first_Pass);
	  	LCD_clearScreen();

	  	LCD_displayStringRowColumn(0, 0, "ReEnter The pass");
	  	getPassword(confirm_Pass);

	  	compare_Pass = strcmp(first_Pass, confirm_Pass);

	  	if (compare_Pass == 0)
	  	  {
	  		//  eepromWriteByte(0x0A, 0x03);/* Write in the Internal_eeprom_avr */

	  		    EEPROM_writeByte(0x0A, 0x03);
	  		  _delay_ms(10);

	  		  Pass_flag = 1;

	  		  LCD_clearScreen();
	  		  LCD_displayStringRowColumn(2,0,"PassWord Changed");
	  		_delay_ms(1000);

	  		  prepareToSend( first_Pass, Pass_send);
	  		  UART_sendByte( CONFIRM_CHANGED);
	  		  UART_sendString(Pass_send);

				message_flag = 0;

	  	 }
	  	else
	  	{
	  		LCD_clearScreen();
	  		LCD_displayStringRowColumn(2,4," False ");
	  		_delay_ms(1000); /* 2 second display error  */
	  		LCD_clearScreen();
	  		  LCD_displayStringRowColumn(1,4,"PassWord");
	  		  LCD_displayStringRowColumn(2,3,"Not Change");
	  		_delay_ms(2000); /* 2 second display error  */

			message_flag = 0;
  	  	 }
	   }
  	}// message flag 1
  }// pass flag 1
 } // While
}//main

