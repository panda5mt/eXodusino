#ifndef WIRE_H_
#define WIRE_H_

/**************************************************************************//**
 * @file     Wire.h
 * @brief    Arduino-like library for MARY
 * @version	V0.50
 * @date	4. April 2012.
 * @author	@@lynxeyed_atsu
 * @note	Copyright (c) 2011 Lynx-EyED's Klavier and Craft-works. <BR>
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions: <BR>
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.<BR>
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/
#include "LPC11xx.h"
#include <libmary.h>

#ifdef __cplusplus
	extern "C" {
#endif

#define BUFFER_LENGTH 32

/*! @enum	WIRE_ACK_STATE
	@brief	I2Cでバイトデータを送った際にスレーブからの値を返す
*/
typedef enum {
	ACK = 0,	/*!< ACK(入力バイトは承認された) */
	NAK,		/*!< ACK(入力バイトは承認されなかった) */
	BUFF_OV, 		/*!< バッファオーバーフロー */
	ADDR_NAK,		/*!< スレーブへアドレスを送信しNACKを受信した */
	DATA_NAK,		/*!< スレーブへデータを送信しNACKを受信した */
	AND_MORE		/*!< その他のエラー */
} WIRE_ACK_STATE;

class TwoWire{

private:
	int sda,scl;

    static uint8_t rxBuffer[];
    static uint8_t rxBufferIndex;
    static uint8_t rxBufferLength;

    static uint8_t txAddress;
    static uint8_t txBuffer[];
    static uint8_t txBufferIndex;
    static uint8_t txBufferLength;

    static uint8_t transmitting;
    static void (*user_onRequest)(void);
    static void (*user_onReceive)(int);
    static void onRequestService(void);
    static void onReceiveService(uint8_t*, int);

public:
	TwoWire();
	void begin();
	void begin(uint8_t);
	void begin(int);
	void begin(int,int);
	void beginTransmission(uint8_t);
	void beginTransmission(int);
	uint8_t endTransmission(void);
	uint8_t requestFrom(uint8_t, uint8_t);
	uint8_t requestFrom(int, int);
	void write(int8_t);
	void send(uint8_t*, uint8_t);
	void send(int8_t *);
	void send(int);
	uint8_t available(void);
	uint8_t receive(void);
	void onReceive( void (*)(int) );
	void onRequest( void (*)(void) );
};

extern TwoWire Wire;

#ifdef __cplusplus
  }
#endif

#endif /* WIRE_H_ */
