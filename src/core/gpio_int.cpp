#include "gpio.h"

#define EXTERNAL_NUM_INTERRUPTS 22
volatile static USER_GPIO_FUNC intFunc[EXTERNAL_NUM_INTERRUPTS];

void attachInterrupt(int pin, USER_GPIO_FUNC func, digitalWriteState mode) {
	pinMode(pin, INPUT);

	switch (mode) {
	case LOW:
		GPIOSetInterrupt(pin, 1, 0, 0);
		break;
	case HIGH:
		GPIOSetInterrupt(pin, 1, 0, 1);
		break;
	case CHANGE:
		GPIOSetInterrupt(pin, 0, 1, 0);
		break;
	case RISING:
		GPIOSetInterrupt(pin, 0, 0, 1);
		break;
	case FALLING:
		GPIOSetInterrupt(pin, 0, 0, 0);
		break;
	default:
		break;
	}


	if (pin >= 0 && pin < 22) //arduinoPinAssign(0~22)
	{
		intFunc[pin] = func;

		switch (arduino_pinAssign[pin * 2]) {
		case 0:
			NVIC_EnableIRQ(EINT0_IRQn);
			break;
		case 1:
			NVIC_EnableIRQ(EINT1_IRQn);
			break;
		case 2:
			NVIC_EnableIRQ(EINT2_IRQn);
			break;
		case 3:
			NVIC_EnableIRQ(EINT3_IRQn);
			break;
		}
	} else if (pin >= 22 && pin < 100) {
		//(22~99:reserved)
	} else if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;
		intFunc[pin] = func;

		switch (mary_pinAssign[pin * 2]) {
		case 0:
			NVIC_EnableIRQ(EINT0_IRQn);
			break;
		case 1:
			NVIC_EnableIRQ(EINT1_IRQn);
			break;
		case 2:
			NVIC_EnableIRQ(EINT2_IRQn);
			break;
		case 3:
			NVIC_EnableIRQ(EINT3_IRQn);
			break;
		}
	}

	GPIOIntEnable(pin);

	return;
}

void detachInterrupt(int pin) {
	GPIOIntDisable(pin);

	if (pin >= 0 && pin < 22) //arduinoPinAssign(0~22)
	{
		intFunc[pin] = 0;
		if (LPC_GPIO[arduino_pinAssign[pin * 2]]->IE == 0) {
			switch (arduino_pinAssign[pin * 2]) {
			case 0:
				NVIC_DisableIRQ(EINT0_IRQn);
				break;
			case 1:
				NVIC_DisableIRQ(EINT1_IRQn);
				break;
			case 2:
				NVIC_DisableIRQ(EINT2_IRQn);
				break;
			case 3:
				NVIC_DisableIRQ(EINT3_IRQn);
				break;
			}
		}
	}
	else if (pin >= 22 && pin < 100) {//(22~99:reserved)
	} else if (pin >= 100 && pin < 200) //maryPinAssign(100~119?)
	{
		pin = pin - 100;
		intFunc[pin] = 0;
		if (LPC_GPIO[mary_pinAssign[pin * 2]]->IE == 0) {
			switch (mary_pinAssign[pin * 2]) {
			case 0:
				NVIC_DisableIRQ(EINT0_IRQn);
				break;
			case 1:
				NVIC_DisableIRQ(EINT1_IRQn);
				break;
			case 2:
				NVIC_DisableIRQ(EINT2_IRQn);
				break;
			case 3:
				NVIC_DisableIRQ(EINT3_IRQn);
				break;
			}
		}
	}
	return;
}

void GPIO_IRQHandler(void) {
	for (int i = 0; i < EXTERNAL_NUM_INTERRUPTS; i++) {
		if (GPIOIntStatus(i)) {
			GPIOIntClear(i);

			if (intFunc[i])
				intFunc[i]();
		}
	}
}

void PIOINT0_IRQHandler(void) {
	GPIO_IRQHandler();
	return;
}

void PIOINT1_IRQHandler(void) {
	GPIO_IRQHandler();
	return;
}

void PIOINT2_IRQHandler(void) {
	GPIO_IRQHandler();
	return;
}

void PIOINT3_IRQHandler(void) {
	GPIO_IRQHandler();
	return;
}
