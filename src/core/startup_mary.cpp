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
	SystemCoreClockUpdate();	// for plls
	setup_systick();			// for millis(),delay(ms)
	setup_TIMER32_1();			// for micros(),delayMicroseconds(us),attachMicroseconds(func,usec)

#if defined(USE_LPC800)
	SwitchMatrix_Init();
	GPIOInit();
#endif

	setup();

	while(1)
	{
		loop();
	}

}
