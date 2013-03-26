/*
 * spi_middle.h
 *
 *  Created on: 2013/03/11
 *      Author: lynxeyed
 */

#ifndef SPI_MIDDLE_H_
#define SPI_MIDDLE_H_


#ifdef __cplusplus
extern "C"
{
#endif

/*! @enum	SSP_PORT
  @brief	SPIポートのチャンネル選択。使用時のCS信号を選択する
  @note		SPIが1ポートしかないMARYでは使用していないので特に影響はないが、2ポート以上あるLPCXpresso LPC1114やmbedシリーズとの後方互換性を考慮し用意している
*/
typedef enum {
	marySSP0,	/*!< MARYのSSPポート(デフォルト) */
	LPCXSSP0,	/*!< LPCXPressoのSSP0ポート */
	LPCXSSP1,	/*!< LPCXpressoのSSP1ポート */
	SCK_P0_6	/*!< SSP0ポートのSCKはP0_6を使う */
} SSP_PORT; // Defaults:marySSP0

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

// lowlevel
void ssp_begin(SSP_PORT port,SSP_CLK_DIVIDER divider,SSP_DATA_MODE dataMode,int bitLength);
unsigned long ssp_transfer(unsigned long txdata);



#ifdef __cplusplus
}
#endif

#endif /* SPI_MIDDLE_H_ */
