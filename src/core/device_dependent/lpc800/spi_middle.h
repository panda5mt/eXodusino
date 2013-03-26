/*
 * spi_middle.h
 *
 *  Created on: 2013/03/06
 *      Author: lynxeyed
 */

#ifndef SPI_MIDDLE_H_
#define SPI_MIDDLE_H_

#include <lpc8xx_spi.h>
#include <gpio.h>
#ifdef __cplusplus
extern "C"
{
#endif

/*! @enum	SSP_PORT
  @brief	SPIポートのチャンネル選択。これに応じて使用時のCS信号を選択する
  @note		他のデバイスの後方互換性を考慮し用意している
*/
typedef enum {
	LPC8XXSPI,	/*!< LPC810のSPIポート(デフォルト) */
	LPC8XXSPI2	/*!< LPC810のSPI2ポート */
} SSP_PORT; // Defaults:LPC8XXSPI

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
	SPI_MODE3 			/*!< SPIモード3	( CPOL = 1, CPHA = 1 )　*/
} SSP_DATA_MODE;

void ssp_begin(SSP_PORT port,SSP_CLK_DIVIDER divider,SSP_DATA_MODE dataMode,int bitLength);
unsigned long ssp_transfer(unsigned long txdata);



#ifdef __cplusplus
}
#endif
#endif /* SPI_MIDDLE_H_ */
