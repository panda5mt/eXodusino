/*
 Print.cpp
 Base class that provides print() and println()
 Created on: 2012/03/17
 */
#ifndef Print_h
#define Print_h

#include <string.h>
#include "LPC11xx.h"

const char radix_bin[] = "01";
const char radix_oct[] = "01234567";
const char radix_dec[] = "0123456789";
const char radix_hex[] = "0123456789ABCDEF";

typedef enum {
	BYTE = 0x01, /*!< 1バイトのアスキーコードが表示される */
	BIN = 0x02, /*!< dataで与えられた数値を2進数で表示する */
	OCT = 0x08, /*!< dataで与えられた数値を8進数で表示する */
	DEC = 0x0A, /*!< dataで与えられた数値を10進数で表示する */
	HEX = 0x10
/*!< dataで与えられた数値を16進数で表示する */
} RADIX_FORMAT;


class Print {
private:
	//	  	RADIX_FORMAT format;
public:
	virtual void write(const char c) = 0;
	void write(const char *s,int length);
    void write(const char *s) { return write((const char *)s, strlen(s)); }

	void print(const char c);
	void print(const char *s);
	void print(int val, RADIX_FORMAT format);

	virtual void println(void);
	void println(const char c);
	void println(const char *s);
	void println(int val, RADIX_FORMAT format);
};

#endif
