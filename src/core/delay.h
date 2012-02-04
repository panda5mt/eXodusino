/*
 * systick.h
 *
 *  Created on: 2011/08/11
 *      Author: atsu
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

/**************************************************************************//**
 * @file     systick.h
 * @brief    Arduino-like library for MARY(LPC1114)
 * @version	v.0.50
 * @date	1. August 2011.
 * @author	this library's assembled by @@dw256 and rebuild by @@lynxeyed_atsu
 * @note	Copyright (c) 2011 Lynx-EyED's Klavier and Craft-works. <BR>
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions: <BR>
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.<BR>
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/


#include "LPC11xx.h"
#include "system_LPC11xx.h"
#include "uart.h"
#ifdef __cplusplus
  extern "C" {
#endif



typedef void (* USER_TIMER_FUNC)(void);

void delay(unsigned long dlyTicks);
void delayMicroseconds(unsigned long us);
unsigned long millis(void);
//low level
void SysTick_Handler(void);
void setup_systick (void);
unsigned long micros(void);
unsigned long attachMicroseconds(USER_TIMER_FUNC func,int us);
void detachMicroseconds(void);

void setup_TIMER32_1(void);
void TIMER32_1_IRQHandler (void);

#endif /* SYSTICK_H_ */

#ifdef __cplusplus
  }
#endif
