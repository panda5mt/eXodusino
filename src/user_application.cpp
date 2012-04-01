#include <libmary.h>

void setup()
{
	Serial.begin(9600);         // XBeeの初期化
	Serial.println("Start");
}



void loop()
{
	delay(1000);
    Serial.println(millis()/1000,DEC);
}
