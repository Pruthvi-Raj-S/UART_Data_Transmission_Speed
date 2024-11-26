/******************************************************************************
* @file: UART.h
*
* @brief: Header provide commond UART utilities.
*
*
* @Author: Pruthvi Raj S
*
* @version: 0.1
* 			- Initial version
*
* @Created on: 26-Nov-2024:
******************************************************************************/

#ifndef UART_H_
#define UART_H_

/******************************************************************************
* Includes
******************************************************************************/
#include "derivative.h"

/******************************************************************************
* Macros
******************************************************************************/

#define UART_0	UART0_BASE_PTR
#define UART_1	UART1_BASE_PTR
#define UART_2	UART2_BASE_PTR

/******************************************************************************
* Types
******************************************************************************/

/******************************************************************************
*define uart ctrl1 type
*
*//*! @addtogroup uart_ctrl1_type
* @{
*******************************************************************************/

/*!
* @brief UART setting type.
*
*/

typedef union
{
	uint8_t byte;  /*!< byte field of union type */
	struct{
		uint8_t bPt			:1; 	/*!< Parity type */
		uint8_t bPe 		:1;		/*!< Parity enable */
		uint8_t bIlt 		:1;		/*!< Idle Line Type Select*/
		uint8_t bWake 		:1;		/*!< Receiver Wakeup Method Select*/
		uint8_t bM			:1;		/*!< 9-Bit or 8-Bit Mode Select*/
		uint8_t bRsrc   	:1;    	/*!< Receiver Source Select*/
		uint8_t bUartswai	:1;		/*!< UART Stops in Wait Mode*/
		uint8_t bLoops		:1;		/*!< Loop Mode Select*/
	}bits;
} UART_Ctrl1Type, *UART_Ctrl1Ptr;
/*! @} End of uart_ctrl1_type */


/******************************************************************************
*define uart ctrl2 type
*
*//*! @addtogroup uart_ctrl2_type
* @{
*******************************************************************************/

/*!
* @brief UART setting type.
*
*/

typedef union
{
	uint8_t byte;  /*!< byte field of union type */
	struct{
		uint8_t bSbk		:1; 	/*!< Send Break */
		uint8_t bRwu 		:1;		/*!< Receiver Wakeup Control*/
		uint8_t bRe 		:1;		/*!< Receiver Enable*/
		uint8_t bTe 		:1;		/*!< Transmitter Enable*/
		uint8_t bIlie		:1;		/*!< Idle Line Interrupt Enable for IDLE*/
		uint8_t bRie   		:1;    	/*!< Receiver Interrupt Enable for RDRF*/
		uint8_t bTcie		:1;		/*!< Transmission Complete Interrupt Enable for TC*/
		uint8_t bTie		:1;		/*!< Transmit Interrupt Enable for TDRE*/
	}bits;
} UART_Ctrl2Type, *UART_Ctrl2Ptr;
/*! @} End of uart_ctrl2_type */


/******************************************************************************
*define uart ctrl3 type
*
*//*! @addtogroup uart_ctrl3_type
* @{
*******************************************************************************/

/*!
* @brief UART setting type.
*
*/

typedef union
{
	uint8_t byte;  /*!< byte field of union type */
	struct{
		uint8_t bPeie		:1; 	/*!< Parity Error Interrupt Enable */
		uint8_t bFeie 		:1;		/*!< Framing Error Interrupt Enable*/
		uint8_t bNeie 		:1;		/*!< Noise Error Interrupt Enable*/
		uint8_t bOrie		:1;		/*!< Overrun Interrupt Enable*/
		uint8_t bTxinv		:1;		/*!< Transmit Data Inversion*/
		uint8_t bTxdir   	:1; 	/*!< TxD Pin Direction in Single-Wire Mode*/
	}bits;
} UART_Ctrl3Type, *UART_Ctrl3Ptr;
/*! @} End of uart_ctrl3_type */


/******************************************************************************
*define uart config type
*
*//*! @addtogroup uart_config_type
* @{
******************************************************************************/
 /*!
 * @brief UART Configuration structure.
 *
 */
typedef struct
{
    UART_Ctrl1Type sctrl1settings;          /*!< UART Control 1 settings */
    UART_Ctrl2Type sctrl2settings;          /*!< UART Control 2 settings */
    UART_Ctrl3Type sctrl3settings;          /*!< UART Control 3 settings */
    uint8_t		   bSbns;					/*!< Stop Bit Number Select */
    uint32_t   	   u32SysClkHz;        		/*!< system clock */
    uint32_t       u32Baudrate;        		/*!< UART baudrate */
} UART_ConfigType,*UART_ConfigPtr;
/*! @} End of uart_config_type  */

