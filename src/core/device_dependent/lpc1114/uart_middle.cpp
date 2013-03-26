/*
 * uart_middle.cpp
 *
 *  Created on: 2013/03/16
 *      Author: lynxeyed
 */
#if defined(USE_LPC1114)
#include <uart_middle.h>

// Flag mask for UART_LSR register.
const unsigned long LSR_TEMT = 0x40;
const unsigned long LSR_THRE = 0x20;
const unsigned long LSR_RDR = 0x01;
const unsigned long ACR_START = 0x01;
const unsigned long IER_RLS = 0x04;
const unsigned long IER_RBR = 0x01;


void uart_begin(SERIAL_PORT port,int speed)
{
	// Divisor ratio
	unsigned long Fdiv;

	// Configure P1[7] as TXD output.
	LPC_IOCON->PIO1_7 &= ~0x07; // FUNC=000 (GPIO)
	LPC_IOCON->PIO1_7 |= 0x01; // FUNC=001 (TXD)

	// Configure P1[6] as RXD input.
	LPC_IOCON->PIO1_6 &= ~0x07; // FUNC=000 (GPIO)
	LPC_IOCON->PIO1_6 |= 0x01; // FUNC=001 (RXD)

	// Enable UART clock
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 12); // UART=1

	// Enable UART peripheral clock
	LPC_SYSCON->UARTCLKDIV = 0x01; // DIV=1

	// fix baud-rate
	Fdiv = (SystemCoreClock * LPC_SYSCON->SYSAHBCLKDIV)
			/ (LPC_SYSCON->UARTCLKDIV * 16 * speed);

	// Set the baud rate divisor value
	LPC_UART->LCR |= 0x80;
	LPC_UART->DLM = Fdiv / 256;
	LPC_UART->DLL = Fdiv % 256;
	LPC_UART->LCR &= ~0x80;

	// Configure UART module as
	// 8 bit, 1 stop bit, no parity
	// Enable and reset TX and RX FIFO.
	LPC_UART->LCR = 0x03;
	LPC_UART->FCR = 0x07;

}

void uart_end(void)
{
	return;
}

void uart_write_char(const char c)
{
	// Wait for TX buffer empty
	while (!(LPC_UART->LSR & LSR_THRE))
		;
	// Put a character
	LPC_UART->THR = c;
}

int uart_available(void)
{
	return (LPC_UART->LSR & LSR_RDR);
}

int uart_read(void)
{
	// Wait for RX buffer valid
	//while (!(LPC_UART->LSR & LSR_RDR));
	return LPC_UART->RBR;
}

#endif
