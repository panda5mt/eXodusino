#include <libmary.h>
#include <stdlib.h>
#include <SPI1.h>

#define S9706_GATE	6		//Low->High:光量の積算。S9706の6番->(D6に接続)
#define S9706_RANGE	P0_1	//受光感度調整。S9706の4番->(P0_1)に接続。

//     PIO2_1	: SCLK -> S9706の5番(CK)
//     PIO2_2	: MISO -> S9706の1番(Dout)

void setup()
{
	pinMode(S9706_GATE,OUTPUT);
	pinMode(S9706_RANGE,OUTPUT);
	Serial.begin(9600);
	SPI1.setBitLength(12);		//12bit ADC
	SPI1.setDataMode(SPI_MODE2);
	SPI1.begin();
	Serial.println("Start");
}

int r,g,b;

void loop()
{
	digitalWrite(S9706_GATE,LOW);
	digitalWrite(S9706_RANGE,HIGH);

	Serial.println("積算を開始");
	digitalWrite(S9706_GATE,HIGH);
	delay(4);


	Serial.println("積算を終了");
	Serial.println("データリード開始");

	digitalWrite(S9706_GATE,LOW);

	r = SPI1.transfer(0xfff);
	g = SPI1.transfer(0xfff);
	b = SPI1.transfer(0xfff);

	Serial.print("r = ");
	Serial.println(r,DEC);
	Serial.print("g = ");
	Serial.println(g,DEC);
	Serial.print("b = ");
	Serial.println(b,DEC);

	delay(1000);

}
