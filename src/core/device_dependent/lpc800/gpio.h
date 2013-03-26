/*
 * gpio.h
 *
 *  Created on: 2011/07/27
 *      Author: lynxeyed
 */
#ifndef GPIO_H_
#define GPIO_H_

//#if defined (__USE_CMSIS)
#include <lpcdevice.h>
#include "lpc8xx_gpio.h"

#ifdef __cplusplus
  extern "C" {
#endif


#define PORT_MAX_PINS 125 // Arduino/MARYで使うピン番号の最大の値

// For LPCXpresso LPC800
#define P0_0	(100)
#define P0_1	(101)
#define P0_2	(102)
#define P0_3	(103)
#define P0_4	(104)
#define P0_5	(105)
#define P0_6	(106)
#define P0_7	(107)
#define P0_8	(108)
#define P0_9	(109)
#define P0_10	(110)
#define P0_11	(111)
#define P0_12	(112)
#define P0_13	(113)
#define P0_14	(114)
#define P0_15	(115)
#define P0_16	(116)
#define P0_17	(117)

#define _BIT0 0//(1U << 0)
#define _BIT1 1//(1U << 1)
#define _BIT2 2//(1U << 2)
#define _BIT3 3//(1U << 3)
#define _BIT4 4//(1U << 4)
#define _BIT5 5//(1U << 5)
#define _BIT6 6//(1U << 6)
#define _BIT7 7//(1U << 7)
#define _BIT8 8//(1U << 8)
#define _BIT9 9//(1U << 9)
#define _BIT10 10//(1U << 10)
#define _BIT11 11//(1U << 11)
#define _BIT12 12//(1U << 12)
#define _BIT13 13//(1U << 13)
#define _BIT14 14//(1U << 14)
#define _BIT15 15//(1U << 15)
#define _BIT16 16//(1U << 16)
#define _BIT17 17//(1U << 17)

// Arduino's pins assign
const unsigned int xpresso_pinAssign[] =
{
	0, _BIT0,	//P0_0
	0, _BIT1,	//P0_1
	0, _BIT2,	//P0_2
	0, _BIT3,	//P0_3
	0, _BIT4,	//P0_4
	0, _BIT5,	//P0_5
	0, _BIT6,	//P0_6
	0, _BIT7,	//P0_7
	0, _BIT8,	//P0_8
	0, _BIT9,	//P0_9
	0, _BIT10,	//P0_10
	0, _BIT11,	//P0_11
	0, _BIT12,	//P0_12
	0, _BIT13,	//P0_13
	0, _BIT14,	//P0_14
	0, _BIT15,	//P0_15
	0, _BIT16,	//P0_16
	0, _BIT17	//P0_17
};


typedef enum {INPUT, OUTPUT}pinModeState;
typedef enum {LOW, HIGH, CHANGE, RISING, FALLING}digitalWriteState;

void pinMode(int pin,pinModeState state);
void digitalWrite(int pin,digitalWriteState state);
int digitalRead(int pin);

//todo: modify these API below
//void GPIOSetInterrupt(int pin, int sense, int single, int event);
//void GPIOIntEnable(int pin);
//void GPIOIntDisable(int pin);
//void GPIOIntClear(int pin);
//int GPIOIntStatus(int pin);
//
//void PIOINT0_IRQHandler (void);
//void PIOINT1_IRQHandler (void);
//void PIOINT2_IRQHandler (void);
//void PIOINT3_IRQHandler (void);
//void GPIO_IRQHandler(void);

typedef void (* USER_GPIO_FUNC)(void);
void attachInterrupt(int pin,USER_GPIO_FUNC func, digitalWriteState mode) ;
void detachInterrupt(int pin);

#ifdef __cplusplus
  }
#endif

#endif /* GPIO_H_ */
