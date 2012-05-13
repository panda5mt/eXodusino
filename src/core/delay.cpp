/*
 * systick.cpp
 *
 *  Created on: 2011/08/11
 *      Author: atsu
 */

#include "delay.h"

volatile static unsigned long msTicks;                            /* counts 1ms timeTicks */
volatile USER_TIMER_FUNC userfunc;	//user function's pointer

/*------------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 ms)
 *------------------------------------------------------------------------------*/
void delay (unsigned long dlyTicks) {
  volatile unsigned long curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks);
}


unsigned long millis(void)
{
	return msTicks;
}

void delayMicroseconds (unsigned long us)
{
  volatile unsigned long usTicks;

  //LPC_TMR16B0->TC = 0;	//reset timer counter
  usTicks = LPC_TMR32B1->TC;				//usTicks = micros();
  while ((LPC_TMR32B1->TC - usTicks) < us);	//while ((micros() - usTicks) < us);

}

unsigned long micros(void)
{
	return LPC_TMR32B1->TC;
}

//for micros() and delayMicroseconds()
void setup_TIMER32_1(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 10);	// Enable clock for CT32B1 module
	NVIC_DisableIRQ(TIMER_32_1_IRQn);
	LPC_TMR32B1->PR = 48;				//48MHz/48=1MHzに分周する
	LPC_TMR32B1->TCR = 1;						//タイマスタート
}

unsigned long attachMicroseconds(USER_TIMER_FUNC func,int us)
{
	//LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 10);	// Enable clock for CT32B1 module
	LPC_TMR32B1->TCR = 0;				//タイマストップ
	LPC_TMR32B1->TC = 0;

	if(us <= 1)return 0;

//	LPC_TMR32B1->PR = 48;				//48MHz/48=1MHzに分周する
	LPC_TMR32B1->MR2 = us - 1;			//us

	LPC_TMR32B1->MCR = (0x3 << 6); // clear at MR2 and Interrupt

	NVIC_EnableIRQ(TIMER_32_1_IRQn);
	NVIC_SetPriority(TIMER_32_1_IRQn,0);//割り込みレベル
	LPC_TMR32B1->TCR = 1;				//タイマスタート

	userfunc = func;

	return 0;
}

void detachMicroseconds(void)
{
	LPC_TMR32B1->MR2 = 0xffffffff;			//us
	NVIC_DisableIRQ(TIMER_32_1_IRQn);

}

/*----------------------------------------------------------------------------
  Timer32_0_Handler
 *----------------------------------------------------------------------------*/
void TIMER32_1_IRQHandler (void)
{
	if (LPC_TMR32B1->IR & (1 << 2)) // MR2 Interrupt
	{
		if(userfunc)userfunc();

		// Clear Flag
		LPC_TMR32B1->IR = (1 << 2);
	}
}

/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
  msTicks++;                        /* increment counter necessary in Delay() */
}

void setup_systick (void) {

	//LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

	// Setup SysTick Timer for 1 msec interrupts
	// Configure System tick timer in 10msec period
	volatile unsigned long period = SystemCoreClock / 1000;     // Period for 1msec SYSTICK
	SysTick_Config(period);             // Configuration

#if 1
  if ( !(SysTick->CTRL & SysTick_CTRL_CLKSOURCE_Msk) )
  {
	/* When external reference clock is used(CLKSOURCE in
	Systick Control and register bit 2 is set to 0), the
	SYSTICKCLKDIV must be a non-zero value and 2.5 times
	faster than the reference clock.
	When core clock, or system AHB clock, is used(CLKSOURCE
	in Systick Control and register bit 2 is set to 1), the
	SYSTICKCLKDIV has no effect to the SYSTICK frequency. See
	more on Systick clock and status register in Cortex-M3
	technical Reference Manual. */
	LPC_SYSCON->SYSTICKCLKDIV = 0x08;
  }
#endif
}

