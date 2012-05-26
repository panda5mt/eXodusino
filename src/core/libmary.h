#ifndef LIBMARY_H_
#define LIBMARY_H_

/**
	@mainpage eXodusino
	@section abstruct 概要
		eXodusinoはCortex-M0でArduinoライクな開発が出来ることを目指すC++ライブラリです
	@section intro 始めに
		eXodusinoはARM Cortex-M0環境でもArduinoライクな環境を構築する為のライブラリです。
	@section motivation 背景
		このライブラリではお手軽に開発する事を目的としてC++ライブラリを作成しており、Arduinoライクな
		開発環境を提供しています。今後ここに新たなライブラリを追加し、より使いやすい環境を随時追加してゆきます
	@section environmen 環境
		arm-none-eabi-gcc-4.5.0以上またはarm-elf-gcc-4.5.0以上
		- WindowsではCodesourcery G++かLPCXpresso IDEが動く環境
		- Mac OSXではSnow Leopard(10.6.1以上)ではXcode 3.4以上がインストール、Lion(10.7)ではXCode 4.1以上がインストールされており、arm-elf-gcc-4.5.0以上がインストールされている事
	@section history 履歴
	- 2011/07/15    初版作成
	- 2012/05/27 Arduino,Wiring算術マクロを移植
 */

/**************************************************************************//**
 * @file     libmary.h
 * @brief    Arduino-like library for MARY(LPC1114)
 * @version	v.0.50
 * @date	1. August 2011.
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


#include "LPC11xx.h"
#include "system_LPC11xx.h"
#include "delay.h"
#include "gpio.h"
#include "uart.h"
#include "analogio.h"
#include "arithmetical.h"


// init for arduino-like settings
#define ARDUINO
#define EXODUSINO


#endif /* LIBMARY_H_ */
