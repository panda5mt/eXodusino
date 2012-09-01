#include <libmary.h>

void setup()
{
	Serial.begin(9600);		// XBeeのセットアップ
    Serial.println("\r\nStart...");

}

void loop()
{
    Serial.println(millis()/1000,DEC);  // 起動後の経過時間を1秒ごとに更新
    delay(1000);
}

