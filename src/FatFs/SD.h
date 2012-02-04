/*
 * SD.h
 *
 *  Created on: 2011/08/19
 *      Author: atsu
 */

#ifndef SD_H_
#define SD_H_


#include <libmary.h>
#include <SPI.h>
#include "pff.h"

#ifdef __cplusplus
  extern "C" {
#endif


class  PETITFS{
private:

	FATFS fatfs;			// File system object
	DIR dir;				// Directory object
	FILINFO fno;			// File information object
	WORD bw, br, i;
	char buff[64];
	FRESULT rc;

public:
	int SDCS;				//CS pin
	PETITFS();
	~PETITFS();

	BOOL begin(SSP_PORT port);
	BOOL begin(int cs_pin);
	BOOL begin();
	BOOL exists();
	BOOL mkdir();
	FRESULT open(const char* filename); //???
	BOOL remove(const char* filename);
	BOOL rmdir(const char* filename);

	int available();
	void close();
	void flush();
	int peek();
	unsigned long position();
	void print(const char *s);
	void print(int val, RADIX_FORMAT format);
	void println(const char *s);
	void println(int val, RADIX_FORMAT format) ;
	BOOL seek(unsigned long pos);
	unsigned long size();
	int read();
	void write(const char *s);
	void write(const char *s,int length);
};






extern PETITFS SDFile;



#ifdef __cplusplus
  } //extern "C"
#endif

#endif /* SD_H_ */
