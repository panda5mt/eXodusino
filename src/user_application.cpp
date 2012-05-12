#include <libmary.h>
#include <math.h>

#define RED		14
#define BLUE	15
#define WAIT_T	150

void delMessage(void)
{
	digitalWrite(RED,LOW);
	digitalWrite(BLUE,LOW);
	digitalWrite(RED,HIGH);
	delay(WAIT_T);
	digitalWrite(RED,LOW);
	digitalWrite(BLUE,HIGH);
	delay(WAIT_T);
	digitalWrite(RED,LOW);
	digitalWrite(BLUE,LOW);
}

void encMessage(int byteString)
{
	char ch = (char) byteString;

	digitalWrite(RED,LOW);
	digitalWrite(BLUE,LOW);

	for(int i=8;i!=0;i--)
	{
		digitalWrite(RED,HIGH);
		digitalWrite(BLUE,HIGH);
		delay(WAIT_T);

		if(byteString & 0x80)
		{
			digitalWrite(BLUE,LOW);
			digitalWrite(RED,HIGH);
		}else
		{
			digitalWrite(BLUE,HIGH);
			digitalWrite(RED,LOW);
		}
		delay(WAIT_T);

		byteString = byteString << 1;

	}
	return;
}


void setup()
{
	Serial.begin(9600);		// XBeeのセットアップ
	pinMode(RED,OUTPUT);	// LEDのピンセットアップ
	pinMode(BLUE,OUTPUT);
}

void loop()
{
	Serial.println("\r\nStart...\r\n");
	digitalWrite(RED,LOW);
	digitalWrite(BLUE,LOW);

	for(int i=0;i<5;i++)
	{
		delMessage();
	}
	while(1)
	{
		if (Serial.available() > 0)
		{ // 受信したデータが存在する
			int incomingByte = Serial.read(); // 受信データを読み込む
			Serial.print(incomingByte,BYTE);
			encMessage(incomingByte);
		}
		delMessage();
	}

}