/******************************************************************************
*define uart config baudrate type
*
*//*! @addtogroup uart_config_baudrate_type
* @{
******************************************************************************/
 /*!
 * @brief UART baudrate type structure.
 *
 */
typedef struct
{
    uint32_t    u32SysClkHz;        /*!< system clock */
    uint32_t    u32Baudrate;        /*!< UART baudrate */
} UART_ConfigBaudrateType;
/*! @} End of uart_config_baudrate_type */

/******************************************************************************
*define uart config mode type list
*
*//*! @addtogroup uart_mode_type_list
* @{
******************************************************************************/
typedef enum
{
    UART_Mode8Bit,                  /*!< 8 bit mode */
    UART_Mode9Bit,                  /*!< 9 bit mode */
    UART_ModeEnableLoopback,        /*!< enable looback mode */
    UART_ModeDisableLoopback,       /*!< disable loopback mode*/
    UART_ModeEnableSingleWire,      /*!< enable single wire mode */
    UART_ModeDisableSingleWire,     /*!< disable single wire mode */
} UART_ModeType;
/*! @} End of uart_mode_type_list   */

/******************************************************************************
*define uart interrupt type list
*
*//*! @addtogroup uart_interrupt_type_list
* @{
******************************************************************************/

typedef enum
{
    UART_TxBuffEmptyInt,            /*!< transmit buffer empty interrupt */
    UART_TxCompleteInt,             /*!< transmit complete interrupt */
    UART_RxBuffFullInt,             /*!< receive buffer full interrupt */

    UART_IdleLineInt,               /*!< idle line interrupt */

    UART_RxOverrunInt,              /*!< receive overrun interrupt */
    UART_NoiseErrorInt,             /*!< noise error interrupt */
    UART_FramingErrorInt,           /*!< framing error interrupt */
    UART_ParityErrorInt,            /*!< parity error interrupt */
} UART_InterruptType;
/*! @} End of uart_interrupt_type_list  */

/******************************************************************************
*define uart flag type list
*
*//*! @addtogroup uart_flag_type_list
* @{
******************************************************************************/
typedef enum
{
    UART_FlagPF = 0,        /*!< Parity error flag */
    UART_FlagFE,            /*!< Framing error flag */
    UART_FlagNF,            /*!< Noise flag */
    UART_FlagOR,            /*!< Receive overrun */
    UART_FlagIDLE,          /*!< Idle line flag */
    UART_FlagRDRF,          /*!< Receive data register full flag */
    UART_FlagTC,            /*!< Transmission complete flag */
    UART_FlagTDRE,          /*!< Transmit data register flag */

    UART_FlagRAF,           /*!< Receiver active flag */
    UART_FlagLBKDE,         /*!< LIN break detection enable */
    UART_FlagBRK13,         /*!< Break character generation length */
    UART_FlagRWUID,         /*!< Receive wake up idle detect */
    UART_FlagRXINV,         /*!< Receive data inversion */
    UART_FlagRev1,          /*!< Reserved */
    UART_FlagRXEDGIF,       /*!< RxD pin active edge interrupt flag */
    UART_FlagLBKDIF,        /*!< LIN break detect interrupt flag */
} UART_FlagType;
/*! @} End of uart_flag_type_list   */


/******************************************************************************
* Global functions declaration
******************************************************************************/
/******************************************************************************
 * \fn  		void UART_Init(UART_MemMapPtr pUART, UART_ConfigType *pConfig)
 * \brief
 *
 * \details
 *
 * \param[in] pUART       base of UART port
 * \param[in] pConfig     pointer to UART configuration structure
 *
 * \return      none
 * \remarks     This function initialize the UART
 ******************************************************************************/
void UART_Init(UART_MemMapPtr pUART, UART_ConfigType *pConfig);

/******************************************************************************
 * \fn  		uint8_t UART_GetChar(UART_MemMapPtr pUART)
 * \brief
 *
 * \details
 *
 * \param[in] pUART       base of UART port
 *
 * \return      uint8_t
 * \remarks     This function Receives a character in UART
 ******************************************************************************/
uint8_t UART_GetChar(UART_MemMapPtr pUART);

/******************************************************************************
 * \fn  		void UART_PutChar(UART_MemMapPtr pUART, uint8_t u8Char)
 * \brief
 *
 * \details
 *
 * \param[in] pUART       base of UART port
 * \param[in] u8Char      char to send
 *
 * \return      none
 * \remarks     This function sends a character in UART
 ******************************************************************************/
void UART_PutChar(UART_MemMapPtr pUART, uint8_t u8Char);

void init_UART(void);
void transmit_char(char);
void transmit_string(char* data_string);
char recieve_char(void);
void recieve_and_echo_char(void);

#endif /* UART_H_ */

/******************************************************************************
*							EOF
******************************************************************************/
