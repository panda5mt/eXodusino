#include "gpio.h"


/*	=======================================
*	Macros and functions for Defining MARY's GPIO Assign
*
*	CN1_7,8		:	(PIO1_2,PIO1_1)
*					should be C17,C18
*
*	CN2_1...8	:	(PIO1_4,PIO1_11,PIO1_7,PIO1_5,PIO3_2,PIO2_0,PIO1_6,PIO0_1)
*					should be C21,C22,C23,C24,C25,C26,C27,C28
*
*	CN3_1...8	:	(PIO1_8,PIO0_3,PIO0_2,PIO3_4,PIO0_4,PIO3_5,PIO0_5,PIO1_7)
*					should be C31,C32,C33,C34,C35,C36,C37,C38
*
*	CN4_1...7	:	(PIO1_9,PIO1_10,PIO0_6,PIO0_11,PIO0_8,PIO1_0,PIO0_9)
*					should be C41,C42,C43,C44,C45,C46,C47
*
*	see also mary_pinAssign[...] in "gpio.h"
*	=======================================
*/
void pinMode(int pin,pinModeState state)
{
	if(pin < 20)			//arduinoPinAssign(0~19)
	{
		if(state == OUTPUT)	//OUTPUT
		{
			LPC_GPIO[ arduino_pinAssign[pin * 2] ]->DIR |= arduino_pinAssign[pin * 2 + 1];
		}else		//INPUT
		{
			LPC_GPIO[ arduino_pinAssign[pin * 2] ]->DIR &= ~(arduino_pinAssign[pin * 2 + 1]);
		}
		return;
	}

	if(pin < 100) return;	//(20~99:reserved)

	if(pin < 200)			//maryPinAssign(100~119?)
	{
		pin = pin - 100;
		if(state == OUTPUT)	//OUTPUT
		{
			LPC_GPIO[ mary_pinAssign[pin * 2] ]->DIR |= mary_pinAssign[pin * 2 + 1];
		}else		//INPUT
		{
			LPC_GPIO[ mary_pinAssign[pin * 2] ]->DIR &= ~(mary_pinAssign[pin * 2 + 1]);
		}
	}
	return;
 }

void digitalWrite(int pin,digitalWriteState state)
{
	if(pin < 20)			//arduinoPinAssign(0~19)
	{
		if(state == HIGH)	//HIGH
		{
			LPC_GPIO[ arduino_pinAssign[pin * 2] ]->MASKED_ACCESS[ arduino_pinAssign[pin * 2 + 1] ] = arduino_pinAssign[pin * 2 + 1];
		}else		//LOW
		{
			LPC_GPIO[ arduino_pinAssign[pin * 2] ]->MASKED_ACCESS[ arduino_pinAssign[pin * 2 + 1] ] &= ~(arduino_pinAssign[pin * 2 + 1]);
		}
		return;
	}

	if(pin < 100) return;	//arduinoPinAssign(20~99:reserved)

	if(pin < 200)			//maryPinAssign(100~119?)
	{
		pin = pin - 100;
		if(state == HIGH)	//HIGH
		{
			LPC_GPIO[ mary_pinAssign[pin * 2] ]->MASKED_ACCESS[ mary_pinAssign[pin * 2 + 1] ] = mary_pinAssign[pin * 2 + 1];
		}else		//LOW
		{
			LPC_GPIO[ mary_pinAssign[pin * 2] ]->MASKED_ACCESS[ mary_pinAssign[pin * 2 + 1] ] &= ~(mary_pinAssign[pin * 2 + 1]);
		}
	}
	return;
 }

