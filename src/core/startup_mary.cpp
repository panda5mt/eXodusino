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

	setup_systick();
	setup_TIMER32_1();

	setup();

	while(1)
	{
		loop();
	}

}
