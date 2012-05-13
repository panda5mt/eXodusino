#include <libmary.h>

void setup()
{
	Serial.begin(9600);		// Setup XBee
}

void loop()
{
	Serial.println("\r\nStart...\r\n");
	
	while(1)
	{
        Serial.println(millis()/1000);
	}

}
