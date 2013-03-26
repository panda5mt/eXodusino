/*
 * uart_middle.h
 *
 *  Created on: 2013/03/16
 *      Author: lynxeyed
 */

#ifndef UART_MIDDLE_H_
#define UART_MIDDLE_H_

#include <lpcdevice.h>

#ifdef __cplusplus
 extern "C" {
#endif

 /*! @enum SERIAL_PORT
  @brief COMポート(UART)のチャンネル選択。
  @note UARTが1ポートしかないMARYでは使用していないので特に影響はないが、2ポート以上UARTが存在するLPCXpressoシリーズや
  mbedシリーズとの後方互換性を考慮し用意している
  */
 typedef enum {
 	marySerial1, /*!< MARYのUARTポート(デフォルト) */
 	mbedSerial1, /*!< mbed(LPC1768/9)のUART1ポート（将来的に対応予定） */
 	mbedSerial2
 /*!< mbed(LPC1768/9)のUART2ポート（将来的に対応予定） */
 } SERIAL_PORT; // Defaults:marySerial1



void uart_begin(SERIAL_PORT port,int speed);
void uart_end(void);
void uart_write_char(const char c);
int uart_available(void);
int uart_read(void);


#ifdef __cplusplus
 }
#endif

#endif /* UART_MIDDLE_H_ */
