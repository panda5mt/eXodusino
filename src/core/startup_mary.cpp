/*
 * startup_mary.cpp
 *
 *  Created on: 2011/08/04
 *      Author: lynxeyed
 */

#include "libmary.h"


void setup(void);
void loop(void);

int main(void)
{

	setup_systick();	// for millis(),delay(us)
	setup_TIMER32_1();	// for micros(),delayMicroseconds(us),attachMicroseconds(func,usec)

	setup();

	while(1)
	{
		loop();
	}

}
