/*
 * uart.cpp
 *
 * Created on: 2011/07/30
 * Author: lynxeyed
 */

#include <string.h>
#include <lpcdevice.h>
#include "uart.h"

#ifdef __cplusplus
extern "C" {
#endif

// Flag mask for UART_LSR register.
const unsigned long LSR_TEMT = 0x40;
const unsigned long LSR_THRE = 0x20;
const unsigned long LSR_RDR = 0x01;
const unsigned long ACR_START = 0x01;
const unsigned long IER_RLS = 0x04;
const unsigned long IER_RBR = 0x01;

USerial Serial;

USerial::USerial()//USerial(SERIAL_PORT port) //define constructor
{
	//this->port = marySerial1; //default = marySerial1
//	format = OCT;
	speed = 9600; //baudrate
	//begin(speed);
}

USerial::~USerial() {

}

void USerial::begin(int speed) {

	this->speed = speed;
	uart_begin(port, speed);

}

void USerial::end() {
	return;
}


void USerial::write(const char c) //uart_putc
{
	uart_write_char(c);
	return;
}

int USerial::available(void) {

	return (uart_available());

}

int USerial::read(void) {

	return (uart_read());

}


#ifdef __cplusplus
} //extern "C"
#endif
