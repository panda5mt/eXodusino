/*
 * uart.cpp
 *
 *  Created on: 2011/07/30
 *      Author: lynxeyed
 */

#include <string.h>
#include "LPC11xx.h"
#include "uart.h"

#ifdef __cplusplus
  extern "C" {
#endif

  // Flag mask for UART_LSR register.
const unsigned long     LSR_TEMT	= 0x40;
const unsigned long     LSR_THRE	= 0x20;
const unsigned long     LSR_RDR		= 0x01;
const unsigned long     ACR_START	= 0x01;
const unsigned long		IER_RLS		= 0x04;
const unsigned long		IER_RBR		= 0x01;

USerial Serial;

USerial::USerial()//USerial(SERIAL_PORT port)			//define constructor
{
	this->port = marySerial1;			//default = marySerial1
	format = OCT;
	speed = 9600;				//baudrate
	//begin(speed);
}

USerial::~USerial()
{

}

void USerial::begin(int speed)
{
	this->speed = speed;
	// Divisor ratio
	unsigned long Fdiv;

	// Configure P1[7] as TXD output.
	LPC_IOCON->PIO1_7 &= ~0x07;         // FUNC=000 (GPIO)
	LPC_IOCON->PIO1_7 |= 0x01;          // FUNC=001 (TXD)

	// Configure P1[6] as RXD input.
	LPC_IOCON->PIO1_6 &= ~0x07;         // FUNC=000 (GPIO)
	LPC_IOCON->PIO1_6 |= 0x01;          // FUNC=001 (RXD)

	// Enable UART clock
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);   // UART=1

	// Enable UART peripheral clock
	LPC_SYSCON->UARTCLKDIV = 0x01;      // DIV=1

	// fix baud-rate
	Fdiv = (SystemCoreClock * LPC_SYSCON->SYSAHBCLKDIV) / (LPC_SYSCON->UARTCLKDIV * 16 * speed);

	// Set the baud rate divisor value
	LPC_UART->LCR |= 0x80;
	LPC_UART->DLM = Fdiv / 256;
	LPC_UART->DLL = Fdiv % 256;
	LPC_UART->LCR &= ~0x80;

	// Configure UART module as
	//   8 bit, 1 stop bit, no parity
	//   Enable and reset TX and RX FIFO.
	LPC_UART->LCR = 0x03;
	LPC_UART->FCR = 0x07;

}

void USerial::end()
{
	return;
}

void USerial::write(const char c)	//uart_putc
{
	// Wait for TX buffer empty
	while (!(LPC_UART->LSR & LSR_THRE));
	// Put a character
	LPC_UART->THR = c;
	return;
}

void USerial::print(const char *s)	//uart_puts
{
    int n;
    for (n = 0; *s; s++, n++) {
        write(*s);
    }
    //return n;
    return;
}

void USerial::print(int val, RADIX_FORMAT format)
{
	if(format == BYTE)
	{
		write((char)(val & 0xff));
		return;
	}
	char s[32];
	int i,j;
	i=j=0; // header of strings
	if (val<0)
	{ //minus value
		s[i]='-';
		val=~val+1;
		i++;
		j++;
	}
	switch(format)
	{
	case BIN:
		while (val>0)
		{ // do until zero
			s[i++]=radix_bin[val%format];
			val/=format;
		}
		break;

	case OCT:
		while (val>0)
		{ // do until zero
			s[i++]=radix_oct[val%format];
			val/=format;
		}
		break;

	case DEC:	//RADIX = Decimal
		while (val>0)
		{ // do until zero
			s[i++]=radix_dec[val%format];
			val/=format;
		}
		break;

	case HEX:	//RADIX = Hexadecimal
		while (val>0)
		{ // do until zero
			s[i++]=radix_hex[val%format];
			val/=format;
		}
		break;
	default:
		break;
	}
	s[i--]='\0'; // EOF
	while (j<i)
	{ // reverse strings array
	char t;
	t=s[j]; s[j]=s[i]; s[i]=t;
	j++; i--;
	}
	print(s);

	return ;
}

void USerial::write(const char *s, int length)
{
	int n;
	for(n=0;n<length;s++,n++)
	{
		write(*s);
	}
	return;
}

void USerial::println(const char *s)
{
	print(s);
	write ('\r');
	write ('\n');
	return;
}


void USerial::println(int val, RADIX_FORMAT format)
{
	print(val,format);
	write ('\r');
	write ('\n');
	return;
}

int USerial::available(void)
{
	return (LPC_UART->LSR & LSR_RDR);
}

int USerial::read(void)
{
	// Wait for RX buffer valid
	//while (!(LPC_UART->LSR & LSR_RDR));
	return LPC_UART->RBR;
}

#ifdef __cplusplus
} //extern "C"
#endif
