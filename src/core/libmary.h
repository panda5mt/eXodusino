#ifndef LIBMARY_H_
#define LIBMARY_H_

/**
	@mainpage MARY-DUINO (Beta)
	@section abstruct 概要
		MARY-DUINOはNXP製LPC1114を搭載したMARY基板でArduinoライクな開発が出来ることを目指すC++ライブラリです
	@section intro 始めに
		CQ出版発行・圓山宗智氏によるトランジスタ技術増刊「2枚入り！組み合わせ自在！超小型ARMマイコン基板」に付属している基板をArduinoライクな環境で開発する為の
		ライブラリです。
	@section motivation 背景
		「2枚入り！組み合わせ自在！超小型ARMマイコン基板」に付属している基板の開発において、よく整備されているライブラリが圓山氏により準備されており、
		とても使いやすい環境が提供されています。このライブラリではよりお手軽に開発する事を目的としてC++ライブラリをフルスクラッチで作成しており、Arduinoライクな
		開発環境を提供しています。今後ここに新たなライブラリを追加し、より使いやすい環境を随時追加してゆきます
	@section environmen 環境
		arm-none-eabi-gcc-4.5.0以上またはarm-elf-gcc-4.5.0以上
		- WindowsではCodesourcery G++かLPCXpresso IDEが動く環境
		- Mac OSXではSnow Leopard(10.6.1以上)ではXcode 3.4以上がインストール、Lion(10.7)ではXCode 4.1以上がインストールされており、arm-elf-gcc-4.5.0以上がインストールされている事
	@section history 履歴
	- 2011/07/15    初版作成
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



// init for arduino-like settings
#define ARDUINO
#define EXODUSINO


#endif /* LIBMARY_H_ */
