/******************************************************************************
* @file: main.c
*
* @brief: This is the main file, its used to check the transmission speed of UART
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

/* MCAL include(s)... */
#include "MCAL_Cfg.h"
#include "../MCAL/inc/clocks.h"
#include "../MCAL/inc/UART.h"

/* Others include(s)... */
#include "derivative.h" /* include peripheral declarations SKEAZ128M4 */
#include "SYS_Handler.h"
#include "EEPROM_SIM.h"

/******************************************************************************
*							DATA TYPE DECLARATION
******************************************************************************/
typedef enum{
	STATE_INIT,
	STATE_RECEIVE,
	STATE_TRANSMIT,
	STATE_ERROR
}te_uartstate;

/******************************************************************************
*							MAIN Function DECLARATIONS
******************************************************************************/
int main(void)
{
  uint16_t v_indexaddress_u16 = 0U;
  uint8_t v_uartrxchar_u8 = 0xFF;
  uint8_t v_uarttxchar_u8 = 0xFF;
  const char v_errorMsg_char[] = "Error: Buffer Overflow\n";
  uint8_t u_errormsgindex_u8;

  SYS_Init();

  te_uartstate E_UARTSTATE_XXR = STATE_INIT;

  for(;;)
  {
	  switch(E_UARTSTATE_XXR)
	  {
	  case STATE_INIT:
		  v_indexaddress_u16 = 0U;
		  u_errormsgindex_u8 = 0U;
		  v_uartrxchar_u8 = 0xFF;
		  v_uarttxchar_u8 = 0xFF;
		  (void)EEPROM_SIM_ClearEEPROM();

		  E_UARTSTATE_XXR = STATE_RECEIVE;
		  break;
	  case STATE_RECEIVE:
		  v_uartrxchar_u8 = UART_GetChar(UART2);

		  if(v_indexaddress_u16==EEPROM_RAM_BUF_SIZE)
		  {
			  E_UARTSTATE_XXR = STATE_ERROR;
		  }
		  else
		  {
			  EEPROM_SIM_Write(v_indexaddress_u16,v_uartrxchar_u8);

			  v_indexaddress_u16++;

			  if(v_uartrxchar_u8 =='\0')
			  {
				  E_UARTSTATE_XXR = STATE_TRANSMIT;
				  v_indexaddress_u16 = 0U;
			  }
		  }
		  break;
	  case STATE_TRANSMIT:
		  if(v_indexaddress_u16==EEPROM_RAM_BUF_SIZE)
		  {
			  E_UARTSTATE_XXR = STATE_ERROR;
		  }
		  else
		  {
			  v_uarttxchar_u8 = EEPROM_SIM_Read(v_indexaddress_u16);
			  (void)UART_PutChar(UART2,v_uarttxchar_u8);
			  v_indexaddress_u16++;
			  if(v_uarttxchar_u8 =='\0')
			  {
				  E_UARTSTATE_XXR = STATE_INIT;
			  }
		  }
		  break;
	  case STATE_ERROR:
		  if(u_errormsgindex_u8<sizeof(v_errorMsg_char))
		  {
			  (void)UART_PutChar(UART2,v_errorMsg_char[u_errormsgindex_u8]);
			  u_errormsgindex_u8++;
		  }
		  else
		  {
			  u_errormsgindex_u8=0U;
			  E_UARTSTATE_XXR = STATE_INIT;
		  }
		  break;
	  }
  }
}

/******************************************************************************
*							EOF
******************************************************************************/
