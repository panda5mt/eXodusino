/*
 * spi_middle.cpp
 *
 *  Created on: 2013/03/06
 *      Author: lynxeyed
 */
#if defined(USE_LPC800)
#include <spi_middle.h>

#define CS_USED			SLAVE0

volatile int SPI_BIT_LENGTH;

void ssp_begin(SSP_PORT port,SSP_CLK_DIVIDER divider,SSP_DATA_MODE dataMode,int bitlength)
{
	volatile int ssp_phase;		//SSP's clock phase
	SPI_BIT_LENGTH = bitlength;

//	/* Pin Assign 8 bit Configuration */
//	/* SPI0_SCK */
//	LPC_SWM->PINASSIGN3 = 0x0cffffffUL;// P0_12 -> SCK
//	/* SPI0_MOSI */  // P0_14 -> MOSI (LSB)
//	/* SPI0_MISO */  // P0_6  -> MISO
//	/* SPI0_SSEL */  // not in use ::P0_13 -> SSEL
//	LPC_SWM->PINASSIGN4 = 0xffff060eUL;

	switch(port)
	{
		//
	}

	switch(divider)
	{
		case SPI_CLOCK_DIV1:	//Special code
			//
			break;
		case SPI_CLOCK_DIV2:
			//
			break;
		case SPI_CLOCK_DIV4:
			//
			break;
		case SPI_CLOCK_DIV8:
			//
			break;
		case SPI_CLOCK_DIV16:
			//
			break;
		case SPI_CLOCK_DIV32:
			//
			break;
		case SPI_CLOCK_DIV64:
			//
			break;
		case SPI_CLOCK_DIV128:
			//
			break;
		default:
			//
			break;
	}

	ssp_phase = 0;
	// dataMode(MODE0,1,2,3)
	switch(dataMode)
	{
						// SSP0CR0::bit6 = CPOL, bit7 = CPHA
		case SPI_MODE0:	// CPOL=0, CPHA = 0
			ssp_phase = 0;

			break;
		case SPI_MODE1:	// CPOL=0, CPHA = 1
			ssp_phase |= CFG_CPHA;
			break;
		case SPI_MODE2:	// CPOL=1, CPHA = 0
			ssp_phase |= CFG_CPOL;
			break;
		case SPI_MODE3:	// CPOL=1, CPHA = 1
			ssp_phase |= (CFG_CPOL + CFG_CPHA);
			break;
		default:
			break;
	}//end switch(dataMode)

	SPI_Init(LPC_SPI0, 0x05, CFG_MASTER | ssp_phase , DLY_PREDELAY(0x0)|DLY_POSTDELAY(0x0)|DLY_FRAMEDELAY(0x0)|DLY_INTERDELAY(0x0));

	return;
}

unsigned long ssp_transfer(unsigned long txdata)
{
	//note:transfer length is up to 16bit when lpc8xx

	uint16_t rxdata_16 = 0;
	uint16_t txdata_16 = txdata;

	//SPI_SendRcv( LPC_SPI0, CS_USED, *tx_p, *rx_p, 1 );
	SPI_SendRcv_with_bit_length( LPC_SPI0, CS_USED, &txdata_16, &rxdata_16, SPI_BIT_LENGTH );
	return (unsigned long)rxdata_16;
}


#endif



