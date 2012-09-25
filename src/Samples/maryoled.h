/*
 * MARYOLED.h
 *
 *  Created on: 2011/08/01
 *      Author: lynxeyed
 */

#ifndef MARYOLED_H_
#define MARYOLED_H_

/**************************************************************************//**
 * @file     maryoled.h
 * @brief    Arduino-like library for MARY(LPC1114)
 * @version	v.0.50
 * @date	1. August 2011.
 * @author	this library's assembled by @@dw256 and @@tedd_okano rebuild by @@lynxeyed_atsu
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

#include "SPI.h"
#include "gpio.h"

#ifdef __cplusplus
  extern "C" {
#endif

typedef enum {OLED,Nokia6610,Nokia6100,PCF8833} LCD_DEVICES; // Defaults:OLED

class MARYOLED {
private:
	SSP_PORT port;
	LCD_DEVICES device;
	int OLED_VCC_ON;
	int OLED_CS;
	int OLED_RES;
	int _row;
	int _column;
	int _foreground;
	int _background;
	int _width;
	int _height;

	/** Command list for the OLED controller */
	enum {
		SET_DISPLAY_MODE_ALL_OFF                = 0xA4,
		SET_COMMAND_LOCK                        = 0xFD,
		SET_SLEEP_MODE_ON                       = 0xAE,
		FRONT_CLOCK_DRIVER_OSC_FREQ             = 0xB3,
		SET_MUX_RATIO                           = 0xCA,
		SET_DISPAY_OFFSET                       = 0xA2,
		SET_DISPAY_START_LINE                   = 0xA1,
		SET_REMAP_COLOR_DEPTH                   = 0xA0,
		SET_GPIO                                = 0xB5,
		FUNCTION_SELECTION                      = 0xAB,
		SET_SEGMENT_LOW_VOLTAGE                 = 0xB4,
		SET_CONTRAST_CURRENT_FOR_COLOR_ABC      = 0xC1,
		MASTER_CONTRAST_CURRENT_CONTROL         = 0xC7,
		LOOKUP_TABLE_FOR_GRAYSCALE_PULSE_WIDTH  = 0xB8,
		USE_BUILT_IN_LINEAR_LUT					= 0xB9,
		SET_RESET_PRECHARGE_PERIOD              = 0xB1,
		ENHANCE_DRIVING_SCHEME_CAPABILITY       = 0xB2,
		SET_PRECHARGE_VOLTAGE                   = 0xBB,
		SET_SECOND_PRECHARGE_VOLTAGE            = 0xB6,
		SET_VCOMH_VOLTAGE                       = 0xBE,
		SET_DISPLAY_MODE_RESET                  = 0xA6,
		SET_COLUMN_ADDRESS                      = 0x15,
		SET_ROW_ADDRESS                         = 0x75,
		WRITE_RAM_COMMAND                       = 0x5C,
		SET_SLEEP_MODE_OFF                      = 0xAF
	};
    /** Constants for power() function */
    enum  {
        OFF   = 0,  /**< : to turning-OFF  */
        ON          /**< : to turning-ON   */
    };


public:
	MARYOLED();		// announce the constructor to initialize
	~MARYOLED();

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

extern MARYOLED oled;

#ifdef __cplusplus
  }
#endif
#endif /* MARYOLED_H_ */
