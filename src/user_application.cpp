#include <libmary.h>
#include <math.h>

#define RED		2//14
#define BLU		14
#define GRE		15

#define WAIT_T	150
#define OFF_POWER	255
#define HIGH_POWER	(0)
#define MID_POWER	(255 - 30)

void hsv2rgb(int hue)
{
	if(hue >= 360)
		hsv2rgb(hue - 360);

	double dh = hue * 1.0;
	double ds = 0.87;
	double dv = 0.53;

	int r = 0;
	int g = 0;
	int b = 0;

	//int inn = (int)floor( dh  / 60.0 );
	int inn = (int)(dh / 60) % 6;
	if(inn < 0)
		inn *= -1;

	double fl = ( dh  / 60.0 ) - (double)inn;
    //if((inn & 1)!=0) fl = 1 - fl; // if i is even
	if(inn == 2) fl = 1 - fl; // if i is even

	double p = dv * ( 1 - ds );
	double q = dv * ( 1 - ds  * fl );
	double t = dv * (1 - (1 - fl) * ds);

	////計算結果のR,G,Bは0.0～1.0なので255倍
	dv = dv * 255.0;
	p = p * 255.0;
	q = q * 255.0;
	t = t * 255.0;

	if(dv > 255)	dv = 255;
	if(t > 255)		t  = 255;
	if(p > 255)		p  = 255;
	if(q > 255)		q  = 255;

	switch( inn )
	{
		case 0: r = (int)dv; g = (int) t;  b = (int)p;	break;
		case 1: r = (int)q;  g = (int) dv; b = (int)p;	break;
		case 2: r = (int)p;  g = (int) dv; b = (int)q;	break;
		case 3: r = (int)p;  g = (int) q;  b = (int)dv;	break;
		case 4: r = (int)t;  g = (int) p;  b = (int)dv;	break;
		default: r = (int)dv; g = (int) p;  b = (int)q;	break;
	}
	Serial.print("r = ");
	Serial.println(r,DEC);
	Serial.print("g = ");
	Serial.println(g,DEC);
	Serial.print("b = ");
	Serial.println(b,DEC);
	Serial.println("");

	analogWrite(RED,255 - r);
	analogWrite(GRE,255 - g);
	analogWrite(BLU,255 - b);

}

void deleteMessage(void)
{
	analogWrite(RED,OFF_POWER);
	analogWrite(GRE,OFF_POWER);
	analogWrite(BLU,OFF_POWER);
	analogWrite(RED,MID_POWER);
	delay(WAIT_T);
	analogWrite(RED,OFF_POWER);
	analogWrite(BLU,HIGH_POWER);
	delay(WAIT_T);
	analogWrite(RED,OFF_POWER);
	analogWrite(BLU,OFF_POWER);
}

void encodeMessage(int byteString)
{
	int hue;
	char ch;

	ch = (char) byteString & 0x0f;
	hue = map(ch, 0, 15, 0, 359);
	hsv2rgb(hue);
//	hsv2rgb(150);

	delay(WAIT_T);

	ch = (char) (byteString >> 4) & 0x0f;
	hue = map(ch, 0, 15, 0, 359);
	hsv2rgb(hue);
//	hsv2rgb(150);

	delay(WAIT_T);

/*
	analogWrite(RED,OFF_POWER);
	analogWrite(BLU,OFF_POWER);

	for(int i=8;i!=0;i--)
	{
		analogWrite(RED,MID_POWER + 15);
		analogWrite(BLU,MID_POWER);
		delay(WAIT_T);

		if(byteString & 0x80)
		{
			analogWrite(BLU,OFF_POWER);
			analogWrite(RED,MID_POWER);
		}else
		{
			analogWrite(BLU,HIGH_POWER);
			analogWrite(RED,OFF_POWER);
		}
		delay(WAIT_T);
		analogWrite(RED,OFF_POWER);
		analogWrite(BLU,OFF_POWER);
		byteString = byteString << 1;

	}
	*/
	return;
}
void setup()
{
	Serial.begin(9600);		// XBeeのセットアップ
	pinMode(RED,OUTPUT);	// LEDのピンセットアップ
	pinMode(BLU,OUTPUT);
	pinMode(GRE,OUTPUT);
}

void loop()
{

	Serial.println("\r\nStart...\r\n");
	digitalWrite(RED,LOW);
	digitalWrite(BLU,LOW);

	for(int i=0;i<5;i++)
	{
		deleteMessage();
	}
	while(1)
	for(int i = 0; i < 360;i = i + 22)
	{
		hsv2rgb(i);
		Serial.print("h = ");
		Serial.println(i,DEC);
		delay(2000);
	}

	while(1)
	{
		if (Serial.available() > 0)
		{ // 受信したデータが存在する
			int incomingByte = Serial.read(); // 受信データを読み込む
			Serial.print(incomingByte,BYTE);
			encodeMessage(0/*incomingByte*/);
		}
		deleteMessage();		// 送信データ無き場合無効データを送出
	}

}

