#include <math.h>
#include <libmary.h>
#include "maryoled.h"


volatile int count = 0;
volatile float mag;
volatile float offsetx;
volatile float offsety;

void setup()
{
	Serial.begin(9600);


	oled.reset();			//for MARY-MB
	//oled.reset(LPCXSSP0);	//for MAPLE Board & LPCXpresso LPC1114

	offsetx = -0.756423894274328;
	offsety = 0.064179410646170;
	mag = 1;

}

void complex_mult(float ar,float ai,float br,float bi,float *cr,float *ci) {
  // C = A * B
  *cr = ar * br - ai * bi;
  *ci = ar * bi + ai * br;
}

float complex_abs2(float r,float i) {
  float ar,ai;
  complex_mult(r,i,r,-i,&ar,&ai);
  return ar;
}

int generateColor(int count, int base)
{
	int r,g,b;
	int d = (count % base) * 256 / base;
	int m = (int)(d / 42.667);

	switch(m) {
		case 0: r=0;          g=6*d;          b=255;         break;
		case 1: r=0;          g=255;          b=255-6*(d-43);break;
		case 2: r=6*(d-86);   g=255;          b=0;           break;
		case 3: r=255;        g=255-6*(d-129);b=0;           break;
		case 4: r=255;        g=0;            b=6*(d-171);   break;
		case 5: r=255-6*(d-214); g=0;         b=255;         break;
		default: r=0;         g=0;            b=0;           break;
	}

	return (((r >> 3) & 0x1f) << 11) | (((g >> 2) & 0x3f) << 5) | ((b >> 3) & 0x1f);
}
volatile int oldtime,nowtime;
void loop()
{
	Serial.print("描画開始時間=");
	Serial.print((oldtime = millis()),DEC);
	Serial.println("mSec");
	oled.window(0,0,128,128);
	for(int y = 0;y < 128;y++)
	{
		for(int x = 0;x < 128;x++) {
			float cr = (x - 64) / 64. / mag + offsetx;
			float ci = (y - 64) / 64. / mag + offsety;
			float zr = 0;
			float zi = 0;
			int t;
			for(t=0;t<512;t++)
			{
				if(complex_abs2(zr,zi) > 4) break;
				complex_mult(zr,zi,zr,zi,&zr,&zi);
				zr += cr;
				zi += ci;
			}
			oled.putp(generateColor(t,64));
		}
	}
	nowtime = millis();
	Serial.print("描画終了時間=");
	Serial.print(nowtime,DEC);
	Serial.println("mSec");
	Serial.print("描画時間=");
	Serial.print((nowtime - oldtime),DEC);
	Serial.println("mSec");
	mag = mag * 1.2;
//  offsety += 0.001;
//  offsetx += 0.0016;

  if(count++ > 100)
  {
    count = 0;
    offsetx = -0.756423894274328;
    offsety = 0.064179410646170;
    mag = 1;
    count = 0;
  }

	delay(1);

}


