#include <libmary.h>
#include <SPI.h>

#define LCD_CS	C33//4 //cs
#define LCD_DC	C21//5  //data command
#define LCD_RES	C31//6 //reset
//MOSI	11	C47
//CLK	13	C43
#define DC_DATA HIGH
#define DC_CMD LOW

//#define STICK_A 7
//#define STICK_B 8
//#define STICK_C 9
//#define STICK_D 10
//#define STICK_CT 2


#define select_disp()   digitalWrite(LCD_CS,LOW)	//PORTD &= ~(1 << PORTD4)
#define unselect_disp() digitalWrite(LCD_CS,HIGH)	//PORTD |=  (1 << PORTD4)

#define set_disp_command()	digitalWrite(LCD_DC,LOW)	//PORTD &= ~(1 << PORTD5)
#define set_disp_data()		digitalWrite(LCD_DC,HIGH)	//PORTD |=  (1 << PORTD5)

/* SSD1283A Unique Value	 */
/* MUST be need for SSD1283A */
#define OFS_COL			2
#define OFS_RAW			0
#define MAX_X			130
#define MAX_Y			130



void sendCmd(unsigned int cmd){
  select_disp();
  set_disp_command();
  //  shiftOut2(PIN_MOSI,PIN_CLK,MSBFIRST,cmd);
  SPI.transfer(cmd);
  set_disp_data();
}

void sendData(unsigned int data){
  select_disp();
  set_disp_data();
  //shiftOut2(PIN_MOSI,PIN_CLK,MSBFIRST,data);
  SPI.transfer(data);
}

void sendData16(unsigned int data1,unsigned int data2){
  select_disp();
  set_disp_data();
  //shiftOut2(PIN_MOSI,PIN_CLK,MSBFIRST,data);
  SPI.transfer(data1);
  SPI.transfer(data2);
}

void sendColor(unsigned int color){
  sendData(color&0x00ff);
}




