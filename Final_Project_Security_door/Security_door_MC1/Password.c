 /******************************************************************************
 *
 * File Name: Final_Project_MC1.c
 *
 * Description: Source file for Passward
 *
 * Author: Ahmed Sobhy
 *
 * 26/1/2019
 *******************************************************************************/
#include "Password.h"
#include <util/delay.h>

void getPassword(uint8 array_passward[]) // function take passward from user
{
	sint8 i;
	uint8 key;
	for (i = 0; i < 5; i++)
	{
	  key = KeyPad_getPressedKey(); //function Key Oad from(driver Keypad).from file kepad.c

		 if ((key >= 0) && (key <= 9))
		{
			 array_passward[i] = key;
		}

		        _delay_ms(300); /* Press time */
				LCD_goToRowColumn(3,5+i); // to display password in middle lcd
	     		LCD_displayCharacter('*');

		  if (i == 4)
		{
			key = KeyPad_getPressedKey();
			if (key == 13)  /* ASCII of Enter */
			{
				break;
			}
			else
			{ /*  if Pressed to any PassWord else Enter not do every thing */
				LCD_displayCharacter(' ');
				    i--;
			}
		}

	}
}

/* This function to attach the # in end Password that meaning the end message to MC2
 understand that  */
void prepareToSend(uint8 array[], uint8 array_to_send[])
{
	sint8 i = 0;
	for (i = 0; i < 6; i++)
	{
		array_to_send[i] = array[i];
		if (i == 5)
		{
			array_to_send[i] = '#';
		}
	}
}
