#include <libmary.h>
#include <math.h>

void setup()
{
	Serial.begin(9600);		// XBeeのセットアップ
	pinMode(P0_7,OUTPUT);
}

void loop()
{

	Serial.println("\r\nStart...\r\n");
	while(1)
	{
		digitalWrite(P0_7,HIGH);
		delay(500);
		digitalWrite(P0_7,LOW);
		delay(500);
	}

}