void initDisplay(){
  select_disp();

  digitalWrite(LCD_RES, LOW);
  delay(80);
  digitalWrite(LCD_RES, HIGH);
  delay(20);

  /* SSD1283A */
  sendCmd(0x10); 			/* Power Control (1) */
  sendData16(0x2f,0x8e); 	/* Onchip DCDC Clock,Fine*2 StartCycle,VGH unregurated */
  /* StepUpCycle fosc,Internal OPAMP Current reserved,Sleep Mode OFF */

  sendCmd(0x11); 			/* Power Control (2) */
  sendData16(0x00,0x0c); 	/* VGH/VCI ratio x4 */

  sendCmd(0x07); 			/* Display Control */
  sendData16(0x00,0x21); 	/* Nomalize source out zero, Vartical Scroll not pafomed */
  /* 1 Divison Display,Source output GND, Gate output GVOFFL */

  sendCmd(0x28); 			/* VCOM-OTP1 */
  sendData16(0x00,0x06);

  sendCmd(0x28); 			/* VCOM-OTP1 */
  sendData16(0x00,0x05);

  sendCmd(0x27); 			/* VCOM-OTP */
  sendData16(0x05,0x7f);

  sendCmd(0x29); 			/* VCOM-OTP2 */
  sendData16(0x89,0xa1);

  sendCmd(0x00); 			/* Oscillator On */
  sendData16(0x00,0x01);
  delay(150);

  sendCmd(0x29); 			/* VCOM-OTP2 */
  sendData16(0x80,0xb0);
  delay(50);

  sendCmd(0x29); 			/* VCOM-OTP2 */
  sendData16(0xff,0xfe);

  sendCmd(0x07); 			/* Display Control */
  sendData16(0x00,0x23);
  delay(50);

  sendCmd(0x07); 			/* Display Control (Confirm) */
  sendData16(0x00,0x23);
  delay(50);

  sendCmd(0x07); 		/* Display Control */
  sendData16(0x00,0x33); 	/* Nomalize source out zero, Vartical Scroll not pafomed */
  /* 1 Divison Display,,Source output GND (OFF) */
  /* Gate output Selected VGH, others GVOFFL */

  sendCmd(0x01); 		/* Driver Output Control */
  sendData16(0x21,0x83); 	/* Reversal ON ,Cs On Common,BGR,Scanning Mounting Method */
  /* Output Shift Direction of Gate Driver G131->G0, */
  /* Output Shift Direction of Source Driver S0->S395, */
  /* Number of Gate Driver 131 */

  sendCmd(0x2f); 		/* ??? */
  sendData16(0xff,0xff);

  sendCmd(0x2c); 		/* Oscillator frequency */
  sendData16(0x80,0x00); 	/* 520kHz */

  sendCmd(0x03); 		/* Entry mode */
  sendData16(0x68,0x30); 	/* Colour mode 65k,OE defines Display Window,D-mode from internal ram */
  /* Horizontal increment & Vertical increment & AM 0 Horizontal */

  sendCmd(0x40); 		/* Set Offset */
  sendData16(0x00,0x02);

  sendCmd(0x27); 		/* Further bias current setting */
  sendData16(0x05,0x70); 	/* Maximum */

  sendCmd(0x02); 		/* LCD-Driving-Waveform Control */
  sendData16(0x03,0x00); 	/* the odd/even frame-select signals and the N-line inversion */
  /* signals are EORed for alternating drive */

  sendCmd(0x0b); 		/* Frame Cycle Control */
  sendData16(0x58,0x0c); 	/* Amount of Overlap 4 clock cycle */
  /* Delay amount of the source output 2 clock cycle */
  /* EQ period 2 clock cycle, Division Ratio 2 */

  sendCmd(0x12); 		/* Power Control 3 */
  sendData16(0x06,0x09); 	/* Set amplitude magnification of VLCD63 = Vref x 2.175 */

  sendCmd(0x13); 		/* Power Control 4 */
  sendData16(0x31,0x00); 	/* Set output voltage of VcomL = VLCD63 x 1.02 */

  sendCmd(0x2a); 			/* Test Commands ? */
  sendData16(0x1d,0xd0);

  sendCmd(0x2b); 			/* Test Commands ? */
  sendData16(0x0a,0x90);

  sendCmd(0x2d); 			/* Test Commands ? */
  sendData16(0x31,0x0f);
  delay(100);

  sendCmd(0x44); 			/* Set CAS Address */
  sendData16(0x83,0x00);

  sendCmd(0x45); 			/* Set RAS Address */
  sendData16(0x83,0x00);

  sendCmd(0x21); 			/* Set RAM Address */
  sendData16(0x00,0x00);

  sendCmd(0x1e); 			/* Power Control 5 */
  sendData16(0x00,0xbf);   /* VcomH = VLCD63 x 0.99 */
  delay(1);

  sendCmd(0x1e); 			/* Power Control 5 */
  sendData16(0x00,0x00); 	/* VcomH =VLCD63 x 0.36 */
  delay(100);

  unselect_disp();
}

void resetArea(){
  int x=0,y=0;
  int xwidth=130 , yheight=130;

  select_disp();

  /* Set CAS Address */
  sendCmd(0x44);
  sendData16(OFS_COL + xwidth - 1, OFS_COL + x);

  /* Set RAS Address */
  sendCmd(0x45);
  sendData16(OFS_RAW + yheight - 1, OFS_RAW + y);

  /* Set RAM Address */
  sendCmd(0x21);
  sendData16(OFS_RAW + y, OFS_COL + x);

  /* Write RAM */
  sendCmd(0x22);

  set_disp_data();
  unselect_disp();
}

void fillScreen(unsigned int color_H,unsigned int color_L){
  select_disp();
  int i;
  resetArea();
  for(i=0;i<16900;i++){
    sendData16(color_H,color_L);
  }
  unselect_disp();
}
