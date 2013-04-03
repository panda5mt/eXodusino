#include <libmary.h>

void setup(void)
{
	Serial.begin(9600);
}

void loop(void)
{
	delay(1000);
	Serial.println(millis()/ 1000,DEC);
}
