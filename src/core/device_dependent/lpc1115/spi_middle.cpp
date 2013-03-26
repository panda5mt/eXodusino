/*
 * spi_middle.cpp
 *
 *  Created on: 2013/03/11
 *      Author: lynxeyed
 */
#if defined(USE_LPC1115)
#include <spi_middle.h>
#include <gpio.h>

void ssp_begin(SSP_PORT port,SSP_CLK_DIVIDER divider,SSP_DATA_MODE dataMode,int bitlength)
{
	// Initialize SSP
	//     PIO0_2(CN3_3)	: SSEL
	//     PIO0_6(CN4_3)	: SCLK
	//     PIO0_8(CN4_5)	: MISO
	//     PIO0_9(CN4_7)	: MOSI

	volatile int sspPhase;		//SSP's clock phase

	pinMode(P0_2,OUTPUT); 				// PIO0_2(CN3_3) out
	LPC_IOCON->PIO0_2  = 0x00000000;	// GPIO, disable pu/pd mos
	digitalWrite(P0_2,HIGH);				// PIO0_2(CN3_3) = 1

	switch(port)
	{
	case LPCXSSP0:
		LPC_IOCON->SCK_LOC = 0x00000001;//2;	// SCK is PIO2_11

		break;

	case marySSP0:
#if defined ( NEXTPINO )
		LPC_IOCON->SCK_LOC = 0x00000000;		// SCK is PIO0_10
		LPC_IOCON->SWCLK_PIO0_10 = 0x00000002;
#else
		LPC_IOCON->SCK_LOC = 0x00000002;		// SCK is PIO0_6
		LPC_IOCON->PIO0_6  = 0x00000002;		// SCK, disable pu/pd mos
#endif
		break;

	case SCK_P0_6:
		LPC_IOCON->SCK_LOC = 0x00000002;		// SCK is PIO0_6
		LPC_IOCON->PIO0_6  = 0x00000002;		// SCK, disable pu/pd mos
		break;

	default: //default = MARY
#if defined ( NEXTPINO )
		LPC_IOCON->SCK_LOC = 0x00000000;		// SCK is PIO0_10
		LPC_IOCON->SWCLK_PIO0_10 = 0x00000002;
#else
		LPC_IOCON->SCK_LOC = 0x00000002;		// SCK is PIO0_6
		LPC_IOCON->PIO0_6  = 0x00000002;		// SCK, disable pu/pd mos
#endif
		break;
	}
	LPC_IOCON->PIO0_9 = 0x00000001;		// MOSI, disable pu/pd mos
	LPC_IOCON->PIO0_8 = 0x00000011;		// MISO, enable pu/pd mos

	//
	// Initialize SPI
	//
	LPC_SYSCON->PRESETCTRL |= (0x1<<0);
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<11);
	//clockDivider
	LPC_SYSCON->SSP0CLKDIV = 0x01; // Divided by 1
	switch(divider)
	{
		case SPI_CLOCK_DIV1:				//Special code
			LPC_SYSCON->SSP0CLKDIV = 0x01;
			break;
		case SPI_CLOCK_DIV2:
			LPC_SYSCON->SSP0CLKDIV = 0x02;
			break;
		case SPI_CLOCK_DIV4:
			LPC_SYSCON->SSP0CLKDIV = 0x04;
			break;
		case SPI_CLOCK_DIV8:
			LPC_SYSCON->SSP0CLKDIV = 0x08;
			break;
		case SPI_CLOCK_DIV16:
			LPC_SYSCON->SSP0CLKDIV = 0x10;
			break;
		case SPI_CLOCK_DIV32:
			LPC_SYSCON->SSP0CLKDIV = 0x20;
			break;
		case SPI_CLOCK_DIV64:
			LPC_SYSCON->SSP0CLKDIV = 0x40;
			break;
		case SPI_CLOCK_DIV128:
			LPC_SYSCON->SSP0CLKDIV = 0x80;
			break;
		default:
			LPC_SYSCON->SSP0CLKDIV = 0x04;		//default
			break;
	}
	// dataMode(MODE0,1,2,3)
	switch(dataMode)
	{
						// SSP0CR0::bit6 = CPOL, bit7 = CPHA
		case SPI_MODE0:	// CPOL=0, CPHA = 0
			sspPhase = 0;
			break;
		case SPI_MODE1:	// CPOL=0, CPHA = 1
			sspPhase = 1;
			break;
		case SPI_MODE2:	// CPOL=1, CPHA = 0
			sspPhase = 2;
			break;
		case SPI_MODE3:	// CPOL=1, CPHA = 1
			sspPhase = 3;
			break;
		case TI_SERIAL_MODE:
		default:
			break;
	}//end switch(dataMode)

	// bitLength
	LPC_SSP0->CR0 = (sspPhase << 6);
	LPC_SSP0->CR0 |= (bitlength - 1);

	//SCLKDivider
	LPC_SSP0->CPSR = 2;		//2 or more but even value


	// Enable the SSP Interrupt
	NVIC_EnableIRQ(SSP0_IRQn);
	NVIC_SetPriority(SSP0_IRQn, 3);

	// Device select as master, SSP Enabled (see also user.manual p.143)
	LPC_SSP0->CR1 = (1U << 1);
	return;
}

unsigned long ssp_transfer(unsigned long txdata)
{
	volatile unsigned long rxdata;
	// Tx
	while ((LPC_SSP0->SR & ((1U<<1)|(1U<<4))) != 1U << 1);
	// Send a byte
	LPC_SSP0->DR = txdata;
	// Wait until the Busy bit is cleared
	while ( LPC_SSP0->SR & (1<<4) );

	// Rx
	while ((LPC_SSP0->SR & (1U<<2)) != 1U << 2 );
	rxdata = LPC_SSP0->DR;

	return rxdata;
}

#endif

