/*
 * uart_middle.h
 *
 *  Created on: 2013/03/16
 *      Author: lynxeyed
 */

#ifndef UART_MIDDLE_H_
#define UART_MIDDLE_H_

#include <lpcdevice.h>
#include <lpc8xx_uart.h>

#ifdef __cplusplus
 extern "C" {
#endif
 typedef enum {
 	Serial0, /*!< UART0ポート(デフォルト) */
 	Serial1  /*!< UART1ポート */
 } SERIAL_PORT; // Defaults:Serial0

void uart_begin(SERIAL_PORT port,int speed);
void uart_end(void);
void uart_write_char(const char c);
int uart_available(void);
int uart_read(void);


#ifdef __cplusplus
 }
#endif

#endif /* UART_MIDDLE_H_ */
