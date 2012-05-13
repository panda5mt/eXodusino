#include "gpio.h"


// IOCON:Cortex-M0 depend Settings
//#ifdef __NXP_LPC1114
#define PORT_BIT_COUNT 12 // up to 12 I/O lines per port
#define PORT_COUNT 4 // up to 4 ports

const uint8_t IOCON_LUT[PORT_COUNT][PORT_BIT_COUNT] = {
    { 0x0C, 0x10, 0x1C, 0x2C, 0x30, 0x34, 0x4C, 0x50, 0x60, 0x64, 0x68, 0x74 },
    { 0x78, 0x7C, 0x80, 0x90, 0x94, 0xA0, 0xA4, 0xA8, 0x14, 0x38, 0x6C, 0x98 },
    { 0x08, 0x28, 0x5C, 0x8C, 0x40, 0x44, 0x00, 0x20, 0x24, 0x54, 0x58, 0x70 },
    { 0x84, 0x88, 0x9C, 0xAC, 0x3C, 0x48 }
};

#define IOCONAddress(port,bit) ((volatile uint16_t * const) (LPC_IOCON_BASE + IOCON_LUT[port][bit]))
#define SetIOCON(port, bit, ioconmask, ioconbits) \
    *IOCONAddress((port),(bit)) = (*IOCONAddress((port),(bit)) & ~(ioconmask)) | (ioconbits)

typedef enum {
    GPIO_DIR_INPUT = 0,
    GPIO_DIR_OUTPUT = 1,
    IOCON_MODE_MASK = (3<<3),
    IOCON_MODE_PULLUP = (2<<3),
    IOCON_MODE_PULLDOWN = (1<<3),
    IOCON_MODE_REPEATER = (3<<3),
    IOCON_MODE_INACTIVE = (0<<3),
    IOCON_FUNC_MASK = 7,
    IOCON_FUNC_0 = 0,
    IOCON_FUNC_1 = 1,
    IOCON_FUNC_2 = 2,
    IOCON_FUNC_3 = 3,
    IOCON_FUNC_4 = 4,
    IOCON_FUNC_5 = 5,
    IOCON_FUNC_6 = 6,
    IOCON_FUNC_7 = 7,
    IOCON_HYS_MASK = (1<<5),
    IOCON_HYS_ENABLE = (1<<5),
    IOCON_HYS_DISABLE = (0<<5),
    IOCON_ADMODE_MASK = (1<<7),
    IOCON_ADMODE_ANALOG = (0<<7),
    IOCON_ADMODE_DIGITAL = (1<<7)
} IOCON_BITFIELD_ENUM;

//#endif

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
	if(pin < 22)			//arduinoPinAssign(0~21)
	{
		//IOCON settings use as GPIO
		if((arduino_pinAssign[pin * 2]) == 0)//PIO0_X
		{
			switch(arduino_pinAssign[pin * 2 + 1])
			{
			case 11:	//P0_11
				SetIOCON(arduino_pinAssign[pin * 2], arduino_pinAssign[pin * 2 + 1], IOCON_FUNC_MASK, IOCON_FUNC_1);
				break;
			default:	//P0_X
				SetIOCON(arduino_pinAssign[pin * 2], arduino_pinAssign[pin * 2 + 1], IOCON_FUNC_MASK, IOCON_FUNC_0);
				break;
			}
		}else if((arduino_pinAssign[pin * 2]) == 1)//PIO1_X
		{
			switch(arduino_pinAssign[pin * 2 + 1])
			{
				case _BIT0:
				case _BIT1:
				case _BIT2:
				case _BIT3:
					SetIOCON(arduino_pinAssign[pin * 2], arduino_pinAssign[pin * 2 + 1], IOCON_FUNC_MASK, IOCON_FUNC_1);
					break;
				default:
					SetIOCON(arduino_pinAssign[pin * 2], arduino_pinAssign[pin * 2 + 1], IOCON_FUNC_MASK, IOCON_FUNC_0);
					break;
			}
		}else //PIO2_X
		{
			SetIOCON(arduino_pinAssign[pin * 2], arduino_pinAssign[pin * 2 + 1], IOCON_FUNC_MASK, IOCON_FUNC_0);
		}

		if(state == OUTPUT)	//OUTPUT
		{
			LPC_GPIO[ arduino_pinAssign[pin * 2] ]->DIR |= (1 << arduino_pinAssign[pin * 2 + 1]);

		}else		//INPUT
		{
			LPC_GPIO[ arduino_pinAssign[pin * 2] ]->DIR &= ~((1 << arduino_pinAssign[pin * 2 + 1]));
		}
		return;
	}

	if(pin < 100) return;	//(20~99:reserved)

	if(pin < 200)			//maryPinAssign(100~119?)
	{
		pin = pin - 100;
		SetIOCON(mary_pinAssign[pin * 2], mary_pinAssign[pin * 2 + 1], IOCON_FUNC_MASK, IOCON_FUNC_0);
		if(state == OUTPUT)	//OUTPUT
		{
			LPC_GPIO[ mary_pinAssign[pin * 2] ]->DIR |= (1 << mary_pinAssign[pin * 2 + 1]);
		}else		//INPUT
		{
			LPC_GPIO[ mary_pinAssign[pin * 2] ]->DIR &= ~((1 << mary_pinAssign[pin * 2 + 1]));
		}
	}
	return;
 }

