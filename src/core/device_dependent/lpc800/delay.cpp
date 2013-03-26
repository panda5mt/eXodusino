/*
 * systick.cpp
 *
 *  Created on: 2011/08/11
 *      Author: atsu
 */
#if defined(USE_LPC800)
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

#if 0
  usTicks = LPC_TMR32B1->TC;				//usTicks = micros();
  while ((LPC_TMR32B1->TC - usTicks) < us);	//while ((micros() - usTicks) < us);
#endif
}

unsigned long micros(void)
{
#if 0
	return LPC_TMR32B1->TC;
#endif
	return 0;
}

//for micros() and delayMicroseconds()
void setup_TIMER32_1(void)
{
#if 0
	LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 10);	// Enable clock for CT32B1 module
	NVIC_DisableIRQ(TIMER_32_1_IRQn);
	LPC_TMR32B1->PR = 48;				//48MHz/48=1MHzに分周する
	LPC_TMR32B1->TCR = 1;						//タイマスタート
#endif
}

unsigned long attachMicroseconds(USER_TIMER_FUNC func,int us)
{
	//LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 10);	// Enable clock for CT32B1 module
#if 0

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
#endif
	return 0;
}

void detachMicroseconds(void)
{
#if 0
	LPC_TMR32B1->MR2 = 0xffffffff;			//us
	NVIC_DisableIRQ(TIMER_32_1_IRQn);
#endif
}

/*----------------------------------------------------------------------------
  Timer32_0_Handler
 *----------------------------------------------------------------------------*/
void TIMER32_1_IRQHandler (void)
{
#if 0
	if (LPC_TMR32B1->IR & (1 << 2)) // MR2 Interrupt
	{
		if(userfunc)userfunc();

		// Clear Flag
		LPC_TMR32B1->IR = (1 << 2);
	}
#endif

}

/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
  msTicks++;                        /* increment counter necessary in Delay() */
}

void setup_systick (void) {

#if defined(USE_LPC800)
	 SysTick->CTRL |= (0x1<<0);
#endif

	// Setup SysTick Timer for 1 msec interrupts
	// Configure System tick timer in 10msec period
	if (SysTick_Config(SystemCoreClock / 1000)) { /* Setup SysTick Timer for 1 msec interrupts  */
		while (1);                                  /* Capture error */
	}





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
#if defined(USE_LPC1114)
	LPC_SYSCON->SYSTICKCLKDIV = 0x08;
#endif
  }
#endif
}
#endif
