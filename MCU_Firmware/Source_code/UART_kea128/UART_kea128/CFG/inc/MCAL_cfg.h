/******************************************************************************
* @file: MCAL_cfg.h
*
* @brief: This header file shall be storing MCAL configurations
*
*
* @Author: Pruthvi Raj S
*
* @version: 0.1
* 			- Initial version
*
* @Created on: 26-Nov-2024:
******************************************************************************/

#ifndef INC_MCAL_CFG_H_
#define INC_MCAL_CFG_H_

/******************************************************************************
*							INCLUDES
******************************************************************************/
#include "derivative.h"

/* Other include(s)... */
#include "uart.h"
#include "clocks.h"

/******************************************************************************
*							MACRO DEFINITION
******************************************************************************/
/*!!! Microcontroller Bus clock 20MHz*/
#define BUS_CLK		20000000U

/*Clock source for UART*/
#define UART_CLK		BUS_CLK

/*Baud rate for UART*/
#define UART_BAUD_RATE  2400U

/******************************************************************************
*							EXTERN DECLARATIONS
******************************************************************************/
extern ICS_ConfigType ICS_Config;
extern UART_ConfigType UART2_Config;

#endif /* INC_MCAL_CFG_H_ */

/******************************************************************************
*							EOF
******************************************************************************/