void digitalWrite(int pin,digitalWriteState state)
{
	if(pin < 22)			//arduinoPinAssign(0~21)
	{
		if(state == HIGH)	//HIGH
		{
			if(LPC_GPIO[ arduino_pinAssign[pin * 2] ]->DIR & 1<<arduino_pinAssign[pin * 2 + 1])//pin is output
			{
				LPC_GPIO[ arduino_pinAssign[pin * 2] ]->MASKED_ACCESS[ (1 << arduino_pinAssign[pin * 2 + 1]) ] = (1 << arduino_pinAssign[pin * 2 + 1]);
			}else//pin is input
			{
				SetIOCON(arduino_pinAssign[pin * 2], arduino_pinAssign[pin * 2 + 1], IOCON_MODE_MASK, IOCON_MODE_PULLUP);
			}
		}else		//LOW
		{
			if(LPC_GPIO[ arduino_pinAssign[pin * 2] ]->DIR & 1<<arduino_pinAssign[pin * 2 + 1])//pin is output
			{
				LPC_GPIO[ arduino_pinAssign[pin * 2] ]->MASKED_ACCESS[ (1 << arduino_pinAssign[pin * 2 + 1]) ] &= ~((1 << arduino_pinAssign[pin * 2 + 1]));
			}else // pin is input
			{
				SetIOCON(arduino_pinAssign[pin * 2], arduino_pinAssign[pin * 2 + 1], IOCON_MODE_MASK, IOCON_MODE_INACTIVE);
			}
		}

		return;
	}


	if(pin < 100) return;	//arduinoPinAssign(20~99:reserved)

	if(pin < 200)			//maryPinAssign(100~119?)
	{
		pin = pin - 100;
		if(state == HIGH)	//HIGH
		{
			if(LPC_GPIO[ mary_pinAssign[pin * 2] ]->DIR & 1<<mary_pinAssign[pin * 2 + 1])//pin is output
			{
				LPC_GPIO[ mary_pinAssign[pin * 2] ]->MASKED_ACCESS[ (1 << mary_pinAssign[pin * 2 + 1]) ] = (1 << mary_pinAssign[pin * 2 + 1]);
			}else//pin is input
			{
				SetIOCON(mary_pinAssign[pin * 2], mary_pinAssign[pin * 2 + 1], IOCON_MODE_MASK, IOCON_MODE_PULLUP);
			}
		}else		//LOW
		{
			if(LPC_GPIO[ mary_pinAssign[pin * 2] ]->DIR & 1<<mary_pinAssign[pin * 2 + 1])//pin is output
			{
				LPC_GPIO[ mary_pinAssign[pin * 2] ]->MASKED_ACCESS[ (1 << mary_pinAssign[pin * 2 + 1]) ] &= ~((1 << mary_pinAssign[pin * 2 + 1]));
			}else // pin is input
			{
				SetIOCON(mary_pinAssign[pin * 2], mary_pinAssign[pin * 2 + 1], IOCON_MODE_MASK, IOCON_MODE_INACTIVE);
			}
		}
	}
	return;
 }

