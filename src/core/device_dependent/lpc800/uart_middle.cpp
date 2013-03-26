/*
 * uart_middle.cpp
 *
 *  Created on: 2013/03/16
 *      Author: lynxeyed
 */
#if defined(USE_LPC800)
#include <uart_middle.h>

void uart_begin(SERIAL_PORT port,int speed)
{
	uint32_t regVal;
#if 1
  /* connect the UART0 TXD abd RXD sigals to port pins(P0.4-P0.0)*/
	regVal = LPC_SWM->PINASSIGN0 & ~( 0xFF << 0 );
	LPC_SWM->PINASSIGN0 = regVal | ( 4 << 0 );				/* P0.4 is UART0 TXD, ASSIGN0(7:0) */
	regVal = LPC_SWM->PINASSIGN0 & ~( 0xFF << 8 );
	LPC_SWM->PINASSIGN0 = regVal | ( 0 << 8 );				/* P0.0 is UART0 RXD. ASSIGN0(15:8) */

//	regVal = LPC_SWM->PINASSIGN0 & ~( 0xFF << 16 );
//	LPC_SWM->PINASSIGN0 = regVal | ( 12 << 16 );			/* P0.12 is UART0 RTS, ASSIGN0(23:16) */
//	regVal = LPC_SWM->PINASSIGN0 & ~( 0xFFUL << 24 );
//	LPC_SWM->PINASSIGN0 = regVal | ( 13 << 24 );			/* P0.13 is UART0 CTS. ASSIGN0(31:24) */
#endif

#if 0
  /* connect the UART1 TXD abd RXD sigals to port pins(P0.4-P0.0)*/
	regVal = LPC_SWM->PINASSIGN1 & ~( 0xFF << 8 );
	LPC_SWM->PINASSIGN1 = regVal | ( 4 << 8 );				/* P0.4 is UART1 TXD, ASSIGN1(15:8) */
	regVal = LPC_SWM->PINASSIGN1 & ~( 0xFF << 16 );
	LPC_SWM->PINASSIGN1 = regVal | ( 0 << 16 );			/* P0.0 is UART1 RXD. ASSIGN1(23:16) */

	regVal = LPC_SWM->PINASSIGN1 & ~( 0xFFUL << 24 );
	LPC_SWM->PINASSIGN1 = regVal | ( 12 << 24 );			/* P0.12 is UART1 RTS. ASSIGN1(31:24) */
	regVal = LPC_SWM->PINASSIGN2 & ~( 0xFF << 0 );
	LPC_SWM->PINASSIGN2 = regVal | ( 13 << 0 );			/* P0.13 is UART1 RTS, ASSIGN2(7:0) */
#endif

#if 0
	/* connect the UART2 TXD abd RXD sigals to port pins(P0.4-P0.0)*/
	regVal = LPC_SWM->PINASSIGN2 & ~( 0xFF << 16 );
	LPC_SWM->PINASSIGN2 = regVal | ( 4 << 16 );			/* P0.4 is UART2 TXD, ASSIGN2(23:16) */
	regVal = LPC_SWM->PINASSIGN2 & ~( 0xFFUL << 24 );
	LPC_SWM->PINASSIGN2 = regVal | ( 0 << 24 );			/* P0.0 is UART2 RXD. ASSIGN2(31:24) */

	regVal = LPC_SWM->PINASSIGN3 & ~( 0xFF << 0 );
	LPC_SWM->PINASSIGN3 = regVal | ( 12 << 0 );			/* P0.12 is UART2 RTS. ASSIGN1(7:0) */
	regVal = LPC_SWM->PINASSIGN3 & ~( 0xFF << 8 );
	LPC_SWM->PINASSIGN3 = regVal | ( 13 << 8 );			/* P0.13 is UART2 RTS, ASSIGN2(15:8) */
#endif

//  UARTInit(LPC_USART0, 115200);
	UARTInit(LPC_USART0, speed);
}

void uart_end(void)
{

}

void uart_write_char(const char c)
{
 	while (!(LPC_USART0->STAT & TXRDY));
	LPC_USART0->TXDATA = c;

}

int uart_available(void)
{
	if (LPC_USART0->STAT & RXRDY)
	{// data available
		return 1;
	}
	return 0;
}

int uart_read(void)
{
	return (int) ( LPC_USART0->RXDATA );
}

#endif