int digitalRead(int pin)
{
	volatile int readValue;
	if(pin < 20)			//arduinoPinAssign(0~19)
	{
		readValue = (LPC_GPIO[ arduino_pinAssign[pin * 2] ]->MASKED_ACCESS[ arduino_pinAssign[pin * 2 + 1] ])? 1 : 0;
		return readValue;
	}

	if(pin < 100) return 0;	//(20~99:reserved)

	if(pin < 200)			//maryPinAssign(100~199?)
	{
		pin = pin - 100;
		readValue = (LPC_GPIO[ mary_pinAssign[pin * 2] ]->MASKED_ACCESS[ mary_pinAssign[pin * 2 + 1] ])? 1 : 0;
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
	if (pin >= 0 && pin < 20) //arduinoPinAssign(0~19)
	{
		if (sense == 0) {
			LPC_GPIO[arduino_pinAssign[pin * 2]]->IS &= ~(arduino_pinAssign[pin
					* 2 + 1]);
			/* single or double only applies when sense is 0(edge trigger). */
			if (single == 0)
				LPC_GPIO[arduino_pinAssign[pin * 2]]->IBE
						&= ~(arduino_pinAssign[pin * 2 + 1]);
			else
				LPC_GPIO[arduino_pinAssign[pin * 2]]->IBE
						|= (arduino_pinAssign[pin * 2 + 1]);
		} else
			LPC_GPIO[arduino_pinAssign[pin * 2]]->IS |= (arduino_pinAssign[pin
					* 2 + 1]);

		if (event == 0)
			LPC_GPIO[arduino_pinAssign[pin * 2]]->IEV
					&= ~(arduino_pinAssign[pin * 2 + 1]);
		else
			LPC_GPIO[arduino_pinAssign[pin * 2]]->IEV |= (arduino_pinAssign[pin
					* 2 + 1]);
	} else if (pin >= 20 && pin < 100) {
		//(20~99:reserved)
	} else if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;
		if (sense == 0) {
			LPC_GPIO[mary_pinAssign[pin * 2]]->IS &= ~(mary_pinAssign[pin * 2
					+ 1]);
			/* single or double only applies when sense is 0(edge trigger). */
			if (single == 0)
				LPC_GPIO[mary_pinAssign[pin * 2]]->IBE &= ~(mary_pinAssign[pin
						* 2 + 1]);
			else
				LPC_GPIO[mary_pinAssign[pin * 2]]->IBE |= (mary_pinAssign[pin
						* 2 + 1]);
		} else
			LPC_GPIO[mary_pinAssign[pin * 2]]->IS |= (mary_pinAssign[pin * 2
					+ 1]);

		if (event == 0)
			LPC_GPIO[mary_pinAssign[pin * 2]]->IEV &= ~(mary_pinAssign[pin * 2
					+ 1]);
		else
			LPC_GPIO[mary_pinAssign[pin * 2]]->IEV |= (mary_pinAssign[pin * 2
					+ 1]);
	}

	return;
}

void GPIOIntEnable(int pin) {
	if (pin >= 0 && pin < 20) //arduinoPinAssign(0~19)
	{

		LPC_GPIO[arduino_pinAssign[pin * 2]]->IE |= arduino_pinAssign[pin * 2
				+ 1];
	} else if (pin >= 20 && pin < 100) { //(20~99:reserved)
	} else if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;
		LPC_GPIO[mary_pinAssign[pin * 2]]->IE |= mary_pinAssign[pin * 2 + 1];
	}

	return;
}

void GPIOIntDisable(int pin) {
	if (pin >= 0 && pin < 20) //arduinoPinAssign(0~19)
	{

		LPC_GPIO[arduino_pinAssign[pin * 2]]->IE &= ~(arduino_pinAssign[pin * 2
				+ 1]);
	} else if (pin >= 20 && pin < 100) {//(20~99:reserved)
	} else if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;
		LPC_GPIO[mary_pinAssign[pin * 2]]->IE &= ~(mary_pinAssign[pin * 2 + 1]);
	}

	return;
}

int GPIOIntStatus(int pin) {
	int regVal = 0;

	if (pin >= 0 && pin < 20) //arduinoPinAssign(0~19)
	{
		if (LPC_GPIO[arduino_pinAssign[pin * 2]]->MIS
				& arduino_pinAssign[pin * 2 + 1]) {
			regVal = 1;
		}
	} else if (pin >= 20 && pin < 100) { //(20~99:reserved)
	} else if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;

		if (LPC_GPIO[mary_pinAssign[pin * 2]]->MIS
				& mary_pinAssign[pin * 2 + 1]) {
			regVal = 1;
		}
	}

	return regVal;
}

void GPIOIntClear(int pin) {
	if (pin >= 0 && pin < 20) //arduinoPinAssign(0~19)
	{

		LPC_GPIO[arduino_pinAssign[pin * 2]]->IC |= arduino_pinAssign[pin * 2
				+ 1];
	} else if (pin >= 20 && pin < 100) { //(20~99:reserved)

	} else if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;
		LPC_GPIO[mary_pinAssign[pin * 2]]->IC |= mary_pinAssign[pin * 2 + 1];
	}

	return;
}
