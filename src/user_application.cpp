#include <libmary.h>
#include <SD.h>
#include <SPI1.h>

#define LRCLK		6					// LRCLK(BU9480F) -> D6(eXodusino)
#define AudioBufRow	256					// length of proc_r
volatile uint16_t	empty_c	= 0;		// Column
volatile uint16_t	proc_r	= 0;		// Row
uint16_t	AudioBuf[2][AudioBufRow];	//AudioBuf[empty_c][proc_r]
bool dac_semp;							// オーディオバッファ書き込み完了フラグ true:完了, false:まだ


uint16_t br;
FRESULT rc;

void readSound(void)
{
	volatile int16_t i=0,j=0;
	while(1){
		if(i != empty_c)
		{
			if(j >= AudioBufRow - 1)
			{
				i = empty_c;			// DACが使用してない(使い終わった)バッファを選択
				j = 0;
			}
		}

		if (j < AudioBufRow - 1)
		{
			rc = pf_read(AudioBuf[i], sizeof(uint16_t)*256, &br);	// Read a chunk of file
			if (rc || !br)break;

			j = j + 256;

		}
		if(j >= AudioBufRow - 1)
		{				// 音声バッファは満タン？(DACがリードしてもOK？)
			dac_semp = true;
		}
	}
}


void playSound(void)
{
	static uint16_t i,j;					// AudioBuf[j][i]
	uint16_t k;
	if(i >= AudioBufRow - 1)
	{
		if(dac_semp)						// empty_cカラムは書き込み完了？(=true？)
		{
			i = 0;
			empty_c =(empty_c == 1)?0:1;	// DACが使い終えたバッファをempty_cとする
			j = (empty_c == 1)?0:1;			// decode()関数がデータを貯めているバッファに切り替え
			dac_semp = false;				// empty_cは空なのでfalse

		}else
		{									// 書き込み完了してない？
			return;
		}
	}
	//DACへデータ送信
	k =(AudioBuf[j][i++]);
	digitalWrite(LRCLK,HIGH);
	SPI1.transfer(k);

	k =(AudioBuf[j][i++]);
	digitalWrite(LRCLK,LOW);
	SPI1.transfer(k);

	return;
}

void setup()
{
	// XBeeの初期化
	Serial.begin(9600);

	//BU9480Fの初期化
	pinMode(LRCLK,OUTPUT);
	SPI1.setBitLength(16);
	SPI1.setClockDivider(SPI_CLOCK_DIV2);
	SPI1.begin();

	// SDCard初期化のtry&catch
	if (!SDFile.begin())
	{
		Serial.println("Cannot detect SDCard") ;
		return ;
	}

	Serial.println("card initialized.") ;
	rc = SDFile.open("test.wav") ;

	if (rc)
	{
		// ファイルオープン失敗
		Serial.println("Failed to open...") ;
		SDFile.close() ;
		while(1);		// 動作停止
	}

}

void loop(void)
{
	Serial.println("Start...");
	attachMicroseconds(playSound,20000);
	detachMicroseconds();
	delayMicroseconds(1000000);
	Serial.println("play start");
	// 45マイクロ秒ごと=22.05kHzごとにplaySound()をコールする
	attachMicroseconds(playSound,45);
	readSound();

	SDFile.close() ;		// ファイルをクローズ
	detachMicroseconds();	// 割り込みを停止

	Serial.println(""); 			//改行
	Serial.println("play end.");
	while(1);

}