int digitalRead(int pin)
{
	volatile int readValue;
	if(pin < 22)			//arduinoPinAssign(0~21)
	{
		readValue = (LPC_GPIO[ arduino_pinAssign[pin * 2] ]->MASKED_ACCESS[ (1 << arduino_pinAssign[pin * 2 + 1]) ])? 1 : 0;
		return readValue;
	}

	if(pin < 100) return 0;	//(20~99:reserved)

	if(pin < 200)			//maryPinAssign(100~199?)
	{
		pin = pin - 100;
		readValue = (LPC_GPIO[ mary_pinAssign[pin * 2] ]->MASKED_ACCESS[ (1 << mary_pinAssign[pin * 2 + 1]) ])? 1 : 0;
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
	if (pin >= 0 && pin < 22)			//arduinoPinAssign(0~21)
	{
		if (sense == 0) {
			LPC_GPIO[arduino_pinAssign[pin * 2]]->IS &= ~((1 << arduino_pinAssign[pin * 2 + 1]));
			/* single or double only applies when sense is 0(edge trigger). */
			if (single == 0)
				LPC_GPIO[arduino_pinAssign[pin * 2]]->IBE
						&= ~((1 << arduino_pinAssign[pin * 2 + 1]));
			else
				LPC_GPIO[arduino_pinAssign[pin * 2]]->IBE
						|= ((1 << arduino_pinAssign[pin * 2 + 1]));
		} else
			LPC_GPIO[arduino_pinAssign[pin * 2]]->IS |= ((1 << arduino_pinAssign[pin * 2 + 1]));

		if (event == 0)
			LPC_GPIO[arduino_pinAssign[pin * 2]]->IEV
					&= ~((1 << arduino_pinAssign[pin * 2 + 1]));
		else
			LPC_GPIO[arduino_pinAssign[pin * 2]]->IEV |= ((1 << arduino_pinAssign[pin * 2 + 1]));
	} else if (pin >= 22 && pin < 100) {
		//(22~99:reserved)
	} else if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;
		if (sense == 0) {
			LPC_GPIO[mary_pinAssign[pin * 2]]->IS &= ~((1 << mary_pinAssign[pin * 2 + 1]));
			/* single or double only applies when sense is 0(edge trigger). */
			if (single == 0)
				LPC_GPIO[mary_pinAssign[pin * 2]]->IBE &= ~((1 << mary_pinAssign[pin * 2 + 1]));
			else
				LPC_GPIO[mary_pinAssign[pin * 2]]->IBE |= ((1 << mary_pinAssign[pin * 2 + 1]));
		} else
			LPC_GPIO[mary_pinAssign[pin * 2]]->IS |= ((1 << mary_pinAssign[pin * 2 + 1]));

		if (event == 0)
			LPC_GPIO[mary_pinAssign[pin * 2]]->IEV &= ~((1 << mary_pinAssign[pin * 2 + 1]));
		else
			LPC_GPIO[mary_pinAssign[pin * 2]]->IEV |= ((1 << mary_pinAssign[pin * 2 + 1]));
	}

	return;
}

void GPIOIntEnable(int pin) {
	if (pin >= 0 && pin < 22)			//arduinoPinAssign(0~21)
	{

		LPC_GPIO[arduino_pinAssign[pin * 2]]->IE |= (1 << arduino_pinAssign[pin * 2 + 1]);
	} else if (pin >= 22 && pin < 100) { //(20~99:reserved)
	} else if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;
		LPC_GPIO[mary_pinAssign[pin * 2]]->IE |= (1 << mary_pinAssign[pin * 2 + 1]);
	}

	return;
}

void GPIOIntDisable(int pin) {
	if (pin >= 0 && pin < 22)			//arduinoPinAssign(0~21)
	{

		LPC_GPIO[arduino_pinAssign[pin * 2]]->IE &= ~((1 << arduino_pinAssign[pin * 2 + 1]));
	} else if (pin >= 22 && pin < 100) {//(22~99:reserved)
	} else if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;
		LPC_GPIO[mary_pinAssign[pin * 2]]->IE &= ~((1 << mary_pinAssign[pin * 2 + 1]));
	}

	return;
}

int GPIOIntStatus(int pin) {
	int regVal = 0;

	if (pin >= 0 && pin < 22)			//arduinoPinAssign(0~21)
	{
		if (LPC_GPIO[arduino_pinAssign[pin * 2]]->MIS
				& (1 << arduino_pinAssign[pin * 2 + 1])) {
			regVal = 1;
		}
	} else if (pin >= 22 && pin < 100) { //(22~99:reserved)
	} else if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;

		if (LPC_GPIO[mary_pinAssign[pin * 2]]->MIS
				& (1 << mary_pinAssign[pin * 2 + 1])) {
			regVal = 1;
		}
	}

	return regVal;
}

void GPIOIntClear(int pin) {
	if (pin >= 0 && pin < 22)			//arduinoPinAssign(0~21)
	{

		LPC_GPIO[arduino_pinAssign[pin * 2]]->IC |= (1 << arduino_pinAssign[pin * 2 + 1]);
	} else if (pin >= 22 && pin < 100) { //(22~99:reserved)

	} else if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;
		LPC_GPIO[mary_pinAssign[pin * 2]]->IC |= (1 << mary_pinAssign[pin * 2 + 1]);
	}

	return;
}
