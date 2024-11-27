/******************************************************************************
* @file: EEPROM_SIM.c
*
* @brief: provides APIs to simulating EEPROM using RAM Buffer
*
*
* @Author: Pruthvi Raj S
*
* @version: 0.1
* 			- Initial version
*
* @Created on: 27-Nov-2024:
******************************************************************************/

/******************************************************************************
*							INCLUDES
******************************************************************************/
/* My include(s)... */
#include "EEPROM_SIM.h"

/* Other include(s)... */
#include "derivative.h" /* include peripheral declarations SKEAZ128M4 */

/******************************************************************************
*							MACRO DEFINITION
******************************************************************************/

/******************************************************************************
*							USER DEFINED DATATYPES
******************************************************************************/

/******************************************************************************
*							INTERNAL VARIABLES
******************************************************************************/

/*Placeholder to store Data in RAM EEPROM*/
static uint8_t A_EEPROM_RAM_BUFF_U8[EEPROM_RAM_BUF_SIZE];

/*Placeholder to store */

/******************************************************************************
 *							API IMPLEMENTATION
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
void EEPROM_SIM_Init(void)
{
	/* Local variables and Initializations */
	uint16_t v_index_u16;

	for(v_index_u16=0;v_index_u16<EEPROM_RAM_BUF_SIZE;v_index_u16++)
	{
		A_EEPROM_RAM_BUFF_U8[v_index_u16]=0xFF;
	}
}

/******************************************************************************
 * \fn  		void EEPROM_SIM_Write(uint8_t* p_databuffer_u8, uint16_t v_index_u8)
 * \brief
 *
 * \details
 *
 * \param       p_databuffer_u8 -> Address of the EEPROM array
 * \return      none
 * \remarks     This function Initializes EEPROM SIM APPlication module
 ******************************************************************************/
void EEPROM_SIM_Write(uint16_t v_arrayindex_u8, uint8_t v_data_u8)
{

}

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
uint8_t EEPROM_SIM_Read(void)
{

}
/******************************************************************************
*							EOF
******************************************************************************/