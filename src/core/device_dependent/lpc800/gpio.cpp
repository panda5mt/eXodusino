#if defined(USE_LPC800)
#include "gpio.h"


// IOCON:Cortex-M0 depend Settings
//#ifdef __NXP_LPC1114
#define PORT_BIT_COUNT 12 // up to 12 I/O lines per port
#define PORT_COUNT 4 // up to 4 ports


void pinMode(int pin,pinModeState state)
{
	if(pin < 100) return;	//(20~99:reserved)

	if(pin < 200)			//maryPinAssign(100~119?)
	{
		pin = pin - 100;
		if(state == OUTPUT)	//OUTPUT
		{
			GPIOSetDir(xpresso_pinAssign[pin * 2],xpresso_pinAssign[pin * 2 + 1], 1);
		}else		//INPUT
		{
			GPIOSetDir(xpresso_pinAssign[pin * 2],xpresso_pinAssign[pin * 2 + 1], 0);
		}
	}
	return;
 }

void digitalWrite(int pin,digitalWriteState state)
{

	if(pin < 100) return;	//(~99:reserved)

	if(pin < 200)			//maryPinAssign(100~119?)
	{
		pin = pin - 100;
		if(state == HIGH)	//HIGH
		{
			if(LPC_GPIO_PORT->DIR0 & (1 << xpresso_pinAssign[pin * 2 + 1]))//pin is output
			{
				GPIOSetBitValue( xpresso_pinAssign[pin * 2], xpresso_pinAssign[pin * 2 + 1], 1);
			}else //pin is input
			{
				//SetIOCON(xpresso_pinAssign[pin * 2], xpresso_pinAssign[pin * 2 + 1], IOCON_MODE_MASK, IOCON_MODE_PULLUP);
			}
		}else		//LOW
		{
			if(LPC_GPIO_PORT->DIR0 & (1 << xpresso_pinAssign[pin * 2 + 1]))//pin is output
			{
				GPIOSetBitValue( xpresso_pinAssign[pin * 2], xpresso_pinAssign[pin * 2 + 1], 0);
			}else // pin is input
			{
				//SetIOCON(xpresso_pinAssign[pin * 2], xpresso_pinAssign[pin * 2 + 1], IOCON_MODE_MASK, IOCON_MODE_INACTIVE);
			}
		}
	}
	return;
 }

int digitalRead(int pin)
{
	volatile int readValue;
	if(pin < 100) return 0;	//(20~99:reserved)

	if(pin < 200)			//maryPinAssign(100~199?)
	{
		pin = pin - 100;
		readValue = GPIOGetPinValue(xpresso_pinAssign[pin * 2], xpresso_pinAssign[pin * 2 + 1]);
		return readValue;
	}
	return 0;
}

/*****************************************************************************
 ** Function name:		GPIOSetInterrupt
 **
 ** Descriptions:		Set interrupt sense, event, etc.
 **						edge or level, 0 is edge, 1 is level
 **						single or double edge, 0 is single, 1 is double
 **						active high or low, etc.
 **
 ** parameters:			pin num, bit position, sense, single/doube, polarity
 ** Returned value:		None
 **
 *****************************************************************************/
void GPIOSetInterrupt(int pin, int sense, int single, int event) {
	if (pin >= 22 && pin < 100) {
		//(22~99:reserved)
	} else if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
//		pin = pin - 100;
//		if (sense == 0) {
//			LPC_GPIO[mary_pinAssign[pin * 2]]->IS &= ~((1 << mary_pinAssign[pin * 2 + 1]));
//			/* single or double only applies when sense is 0(edge trigger). */
//			if (single == 0)
//				LPC_GPIO[mary_pinAssign[pin * 2]]->IBE &= ~((1 << mary_pinAssign[pin * 2 + 1]));
//			else
//				LPC_GPIO[mary_pinAssign[pin * 2]]->IBE |= ((1 << mary_pinAssign[pin * 2 + 1]));
//		} else
//			LPC_GPIO[mary_pinAssign[pin * 2]]->IS |= ((1 << mary_pinAssign[pin * 2 + 1]));
//
//		if (event == 0)
//			LPC_GPIO[mary_pinAssign[pin * 2]]->IEV &= ~((1 << mary_pinAssign[pin * 2 + 1]));
//		else
//			LPC_GPIO[mary_pinAssign[pin * 2]]->IEV |= ((1 << mary_pinAssign[pin * 2 + 1]));
	}

	return;
}

void GPIOIntEnable(int pin) {
	if (pin >= 22 && pin < 100) { //(20~99:reserved)

	} else if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;
//		LPC_GPIO[mary_pinAssign[pin * 2]]->IE |= (1 << mary_pinAssign[pin * 2 + 1]);
	}

	return;
}

void GPIOIntDisable(int pin) {
	if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;
//		LPC_GPIO[mary_pinAssign[pin * 2]]->IE &= ~((1 << mary_pinAssign[pin * 2 + 1]));
	}

	return;
}

int GPIOIntStatus(int pin) {
	int regVal = 0;
	if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;

//		if (LPC_GPIO[mary_pinAssign[pin * 2]]->MIS
//				& (1 << mary_pinAssign[pin * 2 + 1]))
//		{
//			regVal = 1;
//		}
	}

	return regVal;
}

void GPIOIntClear(int pin) {
	if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;
//		LPC_GPIO[mary_pinAssign[pin * 2]]->IC |= (1 << mary_pinAssign[pin * 2 + 1]);
	}

	return;
}

#endif
