/******************************************************************************
* @file: UART.c
*
* @brief: providing common UART API.
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
#include "UART.h"

/******************************************************************************
 *							API IMPLEMENTATION
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
void UART_Init(UART_MemMapPtr pUART, UART_ConfigType *pConfig)
{
    uint16_t u16Sbr;
    uint8_t u8Temp;
    uint32_t u32SysClk = pConfig->u32SysClkHz;
    uint32_t u32Baud = pConfig->u32Baudrate;

	/* Enable the clock to the selected UART */
    if (pUART == UART0_BASE_PTR)
	{
    	SIM_BASE_PTR->SCGC |= SIM_SCGC_UART0_MASK;
	}
    if (pUART == UART1_BASE_PTR)
   	{
       	SIM_BASE_PTR->SCGC |= SIM_SCGC_UART1_MASK;
   	}
    if (pUART == UART2_BASE_PTR)
    {
          	SIM_BASE_PTR->SCGC |= SIM_SCGC_UART2_MASK;
     }

    /* Make sure that the transmitter and receiver are disabled while we
     * change settings.
     */
    pUART->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );

    /* Configure the UART for 8-bit mode, no parity */
    pUART->C1 = pConfig->sctrl1settings.byte;

    /* Calculate baud settings */
    u16Sbr = (((u32SysClk)>>4) + (u32Baud>>1))/u32Baud;

    /* Save off the current value of the UARTx_BDH except for the SBR field */
    u8Temp = pUART->BDH & ~(UART_BDH_SBR_MASK);

    pUART->BDH = u8Temp |  UART_BDH_SBR(u16Sbr >> 8);
    pUART->BDL = (uint8_t)(u16Sbr & UART_BDL_SBR_MASK);

    if(1==pConfig->bSbns)
    {
    	UART_Set2StopBit(pUART);
    }
    else
    {
    	UART_Set1StopBit(pUART);

    }
    pUART->C3=pConfig->sctrl3settings.byte;
  	pUART->C2 =pConfig->sctrl2settings.byte;

  	/* UART2PS=0 (default);
  	 * UART2 Pin Selection Tx PTD7,Rx PTD6 */
    SIM_PINSEL1 &= ~SIM_PINSEL1_UART2PS_MASK;
}

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
uint8_t UART_GetChar(UART_MemMapPtr pUART)
{
    /* Wait until character has been received */
    while (!(pUART->S1 & UART_S1_RDRF_MASK));

    /* Return the 8-bit data from the receiver */
    return pUART->D;
}

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
void UART_PutChar(UART_MemMapPtr pUART, uint8_t u8Char)
{
	/* Wait for transmit buffer to be empty */
	while(!(pUART->S1 & UART_S1_TDRE_MASK));

	/* Send data */
	pUART->D=u8Char;
}

/******************************************************************************
*							EOF
******************************************************************************/
