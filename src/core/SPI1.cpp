/*
 * ssp.cpp
 *
 *  Created on: 2011/07/30
 *      Author: lynxeyed
 */
#include "gpio.h"
#include "SPI1.h"


SSP1 SPI1;

SSP1::SSP1()			//define constructor
{
	this->port = LPCXSSP1;
	bitOrder = LSBFIRST;
	divider = SPI_CLOCK_DIV4;	//Arduino's default
	dataMode = SPI_MODE0;
	bitlength = 8;
	setClockDivider(divider);
	setBitLength(bitlength);
	setBitOrder(LSBFIRST);
	begin();
}

SSP1::~SSP1()		// destructor
{

}
void SSP1::begin()
{
	ssp1_begin(port,divider,dataMode,bitlength);
	return;
}
void SSP1::begin(SSP_PORT port)
{
	this->port = port;
	ssp1_begin(port,divider,dataMode,bitlength);
	return;
}
void SSP1::setBitLength(int bitlength)
{
	this->bitlength = bitlength;
	return;
}
void SSP1::end()
{
	LPC_SSP1->CR1 &= ~(1U << 1);	//the SPI controller is disabled
	return;
}

void SSP1::setBitOrder(SSP_BIT_ORDER bitOrder)
{
	this->bitOrder = bitOrder;
	if(bitOrder == MSBFIRST)
	{
		;
	}
	else
	{
		;
	}
	return;
}

void SSP1::setClockDivider(SSP_CLK_DIVIDER divider)		//See also SSP1CLKDIV(user.manual p.24)
{
	this->divider = divider;
	return;

}

void SSP1::setDataMode(SSP_DATA_MODE mode)
{
	this->dataMode = mode;

}

unsigned long SSP1::transfer(unsigned long txdata)
{
	return ssp1_transfer(txdata);
}



// lowlevel

void ssp1_begin(SSP_PORT port,SSP_CLK_DIVIDER divider,SSP_DATA_MODE dataMode,int bitlength)
{
	// Initialize SSP
	//     PIO2_0			: SSEL
	//     PIO2_1			: SCLK
	//     PIO2_2			: MISO
	//     PIO2_3			: MOSI

	volatile int sspPhase;		//SSP's clock phase

	pinMode(P2_0,OUTPUT); 					// PIO2_0 out
	LPC_IOCON->PIO2_0  = 0x00000000;		// GPIO, disable pu/pd mos
	digitalWrite(P2_0,HIGH);				// PIO2_0 = 1

	LPC_IOCON->PIO2_1  = 0x00000002;		// SCK, disable pu/pd mos
	LPC_IOCON->PIO2_3  = 0x00000002;		// MOSI, disable pu/pd mos
	LPC_IOCON->PIO2_2  = 0x00000012;		// MISO, enable pu/pd mos

	/*
	switch(port){
	case LPCXSSP0:
		LPC_IOCON->SCK_LOC = 0x00000001;//2;	// SCK is PIO2_11
		LPC_IOCON->PIO2_11  = 0x00000001;//2;	// SCK, disable pu/pd mos
		break;
	case marySSP0:
		LPC_IOCON->SCK_LOC = 0x00000002;		// SCK is PIO0_6
		LPC_IOCON->PIO0_6  = 0x00000002;		// SCK, disable pu/pd mos
		break;
	default: //default = MARY
		LPC_IOCON->SCK_LOC = 0x00000002;		// SCK is PIO0_6
		LPC_IOCON->PIO0_6  = 0x00000002;		// SCK, disable pu/pd mos
		break;
	}
	*/

	//LPC_IOCON->PIO0_9 = 0x00000001;		// MOSI, disable pu/pd mos
	//LPC_IOCON->PIO0_8 = 0x00000011;		// MISO, enable pu/pd mos

	//
	// Initialize SPI
	//
	LPC_SYSCON->PRESETCTRL |= (0x1<<2);
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<18);
	//clockDivider
	LPC_SYSCON->SSP1CLKDIV = 0x01; // Divided by 1
	switch(divider)
	{
		case SPI_CLOCK_DIV1:				//Special code
			LPC_SYSCON->SSP1CLKDIV = 0x01;
			break;
		case SPI_CLOCK_DIV2:
			LPC_SYSCON->SSP1CLKDIV = 0x02;
			break;
		case SPI_CLOCK_DIV4:
			LPC_SYSCON->SSP1CLKDIV = 0x04;
			break;
		case SPI_CLOCK_DIV8:
			LPC_SYSCON->SSP1CLKDIV = 0x08;
			break;
		case SPI_CLOCK_DIV16:
			LPC_SYSCON->SSP1CLKDIV = 0x10;
			break;
		case SPI_CLOCK_DIV32:
			LPC_SYSCON->SSP1CLKDIV = 0x20;
			break;
		case SPI_CLOCK_DIV64:
			LPC_SYSCON->SSP1CLKDIV = 0x40;
			break;
		case SPI_CLOCK_DIV128:
			LPC_SYSCON->SSP1CLKDIV = 0x80;
			break;
		default:
			LPC_SYSCON->SSP1CLKDIV = 0x04;		//default
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
	LPC_SSP1->CR0 = (sspPhase << 6);
	LPC_SSP1->CR0 |= (bitlength - 1);

	//SCLKDivider
	LPC_SSP1->CPSR = 2;		//2 or more but even value


	// Enable the SSP Interrupt
	NVIC_EnableIRQ(SSP1_IRQn);
	NVIC_SetPriority(SSP1_IRQn, 3);

	// Device select as master, SSP Enabled (see also user.manual p.143)
	LPC_SSP1->CR1 = (1U << 1);
	return;
}

unsigned long ssp1_transfer(unsigned long txdata)
{
	volatile unsigned long rxdata;
	// Tx
	while ((LPC_SSP1->SR & ((1U<<1)|(1U<<4))) != 1U << 1);
	// Send a byte
	LPC_SSP1->DR = txdata;
	// Wait until the Busy bit is cleared
	while ( LPC_SSP1->SR & (1<<4) );

	// Rx
	while ((LPC_SSP1->SR & (1U<<2)) != 1U << 2 );
	rxdata = LPC_SSP1->DR;

	return rxdata;
}




