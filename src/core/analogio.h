#ifndef ANALOGIO_H_
#define ANALOGIO_H_
/**************************************************************************//**
 * @file     analogio.h
 * @brief    Arduino-like library for eXodusino(LPC1114)
 * @version	v.0.50
 * @date	3. May 2012.
 * @author	@@lynxeyed_atsu
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


#include "gpio.h"

#ifdef __cplusplus
  extern "C" {
#endif

void analogWrite(int pinnum, int value);
//low level functions for software PWM
void setup_TIMER16_0(void);
void TIMER16_0_IRQHandler(void);
void setup_TIMER16_1(void);
void TIMER16_1_IRQHandler(void);
#ifdef __cplusplus
  }
#endif
#endif /* ANALOGIO_H_ */
