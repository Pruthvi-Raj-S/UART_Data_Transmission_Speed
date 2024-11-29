/******************************************************************************
* @file: SYS_Handler.c
*
* @brief: Provides System Handling APIs
*
*
* @Author: Pruthvi Raj S
*
* @version: 0.1
* 			- Initial version
*
* @Created on: 26-Nov-2024:
******************************************************************************/


/******************************************************************************
*							INCLUDES
******************************************************************************/

/* My include(s)... */
#include "SYS_Handler.h"

/* MCAL include(s)... */
#include "MCAL_Cfg.h"
#include "uart.h"
#include "clocks.h"

/* Others include(s)... */
#include "EEPROM_SIM.h"

/******************************************************************************
 *							API IMPLEMENTATION
 ******************************************************************************/
/******************************************************************************
 * \fn  		void SYS_Init(void)
 * \brief
 *
 * \details
 *
 * \param       none
 * \return      none
 * \remarks     This function Initializes all the system module
 ******************************************************************************/
void SYS_Init(void)
{
	/*Initialize CLOCK module*/
	ICS_Init(&ICS_Config);

	/*Initialize UART2 module*/
	UART_Init(UART2, &UART2_Config);

	/*Initialize the EEPROM APP module*/
	EEPROM_SIM_Init();
}

/******************************************************************************
*							EOF
******************************************************************************/
