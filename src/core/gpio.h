/*
 * gpio.h
 *
 *  Created on: 2011/07/27
 *      Author: lynxeyed
 */
#ifndef GPIO_H_
#define GPIO_H_

//#if defined (__USE_CMSIS)
#include "LPC11xx.h"

#ifdef __cplusplus
  extern "C" {
#endif


#define PORT_MAX_PINS 125 // Arduino/MARYで使うピン番号の最大の値

//#endif
//=======================================
// Define LPC_GPIO[4] (each top address)
//=======================================
static LPC_GPIO_TypeDef  (* const LPC_GPIO[4]) = { LPC_GPIO0, LPC_GPIO1, LPC_GPIO2, LPC_GPIO3 };
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
*	=======================================
*/
#define C17	(100)
#define C18	(101)

#define C21 (102)
#define C22 (103)
#define C23 (104)
#define C24 (105)
#define C25 (106)
#define C26 (107)
#define C27 (108)
#define C28 (109)

#define C31 (110)
#define C32 (111)
#define C33 (112)
#define C34 (113)
#define C35 (114)
#define C36 (115)
#define C37 (116)
#define C38 (117)

#define C41 (118)
#define C42 (119)
#define C43 (120)
#define C44 (121)
#define C45 (122)
#define C46 (123)
#define C47 (124)
#define GLED (125)
#define BLED (126)
#define RLED (127)

// For LPCXpresso LPC1114
#define P1_2	(100)
#define P1_1	(101)
#define P1_4	(102)
#define P1_11	(103)
#define P1_7	(104)
#define P1_5	(105)
#define P3_2	(106)
#define P2_0	(107)
#define P1_6	(108)
#define P0_1	(109)
#define P1_8	(110)
#define P0_3	(111)
#define P0_2	(112)
#define P3_4	(113)
#define P0_4	(114)
#define P3_5	(115)
#define P0_5	(116)
//#define P1_7	(117)
#define P1_9	(118)
#define P1_10	(119)
#define P0_6	(120)
#define P0_11	(121)
#define P0_8	(122)
#define P1_0	(123)
#define P0_9	(124)
#define P0_7	(125)
//#define P1_5	(126)
//#define P2_0	(127)

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

const unsigned int mary_pinAssign[] =
{
	1, _BIT2,	//CN1_7
	1, _BIT1,	//CN1_8

	1, _BIT4,	//CN2_1
	1, _BIT11,	//CN2_2
	1, _BIT7,	//CN2_3
	1, _BIT5,	//CN2_4
	3, _BIT2,	//CN2_5
	2, _BIT0,	//CN2_6
	1, _BIT6,	//CN2_7
	0, _BIT1,	//CN2_8

	1, _BIT8,	//CN3_1
	0, _BIT3,	//CN3_2
	0, _BIT2,	//CN3_3
	3, _BIT4,	//CN3_4
	0, _BIT4,	//CN3_5
	3, _BIT5,	//CN3_6
	0, _BIT5,	//CN3_7
	1, _BIT7,	//CN3_8

	1, _BIT9,	//CN4_1
	1, _BIT10,	//CN4_2
	0, _BIT6,	//CN4_3
	0, _BIT11,	//CN4_4
	0, _BIT8,	//CN4_5
	1, _BIT0,	//CN4_6
	0, _BIT9,	//CN4_7
	0, _BIT7,	//GLED
	1, _BIT5,	//BLED
	2, _BIT0	//RLED
};


// Arduino's pins assign
const unsigned int arduino_pinAssign[] =
{
	1, _BIT6,	//P1_6:D0/RX
	1, _BIT7,	//P1_7:D1/TX
	0, _BIT3,	//P0_3:D2
	1, _BIT9,	//P1_9:D3
	3, _BIT4,	//P3_4:D4
	2, _BIT4,	//P2_4:D5
	2, _BIT0,	//P2_0:D6
	2, _BIT3,	//P2_3:D7
	2, _BIT2,	//P2_2:D8
	2, _BIT1,	//P2_1:D9
	0, _BIT2,	//P0_2:D10

	0, _BIT9,	//P0_9:D11
	0, _BIT8,	//P0_8:D12
	0, _BIT6,	//P0_6:D13

	0, _BIT11,	//P0_11:A0/D14
	1, _BIT0,	//P1_0:A1/D15
	1, _BIT1,	//P1_1:A2/D16
	1, _BIT2,	//P1_2:A3/D17
	0, _BIT5,	//P0_5:SDA(A4)/D18
	0, _BIT4,	//P0_4:SCL(A5)/D19
	1, _BIT10,	//P1_10:A6/D20
	1, _BIT11,	//P1_11:A7/D21
//	3, _BIT0,	//DTR
};


typedef enum {INPUT, OUTPUT}pinModeState;
typedef enum {LOW, HIGH, CHANGE, RISING, FALLING}digitalWriteState;

void pinMode(int pin,pinModeState state);
void digitalWrite(int pin,digitalWriteState state);
int digitalRead(int pin);

void GPIOSetInterrupt(int pin, int sense, int single, int event);
void GPIOIntEnable(int pin);
void GPIOIntDisable(int pin);
void GPIOIntClear(int pin);
int GPIOIntStatus(int pin);

void PIOINT0_IRQHandler (void);
void PIOINT1_IRQHandler (void);
void PIOINT2_IRQHandler (void);
void PIOINT3_IRQHandler (void);
void GPIO_IRQHandler(void);

typedef void (* USER_GPIO_FUNC)(void);
void attachInterrupt(int pin,USER_GPIO_FUNC func, digitalWriteState mode) ;
void detachInterrupt(int pin);

#ifdef __cplusplus
  }
#endif

#endif /* GPIO_H_ */
