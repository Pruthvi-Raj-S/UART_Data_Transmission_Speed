/******************************************************************************
* @file: MCAL_cfg.c
*
* @brief: Provides MCAL configurations APIs
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
#include "MCAL_Cfg.h"

/* MCAL include(s)... */

/* Others include(s)... */

/******************************************************************************
*							MACRO DEFINITION
******************************************************************************/


/******************************************************************************
*							INTERNAL VARIABLES
******************************************************************************/

/* structure initialization for UART2 */
UART_ConfigType UART2_Config =
{
	/* UART Control Register 1 settings */
	.sctrl1settings.byte=0x00,			/*!< byte field of union type*/
	.sctrl1settings.bits.bPt=0, 			/*!< Parity type 0:Even, 1:Odd*/
	.sctrl1settings.bits.bPe=0,				/*!< Parity enable 0:No H/W parity, 1:parity*/
	.sctrl1settings.bits.bIlt=0,			/*!< Idle Line Type Select, idle character bit starts after 0:start bit, 1:stop bit*/
	.sctrl1settings.bits.bWake=0,			/*!< Receiver Wakeup Method Select 0:idle, 1:address*/
	.sctrl1settings.bits.bM= UART_Mode8Bit,	/*!< 9-Bit or 8-Bit Mode Select*/
	.sctrl1settings.bits.bRsrc=0,    		/*!< Receiver Source Select depends on loop=1*/
	.sctrl1settings.bits.bUartswai=0,		/*!< UART run/Stops in Wait Mode 0:run, 1:stop*/
	.sctrl1settings.bits.bLoops=0,			/*!< Loop Mode Select 0:normal, 1:loop*/

	/* UART Control Register 2 settings */
	.sctrl2settings.byte=0x00,			/*!< byte field of union type */
	.sctrl2settings.bits.bSbk=0,	 	/*!< Send Break 0:normal, 1:queue break char*/
	.sctrl2settings.bits.bRwu=0,		/*!< Receiver Wakeup Control 0:normal, 1:wake-up*/
	.sctrl2settings.bits.bRe=1,			/*!< Receiver Enable*/
	.sctrl2settings.bits.bTe=1,			/*!< Transmitter Enable*/
	.sctrl2settings.bits.bIlie=0,		/*!< Idle Line Interrupt Enable for IDLE 0:disabled, 1:enabled*/
	.sctrl2settings.bits.bRie=0,    	/*!< Receiver Interrupt Enable for RDRF 0:disabled, 1:enabled*/
	.sctrl2settings.bits.bTcie=0,		/*!< Transmission Complete Interrupt Enable for TC 0:disabled, 1:enabled*/
	.sctrl2settings.bits.bTie=0,		/*!< Transmit Interrupt Enable for TDRE 0:disabled, 1:enabled*/

	/* UART Control Register 3 settings */
	.sctrl3settings.byte=0x00,			/*!< byte field of union type */
	.sctrl3settings.bits.bPeie=0,		/*!< Parity Error Interrupt Enable */
	.sctrl3settings.bits.bFeie=0,		/*!< Framing Error Interrupt Enable*/
	.sctrl3settings.bits.bNeie=0,		/*!< Noise Error Interrupt Enable*/
	.sctrl3settings.bits.bOrie=0,		/*!< Overrun Interrupt Enable*/
	.sctrl3settings.bits.bTxinv=0,		/*!< Transmit Data Inversion*/
	.sctrl3settings.bits.bTxdir=0, 		/*!< TxD Pin Direction in Single-Wire Mode*/

	.bSbns=0,							/*!< Stop Bit Number Select 0: One stop bit, 1: Two stop bit */
	.u32SysClkHz = UART_CLK,			/*!< system clock */
	.u32Baudrate = UART_BAUD_RATE		/*!< UART baudrate */
};

/******************************************************************************
*							EOF
******************************************************************************/