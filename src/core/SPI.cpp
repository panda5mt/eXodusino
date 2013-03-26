/*
 * ssp.cpp
 *
 *  Created on: 2011/07/30
 *      Author: lynxeyed
 */
#include "gpio.h"
#include "SPI.h"


SSP SPI;

SSP::SSP()			//define constructor
{
	//this->port = marySSP0;
	bitOrder = LSBFIRST;
	divider = SPI_CLOCK_DIV4;	//Arduino's default
	dataMode = SPI_MODE0;
	bitlength = 8;
	setClockDivider(divider);
	setBitLength(bitlength);
	setBitOrder(LSBFIRST);
	begin();
}

SSP::~SSP()		// destructor
{

}


void SSP::begin(void)
{
	//this->port = marySSP0;
	ssp_begin(port,divider,dataMode,bitlength);
	return;
}
void SSP::begin(SSP_PORT port)
{
	this->port = port;
	ssp_begin(port,divider,dataMode,bitlength);
	return;
}
void SSP::setBitLength(int bitlength)
{
	this->bitlength = bitlength;
	return;
}
void SSP::end()
{
	//LPC_SSP0->CR1 &= ~(1U << 1);	//the SPI controller is disabled
	return;
}

void SSP::setBitOrder(SSP_BIT_ORDER bitOrder)
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

void SSP::setClockDivider(SSP_CLK_DIVIDER divider)		//See also SSP1CLKDIV(user.manual p.24)
{
	this->divider = divider;
	return;
}

void SSP::setDataMode(SSP_DATA_MODE mode)
{
	this->dataMode = mode;

}

unsigned long SSP::transfer(unsigned long txdata)
{
	return ssp_transfer(txdata);
}

