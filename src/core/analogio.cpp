#include "analogio.h"

#define PWM_MAX_PINS 2
static int pwm_pin_num[PWM_MAX_PINS];			// PWM出力に使うピン番号を格納する
static int pwm_duty_value[PWM_MAX_PINS];		// それぞれのピンのデューティを格納する
static int pwm_already_inuse = 0;				// すでに登録しているピンの数
static int pwm_init_done = 0;
//static int pwm_interrpt_loopnum[PWM_MAX_PINS]; // ユークリッドの互除法を使うので割り込み回数をカウント


void analogWrite(int pinnum, int value)
{
	int i;
	int pwm_using_num = -1;			// PWMを割り当てているピン

	if(pwm_init_done == 0)
	{
		setup_TIMER16_0();
		pwm_init_done = 1;
	}

	for(i = 0; i < PWM_MAX_PINS; i++)
	{
		if(pwm_pin_num[i] == pinnum)	// すでに登録されているピン
		{								// デューティをセット
			pwm_using_num = i;
			pwm_duty_value[i] = value;
			if(value == -1)pwm_already_inuse--;
			break;
		}
	}

	if(pwm_using_num == -1)//新規登録の場合
	{
		if(PWM_MAX_PINS > pwm_already_inuse)	// まだ登録可能
		{
			for(i = 0; i < PWM_MAX_PINS; i++)
			{
				if((pwm_duty_value[i] == -1)&&(value != -1))	// 登録されていないピン
				{
					pwm_using_num = i;
					pwm_pin_num[i] = pinnum;	// ピン番号登録

					pwm_duty_value[i] = value;	// dutyセット
					pwm_already_inuse++;		// 使用中のピン数を+1
					pinMode(pwm_pin_num[i],OUTPUT);
					break;
				}
			}
		}

	}

	switch(pwm_using_num)
	{
		case 0: LPC_TMR16B0->MR1 = pwm_duty_value[i]; break;
		case 1: LPC_TMR16B0->MR2 = pwm_duty_value[i]; break;
		//case 2: LPC_TMR16B1->MR1 = pwm_duty_value[i]; break;
		//case 3: LPC_TMR16B1->MR2 = pwm_duty_value[i]; break;
		default: break;
	}

	//pwm_eucledean_algorithm(pwm_using_pins);// 互除法演算ルーチンへ
	return;
}

void pwm_eucledean_algorithm(int pwm_using_pins)
{
	// reserved for future use.
}

//low level functions for software PWM
void setup_TIMER16_0(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1U << 7);

    // 1周期490Hzで分解能8bit => 約125kHz  (125kHz = 48MHz / 382)
    LPC_TMR16B0->PR = 382;   // Pre-Scaler

    LPC_TMR16B0->MR3 = 255;     // Interval
    LPC_TMR16B0->MR2 = 200;
    LPC_TMR16B0->MR1 = 200;
    // Interval Interrupt Operation
    // Clear TC when MR3 match
    // Interrupt when MR1 reset /MR2 reset /MR3 match
    LPC_TMR16B0->MCR = ((3U << 9)|(1U << 6)|(1U << 3));

    // Enable Interrupt
    NVIC_EnableIRQ(TIMER_16_0_IRQn);
    NVIC_SetPriority(TIMER_16_0_IRQn, 3);

    // Start Timer
    LPC_TMR16B0->TCR = 1;

    for(int i=0; i < PWM_MAX_PINS; i++)	// まだ登録可能
    {
    	pwm_duty_value[i] = -1;	// 登録されていないピン
    }
}

//===========================
// Timer16 Interrupt Handler
//===========================
void TIMER16_0_IRQHandler(void)
{
	if (LPC_TMR16B0->IR & (1U << 1))		//MR1INT = case0
	{
		//Do something
		if(pwm_duty_value[0] != -1) digitalWrite(pwm_pin_num[0],LOW);
		// Clear Flag
		LPC_TMR16B0->IR = (1U << 1);
	}

    if (LPC_TMR16B0->IR & (1U << 2))		//MR2INT = case1
    {
        //Do something
    	if(pwm_duty_value[1] != -1) digitalWrite(pwm_pin_num[1],LOW);
        // Clear Flag
        LPC_TMR16B0->IR = (1U << 2);
    }

    else if(LPC_TMR16B0->IR & (1U << 3))	//MR3INT
    {
    	//Do something
    	for(int i = 0; i < PWM_MAX_PINS; i++)
    	{
    		if(pwm_duty_value[i] != -1)
    		{
    			if(pwm_duty_value[i] > 1) digitalWrite(pwm_pin_num[i],HIGH);
    		}
    	}
		// Clear Flag
		LPC_TMR16B0->IR = (1U << 3);
    }

}
