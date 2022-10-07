 /******************************************************************************
 *
 * File Name: Internal_eeprom_avr.c
 *
 * Description: Source file for Internal_eeprom_avr.c for MC1
 *
 * Author: Ahmed Sobhy
 *
 * 31/1/2019
 *******************************************************************************/

#include "Internal_eeprom_avr.h"

void eepromWriteByte(uint16 u16addr, uint8 u8data)
{

	/* Wait for completion of previous write */
	while (EECR & (1 << EEWE))
		;
	/* Set up address and data registers */
	EEAR = u16addr;
	EEDR = u8data;
	/* Write logical one to EEMWE */
	EECR |= (1 << EEMWE);
	/* Start EEPROM write by setting EEWE */
	EECR |= (1 << EEWE);
}

void eepromReadByte(uint16 u16addr, uint8 *u8data)
{
	/* Wait for completion of previous write */
	while (EECR & (1 << EEWE))
		;
	/* Set up address register */
	EEAR = u16addr;
	/* Start EEPROM read by writing EERE */
	EECR |= (1 << EERE);
	/* Return data from data register */
	 *u8data = EEDR ;
}
