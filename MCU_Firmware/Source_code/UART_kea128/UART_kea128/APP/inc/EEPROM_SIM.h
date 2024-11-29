/******************************************************************************
* @file: EEPROM_SIM.h
*
* @brief: header file is used for simulating EEPROM using RAM Buffer
*
*
* @Author: Pruthvi Raj S
*
* @version: 0.1
* 			- Initial version
*
* @Created on: 27-Nov-2024:
******************************************************************************/

#ifndef INC_EEPROM_SIM_H_
#define INC_EEPROM_SIM_H_

/******************************************************************************
*							INCLUDES
******************************************************************************/
#include "derivative.h"

/******************************************************************************
*							MACRO DEFINITION
******************************************************************************/

#define EEPROM_RAM_BUF_SIZE 4096

/******************************************************************************
*							DATA TYPE DECLARATION
******************************************************************************/

/******************************************************************************
*							API DECLARATIONS
******************************************************************************/

/******************************************************************************
 * \fn  		void EEPROM_SIM_Init(void)
 * \brief
 *
 * \details
 *
 * \param       none
 * \return      none
 * \remarks     This function Initializes EEPROM SIM APPlication module
 ******************************************************************************/
void EEPROM_SIM_Init(void);

/******************************************************************************
 * \fn  		void EEPROM_SIM_Write(uint8_t* p_databuffer_u8, uint16_t v_index_u8)
 * \brief
 *
 * \details
 *
 * \param       v_arrayindex_u8 -> index of the data to be fetched from EEPROM
 * 				v_data_u8	-> Data to be written in EEPROM
 * \return      none
 * \remarks     This function Writes data from EEPROM
 ******************************************************************************/
void EEPROM_SIM_Write(uint16_t v_arrayindex_u8, uint8_t v_data_u8);

/******************************************************************************
 * \fn  		uint8_t EEPROM_SIM_Read(uint16_t v_arrayindex_u8)
 * \brief
 *
 * \details
 *
 * \param       v_arrayindex_u8 -> index of the data to be fetched from EEPROM
 * \return      uint8_t -> returns data from v_arrayindex_u8 in EEPROM
 * \remarks     This function Reads data from EEPROM
 ******************************************************************************/
uint8_t EEPROM_SIM_Read(uint16_t v_arrayindex_u8);

/******************************************************************************
 * \fn  		void EEPROM_SIM_ClearEEPROM(void)
 * \brief
 *
 * \details
 *
 * \param       none
 * \return      none
 * \remarks     This function Initializes EEPROM SIM APPlication module
 ******************************************************************************/
void EEPROM_SIM_ClearEEPROM(void);

#endif /* INC_EEPROM_SIM_H_ */
/******************************************************************************
*							EOF
******************************************************************************/
