#ifndef SSP_H_
#define SSP_H_


/**************************************************************************//**
 * @file     SPI.h
 * @brief    Arduino-like library for MARY
 * @version	V0.50
 * @date	1. August 2011.
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
#include "gpio.h"

#ifdef __cplusplus
  extern "C" {
#endif

/*! @enum	SSP_PORT
  @brief	SPIポートのチャンネル選択。使用時のCS信号を選択する
  @note		SPIが1ポートしかないMARYでは使用していないので特に影響はないが、2ポート以上あるLPCXpresso LPC1114やmbedシリーズとの後方互換性を考慮し用意している
*/
typedef enum {
	marySSP0,	/*!< MARYのSSPポート(デフォルト) */
	LPCXSSP0,	/*!< LPCXPressoのSSP0ポート */
	LPCXSSP1	/*!< LPCXpressoのSSP1ポート */
} SSP_PORT; // Defaults:marySSP1

/*! @enum	SSP_BIT_ORDER
  @brief	SSPIバスの入出力に使用するビットオーダーを設定
  @warning	この機能はまだ実装されていない
  */
typedef enum {
	LSBFIRST, 		/*!< LSBを最初に送出(least-significant bit first) */
	MSBFIRST		/*!< MSBを最初に送出(most-significant bit first) */
} SSP_BIT_ORDER;

/*! @enum	SSP_CLK_DIVIDER
    @brief	SPIクロック分周器の設定. 分周値は2、4、8、16、32、64、128のいずれか
*/
typedef enum {
	SPI_CLOCK_DIV1, 	/*!< SPIクロックはシステムクロックと同じ(MARY-DUINOオリジナル) */
	SPI_CLOCK_DIV2,  	/*!< SPIクロックはシステムクロックの1/2 */
	SPI_CLOCK_DIV4,  	/*!< SPIクロックはシステムクロックの1/4 */
	SPI_CLOCK_DIV8,   	/*!< SPIクロックはシステムクロックの1/8 */
	SPI_CLOCK_DIV16,  	/*!< SPIクロックはシステムクロックの1/16 */
	SPI_CLOCK_DIV32,  	/*!< SPIクロックはシステムクロックの1/32 */
	SPI_CLOCK_DIV64,  	/*!< SPIクロックはシステムクロックの1/64 */
	SPI_CLOCK_DIV128  	/*!< SPIクロックはシステムクロックの1/128 */
} SSP_CLK_DIVIDER;

/*! @enum	SSP_DATA_MODE
    @brief	SPIの転送モードの設定
*/
typedef enum {
	SPI_MODE0 ,			/*!< SPIモード0	( CPOL = 0, CPHA = 0 )　*/
	SPI_MODE1 ,			/*!< SPIモード1	( CPOL = 0, CPHA = 1 )　*/
	SPI_MODE2 ,			/*!< SPIモード2	( CPOL = 1, CPHA = 0 )　*/
	SPI_MODE3 ,			/*!< SPIモード3	( CPOL = 1, CPHA = 1 )　*/
	TI_SERIAL_MODE ,	/*!< Texas Instrumentsの提唱するシリアル方式　*/
	NXP_I2S				/*!< I2Sモード(I2S搭載機種のみ)　*/
} SSP_DATA_MODE;

/*! @class SSP
	@brief SPIを制御するクラス
*/
class SSP {
private:
	SSP_PORT port;				/*!< 使用するポート　*/
	SSP_BIT_ORDER bitOrder;
	SSP_CLK_DIVIDER divider;
	SSP_DATA_MODE dataMode;
	int bitlength;

public:
	SSP();		// announce the constructor to initialize
	~SSP();
	void begin();
	void begin(SSP_PORT port);
	void end();
	void setBitLength(int bitLength);
	void setBitOrder(SSP_BIT_ORDER bitOrder) ;
	void setClockDivider(SSP_CLK_DIVIDER divider);
	void setDataMode(SSP_DATA_MODE mode);
	unsigned long transfer(unsigned long txdata) ;
};


// lowlevel
void ssp_begin(SSP_PORT port,SSP_CLK_DIVIDER divider,SSP_DATA_MODE dataMode,int bitLength);
unsigned long ssp_transfer(unsigned long txdata);



extern SSP SPI;


#ifdef __cplusplus
  }
#endif


#endif /* SSP_H_ */
