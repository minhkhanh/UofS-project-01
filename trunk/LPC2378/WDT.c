 #include "lpc23xx.h"
 #include "MyDefine.h"
 __irq void WDTHandler()
{
	VICVectAddr = 0;
}
__irq void WDTIRQTimer()
{
	char sec[9];
	itoa(WDTV*16 / 12000000, sec);
	sendchars("Board restart sau ");
	sendchars(sec);
	sendchars(" giay nua!\r\n");
	T0IR        = 1;
	VICVectAddr = 0;
}
void WDTTimerInit()
{
	T0MR0         = 11999999;                       /* 1msec = 12000-1 at 12.0 MHz */
  	T0MCR         = 3;                           /* Interrupt and Reset on MR0  */
  	T0TCR         = 1;                           /* Timer0 Enable               */
	VICVectAddr4  = (unsigned long)WDTIRQTimer;/* Set Interrupt Vector        */
  	VICVectCntl4  = 15;                          /* use it for Timer0 Interrupt */
  	VICIntEnable  = (1  << 4);                   /* Enable Timer0 Interrupt     */	
}
void WDTInit(int sec)
{
	VICVectAddr0 = (unsigned long)WDTHandler;	/*Set Interrupt Vector*/
	VICVectCntl0 = 0;				/*use it for Timer0 Interrupt*/
	VICIntEnable = (1 << 0);		/*Enable Timer0 Interrupt*/
	WDTC = (int)((float)sec * 1200000 / 16);					// 300000 khoang 4 giay		 t = clc * WDTC * 4
	WDMOD = 0x03;					/* 0x01= Interrupt */ /* 0x02= reset */

	WDTTimerInit();
}
void WDTFeed()
{
	WDFEED = 0xAA;
	WDFEED = 0x55;
}
