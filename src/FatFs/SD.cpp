/*
 * SD.cpp
 *
 *  Created on: 2011/08/19
 *      Author: atsu
 */
#include <libmary.h>
#include "SD.h"
//#include "pff.h"

PETITFS SDFile;

PETITFS::PETITFS()
{
	this->SDCS = C33;
}

PETITFS::~PETITFS()
{
}
BOOL PETITFS::begin(int cs_pin)
{
	BOOL rt;
	this->SDCS = cs_pin;
	rt = begin();
	return (rt);
}

BOOL PETITFS::begin(SSP_PORT port)
{
	BOOL rt;
	SPI.begin(port);
	if(port == LPCXSSP0)
		rt = begin(P1_4);	//for MAPLE
	else
		rt = begin();
	return (rt);
}

BOOL PETITFS::begin()
{
	rc = pf_mount(&fatfs);
	return (!rc)? TRUE:FALSE;
}

BOOL PETITFS::exists()
{
	return FALSE;
}

BOOL PETITFS::mkdir()
{
	return FALSE;
}

FRESULT PETITFS::open(const char* filename) //???
{
	rc = pf_open(filename);
	return rc;
}


BOOL PETITFS::remove(const char* filename)
{
	return FALSE;
}

BOOL PETITFS::rmdir(const char* filename)
{
	return FALSE;
}

int PETITFS::available(){}
void PETITFS::close(){}
void PETITFS::flush(){}
int PETITFS::peek(){}
unsigned long PETITFS::position(){}
void PETITFS::print(const char *s){}
void PETITFS::print(int val, RADIX_FORMAT format){}
void PETITFS::println(const char *s){}
void PETITFS::println(int val, RADIX_FORMAT format){}
BOOL PETITFS::seek(unsigned long pos){}
unsigned long PETITFS::size(){}

int PETITFS::read()
{
	rc = pf_read(buff, sizeof(char), &br);	/* Read a chunk of file */
	if (rc || !br)
		return -1;			/* Error or end of file */
	else
		return (int)buff[0];
}
void PETITFS::write(const char *s){}
void PETITFS::write(const char *s,int length){}

/*
class FILE {
private:
	char buff[64];
	FRESULT rc;

public:
	FILE();
	~FILE();
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
*/
