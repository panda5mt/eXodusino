/*
 * SpiLcd.h
 *
 *  Created on: 2012/08/01
 *      Author: lynxeyed
 */

#ifndef SPILCD_H_
#define SPILCD_H_

/**************************************************************************//**
 * @file     SpiLcd.h
 * @brief    Arduino-like library for Cortex-M0 Series
 * @version	v.0.50
 * @date	1. August 2011.
 * @author	lynxeyed
 * @note	Copyright (c) 2012 Lynx-EyED's Klavier and Craft-works. <BR>
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

#include "SPI.h"
#include "gpio.h"

#ifdef __cplusplus
  extern "C" {
#endif

typedef enum {ST7735,Nokia6610,Nokia6100,PCF8833} LCD_DEVICES; // Defaults:ST7735

class SPILCD {
private:
	SSP_PORT port;
	LCD_DEVICES device;
	int LCD_VCC_ON;
	int LCD_CS;
	int LCD_RES;
	int _row;
	int _column;
	int _foreground;
	int _background;
	int _width;
	int _height;



public:
	SPILCD();		// announce the constructor to initialize
	~SPILCD();

	void reset();
	void reset(SSP_PORT port);
	void command( int value );
	void data( int value );
	void _window( int x, int y, int width, int height );
	void locate(int column, int row);
	void newline();
	void _putp( int colour );
	int  _putc( int value );
	void cls( void );
	void window( int x, int y, int width, int height );
	void WindowReset(void);
	void putp( int colour );
	void pixel( int x, int y, int colour );
	void fill( int x, int y, int width, int height, int colour );
	void blit( int x, int y, int width, int height, const int* colour );
	void bitblit( int x, int y, int width, int height, const char* bitstream );
	void foreground(int c);
	void background(int c);
	int  width();
	int  height();
	int  columns();
	int  rows();
};

extern SPILCD slcd;

#ifdef __cplusplus
  }
#endif
#endif /* SPILCD_H_ */
