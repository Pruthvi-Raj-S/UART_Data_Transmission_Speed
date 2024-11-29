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
*							MAIN Function
******************************************************************************/
int main(void)
{
	/* Local variables, Initializations and declarations*/
	uint16_t v_indexaddress_u16;
	uint8_t v_uartrxchar_u8;
	uint8_t v_uarttxchar_u8;
	const char v_errorMsg_char[] = "Error: Buffer Overflow\n";
	uint8_t u_errormsgindex_u8;

	/*Initializing all the System modules*/
	SYS_Init();

	/*Initializing the UART State*/
	te_uartstate E_UARTSTATE_XXR = STATE_INIT;

	/*Forever loop to run the code*/
	for(;;)
	{
	  /**/
	  switch(E_UARTSTATE_XXR)
	  {
	  case STATE_INIT:
		  /*This State will Initialize/clear all the values to default*/
		  v_indexaddress_u16 = 0U;
		  u_errormsgindex_u8 = 0U;
		  v_uartrxchar_u8 = 0xFF;
		  v_uarttxchar_u8 = 0xFF;
		  (void)EEPROM_SIM_ClearEEPROM();

		  E_UARTSTATE_XXR = STATE_RECEIVE;
		  break;
	  case STATE_RECEIVE:
		  /*This state will receive the data and write it in EEPROM RAM Buffer*/

		  /*Read the char from UART2 channel*/
		  v_uartrxchar_u8 = UART_GetChar(UART2);

		  /*Check if the buffer is FULL*/
		  if(v_indexaddress_u16==EEPROM_RAM_BUF_SIZE)
		  {
			  /*go to Error state if buffer is full*/
			  E_UARTSTATE_XXR = STATE_ERROR;
		  }
		  else
		  {
			  /*Write the received data into the EEPROM RAM buffer*/
			  EEPROM_SIM_Write(v_indexaddress_u16,v_uartrxchar_u8);

			  /*Increment the index for next value to be written in buffer*/
			  v_indexaddress_u16++;

			  /*Once null char is received, complete string is received*/
			  if(v_uartrxchar_u8 =='\0')
			  {
				  E_UARTSTATE_XXR = STATE_TRANSMIT;

				  /*clear the index, so transmission starts from start*/
				  v_indexaddress_u16 = 0U;
			  }
		  }
		  break;
	  case STATE_TRANSMIT:
		  /*This state will read the data from EEPROM RAM Buffer and transmit it via UART*/
		  if(v_indexaddress_u16==EEPROM_RAM_BUF_SIZE)
		  {
			  E_UARTSTATE_XXR = STATE_ERROR;
		  }
		  else
		  {
			  /*Reading the data from EEPROM*/
			  v_uarttxchar_u8 = EEPROM_SIM_Read(v_indexaddress_u16);

			  /*Transmitting the data read to UART to channel 2*/
			  (void)UART_PutChar(UART2,v_uarttxchar_u8);

			  /*Increment the index for next values*/
			  v_indexaddress_u16++;

			  /*If null char, transmission is done, go back to INIT*/
			  if(v_uarttxchar_u8 =='\0')
			  {
				  E_UARTSTATE_XXR = STATE_INIT;
			  }
		  }
		  break;
	  case STATE_ERROR:
		  /*This state will transmit ERROR Message*/

		  /*Transmit the error message per char*/
		  if(u_errormsgindex_u8<sizeof(v_errorMsg_char))
		  {
			  (void)UART_PutChar(UART2,v_errorMsg_char[u_errormsgindex_u8]);

			  /*Increment the buffer for next char*/
			  u_errormsgindex_u8++;
		  }
		  else
		  {
			  E_UARTSTATE_XXR = STATE_INIT;
		  }
		  break;
	  }
	}
}

/******************************************************************************
*							EOF
******************************************************************************/
