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



#include "derivative.h" /* include peripheral declarations SKEAZ128M4 */

#include "../MCAL/inc/clocks.h"
#include "../MCAL/inc/UART.h"

int main(void)
{
  int counter = 0;

  init_clks_FEE_40MHz();    /* KEA128 clks FEE, 8MHz xtal: core 40 MHz, bus 20MHz */
  init_UART();				/* Initialize UART2 9600 baud, 1 stop, no parity no IRQ */
  transmit_string("Running UART example\n\r"); /* Transmit string, new line, return */
  for(;;) {
    transmit_char('>');       /* Transmit a "prompt" type character */
    recieve_and_echo_char();  /* Wait for an input char, read it & echo it back */
    counter++;                /* Loop counter */
  }
}

/******************************************************************************
*							EOF
******************************************************************************/