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

#ifndef INT_EEPROM_H_
#define INT_EEPROM_H_

#include <avr/io.h>
#include <util/delay.h>
#include "std_types.h"


/* ------------------------------------------------------------------------------------
 [Function Name] :eepromWriteByte
 [Description] :This function is responsible for Writting in the internal EEPROM.
 [Args] :
 [in] unsigned short a_addr:
 This Argshall indicate the address of the location to write in in the EEPROM
 [in] unsigned char a_data:
 This Argshall indicate a 1 byte data to be written in the EEPROM
 [Returns] : void
 ---------------------------------------------------------------------------------------------------------------*/
void eepromWriteByte(uint16 u16addr, uint8 u8data);

/* ---------------------------------------------------------------------------------------------------------------
 [Function Name] :eepromReadByte
 [Description] :This function is responsible for Reading 1 byte from internal EEPROM.
 [Args] :
 [in] unsigned short a_addr:
 This Argshall indicate the address of the location to Read in the EEPROM
 [Returns] :

 ---------------------------------------------------------------------------------------------------------------*/

void eepromReadByte(uint16 u16addr, uint8 *u8data);

#endif /* INT_EEPROM_H_ */
