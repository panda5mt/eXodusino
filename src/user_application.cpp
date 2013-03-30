#include <libmary.h>

void setup(void)
{
	pinMode(P0_1,OUTPUT);
	Serial.begin(9600);
	Serial.println("Start..");
}

void loop(void)
{
	digitalWrite(P0_1,HIGH);
	delay(500);
	digitalWrite(P0_1,LOW);
	delay(500);
	Serial.println(millis()/ 1000,DEC);

}
